#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
const int buttonPinUp = 2;
const int buttonPinDown = 3;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Memory-safe song list
const char* songsArray[] = {
    "Intro",
    "Hot Dog",
    "My Generation",
    "Full Nelson",
    "My Way",
    "Rollin'(Air Raid Vehicle)",
    "Livin'It Up",
    "The One",
    "Getcha Groove On - Dirt Road Mix",
    "Take A Look Around",
    "It'll Be OK",
    "Boiler",
    "Hold On",
    "Rolin'(Urban Assault Vehicle)",
    "Outro"
};

const int songCount = sizeof(songsArray) / sizeof(songsArray[0]);

int playing = 0;
int selected = 7;

// Scrolling for currently playing song
int scrollIndexPlaying = 0;
unsigned long previousMillis = 0;
const long interval = 200;

// Button debounce
bool lastUpState = HIGH;
bool lastDownState = HIGH;
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 150;

// Helper: print scrolling text without Strings
void printScrolling(const char* text, int index, int width) {
    int len = strlen(text);
    for (int i = 0; i < width; i++) {
        int charIndex = (index + i) % (len + 1);
        if (charIndex == len)
            display.print(" ");
        else
            display.print(text[charIndex]);
    }
}

void menuArray(const char* menuItems[], int itemCount, int selected) {
    // Display up to 6 items below the currently playing song
    int linesToShow = 6;
    int start = selected;
    for (int line = 1; line <= linesToShow && (start + line - 1) < itemCount; line++) {
        int i = start + line - 1;
        display.setCursor(0, line * 8);
        if (i == selected)
            display.print("> |");
        else
            display.print("  |");

        const char* name = menuItems[i];
        int nameLen = strlen(name);
        if (nameLen > 17) {
            for (int j = 0; j < 17; j++) display.print(name[j]);
            display.print("?");
        } else {
            display.print(name);
        }
    }
}

void setup() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED not found");
        for (;;);
    }
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    pinMode(buttonPinUp, INPUT_PULLUP);
    pinMode(buttonPinDown, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop() {
    // --- Button handling ---
    bool upState = digitalRead(buttonPinUp);
    bool downState = digitalRead(buttonPinDown);
    unsigned long now = millis();

    if (upState == LOW && lastUpState == HIGH && now - lastButtonTime > debounceDelay) {
        selected--;
        if (selected < 0) selected = songCount - 1;
        lastButtonTime = now;
    }

    if (downState == LOW && lastDownState == HIGH && now - lastButtonTime > debounceDelay) {
        selected++;
        if (selected >= songCount) selected = 0;
        lastButtonTime = now;
    }

    lastUpState = upState;
    lastDownState = downState;

    // --- Display ---
    display.clearDisplay();
    display.setCursor(0, 0);

    const char* songName = songsArray[playing];

    // Scroll the currently playing song
    if (strlen(songName) > 15) {
        if (now - previousMillis >= interval) {
            previousMillis = now;
            scrollIndexPlaying++;
            if (scrollIndexPlaying > strlen(songName)) scrollIndexPlaying = 0;
        }
        display.print("PLAY: ");
        printScrolling(songName, scrollIndexPlaying, 15);
    } else {
        display.print("PLAY: ");
        display.print(songName);
    }

    // Display menu below
    menuArray(songsArray, songCount, selected);

    display.display();
    delay(40);
}
