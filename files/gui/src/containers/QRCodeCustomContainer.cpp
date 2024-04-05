#include <gui/containers/QRCodeCustomContainer.hpp>
#include "gui/widgets/qrcodegen.h"

QRCodeCustomContainer::QRCodeCustomContainer()
{

}

void QRCodeCustomContainer::initialize()
{
    QRCodeCustomContainerBase::initialize();

    QRCode = new QRCodeWidget();
    QRCode->setScale(3);
    QRCode->setQRCodeVersion(10);
    QRCode->setErrorCorrectionLevel(qrcodegen_Ecc::qrcodegen_Ecc_MEDIUM);
    QRCode->convertStringToQRCode("Hello World!");
    resizeTheContainer();
    QRCode->setXY(5, 5);
    add(*QRCode);
}

void QRCodeCustomContainer::resizeTheContainer()
{
    uint16_t newHeight = QRCode->getHeight() + 10;
    uint16_t newWidth = QRCode->getWidth() + 10;
    
    setHeight(newHeight);
    setWidth(newWidth);

    background.setHeight(newHeight);
    background.setWidth(newWidth);
    background.setXY(0, 0);
}