#lang racket

;Aufgabe 1

;1.1
(define (rek-zahl xs zaehler)
  (if (empty? xs)
      (+ 0)
      (+ (* (expt 10 zaehler) (car xs)) (rek-zahl (cdr xs) (+ zaehler 1)))))

;1.2

;Aufgabe 2

;2.1

