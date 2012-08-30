gul_add_test(Image ImageIO_JPEG Read)
gul_add_test(Image ImageIO_JPEG WriteRead)

gul_add_test(Image ImageIO_PNG Read)
gul_add_test(Image ImageIO_PNG WriteRead)
gul_add_test(Image ImageIO_PNG ReadInterlaced)

gul_add_test(Image ImageIO_TIFF Read)
gul_add_test(Image ImageIO_TIFF WriteRead)
gul_add_test(Image ImageIO_TIFF ReadDeflate)
gul_add_test(Image ImageIO_TIFF ReadJPEG)
gul_add_test(Image ImageIO_TIFF ReadPackBits)
gul_add_test(Image ImageIO_TIFF ReadLZW)

gul_add_test(Image ImageIO_PPM ReadRGBASCII)
gul_add_test(Image ImageIO_PPM WriteReadRGBASCII)
gul_add_test(Image ImageIO_PPM ReadRGBBinary)
gul_add_test(Image ImageIO_PPM WriteReadRGBBinary)
gul_add_test(Image ImageIO_PPM ReadGreyscaleASCII)
gul_add_test(Image ImageIO_PPM ReadGreyscaleBinary)
gul_add_test(Image ImageIO_PPM ReadBlackAndWhiteASCII)
gul_add_test(Image ImageIO_PPM ReadBlackAndWhiteBinary)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestImage image algorithms_analyzer algorithms_converter)



