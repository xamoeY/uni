#lang racket

(require "setkarten-module.rkt")

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
;Der Aufruf (pepper + 1) gibt eine Funktion zurück, nämlich das lambda, welches im Körper defniert
;ist. Das lambda ist allerdings noch nicht "fertig", es fehlt nämlich noch der Wert für den
;Parameter arg2, der zwar deklariert, jedoch nicht definiert wurde. Dieser tatsächliche Wert wird
;dann an pepper übergeben auf genau die selbe Weise, wie wir es auch mit einem normalen lambda
;ohne Wrapper gemacht hätten. Das Interessante hierbei ist, dass die 3 eigentlich außerhalb des
;eigentlichen Funktions-Scopes steht, aber dennoch zugegriffen werden darf. Die 3 wird dann erst
;nach definition an arg2 gebunden. Das Binden findet also quasi sogar "von außen" statt.

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
(define liste '(-1 2 3 4 -5 6 -7 8 -9 10 42 49 1 55 700))

;Aufgabe 2.1
(define (abs-sum xs)
  (apply + (map abs xs)))

;Aufgabe 2.2
(define (div-7 xs)
  (filter (lambda (x) (not (equal? 0 x))) (map (lambda (nummer)
               (if (= 0 (modulo nummer 7))
                   nummer
                   0)) xs)))

;Aufgabe 2.3
(define (count-odd xs)
  (length (filter odd? xs)))
;oder
(define (count-odd2 xs)
  (count odd? xs))

;Aufgabe 3

;Aufgabe 3.1
;Eine Karte wird einfach eine Liste ihrer Eigenschaften in der Reihenfolge:
; Form Farbe Anzahl Füllung
;Hierbei sind die jeweiligen Attribute wiederum erneut in Listen definiert, damit
;wir automatisch über diese iterieren können.

(define pattern '(waves oval rectangle))
(define color '(red green blue))
(define count '(1 2 3))
(define mode '(outline solid hatched))
(define attributes '(count pattern mode color))

(define (card count pattern mode color)
  (list count pattern mode color))

(card 2 'waves 'outline 'red)

;Aufgabe 3.2
(define (card-deck)
  (for*/list ([i count]
         [j pattern]
         [k mode]
         [l color])
    (append (list i j k l))))

(define (visualize-deck)
  (for*/list ([i count]
         [j pattern]
         [k mode]
         [l color])
    (show-set-card i j k l)))

;Aufgab 3.3
(define (pos-in-list x xs)
  (- (length xs) (length (member x xs))))

(define (is-a-set? set)
  (map (lambda (attr) (or
                       (and
                         (equal?
                           (list-ref (first set) (pos-in-list attr attributes))
                           (list-ref (second set) (pos-in-list attr attributes)))
                         (equal?
                           (list-ref (second set) (pos-in-list attr attributes))
                           (list-ref (third set) (pos-in-list attr attributes))))
                       (and
                         (not (equal?
                           (list-ref (first set) (pos-in-list attr attributes))
                           (list-ref (second set) (pos-in-list attr attributes))))
                         (not (equal?
                           (list-ref (second set) (pos-in-list attr attributes))
                           (list-ref (third set) (pos-in-list attr attributes))))))) attributes))
  
(is-a-set? '((2 red oval hatched)
             (2 red rectangle hatched)
             (2 red wave hatched)))
  
(is-a-set? '((2 red rectangle outline)
             (2 green rectangle outline)
             (1 green rectangle solid)))