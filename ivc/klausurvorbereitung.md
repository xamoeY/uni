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


# Pruefungsunterlagen Teil 5

## Elektromagnetische Strahlung


# Pruefungsunterlagen Teil 6


# Pruefungsunterlagen Teil 7


# Pruefungsunterlagen Teil 8


# Pruefungsunterlagen Teil 9


# Pruefungsunterlagen Teil 10


# Zur Prüfungsvorbereitung: Verständnisfragen
## Koordinaten und Transformationen

(a) Wie unterscheiden sich das linkshändige und das rechtshändige Koordinatensystem?

Linkshaendig: Z geht von uns weg. Rechtshaending: Z kommt auf uns zu.

(b) Geben Sie die Matrizen für grundlegende Transformationen im 2D und 3D an.

2D-Translation:

    [xy1] * | 1 | 0 | 0 |
            | 0 | 1 | 0 |
            |t_x|t_y| 1 |
            
2D-Skalierung:

    [xy1] * |s_x| 0 | 0 |
            | 0 |s_y| 0 |
            | 0 | 0 | 1 |

2D-Rotation:

    [xy1] * |cos(a) |sin(a)| 0 |
            |-sin(a)|cos(a)| 0 |
            |     0 |    0 | 1 |

2D-Scherung:

    [xy1] * |   1 |sch_y| 0 |
            |sch_x|    1| 0 |
            |   0 |    0| 1 |

3D-Translation:

    [xyz1] * | 1 | 0 | 0 | 0 |
             | 0 | 1 | 0 | 0 |
             | 0 | 0 | 1 | 0 |
             |t_x|t_y|t_z| 1 |
             
3D-Skalierung:

    [xyz1] * |s_x| 0 | 0 | 0 |
             | 0 |s_y| 0 | 0 |
             | 0 | 0 |s_z| 0 |
             | 0 | 0 | 0 | 1 |

3D-Rotation:

    [xyz1] * |cos(a) |sin(a)| 0 | 0 |
             |-sin(a)|cos(a)| 0 | 0 |
             |     0 |    0 | 1 | 0 |
             |     0 |    0 | 0 | 1 |
    
    
(c) Welche Transformationen sind kommutativ, welche nicht?

Alle Transformationen gleichen Typs sind kommutativ.

(d) Welche Transformationen benötigen Sie, um den Radius einer Kugel zu verdoppeln, deren Mittelpunkt die Koordinaten (1,1,2) hat? Geben Sie die Matrizen an.

    |  1 |  0 |  0 | 0 |
    |  0 |  1 |  0 | 0 |
    |  0 |  0 |  1 | 0 |
    | -1 | -1 | -2 | 1 |

    |  2 |  0 |  0 | 0 |
    |  0 |  2 |  0 | 0 |
    |  0 |  0 |  2 | 0 |
    |  0 |  0 |  0 | 1 |

    |  1 |  0 |  0 | 0 |
    |  0 |  1 |  0 | 0 |
    |  0 |  0 |  1 | 0 |
    |  1 |  1 |  2 | 1 |

(e) Gegeben sei ein achsenparalleler Einheitswürfel zentriert um den Ursprung und direkt daneben, zentriert um die positive X-Achse, eine Einheitkugel. Welche Transformation ist nötig, um die Kugel direkt mittig über den Würfel zu setzen?

    |  1 |  0 |  0 | 0 |
    |  0 |  1 |  0 | 0 |
    |  0 |  0 |  1 | 0 |
    |  -(kantenlaenge/2 + radius/2) |  (kantenlaenge/2 + radius/2) |  0 | 1 |

(f) Welche Fixpunkte haben Translation, Rotation und Scherung?

Bei Translation keine. Bei Skalierung Ursprung. Bei Rotation Zentrum. und Scherung dunno lol.

(g) Gegeben seien die Punkte P 1 = (1,2,3,4), P 2 = (2,4,6,8) und P 3 = (0.75,1,1.5,2) in homogenen Koordinaten. Welche Punkte sind identisch?

P1 und P2, is ja klar.


## Projektionen:

(a) Erkären Sie den Unterschied zwischen orthogonaler und schiefer Parallelprojektion.

Bei ortogonaler Parallelprojektion sehen wir genau eine Achse hinunter, sind also senkrecht auf der Bildebene (z.b. bei Grundrissen). Bei schiefen Parallelprojektionen sehen wir keiner alleinigen Achse hinunter und stehen nicht senkrecht auf der Bildebene.

(b) Nennen Sie Vor- und Nachteile und wichtige Anwendungen der einzelnen Projektionen.

Orthogonale Projektion: Schwierig erkennbar fuer ungeuebte Augen aber fuer technische Zeichnungen sehr wichtig und sinnvoll aufgrund der vereinfachten und uniformen Struktur. Teilweise mehrere Ansichten notwendig. Nicht immer eindeutig.
Schiefe Parallelprojektion: Fuer mathematische Zeichnungen, fuer Schaubilder
Perspektivische Projeketionen: Besser fuer Visualisierungen fuer ungeuebte Menschen. Interior Design. Winkel gehen verloren.

(c) Was sind Hauptfluchtpunkte und wo liegen diese im Bild?

Per Definition: Ein Hauptfluchtpunkt ist der Fluchtpunkt von Geraden, die parallel zu einer der Achsen des Weltkoordinatensystems sind.

(d) Gegeben sei eine Kamera, die auf der Y-Achse über der XZ-Ebene steht und leicht nach unten geneigt ist. Wie verändert sich die Lage der Hauptfluchtpunkte, wenn Sie die Kamera etwas stärker nach unten neigen? Wie verändert sich die Lage der Hauptfluchtpunkte, wenn Sie die die Brennweite der Kamera verdoppeln?

Bei der Neigung nach unten wandern die Fluchtpunkte nach oben. Bei Verdoppelung der Brennweite der Kamera wandern die Fluchtpunkte in die Mitte des Bildes.

(e) Was sind konjugierte Fluchtpunkte? Wo liegt der konjugierte Fluchtpunkt zu einem Fluchtpunkt auf der Horizontlinie?

Per Definition: Die Fluchtpunkte x_1 und x_2 der zueinander senkrechten Geraden g_1 ⊥ g_2 parallel zur Grundebene heißen konjugierte Fluchtpunkte.

(f) Ist die Zentralprojektion invertierbar?

Nein, da wir Informationen ueber Winkel verlieren.

(g) Geben Sie die Projektionsmatrix für die Zentralprojektion und die inverse Zentralprojektion an.

P_z= |  1 |  0 |  0 | 0 |
     |  0 |  1 |  0 | 0 |
     |  0 |  0 |  0 |1/f|
     |  0 |  0 |  0 | 1 |

P_z = |  1 |  0 |  0 |  0 |
      |  0 |  1 |  0 |  0 |
      |  0 |  0 |  1 |1/f|
      |  0 |  0 |  0 |  1 |

(h) Was ist die perspektivische Verkürzung?

Alle x und y-Koordinaten werden bei der Projektion ins Bild proportional zur Entfernung z verkürzt.

Die Verkürzung ist umso stärker, je kleiner f ist.

(i) Erklären Sie die Illusion des Ames-Raumes.

Texturverzerrung und Raumdeformation um optische Taeuschung zu erschaffen. Die Person links steht in Wirklichkeit tiefer im Raum, aber wirkt so als ob sie neben der Person rechts stuende.

(j) Wie unterscheidet sich die Abbildung durch eine Lochkamera von der Abbildung durch eine Linsenkamera?

Eine Lochkamera ist unscharf, wenn das Loch grosz ist, aber wenn man das Loch vergroeszert, wird das Bild schnell unscharf. Linsenkameras kompensieren das Problem dadurch, dass das Licht gebuendelt wird, bevor es den Brennpunkt erreicht.

(k) Was sind Nahpunkt und Fernpunkt und wovon hängt deren Lage ab?

Per Definition: Die Ebenen, die den Bereich begrenzen, in dem bei einer gegeben Einstellebene die Zerstreuungskreise kleiner sind als die Auflösung des Bildes, heißen Nahpunktsebene und Fernpunktsebene, die Schnittpunkte dieser Ebenen mit der optischen Achse heißen entsprechend Nahpunkt t_N und Fernpunkt t_F .

## Licht und Farbe:

(a) Wie hängen Wellenlänge, Frequenz, Geschwindigkeit und Farbe des Lichtes zusammen?

Wellenlaenge = Geschwindigkeit/Frequenz

Wellenlaenge bestimmt Farbe des Lichtes.

(b) Wie hängt die Farbe einer Lichtquelle mit der Temperatur der Lichtquelle zusammen?

Man nimmt hierfuer als Vergleich einen schwarzen Koerper, der so stark erhitzt wird, dass er das Licht der Farbe ausstrahlt, das man erhalten moechte. Die Temperatur dieses schwarzen Koerpers entspricht dann der Temperatur des Lichtes.

(c) Nennen Sie einige Farbmodelle.

RGB, CMYK, CIE, YIQ

(d) Wie können Farben aus Grundfarben gemischt werden?

Per Skript: Für Menschen mit normaler Farbtüchtigkeit lassen sich alle Farbtöne selbstleuchtender Farben durch die drei Primärfarben (Rot, Grün, Blau) hinreichend und eindeutig beschreiben.

(e) Was sind Komplementärfarben?

Komplementärfarben sind Paare von Farben, deren additive Mischung weiß ergibt, bzw. schwarz bei subtraktiver Mischung,

(f) Nennen Sie die Komplementärfarbe zu „rot“ im RGB- und im CMY-System.

Cyan jeweils.

(g) Welche Farbe erhalten Sie bei der additiven Mischung von „rot“ und „blau“ und welche bei der subtraktiven Mischung?

Bei additive: Magenta, bei subtraktiv: Schwarz

(h) Was ist die chromatische Aberration? Welche Konsequenzen hat sie für das Farbensehen?

Das sichtbare Licht bestesht aus verschiedenen Wellenlaengen. Chromatische Aberration fuehrt dazu, dass Linsen die verschiedene Brechungsindices fuer verschiedene Wellenlaengen haben, ein geisterhaftes Bild erzeugen.

(i) Welche Farbe können wir am schlechtesten wahrnehmen? Warum?

Blau koennen wir am schlechtesten sehen, da nur 2% der Zapfen blau-empfindlich sind.

(j) Was ist Dispersion?

Per Skript:

* Die Komponenten eines Gemischs von Licht unterschiedlicher Wellenlängen werden unterschiedlich stark gebrochen.
* Beim Durchgang von weißem Licht durch ein Prisma tritt daher eine Dispersion ein.
* Die Brennpunkte von Linsen aus nur einem Material sind für jede Wellenlänge anders (Chromatische Aberration).
* Zur Korrektur von solchen Farbfehlern werden Objektive aus mehreren Linsen mit unterschiedlicher Brechzahl hergestellt.

## Fraktale und Texturen:

(a) Nennen Sie wichtige Eigenschaften der quadratischen Kochkurve.

(b) Wie können Fraktale eingesetzt werden, um Oberflächen zu modellieren?

(c) Was sind Drachenkurven?

(d) Warum sind Texturen für die photorealistische Computergrafik wichtig?

(e) Warum sind Texturen für die räumliche Wahrnehmung wichtig?


## Ikonische Bildverarbeitung:

(a) Welche Teilaufgaben sind zu lösen, um aus einem kontinuierlichen Bildsignal ein Digitalbild zu machen?

(b) Wie kann der Kontrast eines Bildes erhöht werden?

(c) Was ist beim Verkleinern eines Bildes zu beachten?

(d) Was ist Aliasing und wann tritt dieser Effekt auf?

(e) Wie kann Aliasing vermieden werden?

(f) Wodurch kann die Schärfe eine Bildes erhöht werden?

(g) Wodurch können systematische Bildstörungen mit einer typischen Frequenz beseitigt werden?

(h) Was bewirkt ein Tiefpaßfilter?


## Segmentieren von Bildern:

(a) Nennen Sie einige Kantenfinder und beschreiben Sie die Algorithmen.

(b) Welche Rolle spielen Gradienten beim Kantenfinden?

(c) Wie können mit dem Laplace-Operator Kanten gefunden werden?

(d) Welcher Kanten-Operator ist besonders rauschempfindlich umd warum?


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
