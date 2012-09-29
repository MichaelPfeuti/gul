###########################
##### FFMPEG Lib #####
###########################
find_package(FFMPEG)
include_directories(${FFMPEG_INCLUDE_DIR})

###########################
##### Video Lib #####
###########################
add_library(video STATIC
  VideoLoader.cpp
  VideoSaver.cpp
  VideoFrame.cpp
    
  ${INCLUDE}/video/VideoSettings.h
  ${INCLUDE}/video/VideoLoader.h
  ${INCLUDE}/video/VideoSaver.h
  ${INCLUDE}/video/VideoFrame.h
)

target_link_libraries(video base image)
target_link_libraries(video ${FFMPEG_LIBRARIES})
