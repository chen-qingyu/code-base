#let LF = {v(4em); linebreak()}

#let mdelta = $4 a c - b^2$
#let denA = $x^2 + b/a x + c/a$
#let denB = $(x + b/(2 a))^2 + c/a - b^2/(4 a^2)$

$
& integral (m x + n)/(a x^2 + b x + c) dif x space (a != 0)
LF
=& integral (m/a x + n/a)/denA dif x
LF
=& integral (m/a x + n/a)/denB dif x
LF
=& m/a integral x/denB dif x + n/a integral 1/denB dif x
LF
=& m/(2 a) integral (2 x + b/a - b/a) / denB dif x + n/a integral 1/denB dif x
LF
=& m/(2 a) integral (2 x + b/a)/denB dif x + (2 n a - m b)/(2 a^2) integral 1/denB dif x
LF
=& m/(2 a) integral 1/denA dif (denA) + (2 n a - m b)/(2 a^2) integral 1/((x + b/(2 a))^2 + (sqrt(mdelta/(4 a^2)))^2) dif (x + b/(2 a))
LF
=& m/(2 a) ln|denA| + (2 n a - m b)/(2 a^2) 1/(sqrt(mdelta/(4 a^2))) arctan (x + b/(2 a))/(sqrt(mdelta/(4 a^2))) + C
LF
=& m/(2 a) ln|a x^2 + b x + c| + (2 n a - m b)/(a sqrt(mdelta)) arctan (2 a x + b)/(sqrt(mdelta)) + C
LF
$
