#ifndef XMLGAMELOADER_H_INCLUDED
#define XMLGAMELOADER_H_INCLUDED

#include "pugixml.hpp"

class Game;

class XMLGameLoader
{
public:
    XMLGameLoader();
    ~XMLGameLoader();

    Game* LoadGame(const pugi::xml_document&);
};


#endif // XMLGAMELOADER_H_INCLUDED
