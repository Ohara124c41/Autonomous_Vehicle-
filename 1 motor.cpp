#include "DualVNH5019MotorShield.h"
 
DualVNH5019MotorShield md;
 
void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
}
 
void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}
 
void loop()
{
  for (int i = 0; i <= 400; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }
   
  for (int i = 400; i >= -400; i--)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }
   
  for (int i = -400; i <= 0; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }
}

void forward(int time, int speed){

  for(int i=0; i < time; i++){
    md.setM1Speed(speed);
    stopIfFault();
  }  
}

void stop(int time){

  for(int i=0; i < time; i++){
      md.setM1Brake(400);        // 400 is max brake as definied by the .cpp file
      stopIfFault();
  }
}

// this doesnt need to exist as a seperate fnc because setM1Speed() will handle negative speeds already
void reverse(int time, int speed){

  for(int i=0; i < time; i++){
    md.setM1Speed(speed);
    stopIfFault();
  }  
}