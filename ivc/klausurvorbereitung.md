# Kram der in der Klausur angeblich vorkommt:

* Bisschen povray Code schreiben 
* Skizzen 
* Modellierungswerkzeuge
* Konzeptionelle Fragen
* Einführung und Grundbegriffe (Computergrafik vs Bildverarbeitung) 
* Prozesse der grafischen Datenverarbeitung 
* BDRF
* Generalitaetsprinzip
* Bewegungsstereo
* Tiefenmessung
* Projektion
* Transformationen zwischen Koordinatensystemen
* Farbtemperatur
* Globale/Lokale Beleuchtungsmodelle
* Flat/Gouraud/Phong
* Zwei/Dreipunktprojektion

# Pruefungsunterlagen Teil 1

## Computergrafik vs. Bildverarbeitung

### Definition: 1 (Computergrafik)
Die Computergrafik ist die Wissenschaft von den Methoden und Techniken
zur Konvertierung von Daten in und aus grafischer Darstellung mit Hilfe von
elektronischen Rechenanlagen. (ISO)
Sie hat die drei Teilgebiete:
* Grafische Datenverarbeitung,
* Bildverarbeitung,
* Bildverstehen / Mustererkennung.

### Definition: 2 (Grafische Datenverarbeitung)
Die grafische Datenverarbeitung umfaßt Verfahren zur Eingabe und Mani-
pulation von Bildbeschreibungen sowie deren Umwandlung in grafische Dar-
stellungen.


## Prozesse der grafischen DV

Physisches Bild (Ikonische Ebene) --- Bildverarbeitung ---> Geometrische Szenenbeschreibung --- Bildverstehen ---> Bildinterpretation

Bildinterpretation --- Visualisierung ---> Geometrische Szenenbeschreibung --- Grafische DV ---> Physisches Bild (Ikonische Ebene)

### Ebenen der Bildbeschreibung

**Ikonische Ebene:** Das ist die Ebene der Bilder als physikalisches Signal, die Beschreibung von Helligkeiten und Farben als Funktion des Ortes im Bild.

**Die geometrische Ebene:** Die geometrische Szenenbeschreibung beschreibt die Anordnung von den im Bild abgebildeten Szenenkomponenten und die Form der Szenenkomponenten.

**Die Bildinterpretation:** Auf der semantischen Ebene wird die Bedeutung einer im Bild dargestellten Szene beschrieben: Welche Objekte gibt es? Was tun sie? Welche Ziele verfolgen sie?


### Verarbeitungsprozesse

**Bildverarbeitung:** (ikonische) Bildverarbeitung im engeren Sinne bezeichnet alle Verarbeitungsverfahren, bei denen Bilder transformiert werden (Bildrestauration, Registrierung, Falschfarbendarstellung usw.) oder elementare Merkmale der Bilder abgeleitet werden. Auf Deutsch alles was man mit Photoshop machen kann.

**Niedere Bilddeutung:** Die niedere Bilddeutung leitet aus Bildern eine
geometrische Bildbeschreibung ab. Hierzu müssen die Konturen von
Objekten anhand der Bildstrukturen ermittelt und mit Objektmodellen
verglichen werden.


### Verarbeitungsprozesse 2

**Grafische Datenverarbeitung:** Die Gegenrichtung zu den bisher genannten Verfahren — die Aufgabe der grafischen DV ist die Synthese von Bildern, ausgehend von einer geometrischen Szenenbeschreibung. Die beschriebenen Komponenten der Szene werden mittels Projektion und Renderingverfahren abgebildet.

**Visualisierung und Bildverstehen:** Die Verarbeitungsprozesse, die zwischen der geometrischen Beschreibung und der Interpretation vermitteln, gehören nicht mehr zum Bereich der Computergrafik, wie er seinerzeit von der ISO festgelegt wurde. Es sind aber wichtige Forschungsgebiete der Künstlichen Intelligenz und der Bildverarbeitung im weiteren Sinne.


### Probleme

Bildverstehen und Computergrafik haben mit sehr unterschiedlichen Schwierigkeiten zu kämpfen:

* Das größte Problem beim Bildverstehen ist die mangelnde Eindeutigkeit: Jedes Bild kann das Abbild von unendlich vielen verschiedenen
Szenen sein.
* Bei der grafischen DV dagegen ist in der Regel die Lösung eindeutig, aber die Aufgabe besteht darin, Algorithmen zu entwickeln, die diese eindeutigen Lösungen in vertretbarer Zeit finden.


## Modelle und Abstraktionen

**Bildfunktion:** Die grundlegende Abstraktion eines Bildes.

**Geometrische Modelle** dienen zur Modellierung der Form und Anordnung von Objekten, sowie der Abbildung von dreidimensionalen Szenen auf zweidimensionale Bildräume.

**Radiometrische Modelle** beschreiben, wie die Anordnung von Licht, Objektoberflächen und Bildwandlern die Helligkeit und Farbe im Bild beeinflußt.

**Farbmodelle** beschreiben die Beziehung zwischen den Farben im Bild
und spektralen Messungen.

**Digitalisierungsmodelle** beschreiben den Prozeß der Diskretisierung von
analogen Bildfunktionen.

### Modelle und Abstraktionen:

**Bildverstehen:** Die geometrischen und radiometrischen Modelle ver-
suchen den physikalischen Prozeß der Bildentstehung möglichst ge-
nau zu erklären.

**Computergrafik:** Die geometrischen und radiometrischen Modelle
sind Approximationen an die physikalischen Prozesse, die adäquate
Algorithmen ermöglichen.

**Virtuelle Welten:** Die Modelle in der Computergrafik können unmög-
liche Welten beschreiben, in denen andere physikalische Gesetze
gelten als in unserem Universum.

**Visualisierung** von konzeptuellen Welten (abstrakten oder unsicht-
baren Phänomenen).

# Pruefungsunterlagen Teil 2

## 2D-Koordinatensysteme

Koordinatensysteme fuer die Angabe der Positionen und Transformationen von Objekten.

2D-Koordinatensysteme dienen in der Computergrafik und Bildverarbeitung zur Beschreibung der relativen Anordnung von Bildelementen.

Die Koordinaten, die von einem spezifischen Ausgabegerät verwendet werden, nennt man Gerätekoordinaten.

Die Benutzer definieren ihre Koordinaten in anwendungsspezifischen Weltkoordinatensystemen. Diese sind unabhängig von den speziellen Gerätekoordinaten

Die verschiedenen Weltkoordinatensysteme werden meist vor der Abbildung auf die Gerätekoordinaten auf ein normalisiertes Koordinatensystem (normalized device coordinates) abgebildet.

## Hierarchie der Koordinatensysteme

**Weltkoordinatensystem:** Anordnung der Szenenobjekte, Betrachtungsparameter.

**Objektkoordinatensystem:** Anordnung der Komponenten von Objekten, relativ zum Objekt definiert.

**Bildkoordinatensystem:** Anordnung der Bildkomponenten.

**Koordinatensysteme der Grafiksysteme:**

* Normalisierte Gerätekoordinaten
* Viewport-Koordinaten
* Bildschirmkoordinaten

## 2D-Transformationen

2D-Transformationen dienen zur Manipulation von ebenen grafischen Darstellungen, beispielsweise:

* einfache Animationen
* Grafikeditoren
* Koordinatensystemwechsel

Es gibt elementare (**Translation**, **Rotation**, **Skalierung**, **Scherung**) und zusammengesetzte Transformationen (Koordinatentransformation).

* **Translation:** Verschiebung (P + t)
* **Rotation:** Drehung (x*cos(a)-y*sin(a))
* **Skalierung:** Vergroezerung/Verkleinerung (x * s_x, y * s_y) *Allgemeine Skalierung:* unterschiedliche s_x/s_y, *uniforme Skalierung:* gleiche s_x/s_y.

### Zusammengesetzte Transformationen

Bei der Abbildung von Weltkoordinaten auf Gerätekoordinaten ist eine Folge von Transformationen auszuführen, die für viele Punkt gleich sind.

* Um Rechenzeit zu sparen und um möglichst wenig Genauigkeit zu verlieren, werden elementare Transformationen zu zusammengesetzten Transformationen komponiert.
* Alle bisher angesprochenen Transformationen lassen sich in **homogenen Koordinaten** als Matrixoperation darstellen.
* Homogene Koordinaten sind notwendig, da sonst nicht alle Transformationen linear wären.


**Homogene Koordinaten:** Ein Punkt P(x,y) wird in homogenen Koordinaten durch das Tripel P = [x · w,y · w,w] repräsentiert, mit w != 0.

### Rechenregeln

Es gilt das **Assoziativgesetz:** (A · B) · C = A · (B · C), ((P · A) · B) · C = P · (A · B · C).

Das **Kommutativgesetz** gilt meistens **nicht**: A · B != B · A,

nur innerhalb derselben Gruppe von Transformationen (z.B. eine Folge von Rotationen oder Skalierungen) gilt: R(α) · R(β) = R(β) · R(α)

T(t_x1, t_y1) · T(t_x2 ,t_y2) = T(t_x1 + t_x2 ,t_y1 + t_y2)

S(s_x1, s_y1) · S(s_x2 ,s_y2) = S(s_x1 · s_x2, s_y1 · s_y2)

R(δ_1) · R(δ_2) = R(δ_1 + δ_2)

Eine Transformation heißt affin, wenn die Transformationsmatrix A die folgende Form hat:

    A = [a d 0
         b e 0
         c f 1]

* Grafikpakete führen für jedes Objekt eine Transformationsmatrix, in der alle anfallenden Transformationen akkumuliert werden werden.
* Diese Matrix wird mit der Einheitsmatrix initialisiert.
* Der Rechenaufwand für die Anzeige ist konstant und unabhängig von der Zahl der Transformationen.
* Rundungsfehler durch die Abbildung auf ganzzahlige Raster werden klein gehalten, da erst am Ende gerundet wird.

## 3D-Koordinatensysteme

**Haendigkeit:**

* Linkshändiges Koordinatensystem: Die Z-Achse zeigt vom Betrachter weg in die Tiefe.
* Rechtshändiges Koordinatensystem: Die Z-Achse zeigt zum Betrachter


## 3D-Transformationen

Ansich aehnlich aber halt mit einem Drechachstenvektor bei Rotationen und die Matrix hat jetzt 4x4 Komponenten.

Eine 3D-Rotation wird durch

* einen Punkt ( das Rotationszentrum),
* einen Vektor (die Richtung der Drehachse)
* und den Rotationswinkel angegeben.

Rotation und Haendigkeit:

Wenn wir die Finger um die Drehachse legen und dabei den Daumen in die positive Richtung der Drehachse zeigen lassen, dann zeigen die Finger in Richtung der positiven Drehwinkel (linke Hand für ein linkshändiges System, rechte Hand für ein rechtshändiges).


## Transformation zwischen Koordinatensystemen

(Gleichungskram)


# Pruefungsunterlagen Teil 3

## Geometrisches Modellieren

Zweck: Halt CAD.

Es gibt zwei grundsätzlich unterschiedliche Methoden, geometrische Modelle zu repräsentieren:

* Volumenbasierte Repräsentation
* Begrenzungsbasierte Repräsentation

### Volumenbasierte Repräsentationsformen

* Octree (Minecraft)
* Constructive Solid Geometry (Union, Subtract, etc)


# Pruefungsunterlagen Teil 4

## Projektion

Eine Projektion ist die Abbildung eines Vektors x aus einem n-dimensionalen Vektorraum X auf einen Vektor u in einem m-dimensionalen Unterraum U für m < n. Also halt einfach ein fucking Schatten.

**Zentralprojektion:** Eine Zentralprojektion wird festgelegt durch die Angabe

• eines Projektionszentrums (Augpunkt)
• und einer Projektionsebene.

**Projektionsstrahlen** sind Geraden durch den Augpunkt und die abzubildenden Punkte.
Das Abbild des Punktes ist der Schnittpunkt seines Projektionsstrahls mit der Bildebene (die Projektion).

## Parallelprojektion

* Die Punkte des Objekts werden entlang paralleler Strahlen auf die Projektionsebene abgebildet.
* Parallele Linien bleiben parallel.
* Wird die Bildebene parallel zu den Projektionsstrahlen verschoben, bleibt das Bild gleich

Die Parallelprojektionen werden in Abhängigkeit vom Winkel, unter dem die Projektionsstrahlen die Bildebene schneiden, in zwei Gruppen unterteilt:

* Orthogonale Projektion
* Schiefe Parallelprojektion


## Orthogonale Projektion

Grundrisse, Snap To Axis


### Normalaxonometrische Projektion:

Eine orthogonale Projektion heißt Normalaxonometrische Projektion, wenn keine Achse des Weltkoordinatensystems senkrecht zur Bildebene ist. Die normalaxonometrischen Projektionen werden danach unterschieden, wie die Bildebene die Achsen des Koordinatensystems schneidet.

**Isometrische Projektion:** Die Schnittpunkte der Bildebene mit den Hauptachsen sind alle gleich weit vom Ursprung entfernt: alle Koordinaten werden gleich verkürzt.
**Dimetrische Projektion:** Zwei Koordinatenachsen werden in der gleichen Entfernung vom Ursprung geschnitten.
**Trimetrische Projektion:** Alle Koordinatenachsen werden in unterschiedlicher Entfernung vom Ursprung von der Bildebene geschnitten, d.h. alle Koordinaten werden paarweise ungleich verkürzt.


## Schiefe Parallelprojektion

Schrägriß
 
Die Projektionsstrahlen stehen nicht senkrecht auf der Bildebene, Angabe durch α und β.


## Zentralprojektion

* Die Zentralprojektion entspricht der Abbildung durch eine Sammellinse (Kameras, unser Auge) oder eine Lochkamera.
* Sie vermittelt durch die perspektivische Verkürzung einen räumlichen Eindruck.
* Die Abbildungen paralleler Geraden enden in einem Fluchtpunkt.
* Winkel bleiben nur dann erhalten, wenn die Geraden parallel zur Bildebene sind.

(Projektionsgleichung)


## Projektionsgleichung für Weltkoordinaten

(Projektionsgleichung)

## Perspektivische Effekte

### Hauptfluchtpunkte

Es gibt mindestens einen und höchstens drei Hauptfluchtpunkte.

Entsprechend der Anzahl der Hauptfluchtpunkte klassifiziert man die Zentralprojektionen:

* Einpunktprojektion: Ein Hauptfluchtpunkt.
* Zweipunktprojektion: Zwei Hauptfluchtpunkte.
* Dreipunktprojektion: Drei Hauptfluchtpunkte.

### Der Fluchtpunkt von vertikalen Geraden

Vereinfachte Projektionsgleichung: Alle Parameter gleich Null, mit Ausnahme des Neigungswinkels ϕ und der Brennweite f.

(Gleichungskram)


### Der Fluchtpunkt von horizontalen Geraden

Vereinfachte Projektionsgleichung: Alle Parameter gleich Null, mit Ausnahme des Neigungswinkels ϕ, der Brennweite f und der Höhe über der Grundebene.


(Gleichungskram)

### Konjugierte Fluchtpunkte

Die Fluchtpunkte x_1 und x_2 der zueinander senkrechten Geraden g_1 ⊥ g_2 parallel zur Grundebene heißen konjugierte Fluchtpunkte.




# POV-Ray Kram

    translate < tx , ty , tz > // Translation mit dem Vektor ( tx , ty , tz )
    translate y * 3 // Translation entlang der Y−Achse (3 * y = <0,3,0>)
    translate y * 3+x // 3 * y+x = <1,3,0>

    #declare stardot = sphere { 0, 0.7
    texture { T_Gold_1B }
    }
    object { stardot
    translate < 0.839746, −14.392706, 12.386859>}

    rotate <20, 10, 3>
    rotate 20 * x
    rotate 10 * y
    rotate 3 * z

    camera {
        perspective
        location <−20, 30, −40>
        look_at <0, 10, 0>
        angle 70
    }
