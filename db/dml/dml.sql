CREATE DATABASE DML;
USE DML;

-- Users table
CREATE TABLE Users(
    user_id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT NOT NULL UNIQUE,
    password_ TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT CK_password CHECK(length(password_) > 2)
);

-- Orders table
CREATE TABLE Orders(
    order_id INTEGER PRIMARY KEY AUTOINCREMENT,
    product_name TEXT NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    status TEXT DEFAULT 'pending',
);

-- UserOrders table
CREATE TABLE UserOrders(
    user_id INTEGER NOT NULL,
    order_id INTEGER NOT NULL,
    assigned_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (user_id, order_id),
    FOREIGN KEY FK_Users(user_id) REFERENCES Users(user_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY FK_Orders(order_id) REFERENCES Orders(order_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Inserting an entry to the table (only non_default required, default are optional)
INSERT INTO Users(username, email, password_)
VALUES
    ('user1', 'user1@mail.com', '1234'),
    ('user2', 'user2@mail.com', 'securepass');

-- Selecting all instances of Users
SELECT *
FROM Users;

-- Selecting instances of Users which have a certain username length
SELECT *
FROM Users
WHERE length(username) > 4;

-- Full DML language example
SELECT DISTINCT TOP 10
    u.username,
    u.email,
    COUNT(o.order_id) AS total_orders,
    SUM(o.quantity) AS total_quantity,
    AVG(o.quantity) AS avg_quantity,
    MIN(o.order_date) AS first_order,
    MAX(o.order_date) AS last_order
FROM Users u
-- joins
INNER JOIN UserOrders uo ON u.user_id = uo.user_id
LEFT JOIN Orders o ON uo.order_id = o.order_id
WHERE u.user_id IN ( -- intercalated query
    SELECT user_id
    FROM UserOrders
    WHERE order_id BETWEEN 100 AND 200
)
AND EXISTS ( -- intercalated query
    SELECT 1 FROM Orders o2
    WHERE o2.user_id = u.user_id
      AND o2.status LIKE 'shipped%'
)
-- group by and condition with aggregated func
GROUP BY u.user_id, u.username, u.email
HAVING SUM(o.quantity) > ALL ( -- the condition should be respected for all instances returned by this intercalated select
    SELECT SUM(quantity)
    FROM Orders
    WHERE status = 'cancelled'
    GROUP BY user_id
)
ORDER BY total_orders DESC;

-- Set operations
SELECT user_id FROM UserOrders
INTERSECT
(
    SELECT user_id FROM Users
    WHERE created_at >= CURRENT_DATE - INTERVAL '7 days'
)
EXCEPT
(
    SELECT user_id FROM Users
    WHERE email LIKE '%test%'
)
UNION
(
    SELECT user_id from UserOrders
);

DROP DATABASE DML;