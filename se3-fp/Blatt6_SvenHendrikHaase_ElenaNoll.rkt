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
(define schneemann (above/align
                    "center"
                    ;Hut
                    (rectangle 15 20 "solid" "black")
                    (ellipse 40 3 "solid" "black")
                    ;Kopf
                    (underlay/xy
                     (underlay/xy
                      (underlay/xy (ellipse 40 40 "solid" "gray")
                                   7 12
                                   (ellipse 10 10 "solid" "black"))
                      23 12
                     (ellipse 10 10 "solid" "black"))
                     10 25
                     (triangle/ssa 32 52 7  "solid" "orange"))
                    ;Körper
                    (ellipse 80 70 "solid" "gray")
                    (ellipse 110 100 "solid" "gray")))

(define geschenk (above/align "center"
                               (beside
                                (rotate 135 (ellipse 15 5 "outline" "gold"))
                                (flip-horizontal
                                 (rotate 135 (ellipse 15 5 "outline" "gold"))))
                               (underlay
                                (underlay (rectangle 40 35 "solid" "blue")
                                          (rectangle 3 35 "solid" "gold"))
                                (rectangle 40 3 "solid" "gold"))))

;Setzt das Gesamtbild zusammen.
(define erzeuge-bild (underlay/xy
                       bilderrahmen
                       0 30
                       schneemann))