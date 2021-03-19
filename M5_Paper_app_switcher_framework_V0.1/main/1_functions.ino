#include "configuration.h"
#include "credentials.h"

void FullCleanDisplay() // Clean display from possible artifacts only for Debug
{
  canvas.deleteCanvas();  
  canvas.createCanvas(540, 960); 
  canvas.pushCanvas(0,0,UPDATE_MODE_INIT); 
  delay(10);
}

void Turn_off()// tuns off the device
{
  canvas.deleteCanvas();
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  canvas.drawString("Turning Off...", 70, 400); 
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
  delay(5000);
  M5.EPD.Clear(true);
  delay(1000);
  gpio_hold_dis((gpio_num_t)2); // release the gpio pin to make a proper shutdown possible
  M5.shutdown(0);
 
  delay(250); // only gets used if on USB Power -> shutdown does not work on USB Power
  gpio_hold_dis((gpio_num_t)2); // release the gpio pin to make a proper shutdown possible
  esp_deep_sleep_start();// -> because main MOSFET turns also off the devices powers down even on usb power
}









  
