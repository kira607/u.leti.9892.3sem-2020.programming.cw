cmake_minimum_required(VERSION 3.15)
project(CourseWork)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

set(TRUCK
    src/db/truck/truck.cpp
    src/db/truck/truck.h
    src/db/truck/truck_list.cpp
    src/db/truck/truck_list.h
    src/db/truck/truck_db.cpp
    src/db/truck/truck_db.h
)

set(SCHEDULE
    src/db/schedule/delivery.cpp
    src/db/schedule/delivery.h
    src/db/schedule/schedule.cpp
    src/db/schedule/schedule.h
    src/db/schedule/schedule_db.cpp
    src/db/schedule/schedule_db.h
)

set(DRIVER
    src/db/driver/driver.cpp
    src/db/driver/driver.h
    src/db/driver/driver_list.cpp
    src/db/driver/driver_list.h
    src/db/driver/driver_db.cpp
    src/db/driver/driver_db.h
)

set(ROUTE
    src/db/route/route.cpp
    src/db/route/route.h
    src/db/route/route_list.cpp
    src/db/route/route_list.h
    src/db/route/route_db.cpp
    src/db/route/route_db.h
)

set(REQUEST_HANDLER
    src/request_handler/request_handler.cpp
    src/request_handler/request_handler.h
)

set(ADMIN
    src/admin/sha256/sha256.cpp
    src/admin/sha256/sha256.h
    src/admin/administrator_console.cpp
    src/admin/administrator_console.h
    src/common/input.cpp
    src/common/input.h
)

set(COMMON
    src/main.cpp
    src/common/truck_brand.cpp
    src/common/truck_brand.h
    src/common/destination.cpp
    src/common/destination.h
    src/common/date.cpp
    src/common/date.h
        src/common/request.h
    src/common/dbs.cpp
    src/common/dbs.h
    src/libs.h
    src/db/libdb.h
)

set(SOURCE_FILES
    ${TRUCK}
    ${ROUTE}
    ${DRIVER}
    ${SCHEDULE}
    ${REQUEST_HANDLER}
    ${COMMON}
    ${ADMIN}
)

add_executable(CourseWork ${SOURCE_FILES})
