-- +++ - PK
-- --- - CANDIDATE
-- === - FK

-- 1) BCNF
Paricipanti(CodP, Nume, Email, Tara)
            ++++  ----  -----
    -- putem zice ca un participant nu poate folosi acelasi email, insa am avea nevoie si de un alt
    -- field pentru a ne asigura de asta, am folosit Nume
    -- (Nume, Email) UNIQUE

Plaje(CodPJ, Nume, Descriere, Localitate)
      +++++  ----             ----------
    -- dorim sa nu exite mai multe plaje cu acelasi nume in aceeasi localitate
    -- (Nume, Localitate) UNIQUE

Competitii(CodC, Denumire, DataProgramare, OraInceput, OraSfarsit, CodPJ)
           ++++            --------------  ----------  ----------  =====
                                                                   -----
    -- presupunem ca o plaja poate sustine doar o singura competitie la un moment dat

Scoici(CodS, Denumire, Descriere)
       ++++  --------
    -- nu am putea avea aceeasi scoica cu alta descriere

ParticipantiCompetitiiScoici(CodP, CodC, CodS, NrScoici)
                             ====  ====  ====
                             ++++  ++++  ++++
    -- un participant poate culege in cadrul unei competitii
    -- mai multe tipuri de scoici, insa nu pot aparea cu nr diferit

-- 2) Interogari

Grupe[CodGrupa, NumeGrupa, NrSala]
      ++++++++
Parinti[CodParinte, NumeParinte, Adresa, NrTelefon]
        ++++++++++
Copii[CodCopil, NumeCopil, CodParinte, DataNasterii, CodGrupa]
      ++++++++             ==========                ========
PlatiTaxe[CodPlata, CodCopil, DataPlatii, SumaPlatita]
          ++++++++  ========

-- a) Pentru fiecare grupa la care S-A PLATIT CEL PUTIN O TAXA: cod, nume si valoarea totala a taxelor platite pentru copiii din grupa
SELECT G.CodGrupa, G.NumeGrupa, SUM(PT.SumaPlatita) AS SumaTotala
FROM Grupe G
INNER JOIN Copii C ON G.CodGrupa = C.CodGrupa
INNER JOIN PlatiTaxe PT ON C.CodCopil = PT.CodCopil
GROUP BY (G.CodGrupa, G.NumeGrupa);

-- b) Instantele urmatoare:
Grupe                                                               Parinti
CodGrupa        NumeGrupa       NrSala                              CodParinte          NumeParinte         Adresa          NrTelefon
1               Buburuze        1                                   1                   P1                  A1              1111111111
2               Veverite        5                                   2                   P2                  A2              2222222222
3               Albinute        8                                   3                   P3                  A3              3333333333

Copii
CodCopil        NumeCopil       CodParinte      DataNasterii        CodGrupa
1               C1              1               2018.02.12          1
2               C2              2               2018.06.25          1
3               C3              2               2018.06.25          1
4               C4              3               2018.06.30          1
5               C5              1               2020.04.15          2
6               C6              1               2022.06.05          3

-- b1) Rezultatul urmatorului query
-- Selecteaza (NumeParinte, Adresa) ale parintilor care au copii in grupa Buburuze
-- si care au copii intr-o singura grupa (doar in Buburuze)
-- Selecteaza (NumeParinte, Adresa) ale parintilor care au copii+ doar in grupa Buburuze
SELECT p.NumeParinte, p.Adresa
FROM Parinti p
    INNER JOIN Copii c ON p.CodParinte = c.CodParinte
WHERE c.CodGrupa = (SELECT g.CodGrupa -- copiii care sunt in grupa Buburuze
                    FROM Grupe g
                    WHERE g.NumeGrupa = 'Buburuze')
INTERSECT
SELECT p.NumeParinte, p.Adresa
FROM Parinti p
    INNER JOIN Copii c ON p.CodParinte = c.CodParinte
GROUP BY p.CodParinte, p.NumeParinte, p.Adresa
HAVING COUNT(DISTINCT c.CodGrupa) = 1

NumeParinte         Adresa
P2                  A2
P3                  A3

-- b2) Explicati daca urmatoarele dependente functionale sunt respectate de instantele de mai sus
{CodCopil} -> {CodParinte} ===> DA! -- avem coduri copil unice, se va respecta oricum
{CodParinte} -> {CodGrupa} ===> NU! -- un parinte poate avea un copil in mai multe grupe, cum se poate vedea pt CodCopil=1 si CodCopil=5