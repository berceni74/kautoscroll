cmake_minimum_required(VERSION 3.31)
project(kautoscroll)

find_package(PkgConfig REQUIRED)
pkg_check_modules(EVDEV REQUIRED libevdev)

add_executable(kautoscroll
    main.c
    getMouse.c
    virtMouse.c
    getCtrl.c
)

target_link_libraries(kautoscroll PRIVATE ${EVDEV_LINK_LIBRARIES})