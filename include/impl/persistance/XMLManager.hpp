/***************************************************************************
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

#include <3rdParty/pugi/pugixml.hpp>

#include "Assert.h"

#include "memleak.h"

template<typename T>
T* gul::XMLManager::Load(const gul::String& rFile)
{
    pugi::xml_document doc;
    doc.load_file(rFile.GetData());
    pugi::xml_node rootNode = doc.first_child();

    T loaderInstance;
    gul::XMLSerializable<T>::performLoad(loaderInstance, rootNode, true);

    T* pLoadedInstance = gul::XMLSerializable<T>::performLoad(loaderInstance, rootNode);

    ASSERT(pLoadedInstance != nullptr);

    return pLoadedInstance;
}

template<typename T>
void gul::XMLManager::ResetSaveStatus(const T& rInstance)
{
  pugi::xml_node dummyNode;
  gul::XMLSerializable<T>::performSave(rInstance, dummyNode, true);
}

template<typename T>
bool gul::XMLManager::Save(const gul::String& rPath, const T& rInstance)
{
    pugi::xml_document doc;

    gul::XMLManager::ResetSaveStatus(rInstance);
    pugi::xml_node rootNode = doc.append_child("elemet");

    gul::XMLSerializable<T>::performSave(rInstance, rootNode);

    return doc.save_file(rPath.GetData());
}

#include "memleak_template_end.h"
