#let LF = {v(3em); linebreak()}

$
Gamma(s) &= integral_0^(+infinity) e^(-x) x^(s-1) dif x space (s > 0)
LF
&= integral_0^(+infinity) -x^(s-1) dif (e^(-x))
LF
&= 0 - integral_0^(+infinity) e^(-x) dif (-x^(s-1))
LF
&= integral_0^(+infinity) e^(-x) dif (x^(s-1))
LF
&= integral_0^(+infinity) e^(-x) (s - 1) x^(s-2) dif x
LF
&= (s - 1) integral_0^(+infinity) e^(-x) x^(s-2) dif x
LF
&= (s - 1) Gamma(s - 1)
LF
&= (s - 1) (s - 2) Gamma(s - 2)
LF
&= (s - 1) (s - 2) dots.c Gamma(1)
LF
&= (s - 1) (s - 2) dots.c 1
LF
&= (s - 1)!
LF
$
