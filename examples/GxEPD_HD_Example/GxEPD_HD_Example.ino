// GxEPD_HD_Example : example for HD e-Paper displays from Dalian Good Display Inc. (parallel interface).
//
// To be used with "STM32F103VE" of "Generic STM32F103V series" of package "STM32 Boards (STM32Duino.com)" for Arduino.
// install package with Boards Manager after adding to preferences in additional Boards Manager URLs:
// https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/master/STM32/package_stm_index.json
//
// The e-paper display and demo board is available from:
// http://www.buy-lcd.com/index.php?route=product/product&path=2897_10571_10574&product_id=57650
// or https://www.aliexpress.com/store/product/6-inch-HD-Interface-High-resolution-electronic-paper-display-e-ink-epaper-with-TCON-Demo-Kit/600281_32838449413.html

// include library, include base class, make path known
#include <GxEPD_HD_EPD.h>
#include <GxEPD_HD_BW.h>

// select the display io class to use, only one
GxDESTM32T io;
// select the base display class to use, only one
GxGDE06BA base_display(io);

// select the graphics display template class to use, only one
GxEPD_HD_BW<GxGDE06BA, GxGDE06BA::HEIGHT> display(base_display); // full height, one page, no RAM remaining
//GxEPD_HD_BW < GxGDE06BA, GxGDE06BA::HEIGHT / 2 > display(base_display); // half height, 2 pages, ~30k RAM remaining

//#include "bitmaps/BitmapExamples.h"

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// select diagnostic output stream, only one
//HardwareSerial& DiagnosticStream = Serial1; // pins PA9, PA10
HardwareSerial& DiagnosticStream = Serial2; // pins PA2, PA3 for USB jumpers
//HardwareSerial& DiagnosticStream = Serial3; // pins PB10, PB11
//USBSerial& DiagnosticStream = Serial; // pins PA11, PA12 USB direct?

void setup()
{
  //  Serial.begin(115200);
  //  delay(200);
  //  Serial.println();
  //  Serial.println("setup");
  //  Serial.println("hello Serial");
  //  delay(200);

  //  Serial1.begin(115200);
  //  delay(200);
  //  Serial1.println();
  //  Serial1.println("setup");
  //  Serial1.println("hello Serial1");
  //  delay(200);

  //  Serial2.begin(115200);
  //  delay(200);
  //  Serial2.println();
  //  Serial2.println("setup");
  //  Serial2.println("hello Serial2");
  //  delay(200);

  DiagnosticStream.begin(115200);
  delay(200);
  DiagnosticStream.println();
  DiagnosticStream.println("setup");
  DiagnosticStream.println("hello DiagnosticStream");

  delay(200);
  display.init(&DiagnosticStream);
#ifndef _GxBitmapExamples_H_
  io.demo();
#endif
  helloWorld();
  delay(1000);
  // partial refresh mode can be used to full screen,
  // effective if display panel hasFastPartialUpdate
  helloFullScreenPartialMode();
  delay(1000);
  helloArduino();
  delay(1000);
  helloEpaper();
  delay(1000);
  showBitmapExample();
  showFont("FreeMonoBold24pt7b", &FreeMonoBold24pt7b);
  showPartialUpdate();
  //showPartialUpdatePaged();
  DiagnosticStream.println("setup done");
}

void loop()
{
  //  showBitmapExample();
  //  showFont("FreeMonoBold9pt7b", &FreeMonoBold9pt7b);
  //  showFont("FreeMonoBold12pt7b", &FreeMonoBold12pt7b);
  //  showFont("FreeMonoBold18pt7b", &FreeMonoBold18pt7b);
  //  showFont("FreeMonoBold24pt7b", &FreeMonoBold24pt7b);
  delay(30000);
}

void helloWorld()
{
  //DiagnosticStream.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 2;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println("Hello World!");
  }
  while (display.nextPage());
  //DiagnosticStream.println("helloWorld done");
}

void helloFullScreenPartialMode()
{
  //DiagnosticStream.println("helloFullScreenPartialMode");
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    uint16_t x = (display.width() - 160) / 2;
    uint16_t y = display.height() / 2;
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println("Hello World!");
    y = display.height() / 4;
    display.setCursor(x, y);
    display.println("full screen");
    y = display.height() * 3 / 4;
    if (display.width() <= 200) x = 0;
    display.setCursor(x, y);
    if (display.epd2.hasFastPartialUpdate)
    {
      display.println("fast partial mode");
    }
    else if (display.epd2.hasPartialUpdate)
    {
      display.println("slow partial mode");
    }
    else
    {
      display.println("no partial mode");
    }
  }
  while (display.nextPage());
  //DiagnosticStream.println("helloFullScreenPartialMode done");
}

void helloArduino()
{
  //DiagnosticStream.println("helloArduino");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 4;
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println("Hello Arduino!");
  }
  while (display.nextPage());
  delay(1000);
  //DiagnosticStream.println("helloArduino done");
}

void helloEpaper()
{
  //DiagnosticStream.println("helloEpaper");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() * 3 / 4;
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println("Hello E-Paper!");
  }
  while (display.nextPage());
  //DiagnosticStream.println("helloEpaper done");
}

void showBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial)
{
  //DiagnosticStream.println("showBox");
  display.setRotation(1);
  if (partial)
  {
    display.setPartialWindow(x, y, w, h);
  }
  else
  {
    display.setFullWindow();
  }
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
  }
  while (display.nextPage());
  //DiagnosticStream.println("showBox done");
}

void drawCornerTest()
{
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  for (uint16_t r = 0; r <= 4; r++)
  {
    display.setRotation(r);
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
      display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
      display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
      display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);
      display.setCursor(display.width() / 2, display.height() / 2);
      display.print(display.getRotation());
    }
    while (display.nextPage());
    delay(2000);
  }
}

void showBitmapExample()
{
#ifdef _GxBitmapExamples_H_
  display.drawImage(BitmapExample1, sizeof(BitmapExample1), 2, 0, 0, display.epd_hd.WIDTH, display.epd_hd.HEIGHT);
  delay(2000);
  //display.erasePicture(BitmapExample1, sizeof(BitmapExample1));
  display.drawImage(BitmapExample2, sizeof(BitmapExample2), 2, 0, 0, display.epd_hd.WIDTH, display.epd_hd.HEIGHT);
  delay(2000);
  //display.erasePicture(BitmapExample2, sizeof(BitmapExample2));
  display.setRotation(0);
  display.setFullWindow();
  if (1 == display.pages())
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_1, 640, 384, GxEPD_BLACK);
    display.display();
    delay(2000);
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_2, 640, 384, GxEPD_BLACK);
    display.display();
    delay(2000);
  }
  else
  {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_1, 640, 384, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_2, 640, 384, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
  }
#endif
}

void showFont(const char name[], const GFXfont* f)
{
  display.setFullWindow();
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 0);
    display.println();
    display.println(name);
    display.println(" !\"#$%&'()*+,-./");
    display.println("0123456789:;<=>?");
    display.println("@ABCDEFGHIJKLMNO");
    display.println("PQRSTUVWXYZ[\\]^_");
    display.println("`abcdefghijklmno");
    display.println("pqrstuvwxyz{|}~ ");
  }
  while (display.nextPage());
  delay(2000);
}

void showPartialUpdate()
{
  if (display.pages() > 1) return showPartialUpdatePaged();
  display.setFullWindow();
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  float value = 13.95;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(0);
  // draw background
  display.fillScreen(GxEPD_WHITE);
#ifdef _GxBitmapExamples_H_
  //display.drawExampleBitmap(BitmapExample1, 0, 0, display.epd_hd.WIDTH, display.epd_hd.HEIGHT, GxEPD_BLACK);
  display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_2, 640, 384, GxEPD_BLACK);
#else
  helloWorld();
#endif
  display.display();
  delay(2000);

  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
    display.displayWindow(box_x, box_y, box_w, box_h);
    delay(2000);
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    display.displayWindow(box_x, box_y, box_w, box_h);
    delay(1000);
  }
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    // reset the background
    display.fillScreen(GxEPD_WHITE);
    display.setRotation(0);
#ifdef _GxBitmapExamples_H_
    //display.drawExampleBitmap(BitmapExample1, 0, 0, display.epd_hd.WIDTH, display.epd_hd.HEIGHT, GxEPD_BLACK);
    display.drawBitmap((display.epd_hd.WIDTH - 640) / 2, (display.epd_hd.HEIGHT - 384) / 2, bwBitmap640x384_2, 640, 384, GxEPD_BLACK);
#else
    helloWorld();
#endif
    display.displayWindow(0, 0, display.epd_hd.WIDTH, display.epd_hd.HEIGHT);
    display.setRotation(r);
    for (uint16_t i = 1; i <= 10; i++)
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
      display.setCursor(box_x, cursor_y);
      display.print(value * i, 2);
      display.displayWindow(box_x, box_y, box_w, box_h);
      delay(500);
    }
    delay(2000);
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    display.displayWindow(box_x, box_y, box_w, box_h);
  }
  display.setRotation(0);
  //display.powerDown();
}

void showPartialUpdatePaged()
{
  // some useful background
  helloWorld();
  delay(1000);
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(1000);
  }
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    for (uint16_t i = 1; i <= 10; i += incr)
    {
      display.firstPage();
      do
      {
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.setCursor(box_x, cursor_y);
        display.print(value * i, 2);
      }
      while (display.nextPage());
      delay(500);
    }
    delay(1000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(1000);
  }
}

