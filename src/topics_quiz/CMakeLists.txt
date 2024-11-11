cmake_minimum_required(VERSION 3.0.2)
project(topics_quiz)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(topics_quiz_node src/topics_quiz_node.cpp)

target_link_libraries(topics_quiz_node
  ${catkin_LIBRARIES}
)
