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

#include "CTestAssert.h"
#include "CTestData.h"
#include "CLContext.h"
#include "CLProgram.h"

namespace TestCLProgram
{

  gul::String dummySourceValid("__kernel void testKernel(__global float* input,\n"
                               "                         __global float* output)\n"
                               "{\n"
                               "  int index = get_global_id(0);\n"
                               "  output[index] = input[index];\n"
                               "}");
  gul::String dummySourceInvalid("__kernel void testKernel(__global float* input,\n"
                                 "                         __global float* output)\n"
                                 "{\n"
                                 "  int index = get_global_id(0);\n"
                                 "  output[index = input[index];\n"
                                 "}");
  gul::String argumentTestKernel("__kernel void testNoArgs()\n"
                                 "{\n"
                                 "  __local float res;\n"
                                 "  res = 5;\n"
                                 "}\n"
                                 "\n"
                                 "__kernel void testOneArgs(int input)\n"
                                 "{\n"
                                 "  __local float res;\n"
                                 "  res = input;\n"
                                 "}\n"
                                 "\n"
                                 "__kernel void testTwoArgs(__global int* input,\n"
                                 "                          float output)\n"
                                 "{\n"
                                 "  __local float res;\n"
                                 "  res = input[1]*output;\n"
                                 "}\n"
                                 "\n"
                                 );


  int BuildValid(void)
  {
    { // force delete
        gul::CLContext context;
        TEST_TRUE(context.Initialize());
        context.MakeCurrent();

        gul::CLProgram program;
        program.AddSource(dummySourceValid);
        TEST_TRUE(program.Build());
    }

    return EXIT_SUCCESS;
  }

  int BuildInvalid(void)
  {
    { // force delete
        gul::CLContext context;
        TEST_TRUE(context.Initialize());
        context.MakeCurrent();

        gul::CLProgram program;
        program.AddSource(dummySourceInvalid);
        TEST_FALSE(program.Build());
    }

    return EXIT_SUCCESS;
  }

  int NoCurrentContext(void)
  {
    { // force delete
        gul::CLContext context;
        TEST_TRUE(context.Initialize());

        gul::CLProgram program;
        program.AddSource(dummySourceInvalid);
        TEST_ASSERTION(program.Build());
    }

    return EXIT_SUCCESS;
  }

  int RunUnknownKernel(void)
  {
    { // force delete
        gul::CLContext context;
        TEST_TRUE(context.Initialize());
        context.MakeCurrent();

        gul::CLProgram program;
        program.AddSource(argumentTestKernel);
        TEST_TRUE(program.Build());
        gul::CLWorkgroup workGroup(1);
        TEST_ASSERTION(program.Run("wrongKernel", workGroup));
    }

    return EXIT_SUCCESS;
  }

  int RunNoArgs(void)
  {
    { // force delete
        gul::CLContext context;
        TEST_TRUE(context.Initialize());
        context.MakeCurrent();

        gul::CLProgram program;
        program.AddSource(argumentTestKernel);
        TEST_TRUE(program.Build());
        gul::CLWorkgroup workGroup(1, 3);
        TEST_TRUE(program.Run("testNoArgs", workGroup));
    }

    return EXIT_SUCCESS;
  }

  int RunOneArg(void)
  {
    { // force delete
      gul::CLContext context;
      TEST_TRUE(context.Initialize());
      context.MakeCurrent();

      gul::CLProgram program;
      program.AddSource(argumentTestKernel);
      TEST_TRUE(program.Build());
      gul::CLWorkgroup workGroup(1, 3, 123);
      TEST_TRUE(program.Run("testOneArgs", workGroup, 12));
    }

    return EXIT_SUCCESS;
  }

  int RunTwoArgsFirstWrong(void)
  {
    { // force delete
      gul::CLContext context;
      TEST_TRUE(context.Initialize());
      context.MakeCurrent();

      gul::CLProgram program;
      program.AddSource(argumentTestKernel);
      TEST_TRUE(program.Build());
      gul::CLWorkgroup workGroup(1, 3, 123);
      TEST_FALSE(program.Run("testTwoArgs", workGroup, 1, 4.f));
    }

    return EXIT_SUCCESS;
  }

  int RunTwoArgs(void)
  {
    { // force delete
      gul::CLContext context;
      TEST_TRUE(context.Initialize());
      context.MakeCurrent();

      gul::CLProgram program;
      program.AddSource(argumentTestKernel);
      TEST_TRUE(program.Build());

      cl_int error;
      cl_mem intBuffer = clCreateBuffer(context.GetCLContext(),
                                        CL_MEM_READ_WRITE,
                                        5*sizeof(int), nullptr,
                                        &error);
      if(error != CL_SUCCESS)
      {
        return EXIT_FAILURE;
      }

      gul::CLWorkgroup workGroup(1, 3, 123);
      TEST_TRUE(program.Run("testTwoArgs", workGroup, intBuffer, 4.f));
    }

    return EXIT_SUCCESS;
  }
}

