#include "scratch.h"

using nlohmann::json;

scratch::Asset::Asset(int assetId, std::string dataFormat)
{
    this->assetId = assetId;
    this->dataFormat = dataFormat;
}

scratch::Asset::~Asset()
{
    // TODO:
}

int scratch::Asset::getId() { return this->assetId; }

scratch::Stage::Stage(json target)
{
    for (auto& block : target["blocks"])
    {
        this->blocks.push_back(block);
    }
    this->boardcasts = target["boardcasts"];
    this->comments = target["comments"];
    for (auto& costume : target["costumes"])
    {
        this->costumes.push_back(new scratch::Asset(costume["assetId"], costume["dataFormat"]));
    }
    // TODO: Initialise the stage
}

scratch::Stage::~Stage()
{
    // TODO:
    for (auto& costume : this->costumes)
    {
        delete costume;
    }
}