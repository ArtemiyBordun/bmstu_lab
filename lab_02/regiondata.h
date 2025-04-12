#ifndef REGIONDATA_H
#define REGIONDATA_H

#define SIZE 512

struct RegionData {
    int year;
    char region[SIZE];
    double npg;
    double br;
    double dr;
    double gdw;
    double urban;
};

#endif // REGIONDATA_H
