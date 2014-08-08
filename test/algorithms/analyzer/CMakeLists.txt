gul_add_test(Analyzer ImageEquality Equality)
gul_add_test(Analyzer ImageEquality InequalityData)
gul_add_test(Analyzer ImageEquality InequalityFormat)

gul_create_test()
target_link_libraries(TestAnalyzer gul gulTestUtils)



