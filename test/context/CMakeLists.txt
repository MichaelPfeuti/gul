if(OPENAL_FOUND)
  gul_add_test(Context ALContext Init)
endif()

gul_create_test()

target_link_libraries(TestContext gul gulTestUtils)
