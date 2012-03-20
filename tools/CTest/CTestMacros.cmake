############################################################################
##
## This file is part of gul (Graphic Utility Library).
##
## Copyright (c) 2011 Michael Pfeuti.
##
## Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
##
##
## gul is free software: you can redistribute it and/or modify it under the
## terms of the GNU Lesser General Public License as published by the Free
## Software Foundation, either version 3 of the License, or (at your option)
## any later version.
##
## gul is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
## more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with gul. If not, see <http://www.gnu.org/licenses/>.
##
##
## If you have questions regarding the use of this file, please contact
## Michael Pfeuti at mpfeuti@ganymede.ch.
##
############################################################################

#####################################################
### this macro add declarations and registrations ###
### for each test to the mainfunction source file ###
#####################################################
macro(gul_add_test_to_src)
  set(newDecl "// Test Forward Declarations\nDECLARE_TEST(Test${suite}, ${test})")
  set(newReg "// Test Registrations\n  REGISTER_TEST(Test${suite}::${test})")

  string(REPLACE "// Test Forward Declarations" ${newDecl} collection_main_source ${collection_main_source})
  string(REPLACE "// Test Registrations" ${newReg} collection_main_source ${collection_main_source})

  unset(newDecl)
  unset(newReg)
endmacro(gul_add_test_to_src)


#####################################################
## this macro generates the code for a collection  ##
## executable. Each test gets forward decalred and ##
## registered. Certain parts of the code need are  ##
## used to place the decalration and registrations ##
#####################################################
macro(gul_init_test_src)
  set(collection_main_source "/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 Michael Pfeuti.
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
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
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

#include \"CTestMain.h\"

// Test Forward Declarations

void RegisterTests(void)
{
  // Test Registrations
}
")
endmacro(gul_init_test_src)

#####################################################
# this macro splits up the Coll::Suite::Test string #
#####################################################
macro(gul_split_test string)
  string(FIND ${string} "::" idxColl)
  string(FIND ${string} "::" idxSuite REVERSE)
  string(LENGTH ${string} idxTest)

  math(EXPR suiteStart '${idxColl}+2')
  math(EXPR suiteLength '${idxSuite}-${idxColl}-2')
  math(EXPR testStart '${idxSuite}+2')
  math(EXPR testLength '${idxTest}-${idxSuite}-2')
    
  string(SUBSTRING ${string} 0 ${idxColl} collection)
  string(SUBSTRING ${string} ${suiteStart} ${suiteLength} suite)
  string(SUBSTRING ${string} ${testStart} ${testLength} test)
  
  unset(idxColl)
  unset(idxSuite)
  unset(idxTest)
  unset(suiteStart)
  unset(suiteLength)
  unset(testStart)
  unset(testLength)
endmacro(gul_split_test)

#####################################################
####### This macro is used to add a new test ########
#####################################################
macro(gul_add_test collection suite test)
  list(APPEND GUL_TESTS "${collection}::${suite}::${test}")
endmacro(gul_add_test)

#####################################################
####### This macro generates the actual code ########
#####################################################
macro(gul_create_test)
  list(REMOVE_DUPLICATES GUL_TESTS)
  list(SORT GUL_TESTS)
  list(LENGTH GUL_TESTS length)
 
  ### process collections
  while(length GREATER 0)
    list(GET GUL_TESTS 0 gul_test)
    gul_split_test(${gul_test})
    set(collectionCurrent ${collection})
    gul_init_test_src()
    
    ### process suites
    while(collectionCurrent STREQUAL collection)
      set(suiteCurrent ${suite}) 
      
      ### process tests
      while(collectionCurrent STREQUAL collection AND suiteCurrent STREQUAL suite)
        add_test("Test${suite}::${test}" "Test${collection}" "Test${suite}::${test}")        
        gul_add_test_to_src()
       
        # process next entry        
        list(REMOVE_AT GUL_TESTS 0)
        list(LENGTH GUL_TESTS length)
        if(length EQUAL 0)
          break()
        endif(length EQUAL 0)
        list(GET GUL_TESTS 0 gul_test)
        gul_split_test(${gul_test})        
        
      endwhile(collectionCurrent STREQUAL collection AND suiteCurrent STREQUAL suite)
      ### end process tests

      # there exists a source file for each suite named Test[SUITE_NAME].cpp
      set(collection_cpp "${collection_cpp};Test${suiteCurrent}.cpp")

      if(length EQUAL 0)
          break()
      endif(length EQUAL 0)
        
    endwhile(collectionCurrent STREQUAL collection)
    ### end process suites
    
    # For each collection build the source file with the test-function registration
    # and the main funtion
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/TestMain${collectionCurrent}.cpp" ${collection_main_source})
    
    # there is an executable for each collection named Test[COLLECTION_NAME]
    include_directories("${CMAKE_CURRENT_BINARY_DIR}")
    add_executable(Test${collectionCurrent} ${collection_cpp};TestMain${collectionCurrent}.cpp)

  endwhile(length GREATER 0)
  ### end process collections
  
  
  unset(length)
  unset(collection_main_source)
  unset(collection_cpp)
  unset(collection)
  unset(collectionCurrent)
  unset(suite)
  unset(suiteCurrent)
  unset(gul_test)
  unset(GUL_TESTS)
  
endmacro(gul_create_test)

