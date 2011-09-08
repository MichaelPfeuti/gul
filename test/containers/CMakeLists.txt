add_executable(testContainers
		TestMain.cpp
		TestArray.cpp
		TestList.cpp
		TestMap.cpp
		TestSet.cpp
		TestStack.cpp
		)
		
add_test(TestArray testContainers TestArray SizeAndIsEmpty)
add_test(TestArray testContainers TestArray Add)
add_test(TestArray testContainers TestArray AddIndex)
add_test(TestArray testContainers TestArray AddIndexAssertion)
add_test(TestArray testContainers TestArray RemoveIndex)
add_test(TestArray testContainers TestArray RemoveIndexAssertion)
add_test(TestArray testContainers TestArray RemoveElement)
add_test(TestArray testContainers TestArray RemoveElementAssertion)
add_test(TestArray testContainers TestArray Clear)
add_test(TestArray testContainers TestArray IndexOf)
add_test(TestArray testContainers TestArray Contains)


add_test(TestList testContainers TestList)
add_test(TestMap testContainers TestMap)
add_test(TestSet testContainers TestSet)
add_test(TestStack testContainers TestStack)
