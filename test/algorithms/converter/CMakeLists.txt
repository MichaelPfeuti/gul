gul_add_test(Converter ImageToBW ColorToBW)

gul_add_test(Converter ImageToGrayscale Luminosity)
gul_add_test(Converter ImageToGrayscale Average)
gul_add_test(Converter ImageToGrayscale Lightness)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestConverter base
                                    image
                                    algorithms_analyzer
                                    algorithms_converter)

