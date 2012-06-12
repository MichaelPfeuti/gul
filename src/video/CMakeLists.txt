###########################
##### FFMPEG Lib #####
###########################
find_package(FFMPEG)
include_directories(${FFMPEG_INCLUDE_DIR})

###########################
##### Video Lib #####
###########################
add_library(video STATIC
    FFMPEG.cpp
    
    ${INCLUDE}/video/FFMPEG.h
)

target_link_libraries(video base)
target_link_libraries(video ${FFMPEG_LIBRARIES})
