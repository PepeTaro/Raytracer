cmake_minimum_required(VERSION 3.10)

project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sfml sfml.cpp ../src/raytracer.cpp ../src/vector3.cpp ../src/camera.cpp ../src/sphere.cpp ../src/triangle.cpp ../src/color.cpp ../src/light.cpp)
target_include_directories(sfml PRIVATE ../include/)
target_link_libraries(sfml LINK_PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(test_vector3 test_vector3.cpp ../src/vector3.cpp)
target_include_directories(test_vector3 PRIVATE ../include/)

add_executable(test_camera test_camera.cpp ../src/vector3.cpp ../src/camera.cpp)
target_include_directories(test_camera PRIVATE ../include/)

add_executable(test_raytracer test_raytracer.cpp ../src/raytracer.cpp ../src/vector3.cpp ../src/camera.cpp)
target_include_directories(test_raytracer PRIVATE ../include/)
