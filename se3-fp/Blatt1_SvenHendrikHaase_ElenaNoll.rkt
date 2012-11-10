#lang racket

;;Aufgabe 1.1
(define (degrees->radiant x)
  (* x 0.017453292519943))

(define (radiant->degrees x)
  (* x 57.295779513082))

;;Aufgabe 1.2
(define (my-acos a)
  (radiant->degrees (atan (/ (sqrt (- 1 (* (cos (degrees->radiant a))
                                           (cos (degrees->radiant a)))))
                             (cos (degrees->radiant a))))))

;;Aufgabe 1.3
(define (nm->km x)
  (* x 1.852))

;;Aufgabe 2.1
(define (distanzAB breite_a laenge_a breite_b laenge_b)
  (nm->km (* 60 (radiant->degrees(my-acos (+ (* (sin (degrees->radiant breite_a))
                                             (sin (degrees->radiant breite_b)))
                                          (* (cos (degrees->radiant breite_a))
                                             (sin (degrees->radiant breite_b))
                                             (cos (degrees->radiant (- laenge_a laenge_b))))))))))

;;Aufgabe 2.2

;;Aufgabe 2.3
(define (grad->himmelsrichtung x)
  (cond [(= x 0) "N"]
        [(= x 22.5) "NNO"]
        [(= x 45) "NO"]
        [(= x 67.5) "ONO"]
        [(= x 90) "O"]
        [(= x 112.5) "OSO"]
        [(= x 135) "SO"]
        [(= x 157.5) "SSO"]
        [(= x 180) "S"]
        [(= x 202.5) "SSW"]
        [(= x 225) "SW"]
        [(= x 247.5) "WSW"]
        [(= x 270) "W"]
        [(= x 292.5) "WNW"]
        [(= x 315) "NW"]
        [(= x 337.5) "NNW"]
        [else "ND"])) ;;ND = Not Defined

(define (himmelsrichtung->grad x)
  (cond [(equal? x "N") 0]
        [(equal? x "NNO") 22.5]
        [(equal? x "NO") 45]
        [(equal? x "ONO") 67.5]
        [(equal? x "O") 90]
        [(equal? x "OSO") 112.5]
        [(equal? x "SO") 135]
        [(equal? x "SSO") 157.5]
        [(equal? x "S") 180]
        [(equal? x "SSW") 202.5]
        [(equal? x "SW") 225]
        [(equal? x "WSW") 247.5]
        [(equal? x "W") 270]
        [(equal? x "WNW") 292.5]
        [(equal? x "NW") 315]
        [(equal? x "NNW") 337.5]
        [else "ND"])) ;;ND = Not Defined