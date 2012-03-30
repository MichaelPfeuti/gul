/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2012 Michael Pfeuti.
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

#include "XMLSerializable.h"

gul::Map<const void*, unsigned int> gul::XMLSerializable::savingReferences;
gul::Map<unsigned int, void*> gul::XMLSerializable::loadingReferences;

const char* gul::XMLSerializable::refTag = "__ref";
const char* gul::XMLSerializable::refIndexTag = "__refIndex";
