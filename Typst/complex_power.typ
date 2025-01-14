Calculate $u = a + b i$ to the $v = c + d i$ power: $z=u^v$.

$
z =& u^v
\ \
=& (a + b i)^(c + d i)
\ \
& "let" m = sqrt(a^2 + b^2) = abs(u), space w = arctan(b / a) = arg(u)
\ \
=& (m e^(i w))^(c + d i)
\ \
=& (e^(ln m) e^(i w))^(c + d i)
\ \
=& e^((ln m + i w)(c + d i))
\ \
=& e^((c ln m - d w) + i(c w + d ln m))
\ \
& "let" theta = c w + d ln m
\ \
=& e^((c ln m - d w) + i theta)
\ \
=& e^(c ln m - d w) e^(i theta)
\ \
=& e^(c ln m - d w)(cos theta + i sin theta)
\ \
=& (m^c e^(-d w))(cos theta + i sin theta)
\ \
& "let" r = m^c e^(-d w)
\ \
=& r(cos theta + i sin theta)
\ \
=& underbrace(r cos theta, "real part") + underbrace(r sin theta, "imag part") space i
\ \
& r = abs(u)^c e^(-d arg(u)), space theta = c arg(u) + d ln abs(u)
$
