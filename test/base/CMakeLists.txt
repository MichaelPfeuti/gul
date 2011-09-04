add_executable(testBase
		TestMain.cpp
		TestAssert.cpp
		TestString.cpp
		)
		
add_test(TestAssert testBase TestAssert)
add_test(TestString testBase TestString)