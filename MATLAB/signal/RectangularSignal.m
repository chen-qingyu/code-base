t = -1 : 0.01 : 1;
ya = rectpuls(t);
plot(t, ya);

hold on;

k = -1 : 1;
yd = rectpuls(k);
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('rectangular signal');