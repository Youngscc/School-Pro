import numpy as np

def rosenbrock(x):
    return (1 - x[0])**2 + 100 * (x[1] - x[0]**2)**2

def rosenbrock_grad(x):
    grad = np.array([-2*(1-x[0])-400*x[0]*(x[1]-x[0]**2), 200*(x[1]-x[0]**2)])
    return grad

def steepest_descent(x0, max_iter=1000, tol=1e-5, eta=0.001):
    x = x0.copy()
    for i in range(max_iter):
        grad = rosenbrock_grad(x)
        if np.linalg.norm(grad) < tol:
            break
        x -= eta * grad
    return x, rosenbrock(x)

def conjugate_gradient(x0, max_iter=1000, tol=1e-5):
    x = x0.copy()
    d = -rosenbrock_grad(x)
    r = np.dot(d, d)
    for i in range(max_iter):
        alpha = r / np.dot(d, rosenbrock_grad(x))
        x += alpha * d
        new_r = r - alpha * np.dot(d, rosenbrock_grad(x))
        if np.sqrt(new_r) < tol:
            break
        beta = new_r / r
        d = -rosenbrock_grad(x) + beta * d
        r = new_r
    return x, rosenbrock(x)

x0 = np.array([-1.2, 1.0])
x_sd, min_val_sd = steepest_descent(x0)
print("Steepest Descent: ", min_val_sd, x_sd)
x_cg, min_val_cg = conjugate_gradient(x0)
print("Conjugate Gradient: ", min_val_cg, x_cg)
