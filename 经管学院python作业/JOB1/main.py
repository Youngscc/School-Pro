import users_operation as db
import administer as ad
import guest as ge


def hello():
    print("***************************************************************")
    print("***************            WELCOME!           *****************")
    print("***************************************************************")


while True:
    hello()
    log_result = -1
    user_name = ""
    user_id = 0
    while log_result == -1:
        print("Please input your user ID number:")
        user_id = int(input())
        user_info = db.check_user(user_id)
        if user_info is None:
            print("The ID number input is wrong. Please input it one more time.")
            continue
        print("Please input your password:")
        user_password = input()
        if user_password != user_info[2]:
            print("The password input is wrong. Please log in one more time.")
        else:
            log_result = user_info[3]
            user_name = user_info[1]

    print("Log in successfully!")
    print("Hello, " + user_name + "!")

    if log_result == 0:  # 根据该用户的管理员权限决定执行的功能
        ge.main(user_id)
    else:
        ad.main()
