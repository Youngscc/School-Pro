import sqlite3 as sql

con = sql.connect("DEMO.db")


def add_category(category_name):  # 增加图书类目
    cur = con.cursor()
    flag = True
    cur.execute("SELECT id FROM categories WHERE name=(?)", (category_name,))
    now_result = cur.fetchone()
    if now_result is None:
        cur.execute("INSERT INTO categories(name) values(?)", (category_name,))
    else:
        flag = False
    con.commit()
    cur.close()
    return flag


def remove_category(category_name):  # 删除图书类目
    cur = con.cursor()
    cur.execute("SELECT * FROM categories WHERE name=(?)", (category_name,))
    now_result = cur.fetchone()
    if now_result is None:
        print("There is no such category.")
    else:
        cur.execute("DELETE FROM categories WHERE name=?", (category_name,))
    con.commit()
    cur.close()
    return now_result


def get_info(category_name):  # 返回图书类目信息
    cur = con.cursor()
    cur.execute("SELECT * FROM categories WHERE name=(?)", (category_name,))
    now_result = cur.fetchone()
    con.commit()
    cur.close()
    return now_result


def num_up(cate_name, num):  # 修改图书类目下图书的数量，变化量为num
    cur = con.cursor()
    cur.execute("SELECT book_number FROM categories WHERE name=(?)", (cate_name,))
    flag = True
    now_num = cur.fetchone()[0]
    if now_num + num < 0:
        print("The number of this category should be a positive number.")
        flag = False
    else:
        cur.execute("UPDATE categories SET book_number=? WHERE name=(?)", (now_num + num, cate_name))
    con.commit()
    cur.close()
    return flag


def check(cate_name):  # 查询是否存在该类目
    cur = con.cursor()
    cur.execute("SELECT * FROM categories WHERE name=(?)", (cate_name,))
    flag = True
    now_result = cur.fetchone()
    if now_result is None:
        flag = False
    con.commit()
    cur.close()
    return flag
