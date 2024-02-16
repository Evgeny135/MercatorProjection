#include <iostream>
#include <cmath>

double a = 6378137.0;
double b = 6356752.3142;
double e = sqrt(1-((b/a)*(b/a)));

double degToRad(double deg) {
    return deg * (M_PI / 180.0);
}

void latlonToMetersEllips(double latitude, double longitude, double &x, double &y) {
    double lon = degToRad(longitude);
    double lat = degToRad(latitude);
    x = a * lon;
    y = a * log( tan( M_PI/4 + lat/2 )*pow((1-e* sin(1-e* sin(lat)))/((1+e* sin(lat))),e/2));
}

void latlonToMetersSphere(double latitude, double longitude, double &x, double &y) {
    double lon = degToRad(longitude);
    double lat = degToRad(latitude);
    x = a * lon;
    y = a * log( tan( M_PI/4 + lat/2 ));
}

int main() {
    double latitude = 55.751667;
    double longitude = 37.617778;
    double xEllipse, yEllipse,xSphere,ySphere;

    latlonToMetersEllips(latitude, longitude, xEllipse, yEllipse);
    latlonToMetersSphere(latitude, longitude, xSphere, ySphere);

    std::cout << "x = " << xEllipse << ", y = " << yEllipse << std::endl;
    std::cout<< "x = " << xSphere << " , y = " << ySphere << std::endl;

    return 0;
}