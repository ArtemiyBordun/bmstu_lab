#include "lists.h"

Lists* insertToList(Lists* head, RegionData newData) { //убрать 2 звездочки -> заменить на 1 звездочку
    Lists* newNode = (Lists*)malloc(sizeof(Lists));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = newData;
    newNode->next = head;
    //head = newNode;
    return newNode;
}

//void readData(Lists* head, AppContext context) {
//    FILE* file = fopen(context.fileName, "r");
//    if (file == NULL) {
//        printf("File not found\n");
//        return;
//    }

//    char line[256]; // Assuming maximum line length is 256 characters
//    while (fgets(line, sizeof(line), file)) {
//        RegionData newData;
//        int correct = sscanf(line, "%d,%[^,],%lf,%lf,%lf,%lf,%lf", &newData.year, newData.region, &newData.npg, &newData.br, &newData.dr, &newData.gdw, &newData.urban);
//        if (correct == 7)
//            newData.isCorrect = 1;
//        insertToList(head, newData);
//    }
//    fclose(file);
//}
