#lang racket

;Aufgabe 1

;Aufgabe 1.1
;Eine Funktion in Racket ist dann eine Funktion höherer Ordung, wenn Sie als Agrument eine
;Funktion erwartet oder eine Funktion zurückgibt oder beides.

;Aufgabe 1.2
;a) Ja, da map eine der bekanntesten Funktionen höherer Ordnung ist. 
;Das 1. Argument ist eine Funktion.
;b) Nein, da es eine ganz normale Funktion mit einem Argument welches keine Funktion ist und
;auch einen Rückgabewert liefert, der keine Funktion ist.
;c) Ja, da das 1. Argument eine Funktion ist.
;d) Nein, da weder als Arument noch als Rückgabewert eine Funktion vorliegt.

;Aufgabe 1.3

;Aufgabe 1.4
;1. Ausgabe: '(2 4 6)
;Erklärung: Durch map werden alle Elemente der Liste mit 2 multipliziert.
;2. Ausgabe: '((1 . 1) (2 . 2) (3 . 3))
;Erklärung: Es entsteht eine Liste aus 3 Paaren, cons wird durch map auf alle Elemnte der beiden
;Listen angewendet. Es werden also erst die beien 1en zu einem Paar zusammengefügt, danach die
;beiden 2en und danach die beiden 3en.
;3. Ausgabe: '((a b) (()))
;Erklärung: Es werden alle Paare aus einer Liste herausgefileter und als neue Liste zurückgegeben.
;In diesem Fall befinden sich in der Liste 2 Paare, (a b) und (()).  


;Aufgabe 2
(define liste '(1 2 3 4 5 6 7 8 9 10))

;Aufgabe 2.1

;Aufgabe 2.2

;Aufgabe 2.3


;Aufgabe 3

