#lang racket

;Aufgabe 1

;Aufgabe 1.1
(define (every p? xs)
  (if (empty? xs)
      #t
      (if (equal? p? (car xs))
          (every p? (cdr xs))
          #f)))

(define (some p? xs)
  (if (empty? xs)
      #f
      (if (equal? p? (car xs))
          #t
          (some p? (cdr xs)))))

;Aufgabe 1.2

(define (symmetrisch? r)
  (if (empty? r)
      #t
      (if (some (reverse (car r)) r)
          ((remove (reverse (car r)) r)
           (symmetrisch? (cdr r)))
          #f)))