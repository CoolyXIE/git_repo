function g = f_Filter(f, H)
[P, Q] = paddedsize(size(f, 1), size(f, 2));
F = fft2(f, P, Q);
imshow(F);
H2 = zeros(P, Q);
H2(1:size(H,1), 1:size(H,2)) = H;
H = fftshift(H2);
G = H.*F;
g = real(abs(ifft2(G)));
g = g(1:size(f,1), 1:size(f,2));
figure;
imshow(g, []);


