cmake_minimum_required(VERSION 3.10)

## boost
find_package(Boost REQUIRED)

# pcl
find_package(PCL REQUIRED)

set(PCL_INCLUDE_DIRS /usr/local/include/pcl-1.8)

add_definitions(${PCL_DEFINITIONS})

# lidar sdk
set(lidar_dir
    sdk
)

set(lidar_include_dir
    ${lidar_dir}/include
    ${lidar_dir}/src
)

set(lidar_src
    ${lidar_dir}/src/rplidar_driver.cpp
    ${lidar_dir}/src/arch/linux/net_serial.cpp
    ${lidar_dir}/src/arch/linux/net_socket.cpp
    ${lidar_dir}/src/arch/linux/timer.cpp
    ${lidar_dir}/src/hal/thread.cpp
)

include_directories(
   ${PCL_INCLUDE_DIRS}
   ${lidar_include_dir}
)

add_executable(pcl_test
    ${lidar_src}

    lidar_driver.cpp
    main.cpp
)

target_link_libraries(pcl_test
    ${PCL_LIBRARIES}
)
