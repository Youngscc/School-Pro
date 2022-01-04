import sqlite3 as sql

con = sql.connect("DEMO.db")


def add_user(user_name, user_password):  # 增加新用户，用户名为user_name，用户密码为user_password
    cur = con.cursor()
    cur.execute("INSERT INTO users(name, password) values(?, ?)", (user_name, user_password))
    cur.execute("SELECT Max(id) FROM users WHERE users.name=(?)", (user_name,))
    user_id = cur.fetchone()[0]
    con.commit()
    cur.close()
    return user_id


def remove_user(user_id):  # 移除用户ID为user_id的用户
    cur = con.cursor()
    cur.execute("SELECT * FROM users WHERE users.id=(?) ", (user_id,))
    now_result = cur.fetchone()
    if now_result is None:
        print("No such users!")
    else:
        cur.execute("DELETE FROM users WHERE id=?", (user_id,))
    con.commit()
    cur.close()
    return now_result


def borrow_book(user_id, want_borrow):  # 将用户ID为user_id的用户借书数量改变want_borrow，want_borrow可正可负
    print()
    cur = con.cursor()
    cur.execute("SELECT book_number FROM users WHERE users.id=(?) ", (user_id,))
    now_result = cur.fetchone()
    now_borrow = now_result[0]
    flag = True
    if now_borrow + want_borrow < 0:
        print("He (or she) didn't borrow any book.")
        flag = False
    else:
        cur.execute("UPDATE users SET book_number=? WHERE id=?", (now_borrow + want_borrow, user_id))
    con.commit()
    cur.close()
    return flag


def maintain_user(user_id, maintain_opt, maintain_text): # 修改用户ID为user_id的用户的某些信息
    cur = con.cursor()
    flag = True
    cur.execute("SELECT * FROM users WHERE users.id=(?) ", (user_id,))
    now_result = cur.fetchone()
    if now_result is None:
        print("There is no such user.")
    else:
        if maintain_opt == 1:
            cur.execute("UPDATE users SET name=? WHERE id=?", (maintain_text, user_id))
        elif maintain_opt == 2:
            cur.execute("UPDATE users SET password=? WHERE id=?", (maintain_text, user_id))
        else:
            print("The key input is wrong.")
    con.commit()
    cur.close()
    return now_result


def check_user(user_id):  # 返回用户ID为user_id的用户
    cur = con.cursor()
    cur.execute("SELECT * FROM users WHERE users.id=(?) ", (user_id,))
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
