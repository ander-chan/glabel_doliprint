#ifndef IMAGETO_ESC_POS_H
#define IMAGETO_ESC_POS_H



// C++
#include <iostream>
#include <iomanip>
#include <vector>

// Qt
#include <QCoreApplication>
#include <QImage>

using namespace std;

class ImageTo_ESC_POS {
private:
    int m_width;
    int m_height;
    int m_gs_x;
    int m_gs_y;
    int m_gs_k;
    // Actual bytes for image - could have used QByteArray for this, I guess.
    vector <unsigned char> m_bytes;

    // This turns on a pixel a position x, y as you would expect.
    // The bytes in the bitmap is stored in a weird "y first", "x second" order.
    // The bit fiddling here takes care of it.
    void setPixel( int x, int y );

public:
    ImageTo_ESC_POS( const QImage & image );

    // Access internal representation. Should be const something, I guess.
    vector<unsigned char> & getBytes();

    // Bytes suitable to send to the printer to define the bitmap.
    QByteArray getGSStar();;

};
#endif // IMAGETO_ESC_POS_H
