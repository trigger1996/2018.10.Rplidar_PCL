#include "include/config.h"
#include "include/lidar_driver.h"

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

int main(int argc, char *argv[]) {
    __lidar *lidar = new __lidar;

    if (lidar->get_Status() != __success) {
        return -1;
    }

    signal(SIGINT, ctrlc);

    while (true) {

        lidar->update_Data();

        if (ctrl_c_pressed){
            break;
        }
    }

    delete lidar;
    return 0;
}
