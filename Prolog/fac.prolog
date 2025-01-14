fac(0, 1).
fac(N, F) :- N > 0, M is N - 1, fac(M, G), F is N * G.
