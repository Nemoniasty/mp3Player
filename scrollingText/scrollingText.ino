#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    for(;;);
  }
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  
}

String scrollingText(String text, int index,int width){
  String textRes=text+" "+text;
  
  String textPart = textRes.substring(index, index + width);
  return textPart;
}

int index=0;
String text="miki lubi rowery ale nie kolarki";

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(scrollingText(text,index,15));
  display.display();
  index++;
  if(index>=text.length()+1)index=0;
  delay(200);
}
