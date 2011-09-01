#ifndef _XMLGAMESAVER_H__
#define _XMLGAMESAVER_H__

#include <wx/wx.h>
#include <common/Misc.h>
#include <common/ClassFactory.h>

class Game;

class XMLGameSaver
{
public:
    XMLGameSaver(Game* game);
    ~XMLGameSaver();

    bool Save();
    bool Export();

private:
    Game* game;
};

#endif
