gul_add_test(Video VideoLoader FirstFrame)
gul_add_test(Video VideoLoader LastFrame)
gul_add_test(Video VideoLoader MiddleFrame)
gul_add_test(Video VideoLoader FrameCount)
gul_add_test(Video VideoLoader ReadMp4)

gul_add_test(Video VideoSaver FirstFrame)
gul_add_test(Video VideoSaver LastFrame)
gul_add_test(Video VideoSaver MiddleFrame)
gul_add_test(Video VideoSaver FrameCount)
gul_add_test(Video VideoSaver WriteReadMp4)

gul_create_test()

target_link_libraries(TestVideo video algorithms_analyzer)
