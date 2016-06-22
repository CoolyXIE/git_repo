%%清理
close all
clear
clc

%初始化
P1 = [0, 0, 1, 1; 0, 1, 0, 1];
P2 = P1(1,:).^2;
P3 = P1(1,:).*P1(2,:);
P4 = P1(2,:).^2;
P = [P1(1,:); P2; P3; P4; P1(2,:)];
d = [0,1,1,0];

lr = maxlinlr(P, 'bias');

%线性网络
net = linearlayer(0, lr);
net = train(net, P, d);

%显示
plot([0,1],[0,1],'o','LineWidth', 2);
hold on;
plot([0,1],[1,0],'d','LineWidth', 2);
x = -.1:.1:1.1;
y = -.1:.1:1.1;
N = length(x);
X = repmat(x, 1, N);
Y = repmat(y, N, 1);
Y = Y(:)';
P = [X;X.^2;X.*Y;Y.^2;Y];
yy = net(P);
y1 = reshape(yy, N, N);
[C, h] = contour(x, y, y1, 0.5, 'b')
clabel(C, h);
legend('0', '1', 'sfsf');



