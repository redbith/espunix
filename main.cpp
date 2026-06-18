#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <SD.h>

// PIN DEFINITIONS (SPI2 for Display, SPI3 for SD)
#define TFT_CS 4
#define TFT_RST 5
#define TFT_DC 6
#define TFT_MOSI 7
#define TFT_SCLK 15

#define SD_CS 16
#define SD_MOSI 13
#define SD_SCLK 12
#define SD_MISO 17

SPIClass spiSD(FSPI);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

String currentDir = "/";
#define MAX_LOG 12
String logs[MAX_LOG];

void logToScreen(String msg) {
    for (int i = 0; i < MAX_LOG - 1; i++) logs[i] = logs[i + 1];
    logs[MAX_LOG - 1] = msg;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_GREEN);
    for (int i = 0; i < MAX_LOG; i++) tft.println(logs[i]);
}

void setup() {
    Serial.begin(115200);
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);
    
    tft.setCursor(0, 40);
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Starting espunix OS...");
    delay(800); 
    tft.fillScreen(ST7735_BLACK);

    spiSD.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, spiSD)) logToScreen("SD Error!");
    else logToScreen("espunix v1.0 Ready");
    
    Serial.println("\n--- espunix Shell ---");
    Serial.print(currentDir + "$ ");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        if (input.length() == 0) return;
        
        logToScreen("> " + input);
        processCommand(input);
        Serial.print(currentDir + "$ ");
    }
}

void processCommand(String cmd) {
    if (cmd == "clear") {
        for(int i=0; i<MAX_LOG; i++) logs[i] = "";
        tft.fillScreen(ST7735_BLACK);
        return;
    }
    
    if (cmd == "fastfetch") {
        logToScreen("--- espunix ---");
        logToScreen("Kernel: v1.0");
        logToScreen("Uptime: " + String(millis()/1000) + "s");
        logToScreen("RAM Free: " + String(ESP.getFreeHeap()/1024) + "KB");
        logToScreen("SD: " + String(SD.totalBytes()/1024/1024) + "MB");
        logToScreen("CPU: S3 Dual-Core");
        return;
    }

    int spaceIdx = cmd.indexOf(' ');
    String action = (spaceIdx == -1) ? cmd : cmd.substring(0, spaceIdx);
    String rest = (spaceIdx == -1) ? "" : cmd.substring(spaceIdx + 1);

    if (action == "ls") {
        File root = SD.open(currentDir);
        File f = root.openNextFile();
        while(f) { logToScreen(f.name()); f = root.openNextFile(); }
    } 
    else if (action == "touch") {
        File f = SD.open(currentDir + rest, FILE_WRITE);
        if(f) { f.close(); logToScreen("Created: " + rest); }
    }
    else if (action == "cat") {
        File f = SD.open(currentDir + rest);
        if(f) { 
            String content = "";
            while(f.available()) content += (char)f.read();
            logToScreen(content);
            f.close(); 
        }
        else logToScreen("Not found");
    }
    else if (action == "echo") {
        int redirIdx = rest.indexOf('>');
        if (redirIdx != -1) {
            String content = rest.substring(0, redirIdx - 1);
            content.replace("\"", "");
            String fileName = rest.substring(redirIdx + 2);
            File f = SD.open(currentDir + fileName, FILE_WRITE);
            if(f) { f.print(content); f.close(); logToScreen("Saved: " + fileName); }
        } else {
            logToScreen(rest);
        }
    }
    else {
        logToScreen("Cmd not found");
    }
}
