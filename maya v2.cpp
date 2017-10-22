#include "DualVNH5019MotorShield.h"
 
DualVNH5019MotorShield md;

//bool GO=true;
 
void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}
 
void loop()
{

///*                          automatic motor control test                          */

  // code to test operability of defined functions
//  if(GO==true){
    //~ forward(4000, 200);  // proceeds forward for 4 seconds at 1/4 full speed
    //~ delay(2);
    //~ left(500, 400);     // left turn for 1 second at 1/4 full speed
    //~ delay(2);
    //~ right(100, 400);    // right turn for 1 second at 1/4 full speed
    //~ delay(2);
    //~ stop(200);          // stop for 2 seconds
    //~ forward(400, 400);  // forward again for 4 seconds at slightly increased speed
    //~ delay(1000);
    //~ stop(10000);
//    GO = false;
//  }


///*                         independant motor control test                         */

  for(int i = 0; i<400; i++){
  
    leftDirectControl(i);
    rightDirectControl(i);
    delay(2);
  
  }

  unsigned long start = millis();

  while(millis() - start <= 5000){
  
    leftDirectControl(400);
    rightDirectControl(400);
  
  }

  start = millis();

  while(millis() - start <= 5000){
  
    leftDirectControl(400);
    rightDirectControl(0);
  
  }

}

void forward(int time, int speed){

  unsigned long forwardStart = millis();

  while(millis() - forwardStart <= time){
    md.setM1Speed(speed);
    md.setM2Speed(-speed);
  }

  //~ for(int i=0; i < time; i++){
    //~ md.setM1Speed(speed);
    //~ md.setM2Speed(-speed);
    //~ /* The polarity is reversed on one half of the wheels.
       //~ This may not function as intended and may need to be fixed at the hardware level
    //~ */
    //~ delay(time);
  //~ }  
}

void stop(int time){

  unsigned long stop = millis();

  while(millis() - stop <= time){
    md.setM1Brake(400);
    md.setM2Brake(400);
  }

  //~ for(int i=0; i < time; i++){
      //~ md.setM1Brake(400);        // 400 is max brake as definied by the .cpp file
      //~ md.setM2Brake(400);
  //~ }
}

// requires testing to confirm this will turn left
// will require modifying to add opposite wheel rotation for turns
void left(int time, int speed){


  unsigned long leftStart = millis();
  
  while(millis() - leftStart <= time){
    md.setM2Speed(0);  
    md.setM1Speed(speed);
    
  }

  //~ for(int i=0; i<time; i++){  
    //~ md.setM2Speed(0);
    //~ md.setM1Speed(speed);  
    //~ delay(2);
  //~ }
}

// requirest test to confirm this will turn right
void right(int time, int speed){

  for(int i=0; i<time; i++){
    md.setM1Speed(0);
    md.setM2Speed(speed);
  }
}

// this doesnt need to exist as a seperate fnc because setM1Speed() will handle negative speeds already
void reverse(int time, int speed){

  for(int i=0; i < time; i++)
    md.setM1Speed(-speed);
    md.setM2Speed(speed);
}

void leftDirectControl(int speed){

  md.setM2Speed(-speed);

}

void rightDirectControl(int speed){

  md.setM1Speed(speed);
}




/*   original code for single motor

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
  
*/