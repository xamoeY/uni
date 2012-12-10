#lang racket

(require 2htdp/image)

;Aufgabe 1

;            direkte Rekursion  indirekte Rekusion  geschachtelte Rekursion  lineare Rekursion  Baumrekurison
; take               ja               nein                     nein                 ja                nein
; drop               ja               nein                     nein                 ja                nein
; merge              ja               nein                     nein                 nein              ja
; merge-sort         ja               ja                       nein                 ja                ja

; Erklaerung 
; take: Direkt und nicht indirekt, da es sich direkt wieder selber aufruft. Nur linear, da in dem
;       Argument fuer sich selbst kein weiterer Aufruf von sich selbst stattfindet (nicht (take (take ...))).
;       Keine Baumrekursion, da es sich nur einmal selber aufruft.

; drop: Selbe Erklaerung wie bei take.

; merge: Direkt und nicht indirekt, da es sich direkt wieder selber aufruft. Hier liegt Baumrekursion vor,
;        da hier zwei Aufrufe von sich selbst abgehen.

; merge-sort: Diese Funktion ruft sowohl sich selbst direkt mittels Baumrekursion auf als auch zwei andere
;             rekursive Funktionen (indirekt) jeweils ein Mal (linear).

;Aufgabe 2

;Erzeugt einen Bilderrahmen mit schwarzem Hintergrund, der als Grundlage für unser Bild dienen soll.
(define bilderrahmen (empty-scene 500 300 "black"))

;Erzeugt ein transparentes Viereck mit der selben Größe wie unser Bilderrahmen. Wir benötigen dies bei der Positionierung über place-image.
(define transparente-scene (rectangle 500 300 "solid" (color 0 0 0 0)))

;Erzeugt unsere Schneelandschaft, die als Hintergrund dient. Realisiert haben wir dies mit untereinander liegenden Ellipsen.
(define schneelandschaft (underlay
                          (place-image (ellipse 1200 200 "solid" (color 180 180 180)) 300 270 transparente-scene)
                          (place-image (ellipse 500 200 "solid" (color 200 200 200)) 120 310 transparente-scene)
                          (place-image (ellipse 400 200 "solid" (color 230 230 230)) 130 350 transparente-scene)
                          (place-image (ellipse 300 150 "solid" (color 240 240 240)) 400 300 transparente-scene)))

;Erzeugt einen Stern mit super schönem Leuchteffekt, bestehend aus 3 verschiedenen Sternen, die so angeordnet sind, dass es besonders schön aussieht.
(define stern (underlay
               (star 17 "solid" (color 255 250 0 70))
               (radial-star 8 5 10 "solid" "orange")
               (star 10 "solid" "yellow")))

;Erzeugt einen Schneemann. Der Körper besteht aus übereinanderliegenden Ellipsen. Auf dem oberen Teil des Körpers 
;befinden sich mit Hilfe von underlay/xy 2 Knöpfe. Ähnlich beim Kopf. Dieser stizt ebenfalls über above auf dem Körper und hat 2 Augen per underlay/xy bekommen.
;Der Hut besteht aus einem Viereck und einer Ellipse und sitzt ebenfalls per above auf dem Kopf. Die Nase wurde nachträglich per underlay zum gesamten Schneemann 
;hinzugefügt, da wenn man sie nur an den Kopf angefügt hat das above/align "center" kaputt gegangen ist.
(define schneemann (underlay/xy
                    ;Hut
                    (above/align "center"
                                 (rectangle 20 20 "solid" (color 70 50 50))
                                 (ellipse 50 3 "solid" (color 70 50 50))
                                 ;Kopf
                                 (underlay/xy
                                  (underlay/xy (ellipse 40 40 "solid" "white")
                                               7 12
                                               (ellipse 10 10 "solid" "black"))
                                  23 12
                                  (ellipse 10 10 "solid" "black"))
                                 ;Körper
                                 (underlay/xy
                                  (underlay/xy
                                   (ellipse 80 70 "solid" "white")
                                   37 17
                                   (ellipse 6 6 "solid" "black"))
                                  37 42
                                  (ellipse 6 6 "solid" "black"))
                                 (ellipse 110 100 "solid" "white"))
                                 47 50
                                 (triangle/ssa 32 52 7  "solid" "orange")))

;Erzeugt ein Geschenk, der Hauptteil besteht aus einem Rechteck, die Bänder aus 2 sehr schmalen Rechtecken und die Schleifen aus 2 Ellipsen, 
;die outlined sind und gegenseitig horizontal gespiegelt sind. Geschenk ist keine Variable, sondern eine Funktion, die ein Geschenk mit beliebiger Farbe erzeugt.
(define (geschenk color1 color2 color3) 
                  (above/align "center"
                               (beside
                                (rotate 135 (ellipse 15 5 "outline" "gold"))
                                (flip-horizontal
                                 (rotate 135 (ellipse 15 5 "outline" "gold"))))
                               (underlay
                                (underlay (rectangle 40 35 "solid" (color color1 color2 color3))
                                          (rectangle 3 35 "solid" "gold"))
                                (rectangle 40 3 "solid" "gold"))))

;Erzeugt Weihnachtskugeln in verschiedenen Farben. Eine Kugel besteht aus einer Ellipse und per underlay/xy haben wir eine kleine Ellipse
;hinzugefügt, die einen wunderschönen Lichtreflex erzeugt.
(define (weihnachtskugel color1 color2 color3)
  (above/align "center" 
               (ellipse 5 2 "solid" "gold")
               (underlay/xy
                (ellipse 20 20 "solid" (color color1 color2 color3))
                5 5
                (ellipse 5 5 "solid" "white"))))

;Erzeugt einen Tannenbaum, der aus mehreren Dreiecken besteht, die sich gegenseitig überlagern. Am oberen Ende ist ein Stern als Spitze und am underen Ende 
;der Stamm. Alles wurde per overlay/xy zusammengesetzt. Das transparente Viereck benötigen wir, da das erste Element in der overlay-Schachtelung immer oben rechts sitzt,
;der Stern aber auch zentriert auf dem Baum sitzen soll. Per underlay/xy haben wir Weihnachtskugeln auf dem Baucm als Deko platziert.
(define tannenbaum (underlay/xy
                    (underlay/xy
                     (underlay/xy
                      (underlay/xy
                       (underlay/xy
                        (underlay/xy
                         (above/align "center"
                                      (overlay/xy
                                       (overlay/xy
                                        (overlay/xy
                                         (overlay/xy
                                          (overlay/xy
                                           (rectangle 1 1 "solid" (color 0 0 0 0))
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
                                      (rectangle 30 40 "solid" "brown"))
                         40 100
                         (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155))))
                        60 70
                        (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155))))
                       70 120
                       (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155))))
                      90 150
                      (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155))))
                     20 160
                     (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155))))
                    45 135
                    (weihnachtskugel (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155)))))
                                               
;Erzeugt eine Kerze mit schönem Lichteffekt. Die Kerze besteht aus einem Viereck darauf sitzt per above ein Docht und daruf sitzt die über underlay/xy erzeugte
;Flamme, die aus 3 Ellipsen besteht.
(define kerze (above/align "center"
                           (underlay/xy
                            (underlay/xy
                             (ellipse 10 17 "solid" "yellow")
                             2 1
                             (ellipse 7 14 "solid" "orange"))
                            4 4
                            (ellipse 3 8 "solid" "red")) 
                           (rectangle 2 7 "solid" "black")
                           (underlay/xy
                            (rectangle 20 30 "solid" "red")
                            5 0
                            (rectangle 4 30 "solid" (color 250 250 250 100)))))

;Erzeugt einen Stapel aus Geschenken mittels direkter Baumrekursion (wir wollen dafür unsere Zusatzpunkte :-)).
;Wir wissen auch, dass er bei mehr als 2 Ebenen nicht mehr schön aussieht aber Baumrekursion ist es trotzdem.
(define (geschenk-stapel ebenen)
  (above/align "center"
               (geschenk (+ 100 (random 155)) (+ 100 (random 155)) (+ 100 (random 155)))
               (if (= ebenen 1)
                   (rectangle 1 1 "solid" (color 0 0 0 0))
                   (beside/align "center"
                                 (geschenk-stapel (- ebenen 1))
                                 (geschenk-stapel (- ebenen 1))))))

;Erzeugt einen Sternenhimmel aus beliebig vielen Sternen mittels direkter, linearer Rekursion :-).
(define (sternenhimmel anzahl-sterne scene)
   (if (= anzahl-sterne 1)
       (place-image stern (+ (random 450) 25) (+ 30 (random 120)) scene)
       (underlay (place-image (rotate (+ 1 (random 359)) (scale (/ (+ (random 99) 1) 100) stern)) (+ (random 450) 25) (+ 30 (random 120)) scene) (sternenhimmel (- anzahl-sterne 1) scene))))
       
;setzt unser zuvor erzeugte Kerze auf einen Teller, man beachte den tollen Tiefeneffekt.
(define kerzen-teller (underlay/xy
                       (underlay/xy
                        (ellipse 60 40 "solid" "brown")
                        5 11
                        (ellipse 50 20 "solid" (color 80 50 50)))
                        20 -30
                        kerze))

;Setzt das Gesamtbild zusammen.
(define erzeuge-bild (underlay
                      bilderrahmen
                      schneelandschaft
                      (sternenhimmel 100 transparente-scene)
                      (place-image schneemann 80 180 transparente-scene)
                      (place-image tannenbaum 400 130 transparente-scene)
                      (place-image (geschenk-stapel 2) 350 240 transparente-scene)
                      (place-image kerzen-teller 450 250 transparente-scene)))

;ruft unser Weichnachtsbild auf.
(print erzeuge-bild)
