#ifndef SCRATCH_H_
#define SCRATCH_H_

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace scratch {
    class Asset
    {
    private:
        int assetId;
        std::string dataFormat;
        std::string md5ext;
        std::string name;
        int rotationCenterX, rotationCenterY;
    public:
        Asset(int assetId, std::string dataFormat);
        ~Asset();
        int getId();
    };

    class Stage
    {
    private:
        std::vector<nlohmann::json> blocks;
        nlohmann::json boardcasts;
        nlohmann::json comments;
        std::vector<Asset*> costumes;
    public:
        Stage(nlohmann::json target);
        ~Stage();
        std::vector<Asset*> getCostumes();
    };
}
#endif