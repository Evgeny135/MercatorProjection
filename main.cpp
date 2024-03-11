#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdint>
#include "Matrix.h"
#include "Bmp.h"

using namespace std;

void fillMatrix(Matrix<RGB> &matrix) {
    for (int i = 0; i < matrix.getHeight(); i++) {
        for (int j = 0; j < matrix.getWidth(); j++) {
            RGB rgb = {0, 0, 0};
            matrix.set(i, j, rgb);
        }
    }
}

void mercatorToStereographic(double lat, double lon, double &x, double &y, double centerLat, double centerLon) {
    double latRad = lat * M_PI / 180.0;
    double lonRad = lon * M_PI / 180.0;
    double centerLatRad = centerLat * M_PI / 180.0;
    double centerLonRad = centerLon * M_PI / 180.0;

    double k = 2 / (1 + sin(centerLatRad) * sin(latRad) + cos(centerLatRad) * cos(latRad) * cos(lonRad - centerLonRad));

    x = k * cos(latRad) * sin(lonRad - centerLonRad);
    y = k * (cos(centerLatRad) * sin(latRad) - sin(centerLatRad) * cos(latRad) * cos(lonRad - centerLonRad));
}

void stereographicToPixel(double x, double y, int imageWidth, int imageHeight, int &pixelX, int &pixelY) {
    // Преобразование координат в диапазон от -1 до 1
    double normX = (x + 1) / 2;
    double normY = (y + 1) / 2;

    // Нормализация координат в пределах [0, 1]
    double normXCorrected = std::max(0.0, std::min(1.0, normX));
    double normYCorrected = std::max(0.0, std::min(1.0, normY));

    // Преобразование нормализованных координат в координаты пикселей
    pixelX = static_cast<int>(normXCorrected * (imageWidth - 1));
    pixelY = static_cast<int>(normYCorrected * (imageHeight - 1));
}

Matrix<RGB> stereographicProjection(Matrix<RGB> &image, Matrix<RGB> &result) {
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    double centerLat = 90; // Широта центра проекции
    double centerLon = 0; // Долгота центра проекции

    for (int i = 0; i < imageHeight; ++i) {
        for (int j = 0; j < imageWidth; ++j) {
            double lat = 90.0 - (static_cast<double>(i) / (imageHeight - 1)) * 180.0; // широта
            double lon = (static_cast<double>(j) / (imageWidth - 1)) * 360.0 - 180.0; // долгота

            double x, y;
            mercatorToStereographic(lat, lon, x, y,centerLat,centerLon);

            int pixelX, pixelY;
            stereographicToPixel(x, y, imageWidth, imageHeight, pixelX, pixelY);

            if (pixelX >= 0 && pixelX < imageWidth && pixelY >= 0 && pixelY < imageHeight) {
                result.set(pixelX,pixelY,image.get(j,i));
            }
        }
    }

    return result;
}



int main() {
    Bmp bmp("C:\\Users\\trish\\Desktop\\mercator.bmp", "C:\\Users\\trish\\Desktop\\NIIFOTON\\mercator.bmp");

    Matrix<RGB> mercator = bmp.readBmp();

    Matrix<RGB> stereo(mercator.getWidth(), mercator.getHeight());

    fillMatrix(stereo);

    stereographicProjection(mercator, stereo);

    bmp.writeBmp(stereo);

    return 0;
}