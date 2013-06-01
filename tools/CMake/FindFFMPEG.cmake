# Find the FFmpeg library
#
# Sets
#   FFMPEG_INCLUDE_DIR
#   FFMPEG_LIBRARIES

FIND_PATH( FFMPEG_INCLUDE_DIR NAMES ffmpeg/avcodec.h libavcodec/avcodec.h
  /usr/include
  /usr/local/include
)

IF( FFMPEG_INCLUDE_DIR )

  FIND_PROGRAM( FFMPEG_CONFIG ffmpeg-config
    /usr/bin
    /usr/local/bin
    ${HOME}/bin
  )

  IF( FFMPEG_CONFIG )
    EXEC_PROGRAM( ${FFMPEG_CONFIG} ARGS "--libs avformat" OUTPUT_VARIABLE FFMPEG_LIBS )
    SET( FFMPEG_LIBRARIES "${FFMPEG_LIBS}" )

  ELSE( FFMPEG_CONFIG )

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


  ENDIF()

ENDIF()

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFMPEG DEFAULT_MESSAGE FFMPEG_INCLUDE_DIR FFMPEG_LIBRARIES)
