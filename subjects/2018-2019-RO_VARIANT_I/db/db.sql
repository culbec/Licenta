-- 1) Chei candidat si chei externe
Persoane(PK_CodP, Nume, CNP, CodLocalitate, CodJudet, CodRegiune, Votat)
    Candidat(CNP)
Voturi(PK_CodV, Data, Ora)
    Candidat(Data, Ora)
Raspunsuri(FK_CodV, FK_CodI, RaspunsDa, RaspunsNu, Anulat)
    PRIMARY KEY(FK_CodV, FK_CodI)
Intrebari(PK_CodI, Text, NumeCategorie, DescriereCategorie)

-- 2) Dependente functionale
{NumeCategorie} -> {DescriereCategorie}
{CodLocalitate} -> {CodJudet, CodRegiune}
{CodRegiune, CodLocalitate} -> {CodJudet}
{RaspunsDa, RaspunsNu} -> {Anulat}

-- 3) Modificari esentiale pentru a ajunge in 3NF
a) Crearea unui tabel separat pentru stocarea categoriilor - DA! -- putem avea anomalii de inserare/modificare deoarece pentru o anumita categorie trebuie sa stim si descrierea, dependenta tranzitiva {NumeCategorie} -> {DescriereCategorie}
b) Eliminarea campului Anulat din tabelul Raspunsuri - DA! -- reprezinta un camp derivat, il putem determina din RaspunsDa si RaspunsNu, insa nu este esential
c) Utilizarea in tabelul Voturi a unui singur camp care sa memoreze atat data cat si ora la care s-a realizat votarea - NU!
d) Adaugarea unui camp CodP in tabelul voturi care sa refere inregistrari ale tabelului Persoane - DA! -- nu avem asocieri Voturi Persoane

-- 4) Interogare SQL din algebra relationala
-- selecteaza Textul intrebarii si Ora votului pentru voturile cu raspuns la intrebarile cu NumeCategorie 'UE'
PI_{Text, Ora}(SIGMA_{Ora > 18:00}(Voturi THETA_JOIN_{Voturi.CodV=Raspunsuri.CodV} Raspunsuri THETA_JOIN_{Intrebari.CodI=Raspunsuri.CodI} SIGMA_{NumeCategorie='UE'}(Intrebari)))
SELECT DISTINCT I.Text, V.Ora
FROM Voturi V
INNER JOIN Raspunsuri R ON V.CodV = R.CodV
INNER JOIN Intrebari I ON R.CodI = I.CodI
WHERE V.Ora > '18:00' AND I.NumeCategorie = 'UE';

-- 5) Interogare SQL pe structura data care returneaza:
-- Numar total de raspunsuri, numarul total de raspunsuri Da valide, numarul total de raspunsuri Nu valide si numarul total de raspunsuri anulate (Text, NrRaspunsurui, NrDa, NrNu, NrAnulate)
SELECT I.Text, COUNT(*) AS NrRaspunsuri,
    (
        SELECT COUNT(*)
        FROM Raspunsuri R2
        INNER JOIN Raspunsuri R2 ON I.CodI = R2.CodI
        WHERE R2.RaspunsDa = 1 AND R2.RaspunsNu = 0
    ) AS NrDa, 
    (
        SELECT COUNT(*)
        FROM Raspunsuri R3
        INNER JOIN Raspunsuri R3 ON I.CodI = R3.CodI
        WHERE R3.RaspunsDa = 0 AND R3.RaspunsNu = 1
    ) AS NrNu,
    (
        SELECT COUNT(*)
        FROM Raspunsuri R4
        INNER JOIN Raspunsuri R ON I.CodI = R4.CodI
        WHERE R4.RaspunsDa = R4.RaspunsNu OR R4.Anulat = 1
    ) AS NrAnulate,
FROM Intrebari I
INNER JOIN Raspunsuri R ON I.CodI = R.CodI
GROUP BY I.Text;
