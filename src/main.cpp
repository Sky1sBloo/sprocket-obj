#include "importer/MeshToBlueprint.hpp"
#include "importer/ObjReader.hpp"
#include "mesh/Mesh.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>

void showHelp()
{
    std::cout << "Usage: \n"
              << "-i [file path] | Import obj to blueprint\n"
              << "-o [out directory] | Specifies the output directory"
              << "-h | Show help"
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
        }
    }
    if (filePath.empty()) {
        std::cout << "Did not specify file path" << std::endl;
        return 1;
    }

    try {
        SprObj::Mesh mesh = readObj(filePath);
        meshToBlueprint(mesh);
        std::cout << "Exported " << mesh.name << std::endl;
    } catch (const std::runtime_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
