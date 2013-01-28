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
  (medium
   :initarg :init-fahrzeug
   :reader read-medium))

(defclass landfahrzeug (fahrzeug))

(defclass wasserfahrzeug (fahrzeug))

(defclass luftfahrzeug (fahrzeug))

(defclass amphiefahrzeug (landfahrzeug wasserfahrzeug))

(defclass batmanfahrzeug (amphiefahrzeug luftfahrzeug))