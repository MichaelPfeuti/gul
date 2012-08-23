gul_add_test(Converter ImageToBW StaticExecution)

gul_add_test(Converter ImageToGrayscale StaticExecution)
gul_add_test(Converter ImageToGrayscale Luminosity)
gul_add_test(Converter ImageToGrayscale Average)
gul_add_test(Converter ImageToGrayscale Lightness)

gul_create_test()
target_link_libraries(TestConverter base algorithms_analyzer)

