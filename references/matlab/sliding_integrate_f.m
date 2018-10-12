function [ dst_x, dst_y, vel_x, vel_y ] = sliding_integrate_f(ax_in, ay_in, ts, arr_len_in)

% 核心思想：
% 记录加速度序列，每次以滑动的方式添加一个加速度进来，积分得到速度，这样就可以利用频域，又能单数据更新
% 但是这样速度和位移的积分结果就只和加速度序列有关，而与全局状态无关，这显然是错的——比如如果停止运动，过一段时间加速度会很小，然后速度和位移也会趋于0
% 所以需要让这些参数都和全局有关起来
% 所以同样地记录速度即可

global acc_x_arr;                                       % persistent
global acc_y_arr;                        
global vel_x_arr;
global vel_y_arr;
global arr_len;
global t;

% if size(arr_len_in, 1) == 0
%     arr_len = [];                                       % 预留用来复位的，只要arr_len_in输入等于[]，就复位
%     vel_x_arr = []; vel_y_arr = [];                     % 编译的时候记得注释掉这个，用不上，还会造成编译错误
%     acc_x_arr = []; acc_y_arr = [];
%     t         = [];
%     dst_x = 0;      dst_y = 0;
%     vel_x = 0;      vel_y = 0;
%     return;
% end

if size(arr_len, 1) == 0                                % 是否第一次调用
    arr_len = arr_len_in;
end

if size(acc_x_arr, 1) == 0 || size(acc_y_arr, 1) == 0	% 如果是第一次调用，则给滑动数列赋空值
    acc_x_arr = zeros(arr_len, 1);	acc_y_arr = zeros(arr_len, 1);
    vel_x_arr = zeros(arr_len, 1);	vel_y_arr = zeros(arr_len, 1);
    t = (0 : ts : (arr_len - 1) * ts)';
end

% 如果数据不满，则不进行运算
if acc_x_arr(size(acc_x_arr, 1), :) == 0. || acc_y_arr(size(acc_y_arr, 1), :) == 0.
    acc_x_arr(min(find(acc_x_arr == 0))) = ax_in;       % 找到最后一个0（未填满）的位置插入数据
    acc_y_arr(min(find(acc_y_arr == 0))) = ay_in;
    dst_x = 0;      dst_y = 0;
    vel_x = 0;      vel_y = 0;
    return;
end
    
% 正常计算
% 将数据滑动前移一位
for i = 1 : arr_len - 1
    acc_x_arr(i, :) = acc_x_arr(i + 1, :);
    acc_y_arr(i, :) = acc_y_arr(i + 1, :);
end
% 最后一位插入新的数据
    acc_x_arr(arr_len, :) = ax_in;
    acc_y_arr(arr_len, :) = ay_in;    
    
% 如果vel序列没有填满则记录vel序列后退出
% 此时加速度已经能计算，那么先根据加速度序列算出速度序列，然后推出
if vel_x_arr(size(vel_x_arr, 1), :) == 0. || vel_y_arr(size(vel_y_arr, 1), :) == 0.
    vel_x_arr =  iomega(acc_x_arr, ts, 3, 2);
    vel_y_arr =  iomega(acc_y_arr, ts, 3, 2);    
    dst_x = 0;      dst_y = 0;
    vel_x = 0;      vel_y = 0;
    return;
end


    
% 积分
    % 频域积分
    % 速度
    vel_x_int =  iomega(acc_x_arr, ts, 3, 2);
    vel_x_int =  detrend(vel_x_int);
    vel_y_int =  iomega(acc_y_arr, ts, 3, 2);
    vel_y_int =  detrend(vel_y_int);    
    
    % 将数据滑动前移一位
    for i = 1 : arr_len - 1
        vel_x_arr(i, :) = vel_x_arr(i + 1, :);
        vel_y_arr(i, :) = vel_y_arr(i + 1, :);        
    end
    % 最后一位插入新的数据
        vel_x_arr(arr_len, :) = vel_x_int(size(vel_x_int, 1), :);
        vel_y_arr(arr_len, :) = vel_y_int(size(vel_y_int, 1), :);    
        
    %disint =  iomega(acc_arr, ts, 3, 1);
    dis_x_int =  iomega(vel_x_arr, ts, 3, 2);
    % 去除位移中的二次项
    px = polyfit(t, dis_x_int, 2);
    dis_x_int = dis_x_int - polyval(px, t);
    
    %disint =  iomega(acc_arr, ts, 3, 1);
    dis_y_int =  iomega(vel_y_arr, ts, 3, 2);
    % 去除位移中的二次项
    py = polyfit(t, dis_y_int, 2);
    dis_y_int = dis_y_int - polyval(py, t);
    

dst_x = dis_x_int(arr_len, :);      dst_y = dis_y_int(arr_len, :);
vel_x = vel_x_arr(arr_len, :);      vel_y = vel_y_arr(arr_len, :);
end