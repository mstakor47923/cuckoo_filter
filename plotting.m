%%Plotting

%%Test1 - changing bucket size
%%Test2 - changing bucket number
%%Test3 - chaniging fingerprints size

% %figure(5);
% hold on;
% bar(xdata,bpcombine3,0.125,'FaceColor',[0,0,1],...
%                      'EdgeColor',[0,0,1]);   
% bar(xdata,bpcombine2,0.25,'FaceColor',[0,1,0],...
%                      'EdgeColor',[0,1,0]);  
% bar(xdata,bpcombine1,0.4,'FaceColor',[1,0,0]);
% set(gca, 'XTick', 1:6, 'XTickLabel', labels);
% title('Blocking Probability vs Routing Level');

data = csvread('test1.csv',1); % Read the data

subplot(3,3,1)
plot(data(:,1),data(:,2))
xlabel('Bucket size');
ylabel('Time in miliseconds');
subplot(3,3,2)
plot(data(:,1),data(:,3))
xlabel('Bucket size');
ylabel('Memory used in kilobytes');
title('Bucket size is the variable')
subplot(3,3,3)
plot(data(:,1),data(:,4))
xlabel('Bucket size');
ylabel('False positive percentage');




%%Bucket number
data = csvread('test2.csv',1); % Read the data

subplot(3,3,4)
plot(data(:,1),data(:,2))
xlabel('Bucket number');
ylabel('Time in miliseconds');
subplot(3,3,5)
plot(data(:,1),data(:,3))
xlabel('Bucket number');
ylabel('Memory used in kilobytes');
title('Bucket number is the variable')
subplot(3,3,6)
plot(data(:,1),data(:,4))
xlabel('Bucket number');
ylabel('False positive percentage');

%%Fingerprint size
data = csvread('test3.csv',1); % Read the data


subplot(3,3,7)
plot(data(:,1),data(:,2))
xlabel('Fingerprint size');
ylabel('Time in miliseconds');

subplot(3,3,8)
plot(data(:,1),data(:,3))
xlabel('Fingerprint size');
ylabel('Memory used in kilobytes');
title('Fingerprint size is the variable');
subplot(3,3,9)
plot(data(:,1),data(:,4))
xlabel('Fingerprint size');
ylabel('False positive percentage');


