//this is a program for the social robot that i call Mr.Robot
//This is written on 12th July 2021 when the pandemic in Indonesia has worsens
//The purpose of this robot is to make friends with you

#define rodaKiri 7
#define SpeedR 5 //PWM
#define SpeedL 6
#define rodaKanan 4

#define encR A3
#define encL A2



struct package {
  int msg;
};
typedef struct package Package;
Package data[4];

struct command {
  int msg[4] = {0};
};
typedef struct command Command;
  Command cmd;

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

void writeData(int a, int b, int c, int d) {
  //proMicro.write((byte*)&data, sizeof(data));
  int Delay = 100;
  delay(Delay-50);
  //int tutup = millis() + Delay;
  //while(true) {
    //if(millis() > tutup) {
      //Serial.write((byte*)&data, sizeof(data));
      Serial1.print("0");
      Serial1.print(";");
      Serial1.print(a);
      Serial1.print(";");
      Serial1.print(b);
      Serial1.print(";");
      Serial1.print(c);
      Serial1.print(";");
      Serial1.print(d);
      Serial1.println(";$");
      
      
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



#include<SoftwareSerial.h>
int dataStatus;
SoftwareSerial proMicro(8, 9); // HC-12 TX Pin, HC-12 RX Pin 


boolean parsing = false;
char data_cek[20];
int nilai_int[6];
int p = 0;
void getSerialData(int *a, int *b, int *c, int *d) {
    while (proMicro.available() > 0) {
    char data_masuk = proMicro.read();
    data_cek[p] = data_masuk;
    p++;
    if(data_masuk == '$') parsing = true;
    if(parsing) {
      int q = 0;
      int sum;
      int i = 0;
      while (i < sizeof(data_cek)) {
      //for(int i = 0; i < 18; i++) { // ini misalnya 18 adalah panjang total karakter yang mau diparsing (data_masuk)      
        if(data_cek[i] == ';') {       // ;123;345;567;789;$ saya pake contoh ini, makanya panjangnya 18
          sum = 0;
          q++;
        }
        else {
          sum = sum*10 + (data_cek[i] - 48);
          nilai_int[q] = sum;
        }
        i++;
      }
      
      // hasil parsingannya bakal kesimpen di variabel nilai_int[1], nilai_int[2], dst
//      SerialUSB.print(" | ");
//      SerialUSB.print(nilai_int[1]);
//      SerialUSB.print(" | ");
//      SerialUSB.print(nilai_int[2]);
//      SerialUSB.print(" | ");
//      SerialUSB.print(nilai_int[3]);
//      SerialUSB.print(" | ");
//      SerialUSB.print(nilai_int[4]);
//      SerialUSB.println(" | ");
//      SerialUSB.print("\n");
      *a = nilai_int[1];
      *b = nilai_int[2];
      *c = nilai_int[3];
      *d = nilai_int[4];
      
      parsing = false;
      p = 0;
    }
  }
  delay(50);
}


void setup() {
  // put your setup code here, to run once:
  proMicro.begin(9600);
  Serial1.begin(9600);
  
  pinMode(rodaKiri, OUTPUT);
  pinMode(SpeedR, OUTPUT);
  pinMode(SpeedL, OUTPUT);
  pinMode(rodaKanan, OUTPUT);

  pinMode(encR, INPUT);
  pinMode(encL, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  static int maju=0, mundur=0, kiri=0, kanan=0;
  getSerialData(&maju,&mundur,&kiri,&kanan);

  /*
  if(kanan == true) Kanan();
  else if(kiri == true) Kiri();
  else if(maju == true) Maju();
  else if(mundur == true) Mundur();
  else Berhenti();*/

  //readEncoder();
  writeData(maju, mundur, kiri, kanan);
  
  
//  Serial.print("Nilai maju:");
//  Serial.print(maju);
//  Serial.print("Nilai mundur:");
//  Serial.print(mundur);
//  Serial.print("Nilai kiri:");
//  Serial.print(kiri);
//  Serial.print("Nilai kanan:");
//  Serial.println(kanan);

  /*
  dataStatus = readData();
  if(dataStatus == 1) {
    maju = data[0].msg; //posisi lurusnya 92 + 6(biar akurat)
    mundur = data[1].msg;
    kiri = data[2].msg;
    kanan = data[3].msg;
  }
  else if(dataStatus == 0) {
    maju = false; //posisi lurusnya 92 + 6(biar akurat)
    mundur = false;
    kiri = false;
    kanan = false;
  }

  Serial.print(maju);
  Serial.print(" ");
  Serial.print(mundur);
  Serial.print(" ");
  Serial.print(kiri);
  Serial.print(" ");
  Serial.println(kanan);
  delay(100);
  */

}


void Maju() {
  digitalWrite(rodaKanan, HIGH);
  digitalWrite(rodaKiri, LOW);
  analogWrite(SpeedR, 255);
  analogWrite(SpeedL, 255);
  Serial.println("MAJU!");
}


void Mundur() {
  digitalWrite(rodaKanan, LOW);
  digitalWrite(rodaKiri, HIGH);
  analogWrite(SpeedR, 255);
  analogWrite(SpeedL, 255);
  Serial.println("Mundur!");
}

void Kanan() {
  digitalWrite(rodaKanan, HIGH);
  digitalWrite(rodaKiri, HIGH);
  analogWrite(SpeedR, 200);
  analogWrite(SpeedL, 100);
  Serial.println("Kanan!");
}


void Kiri() {
  digitalWrite(rodaKanan, LOW);
  digitalWrite(rodaKiri, LOW);
  analogWrite(SpeedR, 100);
  analogWrite(SpeedL, 200);
  Serial.println("Kiri!");
}

void Berhenti() {
  analogWrite(SpeedR, 0);
  analogWrite(SpeedL, 0);
  Serial.println("Berhenti!");
}

void readEncoder() {
  Serial.print("Encoder right: ");
  Serial.println(analogRead(encR));
  Serial.print("Encoder left:");
  Serial.println(analogRead(encL));
}
