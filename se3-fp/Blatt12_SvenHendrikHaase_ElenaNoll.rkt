#lang racket

(require swindle/extra)

;Aufgabe 1

;1.1
(define (rek-zahl xs zaehler)
  (if (empty? xs)
      (+ 0)
      (+ (* (expt 10 zaehler) (car xs)) (rek-zahl (cdr xs) (+ zaehler 1)))))

;1.2
(define (hoehere-zahl xs)
  (apply + (map (lambda (n1 n2)
                  (* n1 (expt 10 n2)))
                xs (build-list (length xs) values))))
;Aufgabe 2

;2.1

;Als fixe Eingabe dienen drei Listen "summand1", "summand2" und "summe".
;Diese Listen beeinhalten schlicht die Zahlen als Buchstaben repräsentiert.
;Wir lösen dieses Problem mittels amb. Es wird dadurch durch alle Möglichkeiten hindurch getestet,
;ob die Bedingungen erfüllt werden.
;Die Liste der Eingabebuchstaben hat folgendes Format: '(Buchstabe . (amb 0 1 2 3 4 5 6 7 8 9)
;Also z.B.: '((A . 0) (B . 4))

;2.2

(define (distinct? list)
  (equal? (length list) (length (remove-duplicates list))))

(define (mach-amb-list summand1 summand2 summe)
  (map
    (lambda (xs) (cons xs (amb 0 1 2 3 4 5 6 7 8 9)))
    (remove-duplicates (append summand1 summand2 summe))))

(define (prepare-number-list compare-list1 compare-list2)
  (reverse (map
             (lambda (x) (cdr x))
             (filter (lambda (xs) (not (false? (member (car xs) compare-list1)))) compare-list2))))

(define (krypto summand1 summand2 summe)
  (let ((buchstaben (mach-amb-list summand1 summand2 summe)))
    (amb-assert (and (distinct? (map (lambda (xs) (cdr xs)) buchstaben))
                     (= (+ (hoehere-zahl (prepare-number-list summand1 buchstaben))
                           (hoehere-zahl (prepare-number-list summand2 buchstaben)))
                        (hoehere-zahl (prepare-number-list summe buchstaben)))))
    buchstaben))