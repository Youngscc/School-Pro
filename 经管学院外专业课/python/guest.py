import sqlite3 as sql
import books_operation as book_db
import users_operation as user_db
import events_operation as event_db

con = sql.connect("DEMO.db")


def hello():
    print("**************************************************************")
    print("*---------------          WELCOME!          -----------------*")
    print("*---------------Please choose your operation-----------------*")
    print("* 1. Borrow books                                            *")
    print("* 2. Return books                                            *")
    print("* 3. Search for books' information                           *")
    print("* 4. Change my information                                   *")
    print("* 5. Log out                                                 *")
    print("**************************************************************")


def search_book(book_id):  # 输出图书信息（名字，描述，所属类目）
    result = book_db.search_book(book_id)
    if result is None:
        return False
    else:
        print("Book Name: " + result[1])
        print("Book Describe: " + result[4])
        print("Book Category: " + result[5])
    return True


def main(me_id):
    while True:
        hello()
        opt = int(input())
        if opt == 1:  # 借书: 用户借书数量增加，图书借书数量增加，库存数量减少，借书事件增加
            print("Please input the ID number of the book you want to borrow:")
            book_id = int(input())
            if not search_book(book_id):
                print("There is no such book.")
                continue
            if event_db.check(me_id, book_id) is not None:
                print("Sorry, you have borrowed this book.")
                continue
            if not book_db.borrow_book(book_id, 1):
                continue
            event_db.add_event(me_id, book_id)
            user_db.borrow_book(me_id, 1)
            print("Successfully borrow the book!")
        elif opt == 2:  # 还书：用户借书数量减少，图书借书数量减少，库存数量增加，借书事件减少
            print("Please input the ID number of the book you want to return:")
            book_id = int(input())
            if event_db.check(me_id, book_id) is None:
                print("You haven't borrowed this book.")
                continue
            user_db.borrow_book(me_id, -1)
            book_db.borrow_book(book_id, -1)
            event_db.remove_event(me_id, book_id)
            print("Successfully return the book!")
        elif opt == 3:  # 查询图书信息
            print("Please input the ID number of the book you want to search for:")
            book_id = int(input())
            if not search_book(book_id):
                print("There is no such book.")
        elif opt == 4:  # 修改自己信息（名字，密码）
            print("**************************************************************")
            print("* 1. Name                                                    *")
            print("* 2. Password                                                *")
            print("**************************************************************")
            print("Please enter the serial number corresponding to the content you want to modify:")
            opt_a = int(input())
            new_text = ""
            if opt_a == 1:
                print("Please input the new name:")
                new_text = input()
            elif opt_a == 2:  # 修改密码需首先输入旧密码，然后输入新密码并重复输入新密码确认
                print("Please enter the old password:")
                old_pw = input()
                user_info = user_db.check_user(me_id)
                if old_pw != user_info[2]:
                    print("Old password entered is wrong.")
                    continue
                fin = 0
                while fin == 0:
                    print("Please input the new password:")
                    user_pw = input()
                    print("Please input the new password once again to ensure:")
                    user_pw_again = input()
                    if user_pw == user_pw_again:
                        fin = 1
                        new_text = user_pw
                    else:
                        print("The two entered passwords are inconsistent, please try again!")
            user_info = user_db.maintain_user(me_id, opt_a, new_text)
            if user_info is not None:
                print("Successfully modify the information!")
        elif opt == 5:  # 退出登录
            return
        else:
            print("Please input the correct operation number.")
