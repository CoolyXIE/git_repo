% 入口图像为 BW，出口图像为f  
clc,close  
BW=imread('gangsi_bad3.jpg');  
figure, imshow(BW);
hold on;
BW=rgb2gray(BW);  
thresh=[0.01,0.17];  
sigma=2;%定义高斯参数  
f = edge(double(BW),'canny',thresh,sigma);  
figure,imshow(f,[]);title('canny 边缘检测');  
% [H, theta, rho]= hough(f);  
% %imshow(theta,rho,H,[],'notruesize'),  
% axis on,  
% axis normal  
% %xlabel('\theta'),ylabel('rho');  
% P=houghpeaks(H,5);  
% hold on  
% lines=houghlines(f,theta,rho,P); 
% figure,imshow(f,[]),title('Hough Transform Detect Result'),  
% length(lines)
% hold on  
% for k=1:length(lines)   
%     xy=[lines(k).point1;lines(k).point2];  
% plot(xy(:,1),xy(:,2),'LineWidth',4,'Color',[.6 .6 .6]);  
% end  