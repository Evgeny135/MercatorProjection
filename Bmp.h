#ifndef MERCATORPROJECTION_BMP_H
#define MERCATORPROJECTION_BMP_H


#include <fstream>
#include "Matrix.h"

struct RGB{
    unsigned int r,g,b;
};

class Bmp {
public:
    Bmp(std::string inputPath, std::string outputPath);
    Matrix<RGB> readBmp();
    void writeBmp(Matrix<RGB> matrix);
private:
    void readHeader();
    unsigned int getBit(char* buffer);
    std::ifstream inputStream;
    std::ofstream outputStream;
    std::string inputPath;
    std::string outputPath;
    unsigned int size;
    unsigned int offsetImg;
    unsigned int width;
    unsigned int height;
    unsigned int colorDepth;
    unsigned int endImg;
    char header[54];
};


#endif //MERCATORPROJECTION_BMP_H
