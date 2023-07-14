#ifndef RASTER_H
#define RASTER_H

#include <QObject>
#include <QRgb>
class Raster: QObject
{
public:
    Raster(QString file);
     QString *getImageData();
    int closestNDivisibleBy8(int n);
    int getPixelValue(int x, int y, QRgb* pixels);
    QRgb getPixels(QString imgFile);
    QByteArray* imageData;

    QRgb rgbaToPixel(int r, int g, int b, int a);
private:

    int getPixelValue(int x, int y, QVector<QVector<QRgb> > pixels);
    QRgb rgbaToPixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
    int getPixelValue(int x, int y, QImage *img);
    QByteArray rasterize(int printWidth, int printHeight, QImage *pixels);
    void removeTransparency(QImage *img);
    void makeGrayscale(QImage *img);

    void saveImage(QImage *img, QString fileName);
};

#endif // RASTER_H
