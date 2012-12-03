#lang racket
(require "butterfly-module.rkt")

;Aufgabe 1

;Unser erster Gedanke war wie wir am einfachsten prüfen können welches von 2 gegeben Elementen dominant ist.
;Hierzu haben wir uns überlegt die Merkmale in einer Liste zu speichern, die von links nach rechts nach der stärksten dominanz absteigend geordnet ist.
;So kann man einfach die Positionen 2 gegebener Merkmale in der Liste prüfen und weis, dass das Merkmal mit mit dem niedrigeren Positions-Wert das dominante ist.
;Um dies zu überprüfen haben wir einige hiflsfunktionen implementiert.
;Wir fanden diesen Weg schöner und einfacher als z.B. viele if oder cond auszuwerten und zu verschachteln.

;Danach haben wir uns überlegt wie wir einen Schmetterling eigentlich darstellen wollen. Wir haben beschlossen dafür ebenfalls Listen zu verwenden.
;Ein Schmetterlin wird in unserem Konzept durch eine Liste mit 3 Unterlisten repräsentiert. Jeweils eine Unterliste für Musterung, Flügelfarbe und Fühlerform.
;Jede Unterliste enthält 2 Merkmale, das dominante und das rezesive.

;Der nächste Gedanke war wie man beliebige rezesive zu einem als dominant gegebenes Merkmal findet. Hier war die Überlegung unsere gegeben Liste mit den jeweiligen Merkmalen
;einfach nur ab unserem als dominant gegebenen Merkmal zu betrachten, so haben wir eine Liste aus allen möglichen rezesiven Merkmalen die in Frage kommen.
;Um von diesen nur ein zufälliges auszwählen shuffeln wir die Liset und nehmen uns von der zufällig geordneten Liste einfach das erste Element.
;Auf um diese Überlegung umzusetzen haben wir Hilfsmethoden implementiert.

;Danach haben wir versucht zu gegeben dominanten Merkmalen einen Schmetterling in der von uns überlegten Form aufzubauen.

;Danach haben wir uns damit beschäftigt wie wir nun die Kinder zu 2 gegebenen Eltern erzeugen. Hierzu haben wir zuerst Hilfsmethoden geschrieben, die uns nur die beiden Merkmale zur Musterung,
;die beiden Merkmale zur Flügelfarbe oder die beiden Merkmale zur Fühlerform als Liste geben geschrieben. Mithilfe derer konnten dann aus den beiden Merkmalen jeweils zufällig eines auswählen,
;welches dem Kind vererbt wird.

;Zuletzt mussten wir nur noch eine Funktion schreiben die die Eltern und die Kinder darstellt. Hier haben wir den Punkt, dass es immer unterschiedlich viele Kinder sein können mit Hilfsfunktion
;und rekursion umgesetzt.







;3 Listen welche die möglichen Merkmale enthalten. 1 Liste für die möglichen Musterungen, eine für die möglichen Flügelformen
;und eine für die Fühlerformen. Alle Listen sind von links nach rechts nach ihrer Dominanz sotiert wobei links das am stärksten
;dominante ist und es danach absteigen weitergeht.
(define Musterungen '("plain" "dots" "stripes"))
(define Flügelfarben '("red" "green" "blue" "yellow"))
(define Fühlerformen '("straight" "curved"))

;Eine Funktion, mit der man die Position eines Wertes in einer Liste bestimmen kann. 
;Wird benötigt, wenn man von 2 Merkmalen das dominante bestimmmen möchte.
(define (get-listenposition liste string)
  (if (equal? string (car liste)) 
      1
      (+ 1 (get-listenposition (cdr liste) string))))

;Eine Funktion, die benötigt wird um mögliche rezesive Musterungen, Flügelfarben oder Fühlerformen zu einem dominanten Merkmal zu finden.
;Die Möglichen rezesiven Merkmale werden als Liste ausgegeben.
(define (finde-rezesive-helper liste string)
  (if (equal? string (car liste))
      liste
      (finde-rezesive-helper (cdr liste) string)))

;Gibt eine zufällige rezesive Musterung zu einem dominanten Muster aus.
;Wird beim erstellen eines Schmetterlings mit gegeben dominanten Merkmale benötigt.
(define (finde-rezesive-musterung musterung)
  (car (shuffle (finde-rezesive-helper Musterungen musterung))))

;Gibt eine zufällige rezesive Flügelfarbe zu einer dominanten Flügelfarbe aus.
;Wird beim erstellen eines Schmetterlings mit gegeben dominanten Merkmale benötigt.
(define (finde-rezesive-flügelfarbe flügelfarbe)
  (car (shuffle (finde-rezesive-helper Flügelfarben flügelfarbe))))

;Gibt eine zufällige rezesive Fühlerform zu einer dominanten Fühlerform aus.
;Wird beim erstellen eines Schmetterlings mit gegeben dominanten Merkmale benötigt.
(define (finde-rezesive-fühlerform fühlerform)
  (car (shuffle (finde-rezesive-helper Fühlerformen fühlerform))))

;Bestimmt die dominante Musterung von 2 gegebenen Musterungen.
;Wird beim erzeugen der Kinder benötigt.
(define (get-dominante-musterung musterung1 musterung2)
  (if (<= (get-listenposition Musterungen musterung1) (get-listenposition Musterungen musterung2))
      (string->symbol musterung1)
      (string->symbol musterung2)))

;Bestimmt die dominante Flügelfarbe von 2 gegebenen Flügelfarben.
;Wird beim erzeugen der Kinder benötigt.
(define (get-dominante-flügelfarbe flügelfarbe1 flügelfarbe2)
  (if (<= (get-listenposition Flügelfarben flügelfarbe1) (get-listenposition Flügelfarben flügelfarbe2))
      (string->symbol flügelfarbe1)
      (string->symbol flügelfarbe2)))

;Bestimmt die dominante Fühlerform von 2 gegebenen Fühlerformen.
;Wird beim erzeugen der Kinder benötigt.
(define (get-dominante-fühlerform fühlerform1 fühlerform2)
  (if (<= (get-listenposition Fühlerformen fühlerform1) (get-listenposition Fühlerformen fühlerform2))
      (string->symbol fühlerform1)
      (string->symbol fühlerform2)))

;Erzeugt einen Schmetterling, mit gegebenen dominanten Merkmalen und zufälligen, passenden rezesiven Merkmalen.
;Um die passenden rezesiven Merkmale zu finden werden die zuvor definierten Funktionen zum finden eines zufälligen
;rezesiven Merkmals verwendet.
;Ein Schmetterling wird als Liste von 3 Unterlisten mit jeweils 2 Elementen dargestellt. Die 1. Unterliste enthält die beiden 
;(dominante und rezesive) Musterungen, die 2. Liste die beiden Flügelfarben und die 3. Liste die beiden Fühlerformen.
(define (erzeuge-schmetterling musterung-dominant flügelfarbe-dominant fühlerform-dominant)
  (list (list musterung-dominant (finde-rezesive-musterung musterung-dominant)) (list flügelfarbe-dominant (finde-rezesive-flügelfarbe flügelfarbe-dominant)) (list fühlerform-dominant (finde-rezesive-fühlerform fühlerform-dominant))))

;Eine Funktion um die Musterungen eines Schmetterlings als Liste zu bekommen.
;Wird benötigt um zu besitmmen welches der beiden Merkmale an das Kind vererbt wird.
(define (get-musterungen liste)
  (first liste))

;Eine Funktion um die Flügelfarben eines Schmetterlings als Liste zu bekommen.
;Wird benötigt um zu besitmmen welches der beiden Merkmale an das Kind vererbt wird.
(define (get-flügelfarben liste)
  (second liste))

;Eine Funktion um die Fühlerformen eines Schmetterlings als Liste zu bekommen.
;Wird benötigt um zu besitmmen welches der beiden Merkmale an das Kind vererbt wird.
(define (get-fühlerformen liste)
  (third liste))

;Eine Funktion um von den 2 Musterungen, Flügelfarben oder Fühlerformen eines zufällig zu bestimmen welches an das Kind vererbt wird.
(define (zufälliges-merkmal liste)
  (car (shuffle liste)))

;Eine Funktion, die ein Kind zu einer Mutter und einem Vater erzeugt. Mutter und Vater werden wie oben schon beschrieben als
;Liste von 3 Unterlisten übergeben.
(define (erzeuge-kind mutter vater)
      (list (list (zufälliges-merkmal (get-musterungen mutter)) (zufälliges-merkmal (get-musterungen vater)))
            (list (zufälliges-merkmal (get-flügelfarben mutter)) (zufälliges-merkmal (get-flügelfarben vater)))
            (list (zufälliges-merkmal (get-fühlerformen mutter)) (zufälliges-merkmal (get-fühlerformen vater))))) 

;Eine Funktion die einen Schmetterling anhand seiner dominanten Merkmale erzeugt.
(define (print-schmetterling schmetterling)
  (print (show-butterfly (get-dominante-flügelfarbe (first (get-flügelfarben schmetterling)) (second (get-flügelfarben schmetterling)))
                         (get-dominante-musterung (first (get-musterungen schmetterling)) (second (get-musterungen schmetterling)))
                         (get-dominante-fühlerform (first (get-fühlerformen schmetterling)) (second (get-fühlerformen schmetterling))))))

;Hilfsfunktion, die so viele Kinder wie gefordert malt.
(define (print-kinder musterung-mutter flügelfarbe-mutter fühlerform-mutter musterung-vater flügelfarbe-vater fühlerform-vater anzahl-kinder)
  (print-schmetterling (erzeuge-kind (erzeuge-schmetterling musterung-mutter flügelfarbe-mutter fühlerform-mutter) (erzeuge-schmetterling musterung-vater flügelfarbe-vater fühlerform-vater)))
  (if (= 1 anzahl-kinder)
      (printf "\n")
      (print-kinder musterung-mutter flügelfarbe-mutter fühlerform-mutter musterung-vater flügelfarbe-vater fühlerform-vater (- anzahl-kinder 1))))

;Die endgültige Funktion, die abschließend anhand von 3 dominanten Merkmalen der Mutter und 3 dominanten Merkmalen des Vaters die Eltern mit beliebigen möglichen rezesiven
;Merkmalen erzeugt, diese malt und im Anschluss so viele Kinder wie gefordert erzeugt und diese Ebenfalls malt.
(define (print-schmetterlingfamilie musterung-mutter flügelfarbe-mutter fühlerform-mutter musterung-vater flügelfarbe-vater fühlerform-vater anzahl-kinder)
  (print "Eltern")
  (printf "\n")
  (print-schmetterling (erzeuge-schmetterling musterung-mutter flügelfarbe-mutter fühlerform-mutter))
  (print-schmetterling (erzeuge-schmetterling musterung-vater flügelfarbe-vater fühlerform-vater))
  (printf "\n")
  (print "Kinder")
  (printf "\n")
  (print-kinder musterung-mutter flügelfarbe-mutter fühlerform-mutter musterung-vater flügelfarbe-vater fühlerform-vater anzahl-kinder))
      
  
;Test-Aufrufe
;spezieller Aufruf, da alle Kinder ebenfalls "stripes" "yellow" und "curved" als Merkmale haben müssen.
(print-schmetterlingfamilie "stripes" "yellow" "curved" "stripes" "yellow" "curved" 20)
;Aufrufe beliebig. Ein Wirklicher Test ist nicht möglich, da die rezesiven Merkmale zufällig erzeugt werden.
;Ein exakter Test ist also nicht möglich. 
(print-schmetterlingfamilie "plain" "blue" "curved" "dots" "red" "straight" 10)
(print-schmetterlingfamilie "dots" "yellow" "straight" "dots" "green" "straight" 4)
(print-schmetterlingfamilie "plain" "red" "straight" "plain" "red" "straight" 30)
(print-schmetterlingfamilie "stripes" "blue" "straight" "plain" "green" "curved" 8)
;Aufruf mit nur einem Kind um den Grenzwert bezüglich der Kinderzahl zu testen.
(print-schmetterlingfamilie "plain" "red" "straight" "plain" "red" "straight" 1)




;Aufgabe 2

;Idee: Ein Kind kann maximal das jeweils dominanteste Merkmal das entweder bei Mutter oder Vater vorkommt aufweisen.
;Im Beispiel ist es also nicht möglich, dass das Kind von den Eltern stammt. Z.B. kann es da beide das Merkmal "dots" haben
;das Merkmal "plain" aufweisen.

(define (prüfe-musterung-kind musterung-mutter musterung-vater musterung-kind)
  (if (> (max (get-listenposition Musterungen musterung-mutter) (get-listenposition Musterungen musterung-vater)) (get-listenposition Musterungen musterung-kind))
      "True"
      "False"))

(define (prüfe-flügelfarbe-kind flügelfarbe-mutter flügelfarbe-vater flügelfarbe-kind)
  (if (> (max (get-listenposition Flügelfarben flügelfarbe-mutter) (get-listenposition Flügelfarben flügelfarbe-vater)) (get-listenposition Flügelfarben flügelfarbe-kind))
      "True"
      "False"))

(define (prüfe-fühlerform-kind fühlerform-mutter fühlerform-vater fühlerform-kind)
  (if (> (max (get-listenposition Fühlerformen fühlerform-mutter) (get-listenposition Fühlerformen fühlerform-vater)) (get-listenposition Fühlerformen fühlerform-kind))
      "True"
      "False"))

(define (prüfe-ob-kind musterung-mutter flügelfarbe-mutter fühlerform-mutter musterung-vater flügelfarbe-vater fühlerform-vater musterung-kind flügelfarbe-kind fühlerform-kind)
  (if (equal? "True" (prüfe-musterung-kind musterung-mutter musterung-vater musterung-kind) (prüfe-flügelfarbe-kind flügelfarbe-mutter flügelfarbe-vater flügelfarbe-kind)
              (prüfe-fühlerform-kind fühlerform-mutter fühlerform-vater fühlerform-kind))
      "Es kann ein Kind sein"
      "Es kann kein Kind sein"))
  


