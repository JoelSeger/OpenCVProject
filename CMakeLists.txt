cmake_minimum_required(VERSION 3.16)
project(camera_grab LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Locate OpenCV installation
find_package(OpenCV REQUIRED)
# All application sources live in src/
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
# Build main.cpp as an executable
add_executable(camera_grab ${SRC_DIR}/main.cpp
        ${SRC_DIR}/CameraInput.cpp
        ${SRC_DIR}/CameraInput.h
        ${SRC_DIR}/RegionAnalyzer.cpp
        ${SRC_DIR}/ContourDetection.cpp
        ${SRC_DIR}/ContourDetection.h
        ${SRC_DIR}/LineEstimation.cpp
        ${SRC_DIR}/LineEstimation.h
        ${SRC_DIR}/IsValidQuad.cpp
        ${SRC_DIR}/IsValidQuad.h
        ${SRC_DIR}/MarkerRecognizer.cpp
        ${SRC_DIR}/MarkerRecognizer.h
        ${SRC_DIR}/PoseEstimator.cpp
        ${SRC_DIR}/PoseEstimator.h
        ${SRC_DIR}/InteractionMapping.h
        ${SRC_DIR}/InteractionMapping.cpp
        ${SRC_DIR}/LampRenderer.cpp
        ${SRC_DIR}/LampRenderer.h)
# Give the program access to OpenCV headers and libraries.
target_include_directories(camera_grab PRIVATE ${SRC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(camera_grab PRIVATE ${OpenCV_LIBS})

# Unit tests for RegionAnalyzer. ctest || ./test_region_analyzer
enable_testing()
add_executable(test_region_analyzer tests/test_region_analyzer.cpp ${SRC_DIR}/RegionAnalyzer.cpp)
target_include_directories(test_region_analyzer PRIVATE ${SRC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test_region_analyzer PRIVATE ${OpenCV_LIBS})
add_test(NAME region_analyzer COMMAND test_region_analyzer)

# Test for Marker Recognizer
add_executable(test_marker_recognizer tests/test_marker_recognizer.cpp ${SRC_DIR}/MarkerRecognizer.cpp)
target_include_directories(test_marker_recognizer PRIVATE ${SRC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test_marker_recognizer PRIVATE ${OpenCV_LIBS})
add_test(NAME marker_recognizer COMMAND test_marker_recognizer)

# Test for CameraInput (end of stream vs dropped frames)
add_executable(test_camera_input tests/test_camera_input.cpp ${SRC_DIR}/CameraInput.cpp)
target_include_directories(test_camera_input PRIVATE ${SRC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test_camera_input PRIVATE ${OpenCV_LIBS})
add_test(NAME camera_input COMMAND test_camera_input)

# Test for InteractionMapping (marker angle to lamp brightness)
add_executable(test_interaction_mapping tests/test_interaction_mapping.cpp ${SRC_DIR}/InteractionMapping.cpp)
target_include_directories(test_interaction_mapping PRIVATE ${SRC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test_interaction_mapping PRIVATE ${OpenCV_LIBS})
add_test(NAME interaction_mapping COMMAND test_interaction_mapping)
