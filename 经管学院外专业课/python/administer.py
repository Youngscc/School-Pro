import sqlite3 as sql
import books_operation as book_db
import category_operation as cate_db
import users_operation as user_db
import events_operation as event_db

con = sql.connect("DEMO.db")


def hello():
    print("**************************************************************")
    print("*---------------          WELCOME!          -----------------*")
    print("*---------------Please choose your operation-----------------*")
    print("* 1. About books                                             *")
    print("* 2. About users                                             *")
    print("* 3. Log out                                                 *")
    print("**************************************************************")


def hello_books():
    print("**************************************************************")
    print("*---------------        About Books         -----------------*")
    print("*---------------Please choose your operation-----------------*")
    print("* 1. Add new books                                           *")
    print("* 2. Remove books                                            *")
    print("* 3. Search for books' information                           *")
    print("* 4. Edit book information                                   *")
    print("* 5. Add new categories                                      *")
    print("* 6. Remove categories                                       *")
    print("* 7. Search for categories' information                      *")
    print("* 8. Quit                                                    *")
    print("**************************************************************")


def print_book_info(result):  # 输出图书信息
    print("Book Name: " + result[1])
    print("Book Describe: " + result[4])
    print("Book Category: " + result[5])
    print("Borrowed Number: " + str(result[2]))
    print("Rest Number: " + str(result[3]))


def book_main():
    while True:
        hello_books()
        opt = int(input())
        if opt == 1:  # 增加图书，若无该书类目则自动添加该类目
            print("Please input the name of the books:")
            now_name = input()
            print("Please input the number of the books:")
            now_number = int(input())
            print("Please input the describe of the books:")
            now_describe = input()
            print("Please input the category of the books:")
            now_category = input()
            book_id = book_db.add_book(now_name, now_number, now_describe, now_category)
            if book_id != 0:
                print("Add the books successfully! The books' id is " + str(book_id))
                if cate_db.add_category(now_category):
                    print("A new category has been automatically generated")
                cate_db.num_up(now_category, 1)
        elif opt == 2:  # 删除图书，若该图书被从数据库中删除，则将其对应类目中图书数量减一
            print("Please input the ID number of the books you want to remove:")
            now_id = int(input())
            print("Please input the number of the books you want to remove by:")
            now_number = int(input())
            book_info = book_db.remove_book(now_id, now_number)
            if book_info is not None:
                print("Remove the books successfully!")
                cate_db.num_up(book_info[5], -1)
        elif opt == 3:  # 查找图书信息
            print("Please input the ID number of the books you want to search:")
            now_id = int(input())
            result = book_db.search_book(now_id)
            if result is None:
                print("There is no such book!")
            else:
                print_book_info(result)
        elif opt == 4:  # 修改图书信息，修改图书类目时需要同时修改图书信息和类目信息
            print("Please input the ID number of the books whose information you want to change:")
            now_id = int(input())
            if book_db.search_book(now_id) is None:
                print("There is no such book.")
                continue
            print("**************************************************************")
            print("* 1. Name                                                    *")
            print("* 2. Category                                                *")
            print("* 3. Describe                                                *")
            print("**************************************************************")
            print("Please enter the serial number corresponding to the content you want to modify:")
            opt_a = int(input())
            print("Please enter new content:")
            new_content = input()
            book_info = book_db.maintain_book(now_id, opt_a, new_content)
            if book_info is not None:
                print("Successfully modified!")
                if opt_a == 2:
                    cate_db.num_up(book_info[5], -1)  # 修改对应类目信息
                    cate_db.add_category(new_content)
                    cate_db.num_up(new_content, 1)
        elif opt == 5:  # 增加新类目
            print("Please enter the name of the category you want to add.")
            now_name = input()
            if cate_db.add_category(now_name):
                print("Add the new category successfully!")
            else:
                print("This category already exists.")
        elif opt == 6:  # 删除图书类目
            print("Please enter the name of the category you want to remove.")
            now_name = input()
            book_list = book_db.get_cate(now_name)
            for book_id in book_list:
                book_db.maintain_book(book_id[0], 2, "No Category")
                cate_db.num_up("No Category", 1)
            cate_info = cate_db.remove_category(now_name)
            if cate_info is not None:
                print("Remove the category successfully!")
        elif opt == 7:  # 查询图书类目信息，包括类目下书的种类数和所有书的具体信息
            print("Please enter the name of the category whose information you want to search:")
            now_name = input()
            if not cate_db.check(now_name):
                print("There is no such category.")
            else:
                cate_info = cate_db.get_info(now_name)
                if cate_info is None:
                    print("There are no books in this category.")
                else:
                    print("There are " + str(cate_info[2]) + " books in this category.")
                    book_list = book_db.get_cate(now_name)
                    for idx in book_list:
                        print("\n")
                        print_book_info(idx)
        elif opt == 8:
            return
        else:
            print("Please input the correct option number.")


def hello_users():
    print("**************************************************************")
    print("*---------------        About users         -----------------*")
    print("*---------------Please choose your operation-----------------*")
    print("* 1. Add new users                                           *")
    print("* 2. Remove users                                            *")
    print("* 3. Search for users' information                           *")
    print("* 4. Edit users' information                                 *")
    print("* 5. Quit                                                    *")
    print("**************************************************************")


def user_main():
    while True:
        hello_users()
        opt = int(input())
        if opt == 1:  # 注册新账户
            print("Please enter the name of the registered user:")
            now_name = input()
            now_pw = ""
            fin = 0
            while fin == 0:
                print("Please enter your password:")
                now_pw = input()
                print("Please enter your password once again to ensure:")
                now_pw_again = input()
                if now_pw == now_pw_again:
                    fin = 1
                else:
                    print("The two entered passwords are inconsistent, please try again!")
            user_id = user_db.add_user(now_name, now_pw)
            print("Add new user " + str(now_name) + " successfully! The ID number is " + str(user_id) + ".")
        elif opt == 2:  # 删除用户
            print("Please enter the ID number of the user you want to remove:")
            now_id = int(input())
            if now_id == 1:
                print("Administer can't be removed.")
                continue
            event_list = event_db.get_event_by_user(now_id)
            for event_info in event_list:  # 将该用户所借图书强行归还
                book_db.borrow_book(event_info[3], -1)
                user_db.borrow_book(event_info[2], -1)
                event_db.remove_event(event_info[2], event_info[3])
            user_info = user_db.remove_user(now_id)
            if user_info is not None:
                print("Remove the user " + str(user_info[1]) + " successfully!")
        elif opt == 3:  # 查询用户信息
            print("Please input the ID number of the user you want to search for:")
            now_id = int(input())
            user_info = user_db.check_user(now_id)
            if user_info is None:
                print("There is no such user.")
                continue
            print("ID: " + str(now_id))
            print("Name: " + user_info[1])
            print("Password: " + user_info[2])
            book_list = event_db.get_event_by_user(now_id)
            if len(book_list) > 0:  # 输出该用户所有借阅的图书
                print("The books he borrowed are as follows:")
                for event_info in book_list:
                    print("\nBook ID number: " + str(event_info[3]))
                    print("Borrow time: " + str(event_info[1]))
        elif opt == 4:  # 修改用户信息
            print("Please input the ID number of the user whose information you want to change:")
            now_id = int(input())
            if user_db.check_user(now_id) is None:
                print("There is no such user.")
                continue
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
            elif opt_a == 2:
                fin = 0
                while fin == 0:
                    print("Please input the new password:")
                    user_pw = input()
                    print("Please input the new password once again to ensure:")  # 两次输入新密码予以验证
                    user_pw_again = input()
                    if user_pw == user_pw_again:
                        fin = 1
                        new_text = user_pw
                    else:
                        print("The two entered passwords are inconsistent, please try again!")
            user_info = user_db.maintain_user(now_id, opt_a, new_text)
            if user_info is not None:
                print("Successfully modify the information!")
        elif opt == 5:
            return
        else:
            print("Please input the correct operation number.")


def main():
    while True:
        hello()
        opt = int(input())
        if opt == 1:
            book_main()
        elif opt == 2:
            user_main()
        elif opt == 3:
            return
        else:
            print("Please input the correct operation number.")
