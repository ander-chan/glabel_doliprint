#ifndef PRINTERSERIAL_H
#define PRINTERSERIAL_H
//#include "libusb.h"
//#include "Printer.h"
#include <QByteArray>
#include <string>
#include <utility>
#include <vector>

class PrinterSerial : public Printer
{
public:
     static void initPrinterSerial(QString path);
     static PrinterSerial & getPrinter(void);

    void raw(std::string text);
     QByteArray data();
private:

    static void initializePrinter(std::pair<int, int> ids);
    PrinterSerial(std::pair<int, int> ids);
    explicit   PrinterSerial(QString path);
    ~PrinterSerial();

     QByteArray m_data;
     static PrinterSerial & getPrinter(QString path);

};

#endif // PRINTERSERIAL_H
