function [ dst, vel ] = sliding_integrate_f(data_in, ts, arr_len_in)

% 核心思想：
% 记录加速度序列，每次以滑动的方式添加一个加速度进来，积分得到速度，这样就可以利用频域，又能单数据更新
% 但是这样速度和位移的积分结果就只和加速度序列有关，而与全局状态无关，这显然是错的——比如如果停止运动，过一段时间加速度会很小，然后速度和位移也会趋于0
% 所以需要让这些参数都和全局有关起来
% 所以同样地记录速度即可

global acc_arr;                     % persistent
global vel_arr;
global arr_len;
global t;

% if size(arr_len_in, 1) == 0
%     arr_len = [];                   % 预留用来复位的，只要arr_len_in输入等于[]，就复位
%     vel_arr = [];
%     acc_arr = [];
%     t       = [];
%     dst = 0;
%     vel = 0;
%     return;
% end

if size(arr_len, 1) == 0            % 是否第一次调用
    arr_len = arr_len_in;
end

if size(acc_arr, 1) == 0            % 如果是第一次调用，则给滑动数列赋空值
    acc_arr = zeros(arr_len, 1);
    vel_arr = zeros(arr_len, 1);
    t = (0 : ts : (arr_len - 1) * ts)';
end

% 如果数据不满，则不进行运算
if acc_arr(size(acc_arr, 1), :) == 0.
    acc_arr(min(find(acc_arr == 0))) = data_in; % 找到最后一个0（未填满）的位置插入数据
    dst = 0; vel = 0;
    return;
end
    
% 正常计算
% 将数据滑动前移一位
for i = 1 : arr_len - 1
    acc_arr(i, :) = acc_arr(i + 1, :);
end
% 最后一位插入新的数据
    acc_arr(arr_len, :) = data_in;
    
% 如果vel序列没有填满则记录vel序列后退出
% 此时加速度已经能计算，那么先根据加速度序列算出速度序列，然后推出
if vel_arr(size(acc_arr, 1), :) == 0.
    vel_arr =  iomega(acc_arr, ts, 3, 2);
    dst = 0; vel = 0;
    return;
end


    
% 积分
    % 频域积分
    % 速度
    velint =  iomega(acc_arr, ts, 3, 2);
    velint =  detrend(velint);
    
    % 将数据滑动前移一位
    for i = 1 : arr_len - 1
        vel_arr(i, :) = vel_arr(i + 1, :);
    end
    % 最后一位插入新的数据
        vel_arr(arr_len, :) = velint(size(velint, 1), :);
    
    %disint =  iomega(acc_arr, ts, 3, 1);
    disint =  iomega(vel_arr, ts, 3, 2);
    % 去除位移中的二次项
    p = polyfit(t, disint, 2);
    disint = disint - polyval(p, t);

 vel = vel_arr(arr_len, :);
 dst = disint(arr_len,  :);
 
end