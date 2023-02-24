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
#include "ice_usb.h"

enum {
    ITF_NUM_CDC0, ITF_NUM_CDC0_DATA,
    ITF_NUM_MSC0,
    ITF_NUM_DFU,
    ITF_NUM_TOTAL
};

uint8_t const tud_desc_configuration[CONFIG_TOTAL_LEN] = {
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 500/*mA*/),
    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC0, STRID_CDC+0, EPIN+1, 8, EPOUT+2, EPIN+2, 64),
    TUD_MSC_DESCRIPTOR(ITF_NUM_MSC0, STRID_MSC+0, EPOUT+3, EPIN+3, 64),
    TUD_DFU_DESCRIPTOR(ITF_NUM_DFU, CFG_TUD_DFU_ALT, STRID_DFU, DFU_ATTR_CAN_DOWNLOAD, 1000, CFG_TUD_DFU_XFER_BUFSIZE),
};

char const *tud_string_desc[STRID_NUM_TOTAL] = {
    [STRID_LANGID]          = USB_LANG_EN,
    [STRID_MANUFACTURER]    = USB_MANUFACTURER,
    [STRID_PRODUCT]         = USB_PRODUCT,
    [STRID_SERIAL_NUMBER]   = usb_serial_number,
    [STRID_VENDOR]          = USB_VENDOR,
    [STRID_CDC+0]           = "RP2040 UART",
    [STRID_DFU+0]           = "iCE40 DFU (flash)",
    [STRID_DFU+1]           = "iCE40 DFU (CRAM)",
    [STRID_MSC+0]           = "iCE40 MSC (flash)",
};
