#include <M5EPD.h> 
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true
#include <esp_wifi.h>
#include <esp_bt.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#include "configuration.h"
#include "credentials.h"

M5EPD_Canvas canvas(&M5.EPD); // setup for the Display


// For the Clock
rtc_time_t RTCtime;
rtc_date_t RTCDate;
char timeStrbuff[64];

// for NTP to RTC time
time_t t;
struct tm *tm;


// to choose which mode to use
int Modus;
bool new_mode= false;
int a=0;

// for the Touchscreen
int point[2][2];


void setup() {
  M5.begin(true,false,true,true,true); //Touchscreen,SDreader, Serial,BatteryADC,I2C
  Serial.println("Angeschaltet");
  M5.EPD.SetRotation(90); // for the Screen to be upright
  //M5.EPD.Clear(true);  //if you want a Full refresh after every start
  
  wifiMulti.addAP(ssid, password);
  wifiMulti.addAP(ssid1, password1);
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);
  
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
      Serial.println("SPIFFS Mount Failed -> Formatting SPIFFS");
      SPIFFS.format();
      SPIFFS.begin();  
      return;
    }  
    
  File file3 = SPIFFS.open("/Modus.txt","r");
  Modus = file3.parseInt(); //get the value from Storage as an integer
  file3.close();

}

void loop() {
if( M5.BtnP.isPressed())// if button P (Power) was pressed to boot the device manualy, the modus choosing mode is activated
    {  
      M5.update();
      selector();
    }  
if (new_mode == true)
    {
    FullCleanDisplay();
    File file3 = SPIFFS.open("/Modus.txt","w");
      if (!file3) 
    {
      Serial.println("Error opening file Modus for writing");
      return;
    }
      if (file3.print(Modus))
    {
      Serial.println("- file written Modus");
    } else {
      Serial.println("- write failed");
    }
    file3.close(); 
}


if (Modus == 0)
  {
    Serial.println("switching to Selector");
    selector();   
  }
    else if(Modus == 1 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 1");
      mode1();
    }
    else if(Modus == 2 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 2");
      mode2();
    }
    else if(Modus == 3 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 3");
      mode3();
    }
    else if(Modus == 4 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 4");
      mode4();
    }
    else if(Modus == 5 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 5");
      mode5();
    }
    else if(Modus == 6 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 6");
      mode6();
    }
    else if(Modus == 7 && Modus <= Number_of_modes)
    {
      Serial.println("switching to Mode 7");
      mode7();
    }
        else
        {
          Serial.println("mode not known going to selector");
          selector();
        } 


}
