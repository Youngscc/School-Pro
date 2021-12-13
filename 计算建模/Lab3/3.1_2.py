import numpy as np

trans = np.zeros([2, 2])
trans[0][0] = 0.6
trans[0][1] = 0.4
trans[1][0] = 0.3
trans[1][1] = 0.7
print(trans)


def get_initial_weather():
    num = np.random.rand()
    if num < 0.6:
        return 1
    else:
        return 0


def get_next_weather(tod):
    num = np.random.rand()
    if (tod == 1 and num < 0.6) or (tod == 2 and num < 0.3):
        return 1
    else:
        return 2


def get_activity(weather):
    num = np.random.rand()
    if (weather == 1 and num < 0.6) or (weather == 2 and num < 0.1):
        return 1
    elif (weather == 1 and num < 0.3) or (weather == 2 and num < 0.5):
        return 2
    else:
        return 3


Weather = []

n = 20

today_weather = get_initial_weather()
Weather.append(today_weather)
for i in range(n-1):
    today_weather = get_next_weather(today_weather)
    Weather.append(today_weather)
print("The weather is :")
print(Weather)
Activity = []
for i in range(n):
    Activity.append(get_activity(Weather[i]))

print("\nThe activities are:")
print(Activity)


