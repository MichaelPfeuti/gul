add_library(video OBJECT
  VideoLoader.cpp
  VideoSaver.cpp
  VideoFrame.cpp
  VideoConverter.cpp
  manipulator/VideoFrameManipulator.cpp
  manipulator/VFM2DToSBSDelay.cpp
    
  ${INCLUDE}/video/VideoLoader.h
  ${INCLUDE}/video/VideoSaver.h
  ${INCLUDE}/video/VideoFrame.h
  ${INCLUDE}/video/VideoConverter.h
  ${INCLUDE}/video/manipulator/VideoFrameManipulator.h
  ${INCLUDE}/video/manipulator/VFM2DToSBSDelay.h
)
