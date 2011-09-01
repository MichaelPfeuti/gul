#include "xml/XMLGameLoader.h"

#include <model/Game.h>

#include <setup.h>

XMLGameLoader::XMLGameLoader()
{}


XMLGameLoader::~XMLGameLoader()
{}


Game* XMLGameLoader::LoadGame(const pugi::xml_document& doc)
{
    pugi::xml_node gameNode = doc.document_element();
    Game loaderInstance;

    loaderInstance.ResetLoadStatusFor(gameNode);
    Game* game = (Game*) loaderInstance.Load(gameNode);
    // TODO: errorhandling!
    return game;
    
}
