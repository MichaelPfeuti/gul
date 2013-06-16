/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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

#include <ctype.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <libgen.h>

static char header[] =
"#pragma once\n"
"#ifndef _GUL_RESOURCE_%s_H_\n"
"#define _GUL_RESOURCE_%s_H_\n"
"/***************************************************************************\n"
"**\n"
"** This file is part of gul (Graphic Utility Library).\n"
"**\n"
"** Copyright (c) 2011-2013 Michael Pfeuti.\n"
"**\n"
"** Contact: Michael Pfeuti (mpfeuti@ganymede.ch)\n"
"**\n"
"**\n"
"** gul is free software: you can redistribute it and/or modify it under the\n"
"** terms of the GNU Lesser General Public License as published by the Free\n"
"** Software Foundation, either version 3 of the License, or (at your option)\n"
"** any later version.\n"
"**\n"
"** gul is distributed in the hope that it will be useful, but WITHOUT ANY\n"
"** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n"
"** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for\n"
"** more details.\n"
"**\n"
"** You should have received a copy of the GNU Lesser General Public License\n"
"** along with gul. If not, see <http://www.gnu.org/licenses/>.\n"
"**\n"
"**\n"
"** If you have questions regarding the use of this file, please contact\n"
"** Michael Pfeuti at mpfeuti@ganymede.ch.\n"
"**\n"
"***************************************************************************/\n"
"\n"
"static const struct\n"
"{\n"
"  unsigned int size;\n"
"  char 	       data[%d+1];\n"
"} %s = { %d,\n"
"  { ";

static int getLength(FILE *f)
{
  int len;
  fseek(f, 0, SEEK_END);
  len = ftell(f);
  fseek(f, 0, SEEK_SET);
  return len;
}

static void toUpper(char* filename)
{
  for(size_t i = 0; i < strlen(filename); ++i)
  {
    filename[i] = toupper(filename[i]);
  }
}

static void trimSuffix(char* filename)
{
  for(size_t i = 0; i < strlen(filename); ++i)
  {
    filename[i] = filename[i] == '.' ? '\0' : filename[i];
  }
}

int main(int argc, char **argv)
{
  if(argc < 4)
  {
    fprintf(stderr, "usage: textToHeader input output struct_name\n");
    return EXIT_FAILURE;
  }

  FILE *in;
  FILE *out;
  in = fopen(argv[1], "rt");
  out = fopen(argv[2], "wt");

  char* filename = basename(argv[2]);
  trimSuffix(filename);
  char filenameUpper[strlen(filename) + 1];
  strcpy(filenameUpper, filename);
  toUpper(filenameUpper);

  unsigned int size = getLength(in);

  fprintf(out, header, filenameUpper, filenameUpper, size, argv[3], size);
  int count = 0;
  int character;
  while((character = getc(in)) != EOF)
  {
    fprintf(out, "%d, ", character);
    if (++count > 16)
    {
      fprintf(out, "\n    ");
      count = 0;
    }
  }
  fprintf(out, "0 }\n");
  fprintf(out, "  };\n");
  fprintf(out, "#endif\n");

  fclose(in);
  fclose(out);

  return EXIT_SUCCESS;
}
