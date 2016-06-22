clear;
N = 100;
f = zeros(50, 50);
f(15:35, 23:28) = 1;
imshow(f);
F = fft2(f, N, N);
F = log(abs(F));
figure;
x = 1:N;
y = 1:N;
imshow(F, []);
% F = fftshift(abs(F));
% figure
% x =1:N;
% y = 1:N;
% mesh(x,y,F(x,y));
% colormap(gray);
% colorbar
% imshow(fft2(f, N, N));