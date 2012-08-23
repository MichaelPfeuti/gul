gul_add_test(Image JPEG_IO Read)
gul_add_test(Image JPEG_IO WriteRead)

gul_add_test(Image PNG_IO Read)
gul_add_test(Image PNG_IO WriteRead)
gul_add_test(Image PNG_IO ReadInterlaced)

gul_add_test(Image TIFF_IO Read)
gul_add_test(Image TIFF_IO WriteRead)
gul_add_test(Image TIFF_IO ReadDeflate)
gul_add_test(Image TIFF_IO ReadJPEG)
gul_add_test(Image TIFF_IO ReadLZW)
gul_add_test(Image TIFF_IO ReadPackBits)

gul_add_test(Image PPM_IO ReadRGBASCII)
gul_add_test(Image PPM_IO WriteReadRGBASCII)
gul_add_test(Image PPM_IO ReadRGBBinary)
gul_add_test(Image PPM_IO WriteReadRGBBinary)
gul_add_test(Image PPM_IO ReadGreyscaleASCII)
gul_add_test(Image PPM_IO ReadGreyscaleBinary)
gul_add_test(Image PPM_IO ReadBlackAndWhiteASCII)
gul_add_test(Image PPM_IO ReadBlackAndWhiteBinary)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestImage image algorithms_analyzer algorithms_converter)



