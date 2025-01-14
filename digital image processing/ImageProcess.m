clear;
clc;

A = imread("Lenna.jpg");
subplot(2, 3, 1);
imshow(A);
title("A: 原图");

X = [0.3; 0.6];
Y = [0.1; 0.9];
B = imadjust(A, X, Y);
subplot(2, 3, 2);
imshow(B);
title("B: 线性拓展");

c = 2;
C = c * log(1 + double(A) / 255);
subplot(2, 3, 3);
imshow(C);
title("C: 非线性拓展");

D = 255 - A;
subplot(2, 3, 4);
imshow(D);
title("D: 取反");

E = rgb2gray(A);
subplot(2, 3, 5);
imshow(E);
title("E: 灰度图");

threshold = 0.5;
F = imbinarize(E, threshold);
subplot(2, 3, 6);
imshow(F);
title("F: 二值化");
