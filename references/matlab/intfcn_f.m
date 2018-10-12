% 积分操作由加速度求位移，可选时域积分和频域积分
function [disint, velint] = intfcn_f(acc, t, ts)
    % 频域积分
    velint =  iomega(acc, ts, 3, 2);
    velint = detrend(velint);
    disint =  iomega(acc, ts, 3, 1);
    % 去除位移中的二次项
    p = polyfit(t, disint, 2);
    disint = disint - polyval(p, t);
end