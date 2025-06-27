-- 1) Chei primare si Chei externe
Pacienti(PK_CodP, Nume, Prenume, Varsta, DataNasterii);
Proceduri(PK_CodProc, Nume, Descriere, Pret)
FisePacienti(FK_CodPacient, FK_CodProcedura, Data, NumeDoctor, PrenumeDoctor, SpecializareDoctor, VechimeDoctor)
    PRIMARY KEY(FK_CodPacient, FK_CodProcedura, Data) -- un pacient nu poate sa aiba aceeasi procedura de mai multe ori la aceeasi data

-- 2) 3 dependente functionale care nu tin de chei
{DataNasterii} -> {Varsta}  -- daca stim data nasterii, stim si varsta
{Nume} -> {Descriere, Pret} -- presupunand ca numele este unic pentru fiecare procedura
{NumeDoctor, PrenumeDoctor} -> {SpecializareDoctor, VechimeDoctor} -- daca stim numele si prenumele doctorului (fiind unice), cu siguranta stim specializarea si vechimea sa

-- 3) Modificari esentiale pentru a aduce structura bazei de date in 3NF
a) Createa unui tabel pentru stocarea doctorilor - DA! -- avem redundante in cazul procedurilor aceluiasi doctor, vor aparea toate datele doctorului
b) Adaugarea constrangerii de integritate Varsta = data curenta - DataNasterii in tabelul Pacienti - DA!
c) Eliminarea campului Varsta din tabelul Pacienti - DA! -- este un atribut derivat care nu isi are locul, poate introduce anomalii
d) Createa unui tabel separat pentru stocarea varstei pacientilor - NU! -- se poate determina din data nasterii
e) Adaugarea constrangerii de integritate Data < data curenta in tabelul FisePacienti - NU! -- putem avea o interventie care are loc la data curenta, corect ar fi <=

-- 4) Interogare SQL bazata pe algebra relationala

PI_{Nume, Prenume} (SIGMA_{SpecializareDoctor = 'radiologie'}(FisePacienti) THETA_JOIN_{CodPacient = CodP} Pacienti)
SELECT DISTINCT Nume, Prenume
FROM Pacienti
INNER JOIN FisePacienti ON FisePacienti.CodPacient = Pacienti.CodP
WHERE FisePacienti.SpecializareDoctor = 'radiologie';

PI_{Nume, Prenume} (SIGMA_{SpecializareDoctor = 'cardiologie'}(FisePacienti) THETA_JOIN_{CodPacient = CodP} Pacienti)
SELECT DISTINCT Nume, Prenume
FROM Pacienti
INNER JOIN FisePacienti ON FisePacienti.CodPacient = Pacienti.CodP
WHERE FisePacienti.SpecializareDoctor = 'cardiologie';

-- 5) Integorage SQL care returneaza SPECIALIZARILE CARE AU INCASAT CEI MAI MULTI BANI DIN PROCEDURI, NUMELE SPECIALIZARII, NUMARUL DE PROCEDURI SI SUMA INCASATA
-- in format (Specializare, NrProceduri, Suma)

SELECT FP.SpecializareDoctor AS Specializare, COUNT(*) AS NrProceduri, SUM(P.Pret) AS Suma
FROM FisePacienti FP
INNER JOIN Proceduri PR ON FP.CodProcedura = PR.CodProc
INNER JOIN Pacienti PA FP.CodPacient = PA.CodP
GROUP BY S.SpecializareDoctor HAVING SUM(P.Pret) = (
    SELECT MAX(SumaTotala)
    FROM (
        SELECT SUM(PR2.Pret) AS SumaTotala
        FROM FisePacienti FP2
        INNER JOIN Proceduri PR2 ON FP2.CodProcedura = PR2.CodProc
        GROUP BY FP2.SpecializareDoctor
    ) AS QueryMaxSumaTotala
);
