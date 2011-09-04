add_executable(testBase
		TestMain.cpp
    TestAssert.cpp
    TestString.cpp
		)

target_link_libraries(testBase base)
		
add_test(TestAssert testBase TestAssert)

add_test(TestString testBase TestString Concatenation)
