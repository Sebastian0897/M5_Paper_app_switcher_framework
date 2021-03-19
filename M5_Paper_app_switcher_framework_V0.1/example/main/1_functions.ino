#include "configuration.h"
#include "credentials.h"

void FullCleanDisplay() // Clean display from possible artifacts only for Debug
{
  canvas.deleteCanvas();  
  canvas.createCanvas(540, 960); 
  canvas.pushCanvas(0,0,UPDATE_MODE_INIT); 
  delay(10);
}


void MinRefresh () // Updates the Clock when run
{  
  canvas.deleteCanvas();  
  canvas.createCanvas(540, 45); // Size requiered for the clock
  canvas.setTextSize(5); 
  canvas.pushCanvas(0,35,UPDATE_MODE_GC16);   //for a clearer screen refresh
  M5.RTC.begin();  // required for the Clock
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  sprintf(timeStrbuff,"%02d/%02d/%d %02d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min);
  canvas.drawString(timeStrbuff, 35, 5); // position of the time and date
  canvas.pushCanvas(0,35,UPDATE_MODE_GC16); //actually show the new time
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

void set_time()
{       
        ConnectWifi();
        if(WiFi.status() == WL_CONNECTED)
        {
        Serial.println("Time is beeing set from NTP");
        M5.RTC.begin();
        do 
        {
          configTime(UTC_OFFSET*60,0, "pool.ntp.org", "time.nist.gov");
          delay(2000);
          t = time(NULL);
          tm = localtime(&t);
          if (tm->tm_year+1900 >= 121)
          {
            RTCtime.hour = tm->tm_hour;
            RTCtime.min = tm->tm_min;
            RTCtime.sec = tm->tm_sec;
            M5.RTC.setTime(&RTCtime);

            RTCDate.year = tm->tm_year + 1900;
            RTCDate.mon = tm->tm_mon + 1;
            RTCDate.day = tm->tm_mday;
            M5.RTC.setDate(&RTCDate);
            Serial.print("tm_year:");
            Serial.println(tm->tm_year+1900);
          }
        }while (tm->tm_year+1900 < 121);
    }
}

void ConnectWifi() // Connects to wifi.
{  
  canvas.deleteCanvas();  
  canvas.createCanvas(290, 30);
  canvas.setTextSize(3); 
  canvas.drawString("Connecting...", 0, 0);  
  canvas.pushCanvas(10,10,UPDATE_MODE_GL16); 
  

    wifiMulti.run();
  if (WiFi.status()!= WL_CONNECTED)// if no connection was possible
  {  
    canvas.deleteCanvas();  
    canvas.createCanvas(290, 30);
    canvas.setTextSize(3); 
    canvas.drawString("Not Connected", 0, 0);  
    canvas.pushCanvas(10,10,UPDATE_MODE_DU);               
  }
  if(WiFi.status() == WL_CONNECTED)// show that it connected to a WIFI network
  {
    canvas.deleteCanvas();  
    canvas.createCanvas(290, 30); 
    canvas.setTextSize(3); 
    canvas.drawString("Connected", 0, 0);  
    canvas.pushCanvas(10,10,UPDATE_MODE_DU); 
  }
}


void Shutdown() // turns the device off and sets timer to wake when a update of the time is required
{
  M5.RTC.getTime(&RTCtime);
  int timer; 
  timer = 57 - RTCtime.sec;
  esp_sleep_enable_timer_wakeup(400 * uS_TO_MS_FACTOR);// delay for the Display to finish updating
  gpio_hold_en((gpio_num_t) 2); // to prevent the main MOSfet from turning everything off
  gpio_deep_sleep_hold_en();
  esp_light_sleep_start();
  gpio_hold_dis((gpio_num_t)2); 
  M5.shutdown(timer);// turns of the device, RTC starts the Device again in X-secs. should adjust sleep lenght automatically as long as the task does not take over 1min to complete.
  
  delay(250); // only gets used if on USB Power -> shutdown does not work on USB Power
  esp_sleep_enable_timer_wakeup(timer * uS_TO_S_FACTOR); // needed to ensure the Display has finished all the updates
  gpio_hold_en((gpio_num_t) 2); // to prevent the main MOSfet from turning everything off
  gpio_deep_sleep_hold_en();
  esp_deep_sleep_start();
}







  
