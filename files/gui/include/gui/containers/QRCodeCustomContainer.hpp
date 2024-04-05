#ifndef QRCODECUSTOMCONTAINER_HPP
#define QRCODECUSTOMCONTAINER_HPP

#include <gui_generated/containers/QRCodeCustomContainerBase.hpp>
#include "gui/widgets/QRCodeWidget.hpp"

class QRCodeCustomContainer : public QRCodeCustomContainerBase
{
public:
    QRCodeCustomContainer();
    virtual ~QRCodeCustomContainer() {}

    virtual void initialize();
protected:
    void resizeTheContainer();

    QRCodeWidget* QRCode;
};

#endif // QRCODECUSTOMCONTAINER_HPP
