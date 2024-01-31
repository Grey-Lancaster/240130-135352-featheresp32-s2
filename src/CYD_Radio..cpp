#include <Arduino.h>
#include <TFT_eSPI.h>      // Include TFT library
#include <Audio.h>         // Include Audio library
#include <WiFiManager.h>   // Include WiFiManager library by wnatth3

TFT_eSPI tft = TFT_eSPI();  // Initialize TFT library
Audio audio(true, I2S_DAC_CHANNEL_LEFT_EN);  // Initialize Audio library
WiFiManager wifiManager;    // Initialize WiFiManager

void setup() {
  Serial.begin(115200);

  // Start the TFT display and set it to black
  tft.init();
  tft.setRotation(1); // Set the display in landscape
  tft.setTextWrap(true, true);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  
  tft.drawString("Title", 0, 10, 1);

  // WiFiManager local initialization
  wifiManager.autoConnect("AutoConnectAP"); // AutoConnect with AP name "AutoConnectAP"

  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup audio
  audio.forceMono(true);
  audio.setVolume(3);

  bool succeeded;
  do {
    succeeded = audio.connecttohost("http://sc8.1.fm:8100/;");
    delay(500);
    Serial.println("Retrying");
  } while (!succeeded);
}

void loop() {
  audio.loop(); // Process audio
}

void printTitle(const char* info) {
  tft.fillRect(0, 20, 320, 200, TFT_BLACK);
  tft.setCursor(0, 20, 4);
  tft.setTextColor(TFT_SKYBLUE);
  tft.println(info);
}

void printInfo(const char* info) {
  tft.fillRect(0, 230, 320, 10, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(info, 0, 230, 1);
}

// Callback functions for the audio library
void audio_info(const char *info) {
  Serial.print("info        "); 
  Serial.println(info);
  printInfo(info);
}

void audio_id3data(const char *info) {
  Serial.print("id3data     ");
  Serial.println(info);
}

void audio_eof_mp3(const char *info) {
  Serial.print("eof_mp3     ");
  Serial.println(info);
}

void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}

void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
  printTitle(info);
}

void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}

void audio_commercial(const char *info) {
  Serial.print("commercial  ");
  Serial.println(info);
}

void audio_icyurl(const char *info) {
  Serial.print("icyurl      ");
  Serial.println(info);
}

void audio_lasthost(const char *info) {
  Serial.print("lasthost    ");
  Serial.println(info);
}

void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  ");
  Serial.println(info);
}
