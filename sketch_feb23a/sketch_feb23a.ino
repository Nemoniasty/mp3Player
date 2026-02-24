#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String songsArray[]={"Heart shaped box","Dumb","Dumb","Dumb","Dumb","Dumb","Dumb","Dumb","DumbXD","Smells like teen spirit"};
int songCount = sizeof(songsArray) / sizeof(songsArray[0]);

void menuArray(String menuItems[], int itemCount, int selected){
  for(int i = selected, line=1; i < itemCount; i++,line++){
    display.setCursor(0, line * 8);

    if(i == selected)
      display.print("> "+(String)(i+1)+". ");
    else
      display.print("  "+(String)(i+1)+". ");

    display.println(menuItems[i]);
  }
}

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    for(;;);
  }
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  Serial.begin(9600);
}
int playing=0;
int selected=5;
int lastSelected=-1;

void loop() {

  if(selected == lastSelected) return;

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("--Playing: "+songsArray[playing]+"--");
  menuArray(songsArray, songCount, selected);
  display.display();

  lastSelected = selected;
}
