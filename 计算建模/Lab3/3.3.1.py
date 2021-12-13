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


activities = [1, 2, 3]
want_weather = [1, 2, 2]
initial_p = [0, 0.6, 0.4]
tot = 0
for i in range(1, 3):
    for j in range(1, 3):
        for k in range(1, 3):
            tot += initial_p[i] * weather_to_weather(i, j) * weather_to_weather(j, k) * weather_to_activity(
                i, activities[0]) * weather_to_activity(j, activities[1]) * weather_to_activity(k, activities[2])
ans = initial_p[want_weather[0]] * weather_to_weather(want_weather[0], want_weather[1]) * weather_to_weather(
    want_weather[1], want_weather[2]) * weather_to_activity(want_weather[0], activities[0]) * weather_to_activity(
    want_weather[1], activities[1]) * weather_to_activity(want_weather[2], activities[2])
ans /= tot
print(ans)
