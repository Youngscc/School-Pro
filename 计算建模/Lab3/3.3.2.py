import numpy as np


def weather_to_weather(x, y):
    if x == 1:
        if y == 1:
            return 0.6
        else:
            return 0.4
    else:
        if y == 1:
            return 0.3
        else:
            return 0.7


def weather_to_activity(x, y):
    if x == 1:
        if y == 1:
            return 0.6
        elif y == 2:
            return 0.3
        else:
            return 0.1
    else:
        if y == 1:
            return 0.1
        elif y == 2:
            return 0.4
        else:
            return 0.5


activities = [2, 1, 3, 2, 3, 2, 2, 3, 3, 1, 2, 1, 1, 1, 2, 3, 3, 3, 3, 2]
n = len(activities)
yesterday = np.zeros([n, 3], int)
f = np.zeros([n, 3])
weather = np.zeros([n], int)
f[0][1] = 0.6 * weather_to_activity(1, activities[1])
f[0][2] = 0.4 * weather_to_activity(2, activities[1])
for i in range(1, n):
    for j in range(1, 3):
        if f[i - 1][1] * weather_to_weather(1, j) > f[i - 1][2] * weather_to_weather(2, j):
            yesterday[i][j] = 1
        else:
            yesterday[i][j] = 2
        f[i][j] = f[i - 1][yesterday[i][j]] * weather_to_weather(yesterday[i][j], j) * weather_to_activity(j, activities[i])
if f[n-1][1] > f[n-1][2]:
    weather[n-1] = 1
else:
    weather[n-1] = 2
for i in range(n - 2, -1, -1):
    weather[i] = yesterday[i + 1][weather[i + 1]]
print(weather)
