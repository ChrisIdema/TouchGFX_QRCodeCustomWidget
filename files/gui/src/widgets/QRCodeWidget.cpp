#include <gui/widgets/QRCodeWidget.hpp>
#include <touchgfx/hal/HAL.hpp>
#include "touchgfx/hal/Types.hpp"
#include <cstdio>

QRCodeWidget::QRCodeWidget(): qrCodeVersion(1),
                              sizeOfQRCodeSymbol(25),
                              scale(1),
                              errorCorectionLvl(qrcodegen_Ecc_LOW)
{
    qrCodeData = new uint8_t[qrcodegen_BUFFER_LEN_FOR_VERSION(qrCodeVersion)];
}

bool QRCodeWidget::convertStringToQRCode(const char* text)
{
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrCodeData, errorCorectionLvl,
        qrCodeVersion, qrCodeVersion, qrcodegen_Mask_AUTO, true);

    if (ok)
    {
        sizeOfQRCodeSymbol = qrcodegen_getSize(qrCodeData);
        updateWidthAndHeight();
    }
    return ok;
}

bool QRCodeWidget::convertStringToQRCode(const touchgfx::Unicode::UnicodeChar* text)
{
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

    uint8_t convertedToUTF8Buffer[qrcodegen_BUFFER_LEN_MAX];
    touchgfx::Unicode::toUTF8(text, convertedToUTF8Buffer, qrcodegen_BUFFER_LEN_MAX);

    bool ok = qrcodegen_encodeText((const char*)convertedToUTF8Buffer, tempBuffer, qrCodeData, errorCorectionLvl,
        qrCodeVersion, qrCodeVersion, qrcodegen_Mask_AUTO, true);

    if (ok)
    {
        sizeOfQRCodeSymbol = qrcodegen_getSize(qrCodeData);
        updateWidthAndHeight();
    }
    return ok;
}

void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
    //To check if qrCodeData is ready to be drawn
    int result = qrCodeData[0];
    if (!((qrcodegen_VERSION_MIN * 4 + 17) <= result)
        || !(result <= (qrcodegen_VERSION_MAX * 4 + 17)))
    {
        return;
    }

    touchgfx::Rect absInvalidated = invalidatedArea;
    translateRectToAbsolute(absInvalidated);

    auto lcdPtr = &touchgfx::HAL::lcd();

    uint8_t bitDepth = lcdPtr->bitDepth();
    if (bitDepth == 8)
    {
		uint8_t* framebuffer = (uint8_t*)touchgfx::HAL::getInstance()->lockFrameBuffer();

		if (touchgfx::HAL::getInstance()->DISPLAY_ROTATION == touchgfx::DisplayRotation::rotate90)
		{
			for (int y = 0; y < absInvalidated.width; y++)
			{
				for (int x = 0; x < absInvalidated.height; x++)
				{
					framebuffer[(absInvalidated.y + x) + ((((touchgfx::HAL::DISPLAY_WIDTH - 1) - absInvalidated.x) - y) * (touchgfx::HAL::FRAME_BUFFER_WIDTH))] = qrcodegen_getModule(qrCodeData, (y + invalidatedArea.x) / scale, (x + invalidatedArea.y) / scale) ? 0x00 : 0xff;
				}
			}
		}
		else {
			for (int y = 0; y < absInvalidated.height; y++)
			{
				for (int x = 0; x < absInvalidated.width; x++)
				{
					framebuffer[(absInvalidated.x + x) + ((absInvalidated.y + y) * (touchgfx::HAL::FRAME_BUFFER_WIDTH))] = qrcodegen_getModule(qrCodeData, (x + invalidatedArea.x) / scale, (y + invalidatedArea.y) / scale) ? 0x00 : 0xff;
				}
			}
		}
    }
    if (bitDepth == 16)
    {
		uint16_t* framebuffer = touchgfx::HAL::getInstance()->lockFrameBuffer();

		if (touchgfx::HAL::getInstance()->DISPLAY_ROTATION == touchgfx::DisplayRotation::rotate90)
		{
			for (int y = 0; y < absInvalidated.width; y++)
			{
				for (int x = 0; x < absInvalidated.height; x++)
				{
					framebuffer[(absInvalidated.y + x) + ((((touchgfx::HAL::DISPLAY_WIDTH - 1) - absInvalidated.x) - y) * (touchgfx::HAL::FRAME_BUFFER_WIDTH))] = qrcodegen_getModule(qrCodeData, (y + invalidatedArea.x) / scale, (x + invalidatedArea.y) / scale) ? 0x0000 : 0xffff;
				}
			}
		}
		else {
			for (int y = 0; y < absInvalidated.height; y++)
			{
				for (int x = 0; x < absInvalidated.width; x++)
				{
					framebuffer[(absInvalidated.x + x) + ((absInvalidated.y + y) * (touchgfx::HAL::FRAME_BUFFER_WIDTH))] = qrcodegen_getModule(qrCodeData, (x + invalidatedArea.x) / scale, (y + invalidatedArea.y) / scale) ? 0x0000 : 0xffff;
				}
			}
		}
    }

    if (bitDepth == 24)
    {
		uint8_t* framebuffer = (uint8_t*)touchgfx::HAL::getInstance()->lockFrameBuffer();

		if (touchgfx::HAL::getInstance()->DISPLAY_ROTATION == touchgfx::DisplayRotation::rotate90)
		{
			for (int y = 0; y < absInvalidated.width; y++)
			{
				for (int x = 0; x < absInvalidated.height; x++)
				{
					framebuffer[((absInvalidated.y + x) * 3) + ((((touchgfx::HAL::DISPLAY_WIDTH - 1) - absInvalidated.x) - y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH)] = qrcodegen_getModule(qrCodeData, (y + invalidatedArea.x) / scale, (x + invalidatedArea.y) / scale) ? 0x00 : 0xff;
					framebuffer[((absInvalidated.y + x) * 3) + ((((touchgfx::HAL::DISPLAY_WIDTH - 1) - absInvalidated.x) - y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH) + 1] = qrcodegen_getModule(qrCodeData, (y + invalidatedArea.x) / scale, (x + invalidatedArea.y) / scale) ? 0x00 : 0xff;
					framebuffer[((absInvalidated.y + x) * 3) + ((((touchgfx::HAL::DISPLAY_WIDTH - 1) - absInvalidated.x) - y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH) + 2] = qrcodegen_getModule(qrCodeData, (y + invalidatedArea.x) / scale, (x + invalidatedArea.y) / scale) ? 0x00 : 0xff;
				}
			}
		}
		else{
			for (int y = 0; y < absInvalidated.height; y++)
			{
				for (int x = 0; x < absInvalidated.width; x++)
				{
					framebuffer[((absInvalidated.x + x) * 3) + ((absInvalidated.y + y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH)] = qrcodegen_getModule(qrCodeData, (x + invalidatedArea.x) / scale, (y + invalidatedArea.y) / scale) ? 0x00 : 0xff;
					framebuffer[((absInvalidated.x + x) * 3) + ((absInvalidated.y + y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH) + 1] = qrcodegen_getModule(qrCodeData, (x + invalidatedArea.x) / scale, (y + invalidatedArea.y) / scale) ? 0x00 : 0xff;
					framebuffer[((absInvalidated.x + x) * 3) + ((absInvalidated.y + y) * 3) * (touchgfx::HAL::FRAME_BUFFER_WIDTH) + 2] = qrcodegen_getModule(qrCodeData, (x + invalidatedArea.x) / scale, (y + invalidatedArea.y) / scale) ? 0x00 : 0xff;
				}
			}
		}
    }

    touchgfx::HAL::getInstance()->unlockFrameBuffer();
}

touchgfx::Rect QRCodeWidget::getSolidRect() const
{
    return touchgfx::Rect(0,0,getWidth(), getHeight());
}

void QRCodeWidget::setScale(int newScale)
{
    //Multiply the size of the QRCode Container by the scale
    //Every QR Code version has a specific size, so we can't use arbitrary dimensions
    scale = newScale;
    updateWidthAndHeight();
}

void QRCodeWidget::setQRCodeVersion(uint8_t newVersion)
{
    qrCodeVersion = newVersion;

    delete qrCodeData;
    qrCodeData = new uint8_t[qrcodegen_BUFFER_LEN_FOR_VERSION(qrCodeVersion)];
}

void QRCodeWidget::setErrorCorrectionLevel(enum qrcodegen_Ecc errCorLvl)
{
    //Different error correction levels are defined in qrcodegen.h
    errorCorectionLvl = errCorLvl;
}

void QRCodeWidget::updateWidthAndHeight()
{
    setWidth(sizeOfQRCodeSymbol * scale);
    setHeight(sizeOfQRCodeSymbol * scale);
}
