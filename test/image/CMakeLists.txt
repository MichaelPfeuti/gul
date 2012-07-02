gul_add_test(Image JPEG_IO ReadWrite)

gul_add_test(Image PNG_IO ReadWrite)

gul_add_test(Image PPM_IO ReadWriteRGBASCII)
gul_add_test(Image PPM_IO ReadWriteRGBBinary)
gul_add_test(Image PPM_IO ReadWriteGreyscaleASCII)
gul_add_test(Image PPM_IO ReadWriteGreyscaleBinary)
gul_add_test(Image PPM_IO ReadWriteBlackAndWhiteASCII)
gul_add_test(Image PPM_IO ReadWriteBlackAndWhiteBinary)

gul_create_test()
target_link_libraries(TestImage image)



