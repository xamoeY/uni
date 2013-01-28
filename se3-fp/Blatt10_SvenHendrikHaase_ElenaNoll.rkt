#lang swindle

;Aufgabe 1

;1.1
(define (erzeuge-key autor jahr titel)
  (string-append titel autor (number->string jahr)))

(defclass literaturbeitrag ()
   (key
   :reader read-key
   :initarg :init-key)
  (autor
   :reader read-autor
   :initarg :init-autor)
  (jahr
   :reader read-jahr
   :initarg :init-jahr)
  (titel
   :reader read-titel
   :initarg :init-titel))

(defclass buch (literaturbeitrag)
  (verlag
   :reader read-verlag
   :initarg :init-verlag)
  (verlagsort
   :reader read-verlagsort
   :initarg :init-verlagsort)
  (reihe
   :reader read-reihe
   :initarg :init-reihe)
  (seriennummer
   :reader read-seriennummer
   :initarg :init-seriennummer))

(defclass sammelband (buch)
  (herausgeber
   :reader read-herausgeber
   :initarg :init-herausgeber)
  (seitenangabe
   :reader read-seitenangabe
   :initarg :init-seitenangabe))

(defclass zeitschriftenartikel (literaturbeitrag)
  (zeitschrift
   :reader read-zeitschrift
   :initarg :init-zeitschrift)
  (bandnummer
   :reader read-bandnummer
   :initarg :init-bandnummer)
  (heftnummer
   :reader read-heftnummer
   :initarg :init-heftnummer)
  (erscheinungsmonat
   :reader read-erscheinungsmonat))

(define Beispiel-Buch (make buch
                            :init-key (erzeuge-key "Nessie" 1790 "Mein Leben im Loch Ness: Verfolgt als Ungeheuer")
                            :init-autor "Nessie"
                            :init-jahr 1790
                            :init-titel "Mein Leben im Loch Ness: Verfolgt als Ungeheuer"
                            :init-verlag "Minority-Verlag"
                            :init-verlagsort "Inverness"
                            :init-reihe "Die besondere Biographie"
                            :init-seriennummer "Band 1"))

(define Beispiel-Sammelband (make sammelband
                                  :init-key (erzeuge-key "Prefect, F." 1979 "Mostly harmless - some observertions concerning the third planet of the solar system")
                                  :init-autor "Prefect, F."
                                  :init-jahr 1979
                                  :init-titel "Mostly harmless - some observertions concerning the third planet of the solar system"
                                  :init-verlag "Galactic Press"
                                  :init-verlagsort "Vega-System, 3rd planet"
                                  :init-reihe "Travel in Style"
                                  :init-seriennummer "Volume 5"
                                  :init-herausgeber "Adams, D."
                                  :init-seitenangabe 500))

(define Beispiel-Zeitschriftenartikel (make zeitschriftenartikel
                                            :init-key (erzeuge-key "Wells, H. G." 3200 "Zeitmaschinen leicht gemacht")
                                            :init-autor "Wells, H. G."
                                            :init-jahr 3200
                                            :init-titel "Zeitmaschinen leicht gemacht"
                                            :init-zeitschrift "Heimwerkerpraxis für Anfänger"
                                            :init-bandnummer 3
                                            :init-heftnummer 500))

;1.2
(defgeneric cite ((literaturbeitrag))
  :combination generic-append-combination)

(defmethod cite ((b buch))
  (list (string-append (read-verlag b) (read-verlagsort b) (read-reihe b) (read-seriennummer b))))

(defmethod cite ((lb literaturbeitrag))
  (list (string-append (read-autor lb) " (" (number->string (read-jahr lb)) ") " (read-titel lb))))

(defmethod cite ((sa sammelband))
  (list (string-append (read-herausgeber sa) (number->string (read-seitenangabe sa)))))
  
(defmethod cite ((zt zeitschriftenartikel))
  (list (string-append (read-zeitschrift zt) (number->string (read-bandnummer zt)) (number->string (read-heftnummer zt)))))
  
(displayln (cite Beispiel-Buch))
(displayln (cite Beispiel-Sammelband))
(displayln (cite Beispiel-Zeitschriftenartikel))

;Aufgabe 2

;2.1
(defclass fahrzeug ()
  (maximalgeschwindigkeit
   :initarg :maxgeschw
   :reader read-maxgeschw)
  (zuladung
   :initarg :zul
   :reader read-zul)
  (verbrauch
   :initarg :verb
   :reader read-verb)
  (passigier
   :initarg :passa
   :reader read-passa))

(defclass landfahrzeug (fahrzeug)
  (medium
   :initvalue 'land
   :reader read-medium))
  
(defclass wasserfahrzeug (fahrzeug)
  (medium
   :initvalue 'wasser
   :reader read-medium))

(defclass luftfahrzeug (fahrzeug)
    (medium
   :initvalue 'luft
   :reader read-medium))

(defclass amphibienfahrzeug (landfahrzeug wasserfahrzeug))
  
(defclass batmanfahrzeug (amphibienfahrzeug luftfahrzeug))

(define auto (make landfahrzeug :maxgeschw 100 :zul 20 :verb 12 :passa 4))
(define boot (make wasserfahrzeug :maxgeschw 50 :zul 2000 :verb 20 :passa 20))
(define flugzeug (make luftfahrzeug :maxgeschw 1000 :zul 10 :verb 150 :passa 10))
(define hovercraft (make amphibienfahrzeug :maxgeschw 80 :zul 10 :verb 30 :passa 8))
(define batmobil (make batmanfahrzeug :maxgeschw 200 :zul 50 :verb 20 :passa 2))

(defgeneric hole-medium ((fahrzeug))
  :combination generic-append-combination)
; Wir moechten eine Liste aller Bewegungsmodi dieses Fahrzeugs haben.
(defmethod hole-medium ((lf landfahrzeug))
  (list (read-medium lf)))
(defmethod hole-medium ((wf wasserfahrzeug))
  (list (read-medium wf)))
(defmethod hole-medium ((lf luftfahrzeug))
  (list (read-medium lf)))
(defmethod hole-medium ((af amphibienfahrzeug))
  (list (read-medium af)))
(defmethod hole-medium ((btf batmanfahrzeug))
  (list (read-medium btf)))

(defgeneric hole-maxgeschw ((fahrzeug))
  :combination generic-min-combination)
; Wir moechten aus der Hierarchie das Geringste haben.
(defmethod hole-maxgeschw ((lf landfahrzeug))
  read-maxgeschw lf)
(defmethod hole-maxgeschw ((wf wasserfahrzeug))
  read-maxgeschw wf)
(defmethod hole-maxgeschw ((lf luftfahrzeug))
  read-maxgeschw lf)
(defmethod hole-maxgeschw ((af amphibienfahrzeug))
  read-maxgeschw af)
(defmethod hole-maxgeschw ((btf batmanfahrzeug))
  read-maxgeschw btf)

(defgeneric hole-zul ((fahrzeug))
  :combination generic-min-combination)
; Wir moechten aus der Hierarchie das Geringste haben.
(defmethod hole-zul ((lf landfahrzeug))
  read-zul lf)
(defmethod hole-zul ((wf wasserfahrzeug))
  read-zul wf)
(defmethod hole-zul ((lf luftfahrzeug))
  read-zul lf)
(defmethod hole-zul ((af amphibienfahrzeug))
  read-zul af)
(defmethod hole-zul ((btf batmanfahrzeug))
  read-zul btf)

(defgeneric hole-verb ((fahrzeug))
  :combination generic-min-combination)
; Wir moechten aus der Hierarchie das Geringste haben.
(defmethod hole-verb ((lf landfahrzeug))
  read-verb lf)
(defmethod hole-verb ((wf wasserfahrzeug))
  read-verb wf)
(defmethod hole-verb ((lf luftfahrzeug))
  read-verb lf)
(defmethod hole-verb ((af amphibienfahrzeug))
  read-verb af)
(defmethod hole-verb ((btf batmanfahrzeug))
  read-verb btf)

(defgeneric hole-passa ((fahrzeug))
  :combination generic-min-combination)
; Wir moechten aus der Hierarchie das Geringste haben.
(defmethod hole-passa ((lf landfahrzeug))
  read-passa lf)
(defmethod hole-passa ((wf wasserfahrzeug))
  read-passa wf)
(defmethod hole-passa ((lf luftfahrzeug))
  read-passa lf)
(defmethod hole-passa ((af amphibienfahrzeug))
  read-passa af)
(defmethod hole-passa ((btf batmanfahrzeug))
  read-passa btf)

; Wir haben keine Ahnung, warum die Aufrufe nicht gehen bzw. falsche Ergebnisse zurueckliefern.
(displayln (hole-medium hovercraft))
(displayln (hole-maxgeschw batmobil))
(displayln (hole-zul auto))
(displayln (hole-verb hovercraft))
(displayln (hole-passa batmobil))

;Aufgabe 3

;3.1
;a) evaluiert zu -1: Erst wird (- 2 3) zu -1 ausgewertet, danach (min 2 -1) zu -1
;und danach (max -1) zu -1.
;b) evaluiert zu '(+ ,(-24) 2): Das '() erzeugt eine Liste und verhindert, dass der Inhalt vorher ausgewertet wird.
;Das 1. Listenelement ist also das +, das 2. ist ,(-24) und das 3. 2
;c) evaluiert zu 'Alle: car gibt das 1. Element einer Liste zurück. In diesem Fall das Symbol Alle
;d) evaluiert zu '(auf (dem See)): cdr entfernt das 1. Element einer Liste und gibt die Restliste zurück.
;In diesem Fall wird das 'schwimmen entfernt
;e) evaluiert zu '(Listen sind einfach): cons fügt 2 Elemente zu einem Paar zusammen. Da es sich um 2 Listen handelt
;entseht wieder eine Liste
;f) evaluiert zu '(Paare . auch): Cons fügt die beiden Elemente zu einem Paar zusammen
;g) evaluiert zu #t: equal überprüft ob der Inhalt gleich ist. In diesem Fall ist das wahr, da
; (list 'Racket 'Prolog 'Java) zu '(Racket Prolog Java) evaluiert
;h) evaluiert zu #f: eq? vergleicht die Referenz nicht den Wert. Der ist obwohl der selbe Inhalt verglichen wird
;unterschiedlich
;i) evaluiert zu '(1 8 27):
;j) evaluiert zu '(1 3 5): filter odd? such alle ungeraden Listenelemente aus der gegeben Liste
;und gibt diese als neue Liste zurück
;k) evaluiert zu 2: es wird (min 6 2) ausgeführt
;l) evaluiert zu #t: es wird (= 2 2) ausgeführt

;3.2
;1) Ja, es evaluiert zu 10
;2) Nein, da + 2 Zahlen erwartet und *b* ein Symbol ist
;3) Ja, es evaluiert zu 20, da 10 + 10 gerechnet wird, da eval das '*a* extra noch einmal auswertet
;4) Ja, es evaluiert zu #f in Racket werden werden "und" und "oder" träge ausgewertet. (> *b* 3) würde
; einen fehler geben aus dem selben Grund wie bei 2) aber da (> *a* 10) schon #f ergibt, kommt es gar nicht 
; dazu, dass der 2. Teil ausgewertet wird und es wird #f zurück gegeben.
;5) Nein, man darf auch in Racket nicht durch 0 teilen

;3.3
;a)
(+ (* 3 4) (* 5 6))
;b)
(define (berechne-b x)
  (sqrt (- 1 (sqr (sin x)))))

;3.4
(define (länge-vektor a b)
  (sqrt (+ (sqr a) (sqr b))))
(define (mytan a)
  (/ (sin a) (sqrt (- 1 (sqr (sin a))))))

;3.5
(/ (+ 1 4) (- 2 1))
(/ (- 2 (/ (+ 1 3) (* (+ 3 2) 3))) (sqrt 3))

;3.6
; (1 + 2 + 3) * (2 - 3 - (2 - 1))