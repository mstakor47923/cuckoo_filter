dataRef = csvread('dataReference.csv',0);
dataStd = csvread('dataStudent.csv',0);
dataStdDyn=csvread('dataStudentDynamic.csv',0);% Read the data


%ref-vrijeme
data10k_t=dataRef(5:8,3)
data1000k_t=dataRef(13:16,3);
data100k_t=dataRef(9:12,3)

%ref-memorija
data10k_m=dataRef(5:8,4)
data1000k_m=dataRef(13:16,4);
data100k_m=dataRef(9:12,4)

%ref-fp
data10k_f=dataRef(5:8,5)
data1000k_f=dataRef(13:16,5);
data100k_f=dataRef(9:12,5)
%std-vrijeme
datas10k_t=dataStd(5:8,3)
datas100k_t=dataStd(9:12,3)
datas1000k_t=dataStd(13:16,3);
%std memorija
datas10k_m=dataStd(5:8,4)
datas100k_m=dataStd(9:12,4)
datas1000k_m=dataStd(13:16,4);
%std fp rate
datas10k_f=dataStd(5:8,5)
datas100k_f=dataStd(9:12,5)
datas1000k_f=dataStd(13:16,5);


%dyn-vrijeme
dataD10k_t=dataStdDyn(5:8,3);
dataD100k_t=dataStdDyn(9:12,3);
dataD1000k_t=dataStdDyn(13:16,3);
%%dyn memorija
dataD10k_m=dataStdDyn(5:8,4);
dataD100k_m=dataStdDyn(9:12,4);
dataD1000k_m=dataStdDyn(13:16,4);
%dyn fpr
dataD10k_f=dataStdDyn(5:8,5);
dataD100k_f=dataStdDyn(9:12,5);
dataD1000k_f=dataStdDyn(13:16,5);

ymin=0;
ymax=1200;
figure(1)
subplot(1,3,1)


bar([1 2 3 4],[data10k_t(1) datas10k_t(1) dataD10k_t(1);data10k_t(2) datas10k_t(2) dataD10k_t(2);data10k_t(3) datas10k_t(3) dataD10k_t(3);data10k_t(4) datas10k_t(4) dataD10k_t(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'}),set(gca,'YLim',[ymin ymax]);
title("Za 10000 kmera");
legend('Reference','Static','Dynamic')






subplot(1,3,2)
bar([1 2 3 4],[data100k_t(1) datas100k_t(1) dataD100k_t(1);data100k_t(2) datas100k_t(2) dataD100k_t(2);data100k_t(3) datas100k_t(3) dataD100k_t(3);data100k_t(4) datas100k_t(4) dataD100k_t(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'}),set(gca,'YLim',[ymin ymax]);
title("Za 100 000 kmera");
legend('Reference','Static','Dynamic')


subplot(1,3,3)
bar([1 2 3 4],[data1000k_t(1) datas1000k_t(1) dataD1000k_t(1);data1000k_t(2) datas1000k_t(2) dataD1000k_t(2);data1000k_t(3) datas1000k_t(3) dataD1000k_t(3);data1000k_t(4) datas1000k_t(4) dataD1000k_t(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'}),set(gca,'YLim',[ymin ymax]);
title("Za 1 000 000 kmera");
legend('Reference','Static','Dynamic')

figure(2)

subplot(1,3,1)

bar([1 2 3 4],[data10k_m(1) datas10k_m(1) dataD10k_m(1);data10k_m(2) datas10k_m(2) dataD10k_m(2);data10k_m(3) datas10k_m(3) dataD10k_m(3);data10k_m(4) datas10k_m(4) dataD10k_m(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 10000 kmera");
legend('Reference','Static','Dynamic')

subplot(1,3,2)
bar([1 2 3 4],[data100k_m(1) datas100k_m(1) dataD100k_m(1);data100k_m(2) datas100k_m(2) dataD100k_m(2);data100k_m(3) datas100k_m(3) dataD100k_m(3);data100k_m(4) datas100k_m(4) dataD100k_m(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 100000 kmera");
legend('Reference','Static','Dynamic')

subplot(1,3,3)
bar([1 2 3 4],[data1000k_m(1) datas1000k_m(1) dataD1000k_m(1);data1000k_m(2) datas1000k_m(2) dataD1000k_m(2);data1000k_m(3) datas1000k_m(3) dataD1000k_m(3);data1000k_m(4) datas1000k_m(4) dataD1000k_m(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 1 000 000 kmera");
legend('Reference','Static','Dynamic')

figure(3)


subplot(1,3,1)

bar([1 2 3 4],[data10k_f(1) datas10k_f(1) dataD10k_f(1);data10k_f(2) datas10k_f(2) dataD10k_f(2);data10k_f(3) datas10k_f(3) dataD10k_f(3);data10k_f(4) datas10k_f(4) dataD10k_f(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 10000 kmera");
legend('Reference','Static','Dynamic')

subplot(1,3,2)
bar([1 2 3 4],[data100k_f(1) datas100k_f(1) dataD100k_f(1);data100k_f(2) datas100k_f(2) dataD100k_f(2);data100k_f(3) datas100k_f(3) dataD100k_f(3);data100k_f(4) datas100k_f(4) dataD100k_f(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 100000 kmera");
legend('Reference','Static','Dynamic')

subplot(1,3,3)
bar([1 2 3 4],[data1000k_f(1) datas1000k_f(1) dataD1000k_f(1);data1000k_f(2) datas1000k_f(2) dataD1000k_f(2);data1000k_f(3) datas1000k_f(3) dataD1000k_f(3);data1000k_f(4) datas1000k_f(4) dataD1000k_f(4)],'BarWidth',1),set(gca,'XTickLabel',{'10','20','50','100'});
title("Za 1 000 000 kmera");
legend('Reference','Static','Dynamic')

disp("1 figura je vrijeme, 2 memorija, 3 fpr")






%legend([datay datasy], 'M1','M2' );
%legend([b1 b2],'Bar Chart 1','Bar Chart 2')