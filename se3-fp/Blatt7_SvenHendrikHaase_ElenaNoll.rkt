#lang racket

(require 2htdp/image)
(require 2htdp/universe)

;Aufgabe 1

;Allgemein rekursive Funktion
(define (produkt1 liste faktor)
         (if (empty? liste)
             '()
             (cons (* (car liste) faktor)
             (produkt1 (cdr liste) faktor))))

;Mittels Funktion höherer Ordnung
(define (produkt3 liste faktor)
  (map (lambda (faktor2)
         (* faktor faktor2))
       liste))

;Aufgabe2

;Aufgabe 2.1
;Kodierung der Ampel: Ampel besteht aus 3 Werten, die jeweils 1 oder 0 sein können. Die 3 Werte repräsentieren 
;die 3 Farben rot, gelb und grün. Der 1. Wert steht für die Farbe rot, der 2. Wert für die Farbe gelb und der
;3. Wert für die Farbe grün. Der Zustand 1 bedeutet, dass die entsprechende Farbe aktuell aufleuchtet und 0 bedeutet,
;dass die Farbe nicht aufleuchtet.
;Eine Ampel kann also z.B. aus einer Liste mit 3 Werten gespeichert werden.

;Hier werden die 4 möglichen Zustände einer Ampel definiert.
(define rote-Ampel '(1 0 0))
(define rot-gelbe-Ampel '(1 1 0))
(define grüne-Ampel '(0 0 1))
(define gelbe-Ampel '(0 1 0))

;Die Liste der Ampelzustände in sequenzieller Abfolge.
(define Ampelzustände (list rote-Ampel rot-gelbe-Ampel grüne-Ampel gelbe-Ampel))

;Aufgabe 2.2
;Eine Liste, die 4 Werte speichert. Der erste Wert repräsenteirt wie lange sich die Ampel im Zustand rot, der 2. wie lange im Zustand rot-gelb,
;der 3. wie lange im Zustand grün und der 4. wie lange im Zustand gelb befindet. (Wir haben die Länge der einzelnen Phasen erhöht, damit die
;Animation besser sichtbar und nicht zu schnell ist.
(define Zustandslängen '(50 10 50 20))

;Die Funktion expandiere.
(define (expandiere liste1 liste2)
  (map (lambda (wert1 wert2)
         (make-list wert1 wert2))
         liste2 liste1))

;Definiert die expandierte Zustandsliste.
(define expandierte-Zustandsliste (expandiere Ampelzustände Zustandslängen))

;Hilfsfunktion für die verbesserte expandierte Zustandsliste.
(define (helper-bessere-expandierte-Zustandsliste liste)
  (if (empty? liste)
      '()
      (cons (list (first liste) (second liste) (third liste))
      (helper-bessere-expandierte-Zustandsliste (cdddr liste)))))
;Verbesserte expandierte Zustandsliste.
;Erklärung: Für die weitere verarbeitung in Bezug auf Aufgabe 2.3 ist es besser, wenn die expandierte Zustandsliste alle Zustände der Reihe
;nach als Werte enthält. Momentan war dies nicht der Fall, da die Werte noch einmal in Unterlisten geteilt waren.
(define bessere-expandierte-Zustandsliste 
  (helper-bessere-expandierte-Zustandsliste(flatten expandierte-Zustandsliste)))

;Länge der verbesserten expandierten Zustandsliste, wird in Aufgabe 2.3 benötigt.
(define length-bessere-expandierte-Zustandsliste (length bessere-expandierte-Zustandsliste))

;Aufgabe 2.3
;Funktion erstellt eine grafische Ampel anhand eines Zustandes, der als Parameter übergeben wird.
;Der Zustand wird wie oben definiert von einer Liste mit 3 Werten für rot, gelb und grün repräsentiert.
(define (Ampel zustand)
  (underlay/xy
   (underlay/xy
    (underlay/xy
     (rectangle 30 70 "solid" "black")
     5 2.5
     (if (= 0 (first zustand))
         (ellipse 20 20 "solid" "gray")
         (ellipse 20 20 "solid" "red")))
    5 25
    (if (= 0 (second zustand))
        (ellipse 20 20 "solid" "gray")
        (ellipse 20 20 "solid" "yellow")))
   5 47.5
   (if (= 0 (third zustand))
       (ellipse 20 20 "solid" "gray")
       (ellipse 20 20 "solid" "green"))))

;Die Funktion zeigt eine Ampel zum Zeitpunkt t an (Wir gehen davon aus, dass t bei Zustand 0 beginnt und 
;0 den 1. Zustand repräsentiert. Welcher Zustand zum Zeitpunkt t vorliegt kann man anhand der verbesserten 
;expandierten Zustandsliste ermitteln.
(define (zeige-Ampel t)
  (if (>= t length-bessere-expandierte-Zustandsliste)
      (zeige-Ampel (- t length-bessere-expandierte-Zustandsliste))
      (Ampel (list-ref bessere-expandierte-Zustandsliste t))))

;Aufgabe 2.4
;Idee: Die Rotphase muss sich verlängern, da eine Phase hinzukommt in der beide Richtungen "rot haben". Dies ist notwendig, damit 
;keine Unfälle passieren wenn es auf der Kreuzung zu einem kurzen Stau oder der gleichen kommt. 

             