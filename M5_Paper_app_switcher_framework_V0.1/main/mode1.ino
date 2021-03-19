void mode1()
{ // here you put your mode1 program
  canvas.deleteCanvas();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  canvas.drawString("mode 1!", 70, 400); 
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
  
  delay(10000);
  Turn_off();

}
