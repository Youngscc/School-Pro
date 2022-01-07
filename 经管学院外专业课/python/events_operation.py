import sqlite3 as sql

con = sql.connect("DEMO.db")


def add_event(user_id, book_id):  # 增加借书事件，成功返回True，否则返回False
    cur = con.cursor()
    flag = True
    cur.execute("SELECT id FROM events WHERE event_user=(?) AND event_book=(?)", (user_id, book_id))
    now_result = cur.fetchone()
    if now_result is None:
        cur.execute("INSERT INTO events(event_user, event_book) values(?, ?)", (user_id, book_id))
    else:
        print("The user has borrowed this book.")
        flag = False
    con.commit()
    cur.close()
    return flag


def remove_event(user_id, book_id):  # 删除借书事件，成功返回True，否则返回False
    cur = con.cursor()
    cur.execute("SELECT * FROM events WHERE event_user=(?) AND event_book=(?)", (user_id, book_id))
    now_result = cur.fetchone()
    if now_result is None:
        print("The user didn't borrow this book!")
    else:
        cur.execute("DELETE FROM events WHERE id=?", (now_result[0],))
    con.commit()
    cur.close()
    return now_result


def get_event_by_user(user_id):  # 查询所有用户ID为 user_id 的借书事件并返回
    cur = con.cursor()
    cur.execute("SELECT * FROM events WHERE event_user=(?)", (user_id,))
    now_result = cur.fetchall()
    con.commit()
    cur.close()
    return now_result


def check(user_id, book_id):  # 查询所有用户ID为user_id且书ID为book_id的借书事件
    cur = con.cursor()
    cur.execute("SELECT * FROM events WHERE event_user=(?) AND event_book=(?)", (user_id, book_id))
    now_result = cur.fetchone()
    con.commit()
    cur.close()
    return now_result

# add_user("Youngsc")
# add_user("Adsdsd")
# remove_user(2)
# borrow_book(1, 1)
# borrow_book(1, -1)
# maintain_user(1,"Cccpql")
