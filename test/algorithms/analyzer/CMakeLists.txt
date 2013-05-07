gul_add_test(Analyzer ImageEquality Equality)
gul_add_test(Analyzer ImageEquality Inequality)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestAnalyzer gul)



