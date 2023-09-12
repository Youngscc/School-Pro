import numpy as np

def rosenbrock(x):
    return (1 - x[0])**2 + 100 * (x[1] - x[0]**2)**2

def rosenbrock_grad(x):
    grad = np.array([-2*(1-x[0])-400*x[0]*(x[1]-x[0]**2), 200*(x[1]-x[0]**2)])
    return grad

def dfp(x0, max_iter=1000, tol=1e-5):
    n = len(x0)
    H = np.eye(n)
    x = x0.copy()
    for i in range(max_iter):
        grad = rosenbrock_grad(x)
        if np.linalg.norm(grad) < tol:
            break
        p = -np.dot(H, grad)
        alpha = 1.0
        while rosenbrock(x+alpha*p) > rosenbrock(x) + 0.01*alpha*np.dot(grad,p):
            alpha /= 2.0
        s = alpha * p
        x_new = x + s
        y = rosenbrock_grad(x_new) - grad
        if np.dot(y, s) > 0:
            H = np.dot((np.eye(n)-np.outer(s,y)/np.dot(y,s)), np.dot(H, (np.eye(n)-np.outer(y,s)/np.dot(y,s)))) + np.outer(s,s)/np.dot(s,y)
        x = x_new
    return x, rosenbrock(x)

x0 = np.array([-1.2, 1.0])
x_dfp, min_val_dfp = dfp(x0)
print("DFP: ", min_val_dfp, x_dfp)
