gul_add_test(Video VideoLoader FirstFrameMkv)
gul_add_test(Video VideoLoader LastFrameMkv)
gul_add_test(Video VideoLoader MiddleFrameMkv)
gul_add_test(Video VideoLoader FrameCountMkv)

gul_add_test(Video VideoLoader FirstFrameMp4)
gul_add_test(Video VideoLoader LastFrameMp4)
gul_add_test(Video VideoLoader MiddleFrameMp4)
gul_add_test(Video VideoLoader FrameCountMp4)

gul_add_test(Video VideoLoader FirstFrameAvi)
gul_add_test(Video VideoLoader LastFrameAvi)
gul_add_test(Video VideoLoader MiddleFrameAvi)
gul_add_test(Video VideoLoader FrameCountAvi)

gul_add_test(Video VideoLoader FirstFrameMov)
gul_add_test(Video VideoLoader LastFrameMov)
gul_add_test(Video VideoLoader MiddleFrameMov)
gul_add_test(Video VideoLoader FrameCountMov)

gul_add_test(Video VideoLoader FirstFrameOgv)
gul_add_test(Video VideoLoader LastFrameOgv)
gul_add_test(Video VideoLoader MiddleFrameOgv)
gul_add_test(Video VideoLoader FrameCountOgv)

gul_add_test(Video VideoLoader ReadTwice)


gul_add_test(Video VideoSaver FirstFrameMkv)
gul_add_test(Video VideoSaver LastFrameMkv)
gul_add_test(Video VideoSaver MiddleFrameMkv)
gul_add_test(Video VideoSaver FrameCountMkv)

gul_add_test(Video VideoSaver FirstFrameMp4)
gul_add_test(Video VideoSaver LastFrameMp4)
gul_add_test(Video VideoSaver MiddleFrameMp4)
gul_add_test(Video VideoSaver FrameCountMp4)

gul_add_test(Video VideoSaver FirstFrameAvi)
gul_add_test(Video VideoSaver LastFrameAvi)
gul_add_test(Video VideoSaver MiddleFrameAvi)
gul_add_test(Video VideoSaver FrameCountAvi)

gul_add_test(Video VideoSaver FirstFrameMov)
gul_add_test(Video VideoSaver LastFrameMov)
gul_add_test(Video VideoSaver MiddleFrameMov)
gul_add_test(Video VideoSaver FrameCountMov)

gul_add_test(Video VideoSaver FirstFrameOgv)
gul_add_test(Video VideoSaver LastFrameOgv)
gul_add_test(Video VideoSaver MiddleFrameOgv)
gul_add_test(Video VideoSaver FrameCountOgv)


gul_add_test(Video VideoConverter CopyMkv)
gul_add_test(Video VideoConverter CopyMp4)
gul_add_test(Video VideoConverter CopyAvi)
gul_add_test(Video VideoConverter CopyMov)
gul_add_test(Video VideoConverter CopyOgv)

gul_add_test(Video VideoConverter Inane2DToSBS)


gul_create_test()

target_link_libraries(TestVideo video algorithms_analyzer algorithms_converter)
