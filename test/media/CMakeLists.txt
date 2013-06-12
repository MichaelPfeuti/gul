gul_add_test(Media MediaReader FirstFrameMkv)
gul_add_test(Media MediaReader LastFrameMkv)
gul_add_test(Media MediaReader MiddleFrameMkv)
gul_add_test(Media MediaReader FrameCountMkv)

gul_add_test(Media MediaReader FirstFrameMp4)
gul_add_test(Media MediaReader LastFrameMp4)
gul_add_test(Media MediaReader MiddleFrameMp4)
gul_add_test(Media MediaReader FrameCountMp4)

gul_add_test(Media MediaReader FirstFrameAvi)
gul_add_test(Media MediaReader LastFrameAvi)
gul_add_test(Media MediaReader MiddleFrameAvi)
gul_add_test(Media MediaReader FrameCountAvi)

gul_add_test(Media MediaReader FirstFrameMov)
gul_add_test(Media MediaReader LastFrameMov)
gul_add_test(Media MediaReader MiddleFrameMov)
gul_add_test(Media MediaReader FrameCountMov)

gul_add_test(Media MediaReader FirstFrameOgv)
gul_add_test(Media MediaReader LastFrameOgv)
gul_add_test(Media MediaReader MiddleFrameOgv)
gul_add_test(Media MediaReader FrameCountOgv)

gul_add_test(Media MediaReader ReadTwice)

gul_add_test(Media MediaReader ReadMp3Cover)


gul_add_test(Media MediaWriter FirstFrameMkv)
gul_add_test(Media MediaWriter LastFrameMkv)
gul_add_test(Media MediaWriter MiddleFrameMkv)
gul_add_test(Media MediaWriter FrameCountMkv)

gul_add_test(Media MediaWriter FirstFrameMp4)
gul_add_test(Media MediaWriter LastFrameMp4)
gul_add_test(Media MediaWriter MiddleFrameMp4)
gul_add_test(Media MediaWriter FrameCountMp4)

gul_add_test(Media MediaWriter FirstFrameAvi)
gul_add_test(Media MediaWriter LastFrameAvi)
gul_add_test(Media MediaWriter MiddleFrameAvi)
gul_add_test(Media MediaWriter FrameCountAvi)

gul_add_test(Media MediaWriter FirstFrameMov)
gul_add_test(Media MediaWriter LastFrameMov)
gul_add_test(Media MediaWriter MiddleFrameMov)
gul_add_test(Media MediaWriter FrameCountMov)

gul_add_test(Media MediaWriter FirstFrameOgv)
gul_add_test(Media MediaWriter LastFrameOgv)
gul_add_test(Media MediaWriter MiddleFrameOgv)
gul_add_test(Media MediaWriter FrameCountOgv)


gul_add_test(Media MediaConverter CopyMkv)
gul_add_test(Media MediaConverter CopyMp4)
gul_add_test(Media MediaConverter CopyAvi)
gul_add_test(Media MediaConverter CopyMov)
gul_add_test(Media MediaConverter CopyOgv)

gul_add_test(Media MediaConverter Inane2DToSBS)

if(OPENAL_FOUND)
  gul_add_test(Media AudioFrame GetALBuffer)
endif()


gul_create_test()

target_link_libraries(TestMedia gul gulTestUtils)
