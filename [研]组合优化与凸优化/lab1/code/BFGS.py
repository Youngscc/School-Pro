import numpy as np

def rosenbrock(x):
    return (1 - x[0])**2 + 100 * (x[1] - x[0]**2)**2

def rosenbrock_grad(x):
    grad = np.array([-2*(1-x[0])-400*x[0]*(x[1]-x[0]**2), 200*(x[1]-x[0]**2)])
    return grad

def bfgs(x0, max_iter=1000, tol=1e-5):
    n = len(x0)
    B = np.eye(n)
    x = x0.copy()
    grad = rosenbrock_grad(x)
    for i in range(max_iter):
        if np.linalg.norm(grad) < tol:
            break
        p = -np.dot(B, grad)
        alpha = 1.0
        while rosenbrock(x+alpha*p) > rosenbrock(x) + 0.01*alpha*np.dot(grad,p):
            alpha /= 2.0
        s = alpha * p
        x_new = x + s
        y = rosenbrock_grad(x_new) - grad
        rho = 1.0 / np.dot(y, s)
        if rho < 0:
            B = np.eye(n)
        else:
            A = np.eye(n) - rho * np.outer(s, y)
            B = np.dot(A, np.dot(B, A.T)) + rho * np.outer(s, s)
        x = x_new
        grad = rosenbrock_grad(x)
    return x, rosenbrock(x)

x0 = np.array([-1.2, 1.0])
x_bfgs, min_val_bfgs = bfgs(x0)
print("BFGS: ", min_val_bfgs, x_bfgs)
