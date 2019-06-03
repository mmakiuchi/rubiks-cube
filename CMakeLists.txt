cmake_minimum_required(VERSION 2.8)
set(PROJ_NAME AR_Tutorial)

project(${PROJ_NAME})

# Create Main project
set(SOURCES
    main.cpp
#    Handson05.cpp
    PoseEstimation.cpp
    MarkerTracker.cpp
)

set(HEADERS
    # main.h
    DrawPrimitives.h
    PoseEstimation.h
    MarkerTracker.h
)

add_executable(${PROJ_NAME}
    ${SOURCES}
    ${HEADERS}
)

set(GLFW_DIR "" CACHE PATH "Path to GLFW" )
set(GLFW_LIB_DIR "" CACHE PATH "Path to GLFW lib" )
set(GLFW_LIBRARIES ${GLFW_LIB_DIR}/glfw3.lib)
#add_subdirectory(${GLFW_DIR})
include_directories(${GLFW_DIR}/include)
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJ_NAME} opengl32 glu32)

# For OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${PROJ_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS})
endif()

# For OpenCV
#find_package(OpenCV REQUIRED)
#if(OpenCV_FOUND)
#    target_include_directories(${PROJ_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
#    target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS})
#endif()

