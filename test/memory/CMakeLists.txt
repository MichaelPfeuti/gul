add_executable(testMemory
		TestMain.cpp
		TestScopedPtr.cpp
		TestSharedPtr.cpp
		TestUniquePtr.cpp
		TestWeakPtr.cpp
		)
		
add_test(TestScopedPtr testMemory TestScopedPtr)
add_test(TestSharedPtr testMemory TestSharedPtr)
add_test(TestUniquePtr testMemory TestUniquePtr)
add_test(TestWeakPtr testMemory TestWeakPtr)