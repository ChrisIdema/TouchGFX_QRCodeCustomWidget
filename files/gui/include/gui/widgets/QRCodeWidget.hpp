#ifndef QR_CODE_WIDGET_HPP
#define QR_CODE_WIDGET_HPP

#include <touchgfx/widgets/Widget.hpp>
#include "gui/widgets/qrcodegen.h"
#include <touchgfx/hal/Types.hpp>
#include "touchgfx/Unicode.hpp"


class QRCodeWidget : public touchgfx::Widget
{
public:
    QRCodeWidget();

    virtual void draw(const touchgfx::Rect& invalidatedArea) const;
    virtual touchgfx::Rect getSolidRect() const;

    bool convertStringToQRCode(const char* text);
    bool convertStringToQRCode(const touchgfx::Unicode::UnicodeChar* text);

    void setScale(int scale);
    void setQRCodeVersion(uint8_t version);
    void setErrorCorrectionLevel(enum qrcodegen_Ecc);

private:
    void updateWidthAndHeight();

    uint8_t* qrCodeData;
    uint8_t qrCodeVersion;
    int sizeOfQRCodeSymbol;
    int scale;
    enum qrcodegen_Ecc errorCorectionLvl;
};

#endif
