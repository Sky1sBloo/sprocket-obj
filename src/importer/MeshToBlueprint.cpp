#include "MeshToBlueprint.hpp"
#include "json.hpp"
#include "Mesh.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>

/**
 * Generate a vector of vertex that represents an edge from a face
 * An edge is represented by pairs
 */
std::vector<int> generateEdgeFromFaces(const std::vector<SprObj::Face>& faces)
{
    std::vector<int> edges;

    for (const SprObj::Face& face : faces) {
        for (int i = 0; i < face.getIndices().size(); i++) {
            edges.push_back(face.getIndices()[i]);
            if (i == face.getIndices().size() - 1) {
                edges.push_back(face.getIndices().at(0));
            } else {

                edges.push_back(face.getIndices().at(i + 1));
            }
        }
    }

    return edges;
}

void meshToBlueprint(const SprObj::Mesh& mesh, const std::string& outDir)
{
    std::vector<float> vertices;
    for (const SprObj::Vertex& vertex : mesh.vertices) {
        vertices.push_back(vertex.x * -1);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);
    }
    std::vector<int> edges = generateEdgeFromFaces(mesh.faces);
    std::vector<int> edgeFlags(static_cast<int>(edges.size() / 2), 0);

    nlohmann::ordered_json jsonFile {
        { "v", "0.2" },
        { "name", mesh.name },
        { "smoothAngle", 0 },
        { "gridSize", 1 },
        { "format", "freeform" }
    };
    jsonFile["mesh"] = {
        { "majorVersion", 0 },
        { "minorVersion", 3 },
        { "vertices", vertices },
        { "edges", edges },
        { "edgeFlags", edgeFlags }
    };
    jsonFile["mesh"]["faces"] = nlohmann::json::array();
    for (const SprObj::Face& face : mesh.faces) {
        if (face.getIndices().size() < 3) {
            throw std::out_of_range("Face object has 2 vertex");
        }

        std::vector<int> thickness(static_cast<int>(face.getIndices().size()), 5);
        jsonFile["mesh"]["faces"].push_back({ { "v", face.getIndices() },
            { "t", thickness },
            { "tm", face.getIndices().size() == 4 ? 16843009 : 65793 },
            { "te", 0 } });
    }
    jsonFile["rivets"] = {
        { "profiles", { { { "model", 0 }, { "spacing", 0.1 }, { "diameter", 0.05 }, { "height", 0.025 }, { "padding", 0.04 } } } },
    };
    jsonFile["rivets"].push_back({ "nodes", nlohmann::json::array() });

    std::ofstream output(outDir + "/" + mesh.name + ".blueprint");
    output << jsonFile.dump(4);
    output.close();
}
