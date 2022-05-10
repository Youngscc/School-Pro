# -*- coding: utf-8 -*-

import os

argvs = (10, 20, 30, 40, 50, 100)
# argvs = (4, 8, 15, 20, 30, 50)

cmd = "./a -F {} -W {} -R 1 -H {}"
# cmd = "./a -F {} -W 4 -R 1 -H 100 -P {}"
cmdd = "./a -F {} -W 1 -R 1"
filename = "data/Booking_cp.txt"
# filename = "data/kosarak.txt"
# filename = "data/AOL.txt"

# if os.system(cmdd.format(filename)):
#     print("ERROR")

# for i in argvs:
#     if os.system(cmd.format(filename,2, i)):
#         print("ERROR")

if os.system(cmd.format(filename,2, 100)):
        print("ERROR")

for i in argvs:
    if os.system(cmd.format(filename,3, i)):
        print("ERROR")

# for i in argvs:
#     if os.system(cmd.format(filename, i)):
#         print("ERROR")

print("Successful!")