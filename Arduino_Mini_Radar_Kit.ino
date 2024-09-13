/*mini radar kit*/
#include <Servo.h> 
#include <SPI.h>
#include "Ucglib.h"           
#define  trigPin   6          //Ultrasonic Module Trig->D6
#define  echoPin   5          //Ultrasonic Module Echo->D5
#define  ServoPin  3          //Servo Signal->D3
int Ymax = 128;               //vertical pixels of the screen
int Xmax = 160;               //horizontal pixels of the screen
int Xcent = Xmax / 2;         //Horizontal screen center position
int base = 118;               //baseline position
int scanline = 105;           //Radar scan line length
Servo baseServo; 
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);


void setup(void)
{
      ucg.begin(UCG_FONT_MODE_SOLID); //initialization screen
      ucg.setRotate90();              //Set to horizontal screen If the screen display direction is reversed, you can modify the function setRotate90 or setRotate270
      
      pinMode(trigPin, OUTPUT);       //Set the trig Pin port mode
      pinMode(echoPin, INPUT);        //Set echo Pin port mode
      Serial.begin(115200);             //Set the serial port transmission rate
      baseServo.attach(ServoPin);     //Initialize servos
    
      //screen startup interface
      ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
      ucg.setColor(0, 0, 100, 0);
      ucg.setColor(1, 0, 100, 0);
      ucg.setColor(2, 20, 20,20);
      ucg.setColor(3, 20, 20, 20);
      ucg.drawGradientBox(0, 0, 160, 128);
      ucg.setPrintDir(0);
      ucg.setColor(0, 5, 0);
      ucg.setPrintPos(27,42);
      ucg.setFont(ucg_font_logisoso18_tf);  
      ucg.print("Mini Radar");
      ucg.setColor(0, 255, 0);
      ucg.setPrintPos(25,40);
      ucg.print("Mini Radar");
      ucg.setFont(ucg_font_helvB08_tf);
      ucg.setColor(0, 255, 0);
      ucg.setPrintPos(40,100);
      ucg.print("Testing...");
      baseServo.write(90);
      ucg.setColor(0, 255, 0);
    
      //Test the operation of the base, pay attention to the position and rotation posture of the base, and whether there is any jamming (or wire winding).
      for(int x=0;x<180;x+=5)
          { baseServo.write(x);
            delay(50);
           }
      ucg.print("OK!");
      delay(500);
      ucg.setColor(0, 0, 0, 0);
      ucg.setColor(1, 0, 0, 0);
      ucg.setColor(2, 0, 0,0);
      ucg.setColor(3, 0, 0, 0);
    
      //clear screen
      //ucg.clearScreen();
      cls();
      
      ucg.setFont(ucg_font_orgv01_hr);
      ucg.setFontMode(UCG_FONT_MODE_SOLID);
}


void cls()
{
  //clear screen
  ucg.setColor(0, 0, 0, 0);
  
  for(int s=0;s<128;s+=8)
  for(int t=0;t<160;t+=16)
  {
    ucg.drawBox(t,s,16,8);
   // delay(1);
  }
    

}


int calculateDistance()
{ 
      long duration;
      //power off trigPin and wait 2 microseconds
      digitalWrite(trigPin, LOW); 
      delayMicroseconds(2);
      //TrigPin power on delay 10 microseconds and then power off
      digitalWrite(trigPin, HIGH); 
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      //Reading the echoPin returns the travel time of the sound wave (in microseconds)
      duration = pulseIn(echoPin, HIGH);
      //Convert echo time to distance value
      return duration*0.034/2;
}

void fix_font() 
{
      ucg.setColor(0, 180, 0);
      ucg.setPrintPos(70,128-120+7);
      ucg.print("100cm");
      ucg.setPrintPos(70,128-85-11);
      ucg.print("75cm");
      ucg.setPrintPos(70,128-60-8);
      ucg.print("50cm");
      ucg.setPrintPos(70,128-35-4);
      ucg.print("25cm");
}

void fix()
{

      ucg.setColor(0, 40, 0);
      //Draw a background image
      ucg.drawDisc(Xcent, base+1, 3, UCG_DRAW_ALL); 
      ucg.drawCircle(Xcent, base+1, 115, UCG_DRAW_UPPER_LEFT);
      ucg.drawCircle(Xcent, base+1, 115, UCG_DRAW_UPPER_RIGHT);
      ucg.drawCircle(Xcent, base+1, 86, UCG_DRAW_UPPER_LEFT);
      ucg.drawCircle(Xcent, base+1, 86, UCG_DRAW_UPPER_RIGHT);
      ucg.drawCircle(Xcent, base+1, 58, UCG_DRAW_UPPER_LEFT);
      ucg.drawCircle(Xcent, base+1, 58, UCG_DRAW_UPPER_RIGHT);
      ucg.drawCircle(Xcent, base+1, 29, UCG_DRAW_UPPER_LEFT);
      ucg.drawCircle(Xcent, base+1, 29, UCG_DRAW_UPPER_RIGHT);
      ucg.drawLine(0, base+1, Xmax,base+1);
     
      ucg.setColor(0, 120, 0);
      //draw scale
       for(int i= 40;i < 140; i+=2)
       {

        if (i % 10 == 0) 
          ucg.drawLine(105*cos(radians(i))+Xcent,base - 105*sin(radians(i)) , 113*cos(radians(i))+Xcent,base - 113*sin(radians(i)));
        else
        
         ucg.drawLine(110*cos(radians(i))+Xcent,base - 110*sin(radians(i)) , 113*cos(radians(i))+Xcent,base - 113*sin(radians(i)));
       }
          
       //draw some decorative patterns
       ucg.setColor(0,200,0);
       ucg.drawLine(0,0,0,18);
       for(int i= 0;i < 5; i++)
       {
          ucg.setColor(random(255),random(255),random(255));
          ucg.drawBox(2,i*4,random(14)+2,3);
       }

       ucg.setColor(0,0,180);
       ucg.drawFrame(146,0,14,14);
       ucg.setColor(0,0,60);
       ucg.drawHLine(148,0,10);
       ucg.drawVLine(146,2,10);
       ucg.drawHLine(148,13,10);
       ucg.drawVLine(159,2,10);
        
       ucg.setColor(random(255),random(255),random(255));
       //ucg.setColor(0,220,0);
       ucg.drawBox(148,2,4,4);
       ucg.setColor(0,220,0);
       ucg.drawBox(148,8,4,4);
       ucg.setColor(random(255),random(255),random(255));
       //ucg.setColor(100,0,0);
       ucg.drawBox(154,8,4,4);
       ucg.setColor(random(255),random(255),random(255));
       //ucg.setColor(0,0,150);
       ucg.drawBox(154,2,4,4);

       ucg.setColor(0,0,90);
       ucg.drawTetragon(62,123,58,127,98,127,102,123);
       ucg.setColor(0,0,160);
       ucg.drawTetragon(67,123,63,127,93,127,97,123);
       ucg.setColor(0,255,0);
       ucg.drawTetragon(72,123,68,127,88,127,92,123);
}



void loop(void)
{
  
  int distance;
  
  fix(); 
  fix_font();  //Repaint screen background elements

  for (int x=180; x > 4; x-=2){       //The base servo rotates from 180 to 0 degrees
     
      baseServo.write(x);             //Adjust the steering gear angle
      
      //Draw Radar Scanlines
      int f = x - 4; 
      ucg.setColor(0, 255, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      f+=2;
      ucg.setColor(0, 128, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      f+=2;
      ucg.setColor(0, 0, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      ucg.setColor(0,200, 0);
      //Get the distance value
      distance = calculateDistance();
     
      //Draw a point at the corresponding position according to the measured distance
      if (distance < 100)
      {
        ucg.setColor(255,0,0);
        ucg.drawDisc(1.15*distance*cos(radians(x))+Xcent,-(1.15*distance*sin(radians(x)))+base, 1, UCG_DRAW_ALL);
      }
      else
      { //If it is more than 1 meter, it is indicated by a yellow painting on the edge area
        ucg.setColor(255,255,0);
        ucg.drawDisc(116*cos(radians(x))+Xcent,-116*sin(radians(x))+base, 1, UCG_DRAW_ALL);
      }
    
           
      //Debug code, output angle and range value
      Serial.print("Degree:  ");
      Serial.print(x); 
      Serial.print("    ,Distance:   ");
      Serial.println(distance); 
     

      if (x > 70 and x < 110)  fix_font();  //When the scan line and the number coincide, redraw the number
 
      ucg.setColor(0,0,155,  0);
      ucg.setPrintPos(0,126);
      ucg.print("DEG: "); 
      ucg.setPrintPos(24,126);
      ucg.print(x);
      ucg.print("  ");
      ucg.setPrintPos(125,126);
      ucg.print("  ");
      ucg.print(distance);
      ucg.print("cm  "); 
      
  }
  delay(50);
  cls();
  fix(); 
  fix_font();          //Repaint screen background elements
  
  for (int  x=1; x < 176; x+=2){     
      baseServo.write(x);             //Adjust the steering gear angle
      
      //Draw Radar Scanlines
      int f = x + 4;
      ucg.setColor(0, 255, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      f-=2;
      ucg.setColor(0, 128, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      f-=2;
      ucg.setColor(0, 0, 0);
      ucg.drawLine(Xcent, base, scanline*cos(radians(f))+Xcent,base - scanline*sin(radians(f)));
      ucg.setColor(0, 200, 0);
      //测距
      distance = calculateDistance();

      //Draw a point at the corresponding position according to the measured distance
      if (distance < 100)
      {
        ucg.setColor(255,0,0);
        ucg.drawDisc(1.15*distance*cos(radians(x))+Xcent,-(1.15*distance*sin(radians(x)))+base, 1, UCG_DRAW_ALL);
      }
      else
      { //If it is more than 1 meter, it is indicated by a yellow painting on the edge area
        ucg.setColor(255,255,0);
        ucg.drawDisc(116*cos(radians(x))+Xcent,-116*sin(radians(x))+base, 1, UCG_DRAW_ALL);
      }
           
      //Debug code, output angle and range value
      Serial.print("Degree:  ");
      Serial.print(x); 
      Serial.print("    ,Distance:   ");
      Serial.println(distance); 
     
      if (x > 70 and x < 110)  fix_font();  //When the scan line and the number coincide, redraw the number
      
      ucg.setColor(0,0,155,  0);
      ucg.setPrintPos(0,126);
      ucg.print("DEG: "); 
      ucg.setPrintPos(24,126);
      ucg.print(x);
      ucg.print("   ");
      ucg.setPrintPos(125,126);
      ucg.print("   ");
      ucg.print(distance);
      ucg.print("cm   "); 
  
  }
 delay(50);
 cls();

}
