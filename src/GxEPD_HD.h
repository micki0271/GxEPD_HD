// Display Library for parallel interface e-paper panels from Dalian Good Display Co., Ltd.: www.e-paper-display.com
//
// based on Demo Examples from Good Display, available here: http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// class GxEPD_HD : Library header class with common definitions.
//
// Author : J-M Zingg
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// Library: https://github.com/ZinggJM/GxEPD_HD

#ifndef _GxEPD_HD_H_
#define _GxEPD_HD_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>

// the only colors supported by any of these displays; mapping of other colors is class specific, common for GxEPD, GxEPD2 and GxEPD_HD
#define GxEPD_BLACK     0x0000
#define GxEPD_DARKGREY  0x7BEF      /* 128, 128, 128 */
#define GxEPD_LIGHTGREY 0xC618      /* 192, 192, 192 */
#define GxEPD_WHITE     0xFFFF
#define GxEPD_RED       0xF800      /* 255,   0,   0 */
#define GxEPD_YELLOW    GxEPD_RED
#define GxEPD_COLORED   GxEPD_RED
// GxEPD_HD panels support 16 levels of grey

class GxEPD_HD
{
  public:
    enum Panel
    {
      GDE043A2,
      GDE060BA,
      GDEW080T5
    };
};

#endif
