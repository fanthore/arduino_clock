#include "NTPClient.h"
#include "ESP8266WiFi.h" 
#include "WiFiUdp.h" 
#include "SPI.h" 
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "";
const char *password = "";

WiFiUDP ntpUDP;

// Local time ofset 7200
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

String arr_days[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
String date_time; 

void setup()

{

Serial.begin(115200);
WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED )

{

delay ( 500 );
Serial.print ( "." );

}

if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))

{

Serial.println(F("SSD1306 allocation failed"));
for(;;); // Don't proceed, loop forever

}

display.clearDisplay();
display.setTextSize(2); // Draw 2X-scale text
display.setTextColor(WHITE);
display.setCursor(5, 2);
display.println("Connected");
display.println(" to");
display.println(" NTP");
display.display();
delay(3000);

timeClient.begin();

}

void loop()

{

timeClient.update();
display.clearDisplay();
Serial.println(timeClient.getFormattedTime());
display.setTextSize(2); // Change text size
display.setTextColor(WHITE);
display.setCursor(0, 0);

int hh = timeClient.getHours();
int mm = timeClient.getMinutes();
int ss = timeClient.getSeconds();
int day = timeClient.getDay();
String present_day = ("'"+arr_days[day]+"'");
String clean_day = present_day.substring(1,4);
display.println(clean_day);
date_time = timeClient.getFormattedTime();

int index_date = date_time.indexOf("T");

String date = date_time.substring(0, index_date);

Serial.println(date);
display.println(date);
display.display();

}
