add_library(persistance SHARED 
		SettingsManager.cpp
		XMLLoader.cpp
		XMLSaver.cpp
		)
		
target_link_libraries(persistance nvwa)