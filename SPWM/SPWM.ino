#include <LiquidCrystal.h>
#include <SPI.h>

LiquidCrystal lcd( 8,  9, 4, 5, 6, 7);

int menu = 1;
int F = 50;
int Res = 5;

void setup() {
  lcd.begin(16, 2);
  lcd.print("LCD Ready!");
  Serial.begin(9600);
  Serial.println("Serial Ready");
  pinMode(3, OUTPUT);
}

void loop() {
  float t=1/(2*(float)F);
  float step = t/(float)Res;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1/2 cycl: ");
  lcd.setCursor(0, 1);
  lcd.print(String(t*1000) + "ms");
  lcd.setCursor(9, 1);
  lcd.print(String(step*1000) + "ms");
  double wMid[Res];
  double delayHigh[Res];
  double delayLow[Res];
  double x=step/2;
  for(int i=0; i<Res; i++){
    wMid[i] = x;
    delayHigh[i] = step * sin(2*3.1416*F*x);
    delayLow[i] = (step/2) - (delayHigh[i]/2);
    Serial.println("Delay-Low: " + String(delayLow[i]*1000000) + "uS DelayHigh: " + String(delayHigh[i]*1000000) + "uS");
    x += step;
  }

  /*
  for(int i=0; i<Res; i++){
      //arr[i] = x;
      digitalWrite(3, HIGH);
      float dl=step * sin(2*3.1416*F*x);
      float dlm = dl*1000000;
      delayMicroseconds(dlm);
      digitalWrite(3, LOW);
      x = x+step;
      Serial.println(String(i) + " -- " + String(dlm, 4));
      //Serial.println(String(i) + " -- " + String(x*1000, 6) + " -- " + String(dlm*1000000, 6));
      //Serial.println(String(arr[i]*10000, 4) + " --- " + String(dl*1000, 4));
    }
  //}
  */
  while(checkButton()==' '){
    for(int i =0; i<Res; i++){
      delayMicroseconds(delayLow[i]*1000000);
      digitalWrite(3, HIGH);
      delayMicroseconds(delayHigh[i]*1000000);
      digitalWrite(3, LOW);
      delayMicroseconds(delayLow[i]*1000000);


      //delayMicroseconds(5000);


      //delayMicroseconds(delayLow[i]*1000000);
      //digitalWrite(3, LOW);
      //delayMicroseconds(delayHigh[i]*1000000);
      //digitalWrite(3, HIGH);
      //delayMicroseconds(delayLow[i]*1000000);

      //delayMicroseconds(5000);
    }
  }
  //while(checkButton()==' ');
}


char checkButton() {
  int x = analogRead (A0);
  char buttonPressed;
  if (x < 25) {
    buttonPressed = 'R';
  } else if (x>55 && x < 80) {
    buttonPressed = 'U';
  } else if (x>170 && x < 200){
    buttonPressed = 'D';
  } else if (x>330 && x < 350){
    buttonPressed = 'L';
  } else if (x>570 && x < 590){
    buttonPressed = 'S';
  } else {
    buttonPressed = ' ';
  }
  return buttonPressed;
}