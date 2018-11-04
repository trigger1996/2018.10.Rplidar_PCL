#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <cmath>

using namespace std;

static double limit_Data(double in, double limit) {
    if (limit < 0)
        limit = -limit;

    if (in > limit)
        return limit;
    else if (in < -limit)
        return -limit;
    else
        return in;
}

class __control_pid {
public:

    __control_pid() {
        init(0., 0., 0., 0., 1.);
    }

    __control_pid(double _kp, double _ki, double _kd, double _inte_limit, double _samp_rate) {
        init(_kp, _ki, _kd, _inte_limit, _samp_rate);
    }

    void init(double _kp, double _ki, double _kd, double _inte_limit, double _samp_rate) {
        kp = _kp;
        ki = _ki;
        kd = _kd;
        inte_limit = _inte_limit;
        samp_rate  = _samp_rate;
        dt = 1. / samp_rate;

        reset();
    }

    void set_KP(double in) { kp = in; }
    void set_KI(double in) { ki = in; }
    void set_KD(double in) { kd = in; }

    void set_Integration_Limit(double in) { inte_limit = in; }
    void set_Sample_Rate(double in) {
        samp_rate = in;
        dt = 1. / samp_rate;
    }

    void update_Data(double in) {
        data_last = data;
        data = in;
    }

    double get_P(double data_in, double exp_in) {
        data_last = data;
        data = data_in;
        return kp * (exp_in - data);
    }

    double get_PI(double data_in, double exp_in) {
        data_last = data;
        data = data_in;
        data_inte += data;

        return kp * (exp_in - data) + limit_Data(ki * data_inte, inte_limit);
    }

    double get_PD(double data_in, double exp_in) {
        data_last = data;
        data = data_in;

        return kp * (exp_in - data) + kd * (data - data_last) / dt;
    }

    double get_PID(double data_in, double exp_in) {
        data_last = data;
        data = data_in;
        data_inte += data;

        return kp * (exp_in - data) + limit_Data(ki * data_inte, inte_limit) + kd * (data - data_last) / dt;
    }

    void reset() {
        data = data_last = 0;
        data_inte = 0.;
    }

private:
    double kp, ki, kd;

    double data, data_last;
    double data_inte;

    double inte_limit;
    double samp_rate, dt;

};

#endif // CONTROL_HPP
