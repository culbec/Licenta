CREATE TABLE Locatii(
    CodLocatie INTEGER PRIMARY KEY IDENTITY,
    Denumire TEXT NOT NULL,
    Adresa TEXT NOT NULL UNIQUE
);

CREATE TABLE Genuri(
    CodGen INTEGER PRIMARY KEY IDENTITY,
    Denumire TEXT NOT NULL,
    Descriere TEXT NOT NULL,
);

CREATE TABLE Actori(
    CodActor INTEGER PRIMARY KEY IDENTITY,
    Nume TEXT NOT NULL
);

CREATE TABLE Filme(
    Titlu TEXT PRIMARY KEY,
    An INTEGER NOT NULL CHECK(An > 1700)
);

CREATE TABLE FilmeGenuri(
    TitluFilm TEXT NOT NULL,
    CodGen INTEGER NOT NULL,
    FOREIGN KEY FK_TitluFilm(TitluFilm) REFERENCES Filme(TitluFilm)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY FK_CodGen(CodGen) REFERENCES Genuri(CodGen)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT PK_FilmeGenuri PRIMARY KEY(TitluFilm, CodGen)
);

CREATE TABLE FilmeActori(
    TitluFilm TEXT NOT NULL,
    CodActor INTEGER NOT NULL,
    FOREIGN KEY FK_TitluFilm(TitluFilm) REFERENCES Filme(TitluFilm)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY FK_CodActor(CodActor) REFERENCES Actori(CodActor)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT PK_FilmeGenuri PRIMARY KEY(TitluFilm, CodActor)
);

CREATE TABLE Proiectii(
    CodProiectie INTEGER NOT NULL IDENTITY,
    CodLocatie INTEGER NOT NULL,
    TitluFilm TEXT NOT NULL,
    Data DATE NOT NULL DEFAULT CURRENT_DATE,
    Ora TIME NOT NULL DEFAULT CURRENT_TIME,
    FOREIGN KEY FK_CodLocatie(CodLocatie) REFERENCES Locatii(CodLocatie)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY FK_TitluFilm(TitluFilm) REFERENCES Filme(TitluFilm)
        ON DELETE CASCADE
        ON UPDATE CASCADE
    CONSTRAINT PK_Proiectii(CodProiectie, CodLocatie, TitluFilm)
);

SELECT L.Denumire, L.Adresa
FROM Locatii L
INNER JOIN Proiectii P ON L.CodLocatie = P.CodLocatie
INNER JOIN FilmeGenuri FG ON P.TitluFilm = FG.TitluFilm
INNER JOIN Genuri G ON FG.CodGen = G.CodGen
INTERSECT
(
    SELECT L2.Denumire, L2.Adresa
    FROM Locatii L2
    INNER JOIN Proiectii P2 ON L2.CodLocatie = P2.CodLocatie
    INNER JOIN FilmeGenuri FG2 ON P2.TitluFilm = FG2.TitluFilm
    INNER JOIN Genuri G2 ON FG2.CodGen = G2.CodGen
    WHERE G2.Denumire = 'comedie'
)
INTERSECT
(
    SELECT L3.Denumire, L3.Adresa
    FROM Locatii L3
    INNER JOIN Proiectii P3 ON L3.CodLocatie = P3.CodLocatie
    INNER JOIN FilmeGenuri FG3 ON P3.TitluFilm = FG3.TitluFilm
    INNER JOIN Genuri G3 ON FG3.CodGen = G3.CodGen
    WHERE G3.Denumire = 'drama'
);

SELECT L.Denumire, L.Adresa
FROM Locatii L
INNER JOIN Proiectii P ON L.CodLocatie = P.CodLocatie
INNER JOIN FilmeGenuri FG ON P.TitluFilm = FG.TitluFilm
INNER JOIN Genuri G ON FG.CodGen = G.CodGen
WHERE G.Denumire IN ('comedie', 'drama')
GROUP BY L.Denumire, L.Adresa
HAVING COUNT(DISTINCT G.Denumire) = 2;

SELECT COUNT(*) AS NrBilete
FROM Proiectii P
INNER JOIN FilmeActori FA ON P.TitluFilm = FA.TitluFilm
INNER JOIN Actori A ON FA.CodActor = A.CodActor
INNER JOIN Locatii L ON P.CodLocatie = L.CodLocatie
WHERE L.Adresa = 'Piata Unirii' AND A.Nume = 'Alain Delon'
GROUP BY P.TitluFilm;

SELECT F.Titlu, F.An
FROM Filme F
INNER JOIN Proiectii P ON F.Titlu = P.TitluFilm
GROUP BY F.Titlu, F.An
HAVING COUNT(*) = (
    SELECT MAX(COUNT(*))
    FROM Filme F
    INNER JOIN Proiectii P ON F.Titlu = P.TitluFilm
    GROUP BY F.Titlu, F.An
);