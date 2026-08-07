#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 19
#define SCL_PIN 18

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// =========================
// DATA LIRIK + TIMESTAMP
// =========================

struct Lyric {
  int time;
  String line1;
  String line2;
  String line3;
};

Lyric lyrics[] = {
    {0,  "But you", "should", "know"},
    {2,  "That I", "died", "slow"},
    {4,  "Running", "through", "the halls"},
    {7,  "Of your", "haunted", "home"},
    {9, "And the", "toughest", "part"},
    {12, "is that", "we both", "know"},
    {14, "What", "happened", "to you"},
    {15, "Why", "you're out", "on your,own"},
    {18, "Merry", "Christmas", ""},
    {21, "Please", "don't", "call"},
    {23, "Merry", "Christmas", ""},
    {25, "I'm not", "yours", "at all"},
    {27, "Merry", "Christmas", ""},
    {29, "Please", "don't", "call me"}
};

int lyricTotal = sizeof(lyrics) / sizeof(lyrics[0]);

// =========================

unsigned long startTime;
int currentLyric = 0;

void setup() {

  Wire.begin(SDA_PIN, SCL_PIN);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.setTextColor(WHITE);

  // ===== INTRO RAFFA ❤️ =====
  for (int i = 0; i < 5; i++) {

    // Hati kecil
    display.clearDisplay();

    display.setTextSize(2);
    drawCenter("Raffa", 12);

    display.fillCircle(62, 43, 3, WHITE);
    display.fillCircle(66, 43, 3, WHITE);
    display.fillTriangle(58, 44, 70, 44, 64, 52, WHITE);

    display.display();

    delay(180);

    // Hati besar
    display.clearDisplay();

    display.setTextSize(2);
    drawCenter("Raffa", 12);

    display.fillCircle(61, 42, 5, WHITE);
    display.fillCircle(67, 42, 5, WHITE);
    display.fillTriangle(54, 45, 74, 45, 64, 58, WHITE);
  
    display.display();

    delay(180);
  }

  // Diam sebentar sebelum lagu dimulai
  delay(500);
 
  startTime = millis();

}

void loop() {

  int now = (millis() - startTime) / 1000;

  // Cari lirik sesuai timestamp
  for (int i = 0; i < lyricTotal; i++) {

    if (now >= lyrics[i].time) {

      currentLyric = i;

    }

  }

  // Tampilkan lirik
  showLyric();

  // Jika lagu selesai
  if (now >= lyrics[lyricTotal - 1].time + 3) {

    // Animasi Raffa ❤️
    for (int i = 0; i < 5; i++) {

      // Hati kecil
      display.clearDisplay();

      display.setTextColor(WHITE);
      display.setTextSize(2);

      drawCenter("Raffa", 12);

      display.fillCircle(62, 43, 3, WHITE);
      display.fillCircle(66, 43, 3, WHITE);
      display.fillTriangle(58, 44, 70, 44, 64, 52, WHITE);

      display.display();

      delay(180);

      // Hati besar
      display.clearDisplay();

      display.setTextColor(WHITE);
      display.setTextSize(2);

      drawCenter("Raffa", 12);

      display.fillCircle(61, 42, 5, WHITE);
      display.fillCircle(67, 42, 5, WHITE);
      display.fillTriangle(54, 45, 74, 45, 64, 58, WHITE);

      display.display();

      delay(180);

    }

    delay(500);

    // Mulai lagi dari awal
    startTime = millis();
    currentLyric = 0;

  }

  delay(50);

}

// =========================
// TAMPILKAN LIRIK
// =========================

void showLyric() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  drawCenter(lyrics[currentLyric].line1, 5);
  drawCenter(lyrics[currentLyric].line2, 25);
  drawCenter(lyrics[currentLyric].line3, 45);

  display.display();
}

// =========================
// TEXT CENTER
// =========================

void drawCenter(String text, int y) {
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;

  display.setCursor(x, y);
  display.print(text);
}