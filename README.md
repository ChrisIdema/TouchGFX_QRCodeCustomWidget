# TouchGFX_QRCodeCustomWidget
QRCodeCustomWidget for TouchGFX

Forked from https://community.st.com/t5/stm32-mcus-touchgfx-and-gui/share-your-custom-widgets/m-p/653550/highlight/true#M36786
by user "Mohammad MORADI ESFAHANIASL"

A custom QR Code widget with you that you can use to create a QR Code either from text provided in the code or text from a Text Area in the designer. 
It is worth mentioning that the size of the QR Code symbol depends on the version you choose (from 1 to 40, you can read more about the different sizes [here](https://www.qrcode.com/en/about/version.html)) and the scale (i.e. multiply factor). 

# How to use

* export to tpkg file using `git archive --format=zip --output=QRCodeCustomContainer.tpkg HEAD`
* import in TouchGFX using Edit/Import/Custom Container

