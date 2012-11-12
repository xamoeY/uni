#lang racket

; 1. Aufgabe
; 1) Ausgabe: 'Katze
;    Begründung: Ist so definiert.
; 2) Ausgabe: 'Katze
;    Begründung: plueschi ist als miau definiert und das ist als 'Katze definiert.
; 3) Ausgabe: 'miau
;    Begründung: Ist so definiert.
; 4) Ausgabe: 'pluschi
;    Begründung: quote macht einen String aus dem Parameter.
; 5) Ausgabe: 'Katze
;    Begründung: eval ist die Umkehrfunktion von quote und miau ist definiert als 'Katze.
; 6) Ausgabe: <fehler>
;    Begründung: 'Katze ist am Ende der Definitionskette und Katze wird ausgeführt, aber ist nicht definiert.
; 7) Ausgabe: 'Katze
;    Begründung: 'plueschi wird zu plueschi umgewandelt und dann ausgeführt.
; 8) Ausgabe: 'Ich
;    Begründung: PersonC wird auf PersonA definiert und PersonA ist zu dem Zeitpunkt immer noch 'Ich, weil
;                die Zuweisung (PersonA 'Sam) im Kopf von let erfolgt und noch nicht im Kopf verfügbar ist.
; 9) Ausgabe: '(miau plueschi)
;    Begründung: Jedes d schneidet einen Eintrag von links heraus.
; 10) Ausgabe: 'Katze
;     Begründung: cons macht ein Paar und cdr gibt uns das 2. Element aus.
; 11) Ausgabe: '(Katze)
;     Begründung: list macht eine Liste und cdr gibt uns alle Elemente als Liste rechts von dem 1. Element aus
; 12) Ausgabe: 0.1411200080598672
;     Begründung: Zahlen sind immer definiert und können auch ohne vorhergegangene explizite Definition evaluiert werden.
; 13) Ausgabe: 'peter
;     Begründung: eval wandelt den äußersten Ausdruck mit ' um (hier eine Liste) und führt ihn aus.
; 14) Ausgabe 'miau
;     Begründung: eval wandelt 'peter zu peter um und peter ist als 'miau definiert.

; 2.1 Aufgabe
(define (factorial n)
  (cond
    [(= n 0) 1]
    [else (* n (factorial (- n 1)))]))

; 2.2 Aufgabe
(define (power r n)
  (cond
    [(= n 0) 1]
    [else (cond
            [(odd? n) (* (power r (- n 1)) r)]
            [(even? n) (sqr (power r (/ n 2)))])]))

; 2.3 Aufgabe
(define (euler-helper n max)
  (if
   (<= n max)
   (+ (/ 1 (factorial n)) (euler-helper (+ 1 n) max))
   1))

(define euler
  (* (expt 10 1001) (euler-helper 1 1000)))

; 2.4 Aufgabe
(define (pi-helper n max vorzeichen)
  (if
   (<= n max)
   (+ (* vorzeichen (/ 1 n)) (pi-helper (+ 2 n) max (* -1 vorzeichen)))
   0))

(define pi-quarter
  (* (expt 10 10001) (pi-helper 1 10000 1)))

; 3. Aufgabe
(define (type-of n)
  (cond
    [(boolean? n) 'Bolean]
    [(list? n) 'List]
    [(pair? n) 'Pair]
    [(symbol? n) 'Symbol]
    [(number? n) 'Number]
    [(char? n) 'Char]
    [(string? n) 'String]
    [(vector? n) 'Vector]
    [(procedure? n) 'Procedure]))
    
(type-of (+ 3 7)) ; Number, da 3+7=10 und 10 eine Zahl ist.
(type-of type-of) ; Procedure, da type-of eine Procedure ist.
(type-of (type-of type-of)) ; Symbol, da (type-of type-of) 'Procedure ergibt und dies wiederum ein Symbol ist.
(type-of (string-ref "Schneewitchen_und_die_7_Zwerge" 2)) ; Char, da (string-ref str k) gibt den Buchstaben des Strings
; str an der Position k zurück in unserem Fall h. H ist ein Char (Buchstabe).
(type-of (lambda (x) x)) ; Procedure, da lambda eine Prozedur ist.
(define (id z) z)
(type-of (id cos)) ; Procedure, da (id cos) cos zurückgibt und cos eine Procedure ist.
(type-of '(1 2 3)) ; List, da '(1 2 3) eine Liste definiert.
(type-of '()) ; List, da eine leere Liste nach Definition auch eine Liste ist.