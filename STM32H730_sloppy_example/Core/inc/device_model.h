#ifndef DEVICE_MODEL_H_INCLUDED
#define DEVICE_MODEL_H_INCLUDED

#define MDK_ARM_ENV // if MDK ARM Keil IDE is used

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)


#define USB_CDC_CIRC_BUF_USED
#if defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define USB_CDC_CIRC_BUFFER_SIZE 0x100 // 0x800UL*2
#else 
#define USB_CDC_CIRC_BUFFER_SIZE 0x200UL*2// 0x400UL*2
#endif


#define USB_FS_IRQ_P 4


#endif /* DEVICE_MODEL_H_INCLUDED*/
