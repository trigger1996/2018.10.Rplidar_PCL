#ifndef NED_2_LAT_LON_HPP
#define NED_2_LAT_LON_HPP

#include "config.h"
#include <math.h>

#define LON_INIT (double)118.2300000
#define LAT_INIT (double)24.6200000


static inline void ned_2_lat_lon(double x_in, double y_in, double z_in,
                                 double &lat, double &lon, double &alt) {
    // x->m y->m alt->m
    // 先求出起始点的墨卡托投影
    static double x_init = LON_INIT * 20037508.3427892 / 180.;
    static double y_init = log(tan(90. + LAT_INIT) * M_PI / 360.) / (double)(M_PI / 180.);
    y_init = y_init * 20037508.3427892 / 180.;

    // 墨卡托投影加上当前值
    double x = y_in + x_init;
    double y = x_in + y_init;

    // 墨卡托投影转回经纬度
    lon = x / 20037508.3427892 * 180.;
    lat = y / 20037508.3427892 * 180.;
    lat = (double)180. / M_PI * (2 * atan(exp(lat * M_PI / (double)180.)) - M_PI / (double)2.);

    alt = z_in;
}

#endif // NED_2_LAT_LON_HPP

