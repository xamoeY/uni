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
* **Skalierung:** Vergroezerung/Verkleinerung (x * s_x, y * s_y)
