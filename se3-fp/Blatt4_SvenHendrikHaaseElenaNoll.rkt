#lang racket
;Aufgabe 1.1

;Evaluiert zu 0: Zu erst wird die Subtraktion, danach (min 2 -1) zu -1 und zum Schluss (max -1 0) zu 0 ausgewertet.

;Aufgabe 1.2
;Evaluiert gar nicht, da das einfache Semikolon eine Auswertung verhindert. 
;Der Ausdruck wird genau so wie er eingegeben wird wieder ausgegeben.

;Aufgabe 1.3
;Evaluiert zu 'drauss.
;'(Von drauss vom Walde) ist eine Liste. cadr gibt das 2. Listenelement aus.

;Aufgabe 1.4
;Evaluiert zu '(). Gibt die leere Liste zurück, da cddr das 3. Element einer Liste zurückgeben würde, 
;unsere Liste aber nur 2 Elemente enhält.

;Aufgabe 1.5
;Evaluiert zu der Liste '(Listen sind einfach). Cons vereinigt das Symbol 'Listen mit der Liste '(sind einfach) 
;zu einer gemeinsamen Liste.

;Aufgabe 1.6
;Evaluiert zu dem Paar '(Paare . auch). Cons vereinigt die beiden Symbole zu einem Paar.

;Aufgabe 1.7
;Evaluiert zu true. (list 'Racket 'Prolog 'Java) erzeugt die Liste '(Racket Prolog Java). Somit wird
;(equal? '(Racket Prolog Java) '(Racket Prolog Java)) ausgewertet was true ergibt.

;Aufgabe 1.8
;Evaluiert zu false. (list 'Racket 'Prolog 'Java) wird wie oben beschrieben zu '(Racket Prolog Java) ausgewertet.
;(cons 'Racket '(Prolog Java)) wird ebefalls zu '(Racket Prolog Java) ausgewertet. Würde man nun nach equal? fragen 
;würde der Ausdruck zu true ausgewertet werden. eq? testet aber ob auf das selbe Objekt referenziert wird.
;Dies ist nicht der Fall und deshalb evaluiert der Ausdruck zu false.

;2.1
;<notfallfunkspruch> ::= <ueberschrift-teil> <standort-teil> <zeitpunkt-teil> <beschreibung-teil> <weitere-angaben-teil>
;                        <peilzeichen-teil> <unterschrift-teil> "OVER" <EOL>
;<ueberschrift-teil> ::= <mayday3-teil> "HIER IST" <EOL> <namens3-teil> <rufzeichen-teil> "MAYDAY"
;                        <namens-teil> "ICH BUCHSTABIERE" <name-buchstabiert-teil> "RUFZEICHEN" <rufzeichen-teil>
;<mayday3-teil> ::= "MAYDAY" "MAYDAY" "MAYDAY" <EOL>
;<namens3-teil> ::= <schiffname> <schiffname> <schiffname>
;<rufzeichen-teil> ::= <rufzeichen-buchstabiert> <EOL>
;<namens-teil> ::= <schiffname>
;<name-buchstabiert-teil> :== <schiffname-buchstabiert> <EOL>
;<standort-teil> ::= "NOTFALLPOSITION UNGEFÄHR" <position-teil> <EOL>
;<position-teil> ::= <position>
;<zeitpunkt-teil> ::= "NOTFALLZEIT" <zeitpunkt> <EOL>
;<beschreibung-teil> ::= <beschreibung> <EOL>
;<weitere-angaben-teil> ::= <weitere-angaben> <EOL>
;<peilzeichen-teil> ::= <peilzeichen> <EOL>
;<unterschrift-teil> ::= <namens-teil> <rufzeichen-teil> <EOL>

;2.2
;Buchstabiertafel mit Hilfsfunktionen:
(define Internationale-Buchstabiertafel
   '((#\A "Alfa")
     (#\B "Bravo")
     (#\C "Charlie") 
     (#\D "Delta")
     (#\E "Echo")
     (#\F "Foxtrott")
     (#\G "Golf")
     (#\H "Hotel")
     (#\I "India")
     (#\J "Juliett")
     (#\K "Kilo")
     (#\L "Lima")
     (#\M "Mike")
     (#\N "November")
     (#\O "Oscar")
     (#\P "Papa")
     (#\Q "Quebec")
     (#\R "Romeo")
     (#\S "Sierra")
     (#\T "Tango")
     (#\U "Uniform")
     (#\V "Viktor")
     (#\W "Whiskey")
     (#\X "X-ray")
     (#\Y "Yankee")
     (#\Z "Zulu")
     (#\0 "Nadazero")
     (#\1 "Unaone")
     (#\2 "Bissotwo")
     (#\3 "Terrathree")
     (#\4 "Kartefour")
     (#\5 "Pantafive")
     (#\6 "Soxisix")
     (#\7 "Setteseven")
     (#\8 "Oktoeight")
     (#\9 "Novenine")
     (#\, "Decimal")
     (#\space " ")))

(define (Buchstabe->Schlüssel char)
  (car(reverse(assoc (char-upcase char) Internationale-Buchstabiertafel))))

(define (Übersetze-Text-Helper2 text-liste)
  (string-append (Buchstabe->Schlüssel (car text-liste)) " " (Übersetze-Text-Helper (cdr text-liste))))

(define (Übersetze-Text-Helper text-liste)
  (if (empty? text-liste) "" (Übersetze-Text-Helper2 text-liste)))

(define (Übersetze-Text text)
  (Übersetze-Text-Helper (string->list text)))

;Eigentliche Funktion zum absenden des Notrufes.
(define (NOTRUF schiffsname rufzeichen position zeit sonstiges)
  (string-append "MAYDAY MAYDAY MAYDAY" " ~n " 
                 "HIER IST" " ~n " 
                 schiffsname " " schiffsname " "schiffsname " " (Übersetze-Text rufzeichen) "~n "
                 "MAYDAY " schiffsname " ICH BUCHSTABIERE " (Übersetze-Text schiffsname) "~n "
                 "Rufzeichen " (Übersetze-Text rufzeichen) "~n "
                 "NOTFALLPOSITION " position " ~n "
                 "NOTFALLZEIT " zeit " ~n "
                 sonstiges " ~n "
                 "ICH SENDE DEN TRÄGER --" " ~n "
                 schiffsname " " (Übersetze-Text rufzeichen) "n "
                 "OVER"))

;Aufgabe 2.3
(NOTRUF "BABETTE" "DEJY" "10 SM  NORDÖSTLICH LEUCHTTURM KIEL" "1000 UTC" "SCHWERER WASSEREINBRUCH WIR SINKEN KEINE VERLETZTEN VIER MANN GEHEN IN DIE RETTUNGSINSEL SCHNELLE HILFE ERFORDERLICH")

(NOTRUF "BYE BYE LOVE" "DESY" "055°45’N, 006°31’E" "1020 UTC" "NACH KENTERUNG IN SCHWERER SEE SINKT: 8 MANN AN BOARD SCHIFF IST 12M LANG BLAUER RUMPF")

;Aufgabe 3.1
;Inerre Reduktion reduzirt die Terme von innen nach außen, äußere Reduktion genau umgedreht von außen nach innen.
;inerre Rekudtion:
;    (sqr (* 3 (+ 1 (sqr 2))))
;        ->(sqr (* 3 (+ 1 (* 2 2))) ;(sqr)
;        ->(sqr (* 3 (+ 1 4)) ;(*)
;        ->(sqr (* 3 5)) ;(+)
;        ->(sqr 15) ;(*)
;        ->(* 15 15) ;(sqr)
;        ->225 ;(*)

;äußere Reduktion
;    (sqr (* 3 (+ 1 (sqr 2))))
;        ->(* (* 3 (+ 1 (sqr 2))) (* 3 (+ 1 (sqr 2))) ;(sqr)
;        ->(* (* 3 (+ 1 (* 2 2))) (* 3 (+ 1 (sqr 2))) ;(sqr)
;        ->(* (* 3 (+ 1 4)) (* 3 (+ 1 (sqr 2))) ;(*)
;        ->(* (* 3 5) (* 3 (+ 1 (sqr 2))) ;(+)
;        ->(* 15 (* 3 (+ 1 (sqr 2))) ;(*)
;        ->(* 15 (* 3 (+ 1 (* 2 2))) ;(sqr)
;        ->(* 15 (* 3 (+ 1 4))) ;(*)
;        ->(* 15 (* 3 5)) ;(+)
;        ->(* 15 15) ;(*)
;        ->225 ;(*)

;Aufgabe 3.2
;Für normale Funktionen wird die innere Reduktion angewendet. Für Spezialformen die äußere Reduktion.

;Aufgabe 3.3