clear;
clc;
close all;

%% 数据采样
sample_rate = 100;
inte_rate   = 15;

dt = 1. / sample_rate;
tx = 1. / inte_rate;

single_len = floor(tx / dt);



% roll pitch yaw ax ay az
raw = importdata('../acc_dataset_5_100Hz.txt');


roll  = raw(:, 1);
pitch = raw(:, 2);
yaw   = raw(:, 3);
ax    = raw(:, 4);
ay    = raw(:, 5);
az    = raw(:, 6);

len = size(raw, 1);

dt = 1. / sample_rate;
t  = 0 : dt : (size(raw, 1) - 1) * dt;

%% 积分
% 巴特沃滤波器
N=0; % 阶数
Fp=2; % 通带截止频率50Hz
Fc=20; % 阻带截止频率100Hz
Rp=3; % 通带波纹最大衰减为1dB
Rs=60; % 阻带衰减为60dB

% 3.0 计算最小滤波器阶数
na=sqrt(10^(0.1*Rp)-1);
ea=sqrt(10^(0.1*Rs)-1);
N=ceil(log10(ea/na)/log10(Fc/Fp));

Wn= Fp / (sample_rate / 2);
[Bb Ba]=butter(N,Wn,'low'); % 调用MATLAB butter函数快速设计滤波器
[BH,BW]=freqz(Bb,Ba); % 绘制频率响应曲线
Bf=filter(Bb,Ba,ax); % 进行低通滤波
By=fft(Bf,len);  % 对信号f1做len点FFT变换

ax_prefiltered = ax;
ax = Bf;

Wn= Fp / (sample_rate / 2);
[Bb Ba]=butter(N,Wn,'low'); % 调用MATLAB butter函数快速设计滤波器
[BH,BW]=freqz(Bb,Ba); % 绘制频率响应曲线
Bf=filter(Bb,Ba,ay); % 进行低通滤波
By=fft(Bf,len);  % 对信号f1做len点FFT变换

ay_prefiltered = ay;
ay = Bf;

ax = ax .* cosd(pitch);
ay = ay .* cosd(roll);

% t = 0 : dt : (size(raw, 1) - 1) * dt;
% t = t';
% [ dst, vel ] = intfcn_f(ax, t, dt);

filter_len = 511;
for i = 1 : len - filter_len
    
    ax_in = ax(i : i + filter_len, 1);
    t = 0 : dt : filter_len * dt;
    t = t';
    [ dst, vel ] = intfcn_f(ax_in, t, dt);

    vel_out(i, :) = vel(filter_len, :);
    dst_out(i, :) = dst(filter_len, :);
end

vel = [];
vel = vel_out;
dst = [];
dst = dst_out;

t = 0 : dt : (size(dst, 1) - 1) * dt;

%% 作图
subplot(2, 1, 1);
    plot(t, vel, 'b');
    hold on;
    plot(t, ax(filter_len : size(ax, 1) - 1), 'r');    
    %plot(t, ax(1 : size(vel, 1)), 'r');
subplot(2, 1, 2);
    plot(t, vel, 'b');
    hold on;
    plot(t, dst, 'g');    
