gul_add_test(Converter ImageToSBS SameSize)
gul_add_test(Converter ImageToSBS DifferentSize)

gul_create_test()
target_link_libraries(TestConverter gul)



