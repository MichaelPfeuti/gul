gul_add_test(Filter ImageToBW GrayToBW)

gul_add_test(Filter ImageToGrayscale Luminosity)
gul_add_test(Filter ImageToGrayscale Average)
gul_add_test(Filter ImageToGrayscale Lightness)

gul_create_test()
target_link_libraries(TestFilter gul gulTestUtils)

