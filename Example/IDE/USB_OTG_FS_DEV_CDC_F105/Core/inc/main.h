#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/****************************************************************
* A device based on STM32F105
*
*
* Alex Svetlichnyy 2018 svetlal@outlook.com
*****************************************************************/

#include "stm32f1xx.h"
#include "stm32f105xc.h"
#include "stm32f105_clock.h"
#include "stm32f105_usbdfs_cdc.h"
#include "stm32f105_usbdfs_macros.h"

#define LOBYTE(x) ((uint8_t)x)
#define HIBYTE(x) ((uint8_t)(x >> 8))

#endif /* MAIN_H_INCLUDED*/
