#lang racket

(require 2htdp/image)

;Aufgabe 1

;Aufgabe 2
(define bilderrahmen (empty-scene 500 300))

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

(define erzeuge-bild (underlay/xy
                      bilderrahmen
                      0 0
                      schneemann))