#pragma once
#include <stdexcept>
#include <string>
#include <vector>

namespace SprObj {
struct Vertex {
    float x, y, z;
    Vertex(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
};

// Triangular face for now
class Face {
public:
    Face() {
        vertexIndices.reserve(4);
    }
    void pushVertex(int vertexIndex)
    {
        if (vertexIndices.size() >= 4) {
            throw std::out_of_range("Face is a non supported ngon");
        }
        vertexIndices.push_back(vertexIndex);
    }
    const std::vector<int>& getIndices() const { return vertexIndices; }

private:
    std::vector<int> vertexIndices;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::string name;
};
}
