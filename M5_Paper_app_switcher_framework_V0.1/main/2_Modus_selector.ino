

void selector()
{
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);// to have the same orientation as the display-> so the positions on the display and on the touchscreen match
  //M5.EPD.Clear(true);
  canvas.deleteCanvas();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  canvas.drawString("Mode Selector", 70, 400);
  canvas.drawString("Touch to Start", 60, 440);
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
  a=0;

if(M5.TP.avaliable())// check if touch driver is reachable
{
  int c=0;
  M5.TP.flush();// reset values
  while (M5.TP.getFingerNum() == 0)// while no fingers are detected
  {
    delay(50);  
    M5.TP.update();
    //Serial.println("waiting...");
    c++;
    if(c>=1200)// to go to sleep if nothing has happened after 60sec-> energysaving 
    {
      c=0;
      Turn_off();
    }
    
  }
  if (M5.TP.getFingerNum() >0 )// if a finger has been detected
  {
    canvas.deleteCanvas();
    canvas.createCanvas(540, 960);
    //M5.EPD.Clear(true);
    Serial.println("touched");
    while ( a < Number_of_modes)
    {
      int y_sq = 15 +(118*a);
      canvas.drawRect(20,y_sq,500,100,15);
      canvas.setTextSize(4);
      if (a==0){canvas.drawString(Mode_0,50, (y_sq+30));}
      if (a==1){canvas.drawString(Mode_1,50, (y_sq+30));}
      if (a==2){canvas.drawString(Mode_2,50, (y_sq+30));}
      if (a==3){canvas.drawString(Mode_3,50, (y_sq+30));}
      if (a==4){canvas.drawString(Mode_4,50, (y_sq+30));}
      if (a==5){canvas.drawString(Mode_5,50, (y_sq+30));}
      if (a==6){canvas.drawString(Mode_6,50, (y_sq+30));}
      a++;
    } 
      canvas.drawRect(20,841,500,100,15);
      canvas.setTextSize(5);
      canvas.drawString("Shutdown",150,(841+30));
      a=0;
    
      canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
      M5.TP.flush();
  }
  c=0;
  while (M5.TP.getFingerNum() ==0 )// waiting for input
  {
    delay(50);
    M5.TP.update();
    c++;
     if(c>=1200)
    {
      c=0;
      M5.TP.flush();
      Turn_off();
    }
  }
  if (M5.TP.getFingerNum() >0 )// when input is received
  {
    new_mode = true;// so other aplications know it is th first time they have been swichted to
    int i;
    int b = 15;
    tp_finger_t FingerItem= M5.TP.readFinger(i);
    point [i][0] = FingerItem.x;
    point [i][1] = FingerItem.y;
    Serial.print("X:");  
    Serial.println(FingerItem.x);
    Serial.print("Y:");
    Serial.println(FingerItem.y);
    a=1;
    while (a <= Number_of_modes)
    {
      if ( FingerItem.y <= (15 +(118*a))&& FingerItem.y >=b) // check every available sqaure if it has been touched-> dont care about X co-ordinate
      {
        if (a==1){Modus=1;Serial.println(Modus); return;}
        if (a==2){Modus=2;Serial.println(Modus); return;}
        if (a==3){Modus=3;Serial.println(Modus); return;}
        if (a==4){Modus=4;Serial.println(Modus); return;}
        if (a==5){Modus=5;Serial.println(Modus); return;}
        if (a==6){Modus=6;Serial.println(Modus); return;}
        if (a==7){Modus=7;Serial.println(Modus); return;}
      }
     b=(15+(118*a));
     a++; 
    }
  if (FingerItem.y >= (15 +(118*7)))
  {
    M5.TP.flush();
    Turn_off();
  }   
 Modus=0;
 M5.TP.flush();
}
}
}
