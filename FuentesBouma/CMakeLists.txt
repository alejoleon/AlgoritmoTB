
cmake_minimum_required(VERSION 2.8)
 
project(AlgoritmoBouma)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#find_package(QT4 REQUIRED)
#include(${QT_USE_FILE})

# Set your files and resources here
FILE(GLOB AlgoritmoBoumaSources "${PROJECT_SOURCE_DIR}/*.cpp")
FILE(GLOB AlgoritmoBoumaHeaders "${PROJECT_SOURCE_DIR}/*.h")

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

#add_executable(Bouma Bouma.cpp)

ADD_EXECUTABLE(
  Bouma 
  ${AlgoritmoBoumaSources}
  )

target_link_libraries(Bouma
${VTK_LIBRARIES} ${ITK_LIBRARIES})
#${QT_LIBRARIES}
