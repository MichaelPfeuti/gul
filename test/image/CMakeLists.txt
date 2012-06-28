gul_add_test(Image JPEG_IO Read_Write)

gul_add_test(Image PPM_IO ReadWriteRGBASCII)
gul_add_test(Image PPM_IO ReadWriteRGBBinary)
gul_add_test(Image PPM_IO ReadWriteGreyscaleASCII)
gul_add_test(Image PPM_IO ReadWriteGreyscaleBinary)
gul_add_test(Image PPM_IO ReadWriteBlackAndWhiteASCII)
gul_add_test(Image PPM_IO ReadWriteBlackAndWhiteBinary)

gul_create_test()
target_link_libraries(TestImage image)



