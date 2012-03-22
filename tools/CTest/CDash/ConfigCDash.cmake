configure_file(tools/CTest/CDash/Common.ctest.in CDash/Common.ctest @ONLY)

configure_file(tools/CTest/CDash/Experimental/Doxygen.ctest.in             CDash/Experimental/Doxygen.ctest            @ONLY)
configure_file(tools/CTest/CDash/Experimental/CodingConventions.ctest.in   CDash/Experimental/CodingConventions.ctest  @ONLY)
configure_file(tools/CTest/CDash/Experimental/Debug.ctest.in               CDash/Experimental/Debug.ctest              @ONLY)
configure_file(tools/CTest/CDash/Experimental/Release.ctest.in             CDash/Experimental/Release.ctest            @ONLY)
configure_file(tools/CTest/CDash/Experimental/Experimental.ctest.in        CDash/Experimental/Experimental.ctest            @ONLY)

configure_file(tools/CTest/CDash/Continuous/Continuous.ctest.in CDash/Continuous/Continuous.ctest @ONLY)

configure_file(tools/CTest/CDash/Nightly/Nightly.ctest.in CDash/Nightly/Nightly.ctest @ONLY)