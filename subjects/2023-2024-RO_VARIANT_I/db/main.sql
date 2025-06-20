CREATE DATABASE Main;
USE Main;

-- Problema 1
CREATE TABLE Cafenea(
    cod         INTEGER PRIMARY KEY AUTOINCREMENT,
    adresa      TEXT NOT NULL DEFAULT "",
    capacitate  INTEGER NOT NULL CHECK(capacitate >= 0),
    terasa      INTEGER NOT NULL DEFAULT 0 CHECK(terasa IN (0, 1)),
    wifi        INTEGER NOT NULL DEFAULT 0 CHECK (wifi IN (0, 1))
);

CREATE TABLE Preparat(
    cod         INTEGER PRIMARY KEY AUTOINCREMENT,
    denumire    TEXT NOT NULL,
    descriere   TEXT NOT NULL,
    pret        FLOAT NOT NULL CHECK(pret > 0.0)
);

CREATE TABLE Client(
    cod             INTEGER PRIMARY KEY AUTOINCREMENT,
    numarTelefon    TEXT NOT NULL UNIQUE CHECK(length(numarTelefon) = 10)
);

-- U - unique constraint for a certain relationship instance
-- Un client poate face mai multe comenzi in aceeasi zi, in aceeasi cafenea:                cod,    U_data_comanda,     cantitate,  U_cod_client,   cod_preparat,   U_cod_cafenea
-- Un client poate face mai multe comenzi in aceeasi zi, in cafenele diferite:              cod,    U_data_comanda,     cantitate,  U_cod_client,   cod_preparat,   cod_cafenea
-- Un client poate face mai multe comenzi in aceeasi cafenea, in zile diferite:             cod,    data_comanda,       cantitate,  U_cod_client,   cod_preparat,   U_cod_cafenea
-- Mai multi clienti pot face comenzi intr-o cafenea, in aceeasi zi sau in zile diferite:   cod,    data_comanda,       cantitate,  cod_client,     cod_preparat,   cod_cafenea
--
-- We need more constraints to satisfy these constraints!
-- 1. Multiple items per order:                                                                                 link table between Comanda and Preparat
-- 2. A client can make multiple orders on the same date, in multiple cafes (the same one or different one):    UNIQUE(cod_client, data_comanda, cod_cafenea)
CREATE TABLE Comanda(
    cod             INTEGER PRIMARY KEY NOT NULL,
    data_comanda    DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY cod_client REFERENCES Client(cod)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY cod_cafenea REFERENCES Cafenea(cod)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT U_Client_DataComanda_Cafenea UNIQUE(cod_client, data_comanda, cod_cafenea)
);

CREATE TABLE ComandaPreparat(
    cod_comanda INTEGER NOT NULL,
    cod_preparat INTEGER NOT NULL,
    cantitate INTEGER NOT NULL CHECK(cantitate > 0),
    FOREIGN KEY (cod_comanda) REFERENCES Comanda(cod)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (cod_preparat) REFERENCES Preparat(cod)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT PK_ComandaPreparat PRIMARY KEY (cod_comanda, cod_preparat)
);

-- Structura de mai sus este in BCNF deoarece toate dependentele sunt date exclusiv de intreaga cheie
-- Cafenea:         cod ca primary key, adresa poate fi cheie candidat deoarece nu pot exista doua cafenele la aceeasi adresa
-- Preparat:        cod ca primary key, discutabil daca denumire si descriere pot fi chei candidat, astfel incat pot exista produse cu aceeasi denumire
--                  sau aceeasi descriere, dar care sa fie insa produse diferite (cam ciudat, as pune denumire ca cheie candidat)
-- Client:          cod ca primary key, numar telefon ar trebui sa fie unic per client => cheie candidat
-- Comanda:         cod ca primary key, (cod_client, data_comanda, cod_cafenea) identifica o comanda => cheie candidat
-- ComandaPreparat: tabela de legatura, (cod_comanda, cod_preparat) cheie primara compusa

-- COMMENT THIS IF YOU WANT THE SQL TO WORK!!!
-- Problema 2
Regizori[PK_CodRegizor, Nume Tara]
Filme[PK_CodFilm, Titlu, An, Incasari, FK_CodRegizor]
Premii[PK_CodPremiu, Denumire, Instituie]
FilmePremii[PK_(CodFilm, CodPremiu, Categorie), An]

-- Join intre Regizori si Premii pe baza filmelor regizorului care au premii
-- Grupam randurile dupa Regizor.Cod si Regizor.Nume
-- Selectam doar acele tuple care au numarul distinct de Premii.Denumire = 2, facand selectia pe Premii.Denumire = 'Oscar' sau Premii.Denumire = 'Ursul de Aur'
SELECT R.Cod, R.Nume
FROM Regizori R
    INNER JOIN Filme F ON R.CodRegizor = F.CodRegizor
    INNER JOIN FilmePremii FP ON F.CodFilm = FP.CodFilm
    INNER JOIN Premii P ON FP.CodPremiu = P.CodPremiu
WHERE P.Denumire IN ('Oscar', 'Ursul de Aur')
GROUP BY R.Cod, R.Nume HAVING COUNT(DISTINCT P.Denumire) = 2;

-- PROVIDED INSTANCES
Filme
CodFilm     Titlu   An      Incasari    CodRegizor
1           t1      1990    1.10        1
2           t2      2023    1.50        2
3           t3      2020    5.90        1
4           t4      1965    2.00        1
5           t5      2000    4.50        2

FilmePremii
CodFilm     CodPremiu   Categorie   An
1           1           1           1990
1           2           3           1991
2           1           1           2023
5           1           1           2000
5           2           4           2000

Premii
CodPremiu   Denumire    Institutie
1           p1          i1
2           p2          i2

--* b1) (CodFilm, Titlu) PENTRU Filme CARE NU AU FOST PREMIATE CU TOATE PREMIILE
--*                  SI CARE AU INCASARILE MAI MARI DECAT MAXIMUL TUTUROR MEDIILOR FILMELOR GRUPATE DUPA REGIZOR
--* se grupeaza toate filmele dupa regizor si se calculeaza media incasarilor pentru filmelor acelui regizor
SELECT f.CodFilm, f.Titlu
FROM Filme f
-- filtreaza dupa filmele care nu sunt premiate in cu toate premiile
WHERE NOT EXISTS
    -- selecteaza toate codurile Premii care nu sunt asociate filmului
    (SELECT p.CodPremiu
        FROM Premii p
        EXCEPT
            SELECT DISTINCT fp.CodPremiu
            FROM FilmePremii fp
            WHERE fp.CodFilm = f.CodFilm
    )
-- filme ce au incasari > maximul AVG_INCASARI pentru filmele grupate dupa regizor
AND f.Incasari > (SELECT MAX(IncMed)
                    FROM (
                            SELECT AVG(f2.Incasari) IncMed
                            FROM Filme f2
                            GROUP BY f2.CodRegizor
                         ) t
                )

-- b) Sunt satisfacute urmatoarele dependente functionale?
-- {An} -> {CodRegizor}     ----- An:1990 -> CodRegizor{1} si An:2020 -> CodRegizor{1} =====> NU!
-- {CodRegizor} -> {Titlu}  ----- CodRegizor:1 -> Titlu:t1 si CodRegizor:1 -> Titlu:t3 =====> NU!
DROP DATABASE Main;