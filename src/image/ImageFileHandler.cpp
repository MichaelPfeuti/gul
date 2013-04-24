/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti
**
** Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
**
**
** gul is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** gul is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
** more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with gul. If not, see <http://www.gnu.org/licenses/>.
**
**
** If you have questions regarding the use of this file, please contact
** Michael Pfeuti at mpfeuti@ganymede.ch.
**
***************************************************************************/

#include "ImageFileHandler.h"
#include <cstdlib>
#include "ImageIO_PPM.h"
#include "File.h"

#ifdef LIBJPEG_FOUND
#  include "ImageIO_JPEG.h"
#endif

#ifdef LIBPNG_FOUND
#  include "ImageIO_PNG.h"
#endif

#ifdef LIBTIFF_FOUND
#  include "ImageIO_TIFF.h"
#endif

gul::ImageFileHandler* gul::ImageFileHandler::instance = nullptr;

gul::ImageFileHandler::ImageFileHandler(void)
{
  initializeAllLoaders();
}

gul::ImageFileHandler::~ImageFileHandler(void)
{
  MapBasic<String, ImageIO*>::Iterator it = endingsMap.GetIterator();
  while(it.HasNext())
  {
    MapBasic<String, ImageIO*>::Pair pair = it.Next();
    GUL_DELETE(pair.GetValue());
  }
  endingsMap.Clear();
}

void gul::ImageFileHandler::initializeAllLoaders(void)
{
#ifdef LIBJPEG_FOUND
  endingsMap.Add("jpeg", new ImageIO_JPEG());
  endingsMap.Add("jpg", new ImageIO_JPEG());
  endingsMap.Add("jpe", new ImageIO_JPEG());
  endingsMap.Add("jif", new ImageIO_JPEG());
  endingsMap.Add("jfif", new ImageIO_JPEG());
  endingsMap.Add("jfi", new ImageIO_JPEG());
#endif

#ifdef LIBPNG_FOUND
  endingsMap.Add("png", new ImageIO_PNG());
#endif

#ifdef LIBTIFF_FOUND
  endingsMap.Add("tiff", new ImageIO_TIFF());
  endingsMap.Add("tif", new ImageIO_TIFF());
#endif

  endingsMap.Add("ppm", new ImageIO_PPM());
  endingsMap.Add("pgm", new ImageIO_PPM());
  endingsMap.Add("pbm", new ImageIO_PPM());
  endingsMap.Add("pnm", new ImageIO_PPM());
}

gul::Image gul::ImageFileHandler::Load(const gul::File& file) const
{
  ASSERT_MSG(file.Exists(), "File does not exist!");

  gul::ImageIO* io = endingsMap.Get(file.GetSuffix().LowerCase());
  ASSERT_MSG(io != nullptr, "Unknown Image Input Format!");

  return io->Load(file);
}

void gul::ImageFileHandler::Save(const gul::File& file, const gul::Image& image) const
{
  ASSERT_MSG(file.IsPathValid(), "Invalid Path!");

  gul::ImageIO* io = endingsMap.Get(file.GetSuffix().LowerCase());
  ASSERT_MSG(io != nullptr, "Unknown Image Output Format!");

  io->Save(file, image);
}

gul::ImageFileHandler& gul::ImageFileHandler::Instance(void)
{
  if(instance == nullptr)
  {
    instance = new ImageFileHandler();
    atexit(deleteInstance);
  }

  return *instance;
}

void gul::ImageFileHandler::deleteInstance(void)
{
  GUL_DELETE(instance);
}
