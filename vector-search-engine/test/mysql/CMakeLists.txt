cmake_minimum_required(VERSION 3.27)
project(mysql-test)

#find_package(mysql-concpp REQUIRED ${REQUIRED_COMPONENTS})
include_directories(/usr/local/mysql/connector-c++-8.0.33/include/)
link_directories(/usr/local/mysql/connector-c++-8.0.33/lib64)

add_executable(mysql-test mysql-test.cpp)
target_link_libraries(mysql-test mysqlcppconn)