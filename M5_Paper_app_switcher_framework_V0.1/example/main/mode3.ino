void mode3()
{
    canvas.deleteCanvas();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  canvas.drawString("mode 3!", 70, 400); 
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
  delay(10000);
  Turn_off();
  
}
