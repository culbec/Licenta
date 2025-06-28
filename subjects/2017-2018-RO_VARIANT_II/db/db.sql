-- 1) Chei primare si chei externe
Companii(PK_CodC, Denumire, Vechime, Tara, Continent)
Aeroporturi(PK_CodA, Nume, Oras, Tara, Continent)
Zboruri(FK_CodCompanie, FK_CodAeroportPlecare, FK_CodAeroportSosire, Data, Ora, TipAvion, NumarLocuri)

-- 2) Cel putin 3 dependente functionale care sa nu se refere la campuri ce reprezinta coduri
Companii: {Tara} -> {Continent} -- o tara poate apartine doar unui singur continent
Aeroporturi: {Tara} -> {Continent} -- o tara poate apartine doar unui singur continent
Zboruri: {TipAvion} -> {NumarLocuri} -- logic nu am putea avea acelasi avion cu locuri diferite

-- 3) Modificari esentiale pentru a ajunge in 3NF, justificati unde e cazul
a) Crearea unui tabel separat pentru stocarea tarilor - DA! -- anomalii de inserare/update/stergere, dependenta tranzitiva
b) Utilizarea unui camp DataInfiintarii in locul campului Vechime - NU! -- este good practice, dar nu e esential
c) Crearea unui tabel separat pentru stocarea tipurilor de avioane - DA! -- depedenta tranzitiva in tabela Zboruri
d) Adaugarea constrangerii de integritate CodAeroportPlecare > CodAeroportSosire - NU! -- putem avea CodAeroportPlecare < CodAeroportSosire, ar trebui sa avem CodAeroportPlecare <> CodAeroportSosire

-- 4) Interogarea SQL plecand de la algebra relationala
--* Denumirea companiilor de pe continentul Asia care au inregistrate zboruri ale caror avioane au mai mult de 200 de locuri

PI_{Denumire}(SIGMA_{Continent='Asia'}(Companii THETA_JOIN_{CodC=CodCompanie} SIGMA_{NumarLocuri>200}(Zboruri)))
SELECT DISTINCT C.Denumire
FROM Companii C
INNER JOIN Zboruri Z ON C.CodC = Z.CodCompanie
WHERE C.Continent = 'Asia' AND Z.NumarLocuri > 200;

-- 5) Interogare SQL
-- Numarul total de zboruri din si inspre fiecare aeroport (Nume, NrZboruri)
SELECT A.Nume, COUNT(*) AS NrZboruri
FROM Aeroporturi A
LEFT JOIN Zboruri Z ON A.CodA IN (Z.CodAeroportPlecare, A.CodA = Z.CodAeroportSosire)
GROUP BY A.Nume;