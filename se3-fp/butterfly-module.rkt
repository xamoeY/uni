#lang racket
(require 2htdp/image)
(provide 
 some-butterflies
 show-butterfly
 set-size!)

(define size 100)
(define kopfbreite (/ size 7))
(define bodycolor 'black)

(define (set-size! s)
  ;setze die Laenge der Schmetterlinge
  (set! size s))

(define (streifen)
  (above 
   (rhombus (/ size 4.8) 170 'solid 'black)
   (rhombus (/ size 2.8) 170 'solid 'black)
   (rhombus (/ size 1.8) 170 'solid 'black)
   (rhombus (/ size 2.8) 170 'solid 'black)
   (rhombus (/ size 4.8) 170 'solid 'black)
   ))

(define (punkte)
  (beside
   (overlay 
    (circle (/ size 12.8)  'solid 'black)
    (circle (/ size 9.8)  'solid 'gray)
    )
   (overlay 
    (circle (/ size 7.8)  'solid 'black)
    (circle (/ size 5.8)  'solid 'gray)
    )
   (overlay 
    (circle (/ size 12.8) 'solid 'black)
    (circle (/ size 9.8) 'solid 'gray)
    )))

(define (einfarbig)
  (overlay
   (scale 0.9 
          (rhombus (/ size 1.5) 120 'outline 'black))
   (rhombus (/ size 1.5) 120 'outline 'black)))

(define (fluegel-segm farbe muster)
  ;zeichne ein Segment des Fluegels als Rhombus
  (let ([wing (rhombus (/ size 1.5) 120 'solid farbe)])
    (if muster (overlay muster wing) wing )))

(define (linker-fluegel farbe muster)
  ; setze zwei Rhomben zum linken Fluegel zusammen
  (let ([l_oben 
         (rotate -40 (fluegel-segm farbe muster))])
    (above l_oben (flip-vertical l_oben))))


(define (fluegel farbe muster)
  ; das Fluegelpaar: spiegele den linken Fluegel als rechten Fluegel
  (let ([links (linker-fluegel farbe muster)])
    (beside links  (flip-horizontal links))))

(define (fuehler-krumm)
  ; zeichne gekruemmte Fuehler
  (crop 0 (/ kopfbreite 2) 
        (* 2 kopfbreite) (/ kopfbreite 0.7)
        (circle kopfbreite 'outline bodycolor)))

(define (fuehler-gerade)
  ; zeichne gerade Fuehler
  (crop 0 (* 2 kopfbreite) 
        (* 2 kopfbreite) (* kopfbreite 1.5)
        (rhombus (* kopfbreite 2) 40 'outline bodycolor)))

(define (body fuehler)
  ; zeichne Rumpf, Kopf und Fuehler
  (above 
   fuehler
   (circle (/ kopfbreite 2)'solid bodycolor)
   (ellipse kopfbreite ( * size 0.8) 'solid bodycolor)))

(define (butterfly farbe muster fuehler)
  (overlay (body fuehler) (fluegel farbe muster)))

(define (show-butterfly 
         the_color the_pattern the_shape)
  ; the_color: 'red, 'green, 'blue, 'yellow
  ; the_pattern: 'plain, 'stripes, 'dots
  ; the_shape: 'straight, 'curved
  (butterfly 
   the_color
   (case the_pattern
     [(plain) (einfarbig)]
     [(stripes) (streifen)]
     [(dots) (punkte)]
     [else #f]); default: uni
   (if (eq? the_shape 'straight)
       (fuehler-gerade)(fuehler-krumm)))
  )


;testing
(define some-butterflies
  ; ein Bild mir drei Schmetterlingen Seite an Seite
  (beside 
   (show-butterfly 'red 'stripes 'curved)
   (rhombus (/ size 10) 90 'outline 'orange); abstand
   (show-butterfly 'green 'plain 'straight)
   (rhombus (/ size 10) 90 'outline 'orange); abstand
   (show-butterfly 'blue 'dots 'curved)
   ))

(define Antonia-Anton-Toni
  ; ein Bild mir drei Schmetterlingen Seite an Seite
  (beside 
   (above (show-butterfly 'blue 'dots 'curved)
          (text "Antonia" 24 'black))
   (rhombus (/ size 10) 90 'outline 'orange); abstand
   (above (show-butterfly 'yellow 'dots 'curved)
          (text "Anton" 24 'black))
   (rhombus (/ size 10) 90 'outline 'orange); abstand
    (above (scale 0.5 (show-butterfly 'red 'straight 'curved))
           (text "Toni" 24 'black))
   ))
;(save-image some-butterflies "butterfly-pic.png")
; some-butterflies
