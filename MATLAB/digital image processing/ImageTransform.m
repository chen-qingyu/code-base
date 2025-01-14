clear;
clc;

A = zeros(256, 256);
A(128-64:128+64, 128-8:128+8) = 1;
subplot(2, 3, 1);
imshow(A);
title("A: raw image");

B = fftshift(abs(fft2(A)));
subplot(2, 3, 2);
imshow(B, [5 50]);
title("B: image A's DFT");

C = abs(dct2(A));
subplot(2, 3, 3);
imshow(C);
title("C: image A's DCT");

D = imrotate(A, 90);
subplot(2, 3, 4);
imshow(D);
title("D: image A rotated 90 degree");

E = fftshift(abs(fft2(D)));
subplot(2, 3, 5);
imshow(E, [5 50]);
title("E: image D's DFT");

F = abs(dct2(A));
subplot(2, 3, 6);
imshow(F);
title("F: image D's DCT");
