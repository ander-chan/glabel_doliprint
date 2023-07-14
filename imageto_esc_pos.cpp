#include "imageto_esc_pos.h"



void ImageTo_ESC_POS::setPixel(int x, int y) {
    size_t byte_index = x * m_gs_y + y / 8;
    int bit_no = y % 8;
    // Swap msb/lsb order. This probably only works on machines with "normal" endianess.....
    unsigned char bit = 1 << ( 7 - bit_no );
    m_bytes.at( byte_index ) = m_bytes.at( byte_index ) | bit;
}

ImageTo_ESC_POS::ImageTo_ESC_POS(const QImage &image) {
    // Set up x and y as pr. epson manual
    m_width = image.width();
    m_height = image.height();

    m_gs_x = m_width / 8 + (m_width % 8 != 0?1:0);
    m_gs_y = m_height / 8 + (m_height % 8 != 0?1:0);

    if ( m_gs_x > 255 || m_gs_y > 255 ) {
        // You may want to write an error message here
        throw "Too large on dimension";
    }

    m_gs_k = m_gs_x * m_gs_y * 8;
    // Bit unsure about this limit. It depends on the actual printer....
    if ( m_gs_k > (3072*8) ) {
        // You may want to write an error message here
        throw "Too large on area";
    }

    vector<unsigned char> bytes( m_gs_k, 0 ); // Blank all bytes.
    m_bytes = bytes;

    // Iterate over the image, turn on any pixels that are set in the monochromo image.
    for ( int i_y = 0; i_y < m_height; ++i_y ) {
        for ( int i_x = 0; i_x < m_width; ++i_x ) {
            if ( image.pixelIndex( i_x, i_y ) == Qt::color1 ) {
                setPixel( i_x, i_y );
            }
        }
    }
}

vector<unsigned char> &ImageTo_ESC_POS::getBytes() {
    return m_bytes;
}

QByteArray ImageTo_ESC_POS::getGSStar() {
    QByteArray res( m_bytes.size() + 4, 0 );
    res[0] = 29;
    res[1] = '*';
    res[2] = (unsigned char) m_gs_x;
    res[3] = (unsigned char) m_gs_y;
    for ( size_t i = 0; i < m_bytes.size(); ++i ) {
        res[ (int)(4 + i) ] = m_bytes.at( i ) ;
    }
    return res;
}
