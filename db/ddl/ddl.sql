CREATE DATABASE DDL;
USE DDL;

-- Users table
CREATE TABLE Users(
    user_id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT CK_password CHECK(length(password) > 8)
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

-- Adding a phone attribute to Users
ALTER TABLE Users ADD COLUMN phone TEXT;

-- Renaming email to email_address in Users
ALTER TABLE Users RENAME COLUMN email TO email_address;

-- Renaming Users to AppUsers
ALTER TABLE Users RENAME TO AppUsers;

-- Dropping password from Users
ALTER TABLE Users DROP COLUMN password;

-- Dropping the Users table (with safe check)
DROP TABLE IF EXISTS AppUsers;

-- Dropping the database
DROP DATABASE DDL;