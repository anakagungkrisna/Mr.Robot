#define motorUL PB12
#define accUL PB7
#define motorDL PB13
#define accDL PB6
#define motorUR PB14
#define accUR PB8
#define motorDR PB15
#define accDR PB9


struct package {
  int msg;
};
typedef struct package Package;
Package data[4];

boolean parsing = false;
char data_cek[20];
int nilai_int[6];
int p = 0;
void getSerialData(int *a, int *b, int *c, int *d) {
    while (Serial1.available() > 0) {
    char data_masuk = Serial1.read();
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
      //SerialUSB.print("\n");
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
  pinMode(motorUL, OUTPUT);
  pinMode(motorDL, OUTPUT);
  pinMode(motorUR, OUTPUT);
  pinMode(motorDR, OUTPUT);
  pinMode(accUL, OUTPUT);
  pinMode(accDL, OUTPUT);
  pinMode(accUR, OUTPUT);
  pinMode(accDR, OUTPUT);

  pinMode(PC13, OUTPUT);
  Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  static int maju=0, mundur=0, kiri=0, kanan=0;
  getSerialData(&maju,&mundur,&kiri,&kanan);
  if(kanan == true) rotateRight();
  else if(kiri == true) rotateLeft();
  else if(maju == true) forward();
  else if(mundur == true) backward();
  else Stop();


  /*
  sideRight();
  digitalWrite(PC13, HIGH);
  delay(2000);
  sideLeft();
  digitalWrite(PC13, LOW);
  delay(2000);

  rotateRight();
  digitalWrite(PC13, HIGH);
  delay(2000);
  rotateLeft();
  digitalWrite(PC13, LOW);
  delay(2000);

  forward();
  digitalWrite(PC13, HIGH);
  delay(2000);
  backward();
  digitalWrite(PC13, LOW);
  delay(2000);
  */
}



void sideRight(void) {
  digitalWrite(motorUL, HIGH);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, HIGH);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, HIGH);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, HIGH);
  analogWrite(accDR, 150);
}

void sideLeft(void) {
  digitalWrite(motorUL, LOW);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, LOW);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, LOW);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, LOW);
  analogWrite(accDR, 150);
}

void rotateRight(void) {
  digitalWrite(motorUL, HIGH);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, LOW);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, HIGH);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, LOW);
  analogWrite(accDR, 150);
}

void rotateLeft(void) {
  digitalWrite(motorUL, LOW);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, HIGH);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, LOW);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, HIGH);
  analogWrite(accDR, 150);
}

void forward(void) {
  digitalWrite(motorUL, LOW);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, HIGH);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, HIGH);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, LOW);
  analogWrite(accDR, 150);
}

void backward(void) {
  digitalWrite(motorUL, HIGH);
  analogWrite(accUL, 150);
  digitalWrite(motorDL, LOW);
  analogWrite(accDL, 150);
  digitalWrite(motorUR, LOW);
  analogWrite(accUR, 150);
  digitalWrite(motorDR, HIGH);
  analogWrite(accDR, 150);
}

void Stop(void) {
  analogWrite(accUL, 0);
  analogWrite(accDL, 0);
  analogWrite(accUR, 0);
  analogWrite(accDR, 0);
}
