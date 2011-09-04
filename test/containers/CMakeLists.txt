add_executable(testContainers
		TestMain.cpp
		TestArray.cpp
		TestList.cpp
		TestMap.cpp
		TestSet.cpp
		TestStack.cpp
		)
		
add_test(TestArray testContainers TestArray)
add_test(TestList testContainers TestList)
add_test(TestMap testContainers TestMap)
add_test(TestSet testContainers TestSet)
add_test(TestStack testContainers TestStack)
