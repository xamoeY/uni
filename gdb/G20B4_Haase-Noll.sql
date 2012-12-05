DROP DATABASE IF EXISTS Uebung;
CREATE DATABASE Uebung;
USE Uebung;

CREATE TABLE Abteilungen (
    aid     int NOT NULL PRIMARY KEY,
    name    varchar(50) UNIQUE
);

CREATE TABLE Personal (
    pid     int NOT NULL PRIMARY KEY,
    vorname varchar(50) NOT NULL,
    nachname    varchar(50) NOT NULL,
    geburt  date    NULL,
    wohnort varchar(50) NULL,
    abteilung   int NOT NULL,
    CONSTRAINT abteilung_id FOREIGN KEY(abteilung) REFERENCES Abteilungen(aid)
);

CREATE TABLE Projekte (
    prid   int NOT NULL PRIMARY KEY,
    name    varchar(100) NOT NULL,
    leiter  int NOT NULL,
    budget  int NOT NULL CHECK(0 < budget < 200000),
    CONSTRAINT personal_id1 FOREIGN KEY(leiter) REFERENCES Personal(pid)
);

CREATE TABLE ProjektArbeiter (
    prid    int NOT NULL,
    pid     int NOT NULL,
    PRIMARY KEY(prid, pid),
    CONSTRAINT projekte_id2 FOREIGN KEY(prid) REFERENCES Projekte(prid),
    CONSTRAINT personal_id2 FOREIGN KEY(pid) REFERENCES Personal(pid)
);

INSERT INTO Abteilungen (aid, name) VALUES (1, "Controlling"),
                                           (4, "Marketing"),
                                           (2, "Einkauf");

INSERT INTO Personal (pid, vorname, nachname, geburt, wohnort, abteilung) VALUES
            (4, "Peter", "Müller", "1962-07-25", "Hamburg", 2),
            (8, "Bianca", "Lohnse", "1982-01-13", "Kiel", 4),
            (11, "Murat", "Sahir", "1990-03-16", "Hamburg", 2),
            (21, "Frank", "Siebenstein", "1975-12-02", "Norderstedt", 1),
            (22, "Bernd", "Schmidt", "1973-11-26", "Norderstedt", 1),
            (24, "Ulrike", "Müller", "1963-10-07", "Hamburg", 2),
            (31, "Jochen", "Fuhrmann", "1958-05-09", "Stade", 2);

INSERT INTO Projekte (prid, name, leiter, budget) VALUES (15, "Prozessoptimierung", 22, 10000),
                                                         (36, "B.L.I.C.K.F.A.N.G", 8, 7500);

INSERT INTO ProjektArbeiter (prid, pid) VALUES (36, 8),
                                               (15, 21),
                                               (36, 11),
                                               (15, 22),
                                               (36, 31);

DELETE FROM Personal WHERE vorname = "Peter" AND nachname = "Müller";
SELECT * FROM Personal;

DROP TABLE ProjektArbeiter;
DROP TABLE Projekte;
DROP TABLE Personal;
DROP TABLE Abteilungen;
