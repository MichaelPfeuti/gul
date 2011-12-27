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

#include "memleak.h"

template<typename T>
gul::XMLGameSaver<T>::XMLGameSaver(const T& rInstance)
  : rInstance(rInstance)
{
}

template<typename T>
bool gul::XMLGameSaver<T>::Save(const gul::String& rPath)
{
    pugi::xml_document doc;
    gul::String saveFile = rPath + ".xml";

    this->rInstance.ResetSaveStatus();
    pugi::xml_node rootNode;
    rootNode.set_name("TESTE");

    //pugi::xml_node rootNode = this->game->Save();
    doc.append_copy(rootNode);

    return doc.save_file(saveFile.mb_str());
}

#include "memleak_template_end.h"
