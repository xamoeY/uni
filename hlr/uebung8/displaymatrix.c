/****************************************************************************/
/****************************************************************************/
/**                                                                        **/
/**  	      	   TU Muenchen - Institut fuer Informatik                  **/
/**                                                                        **/
/** Copyright: Dr. Thomas Ludwig                                           **/
/**            Thomas A. Zochler                                           **/
/**            Andreas C. Schmidt                                          **/
/**                                                                        **/
/** File:      displaymatrix.c                                             **/
/**                                                                        **/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Beschreibung der Funktion DisplayMatrix:                               **/
/**                                                                        **/
/** Die Funktion DisplayMatrix gibt eine Matrix ( double v[...] )          **/
/** in einer "ubersichtlichen Art und Weise auf die Standardausgabe aus.   **/
/**                                                                        **/
/** Die "Ubersichtlichkeit wird erreicht, indem nur ein Teil der Matrix    **/
/** ausgegeben wird. Aus der Matrix werden die Randzeilen/-spalten sowie   **/
/** sieben Zwischenzeilen ausgegeben.                                      **/
/**                                                                        **/
/** Die Funktion erwartet einen Zeiger auf ein lineares Feld, in dem       **/
/** die Matrixeintraege wie in einer zweidimensionalen Matrix abgelegt     **/
/** sind.                                                                  **/
/**                                                                        **/
/** S"amtliche Ergebnisse werden auch Gnuplot-gerecht in ein file names    **/
/** "function.data" im lokalen Verzeichnis ausgegeben. Mittels des "plot"- **/
/** Skripts laesst sich das Ergebnis graphisch veranschaulichen.           **/
/****************************************************************************/

/****************************************************************************/
/** Beschreibung der Funktion DisplayMatrixAddr:                           **/
/**                                                                        **/
/** Gleiche Funktionalitaet wie DisplayMatrix, mit dem einzigen Unter-	   **/
/** schied, dass ein Dreifachpointer auf die Matrix erwartet wird, und	   **/
/** somit mittels Addressrechnung auf die Matrix zugegriffen wird.         **/
/**                                                                        **/
/** Ein zusaetzlicher Parameter gibt an, auf welche der zweidimensionalen  **/
/** Matrizen zugegriffen werden soll.                                      **/
/****************************************************************************/

#include "partdiff-seq.h"
#include <stdio.h>

//void DisplayMatrix ( char *s, double *v, int interlines )
//{
//  FILE *file;
//  int x,y;
//  int lines = 8 * interlines + 9;
//
//  printf ( "%s\n", s );
//  for ( y = 0; y < 9; y++ )
//  {
//    for ( x = 0; x < 9; x++ )
//    {
//      printf ( "%7.4f", v[y*(interlines+1)*lines+x*(interlines+1)]);
//    }
//    printf ( "\n" );
//  }
//  fflush ( stdout );
//  file=fopen("function.data","w");
//  for ( y = 0; y < 9; y++)
//  {
//    for ( x = 0; x < 9; x++)
//    {
//      fprintf(file," %7.4f  %7.4f  %7.4f\n", (double)(x)*0.125,(double)(y)*0.125,
//      v[y*(interlines+1)*lines+x*(interlines+1)]);
//    }
//    fprintf(file,"\n");
//  }
//  fclose(file);
//}

void DisplayMatrix ( char *s, double *v, int interlines , int rank , int size, int from, int to )
{
  int x,y;
  int lines = 8 * interlines + 9;
  MPI_Status status;

  /* first line belongs to rank 0 */
  if (rank == 0)
    from--;

  /* last line belongs to rank size-1 */
  if (rank + 1 == size)
    to++;

  if (rank == 0)
    printf ( "%s\n", s );

  for ( y = 0; y < 9; y++ )
  {
    int line = y*(interlines+1);

    if (rank == 0)
    {
      /* check whether this line belongs to rank 0 */
      if (line < from || line > to)
      {
        /* use the tag to receive the lines in the correct order
         * the line is stored in v, because we do not need it anymore */
        MPI_Recv(v, lines, MPI_DOUBLE, MPI_ANY_SOURCE, 42 + y, MPI_COMM_WORLD, &status);
      }
    }
    else
    {
      if (line >= from && line <= to)
      {
        /* if the line belongs to this process, send it to rank 0
         * (line - from + 1) is used to calculate the correct local address */
        MPI_Send(&v[(line - from + 1)*lines], lines, MPI_DOUBLE, 0, 42 + y, MPI_COMM_WORLD);
      }
    }

    for ( x = 0; x < 9; x++ )
    {
      if (rank == 0)
      {
        if (line >= from && line <= to)
        {
          /* this line belongs to rank 0 */
          printf ( "%7.4f", v[line*lines + x*(interlines+1)]);
        }
        else
        {
          /* this line belongs to another rank and was received above */
          printf ( "%7.4f", v[x*(interlines+1)]);
        }
      }
    }

    if (rank == 0)
      printf ( "\n" );
  }
  fflush ( stdout );
}

void DisplayMatrixAddr ( char *s, double ***v, int interlines, int matrixnum )
{
  FILE *file;
  int x,y;

  printf ( "%s\n", s );
  for ( y = 0; y < 9; y++ )
  {
    for ( x = 0; x < 9; x++ )
    {
      printf ( "%7.4f", v[matrixnum][y*(interlines+1)][x*(interlines+1)]);
    }
    printf ( "\n" );
  }
  fflush ( stdout );
  file=fopen("function.data","w");
  for ( y = 0; y < 9; y++)
  {
    for ( x = 0; x < 9; x++)
    {
      fprintf(file," %7.4f  %7.4f  %7.4f\n", (double)(x)*0.125,(double)(y)*0.125,
      v[matrixnum][y*(interlines+1)][x*(interlines+1)]);
    }
    fprintf(file,"\n");
  }
  fclose(file);

}

