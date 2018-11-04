#include "include/main_task.h"

/*
 * Rember:
 *  sudo chmod 777 /dev/ttyS1
 *  sudo chmod 777 /dev/ttyUSB0
 */

int  _argc;
char **_argv;

void *ros_main_thread(void *arg);
void *rplidar_main_thread(void *arg);


int main(int argc, char *argv[]) {

    _argc = argc;
    _argv = argv;

    pthread_t ros_main_id, rplidar_main_id;
    int ret;

    ret = pthread_create(&ros_main_id, NULL, ros_main_thread, NULL);
    if(ret != 0) {
        printf ("Create ros thread error!\n");
        exit (1);
    }

    ret = pthread_create(&rplidar_main_id, NULL, rplidar_main_thread, NULL);
    if(ret != 0) {
        printf ("Create rplidar thread error!\n");
        exit (2);
    }

    while (true) {
        sleep(1);
    }

    pthread_join(ros_main_id, NULL);
    pthread_join(rplidar_main_id, NULL);
    return 0;
}

void *ros_main_thread(void *arg) {
    main_ros(_argc, _argv);
}

void *rplidar_main_thread(void *arg) {
    main_rplidar(_argc, _argv);
}
