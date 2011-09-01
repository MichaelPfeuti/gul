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

#include "xml/XMLGameSaver.h"

#include <wx/wfstream.h>
#include <wx/dir.h>
#include <wx/filename.h>

#include <model/Picture.h>
#include <model/Game.h>
#include <common/Constants.h>
#include <common/Assertions.h>

#include <setup.h>


XMLGameSaver::XMLGameSaver(Game *game)
{
    this->game = game;
}

XMLGameSaver::~XMLGameSaver() {}

/**
 * saves the game to a predefined location. The pictures are not copied to the final location here.
 */
bool XMLGameSaver::Save()
{
    pugi::xml_document doc;
    wxString saveFile = this->game->GetPath() + this->game->GetName() + wxT(".xml");
    // generate xml
    this->game->ResetSaveStatus();
    pugi::xml_node rootNode;
    rootNode.set_name("TESTE");
    //pugi::xml_node rootNode = this->game->Save();
    doc.append_copy(rootNode);

    return doc.save_file(saveFile.mb_str());
}

bool XMLGameSaver::Export()
{
    // move the game to a new directory
    wxString destination = this->game->GetPath() + this->game->GetName();
    this->game->SetPath(destination);
    
    if (!wxDir::Exists(destination)) {
        if (!wxFileName::Mkdir(destination, 0777, wxPATH_MKDIR_FULL)) {
            return false;
        }
        wxFileName::SetCwd(destination);
        
        for (int i = 0; i < this->game->GetPictureCount(); i++) {
            Picture* picture = this->game->GetPictureAtIndex(i);
            wxString path = picture->GetPath();
            int position = path.Find(FILE_SEPARATOR, true);
            path = destination + path.SubString(position, path.Len());
            wxMessageBox(path);
            picture->SetPath(path);
            picture->SaveFile(path);
            picture->Destroy();
            delete picture;
        }
        return this->Save();
    }
    FAIL("Export should tried to export to a nonexistent directory")
    return NULL; //should never be reached!
}
