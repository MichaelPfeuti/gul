add_executable(testContainers
		TestMain.cpp
		TestArray.cpp
		TestList.cpp
		TestMap.cpp
		TestSet.cpp
		TestStack.cpp
		)

target_link_libraries(testContainers containers base nvwa)
		
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

add_test(TestMap::SizeAndIsEmpty  testContainers TestMap SizeAndIsEmpty)
add_test(TestMap::Add             testContainers TestMap Add)
add_test(TestMap::Remove          testContainers TestMap Remove)
add_test(TestMap::RemoveAssertion testContainers TestMap RemoveAssertion)
add_test(TestMap::Get             testContainers TestMap Get)
add_test(TestMap::GetAssertion    testContainers TestMap GetAssertion)
add_test(TestMap::Clear           testContainers TestMap Clear)
add_test(TestMap::Contains        testContainers TestMap Contains)
add_test(TestMap::GetKeys         testContainers TestMap GetKeys)
add_test(TestMap::GetValues       testContainers TestMap GetValues)

add_test(TestSet::SizeAndIsEmpty  testContainers TestSet SizeAndIsEmpty)
add_test(TestSet::Add             testContainers TestSet Add)
add_test(TestSet::Remove          testContainers TestSet Remove)
add_test(TestSet::RemoveAssertion testContainers TestSet RemoveAssertion)
add_test(TestSet::Clear           testContainers TestSet Clear)
add_test(TestSet::Contains        testContainers TestSet Contains)

add_test(TestStack::SizeAndIsEmpty  testContainers TestStack SizeAndIsEmpty)
add_test(TestStack::Top             testContainers TestStack Top)
add_test(TestStack::TopAssertion    testContainers TestStack TopAssertion)
add_test(TestStack::Pop             testContainers TestStack Pop)
add_test(TestStack::PopAssertion    testContainers TestStack PopAssertion)
add_test(TestStack::Push            testContainers TestStack Push)
add_test(TestStack::Clear           testContainers TestStack Clear)

