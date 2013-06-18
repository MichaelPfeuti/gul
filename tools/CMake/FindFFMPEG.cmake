# Find the FFmpeg library
#
# Sets
#   FFMPEG_INCLUDE_DIR
#   FFMPEG_LIBRARIES

FIND_PATH( FFMPEG_INCLUDE_DIR NAMES ffmpeg/avcodec.h libavcodec/avcodec.h
  /usr/include
  /usr/local/include
)

FIND_LIBRARY( FFMPEG_avcodec_LIBRARY avcodec
  /usr/lib
  /usr/local/lib
  /usr/lib64
  /usr/local/lib64
)

FIND_LIBRARY( FFMPEG_avformat_LIBRARY avformat
  /usr/lib
  /usr/local/lib
  /usr/lib64
  /usr/local/lib64
)

FIND_LIBRARY( FFMPEG_avutil_LIBRARY avutil
  /usr/lib
  /usr/local/lib
  /usr/lib64
  /usr/local/lib64
)

FIND_LIBRARY( FFMPEG_swscale_LIBRARY swscale
  /usr/lib
  /usr/local/lib
  /usr/lib64
  /usr/local/lib64
)

FIND_LIBRARY( FFMPEG_swresample_LIBRARY swresample
  /usr/lib
  /usr/local/lib
  /usr/lib64
  /usr/local/lib64
)

IF( FFMPEG_avcodec_LIBRARY )
  SET( FFMPEG_LIBRARIES ${FFMPEG_avcodec_LIBRARY} )
ENDIF()

IF( FFMPEG_avformat_LIBRARY )
  SET( FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${FFMPEG_avformat_LIBRARY} )
ENDIF()

IF( FFMPEG_avutil_LIBRARY )
   SET( FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${FFMPEG_avutil_LIBRARY} )
ENDIF()

IF( FFMPEG_swscale_LIBRARY )
   SET( FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${FFMPEG_swscale_LIBRARY} )
ENDIF()

IF( FFMPEG_swresample_LIBRARY )
   SET( FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${FFMPEG_swresample_LIBRARY} )
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set FFMPEG_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFMPEG DEFAULT_MSG FFMPEG_LIBRARIES FFMPEG_INCLUDE_DIR)

mark_as_advanced(FFMPEG_avcodec_LIBRARY
                 FFMPEG_avformat_LIBRARY
                 FFMPEG_avutil_LIBRARY
                 FFMPEG_swscale_LIBRARY
                 FFMPEG_swresample_LIBRARY
                 FFMPEG_INCLUDE_DIR)
