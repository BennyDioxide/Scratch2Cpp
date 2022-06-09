#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <libzippp/libzippp.h>
#include <nlohmann/json.hpp>
#include "scratch.h"

using std::cout, std::cerr, std::string, std::vector, std::find, std::endl;
using libzippp::ZipArchive, libzippp::ZipEntry;
using nlohmann::json;

int main(int argc, char** argv)
{
    ZipArchive* project;
    string project_filename;
    json project_json;
    vector<json> targets;
    // int file_count;

    if (argc < 2)
    {
        cerr << "Error: No input file specified\n";
        return 1;
    }

    project_filename = argv[1];

    // Open the project file
    int err = 0;
    project = new ZipArchive(project_filename);
    project->open(ZipArchive::ReadOnly);

    vector<ZipEntry> entries = project->getEntries();
    vector<scratch::Stage*> stages;

    for (ZipEntry& entry : entries) {
        string name = entry.getName();
        int size = entry.getSize();

        if (name == "project.json") project_json = json::parse(entry.readAsText());
    }

    for (auto& target : project_json["targets"]) {
        cout << target << endl;
        if (target["isStage"] == "true")
        {
            const auto index = project_json["targets"].find(target);
            cout << index.key() << target << endl;
            stages.push_back(new scratch::Stage(target));
            // targets.erase(index);
            continue;
        }
        targets.push_back(target);
    }

    project_json.erase("meta");
    project_json.erase("targets");

    cout << project_json << endl;
    // cout << targets << endl;

    for (auto& stage : stages) {
        delete stage;
    }

    project->close();
    delete project;
    return 0;
}