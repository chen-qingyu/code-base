#let LF = {v(3em); linebreak()}

$
& lim_(x -> 0) ((a_1^x + a_2^x + a_3^x + dots.c + a_n^x) / n)^(1/x)
LF
=& lim_(x -> 0) e^((1/x ln (a_1^x + a_2^x + a_3^x + dots.c + a_n^x) / n))
LF
=& lim_(x -> 0) e^((1/x ln (1 + (a_1^x + a_2^x + a_3^x + dots.c + a_n^x - n) / n)))
LF
=& lim_(x -> 0) e^((1/x ((a_1^x + a_2^x + a_3^x + dots.c + a_n^x - n) / n)))
LF
=& lim_(x -> 0) e^(((a_1^x + a_2^x + a_3^x + dots.c + a_n^x - n) / (n x)))
LF
=& lim_(x -> 0) e^(((a_1^x ln a_1 + a_2^x ln a_2 + a_3^x ln a_3 + dots.c + a_n^x ln a_n)/ n))
LF
=& e^(((ln a_1 + ln a_2 + ln a_3 + dots.c + ln a_n)/ n))
LF
=& e^((1/n ln (a_1 a_2 a_3 dots.c a_n)))
LF
=& (a_1 a_2 a_3 dots.c a_n)^(1/n)
LF
$
