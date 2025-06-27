-- 1) Chei primare si chei externe
Echipe(PK_CodE, Tara, Continent)
Jucatori(PK_CodJ, FK_CodEchipa, Nume, Varsta, NumarMeciuri)
Meciuri(FK_CodEchipa1, GoluriEchipa1, FK_CodEchipa2, GoluriEchipa2, Data, Stadion, NumarLocuri, Oras, Tara)

-- 2) Dependente functionale
{Tara} -> {Continent} -- o tara nu poate face parte din mai multe continente
{Oras, Tara, Stadion} -> {NumarLocuri} -- nu are sens ca acelasi nume de stadion sa apara in mai multe orase din aceeasi tara
{Stadion, Oras} -> {NumarLocuri}
{Oras, Tara} -> {Continent}

-- 3) 3NF
a) Crearea unui tabel separat pentru stocarea tarilor - Da! -- avem {Tara} -> {Continent}
b) Utilizarea unui camp DataNasterii in loc de Varsta - Nu! -- nu este esential
c) Crearea unui tabel pentru stocarea stadioanelor - Da! -- anomalii de inserare, modificare, stergere
d) Adaugarea constrangerii de integritate CodEchipa1 > CodEchipa2 - Nu! -- ar trebui CodEchipa1 <> CodEchipa2

-- 4) Interogarea SQL
-- Numele jucatorilor care joaca la echipe de pe continentul Asia si care au mai mult de 100 de meciuri jucate
PI_{Nume}(SIGMA_{Continent = 'Asia'}(Echipe THETA_JOIN_{CodE = CodEchipa} SIGMA_{NumarMeciuri>100}(Jucatori)))
SELECT DISTINCT J.Nume
FROM Jucatori J
INNER JOIN Echipe E ON J.CodEchipa = E.CodE
WHERE E.Continent='Asia' AND J.NumarMeciuri > 100;

-- 5)
SELECT E.Tara, COUNT(*) AS NrMeciuri
FROM Echipe E
INNER JOIN Meciuri M ON E.CodE = M.CodEchipa1 OR E.CodE = M.CodEchipa2
GROUP BY E.CodE;