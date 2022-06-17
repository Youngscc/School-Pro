import numpy as np
import csv


# load data
def load_data():
    with open("vector01.csv", mode="r") as file1:
        lines = csv.reader(file1)
        rows = 0
        max_len = 0
        for line in lines:
            rows += 1
            temp_len = len(line)
            if temp_len > max_len:
                max_len = temp_len
    file1.close()
    with open("vector01.csv", mode="r") as file1:

        row = 0
        datamat = np.zeros((rows, max_len))

        lines = csv.reader(file1)
        for line in lines:
            i = 0
            for kk in line:
                datamat[row, i] = float(kk)
                i += 1
            row += 1

        return rows, max_len, datamat
