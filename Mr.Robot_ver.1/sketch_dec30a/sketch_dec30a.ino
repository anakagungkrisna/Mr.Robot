#include <LedControl.h>
//DIN(1) = 16 / 4
//LOAD(12) = 14 / 7
//SCK(8) = 15 / 6
//no. of connected MAX7219 = 1
LedControl lc=LedControl(4,6,7,1);

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);// clear screen

  Serial.begin(9600);
}
//37
void loop() {
  // put your main code here, to run repeatedly:

  /*
   for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true); // turns on LED at col, row
      delay(500);
      Serial.print(row);
      Serial.println(col);
    }
  }

  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false); // turns off LED at col, row
      delay(500);
      Serial.print(row);
      Serial.println(col);
    }
  }
  */
  
  lc.setLed(0,0,4,false);
  lc.setLed(0,4,4,false);
  delay(1000);
  lc.setLed(0,0,4,true);
  lc.setLed(0,4,4,true);
  delay(1000);
  
}
