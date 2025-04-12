#include "filereader.h"

float FileReader::getMinZ(const vector<vector<float>>& data)
{
    float res = data[0][0];
    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < data[i].size(); j++)
            if (res > data[i][j])
                res = data[i][j];
    return res;
}

float FileReader::getMaxZ(const vector<vector<float>>& data)
{
    float res = data[0][0];
    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < data[i].size(); j++)
            if (res < data[i][j])
                res = data[i][j];
    return res;
}

vector<vector<float>> FileReader::normalize(vector<vector<float>>& data, NormalizationParameters& parameters)
{
    float min = getMinZ(data);
    float max = getMaxZ(data);
    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < data[i].size(); j++)
           data[i][j] = parameters.min +
                   ((data[i][j] - min) * (max - min)) / (parameters.max - parameters.min);
    return data;
}

vector<vector<float>> FileReader::getDataFromFile(const string& path) {
    vector<vector<float>> data;
    FacadeOperationResult result;
    ifstream file(path);

    if (!file.is_open())
        throw "File reading error";

    string str;
    while (getline(file, str))
    {
        if (str.empty())
            throw "File reading error";

        vector<float> row;
        size_t pos = 0;
        float value;
        str.push_back(',');
        while (str.size())
        {
            string sValue;
            pos = str.find(',');
            sValue = str.substr(0, pos);
            value = stoi(sValue);
            row.push_back(value);
            str.erase(0, pos + 1);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}

vector<Vertex>* FileReader::makeVertices(vector<vector<float>>& data, const NormalizationParameters params)
{
    vector<Vertex>* res = new vector<Vertex>;
    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < data[i].size(); j++)
        {
            Point3D tmpPoint(i * params.step, j * params.step, data[i][j]);
            Vertex tmpVertex(tmpPoint);
            res->push_back(tmpVertex);
        }
    return res;
}

vector<Edge>* FileReader::makeEdge(vector<Vertex>& vertices, size_t length, size_t width)
{
    vector<Edge>* res = new vector<Edge>;
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if ((i + 1) < length)
            {
                Edge horizontalEdge(vertices[width * i + j], vertices[width * (i + 1) + j]);
                res->push_back(horizontalEdge);
            }
            if ((j + 1) < width)
            {
                Edge verticalEdge(vertices[width * i + j], vertices[width * i + j + 1]);
                res->push_back(verticalEdge);
            }
        }
    }
    return res;
}

shared_ptr<Scene> FileReader::readScene(string path, NormalizationParameters parameters)
{
    FacadeOperationResult res;
    vector <vector<float>> data = getDataFromFile(path);

    if (data.size() != data[0].size())
        throw runtime_error("File reading error");

    data = normalize(data, parameters);
    vector<Vertex>* vertices = makeVertices(data, parameters);
    vector<Edge>* edges = makeEdge(*vertices, data.size(), data[0].size());
    vector<Figure> figures;
    unique_ptr<Figure> figure = make_unique<Figure>(vertices, edges);
    figures.push_back(*figure);
    shared_ptr<Scene> scene = make_shared<Scene>(figures);
    return scene;
}

