# STM32_FS_USB_CDC_device_CMSIS
STM32F105 USB FS (OTG_FS) CDC Device (Virtual Com Port) CMSIS, no HAL, Keil, CubeIDE and GCC

This is an implementation of my library (USB_OTG_FS CDC-device) in STM32 (STM32F105).

This example shows how to use it along with a circular buffer.

Usage:

1. Use EndPoint[1].rxCallBack function to handle the data coming from host (COM-port terminal).

2. Use EndPoint[1].setTxBuffer function to set and send the data you want to send to host.

3. Edit usb_cdc_desc.h file, if you want to use different descriptors than provided with STM HAL example.

