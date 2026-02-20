#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
const int buttonPinUp = 2;
const int buttonPinDown = 3;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String songsArray[] = {
    "Heart shaped box",
    "Dumb",
    "Dumb",
    "Dumb",
    "Dumb",
    "Dumb",
    "Dumb",
    "Dumb",
    "DumbXD",
    "Smells like teen spirit"
};
int songCount = sizeof(songsArray) / sizeof(songsArray[0]);

int playing = 0;
int selected = 7;

// scroll index only for currently playing song
int scrollIndexPlaying = 0;
unsigned long previousMillis = 0;
const long interval = 100;

// helper function for scrolling
String scrollingText(String text, int index, int width){
    String textRes = text + " " + text;  // add space for smooth loop
//    if(index + width > textRes.length())
//        return textRes.substring(index);
    return textRes.substring(index, index + width);
}

// display the menu (no scrolling)
void menuArray(String menuItems[], int itemCount, int selected){
    for(int i = selected, line=1; i < itemCount; i++, line++){
        display.setCursor(0, line*8);
        if(i == selected)
            display.print("> "+String(i+1)+". ");
        else
            display.print("  "+String(i+1)+". ");
        
        
        if(menuItems[i].length()>14){
          display.println(menuItems[i].substring(0,14)+"?");
        }else{
          display.println(menuItems[i]);
        }
    }
}

void setup() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        Serial.println("OLED not found");
        for(;;);
    }
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    pinMode(buttonPinUp, INPUT_PULLUP);
    pinMode(buttonPinDown, INPUT_PULLUP);
    
    Serial.begin(9600);
}

bool buttonPressedUp=false;
bool buttonPressedDown=false;
void loop(){
    
    if (digitalRead(buttonPinUp) == LOW)buttonPressedUp=true;
    if (digitalRead(buttonPinDown) == LOW)buttonPressedDown=true;
    if (digitalRead(buttonPinUp) == HIGH && buttonPressedUp==true){buttonPressedUp=false;selected--;}
    if (digitalRead(buttonPinDown) == HIGH && buttonPressedDown==true){buttonPressedDown=false;selected++;}
    if(selected>songCount-1)selected=0;
    if(selected<0)selected=songCount-1;
    
    display.setCursor(0,0);

    // currently playing song at top
    String songName = songsArray[playing];
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      display.clearDisplay();
      
      previousMillis = currentMillis;
      if(songName.length() > 15){  // scroll only if too long
        display.print("--P: ");
        display.println(scrollingText(songName, scrollIndexPlaying, 15));

        // advance the scroll index
        scrollIndexPlaying++;
        if(scrollIndexPlaying >= songName.length() + 1)scrollIndexPlaying = 0;
      } else {
        display.print("--P: "+songName);
      } 
    }
    menuArray(songsArray, songCount, selected);
    display.display();
    

    // menu below
    

    
}
