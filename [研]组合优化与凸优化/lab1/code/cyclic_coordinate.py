import numpy as np
import math

def rosenbrock(x):
    x1 = x[0]
    x2 = x[1]
    return 100.0 * (x2 - x1**2)**2 + (1 - x1)**2

def rosenbrock_grad(x):
    x1 = x[0]
    x2 = x[1]
    grad = np.zeros(2)
    grad[0] = -400.0 * x1 * (x2 - x1**2) - 2.0 * (1 - x1)
    grad[1] = 200.0 * (x2 - x1**2)
    return grad

def find_initial_range(loss_function, x, direction):
    # 设置步长和最大迭代次数。
    step = 1.0
    max_iter = 100
    
    # 在当前点的左侧不断迭代，直到找到一个函数值较小的点。
    a = 0
    fmin = loss_function(x + a * direction)
    for i in range(max_iter):
        xnew = x + (a - step * (i + 1)) * direction
        fnew = loss_function(xnew)
        if fnew < fmin:
            a = a - step * (i + 1)
            # print(a)
            fmin = fnew
        else:
            break
    
    # 在当前点的右侧不断迭代，直到找到一个函数值较小的点。
    b = 0
    fmax = loss_function(x + b * direction)
    for i in range(max_iter):
        xnew = x + (b + step * (i + 1)) * direction
        fnew = loss_function(xnew)
        if fnew < fmax:
            b = b + step * (i + 1)
            fmax = fnew
        else:
            break
    
    # 如果初始搜索区间太小，则扩大一倍。
    if abs(b - a) < 1e-6:
        a = -2 * step
        b = 2 * step
    
    return a, b


def golden_search(loss_function, x, direction, epsilon=1e-5):
    phi = (1 + math.sqrt(5)) / 2
    a, b = find_initial_range(loss_function, x, direction)
    x1 = b - (b - a) / phi
    x2 = a + (b - a) / phi
    while abs(b - a) > epsilon:
        if loss_function(x + x1 * direction) < loss_function(x + x2 * direction):
            b = x2
        else:
            a = x1
        x1 = b - (b - a) / phi
        x2 = a + (b - a) / phi
    return (a + b) / 2

def fibonacci_search(loss_function, x, direction, delta=1e-5):
    fib_sequence = [1,1]
    a, b = find_initial_range(loss_function, x, direction)
    while (fib_sequence[-1] < (b-a)/delta):
        fib_sequence.append(fib_sequence[-1] + fib_sequence[-2])
    n = len(fib_sequence) - 1

    x1 = a + fib_sequence[n - 2] * (b - a) / fib_sequence[n]
    x2 = a + fib_sequence[n - 1] * (b - a) / fib_sequence[n]

    while abs(b - a) > 1e-5:
        if loss_function(x + x1 * direction) < loss_function(x + x2 * direction):
            b = x2
            x2 = x1
            x1 = a + fib_sequence[n - 2] * (b - a) / fib_sequence[n]
        else:
            a = x1
            x1 = x2
            x2 = a + fib_sequence[n - 1] * (b - a) / fib_sequence[n]

    return (a + b) / 2

def dichotomous_search(loss_function, x, direction, epsilon=1e-5):
    a, b = find_initial_range(loss_function, x, direction)
    while abs(b - a) > epsilon:
        midpoint = (a + b) / 2
        if loss_function(x + midpoint * direction) < loss_function(x + (midpoint + epsilon) * direction):
            b = midpoint
        else:
            a = midpoint
    return (a + b) / 2

def cyclic_coordinate_method(func, func_grad, start, method='golden_search', epsilon=1e-3, k_max=10000):
    x, M, k = [np.array(start)], len(start), 0
    while True:
        # 如果满足终止条件，则退出循环
        gradient = func_grad(x[k])
        if k > k_max or np.linalg.norm(gradient) < epsilon:
            break

        # 使用轮换算法确定要优化的坐标
        direction = np.zeros(M)
        direction[k % M] = 1

        # 根据选择的搜索方法更新 x
        if method == 'golden_search':
            step = golden_search(func, x[k], direction)
        elif method == 'fibonacci_search':
            step = fibonacci_search(func, x[k], direction)
        elif method == 'dichotomous_search':
            step = dichotomous_search(func, x[k], direction)
        else:
            return x

        x.append(x[k] + direction * step)
        k += 1

    return x

x0 = [5.0, 10.0]
result = cyclic_coordinate_method(rosenbrock, rosenbrock_grad, x0, 'golden_search')
print("golden_search: ", result[len(result)-1])
result = cyclic_coordinate_method(rosenbrock, rosenbrock_grad, x0, 'fibonacci_search')
print("fibonacci_search: ", result[len(result)-1])
result = cyclic_coordinate_method(rosenbrock, rosenbrock_grad, x0, 'dichotomous_search')
print("dichotomous_search: ", result[len(result)-1])