#include "raster.h"
#include <QColor>
#include <QDebug>
#include <QRgb>
#include <QByteArray>
#include <QImage>
Raster::Raster(QString file)
{

    ;

    int height{0};

    int printHeight{0};
    int printWidth{0};
    int width{0};

    qDebug("load image pixels");
    QImage *img_ = new QImage(file);
    //QImage img = img_->convertToFormat(QImage::Format_RGBA8888,Qt::AutoColor);
    removeTransparency(img_);
    makeGrayscale(img_);

    width = img_->width();
    height = img_->height();
    printWidth = closestNDivisibleBy8(width);
    printHeight = closestNDivisibleBy8(height);
    qDebug()<<printWidth;
    qDebug()<<printHeight;
    saveImage(img_,"/home/ander/qtproyects/GlabelConnector/tests/test1.png");



    QByteArray bytes = rasterize(printWidth, printHeight, img_);
    static const char imageHeader[] = { 0x1d,0x76,0x30,0x00};


    QByteArray imageData;
    static const char imageSize[] = { char((width >> 3) & 0xff), char(((width >> 3) >> 8) & 0xff), char(height & 0xff), char((height >> 8) & 0xff)};

    imageData.append(imageHeader);
    imageData.append(QByteArray(imageSize,sizeof (imageSize)));
    imageData.append( bytes);
    qDebug()<<imageData;



}
// implment remove transparency
void Raster::removeTransparency(QImage *img)
{
    for(int i=0;i<img->width();i++)
    {
        for(int j=0;j<img->height();j++)
        {
            QColor color = img->pixel(i,j);
            if(color.alpha()==0)
            {
                img->setPixel(i,j,Qt::white);
            }
        }
    }
}
// implment make grayscale
void Raster::makeGrayscale(QImage *img)
{
    for(int i=0;i<img->width();i++)
    {
        for(int j=0;j<img->height();j++)
        {
            QColor color = img->pixel(i,j);
            int gray = (color.red()+color.green()+color.blue())/3;
            img->setPixelColor(i,j,QColor(gray,gray,gray));
        }
    }
}
int Raster::closestNDivisibleBy8(int n)
{int n1{0};
    int q{0};

    q = n / 8;
    n1 = q * 8;
    return n1;

}
int Raster::getPixelValue(int x, int y, QImage * img)
{
    QColor pixel ;
    if (!img || x < 0 || x >= img->width() || y < 0 || y >= img->height()) {
        qWarning("QImage::pixel: coordinate (%d,%d) out of range", x, y);

    }else{
         pixel = img->pixelColor(x,y);
         qDebug()<<pixel.red();
    }
    //treshold pixel
    if(pixel.red()>=128)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    if (pixel.red() > 0) {
        return 0;
    }
    return 1;
}
QByteArray Raster::rasterize(int printWidth, int printHeight, QImage* pixels)
{
    QByteArray data;
    QVector<uint16_t> bytes;

    if (printWidth % 8 != 0) {
        qDebug("printWidth must be a multiple of 8");
        return NULL;
    }if (printHeight % 8 != 0) {
        qDebug("printHeight must be a multiple of 8");
        return NULL;
    }
    bytes = QVector<uint16_t>( (printWidth * printHeight) >> 3);

    for (int y = 0; y < printHeight; y++){


        for (int x = 0; x < printWidth; x = x + 8){


            int i = y * (printWidth >> 3) + (x >> 3);
            bytes.insert(i, (getPixelValue(x + 0, y, pixels) << 7) | (getPixelValue(x + 1, y, pixels) << 6) | (getPixelValue(x + 2, y, pixels) << 5) | (getPixelValue(x + 3, y, pixels) << 4) | (getPixelValue(x + 4, y, pixels) << 3) | (getPixelValue(x + 5, y, pixels) << 2) | (getPixelValue(x + 6, y, pixels) << 1) | getPixelValue(x + 7, y, pixels));


        }
        // populate vector
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << bytes;
    }
     saveImage(pixels,"/home/ander/qtproyects/GlabelConnector/tests/test2.png");
    return data;

}
QRgb Raster::rgbaToPixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{

    return qRgba(char(r >> 8), char(g >> 8), char(b >> 8),char(a >> 8) );

}
//implement save qimage to file
void Raster::saveImage(QImage* img,QString fileName)
{
   
    img->save(fileName);
}
//method to get raw data
QString * Raster::getImageData()
{
    //get raw string
    QString *rawData = new QString(imageData->toHex());
    //remove first two characters
    //rawData->remove(0,2);
    //remove last two characters
    rawData->remove(rawData->length()-2,2);
    //return raw string
    return rawData;

}

