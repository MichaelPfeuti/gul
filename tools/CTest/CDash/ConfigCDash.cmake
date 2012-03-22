configure_file(tools/CTest/CDash/Common.ctest.in CDash/Common.ctest @ONLY)

configure_file(tools/CTest/CDash/Experimental/Doxygen.ctest.in             CDash/Experimental/Doxygen.ctest            @ONLY)
configure_file(tools/CTest/CDash/Experimental/CodingConventions.ctest.in   CDash/Experimental/CodingConventions.ctest  @ONLY)
configure_file(tools/CTest/CDash/Experimental/Debug.ctest.in               CDash/Experimental/Debug.ctest              @ONLY)
configure_file(tools/CTest/CDash/Experimental/Release.ctest.in             CDash/Experimental/Release.ctest            @ONLY)

configure_file(tools/CTest/CDash/Continuous/CodingConventions.ctest.in   CDash/Continuous/CodingConventions.ctest  @ONLY)
configure_file(tools/CTest/CDash/Continuous/Debug.ctest.in               CDash/Continuous/Debug.ctest              @ONLY)
configure_file(tools/CTest/CDash/Continuous/Release.ctest.in             CDash/Continuous/Release.ctest            @ONLY)
configure_file(tools/CTest/CDash/Continuous/Continuous.ctest.in             CDash/Continuous/Continuous.ctest            @ONLY)

configure_file(tools/CTest/CDash/Nightly/Doxygen.ctest.in             CDash/Nightly/Doxygen.ctest            @ONLY)
configure_file(tools/CTest/CDash/Nightly/CodingConventions.ctest.in   CDash/Nightly/CodingConventions.ctest  @ONLY)
configure_file(tools/CTest/CDash/Nightly/Debug.ctest.in               CDash/Nightly/Debug.ctest              @ONLY)
configure_file(tools/CTest/CDash/Nightly/Release.ctest.in             CDash/Nightly/Release.ctest            @ONLY)