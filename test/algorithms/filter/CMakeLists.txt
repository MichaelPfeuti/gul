gul_add_test(Filter ImageToBW ColorToBW)

gul_add_test(Filter ImageToGrayscale Luminosity)
gul_add_test(Filter ImageToGrayscale Average)
gul_add_test(Filter ImageToGrayscale Lightness)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestFilter base
                                    image
                                    algorithms_analyzer
                                    algorithms_filter)

