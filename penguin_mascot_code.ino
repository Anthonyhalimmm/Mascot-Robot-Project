#include <Servo.h>
Servo myservokiri;
Servo myservokanan;
Servo myservobadan;
Servo myservoatas;


// servo kiri pin
int servokiri = 6;
int nilai_servokiri = 90;
int tujuan_servokiri;
int delay_servokiri;
// servo kanan pin
int servokanan = 5;
int nilai_servokanan = 90;
int tujuan_servokanan;
int delay_servokanan;
// servo badan pin
int servobadan = 7;
int nilai_servobadan = 60;
int tujuan_servobadan;
int delay_servobadan;
// servo atas pin
int servoatas = 4;
int nilai_servoatas = 90;
int tujuan_servoatas;
int delay_servoatas;


//wave
const int wave_sudut_kiri[] = { 70, 40, 70, 45, 70, 90, 90, 90, 90, 90};
const int wave_waktu_kiri[] = { 22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 1, 1, 1, 1};
const int wave_sudut_kanan[] = { 70, 40, 70, 45, 70, 90, 90, 90, 90, 90};
const int wave_waktu_kanan[] = {  22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 1, 1, 1, 1};
const int wave_sudut_badan[] = { 70, 50, 70, 50, 70, 60, 60, 60, 60, 60};
const int wave_waktu_badan[] = { 33.75,33.75, 33.75, 33.75, 33.75, 33.75, 1, 1, 1, 1};
const int wave_waktu_atas[] = { 16.9, 16.9, 16.9, 16.9, 16.9, 16.9, 1, 1, 1, 1};
const int wave_sudut_atas[] = { 70, 110, 70, 110, 70, 90, 90, 90, 90, 90}; //too fast


//dance 1
const int dance_sudut_kiri[] = { 120, 60, 120, 60, 120, 60, 120, 60, 120, 90};
const int dance_waktu_kiri[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };
const int dance_sudut_kanan[] = { 60, 120, 60, 120, 60, 120, 60, 120, 60, 90 };
const int dance_waktu_kanan[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };
const int dance_sudut_badan[] = { 90, 30, 90, 30, 90, 30, 90, 30, 90, 60 };
const int dance_waktu_badan[] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };
const int dance_waktu_atas[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };
const int dance_sudut_atas[] = { 70, 110, 70, 110, 70, 110, 70, 110, 70, 90 }; // pas


//dance 2
const int dance2_sudut_kiri[] = { 120, 60, 120, 60, 120, 60, 120, 60, 120, 90};
const int dance2_waktu_kiri[] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15 };
const int dance2_sudut_kanan[] = { 120, 60, 120, 60, 120, 60, 120, 60, 120, 90 };
const int dance2_waktu_kanan[] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15 };
const int dance2_sudut_badan[] = { 90, 30, 90, 30, 90, 30, 90, 30, 90, 60 };
const int dance2_waktu_badan[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
const int dance2_waktu_atas[] = { 22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 22.5, 22.5 };
const int dance2_sudut_atas[] = { 70, 110, 70, 110, 70, 110, 70, 110, 70, 90 };


//angry
const int angry_sudut_kiri[] = { 80, 130, 80, 130, 80, 90, 90, 90, 90, 90 };
const int angry_waktu_kiri[] = {25, 15, 25, 15, 25, 15, 1, 1, 1, 1};
const int angry_sudut_kanan[] = { 100, 50, 100, 50, 100, 90, 90, 90, 90, 90 };
const int angry_waktu_kanan[] = {25, 15, 25, 15, 25, 15, 1, 1, 1, 1};
const int angry_sudut_badan[] = { 80, 40, 80, 40, 80, 60, 60, 60, 60, 60 };
const int angry_waktu_badan[] = { 25, 15, 25, 15, 25, 15, 1, 1, 1, 1};
const int angry_waktu_atas[] = { 18, 18, 18, 18, 18, 18, 1, 1, 1, 1};
const int angry_sudut_atas[] = { 70, 110, 70, 110, 70, 90, 90, 90, 90, 90 };//agak meleset. tangan naik lambat


//sad
const int sad_sudut_kiri[] = { 100, 130, 100, 130, 100, 90, 90, 90, 90, 90 };
const int sad_waktu_kiri[] = {50, 50, 50, 50, 50, 25, 1, 1, 1, 1};
const int sad_sudut_kanan[] = { 80, 50, 80, 50, 80, 90, 90, 90, 90, 90 };
const int sad_waktu_kanan[] = {50, 50, 50, 50, 50, 25, 1, 1, 1, 1};
const int sad_sudut_badan[] = { 70, 50, 70, 50, 70, 60, 60, 60, 60, 60 };
const int sad_waktu_badan[] = { 75, 75, 75, 75, 75, 37.5, 1, 1, 1, 1};
const int sad_waktu_atas[] = { 37.5, 37.5, 37.5, 37.5, 37.5, 19, 1, 1, 1, 1};
const int sad_sudut_atas[] = { 70, 110, 70, 110, 70, 90, 90, 90, 90, 90 };// something off


//excited
const int excited_sudut_kiri[] = { 50, 80, 50, 80, 50, 90, 90, 90, 90, 90 };
const int excited_waktu_kiri[] = {30, 30, 30, 30, 30, 30, 1, 1, 1, 1};
const int excited_sudut_kanan[] = { 130, 100, 130, 100, 130, 90, 90, 90, 90, 90 };
const int excited_waktu_kanan[] = {30, 30, 30, 30, 30, 30, 1, 1, 1, 1 };
const int excited_sudut_badan[] = { 70, 50, 70, 50, 70, 60, 60, 60, 60, 60 };
const int excited_waktu_badan[] = { 45, 45, 45, 45, 45, 45, 1, 1, 1, 1};
const int excited_waktu_atas[] = { 18, 18, 18, 18, 18, 18, 1, 1, 1, 1};
const int excited_sudut_atas[] = { 70, 110, 70, 110, 70, 90, 90, 90, 90, 90}; // thank you for ur purchase is wrong




int sudut_servokiri[10];
int waktu_servokiri[10];
int sudut_servokanan[10];
int waktu_servokanan[10];
int sudut_servobadan[10];
int waktu_servobadan[10];
int sudut_servoatas[10];
int waktu_servoatas[10];




// ultrasonic
#define trig 22
#define echo 23




// mp3
#include <DFRobotDFPlayerMini.h>




#define mp3Serial Serial3
DFRobotDFPlayerMini mp3;




// gate utk stop ultrasonic
int distance;
bool waveDetected = false;
bool personDetected = false;




// gate utk ga looping
bool waveContinue = true;
bool personContinue = true;




// gate utk lcd
bool defaultlcd = true;




//millis
unsigned long wavemilliskiri = 0;
long waveintervalkiri;




unsigned long wavemilliskanan = 0;
long waveintervalkanan;




unsigned long wavemillisbadan = 0;
long waveintervalbadan;




unsigned long wavemillisatas = 0;
long waveintervalatas;


bool espReady = true;




void sendLCD(const char* cmd) {
  if (!espReady) return;
  Serial2.println(cmd);
  espReady = false;
}


void checkESP() {
  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    if (msg.indexOf("READY") >= 0) {
      espReady = true;
    }
  }
}


void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);




  myservokiri.attach(servokiri);
  myservokanan.attach(servokanan);
  myservobadan.attach(servobadan);
  myservoatas.attach(servoatas);




  myservokiri.write(nilai_servokiri);
  myservokanan.write(nilai_servokanan);
  myservobadan.write(nilai_servobadan);
  myservoatas.write(nilai_servoatas);


  randomSeed(analogRead(A0));




  mp3Serial.begin(9600);
  mp3.begin(mp3Serial);
  mp3.volume(27);
}




void loop() {
  checkESP();
  // Serial.print(nilai_servokiri);
  // Serial.print(" ");
  // Serial.print(tujuan_servokiri);
  // Serial.print(" | ");
  // Serial.print(nilai_servokanan);
  // Serial.print(" ");
  // Serial.println(tujuan_servokanan);


  if (waveDetected == false && personDetected == false) {  // ditambahkan personDetected
    if (espReady) {
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
    }


    int timing = pulseIn(echo, HIGH, 25000);  // ~4m timeout
    if (timing == 0) return;
    distance = (timing * 0.034) / 2;
    // Serial.println(distance);


    if (distance > 15) {
      waveContinue = false;
    }
    if (distance < 80 || distance > 150) {  //ditambahkan utk persondetected
      personContinue = false;
    }
    if (distance < 15 && waveContinue == false && personDetected == false) {
      int moveType = random(0, 6);
      Serial.println(moveType);
      if (moveType == 0) {  // inisialisasi array wave
        memcpy(sudut_servokiri, wave_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, wave_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, wave_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, wave_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, wave_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, wave_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, wave_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, wave_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|3.raw|right|8.raw");
          sendLCD("left|3.raw|right|7.raw");
          defaultlcd = false;
        }
        delay(700);
        int wavesound;
        if (random(0, 2) == 0) {
          wavesound = 14;  // 0014.mp3 hihihi hello
        } else {
          wavesound = 2;  // 0002.mp3 i can wave too
        }
        mp3.play(wavesound);


      } else if (moveType == 1) {  // inisialisasi array dance
        memcpy(sudut_servokiri, dance_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, dance_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, dance_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, dance_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, dance_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, dance_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, dance_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, dance_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|4.raw|right|9.raw");
          sendLCD("left|4.raw|right|9.raw");
          defaultlcd = false;
        }
        delay(700);
        // int dancesound;
        // if (random(0, 2) == 0) {
        //   dancesound = 9;  // 008.mp3
        // } else {
        //   dancesound = 13;  // 0010.mp3
        // }
        mp3.play(5);


      } else if (moveType == 2) {  // inisialisasi array angry
        memcpy(sudut_servokiri, angry_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, angry_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, angry_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, angry_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, angry_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, angry_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, angry_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, angry_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|4.raw|right|9.raw");
          sendLCD("left|1.raw|right|6.raw");
          defaultlcd = false;
        }
        delay(700);
        int angrysound;
        if (random(0, 2) == 0) {
          angrysound = 1;  // 001.mp3 thats not nice
        } else {
          angrysound = 6;  // 006.mp3 im angry now
        }
        mp3.play(angrysound);
      } else if (moveType == 3) {  // inisialisasi array sad
        memcpy(sudut_servokiri, sad_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, sad_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, sad_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, sad_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, sad_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, sad_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, sad_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, sad_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|4.raw|right|9.raw");
          sendLCD("left|5.raw|right|10.raw");
          defaultlcd = false;
        }
        delay(700);
        int sadsound;
        if (random(0, 2) == 0) {
          sadsound = 11;  
        } else {
          sadsound = 18;  // im sad and i feel dizzy
        }
        mp3.play(sadsound);
      } else if (moveType == 4) {  // inisialisasi array excited
        memcpy(sudut_servokiri, excited_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, excited_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, excited_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, excited_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, excited_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, excited_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, excited_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, excited_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|4.raw|right|9.raw");
          sendLCD("left|4.raw|right|9.raw");
          defaultlcd = false;
        }
        delay(700);
        int excitedsound;
        if (random(0, 2) == 0) {
          excitedsound = 3;  // 003.mp3
        } else {
          excitedsound = 7;  // 006.mp3
        }
        mp3.play(excitedsound);
      } else if (moveType == 5) {  // inisialisasi array dance 2 (dance with song)
        memcpy(sudut_servokiri, dance2_sudut_kiri, sizeof(sudut_servokiri));
        memcpy(waktu_servokiri, dance2_waktu_kiri, sizeof(waktu_servokiri));
        memcpy(sudut_servokanan, dance2_sudut_kanan, sizeof(sudut_servokanan));
        memcpy(waktu_servokanan, dance2_waktu_kanan, sizeof(waktu_servokanan));
        memcpy(sudut_servobadan, dance2_sudut_badan, sizeof(sudut_servobadan));
        memcpy(waktu_servobadan, dance2_waktu_badan, sizeof(waktu_servobadan));
        memcpy(waktu_servoatas, dance2_waktu_atas, sizeof(waktu_servoatas));
        memcpy(sudut_servoatas, dance2_sudut_atas, sizeof(sudut_servoatas));


        if (defaultlcd == true) {
          // Serial2.println("left|4.raw|right|9.raw");
          sendLCD("left|4.raw|right|9.raw");
          defaultlcd = false;
        }
        delay(700);
        int dance2sound;
        if (random(0, 2) == 0) {
          dance2sound = 19;  
        } else {
          dance2sound = 17;  // gangnam style and im not cute anymore song
        }
        mp3.play(dance2sound);
      }
      //tambah gerakan disini
      waveDetected = true;
      tujuan_servokiri = sudut_servokiri[0];
      delay_servokiri = waktu_servokiri[0];
      tujuan_servokanan = sudut_servokanan[0];
      delay_servokanan = waktu_servokanan[0];
      tujuan_servobadan = sudut_servobadan[0];
      delay_servobadan = waktu_servobadan[0];
      tujuan_servoatas = sudut_servoatas[0];
      delay_servoatas = waktu_servoatas[0];
      wavemilliskiri = millis();
      wavemilliskanan = millis();
      wavemillisbadan = millis();
      wavemillisatas = millis();
    }
    if (distance > 80 && distance < 150 && personContinue == false && waveDetected == false) {
      // Serial.println("Masuk B");
      memcpy(sudut_servokiri, wave_sudut_kiri, sizeof(sudut_servokiri));
      memcpy(waktu_servokiri, wave_waktu_kiri, sizeof(waktu_servokiri));
      memcpy(sudut_servokanan, wave_sudut_kanan, sizeof(sudut_servokanan));
      memcpy(waktu_servokanan, wave_waktu_kanan, sizeof(waktu_servokanan));
      memcpy(sudut_servobadan, wave_sudut_badan, sizeof(sudut_servobadan));
      memcpy(waktu_servobadan, wave_waktu_badan, sizeof(waktu_servobadan));
      memcpy(waktu_servoatas, wave_waktu_atas, sizeof(waktu_servoatas));
      memcpy(sudut_servoatas, wave_sudut_atas, sizeof(sudut_servoatas));


      if (defaultlcd == true) {
        // Serial2.println("left|3.raw|right|8.raw");
        sendLCD("left|3.raw|right|8.raw");
        defaultlcd = false;
      }
      delay(600);
      int wavesound;
      if (random(0, 2) == 0) {
        wavesound = 4;  // 004.mp3
      } else {
        wavesound = 21;  // 0015.mp3
      }
      mp3.play(wavesound);


      personDetected = true;
      tujuan_servokiri = sudut_servokiri[0];
      delay_servokiri = waktu_servokiri[0];
      tujuan_servokanan = sudut_servokanan[0];
      delay_servokanan = waktu_servokanan[0];
      tujuan_servobadan = sudut_servobadan[0];
      delay_servobadan = waktu_servobadan[0];
      tujuan_servoatas = sudut_servoatas[0];
      delay_servoatas = waktu_servoatas[0];
      wavemilliskiri = millis();
      wavemilliskanan = millis();
      wavemillisbadan = millis();
      wavemillisatas = millis();
    }
    delay(1);
  }


  else {
    //gerakkan servo sampai semua nya -1
    if (nilai_servoatas != tujuan_servoatas) {
      gerak_servoatas();
    } else {
      for (int i = 0; i < 10; i++) {
        if (nilai_servoatas == sudut_servoatas[i]) {
          sudut_servoatas[i] = -1;
          break;
        }
      }
      for (int i = 0; i < 10; i++) {
        if (sudut_servoatas[i] != -1) {
          tujuan_servoatas = sudut_servoatas[i];
          delay_servoatas = waktu_servoatas[i];
          break;
        }
      }
    }
    if (nilai_servokiri != tujuan_servokiri) {
      gerak_servokiri();
    } else {
      for (int i = 0; i < 10; i++) {
        if (nilai_servokiri == sudut_servokiri[i]) {
          sudut_servokiri[i] = -1;
          break;
        }
      }
      for (int i = 0; i < 10; i++) {
        if (sudut_servokiri[i] != -1) {
          tujuan_servokiri = sudut_servokiri[i];
          delay_servokiri = waktu_servokiri[i];
          break;
        }
      }
    }
    if (nilai_servokanan != tujuan_servokanan) {
      gerak_servokanan();
    } else {
      for (int i = 0; i < 10; i++) {
        if (nilai_servokanan == sudut_servokanan[i]) {
          sudut_servokanan[i] = -1;
          break;
        }
      }
      for (int i = 0; i < 10; i++) {
        if (sudut_servokanan[i] != -1) {
          tujuan_servokanan = sudut_servokanan[i];
          delay_servokanan = waktu_servokanan[i];
          break;
        }
      }
    }
    if (nilai_servobadan != tujuan_servobadan) {
      gerak_servobadan();
    } else {
      for (int i = 0; i < 10; i++) {
        if (nilai_servobadan == sudut_servobadan[i]) {
          sudut_servobadan[i] = -1;
          break;
        }
      }
      for (int i = 0; i < 10; i++) {
        if (sudut_servobadan[i] != -1) {
          tujuan_servobadan = sudut_servobadan[i];
          delay_servobadan = waktu_servobadan[i];
          break;
        }
      }
    }
    if (tujuan_servokiri == nilai_servokiri
        && tujuan_servokanan == nilai_servokanan
        && tujuan_servobadan == nilai_servobadan
        && tujuan_servoatas == nilai_servoatas
        && sudut_servokiri[9] == -1
        && sudut_servokanan[9] == -1
        && sudut_servobadan[9] == -1
        && sudut_servoatas[9] == -1) {


      if (waveDetected) {
        waveDetected = false;
        waveContinue = true;
      }


      if (personDetected) {
        personDetected = false;
        personContinue = true;
      }
      // Serial2.println("left|2.raw|right|7.raw"); // original eyes
      sendLCD("left|2.raw|right|7.raw");
      defaultlcd = true;
    }
    delay(1);
  }
  // Serial.print(waveDetected);
  // Serial.print("|");
  // Serial.print(waveContinue);
  // Serial.print("|");
  // Serial.print(personDetected);
  // Serial.print("|");
  // Serial.print(personContinue);
  // Serial.print("|");
  // Serial.print(nilai_servoatas);
  // Serial.print("|");
  // Serial.print(tujuan_servoatas);
  // Serial.print("|");
  // Serial.print(nilai_servokiri);
  // Serial.print("|");
  // Serial.print(tujuan_servokiri);
  // Serial.print("|");
  // Serial.print(nilai_servokanan);
  // Serial.print("|");
  // Serial.println(tujuan_servokanan);
}
//logic gerak kiri dan kanan
void gerak_servokiri() {
  if (millis() - wavemilliskiri > delay_servokiri) {
    if (nilai_servokiri > tujuan_servokiri) {
      nilai_servokiri--;
    } else if (nilai_servokiri < tujuan_servokiri) {
      nilai_servokiri++;
    }
    myservokiri.write(nilai_servokiri);
    wavemilliskiri = millis();
  }
}
void gerak_servokanan() {
  if (millis() - wavemilliskanan > delay_servokanan) {
    if (nilai_servokanan > tujuan_servokanan) {
      nilai_servokanan--;
    } else if (nilai_servokanan < tujuan_servokanan) {
      nilai_servokanan++;
    }
    myservokanan.write(nilai_servokanan);
    wavemilliskanan = millis();
  }
}
void gerak_servobadan() {
  if (millis() - wavemillisbadan > delay_servobadan) {
    if (nilai_servobadan > tujuan_servobadan) {
      nilai_servobadan--;
    } else if (nilai_servobadan < tujuan_servobadan) {
      nilai_servobadan++;
    }
    myservobadan.write(nilai_servobadan);
    wavemillisbadan = millis();
  }
}
void gerak_servoatas() {
  if (millis() - wavemillisatas > delay_servoatas) {
    if (nilai_servoatas > tujuan_servoatas) {
      nilai_servoatas--;
    } else if (nilai_servoatas < tujuan_servoatas) {
      nilai_servoatas++;
    }
    myservoatas.write(nilai_servoatas);
    wavemillisatas = millis();
  }
}




//mp3 sound
//001 thats not nice
//002 i can wave too
//003 thank you for your purchase
//004 we sell pancakes, bingsu, and drinks (utk persondetected)
//005 cny song
//006 i am angry now
//007 i love you snow much
//008 im shy
//009 watch me dance
//0010 ig song qthkr | song
//0011 don't leave me
//0012 ig ocean | song
//0013 hihi spin spin spin
//0014 hihihi hello
//0015 hi i'm a penguin
//0016 too close
//0017 i'm not cute anymore | song
//0018 i feel dizzy
//0019 gangnam style | song
//0020 kencana dengnengdengnen | song
//0021 hi welcome to misnow (utk persondetected)




//lcd image
// 001 angry
// 002 normal
// 003 close
// 004 happy
// 005 sad
// 006 angry (right)
// 007 normal (right)
// 008 close (right)
// 009 happy (right)
// 010 sad (right)