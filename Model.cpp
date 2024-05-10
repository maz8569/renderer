#include "Model.h"

Model::Model() : vertices(), texture(), normals()
{
    
}

Model::Model(const char* filename) : vertices(), texture(), normals()
{
    loadOBJModel(filename);
}

IntersectionResult Model::render(Ray ray)
{
    IntersectionResult res;
    for (auto& tri : triangles) {
        res = tri.Hit(ray);
        if (res.type == HIT) {
            break;
        }
    }

    return res;
}

bool Model::loadOBJModel(const char* filename)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    std::vector<Vector3> temp_vertices;
    std::vector<Vector3> temp_uvs;
    std::vector<Vector3> temp_normals;

    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if (strcmp(lineHeader, "v") == 0) {
            Vector3 vertex;
            fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            Vector3 uv;
            fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            Vector3 normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);

            triangles.push_back(Triangle(temp_vertices[vertexIndex[0] - 1], temp_vertices[vertexIndex[1] - 1], temp_vertices[vertexIndex[2] - 1], Material({0, 0, 255})));

            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            
            unsigned int vertexIndex = vertexIndices[i];
            Vector3 vertex = temp_vertices[vertexIndex - 1];

            unsigned int uvIndex = uvIndices[i];
            Vector3 uv = temp_uvs[uvIndex - 1];

            unsigned int normalIndex = normalIndices[i];
            Vector3 normal = temp_normals[normalIndex - 1];

            //std::cout << "v: " << vertex << "\n";
            //std::cout << "t: " << uv << "\n";
            //std::cout << "n: " << normal << "\n";
            vertices.push_back(vertex);

            texture.push_back(uv);
            normals.push_back(normal);
        }

    }

    return false;
}
