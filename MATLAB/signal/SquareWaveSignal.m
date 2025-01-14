w = 1;

t = -10 : 0.01 : 10;
ya = square(w * t);
plot(t, ya);

hold on;

k = -10 : 10;
yd = square(w * k);
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('square wave signal');