#ifndef LIDAR_DRIVER_CPP
#define LIDAR_DRIVER_CPP

#include "config.h"
#include "../sdk/include/rplidar.h" //RPLIDAR standard sdk, all-in-one header

using namespace std;
using namespace rp::standalone::rplidar;

enum __lidar_error_list {
    __success         = 0,
    __connect_failed  = 1,
    __lidar_unhealthy = 2,
};

class __lidar {
public:

    __lidar();

    __lidar(char driver_in[]);

    __lidar(char driver_in[], int baud_in);

    ~__lidar();

    __lidar_error_list get_Status()  { return status; }

    vector<__scandot> get_Data()     { return data; }

    vector<__scandot> get_LastData() { return data_last; }

    __lidar_error_list init();

    bool update_Data();

    bool update_Data(vector<__scandot> &getdata);

    bool update_Data(vector<__scandot> &getdata, vector<__scandot> &getdata_last);

protected:

    const char * opt_com_path = NULL;
    _u32         baudrateArray[2] = {115200, 256000};
    _u32         opt_com_baudrate = 0;
    u_result     op_result;

    __lidar_error_list status;

    vector<__scandot> data, data_last;

    RPlidarDriver *drv;

    bool is_Healthy();

    double dst_cloest = 200.;   // mm, within this distance, the data is invalid
};

#endif // LIDAR_DRIVER_CPP
