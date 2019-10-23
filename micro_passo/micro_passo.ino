#define PWM 255
#define razaoPWM 256       //resolução do micropasso
#define ciclosVolta 25    //ciclos da função por volta no motor (possivelmente errado)
#define R 0.03            //raio da roda;
#define minTime 10        //80us pra 16PWM
#include <TimerOne.h>
#include <Wire.h>
#include <VL53L0X.h>

//CAMÊRA
char teste = 'x';
int flag = 0;

//SENSORES INFRAVERMELHOS
VL53L0X sensor;
VL53L0X sensor2;
VL53L0X sensor3;
int inf_e = 8;
int inf_m = 12;
int inf_d = 13;


//PINOS MOTORES DE PASSO
int a1 = 5;
int a2 = 9;
int b1 = 6;
int b2 = 10;

//PINOS SENSOR DE COR
int S2 = 2;   //9
int S3 = 4;   //10
int OUT = 7;  //8
int red;
int green;
int blue;

bool foundBox = false;

unsigned int tempo = minTime;

int distCiclos(float dist) { //distância linear em metros
  return ciclosVolta * (dist / (2 * PI * R));
}

double RPM(int t, int r) {
  return 60 / ((49152 / r + 192) * (t * 0.000001));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void passoCompleto(int ciclos) {
  for (int j = 0; j < ciclos; j++) { 

    Serial.println("aqui");
    for(int i=0; i<8 ; i++){

      PORTB = B00111111;
      delay(1000);
      PORTB = B00000000;
      delay(1000);
      }
    
  }//for int j
}// void counterClockwise
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void counterClockwise(int ciclos) {
  for (int j = 0; j < ciclos; j++) { 
//    if (j >= (int)(0.2*ciclos) && j <= (int)(0.8*ciclos)) {
//      tempo = minTime;
//    }
//    else if (j < (int)(0.2*ciclos)) {
//      tempo = minTime * 0.5 * ((int)(0.2*ciclos) - j);
//    }
//    else {
//      tempo = minTime * 0.5 * (j - (int)(0.8*ciclos));
//    }
//      
    //0->45°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, PWM);
      if((i * razaoPWM - 1) > PWM){
        analogWrite(b1, PWM);
      }
      else{
        analogWrite(b1, (i * razaoPWM - 1));
      }
      analogWrite(a2, 0);
      analogWrite(b2, 0);
      delay(tempo);
    }
    //45->90°
    for (int i = 1; i <= (PWM + 1) / razaoPWM; i++) {
      if((PWM - (i * razaoPWM - 1)) < 0){
        analogWrite(a1, 0);
      }
      else{
        analogWrite(a1, PWM - (i * razaoPWM - 1));
      }
      analogWrite(b1, PWM);
      analogWrite(a2, 0);
      analogWrite(b2, 0);
      delay(tempo);
    }
    //90->135°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, 0);
      analogWrite(b1, PWM);
      if((i * razaoPWM - 1) > PWM){
        analogWrite(a2, 0);
      }
      else{
        analogWrite(a2, (i * razaoPWM - 1));
      }
      analogWrite(b2, 0);
      delay(tempo);
    }
    //135->180°
    for (int i = 1; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, 0);
      if((PWM - (i * razaoPWM - 1)) < 0){
        analogWrite(b1, 0);
      }
      else{
        analogWrite(b1, PWM - (i * razaoPWM - 1));
      }
      analogWrite(a2, PWM);
      analogWrite(b2, 0);
      delay(tempo);
    }
    //180->225°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, 0);
      analogWrite(b1, 0);
      analogWrite(a2, PWM);
      if((i * razaoPWM - 1) > PWM){
        analogWrite(b2, 0);
      }
      else{
        analogWrite(b2, (i * razaoPWM - 1));
      }
      delay(tempo);
    }
    //225->270°
    for (int i = 1; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, 0);
      analogWrite(b1, 0);
      if((PWM - (i * razaoPWM - 1)) < 0){
        analogWrite(a2, 0);
      }
      else{
        analogWrite(a2, PWM - (i * razaoPWM - 1));
      }
      analogWrite(b2, PWM);
      delay(tempo);
    }
    //270->315°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      if((i * razaoPWM - 1) > PWM){
        analogWrite(a1, 0);
      }
      else{
        analogWrite(a1, (i * razaoPWM - 1));
      }
      analogWrite(b1, 0);
      analogWrite(a2, 0);
      analogWrite(b2, PWM);
      delay(tempo);
    }
    //315->360°
    for (int i = 1; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(a1, PWM);
      analogWrite(b1, 0);
      analogWrite(a2, 0);
      if((PWM - (i * razaoPWM - 1)) < 0){
        analogWrite(b2, 0);
      }
      else{
        analogWrite(b2, PWM - (i * razaoPWM - 1));
      }
      delay(tempo);
    }
  }
}

void clockwise(int ciclos) {
  for (int j = 0; j < ciclos; j++) {
    if (j >= ciclosVolta && j <= (ciclos - ciclosVolta)) {
      tempo = minTime;
    }
    else if (j < ciclosVolta) {
      tempo = minTime * 0.25 * (ciclosVolta - j);
    }
    else {
      tempo = minTime * 0.25 * (j - (ciclos - ciclosVolta));
    }
    //0->45°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM);
      analogWrite(a1, (i * razaoPWM - 1));
      analogWrite(b2, 0);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //45->90°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM - (i * razaoPWM - 1));
      analogWrite(a1, PWM);
      analogWrite(b2, 0);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //90->135°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, PWM);
      analogWrite(b2, (i * razaoPWM - 1));
      analogWrite(a2, 0);
      delay(tempo);
    }
    //135->180°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, PWM - (i * razaoPWM - 1));
      analogWrite(b2, PWM);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //180->225°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, 0);
      analogWrite(b2, PWM);
      analogWrite(a2, (i * razaoPWM - 1));
      delay(tempo);
    }
    //225->270°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, 0);
      analogWrite(b2, PWM - (i * razaoPWM - 1));
      analogWrite(a2, PWM);
      delay(tempo);
    }
    //270->315°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, (i * razaoPWM - 1));
      analogWrite(a1, 0);
      analogWrite(b2, 0);
      analogWrite(a2, PWM);
      delay(tempo);
    }
    //315->360°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM);
      analogWrite(a1, 0);
      analogWrite(b2, 0);
      analogWrite(a2, PWM - (i * razaoPWM - 1));
      delay(tempo);
    }
  }
}
void voltaInfinita(){
    //0->45°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM);
      analogWrite(a1, (i * razaoPWM - 1));
      analogWrite(b2, 0);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //45->90°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM - (i * razaoPWM - 1));
      analogWrite(a1, PWM);
      analogWrite(b2, 0);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //90->135°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, PWM);
      analogWrite(b2, (i * razaoPWM - 1));
      analogWrite(a2, 0);
      delay(tempo);
    }
    //135->180°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, PWM - (i * razaoPWM - 1));
      analogWrite(b2, PWM);
      analogWrite(a2, 0);
      delay(tempo);
    }
    //180->225°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, 0);
      analogWrite(b2, PWM);
      analogWrite(a2, (i * razaoPWM - 1));
      delay(tempo);
    }
    //225->270°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, 0);
      analogWrite(a1, 0);
      analogWrite(b2, PWM - (i * razaoPWM - 1));
      analogWrite(a2, PWM);
      delay(tempo);
    }
    //270->315°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, (i * razaoPWM - 1));
      analogWrite(a1, 0);
      analogWrite(b2, 0);
      analogWrite(a2, PWM);
      delay(tempo);
    }
    //315->360°
    for (int i = 0; i <= (PWM + 1) / razaoPWM; i++) {
      analogWrite(b1, PWM);
      analogWrite(a1, 0);
      analogWrite(b2, 0);
      analogWrite(a2, PWM - (i * razaoPWM - 1));
      delay(tempo);
    }
}

void color() {
  // ----- OBS: Os valores dessa tabela irão variar dependendo da luminosidade do local. ------
  /* Tabela de Valores do RGB das Cores
         COR  | RED | GREEN | BLUE |
       PRETO  | 13  |   22  |  20  |
     VERMELHO | 06  |   14  |  12  |
       VERDE  | 11  |   16  |  15  |
        AZUL  | 12  |   18  |  13  |
       CINZA  | 06  |   08  |  07  |
       BRANCO | 04  |   04  |  04  |
  */

  if (red < 11) {
    Serial.print(red);
    Serial.print(" : ");
    Serial.print(blue);
    Serial.print(" : ");
    Serial.println(green);
}

  else if (11 < red && red < 25 && green < 20) {
    Serial.print(red);
    Serial.print(" : ");
    Serial.print(blue);
    Serial.print(" : ");
    Serial.println(green);
  }

  else if (20 < red) {
    Serial.print(red);
    Serial.print(" : ");
    Serial.print(blue);
    Serial.print(" : ");
    Serial.println(green);
  }
}

void calculo_RGB() {
  //Seleciona leitura com filtro para vermelho de acordo com a tabela lembra?
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  //Lê duração do pulso em LOW
  red = pulseIn(OUT, LOW);  // Função que retorna a duração do pulso em ms

  //Seleciona leitura com filtro para verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  //Lê duração do pulso em LOW
  green = pulseIn(OUT, LOW);

  //Seleciona leitura com filtro para azul
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  //Lê duração do pulso em LOW
  blue = pulseIn(OUT, LOW);

  color();
}

void infravermelho() {
  Serial.println("__________________________________________________________________");
  Serial.println("");
  Serial.println("=================================");
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 30; i++) {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println("=================================");


  //CHECK DISTANCES
  long DISTANCE_FWD = (sensor.readRangeSingleMillimeters());
  long DISTANCE_FLT = (sensor2.readRangeSingleMillimeters());
  long DISTANCE_FRT = (sensor3.readRangeSingleMillimeters());

  //FWD OR SENSOR
  if (sensor.timeoutOccurred()) {
    Serial.println("_________________________________");
    Serial.print("Distance FWD (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else {
    Serial.println("_________________________________");
    Serial.print("Distance FWD   (mm): ");
    Serial.println((double)DISTANCE_FWD);
    Serial.println("_________________________________");
    Serial.println("");
  }

  //FLT OR SENSOR2
  if (sensor2.timeoutOccurred()) {
    Serial.println("_________________________________");
    Serial.print("Distance FLT (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else {
    Serial.println("_________________________________");
    Serial.print("Distance FLT   (mm): ");
    Serial.println((double)DISTANCE_FLT);
    Serial.println("_________________________________");
    Serial.println("");
  }

  //FRT OR SENSOR3
  if (sensor3.timeoutOccurred()) {
    Serial.println("_________________________________");
    Serial.print("Distance FRT (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else {
    Serial.println("_________________________________");
    Serial.print("Distance FRT   (mm): ");
    Serial.println((double)DISTANCE_FRT);
    Serial.println("_________________________________");
    Serial.println("");
  }

  Serial.println("__________________________________________________________________");
  Serial.println();
  Serial.println();

  delay(1000);//can change to a lower time like 100
}

//void comunication(){
//  if (Serial.available()>0){
//    if(teste == 'r'){
//      flag=5;
//      if (flag != 0){
//      counterClockwise(ciclosVolta);
//      Serial.println(teste);
//      flag = 0;}
//    }
//    else if(teste == 'e' && flag != 1){
//      Serial.println(teste);
//      flag = 1;
//    }
//    else if(teste =='a' && flag != 2){
//      Serial.println(teste);
//      flag = 2;
//    }
//    else if(teste =='h' && flag != 3){
//      Serial.println(teste);
//      flag = 3; 
//    }
//    else if(teste =='d' && flag != 4){
//      Serial.println(teste);
//      flag = 4; 
//    }
//  }
//  if(flag == 0){
//    teste = Serial.read();
//  }
//  else if(flag == 1){
//    teste = Serial.read();
//  }
//  else if(flag == 2){
//    teste = Serial.read();
//  }
//  else if(flag == 3){
//    teste = Serial.read();
//  }
//  else if(flag == 4){
//    teste = Serial.read();
//  }
//}

  
void setup() {
  Serial.begin(9600);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  pinMode(inf_e, OUTPUT);
  pinMode(inf_m, OUTPUT);
  pinMode(inf_d, OUTPUT);
  digitalWrite(inf_e, LOW);
  digitalWrite(inf_m, LOW);
  digitalWrite(inf_d, LOW);
  delay(500);
  Wire.begin();

  //SENSOR 1
  pinMode(inf_e, INPUT);
  sensor.init(true);
  sensor.setAddress((uint8_t)22);

  //SENSOR 2
  pinMode(inf_m, INPUT);
  sensor2.init(true);
  sensor2.setAddress((uint8_t)25);

  //SENSOR 3
  pinMode(inf_d, INPUT);
  sensor3.init(true);
  sensor3.setAddress((uint8_t)28);

  sensor.setTimeout(500);
  sensor2.setTimeout(500);
  sensor3.setTimeout(500);


  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(comunication);

  //Serial.println(distCiclos(1));
  //Serial.println(RPM(tempo, razaoPWM));
  //clockwise(6);
  //delay(1000);
  //counterClockwise(6);
}

void loop() {
  //counterClockwise(0);
  //passoCompleto(1);
  //infravermelho();
  calculo_RGB();
}
