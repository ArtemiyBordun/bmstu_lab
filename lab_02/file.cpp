#include "file.h"

FILE* openFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    return file;
}

void closeFile(FILE* file) {
    if (file != NULL)
        fclose(file);
}

void processData(List* next, const char* fileName) {
    FILE* file = openFile(fileName);
    if (file == NULL)
        return;

    char line[MAXSIZE];
    int cnt = 0;
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        RegionData newData;
        int correct = sscanf(line, "%d,%[^,],%lf,%lf,%lf,%lf,%lf", &newData.year, newData.region,
                             &newData.npg, &newData.br, &newData.dr, &newData.gdw, &newData.urban);
        if (correct == CORRECT) {
            pushBack(next, newData);
            cnt++;
        }
    }
    closeFile(file);
    next->size = cnt;
}
