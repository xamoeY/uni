#lang racket

(require 2htdp/image)

;Aufgabe 1

;Aufgabe 2

;Erzeugt einen Bilderrahmen der als Grundlage für unser Bild dienen soll.
(define bilderrahmen (empty-scene 500 300))

;Erzeugt einen Stern.
(define stern (underlay
               (radial-star 8 8 50 "solid" "orange")
               (star 50 "solid" "yellow")))

;Erzeugt einen Schneemann.
(define schneemann (underlay/xy
                    ;Hut
                    (above/align "center"
                                 (rectangle 15 20 "solid" "black")
                                 (ellipse 40 3 "solid" "black")
                                 ;Kopf
                                 (underlay/xy
                                  (underlay/xy (ellipse 40 40 "solid" "gray")
                                               7 12
                                               (ellipse 10 10 "solid" "black"))
                                  23 12
                                  (ellipse 10 10 "solid" "black"))
                                 ;Körper
                                 (ellipse 80 70 "solid" "gray")
                                 (ellipse 110 100 "solid" "gray"))
                                 47 50
                                 (triangle/ssa 32 52 7  "solid" "orange")))

;Erzeugt ein Geschenk
(define geschenk (above/align "center"
                               (beside
                                (rotate 135 (ellipse 15 5 "outline" "gold"))
                                (flip-horizontal
                                 (rotate 135 (ellipse 15 5 "outline" "gold"))))
                               (underlay
                                (underlay (rectangle 40 35 "solid" "blue")
                                          (rectangle 3 35 "solid" "gold"))
                                (rectangle 40 3 "solid" "gold"))))

;Erzeugt einen Tannenbaum
(define tannenbaum (above/align "center"
                                (overlay/xy
                                 (overlay/xy
                                  (overlay/xy
                                   (overlay/xy
                                    (overlay/xy
                                     (rectangle 1 1 "solid" "white")
                                     40 2
                                     (radial-star 6 6 30 "solid" "orange"))
                                    30 30
                                    (isosceles-triangle 60 70 "solid" "darkgreen"))
                                   20 50
                                   (isosceles-triangle 80 70 "solid" "darkgreen"))
                                  10 70
                                  (isosceles-triangle 100 70 "solid" "darkgreen"))
                                 0 90
                                 (isosceles-triangle 120 70 "solid" "darkgreen"))
                                (rectangle 30 40 "solid" "brown")))

;Erzeugt eine Kerze
(define kerze (above/align "center"
                           (underlay/xy
                            (underlay/xy
                             (ellipse 10 17 "solid" "yellow")
                             2 1
                             (ellipse 7 14 "solid" "orange"))
                            4 4
                            (ellipse 3 8 "solid" "red")) 
                           (rectangle 2 7 "solid" "black")
                           (rectangle 20 30 "solid" "red")))

(define (geschenk-stapel ebenen)
  (above/align "center"
               geschenk
               (if (= ebenen 0)
                   kerze
                   (beside/align "center"
                                 (geschenk-stapel (- ebenen 1))
                                 (geschenk-stapel (- ebenen 1))))))
  

;Setzt das Gesamtbild zusammen.
(define erzeuge-bild (underlay/xy
                      (underlay/xy
                       (underlay/xy
                        (underlay/xy
                         bilderrahmen
                         0 30
                         schneemann)
                        200 10
                        stern)
                       350 240
                       geschenk)
                      360 50
                      tannenbaum))