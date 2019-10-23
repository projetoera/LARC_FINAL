byte passo = 0, passo1=8, passo2=1;
bool Up=HIGH, first=true, clockWise=HIGH;
int microStep=256;
int PWM = 0 + microStep, PWMToPin=0, PWMPin=0;
int i = 1, lastPin = 5;
bool clockWiseLast = HIGH, trocou = false;

void setup() {
    //Serial.begin(9600);

    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    pinMode(3, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), function, CHANGE);
    delay(500);
}

bool andar = LOW;

void loop() {
  if(andar==HIGH){
  microPasso();
  }
  else{
    desliga();
    }
}//void looop

void desliga(){
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void function(){
                if(digitalRead(2)==HIGH){
                  andar=HIGH;
                  
                  clockWise=digitalRead(3);

                          if(clockWiseLast!=clockWise){
                            Up=!Up;
                            clockWiseLast=clockWise;
                            //Serial.println("trocou");
                            trocou=true;
                          }
                            
                }
                else{
                  andar=LOW;
                }
}//void function interrupção

void microPasso(){

          if(digitalRead(lastPin)==LOW)digitalWrite(lastPin,HIGH);
  
                switch(i){
                  case 1: PWMPin=6;break;
                  case 2: PWMPin=5;break;
                  case 3: PWMPin=9;break;
                  case 4: PWMPin=6;break;
                  case 5: PWMPin=10;break;
                  case 6: PWMPin=9;break;
                  case 7: PWMPin=5;break;
                  case 8: PWMPin=10;break;
                }

         for(int j=0; j<(256/microStep); j++){
          
                if(Up==HIGH)PWM = (j+1)*microStep;
                if(Up==LOW)PWM = 256-((j+1)*microStep);
                
                if(trocou==true){
                  trocou=false;
                  PWM=256;
                }
                  
                PWMToPin=PWM;
                if(PWMToPin==256)PWMToPin=255;

                analogWrite(PWMPin, PWMToPin);

//                Serial.print(Up);
//                Serial.print(" : ");
//                Serial.print(lastPin);
//                Serial.print(" : ");
//                Serial.print(PWMToPin);
//                Serial.print(" : ");
//                Serial.print(PWMPin);
//                Serial.print(" : ");
//                Serial.println(i);
                delayMicroseconds (300*microStep);
          
                if(PWM>=256 && Up==HIGH){
                  lastPin=PWMPin;
                  Up=LOW;
                  break;
                } 
                if(PWM<=0 && Up==LOW){
                  Up=HIGH;
                  break;
                }
                
                }

    if(clockWise==HIGH){
     i++;
    }
    else{
      i--;
    }
  if(i==0)i=8;
  if(i==9)i=1;
  }//microPasso
