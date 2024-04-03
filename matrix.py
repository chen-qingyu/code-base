import sympy

A = sympy.Matrix([[1, 2], [3, 4]])
B = sympy.zeros(2)
C = sympy.ones(2)
D = sympy.eye(2)

print(((A+B)*(C+D))**(-1))
# Matrix([[-11/6, 5/6], [5/3, -2/3]])
