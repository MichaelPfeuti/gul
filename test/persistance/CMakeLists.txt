add_executable(testPersistance
		TestMain.cpp
		TestSettingsManager.cpp
		TestXMLLoader.cpp
		TestXMLSaver.cpp
		)
		
add_test(TestSettingsManager testPersistance TestSettingsManager)
add_test(TestXMLLoader testPersistance TestXMLLoader)
add_test(TestXMLSaver testPersistance TestXMLSaver)
