#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    for(;;);
  }
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  Serial.begin(9600);
}

String scrollingText(int index){
  String text="moj dlugi text";
  
  String textPart="";
  for(int i=index;i<index+8;i++){
    textPart+=text[i];
  }
  display.println(textPart);
  
}
int index=0;
void loop() {
  scrollingText(index);
  index++;
  delay(500);
}
