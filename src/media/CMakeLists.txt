add_library(media OBJECT
  AudioFrame.cpp
  MediaFrame.cpp
  MediaReader.cpp
  MediaWriter.cpp
  VideoFrame.cpp
  MediaConverter.cpp
  manipulator/VideoFrameManipulator.cpp
  manipulator/VFM2DToSBSDelay.cpp

  ${INCLUDE}/media/AudioFrame.h
  ${INCLUDE}/media/manipulator/VFM2DToSBSDelay.h
  ${INCLUDE}/media/manipulator/VideoFrameManipulator.h
  ${INCLUDE}/media/MediaConverter.h
  ${INCLUDE}/media/MediaFrame.h
  ${INCLUDE}/media/MediaReader.h
  ${INCLUDE}/media/MediaWriter.h
  ${INCLUDE}/media/VideoFrame.h
)
