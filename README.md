## Toolchain installation
    ### For Ubuntu 18
        Tested, no need to change anything.
    ### For Ubuntu 16
        Tested on a Intel Up board
        Do as follows:

            sudo add-apt-repository ppa:ubuntu-toolchain-r/test
            sudo apt-get update

            sudo apt-get install gcc-7
            sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 80
            sudo update-alternatives --config gcc

            sudo apt-get install g++-7
            sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 80
            sudo update-alternatives --config g++

        Then Compile pcl 1.8.0
            git clone https://github.com/pointcloudlibrary/pcl
            git checkout pcl-1.8.0
            cd pcl
            mkdir build
            cd build
            cmake ..
            make
            sudo make install

        When Testing...
            sudo chmod 777 /dev/ttyUSB0
            sudo chmod 777 /dev/ttyS1

            Added 1.8 requirement on CMakeLists.txt
                find_package(PCL REQUIRED) --> find_package(PCL 1.8 REQUIRED)
            * I've tried these 3 times until its success...
            * special thanks to https://blog.csdn.net/weixin_35762621/article/details/80336291

    ## For Debian stretch
        Tested on win10 subsystem(Debian)
        In this platform, PCL is not successfully compiled so apt-get install is used to fetch PCL library.

            Added Qt libraries in CMakeLists.txt
            * special thanks to https://www.jianshu.com/p/7eeb6f79a275

## To Install
    git clone https://github.com/trigger1996/2018.10.Rplidar_PCL/
    git checkout ros_px4
    git submodule update --init --recursive
