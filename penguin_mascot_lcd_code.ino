#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// ================= MODE SERIAL =================
// Pilih mode komunikasi:
// 0 = Serial (USB) untuk debugging dari Arduino IDE
// 1 = Serial2 untuk komunikasi dari Arduino Mega/ESP32 lain
#define SERIAL_MODE 0


bool espBusy = false;

// ================= PIN TFT =================
// TFT 1 (LEFT / KIRI)
#define TFT1_CS 5
#define TFT1_DC 17
#define TFT1_RST 16
#define TFT1_LED 2

// TFT 2 (RIGHT / KANAN)
#define TFT2_CS 21
#define TFT2_DC 22
#define TFT2_RST 25
#define TFT2_LED 12

// ================= PIN SD =================
#define SD_CS 4  // CS SD Card

// ================= TFT =================
Adafruit_ST7735 tft1 = Adafruit_ST7735(TFT1_CS, TFT1_DC, TFT1_RST);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT2_CS, TFT2_DC, TFT2_RST);

// ================= Ukuran TFT =================
#define TFT_WIDTH 128
#define TFT_HEIGHT 160

// ================= Konfigurasi =================
// ROTATION: 0=portrait, 1=landscape, 2=inverted portrait, 3=inverted landscape
#define DISPLAY_ROTATION 0
// COLOR_MODE: 0=default, 1=swap byte, 2=swap R&B, 3=swap byte & R&B
#define COLOR_MODE 2
// FIT_MODE: 0=center, 1=stretch full
#define FIT_MODE 1
// BACKGROUND_COLOR: 0=hitam, 1=putih
#define BACKGROUND_COLOR 1

// ================= Buffer Command =================
#define COMMAND_BUFFER_SIZE 256
char commandBuffer[COMMAND_BUFFER_SIZE];
int commandIndex = 0;

void setup() {
  // Serial selection
  if (SERIAL_MODE == 0) {
    Serial.begin(115200);
    Serial.println("ESP32 Dual TFT - Serial Mode (USB)");
  } else {
    Serial.begin(115200);   // Debug via USB
    Serial2.begin(115200);  // Communication from Arduino Mega
    Serial.println("ESP32 Dual TFT - Serial2 Mode");
  }

  // Inisialisasi pin CS untuk semua device ke HIGH (inactive)
  pinMode(TFT1_CS, OUTPUT);
  digitalWrite(TFT1_CS, HIGH);
  pinMode(TFT2_CS, OUTPUT);
  digitalWrite(TFT2_CS, HIGH);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  // Inisialisasi SPI untuk TFT & SD Card (VSPI - shared bus)
  Serial.println(" Inisialisasi SPI (VSPI)...");
  SPI.begin(18, 19, 23);

  // Inisialisasi SD Card dengan shared SPI bus
  Serial.println(" Inisialisasi SD Card...");
  if (!SD.begin(SD_CS, SPI)) {
    Serial.println(" Gagal inisialisasi SD Card!");
    Serial.println("   Cek kabel dan pastikan SD card terpasang dengan benar.");
    Serial.println("   SD VSPI Pins: SCK=18, MISO=19, MOSI=23, CS=4");
  }
  Serial.println(" SD Card siap");

  // Release SD Card dari SPI sebelum inisialisasi TFT
  SPI.endTransaction();

  // Inisialisasi pin RST untuk kedua TFT
  pinMode(TFT1_RST, OUTPUT);
  digitalWrite(TFT1_RST, HIGH);
  pinMode(TFT2_RST, OUTPUT);
  digitalWrite(TFT2_RST, HIGH);

  // Nyalakan backlight untuk kedua TFT
  pinMode(TFT1_LED, OUTPUT);
  digitalWrite(TFT1_LED, HIGH);
  pinMode(TFT2_LED, OUTPUT);
  digitalWrite(TFT2_LED, HIGH);

  // Inisialisasi TFT 1 (LEFT)
  Serial.println("\n TFT 1 (LEFT) init...");
  tft1.initR(INITR_GREENTAB);
  tft1.setRotation(DISPLAY_ROTATION);
  tft1.fillScreen(ST77XX_BLACK);
  Serial.print("TFT 1 dimensi: ");
  Serial.print(tft1.width());
  Serial.print("x");
  Serial.println(tft1.height());

  // Inisialisasi TFT 2 (RIGHT)
  Serial.println("\n TFT 2 (RIGHT) init...");
  tft2.initR(INITR_GREENTAB);
  tft2.setRotation(DISPLAY_ROTATION);
  tft2.fillScreen(ST77XX_BLACK);
  Serial.print("TFT 2 dimensi: ");
  Serial.print(tft2.width());
  Serial.print("x");
  Serial.println(tft2.height());

  tft1.setSPISpeed(40000000);  // 40 MHz
  tft2.setSPISpeed(40000000);

  Serial.print("\n Rotation: ");
  Serial.println(DISPLAY_ROTATION);
  Serial.print(" Color mode: ");
  Serial.println(COLOR_MODE);
  Serial.print(" Serial Mode: ");
  Serial.println(SERIAL_MODE == 0 ? "USB (Serial)" : "Serial2");

  // Tampilkan pesan siap
  Serial.println("\n========================================");
  Serial.println(" READY - Waiting for commands");
  Serial.println("========================================");
  Serial.println("Format command:");
  Serial.println("  left|3.raw|right|8.raw  - Display 3.raw on left, 8.raw on right");
  Serial.println("  left|3.raw               - Display only on left");
  Serial.println("  right|8.raw              - Display only on right");
  Serial.println("  5.raw                    - Display on both TFTs");
  Serial.println("  list                     - List all files on SD card");
  Serial.println("========================================\n");

  // List semua file di SD card untuk debugging
  Serial.println(" Files on SD Card:");
  File root = SD.open("/");
  if (root) {
    File file = root.openNextFile();
    while (file) {
      Serial.print("  ");
      Serial.print(file.name());
      Serial.print(" (");
      Serial.print(file.size());
      Serial.println(" bytes)");
      file = root.openNextFile();
    }
    root.close();
  } else {
    Serial.println("   Failed to open directory!");
  }
  Serial.println("\n========================================\n");
}

void loop() {
  // Baca data dari serial yang dipilih
  if (SERIAL_MODE == 0) {
    // Mode Serial (USB)
    while (Serial.available() > 0) {
      char c = Serial.read();




      // Tambah ke buffer
      if (c == '\n' || c == '\r') {
        // Command selesai, parse dan eksekusi
        commandBuffer[commandIndex] = '\0';
        if (commandIndex > 0) {
          Serial.print(" Command received: ");
          Serial.println(commandBuffer);
          parseCommand(commandBuffer);
          Serial.println("READY");
        }
        commandIndex = 0;
      } else if (commandIndex < COMMAND_BUFFER_SIZE - 1) {
        commandBuffer[commandIndex++] = c;
      }
    }
  } else {
    // Mode Serial2
    while (Serial2.available() > 0) {
      char c = Serial2.read();




      // Echo ke Serial USB untuk debugging
      Serial.write(c);

      // Tambah ke buffer
      if (c == '\n' || c == '\r') {
        // Command selesai, parse dan eksekusi
        commandBuffer[commandIndex] = '\0';
        if (commandIndex > 0) {
          Serial.print("\n Command received: ");
          Serial.println(commandBuffer);
          parseCommand(commandBuffer);
        }
        commandIndex = 0;
      } else if (commandIndex < COMMAND_BUFFER_SIZE - 1) {
        commandBuffer[commandIndex++] = c;
      }
    }
  }
}

// ================= Parse Command =================
void parseCommand(char* command) {
  char filenameLeft[32] = "";
  char filenameRight[32] = "";
  bool hasLeft = false;
  bool hasRight = false;

  // Cek command special
  if (strcmp(command, "list") == 0) {
    Serial.println("\n Files on SD Card:");
    File root = SD.open("/");
    if (root) {
      File file = root.openNextFile();
      while (file) {
        Serial.print("  ");
        Serial.print(file.name());
        Serial.print(" (");
        Serial.print(file.size());
        Serial.println(" bytes)");
        file = root.openNextFile();
      }
      root.close();
    } else {
      Serial.println("   Failed to open directory!");
    }
    Serial.println(" List complete\n");
    return;
  }

  // Parse command normal
  char* token = strtok(command, "|");

  if (token == NULL) {
    Serial.println(" Invalid command format");
    return;
  }

  // Cek apakah command dimulai dengan "left" atau "right"
  if (strcmp(token, "left") == 0) {
    // Format: left|filename_left|right|filename_right
    // atau: left|filename_left
    token = strtok(NULL, "|");
    if (token == NULL) {
      Serial.println(" Missing left filename");
      return;
    }
    strcpy(filenameLeft, token);
    hasLeft = true;




    // Cek apakah ada "right" setelahnya
    token = strtok(NULL, "|");
    if (token != NULL && strcmp(token, "right") == 0) {
      token = strtok(NULL, "|");
      if (token != NULL) {
        strcpy(filenameRight, token);
        hasRight = true;
      }
    }
  } else if (strcmp(token, "right") == 0) {
    // Format: right|filename_right
    token = strtok(NULL, "|");
    if (token == NULL) {
      Serial.println(" Missing right filename");
      return;
    }
    strcpy(filenameRight, token);
    hasRight = true;
  } else {
    // Format: filename (tampilkan di kedua TFT)
    strcpy(filenameLeft, token);
    strcpy(filenameRight, token);
    hasLeft = true;
    hasRight = true;
  }

  // Tampilkan gambar
  Serial.println("\n Executing command...");

  // Efek robot blink - matikan backlight sambil render
  digitalWrite(TFT1_LED, LOW);
  digitalWrite(TFT2_LED, LOW);
  tft1.fillScreen(ST77XX_BLACK);
  tft2.fillScreen(ST77XX_BLACK);
  delay(80);  // Blink duration

  // Render ke TFT yang sesuai (backlight mati biar gak kelihatan rendering)
  if (hasLeft) {
    Serial.print(" TFT LEFT: ");
    Serial.println(filenameLeft);
    displayRawImage(filenameLeft, tft1);
  }

  if (hasRight) {
    Serial.print(" TFT RIGHT: ");
    Serial.println(filenameRight);
    displayRawImage(filenameRight, tft2);
  }

  // Nyalakan backlight setelah selesai render
  digitalWrite(TFT1_LED, HIGH);
  digitalWrite(TFT2_LED, HIGH);

  Serial.println(" Command executed\n");
}

// ================= Fungsi tampil RAW =================
void displayRawImage(const char* filename, Adafruit_ST7735& tft) {


  char fullPath[64];
  if (filename[0] != '/') {
    fullPath[0] = '/';
    strcpy(fullPath + 1, filename);
  } else {
    strcpy(fullPath, filename);
  }


  SPI.endTransaction();
  File file = SD.open(fullPath);
  if (!file) {
    Serial.println(" Gagal buka file RAW!");
    return;
  }


  uint16_t imgWidth = 128;
  uint16_t imgHeight = 160;


  size_t totalPixels = file.size() / 2;
  if (totalPixels == 25600) {
    imgWidth = 160;
    imgHeight = 160;
  }


  if (imgWidth > tft.width()) imgWidth = tft.width();
  if (imgHeight > tft.height()) imgHeight = tft.height();


  // ===== SET WINDOW SEKALI =====
  tft.startWrite();
  tft.setAddrWindow(0, 0, imgWidth, imgHeight);


  static uint16_t lineBuffer[2][TFT_WIDTH];


  for (uint16_t y = 0; y < imgHeight; y += 2) {


    for (uint8_t row = 0; row < 2; row++) {
      if (y + row >= imgHeight) break;


      for (uint16_t x = 0; x < imgWidth; x++) {
        uint8_t hi = file.read();
        uint8_t lo = file.read();
        uint16_t color = (hi << 8) | lo;


        if (COLOR_MODE == 2) {
          uint16_t r = (color >> 11) & 0x1F;
          uint16_t g = (color >> 5) & 0x3F;
          uint16_t b = color & 0x1F;
          color = (b << 11) | (g << 5) | r;
        }


        lineBuffer[row][x] = color;
      }
    }


    // ===== KIRIM 2 BARIS SEKALIGUS =====
    tft.writePixels(lineBuffer[0], imgWidth);
    if (y + 1 < imgHeight) {
      tft.writePixels(lineBuffer[1], imgWidth);
    }
  }

  tft.endWrite();
  file.close();

  Serial.println(" Render selesai (streaming mode)");
}