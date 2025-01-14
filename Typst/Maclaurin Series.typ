#let LF = {v(4em); linebreak()}

= Maclaurin Series

$
& e^x &&= 1 + x + 1/2 x^2 + o(x^2) &&= sum_(n=0)^infinity 1/(n!)x^n, space x in (-infinity, +infinity)
LF
& sin x &&= x - 1/6 x^3 + o(x^3) &&= sum_(n=0)^infinity ((-1)^n)/(2 n + 1)! x^(2 n + 1), space x in (-infinity, +infinity)
LF
==>^"Derivation" & cos x &&= 1 - 1/2 x^2 + o(x^3) &&= sum_(n=0)^infinity ((-1)^n)/(2 n)! x^(2 n), space x in (-infinity, +infinity)
LF
& arcsin x &&= x + 1/6 x^3 + o(x^3) &&= sum_(n=0)^infinity (2 n)!/(4^n (n!)^2 (2n + 1)) x^(2 n + 1), space x in [-1, +1]
LF
& tan x &&= x + 1/3 x^3 + o(x^3) &&= sum_(n=1)^infinity (B_(2 n)(-4)^n (1-4^n))/(2 n)! x^(2 n - 1), space x in (-pi/2, +pi/2)
LF
& arctan x &&= x - 1/3 x^3 + o(x^3) &&= sum_(n=0)^infinity ((-1)^n)/(2 n + 1) x^(2 n + 1), space x in [-1, +1]
LF
& (1+x)^alpha &&= 1 + alpha x + (alpha (alpha - 1))/2 x^2 + o(x^2) &&= sum_(n=0)^infinity C_alpha^n x^n, space x in (-1, +1)
LF
& ln(1 + x) &&= x - 1/2 x^2 + o(x^2) &&= sum_(n=0)^infinity ((-1)^n)/(n + 1) x^(n + 1), space x in (-1, +1]
LF
==>^"Derivation" & 1/(1+x) &&= 1 - x + x^2 + o(x^2) &&= sum_(n=0)^infinity (-x)^n, space x in (-1, +1)
LF
==>^(x -> (-x)) & 1/(1-x) &&= 1 + x + x^2 + o(x^2) &&= sum_(n=0)^infinity x^n, space x in (-1, +1)
LF
$
