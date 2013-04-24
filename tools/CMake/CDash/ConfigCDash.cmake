configure_file(${CMAKE_CURRENT_LIST_DIR}/Common.ctest.in CDash/Common.ctest @ONLY)

configure_file(${CMAKE_CURRENT_LIST_DIR}/Experimental/Doxygen.ctest.in             CDash/Experimental/Doxygen.ctest            @ONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/Experimental/CodingConventions.ctest.in   CDash/Experimental/CodingConventions.ctest  @ONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/Experimental/Debug.ctest.in               CDash/Experimental/Debug.ctest              @ONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/Experimental/Release.ctest.in             CDash/Experimental/Release.ctest            @ONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/Experimental/Experimental.ctest.in        CDash/Experimental/Experimental.ctest       @ONLY)

configure_file(${CMAKE_CURRENT_LIST_DIR}/Continuous/Continuous.ctest.in CDash/Continuous/Continuous.ctest @ONLY)

configure_file(${CMAKE_CURRENT_LIST_DIR}/Nightly/Nightly.ctest.in CDash/Nightly/Nightly.ctest @ONLY)