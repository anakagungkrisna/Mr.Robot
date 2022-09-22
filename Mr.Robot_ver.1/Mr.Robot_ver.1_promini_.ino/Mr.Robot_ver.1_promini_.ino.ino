
//***ST7735 Display***//
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_CS     7
#define TFT_RST   6  // you can also connect this to the Arduino reset
#define TFT_DC    5
#define TFT_SCLK 3   // set these to be whatever pins you like!
#define TFT_MOSI 4   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


//***USB Input***//
#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//w = 26, s = 22, a = 4, d = 7, > = 79, < = 80, v = 81, ^ = 82
bool maju = false;
bool mundur = false;
bool kiri = false;
bool kanan = false;
int servoA = 100;
int servoB = 100;
bool incSrvA = false;
bool decSrvA = false;
bool incSrvB = false;
bool decSrvB = false;

struct package {
  int msg[4] = {0};
};

typedef struct package Package;
  Package data;


void writeData() {
  //proMicro.write((byte*)&data, sizeof(data));
  int Delay = 100;
  delay(Delay-50);
  //int tutup = millis() + Delay;
  //while(true) {
    //if(millis() > tutup) {
      //Serial.write((byte*)&data, sizeof(data));
      Serial.print("0");
      Serial.print(";");
      Serial.print(maju);
      Serial.print(";");
      Serial.print(mundur);
      Serial.print(";");
      Serial.print(kiri);
      Serial.print(";");
      Serial.print(kanan);
      Serial.println(";$");
      
      
//      Serial.print ("\ nSent:");
//      Serial.print (data.msg[0]);
//      Serial.print (" ");
//      Serial.print (data.msg[1]);
//      Serial.print (" ");
//      Serial.print (data.msg[2]);
//      Serial.print (" ");
//      Serial.print (data.msg[3]);
//      Serial.print (" ");

      if(incSrvB == true) servoB += 1;
      if(decSrvB == true) servoB -= 1;
      if(decSrvA == true) servoA -= 1;
      if(incSrvA == true) servoA += 1;
//      Serial.print (servoA);
//      Serial.print (" ");
//      Serial.println (servoB);

//      break;
//    }
//  }

}

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyUp	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
//  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
//  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
//  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
//  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

//  Serial.print(" >");
  PrintHex<uint8_t>(key, 0x80);
//  Serial.print("< ");

//  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
//  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
//  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
//  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
//  Serial.print("DN ");
//  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);
//  Serial.println(key);

  if (c)
    OnKeyPressed(c);

  //Fungsinya mulai disini. set true as long as key is pressed
  if(key == 26) maju = true;
  if(key == 22) mundur = true;
  if(key == 4) kiri = true;
  if(key == 7) kanan = true;
  if(key == 79) incSrvB = true;
  if(key == 80) decSrvB = true;
  if(key == 81) incSrvA = true;
  if(key == 82) decSrvA = true;
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    //Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    //Serial.println("LeftShift changed");
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    //Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    //Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    //Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    //Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    //Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    //Serial.println("RightGUI changed");
  }

}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
//  Serial.print("UP ");
//  PrintKey(mod, key);
  

    //Fungsinya mulai disini. set to false if key unpressed
  if(key == 26) maju = false;
  if(key == 22) mundur = false;
  if(key == 4) kiri = false;
  if(key == 7) kanan = false;

  if(key == 79) incSrvB = false;
  if(key == 80) decSrvB = false;
  if(key == 81) incSrvA = false;
  if(key == 82) decSrvA = false;
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
//  Serial.print("ASCII: ");
//  Serial.println((char)key);
};

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void setup()
{
  tft.initR(INITR_BLACKTAB);        // Initialize ST7735R screen
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Still in development with: Anak Agung Krisna Ananda Kusuma", ST77XX_WHITE);
  delay(1000);

  
  Serial.begin( 9600 );
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  //  Serial.println("Start");

  if (Usb.Init() == -1)
  //    Serial.println("OSC did not start.");

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop()
{
  
  Usb.Task();
//  if(maju == true) {
//    Maju();
//    Usb.Task();
//  }
//  if(mundur == true) {
//    Mundur();
//    Usb.Task();
//  }
//  if(kiri == true) {
//    Kiri();
//    Usb.Task();
//  }
//  if(kanan == true) {
//    Kanan();
//    Usb.Task();
//  }

  data.msg[0] = maju;
  data.msg[1] = mundur;
  data.msg[2] = kiri;
  data.msg[3] = kanan;

  writeData();
}


void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
