clc;
clear;
close all;


%% read data

im = double(imread('image.jpg'))/255;
mark = double(imread('mark.jpg'))/255;
figure, imshow(im), title('original image');
figure, imshow(mark), title('watermark');


%% encode mark

imsize = size(im);
% random
TH = zeros(imsize(1)*0.5,imsize(2),imsize(3));
TH1 = TH;
TH1(1:size(mark,1),1:size(mark,2),:) = mark;
M = randperm(0.5*imsize(1));
N = randperm(imsize(2));
for i=1:imsize(1)*0.5
    for j=1:imsize(2)
        TH(i,j,:)=TH1(M(i),N(j),:);
    end
end
% symmetric
mark_ = zeros(imsize(1),imsize(2),imsize(3));
mark_(1:imsize(1)*0.5,1:imsize(2),:) = TH;
for i=1:imsize(1)*0.5
    for j=1:imsize(2)
        mark_(imsize(1)+1-i,imsize(2)+1-j,:)=TH(i,j,:);
    end
end
figure, imshow(mark_), title('encoded watermark');


%% add watermark

FA = fft2(im);
figure, imshow(real(FA)), title('spectrum of original image');
FB = FA+double(mark_);
figure, imshow(real(FB)), title('spectrum of watermarked image');
FAO = ifft2(FB);
figure, imshow(real(FAO)), title('watermarked image');


%% extract watermark

FA2 = fft2(FAO);
G = (FA2-FA);
GG = G;
for i=1:imsize(1)*0.5
    for j=1:imsize(2)
        GG(M(i),N(j),:)=G(i,j,:);
    end
end
for i=1:imsize(1)*0.5
    for j=1:imsize(2)
        GG(imsize(1)+1-i,imsize(2)+1-j,:)=GG(i,j,:);
    end
end
figure, imshow(real(GG)), title('extracted watermark');
