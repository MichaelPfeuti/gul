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

gul_add_test(Image ImageFileHandler LoadJPEG)
gul_add_test(Image ImageFileHandler SaveJPEG)
gul_add_test(Image ImageFileHandler LoadPNG)
gul_add_test(Image ImageFileHandler SavePNG)
gul_add_test(Image ImageFileHandler LoadPPM)
gul_add_test(Image ImageFileHandler SavePPM)
gul_add_test(Image ImageFileHandler LoadTIFF)
gul_add_test(Image ImageFileHandler SaveTIFF)

gul_add_test(Image Image Constructor)
gul_add_test(Image Image CopyConstructor)
gul_add_test(Image Image Assignment)
gul_add_test(Image Image AssignmentSelf)
gul_add_test(Image Image AssignmentExchange)
gul_add_test(Image Image DeleteReferee)

gul_add_util_sources(Utils.h Utils.cpp)
gul_create_test()
target_link_libraries(TestImage image algorithms_analyzer algorithms_converter)



