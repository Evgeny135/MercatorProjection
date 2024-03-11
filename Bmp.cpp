#include <string>
#include <cstdint>
#include "Bmp.h"
#include "Matrix.h"


unsigned int Bmp::getBit(char *buffer) {
    unsigned int size = 0;
    int length = sizeof(*buffer / buffer[0]);
    for (int i = 0; i < length; i++)
    {
        size += static_cast<uint32_t>(static_cast<uint8_t>(buffer[i])) << 8 * i;
    }
    return size;
}

Bmp::Bmp(std::string inputPath, std::string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

Matrix<RGB> Bmp::readBmp() {
    readHeader();
    Matrix<RGB> matrix(this->width, this->height);

    inputStream.seekg(this->offsetImg);

    for (int y = this->height - 1; y >= 0; y--) {
        for (int x = 0; x < this->width; x++) {
            char pixelData[3];
            inputStream.read(pixelData, 3);
            RGB pixel;
            pixel.b = static_cast<unsigned char>(pixelData[0]);
            pixel.g = static_cast<unsigned char>(pixelData[1]);
            pixel.r = static_cast<unsigned char>(pixelData[2]);

            matrix.set(x,y,pixel);
        }
    }
    inputStream.close();
    return matrix;
}

void Bmp::writeBmp(Matrix<RGB> matrix) {
    this->outputStream = std::ofstream(outputPath,std::ios::binary);

    outputStream.write(header,54);

    outputStream.seekp(offsetImg);

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            RGB pixel = matrix.get(x,y);
            char pixelData[3] = { static_cast<char>(pixel.b), static_cast<char>(pixel.g), static_cast<char>(pixel.r) };
            outputStream.write(pixelData, 3);
        }
    }

    outputStream.close();
}

void Bmp::readHeader() {
    char buffer[4];
    this->inputStream = std::ifstream(this->inputPath,std::ios::binary);

    inputStream.seekg(2);
    inputStream.read(buffer,4);
    this->size = getBit(buffer);

    inputStream.seekg(10);
    inputStream.read(buffer,4);
    this->offsetImg = getBit(buffer);

    inputStream.seekg(18);
    inputStream.read(buffer, 4);
    this->width = getBit(buffer);
    inputStream.read(buffer, 4);
    this->height = getBit(buffer);

    inputStream.seekg(28);
    inputStream.read(buffer,2);
    this->colorDepth = getBit(buffer);

    inputStream.seekg(0);
    inputStream.read(header,54);
}


