import os
import time
argvs = (2, 3, 4, 8, 16, 32, 64, 128, 256, 512, 1024)
ISOTIMEFORMAT='%Y-%M-%D-%H-%M-%S'

cmd1 = "./main -n {} -o {} " + str(time.time())
cmd2 = "./cmpDown -n {} -o {} " + str(time.time())
cmd3 = "./cmpUp -n {} -o {} " + str(time.time())


# for i in range(1, 5):
#     # print("------ o = " + str(i) + " ----------")
#     with open("data.txt","a") as file:
#         file.write("o = " + str(i) + "\n")
#         file.flush()
#         for arg in argvs:
#             # print("n = " + str(arg))
#             if os.system(cmd1.format(arg, i)):
#                 print("ERROR")
# # print(" ------------------------------------- cmp ------------------------------------------")

# for i in range(1, 5):
#     # print("------ o = " + str(i) + " ----------")
#     with open("data.txt","a") as file:
#         file.write("o = " + str(i) + "\n")
#         file.flush()
#         for arg in argvs:
#             # print("n = " + str(arg))
#             if os.system(cmd2.format(arg, i)):
#                 print("ERROR")

with open("data.txt","a") as file:
    file.write(" --------------------- Upper Bound ----------------------- \n")
    file.flush()


for i in range(1, 5):
    # print("------ o = " + str(i) + " ----------")
    with open("data.txt","a") as file:
        file.write("o = " + str(i) + "\n")
        file.flush()
        for arg in argvs:
            # print("n = " + str(arg))
            if os.system(cmd3.format(arg, i)):
                print("ERROR")