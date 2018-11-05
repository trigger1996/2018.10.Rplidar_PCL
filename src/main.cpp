#include "include/main_task.h"


/*
 * Remeber:
 *  sudo chmod 777 /dev/ttyS1
 *  sudo chmod 777 /dev/ttyUSB0
 *
 * About CPU Lock:
 *  http://blog.jobbole.com/107334/
 */

int  _argc;
char **_argv;

void *ros_main_thread(void *arg);
void *rplidar_main_thread(void *arg);


int main(int argc, char *argv[]) {
    _argc = argc;
    _argv = argv;

    int cpu_num = 0;
    cpu_num  = (int)sysconf(_SC_NPROCESSORS_CONF);  // get_cpu_count
    if (cpu_num < 2) {
        cout << "cpu core num demand not reached!" << endl;
        exit(-1);
    }

    pthread_t ros_main_id, rplidar_main_id;
    pthread_attr_t ros_main_attr, rplidar_main_attr;
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
    cpu_set_t mask, get;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
        fprintf(stderr, "set thread affinity failed\n");
    }
    CPU_ZERO(&get);
    if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
        fprintf(stderr, "get thread affinity failed\n");
    }

    main_ros(_argc, _argv);

    pthread_exit(NULL);
}

void *rplidar_main_thread(void *arg) {
    cpu_set_t mask, get;
    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
        fprintf(stderr, "set thread affinity failed\n");
    }
    CPU_ZERO(&get);
    if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
        fprintf(stderr, "get thread affinity failed\n");
    }

    main_rplidar(_argc, _argv);

    pthread_exit(NULL);
}
