#ifndef FILEREADER_H
#define FILEREADER_H
#include "fstream"
#include "memory"
#include "basefilereader.h"
#include "facadeoperationresult.h"
#include "figure.h"
#include "point.h"
#include "vector"

class FileReader : public BaseFileReader{
public:
    float getMinZ(const vector<vector<float>>& data);
    float getMaxZ(const vector<vector<float>>& data);
    vector<vector<float>> normalize(vector<vector<float>>& data, NormalizationParameters& parameters);
    vector<vector<float>> getDataFromFile(const string& path);
    vector<Vertex>* makeVertices(vector<vector<float>>& data, const NormalizationParameters params);
    vector<Edge>* makeEdge(vector<Vertex>& vertices, size_t length, size_t width);
    shared_ptr<Scene> readScene(string path, NormalizationParameters parameters) override;
};

#endif // FILEREADER_H
