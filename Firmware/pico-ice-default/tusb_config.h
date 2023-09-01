/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 * Copyright (c) 2022 TinyVision.ai Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

// pico-ice-sdk
#include "ice_flash.h"
#include "boards/pico_ice.h"

// RHPort number used for device can be defined by board.mk, port 0 for pico-ice
#define BOARD_DEVICE_RHPORT_NUM     0

// Device mode with rhport and speed defined by board.mk
#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE

// Either full or high speed supported by RP2040
#define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_FULL_SPEED

// Enable Device stack
#define CFG_TUD_ENABLED             1

// Default is max speed that hardware controller could support with on-chip PHY
#define CFG_TUD_MAX_SPEED           OPT_MODE_FULL_SPEED

// Device classes
#define CFG_TUD_CDC                 3
#define CFG_TUD_MSC                 1
#define CFG_TUD_DFU                 1
#define CFG_TUD_DFU_ALT             2
#define CFG_TUD_HID                 0
#define CFG_TUD_MIDI                0
#define CFG_TUD_VENDOR              0

// Configure the TinyUF2 drag-and-drop to USB drive for FPGA-programming
#define ICE_USB_USE_TINYUF2_MSC     1

// Configure 2-way forwarding between USB CDC1 and UART
#define ICE_USB_UART0_CDC           1

// Configure 2-way forwarding between USB CDC2 and SPI
#define ICE_USB_SPI_CDC             2

// CDC FIFO size of TX and RX and Endpoint buffer size
#define CFG_TUD_CDC_RX_BUFSIZE      512
#define CFG_TUD_CDC_TX_BUFSIZE      512
#define CFG_TUD_CDC_EP_BUFSIZE      512

// MSC Buffer size of Device Mass storage
#define CFG_TUD_MSC_BUFSIZE         ICE_FLASH_SECTOR_SIZE

// Must be a multiple of flash page size
#define CFG_TUD_DFU_XFER_BUFSIZE    256
