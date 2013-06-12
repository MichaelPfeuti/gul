############################################################################
##
## This file is part of gul (Graphic Utility Library).
##
## Copyright (c) 2012 Michael Pfeuti.
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

# find AStyle application
find_program(ASTYLE_EXECUTABLE astyle
             DOC "AStyle A Free, Fast and Small Automatic Formatter (http://astyle.sourceforge.net/)"
             )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AStyle DEFAULT_MSG ASTYLE_EXECUTABLE)

MARK_AS_ADVANCED(ASTYLE_EXECUTABLE)
