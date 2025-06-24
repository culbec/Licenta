CREATE DATABASE Main;
USE Main;

-- 1. Create Database Schema
CREATE TABLE Firma(
    CodFirma INTEGER PRIMARY KEY AUTOINCREMENT,
    Nume TEXT NOT NULL CHECK(length(Nume) > 4),
    TaraProvenienta TEXT NOT NULL CHECK(length(TaraProvenienta) > 4)
);

CREATE TABLE Bicicleta(
    CodBicicleta INTEGER PRIMARY KEY AUTOINCREMENT,
    CodFirma INTEGER NOT NULL,
    Model TEXT NOT NULL CHECK(length(Model) > 4),
    Marime INTEGER NOT NULL CHECK(Marime > 0),
    PretInchirere FLOAT NOT NULL CHECK(PretInchirere > 10.0),
    FOREIGN KEY FK_Firma(CodFirma) REFERENCES Firma(CodFirma)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Client(
    CNP INTEGER PRIMARY KEY AUTOINCREMENT
    NumarTelefon TEXT NOT NULL UNIQUE,
    Email TEXT NOT NULL UNIQUE,
    Nume TEXT NOT NULL,
);

CREATE TABLE FisaInchiriere(
    CodFisaInchiriere INTEGER PRIMARY KEY AUTOINCREMENT
    CodClient TEXT   NOT NULL,
    DataIntocmire DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT UNIQUE_Client_DataIntocmire UNIQUE(CodClient, DataIntocmire),
    FOREIGN KEY FK_Client(CodClient) REFERENCES Client(CNP)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
);

-- we need to make sure that the Bicicleta is not rented
-- at the same time by two persons
CREATE TABLE InchiriereBicicleta(
    CodFisaInchiriere INTEGER NOT NULL,
    CodBicicleta INTEGER NOT NULL,
    DataInceput DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    DataSfarsit DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY FK_FisaInchiriere(CodFisaInchiriere) REFERENCES FisaInchiriere(CodFisaInchiriere)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY FK_Bicicleta(CodBicicleta) REFERENCES Bicicleta(CodBicicleta)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT PK_InchiriereBicicleta PRIMARY KEY (CodFisaInchiriere, CodBicicleta, DataInceput, DataSfarsit)
)

-- 2. SQL Queries on existing database schema
Clienti[PK_CodClient, NumeClient, Telefon]
Soferi[PK_CodSofer, NumeSofer, Salariu]
Autoturisme[PK_CodAuto, NumarInmatriculare, MarcaAuto, FK_CodSofer]
Curse[PK_CodCursa, FK_CodClient, FK_CodAuto, DataCursa, MomentPlecare, DurataCursa, LocPlecare, Destinatie, SumaDePlata]

-- a)
SELECT DISTINCT S.CodSofer, S.NumeSofer, S.Salariu
FROM Soferi S
WHERE S.CodSofer IN (
    SELECT S1.CodSofer
    FROM Soferi S1
    INNER JOIN Autoturisme A1 ON S1.CodSofer = A1.CodSofer
    INNER JOIN Curse Cu1 ON A1.CodAuto = Cu1.CodAuto
    WHERE A1.MarcaAuto = 'Ford' AND Cu1.Destinatie = 'Iulius Mall Cluj'    
)
AND S.Salariu = (
    SELECT MAX(S2.Salariu)
    FROM Soferi S2
    INNER JOIN Autoturisme A2 ON S2.CodSofer = A2.CodSofer
    INNER JOIN Curse Cu2 ON A2.CodAuto = Cu2.CodAuto
    WHERE A2.MarcaAuto = 'Ford' AND Cu2.Destinatie = 'Iulius Mall Cluj' 
);

-- b)
Autoturisme
CodClient       NumarInmatriculare      MarcaAuto       CodSofer
1               CJ11AAA                 Ford            1
2               CJ22BBB                 Opel            2
3               CJ33CCC                 Volkswagen      3

Curse
CodCursa        CodClient               CodAuto         DataCursa       MomentPlecare           DurataCursa         LocPlecare          Destinatie      SumaDePlata
1               1                       1               2023.06.25      07:30                   15                  LP1                 D1              20
2               1                       2               2023.06.26      08:30                   20                  LP2                 D3              30
3               2                       1               2023.06.26      12:30                   10                  LP4                 D4              15
4               1                       1               2023.06.30      10:15                   5                   LP1                 D2              10
--5               3                       3               2023.07.01      15:05                   40                  LP1                 D4              50
--6               3                       2               2023.07.01      20:00                   12                  LP2                 D2              15

-- b1) CodSofer + NumarDistinctClienti pt soferul/soferii care au transportat
-- numarul maxim de clienti distincti in perioada 01/01/2023-30/06/2023
SELECT a.CodSofer, COUNT(DISTINCT c.CodClient) Nr
FROM Autoturisme a INNER JOIN Curse c ON a.CodAuto = c.CodAuto
WHERE c.DataCursa BETWEEN '2023.01.01' AND '2023.06.30'
GROUP BY a.CodSofer
HAVING COUNT(DISTINCT c.CodClient) >= ALL
    (
        SELECT COUNT(DISTINCT c.CodClient)
        FROM Autoturisme a INNER JOIN Curse C ON a.CodAuto = c.CodAuto
        WHERE c.DataCursa BETWEEN '2023.01.01' AND '2023.06.30'
        GROUP BY a.CodSofer
    )

CodSofer        Nr
1               2

-- b2) 
-- {CodCursa} -> {CodAuto}. Avem CodCursa unice => ok!
-- {CodAuto} -> {LocPlecare}. CodAuto=1 are LocPlecare=LP1 sau LocPlecare=LP4, deci nu e adevarat

DROP DATABASE Main;