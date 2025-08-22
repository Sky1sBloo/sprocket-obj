#include "ObjReader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

enum class ObjType {
    VERTEX,
    FACE,
    NAME
};

SprObj::Mesh readObj(const std::string& filePath)
{
    std::ifstream objFile { filePath };
    std::string line;

    SprObj::Mesh mesh;

    while (std::getline(objFile, line)) {
        std::stringstream lineStream { line };
        std::string type;
        ObjType currentType;

        std::getline(lineStream, type, ' ');
        if (type == "v") {
            currentType = ObjType::VERTEX;
        } else if (type == "f") {
            currentType = ObjType::FACE;
        } else if (type == "o") {
            currentType = ObjType::NAME;
        } else {
            continue;
        }

        switch (currentType) {
        case ObjType::VERTEX: {
            std::string x, y, z;
            std::getline(lineStream, x, ' ');
            std::getline(lineStream, y, ' ');
            std::getline(lineStream, z, ' ');

            mesh.vertices.push_back(SprObj::Vertex { std::stof(x), std::stof(y), std::stof(z) });
            break;
        }
        case ObjType::FACE: {
            std::string faceValue;
            mesh.faces.push_back(SprObj::Face {});

            while (std::getline(lineStream, faceValue, ' ')) {
                std::stringstream faceStream { faceValue };
                std::string vIdx;
                std::getline(faceStream, vIdx, '/');
                try {
                    mesh.faces.back().pushVertex(std::stoi(vIdx) - 1);
                } catch (const std::out_of_range& ex) {
                    throw std::runtime_error("Obj file has an ngon");
                }
            }
            break;
        }
        case ObjType::NAME: {
            std::getline(lineStream, mesh.name);
            break;
        }
        }
    }
    if (mesh.name.empty()) {
        mesh.name = "Model";
    }
    return mesh;
}
