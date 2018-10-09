#include "include/config.h"
#include "include/lidar_driver.h"
#include "include/registration_icp_ndt.h"

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}

int main(int argc, char *argv[]) {
    __lidar *lidar = new __lidar;
    __registration_abs *reg = new __registration_icp_ndt;

    static int i = 0;
    static double dx = 0., dy = 0.;

    signal(SIGINT, ctrlc);

    while (true) {

        if (lidar->update_Data()) {
            if(lidar->get_Data().size() && lidar->get_LastData().size()) {
                reg->set_Src_PointCloud(lidar->get_LastData());
                reg->set_Ref_PointCloud(lidar->get_Data());

                reg->update();

                dx += reg->get_dx();
                dy += reg->get_dy();

                cout << "dx: " << dx << " dy: " << dy << endl;      // cm
            }
        }

        i++;
        if (ctrl_c_pressed){
            break;
        }
    }

    delete lidar;
    delete reg;
    return 0;
}
