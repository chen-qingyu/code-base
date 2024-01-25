#let LF = {v(3em); linebreak()}

$
& integral sqrt(1+x^2) dif x space ("let" x = tan t)
LF
=& I
LF
=& integral sec t dif tan t
LF
=& sec t tan t - integral tan t dif sec t
LF
=& sec t tan t - integral tan^2 t sec t dif t
LF
=& sec t tan t - integral (sec^2 t - 1) sec t dif t
LF
=& sec t tan t - integral sec^3 t dif t + integral sec t dif t
LF
=& sec t tan t - I + ln|sec t + tan t| + C
LF
LF
=> I =& 1/2 (sec t tan t + ln|sec t + tan t|) + C
LF
=& 1/2 (x sqrt(1+x^2) + ln(x + sqrt(1+x^2))) + C
LF
$
