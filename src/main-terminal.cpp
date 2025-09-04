#include "importer/MeshToBlueprint.hpp"
#include "importer/ObjReader.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>

void showHelp()
{
    std::cout << "Usage: \n"
              << "-i [file path] | Import obj to blueprint\n"
              << "-o [out directory] | Specifies the output directory"
              << "-n [name] | Set object name"
              << "-h | Show help"
              << "-t [thickness] | Set object thickness (default 5mm)"
              << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        showHelp();
        return 0;
    }

    std::string filePath = "";
    std::string outDir = ".";
    std::string meshName = "";
    int meshThickness = 5;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        }

        if (strcmp(argv[i], "-i") == 0) {
            if (i >= argc) {
                std::cerr << "Too few arguments, see -h for usage" << std::endl;
                return 1;
            }
            filePath = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i >= argc) {
                std::cerr << "Too few arguments, see -h for usage" << std::endl;
                return 1;
            }
            outDir = argv[i + 1];
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i >= argc) {
                std::cerr << "Too few arguments, see -h for usage" << std::endl;
                return 1;
            }
            meshName = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i >= argc) {
                std::cerr << "Too few arguments, see -h for usage" << std::endl;
                return 1;
            }
            try {
                meshThickness = std::stoi(argv[i + 1]);
            } catch (const std::invalid_argument& ex) {
                std::cerr << "Argument not a number" << std::endl;
            }
        }
    }
    if (filePath.empty()) {
        std::cout << "Did not specify file path" << std::endl;
        return 1;
    }

    try {
        SprObj::Mesh mesh = readObj(filePath);
        if (!meshName.empty()) {
            mesh.name = meshName;
        }
        mesh.thickness = meshThickness;

        meshToBlueprint(mesh, outDir);
        std::cout << "Exported " << mesh.name << std::endl;
    } catch (const std::runtime_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
