## Toolchain installation
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update 

    sudo apt-get install gcc-7
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 80
    sudo update-alternatives --config gcc

    sudo apt-get install g++-7
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 80
    sudo update-alternatives --config g++

    *special thanks to https://blog.csdn.net/weixin_35762621/article/details/80336291

## To Install
    git clone https://github.com/trigger1996/2018.10.Rplidar_PCL/
    git checkout ros_px4
    git submodule update --init --recursive
