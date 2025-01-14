K = 1; % 比例系数
T = 1; % 时间常数
wn = sqrt(K/T);
zeta = 1/(2*sqrt(K*T));

% 比例环节
Gb = tf(K, 1);

% 惯性环节
Gg = tf(1, [T, 1]);

% 积分环节
Gj = tf(1, [1, 0]);

% 振荡环节
Gz = tf(wn*wn, [1, 2*wn*zeta, wn*wn]);

% 微分环节
Gw = tf([1, 0], 1);

% 一阶微分环节
Gy = tf([T, 1], 1);

% 二阶微分环节
Ge = tf([1, 2*wn*zeta, wn*wn], 1);