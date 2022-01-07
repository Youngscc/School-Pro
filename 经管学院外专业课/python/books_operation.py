import sqlite3 as sql

con = sql.connect("DEMO.db")


def add_book(book_name, book_num, book_describe, book_category):  # 添加图书
    cur = con.cursor()
    cur.execute("SELECT id FROM books WHERE books.name=(?) AND books.describe=(?) AND books.category=(?)",
                (book_name, book_describe, book_category))
    now_result = cur.fetchone()
    if now_result is None:
        cur.execute("INSERT INTO books(name, rest_num, describe, category) values(?,?,?,?)",
                    (book_name, book_num, book_describe, book_category))
    else:
        now_id = now_result[0]
        cur.execute("SELECT rest_num FROM books WHERE books.id=(?)", (now_id,))
        now_sum = cur.fetchone()[0]
        cur.execute("UPDATE books SET rest_num=? WHERE id=?", (book_num + now_sum, now_id))
    cur.execute("SELECT id FROM books WHERE books.name=(?) AND books.describe=(?) AND books.category=(?)",
                (book_name, book_describe, book_category))
    book_id = cur.fetchone()[0]
    con.commit()
    cur.close()
    return book_id


def remove_book(book_id, want_del):  # 删除图书一定数量，若该图书的借阅量和库存量总和为0，则将其从数据库中删除
    cur = con.cursor()
    cur.execute("SELECT * FROM books WHERE books.id=(?) ", (book_id,))
    now_result = cur.fetchone()
    if now_result is None:
        print("No such books!")
    elif now_result[3] < want_del:
        print("The rest numbers of the books isn't enough.")
        now_result = None
    elif now_result[3] > want_del or (now_result[3] == want_del and now_result[2] > 0):
        cur.execute("UPDATE books SET rest_num=? WHERE id=?", (now_result[3] - want_del, book_id))
        print("Remove the books successfully!")
        now_result = None
    else:
        cur.execute("DELETE FROM books WHERE id=?", (book_id,))
    con.commit()
    cur.close()
    return now_result


def borrow_book(book_id, want_borrow):  # 增加图书借阅量，减少图书库存量
    cur = con.cursor()
    cur.execute("SELECT rest_num, borrowed_num FROM books WHERE books.id=(?) ", (book_id,))
    now_result = cur.fetchone()
    now_rest = now_result[0]
    now_borrow = now_result[1]
    flag = True
    if want_borrow > 0:
        if now_rest >= want_borrow:
            cur.execute("UPDATE books SET rest_num=?, borrowed_num=? WHERE id=?",
                        (now_rest - want_borrow, now_borrow + want_borrow, book_id))
        else:
            print("The rest the book is not enough!")
            flag = False
    if want_borrow < 0:
        if now_borrow >= -want_borrow:
            cur.execute("UPDATE books SET rest_num=?, borrowed_num=? WHERE id=?",
                        (now_rest - want_borrow, now_borrow + want_borrow, book_id))
        else:
            print("The number of books returned is wrong!")
            flag = False
    con.commit()
    cur.close()
    return flag


def maintain_book(book_id, maintain_opt, maintain_text):  # 修改图书部分信息
    cur = con.cursor()
    cur.execute("SELECT * FROM books WHERE id=(?) ", (book_id,))
    now_result = cur.fetchone()
    if now_result is None:
        print("There is no such book.")
    else:
        if maintain_opt == 1:
            cur.execute("UPDATE books SET name=? WHERE id=?", (maintain_text, book_id))
        elif maintain_opt == 2:
            cur.execute("UPDATE books SET category=? WHERE id=?", (maintain_text, book_id))
        elif maintain_opt == 3:
            cur.execute("UPDATE books SET describe=? WHERE id=?", (maintain_text, book_id))
        else:
            print("The key input is wrong.")
    con.commit()
    cur.close()
    return now_result


def search_book(book_id):  # 返回图书ID为book_id的书
    cur = con.cursor()
    cur.execute("SELECT * FROM books WHERE books.id=(?) ", (book_id,))
    now_result = cur.fetchone()
    con.commit()
    cur.close()
    return now_result


def get_cate(cate_name):  # 返回类目为cate_name的所有书
    cur = con.cursor()
    cur.execute("SELECT * FROM books WHERE category=(?) ", (cate_name,))
    now_result = cur.fetchall()
    con.commit()
    cur.close()
    return now_result
