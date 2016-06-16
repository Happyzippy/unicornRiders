% Matlab file for calculations related to the walker robot
clear all;

%% Inline functions

A = @(p) [cos(p(1)) -sin(p(1))*cos(p(4))  sin(p(1))*sin(p(4)) p(3)*cos(p(1))
          sin(p(1))  cos(p(1))*cos(p(4)) -cos(p(1))*sin(p(4)) p(3)*sin(p(1))
          0          sin(p(4))            cos(p(4))           p(2)
          0          0                    0                   1 ];  

%Denavit Hartemberg parameters
AltoParam = @(q) [q(1)   -0.02     0.045      pi/2
                  q(2)-pi/2     0     0.08   0];

q_initial = [0 0];
q_initial = q_initial./(180/pi)
%figure(101)
%plot_robot(AltoParam(q_initial))

%% Calculate inverse kinematic solution

syms q1_ d1_ r1_ a1_ q2_ q2x_ r2_
d1 = -0.02
r1 =  0.045
a1 =  pi/2
q2x= -pi/2
r2 =  0.08
T = A([q1_, d1_, r1_, a1_])*A([q2_ + q2x_, 0, r2_, 0])
T = subs(T, d1_, d1);
T = subs(T, r1_, r1);
T = subs(T, a1_, a1);
T = subs(T, q2x_, q2x);
T = subs(T, r2_, r2)

%% IK implementation

% ik
ik = @(T) [atan2(T(1,3),-T(2,3))  atan2(T(3,1),T(3,2))-q2x] / pi * 180

% link transformation
T02 = @(Q) A([double(Q(1)), d1, r1, a1])*A([double(Q(2))+q2x, 0, r2, 0]);

% test
q = [0 20] / 180*pi
q_ik = ik(T02(q))

%% Design walk cycle

angle2command = 1024/300
command2angle = 1/angle2command

softMultiplier = 3

% kernel
filt = hann((softMultiplier*2 + 1));
filt = filt/sum(filt)

q1 = [20 12   4  -4  -12  -20 -17   3 15 20]%*0.3;
q2 = [45 41.5 40 40  41.5  45  55  63 59 53];


figure(1)
plot((0:length(q1)-1)*softMultiplier,q1)
hold on
plot((0:length(q2)-1)*softMultiplier,q2)
grid on
plot(softMultiplier*[5 5], ylim,'k')


q1 = repmat(q1,softMultiplier,1)
q1 = cconv(q1(:), filt, numel(q1));
q1 = circshift(q1, -floor(length(filt)*3/4) + 1);
q1 = round(q1*angle2command) * command2angle

q2 = repmat(q2,softMultiplier,1)
q2 = cconv(q2(:), filt, numel(q2));
q2 = circshift(q2, -floor(length(filt)*3/4) + 1);
q2 = round(q2*angle2command) * command2angle

plot([0:length(q1)-1], q1)
plot([0:length(q1)-1], q2)
hold off

figure(2)
clf
hold on
plot3(0, 0, 0, 'ko')
daspect([1 1 1])
hold on
clear data
for n1 = 1:length(q1)
    q = [q1(n1) q2(n1)]/180*pi;
    T = T02(q);
    data(n1,1:3) = T(1:3,4);
end
data(end+1,:) = data(1,:)

plot3(data(:,1), data(:,2), data(:,3),'k.-')
hold off
grid on
view(0,0)  % XY

figure(3)
plot(sqrt(sum(diff(data).^2,2))/length(q1),'k')
hold on
plot(diff(data)/length(q1))
plot(softMultiplier*[5 5], ylim,'k')
hold off
legend('v','dx','dy','dz')


%% Code Generate walker_conf.cpp
fid=fopen('walker_conf.cpp','wt');

fprintf(fid, '/***\n\tWalker Robot configuration file\n\n\tDO NOT EDIT, THIS FILE IS CODE GENERATED\n***/\n\n');
fprintf(fid, '#include "walker_conf.h"\n');
fprintf(fid, '#include <stdint.h>\n\n');
fprintf(fid, ['#define WALKCYCLE_LUT_TABLE_SIZE ' num2str(numel(q1)) '\n\n']);

fprintf(fid, ['int hipCycle(int index, float phase)\n{\n\t']);
str = sprintf('%i,',round(q1*angle2command)');
str = str(1:end-1);
fprintf(fid, ['static const int16_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {' str '};\n']);
fprintf(fid, ['\tindex = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) %% WALKCYCLE_LUT_TABLE_SIZE;\n\treturn lookup[index];\n}\n\n']);


fprintf(fid, ['int kneeCycle(int index, float phase)\n{\n\t']);
str = sprintf('%i,',round(q2*angle2command)');
str = str(1:end-1);
fprintf(fid, ['static const int16_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {' str '};\n']);
fprintf(fid, ['\tindex = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) %% WALKCYCLE_LUT_TABLE_SIZE;\n\treturn lookup[index];\n}\n\n']);

fclose(fid);



















