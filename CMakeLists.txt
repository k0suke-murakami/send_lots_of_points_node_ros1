# cmake_minimum_required(VERSION 3.0.2)
# project(send_lots_of_points_node)

# find_package(catkin REQUIRED COMPONENTS
#   geometry_msgs
#   pcl_ros
#   roscpp
#   sensor_msgs
# )

# catkin_package(
# )

# include_directories(
#  ${catkin_INCLUDE_DIRS}
# )

# add_executable(${PROJECT_NAME} src/send_lots_of_points_node_ros1.cpp)

# project(send_lots_of_points_node)

# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   geometry_msgs
#   sensor_msgs
#   pcl_ros
# )

# include_directories(
#   ${catkin_INCLUDE_DIRS}
# )

# add_executable(${PROJECT_NAME} src/send_lots_of_points_node_ros1.cpp)

# target_link_libraries(${PROJECT_NAME}
#   ${catkin_LIBRARIES}
# )

# # Install
# ## executables and libraries
# install(
#   TARGETS
#     ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

# ## project namespaced headers
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
# )

cmake_minimum_required(VERSION 3.0.2)
project(send_lots_of_points_node)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_ros
  roscpp
  sensor_msgs
)


catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    pcl_ros
    sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

# Target
## obstacle_collision_checker_node
add_executable(send_lots_of_points_node
  src/send_lots_of_points_node_ros1.cpp
)

target_link_libraries(send_lots_of_points_node
  ${catkin_LIBRARIES}
)

add_dependencies(send_lots_of_points_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

# Install
## executables and libraries
install(
  TARGETS
    send_lots_of_points_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## project namespaced headers
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
# )

## directories
# install(
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )
