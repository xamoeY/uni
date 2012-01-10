/* aufgabe9.c
 * Einfaches Programm zum Test des gcc-Compilers und der zugehörigen Tools.
 * Bitte setzen Sie in das Programm ihre Matrikelnummer ein und probieren
 * Sie alle der folgenden Operationen aus:
 *
 * Funktion         Befehl                                   erzeugt
 * ----------------+--------------------------------------+----------------
 * C -> Assembler:  gcc -O2 -S aufgabe9.c                 -> aufgabe9.s
 * C -> Objektcode: gcc -O2 -c aufgabe9.c                 -> aufgabe9.o
 * C -> Programm:   gcc -O2 -o aufgabe9.exe aufgabe9.c    -> aufgabe9.exe
 * Disassembler:    objdump -d aufgabe9.o
 * Ausführen:       aufgabe9.exe
 */

#include <stdio.h>

int main( int argc, char** argv )
{ int matrikelnummer = 7654321;

  printf( "Meine Matrikelnummer ist %d\n", matrikelnummer );
  return 0;
}
