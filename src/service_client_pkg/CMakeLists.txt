cmake_minimum_required(VERSION 3.0.2)
project(service_client_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  trajectory_by_name_srv
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(simple_service_client src/simple_service_client.cpp)
target_link_libraries(simple_service_client ${catkin_LIBRARIES})

install(TARGETS simple_service_client
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
