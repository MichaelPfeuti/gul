gul_add_test(Base Assert Assertion)

gul_add_test(Base String Size)
gul_add_test(Base String Construction)
gul_add_test(Base String Assignment)
gul_add_test(Base String Concatenation)
gul_add_test(Base String PlaceHolder)
gul_add_test(Base String PlaceHolderPrecision)
gul_add_test(Base String ReplaceString)
gul_add_test(Base String ReplaceStringBackward)
gul_add_test(Base String ReplaceStringAll)
gul_add_test(Base String ReplaceRange)
gul_add_test(Base String Substring)
gul_add_test(Base String CharAt)
gul_add_test(Base String Find)
gul_add_test(Base String FindBackward)
gul_add_test(Base String Count)
gul_add_test(Base String LowerCase)
gul_add_test(Base String ToLong)
gul_add_test(Base String ToDouble)
gul_add_test(Base String ToBool)
gul_add_test(Base String Traits)
gul_add_test(Base String RTTI)

gul_add_test(Base ClassFactory CreateClass)
gul_add_test(Base ClassFactory CreateTemplateClass)
gul_add_test(Base ClassFactory CreateAssertion)
gul_add_test(Base ClassFactory CreateSuperClass)

gul_add_test(Base Traits ClassName)
gul_add_test(Base Traits CompositedTemplates)
gul_add_test(Base Traits Primitives)
gul_add_test(Base Traits PrimitivePointers)
gul_add_test(Base Traits DualTemplates)
gul_add_test(Base Traits PointerTypeClassName)

gul_add_test(Base RTTI ClassName)
gul_add_test(Base RTTI ClassNameInheritance)
gul_add_test(Base RTTI CompositedTemplates)
gul_add_test(Base RTTI DualTemplates)

gul_add_test(Base File GetSuffix)

gul_create_test()
target_link_libraries(TestBase base)



