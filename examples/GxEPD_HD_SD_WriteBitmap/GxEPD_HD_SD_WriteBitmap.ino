// GxEPD_HD_SD_WriteBitmap: utility for Display Library for HD e-Paper displays from Dalian Good Display Inc. (parallel interface).
//
// Display Library based on Demo Example available from Good Display
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD_HD

#include <GxEPD_HD.h>

#include "bitmaps/Bitmap_Tiger_320x240x24_4Bit.h"

// include SdFat for FAT32 support with long filenames; available through Library Manager
#include <SdFat.h>

#if defined(SdFat_h)
SdFat SD;
#define FileClass SdFile
#define position curPosition
#define seek seekSet
#else
#include <SD.h>
#define FileClass File
#undef SdFat_h
#endif

void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  if (!SD.begin(SS))
  {
    Serial.println("initialization failed!");
    while (1) yield();
  }
  Serial.println("initialization done.");
  writeBitmaps();
}

void loop()
{
}

//void writeBitmap(const char filename[], const uint8_t bitmap[], int16_t w, int16_t h, uint16_t depth = 1);
uint8_t filldata_1[] = {0x0, 0x23, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0};
uint8_t filldata_4[] = {0x0, 0x0, 0x0, 0x0, 0x12, 0xB, 0x0, 0x0, 0x12, 0xB, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x11, 0x11, 0x11,
                        0xFF, 0x22, 0x22, 0x22, 0xFF, 0x33, 0x33, 0x33, 0xFF, 0x44, 0x44, 0x44, 0xFF, 0x55, 0x55, 0x55, 0xFF, 0x66, 0x66, 0x66, 0xFF, 0x77, 0x77, 0x77,
                        0xFF, 0x88, 0x88, 0x88, 0xFF, 0x99, 0x99, 0x99, 0xFF, 0xAA, 0xAA, 0xAA, 0xFF, 0xBB, 0xBB, 0xBB, 0xFF, 0xCC, 0xCC, 0xCC, 0xFF, 0xDD, 0xDD, 0xDD,
                        0xFF, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
                       };

void writeBitmaps()
{
#ifdef _GxBitmap_Tiger_320x240x24_4Bit_H_
  writeBitmap("GxBitmap_Tiger_320x240x24_4Bit.bmp", GxBitmap_Tiger_320x240x24_4Bit, 320, 240, 4);
#endif
}

void writeBitmap(const char filename[], const uint8_t bitmap[], int16_t w, int16_t h, uint16_t depth)
{
  FileClass bitmapFile;
  uint32_t ppb = 8 / depth; // pixel per byte
  uint32_t rowSizeCode = (w + ppb - 1) / ppb;
  // BMP rows are padded (if needed) to 4-byte boundary
  uint32_t rowSizeBMP = (rowSizeCode + 3) & ~3;
  Serial.print("writeBitmap(\""); Serial.print(filename); Serial.println("\")");
  Serial.print("rowSizeCode "); Serial.println(rowSizeCode);
  Serial.print("rowSizeBMP  "); Serial.println(rowSizeBMP);
  uint32_t headerSize = 40;
  uint32_t imageOffset = depth == 1 ? 62 : 118; // until known better
  uint32_t fileSize = imageOffset + h * rowSizeBMP;
#if defined(SdFat_h)
  if (bitmapFile.open(filename, FILE_WRITE))
#else
  bitmapFile = SD.open(filename, FILE_WRITE);
  if (bitmapFile)
#endif
  {
    bitmapFile.seek(0);
    write16(bitmapFile, 0x4D42); // BMP signature
    write32(bitmapFile, fileSize); // fileSize
    write32(bitmapFile, 0); // creator bytes
    write32(bitmapFile, imageOffset); // image offset
    write32(bitmapFile, headerSize); // Header size
    write32(bitmapFile, w); // image width
    write32(bitmapFile, h); // image height
    write16(bitmapFile, 1); // # planes
    write16(bitmapFile, depth); // // bits per pixel
    write32(bitmapFile, 0); // format uncompressed

    //Serial.print("first position "); Serial.println(bitmapFile.position());
    uint32_t j = 0;
    uint8_t* filldata = filldata_1;
    uint32_t filldata_size = sizeof(filldata);
    if (depth == 4)
    {
      filldata = filldata_4;
      filldata_size = sizeof(filldata_4);
    }
    for (uint32_t i = bitmapFile.position(); i < imageOffset; i++)
    {
      //bitmapFile.write(uint8_t(0)); // remaining header bytes
      bitmapFile.write(j < filldata_size ? filldata[j++] : 0); // remaining header bytes
    }
    Serial.print("start position "); Serial.println(bitmapFile.position());
    uint32_t rowidx = (h - 1) * rowSizeCode; // in reverse order
    for (uint16_t row = 0; row < h; row++) // for each line
    {
      uint32_t colidx;
      for (colidx = 0; colidx < rowSizeCode; colidx++)
      {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
        uint8_t data = pgm_read_byte(&bitmap[rowidx + colidx]);
#else
        uint8_t data = bitmap[rowidx + colidx];
#endif
        bitmapFile.write(data);
      }
      rowidx -= rowSizeCode; // in reverse order
      while (colidx++ < rowSizeBMP) bitmapFile.write(uint8_t (0)); // padding
      //Serial.println(bitmapFile.position());
    }
    Serial.println(bitmapFile.position());
    bitmapFile.close();
    Serial.println("done");
  }
  else Serial.print("open file for write failed!");
}

void write16(FileClass & f, uint16_t v)
{
  f.write(uint8_t(v));
  f.write(uint8_t(v >> 8));
}

void write32(FileClass & f, uint32_t v)
{
  f.write(uint8_t(v));
  f.write(uint8_t(v >> 8));
  f.write(uint8_t(v >> 16));
  f.write(uint8_t(v >> 24));
}
