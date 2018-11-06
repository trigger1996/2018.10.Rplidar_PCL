#include "include/lidar_driver.h"

__lidar::__lidar() {

#ifdef _WIN32
    // use default com port
    opt_com_path = "\\\\.\\com3";
#else
    opt_com_path = "/dev/ttyUSB0";
#endif
    opt_com_baudrate = 0;

    status = init();
}

__lidar::__lidar(char driver_in[]) {
    opt_com_path = (const char *)driver_in;
    opt_com_baudrate = 0;

    status = init();
}

__lidar::__lidar(char driver_in[], int baud_in) {
    opt_com_path = (const char *)driver_in;
    opt_com_baudrate = baud_in;

    status = init();
}

__lidar::~__lidar() {

    drv->stop();
    drv->stopMotor();
    RPlidarDriver::DisposeDriver(drv);
    drv = NULL;
}

__lidar_error_list __lidar::init() {

    printf("Ultra simple LIDAR data grabber for RPLIDAR.\n"
            "Version: "RPLIDAR_SDK_VERSION"\n");

    rplidar_response_device_info_t devinfo;
    bool connectSuccess = false;
    // make connection...
    if (opt_com_baudrate == 0) {
        size_t baudRateArraySize = (sizeof(baudrateArray))/ (sizeof(baudrateArray[0]));
        for(size_t i = 0; i < baudRateArraySize; ++i) {
            if(!drv)
                drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
            if(IS_OK(drv->connect(opt_com_path, baudrateArray[i]))) {
                op_result = drv->getDeviceInfo(devinfo);

                if (IS_OK(op_result)) {
                    connectSuccess = true;
                    break;
                }
                else {
                    delete drv;
                    drv = NULL;
                }
            }
        }
    }
    else {
        if(!drv)
            drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
        if (IS_OK(drv->connect(opt_com_path, opt_com_baudrate))) {
            op_result = drv->getDeviceInfo(devinfo);

            if (IS_OK(op_result)) {
                connectSuccess = true;
            }
            else {
                delete drv;
                drv = NULL;
            }
        }
    }
    if (!connectSuccess) {
        fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
            , opt_com_path);
        return __connect_failed;
    }

    // print out the device serial number, firmware and hardware version number..
    printf("RPLIDAR S/N: ");
    for (int pos = 0; pos < 16 ;++pos) {
        printf("%02X", devinfo.serialnum[pos]);
    }

    printf("\n"
            "Firmware Ver: %d.%02d\n"
            "Hardware Rev: %d\n"
            , devinfo.firmware_version>>8
            , devinfo.firmware_version & 0xFF
            , (int)devinfo.hardware_version);



    // check health...
    if (!is_Healthy()) {
        return __lidar_unhealthy;
    }

    drv->startMotor();
    // start scan...
    //drv->startScan(0,1);
    drv->startScanExpress(0, RPLIDAR_CONF_SCAN_COMMAND_HQ);     // RPLIDAR_CONF_SCAN_COMMAND_EXPRESS

    return __success;
}

bool __lidar::update_Data() {
    rplidar_response_measurement_node_hq_t nodes[8192];
    size_t   count = _countof(nodes);

    op_result = drv->grabScanDataHq(nodes, count);

    if (IS_OK(op_result)) {
        drv->ascendScanData(nodes, count);

        data_last.clear();
        data_last = data;
        data.clear();
        for (int pos = 0; pos < (int)count ; ++pos) {
            __scandot temp;
            temp.angle    =  nodes[pos].angle_z_q14 * 90.f / (1 << 14);
            temp.dst      =  nodes[pos].dist_mm_q2 / (1 << 2);                              // mm
            temp.quality  =  nodes[pos].quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;
            temp.is_start = (nodes[pos].flag & RPLIDAR_RESP_MEASUREMENT_SYNCBIT);
//            if (!temp.quality)        // 这个加了后面NDT会爆炸
//                continue;
            data.push_back(temp);

//                printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
//                    temp.is_start ?"S ":"  ",
//                    temp.angle,
//                    temp.dst,
//                    temp.quality);
        }
        return true;
    }
    return false;
}

bool __lidar::update_Data(vector<__scandot> &getdata) {
    update_Data();
    getdata = data;
}

bool __lidar::update_Data(vector<__scandot> &getdata, vector<__scandot> &getdata_last) {
    update_Data();
    getdata      = data;
    getdata_last = data_last;
}



bool __lidar::is_Healthy() {
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;

    op_result = drv->getHealth(healthinfo);
    if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
        printf("RPLidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
            fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want rplidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}
