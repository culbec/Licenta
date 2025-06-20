CREATE DATABASE Main;
USE Main;

-- Problema 1
CREATE TABLE Competitor(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    last_name TEXT NOT NULL,
    first_name TEXT NOT NULL,
    date_of_birth DATETIME NOT NULL
);

CREATE TABLE Event(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    event_name TEXT NOT NULL,
    event_description TEXT NOT NULL,
    event_date DATE NOT NULL
);

CREATE TABLE CompetitorEvents(
    id_participation INTEGER PRIMARY KEY AUTOINCREMENT,
    id_competitor INTEGER NOT NULL,
    id_event INTEGER NOT NULL,
    FOREIGN KEY (id_competitor) REFERENCES Competitor(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_event) REFERENCES Event(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT U_IdCompetitor_IdEvent UNIQUE (id_competitor, id_event)
);

CREATE TABLE Judge(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    last_name TEXT NOT NULL,
    first_name TEXT NOT NULL
);

CREATE TABLE JudgeEvaluations(
    id_jugde INTEGER NOT NULL,
    id_participantion INTEGER NOT NULL,
    score INTEGER NOT NULL CHECK(score >= 1 AND score <= 10),
    FOREIGN KEY (id_jugde) REFERENCES Judge(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_participation) REFERENCES CompetitorEvents(id_participantion),
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT PK_JudgeEvaluations PRIMARY KEY (id_jugde, id_participantion)
);

-- Problema 2
-- a)
Newspapers[PK_NewspaperID, NewspaperName]
Journalists[PK_JournalistID, LastName, FirstName, FK_NewspaperID]
Categories[PK_CategoryID, Name]
Articles[PK_ArticleID, Title, PublicationDate, Text, FK_JournalistID, FK_CategoryID]

SELECT COUNT(*) AS No_Articles
FROM Articles A
    INNER JOIN Categories C ON A.CategoryID = C.CategoryID
    INNER JOIN Journalists J ON A.JournalistID = J.JournalistID
    INNER JOIN Newspaper N ON J.NewspaperID = N.NewspaperID
WHERE C.Name = 'Economics' AND N.NewspaperName = 'Universe';

-- b) Consider the following instances
Categories
CategoryID      Name
1               c1
2               c2
3               c3

Articles
ArticleID       Title       PublicationDate     Text        JournalistID        CategoryID
1               a1          1-1-2022            t1          1                   2
2               a2          1-2-2022            t2          2                   3
3               a3          1-1-2022            t3          3                   1
4               a4          1-5-2022            t4          1                   2
5               a5          1-3-2022            t5          2                   1
7               a7          1-7-2022            t7          2                   2
8               a8          1-5-2022            t8          4                   2

-- b1)
-- Selects the Journalist ID and the number of articles they've written
-- for articles in category 'c2' and for which the number of written articles is greater than 2
SELECT A.JournalistID, COUNT(*) No
FROM Articles A
    -- extracts the categories of the articles
    INNER JOIN Categories C ON A.CategoryID = C.CategoryID
-- extracts only the categories with name 'c2'
WHERE C.Name = 'c2'
-- groups the articles that have the category 'c2' by the journalist ID
GROUP BY A.JournalistID
-- selects only those articles for which their journalists have written more than 2 articles
HAVING 2 < (SELECT COUNT(*)
    FROM Articles A2
    WHERE A2.JournalistID = A.JournalistID
)

-- b2)
-- {JournalistID} -> {Title}    ----- not respected, as a Journalist, for instance with ID 1, has articles with different titles, for instance a1 and a4
-- {ArticleID}  -> {Text}       ----- is respected!

DROP DATABASE Main;