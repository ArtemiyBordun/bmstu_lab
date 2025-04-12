#include "workfile.h"

FILE* openFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    return file;
}

void closeFile(FILE* file)
{
    fclose(file);
}

void workFile(AppContext* context)
{
    FILE* file = openFile(context->fileName);
    if (file != NULL)
    {
        countRowsInFile(context, file);
        parseRows(context, file);
        closeFile(file);
    }
}

void countRowsInFile(AppContext* context, FILE* file)
{
    size_t count = 0;
    int c;
    do {
        c = fgetc(file);
        if (c == '\n') {
            count++;
        }
    } while(c != EOF);
    rewind(file);
    context->rows = count;
}

void parseRows(AppContext* context, FILE* f)
{
    char** elem;
    double** matrix = (double**)calloc(context->rows, sizeof(double*));
    if (matrix == NULL)
    {
        context->error = memoryError;
        return;
    }
    for(size_t i = 0; i < context->rows; i++) {
        char tempStr[LEN] = {0};
        fgets(tempStr, LEN, f);
        if ((context->columns = parseWords(&elem, tempStr, ",")) == 0) {
            context->error = fileError;
            break;
        }
        matrix[i] = (double*)calloc(context->columns, sizeof(double));
        if (matrix[i] == NULL) {
            matrix = NULL;
            context->error = memoryError;
            break;
        }
        for(size_t j = 0; j < context->columns; j++) {
            matrix[i][j] = atoi(*(elem + j));
        }
    }
    context->mat = matrix;
}
