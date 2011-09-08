add_executable(testContainers
		TestMain.cpp
		TestArray.cpp
		TestList.cpp
		TestMap.cpp
		TestSet.cpp
		TestStack.cpp
		)
		
add_test(TestArray::SizeAndIsEmpty          testContainers TestArray SizeAndIsEmpty)
add_test(TestArray::Add                     testContainers TestArray Add)
add_test(TestArray::AddIndex                testContainers TestArray AddIndex)
add_test(TestArray::AddIndexAssertion       testContainers TestArray AddIndexAssertion)
add_test(TestArray::RemoveIndex             testContainers TestArray RemoveIndex)
add_test(TestArray::RemoveIndexAssertion    testContainers TestArray RemoveIndexAssertion)
add_test(TestArray::RemoveElement           testContainers TestArray RemoveElement)
add_test(TestArray::RemoveElementAssertion  testContainers TestArray RemoveElementAssertion)
add_test(TestArray::Clear                   testContainers TestArray Clear)
add_test(TestArray::IndexOf                 testContainers TestArray IndexOf)
add_test(TestArray::Contains                testContainers TestArray Contains)

add_test(TestList::SizeAndIsEmpty          testContainers TestList SizeAndIsEmpty)
add_test(TestList::Add                     testContainers TestList Add)
add_test(TestList::AddIndex                testContainers TestList AddIndex)
add_test(TestList::AddIndexAssertion       testContainers TestList AddIndexAssertion)
add_test(TestList::RemoveIndex             testContainers TestList RemoveIndex)
add_test(TestList::RemoveIndexAssertion    testContainers TestList RemoveIndexAssertion)
add_test(TestList::RemoveElement           testContainers TestList RemoveElement)
add_test(TestList::RemoveElementAssertion  testContainers TestList RemoveElementAssertion)
add_test(TestList::Clear                   testContainers TestList Clear)
add_test(TestList::IndexOf                 testContainers TestList IndexOf)
add_test(TestList::Contains                testContainers TestList Contains)

add_test(TestMap testContainers TestMap)
add_test(TestSet testContainers TestSet)
add_test(TestStack testContainers TestStack)
