#let LF = {v(3em); linebreak()}

$
& lim_(x -> infinity) ((a x + b) / (a x + c))^(h x + k) space (a != 0)
LF
=& lim_(x -> infinity) e^((h x + k) ln((a x + b) / (a x + c)))
LF
=& lim_(x -> infinity) e^((h x + k) ln((a x + b + c - c) / (a x + c)))
LF
=& lim_(x -> infinity) e^((h x + k) ln(1 + (b - c) / (a x + c)))
LF
=& lim_(x -> infinity) e^((h x + k) (b - c) / (a x + c))
LF
=& lim_(x -> infinity) e^(((b - c)h x + (b - c)k)/(a x + c))
LF
=& e^(((b - c)h)/a)
LF
$
