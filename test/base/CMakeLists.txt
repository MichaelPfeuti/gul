add_executable(testBase
		TestMain.cpp
    TestAssert.cpp
    TestString.cpp
		)

target_link_libraries(testBase base memory)
		
add_test(TestAssert testBase TestAssert)

add_test(TestString testBase TestString Concatenation)
add_test(TestString testBase TestString PlaceHolder)
add_test(TestString testBase TestString ReplaceString)
add_test(TestString testBase TestString ReplaceRange)

