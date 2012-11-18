#lang racket
;Aufgabe 1.1
;Begründung: Wir haben eine assoziative Liste verwendet, weil sie für unseren Zweck optimal ist.
;            Wir stecken einen Char rein und bekommen den jeweiligen String heraus.
(define Internationale-Buchstabiertafel
   '((#\A "Alfa")
     (#\B "Bravo")
     (#\C "Charlie") 
     (#\D "Delta")
     (#\E "Echo")
     (#\F "Foxtrott")
     (#\G "Golf")
     (#\H "Hotel")
     (#\I "India")
     (#\J "Juliett")
     (#\K "Kilo")
     (#\L "Lima")
     (#\M "Mike")
     (#\N "November")
     (#\O "Oscar")
     (#\P "Papa")
     (#\Q "Quebec")
     (#\R "Romeo")
     (#\S "Sierra")
     (#\T "Tango")
     (#\U "Uniform")
     (#\V "Viktor")
     (#\W "Whiskey")
     (#\X "X-ray")
     (#\Y "Yankee")
     (#\Z "Zulu")
     (#\0 "Nadazero")
     (#\1 "Unaone")
     (#\2 "Bissotwo")
     (#\3 "Terrathree")
     (#\4 "Kartefour")
     (#\5 "Pantafive")
     (#\6 "Soxisix")
     (#\7 "Setteseven")
     (#\8 "Oktoeight")
     (#\9 "Novenine")
     (#\, "Decimal")
     (#\., "Stop")))

;Aufgabe 1.2

(define (Buchstabe->Schlüssel char)
  (car(reverse(assoc char Internationale-Buchstabiertafel))))

;Aufgabe 1.3

(define (Buchstabe->Schlüssel2 char)
  (car(reverse(assoc (char-upcase char) Internationale-Buchstabiertafel))))

;Aufgabe 1.4
(define (Übersetze-Text-Helper2 text-liste)
  (string-append (Buchstabe->Schlüssel2 (car text-liste)) " " (Übersetze-Text-Helper (cdr text-liste))))

(define (Übersetze-Text-Helper text-liste)
  (if (empty? text-liste) "" (Übersetze-Text-Helper2 text-liste)))

(define (Übersetze-Text text)
  (Übersetze-Text-Helper (string->list text)))

; Aufgabe 2
(require "flaggen-module.rkt")

(define Internationale-Flaggentafel
   '((#\A A)
     (#\B B)
     (#\C C) 
     (#\D D)
     (#\E E)
     (#\F F)
     (#\G G)
     (#\H H)
     (#\I I)
     (#\J J)
     (#\K K)
     (#\L L)
     (#\M M)
     (#\N N)
     (#\O O)
     (#\P P)
     (#\Q Q)
     (#\R R)
     (#\S S)
     (#\T T)
     (#\U U)
     (#\V V)
     (#\W W)
     (#\X X)
     (#\Y Y)
     (#\Z Z)
     (#\0 Z0)
     (#\1 Z1)
     (#\2 Z2)
     (#\3 Z3)
     (#\4 Z4)
     (#\5 Z5)
     (#\6 Z6)
     (#\7 Z7)
     (#\8 Z8)
     (#\9 Z9)))

;Aufgabe 2.1

(define (Buchstabe->Schlüssel-Flagge char)
  (eval (car(reverse(assoc char Internationale-Flaggentafel)))))

;Aufgabe 2.2

(define (Buchstabe->Schlüssel2-Flagge char)
  (eval (car(reverse(assoc (char-upcase char) Internationale-Flaggentafel)))))

;Aufgabe 2.3
(define (Übersetze-Text-Helper2-Flagge text-liste)
  (list* (Buchstabe->Schlüssel2-Flagge (car text-liste)) (Übersetze-Text-Helper-Flagge (cdr text-liste))))

(define (Übersetze-Text-Helper-Flagge text-liste)
  (if (empty? text-liste) '() (Übersetze-Text-Helper2-Flagge text-liste)))

(define (Übersetze-Text-Flagge text)
  (Übersetze-Text-Helper-Flagge (string->list text)))