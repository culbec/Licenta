-- +++ --- PK
-- --- --- CANDIDATE KEY
-- === --- FK

-- a)
Specializari(CodS, Denumire)
             ++++

Comisii(CodC, CodS, DenumireComisie)
        ++++  ====

Profesori(CodP, NumeProfesor)
          ++++

CuvinteCheie(CodCC, Denumire)
             +++++  --------

Studenti(CodST, TitluLucrare, CodP)
         +++++  ------------  ====

StudentiCuvinteCheie(CodST, CodCC)
                     +++++  +++++

StudentiComisii(CodST, CodC, NotaFinala)
                +++++  ++++

-- b)

-- i) Lista comisiilor (denumire si specializare) care au evaluat cel putin o lucrare cu tematica 'data mining' si cel putin una cu tematica
-- 'cloud computing'

SELECT C.DenumireComisie, S.Denumire
FROM Comisii C
    INNER JOIN Specializari S ON C.CodS = S.CodS
    INNER JOIN StudentiComisii SC ON C.CodC = SC.CodC
    INNER JOIN StudentiCuvinteCheie SCC ON SC.CodST = SCC.CodST
    INNER JOIN CuvinteCheie CC ON SCC.CodCC = CC.CodCC
WHERE CC.Denumire IN ('data mining', 'cloud computing')
GROUP BY C.DenumireComisie, S.Denumire
    HAVING COUNT(DISTINCT(CC.Denumire)) = 2;

-- ii) Numarul studentilor coordonati de profesorul Ion Popescu si care au primit nota de trecere (>=6) din partea
-- comisiilor de la Informatica Engleza

SELECT COUNT(DISTINCT ST.CodST) AS NrStudentiPromovati
FROM Studenti ST
    INNER JOIN StudentiComisii SC ON ST.CodST = SC.CodST
    INNER JOIN Profesori P ON ST.CodP = P.CodP
    INNER JOIN Comisii C ON SC.CodC = C.CodC
    INNER JOIN Specializari S ON C.CodC = S.CodS
WHERE P.NumeProfesor = 'Ion Popescu'
    AND SC.NotaFinala >= 6
    AND S.Denumire = 'Informatica Engleza'
-- putem renunta la acest group by daca vrem sa consideram Ion Popescu ca un nume general
-- adica lasam ca profesorii sa aiba acelasi nume, dar nu consideram ca sunt distincti, ci cautam un total general
GROUP BY P.CodP;

-- iii) Lista profesorilor (cod si nume) cu cel mai mare numare studenti cu note peste 8.

SELECT P.CodP, P.NumeProfesor
FROM Profesori P
    INNER JOIN Studenti ST ON P.CodP = ST.CodP
    INNER JOIN StudentiComisii SC ON ST.CodST = SC.CodST
WHERE SC.NotaFinala > 8
GROUP BY P.CodP, P.NumeProfesor
    HAVING COUNT(DISTINCT ST.CodST) = (
        SELECT MAX(NumarStudenti)
        FROM (
            SELECT COUNT(DISTINCT ST2.CodST) AS NumarStudenti
            FROM Profesori P2
                INNER JOIN StudentiComisii SC2 ON ST2.CodST = SC2.CodST
            WHERE SC2.NotaFinala > 8
            GROUP BY ST2.CodP
        ) AS Statistici
    );