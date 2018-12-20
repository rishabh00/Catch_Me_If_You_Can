#ifndef _RGBMATRIXPANEL_H
#define _RGBMATRIXPANEL_H

#include "utilities.h"
#include "Adafruit_mfGFX.h"
#include "LabGPIO.hpp"

extern LabGPIO  P_addrA; //addrA
extern LabGPIO  P_addrB; //addrB
extern LabGPIO  P_addrC; //addrC
extern LabGPIO  P_addrD; //addrD
extern LabGPIO  P_LATCH; //LATCH
extern LabGPIO  P_OE; //OE
extern LabGPIO  P_CLOCK; //CLOCK
extern LabGPIO  P_R1; //R1
extern LabGPIO  P_G1; //G1
extern LabGPIO  P_B1; //B1
extern LabGPIO  P_R2; //R2
extern LabGPIO  P_G2; //G2
extern LabGPIO  P_B2; //B2

class RGBmatrixPanel : public Adafruit_GFX {

 public:

//  // Constructor for 16x32 panel:
//  RGBmatrixPanel(uint8_t a, uint8_t b, uint8_t c,
//    uint8_t sclk, uint8_t latch, uint8_t oe, bool dbuf, uint16_t width=32);

  // Constructor for 32x32 panel (adds 'd' pin):
  RGBmatrixPanel(bool dbuf, uint16_t width=32);

  virtual ~RGBmatrixPanel()
  {

  }

  void
    begin(void),
    drawPixel(int16_t x, int16_t y, uint16_t c),
    fillScreen(uint16_t c),
    updateDisplay(void),
    swapBuffers(bool),
    dumpMatrix(void);
  uint8_t
    *backBuffer(void);
  uint16_t
    Color333(uint8_t r, uint8_t g, uint8_t b),
    Color444(uint8_t r, uint8_t g, uint8_t b),
    Color888(uint8_t r, uint8_t g, uint8_t b),
    Color888(uint8_t r, uint8_t g, uint8_t b, bool gflag),
    ColorHSV(long hue, uint8_t sat, uint8_t val, bool gflag);

 private:

  uint8_t         *matrixbuff[2];
  uint8_t          nRows;
  volatile uint8_t backindex;
  volatile bool swapflag;

  // Init/alloc code common to both constructors:
  void init(uint8_t rows, bool dbuf, uint16_t width);

  uint8_t   _sclk, _latch, _oe, _a, _b, _c, _d;

    //void debugpanel(String message, int value);

  // Counters/pointers for interrupt handler:
  volatile uint8_t row, plane;
  volatile uint8_t *buffptr;
};

#endif
