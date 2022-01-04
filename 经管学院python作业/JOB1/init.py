import sqlite3 as sql

con = sql.connect("DEMO.db")
cur = con.cursor()
cur.execute("DROP TABLE IF EXISTS Users;")
cur.execute("DROP TABLE IF EXISTS Books;")
cur.execute("DROP TABLE IF EXISTS Events;")
cur.execute("DROP TABLE IF EXISTS Categories;")
con.commit()
sql = "CREATE TABLE Users(" \
      "id integer PRIMARY KEY AUTOINCREMENT," \
      "name text NOT NULL, " \
      "password text NOT NULL, " \
      "is_admin integer NOT NULL DEFAULT 0, " \
      "book_number integer DEFAULT 0" \
      ");"
cur.execute(sql)

sql = "CREATE TABLE Categories (" \
      "id integer PRIMARY KEY AUTOINCREMENT, " \
      "name text NOT NULL UNIQUE, " \
      "book_number integer DEFAULT 0" \
      ");"
cur.execute(sql)
sql = "CREATE TABLE Books(" \
      "id integer PRIMARY KEY AUTOINCREMENT," \
      "name text NOT NULL, " \
      "borrowed_num integer NOT NULL DEFAULT 0," \
      "rest_num integer NOT NULL DEFAULT 0," \
      "describe text," \
      "category text NOT NULL, CONSTRAINT fk_book_category FOREIGN KEY (category) REFERENCES Categories(name)" \
      ");"
cur.execute(sql)
sql = "CREATE TABLE Events(" \
      "id integer PRIMARY KEY AUTOINCREMENT, " \
      "event_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, " \
      "event_user integer NOT NULL, " \
      "event_book integer NOT NULL, " \
      "CONSTRAINT fk_event_user FOREIGN KEY (event_user) REFERENCES Users(id), " \
      "CONSTRAINT fk_event_book FOREIGN KEY (event_book) REFERENCES Books(id)" \
      ");"
cur.execute(sql)
cur.execute("INSERT INTO users(name, password, is_admin) values('Administer', 'administer', 1)")
cur.execute("INSERT INTO categories(name) values('No Category')")
cur.close()
con.commit()
con.close()
