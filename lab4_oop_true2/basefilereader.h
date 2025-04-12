#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H
#include "scene.h"
#include "string"
#include "memory"
#include "normalizationparameters.h"

using namespace std;

class BaseFileReader {
public:
    virtual shared_ptr<Scene> readScene(string path, NormalizationParameters parameters) = 0;
    virtual ~BaseFileReader() {}
};
#endif // BASEFILEREADER_H
