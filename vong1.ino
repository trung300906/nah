#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 125
#define SERVOMAX 575
unsigned long elapsedTime;
unsigned long lastChangeTime = 0;
int tayphai = 0, tayphaik = 1, taytrai = 4, taytraik = 5, chanphai = 2, chanphaik = 3, chantrai = 6, chantraik = 7, than = 12;
int dem1 = 0, dem2 = 0;
void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);
  Wire.setClock(400000);
  Serial.begin(31250);
  pinMode(A0, INPUT);
}

void loop() {
  pwm.setPWM(tayphai, 0, xoay(0));
  pwm.setPWM(taytrai, 0, xoay(180));
  pwm.setPWM(tayphaik, 0, xoay(90));
  pwm.setPWM(taytraik, 0, xoay(90));
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chantrai, 0, xoay(90));
  pwm.setPWM(chanphaik, 0, xoay(90));
  pwm.setPWM(chantraik, 0, xoay(90));
  pwm.setPWM(than, 0, xoay(90));
  int analog = analogRead(A0);
  Serial.println(analog);
  chao(dem1, analog);
  logic(dem2);
  nhaykethuc(dem2);
  while (1) {};
}
void chao(int &dem1, int &analog) {
  //Serial.println("thực hiện động tác chào");
  int time = 20;
  for (int i = 0; i <= 90; i++) {
    pwm.setPWM(tayphai, 0, xoay(i));
    delay(time / 10);
  }
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(tayphaik, 0, xoay(i));
    delay(time / 10);
  }
  for (int i = 90 + 45; i >= 45; i--) {
    pwm.setPWM(tayphaik, 0, xoay(i));
    delay(time / 10);
  }
  while (analog >= 1015) {
    for (int i = 0; i <= 4; i++) {
      for (int j = 45; j <= 135; j++) {
        pwm.setPWM(tayphaik, 0, xoay(j));
        delay(time / 10);
      }
      for (int j = 135; j >= 45; j--) {
        pwm.setPWM(tayphaik, 0, xoay(j));
        delay(time / 10);
      }
    }
    Serial.println(analog);
    analog = analogRead(A0);
  }
    for (int i = 45; i <= 90; i++) {
      pwm.setPWM(tayphaik, 0, xoay(i));
      delay(time / 10);
    }
    for (int i = 90; i >= 0; i--) {
      pwm.setPWM(tayphai, 0, xoay(i));
      delay(time / 10);
    }
    delay(time / 10);

  dem1++;
}

void nhaykethuc(int &dem2) {
  //Serial.println("thực hiện động tác kết thúc");
  pwm.setPWM(tayphai, 0, xoay(0));
  pwm.setPWM(tayphaik, 0, xoay(90));
  pwm.setPWM(taytrai, 0, xoay(180));
  pwm.setPWM(taytraik, 0, xoay(90));
  delay(100);
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chanphaik, 0, xoay(90));
  pwm.setPWM(chantrai, 0, xoay(90));
  pwm.setPWM(chantraik, 0, xoay(90));
  delay(100);
  for (int i = 90; i <= 180; i++) {
    pwm.setPWM(taytraik, 0, xoay(i));
    delay(16);
  }
  for (int i = 0; i <= 13; i++) {
    Serial.println("---------------------------------------------");
  }
  dem2++;
}
void logic(int &dem2) {
  //3 → 6.5: R
  Serial.println("3->6.5");
  pwm.setPWM(taytrai, 0, xoay(90));
  delay(20);
  pwm.setPWM(taytraik, 0, xoay(180));
  for (int i = 90; i <= 90 + 30; i++) {
    pwm.setPWM(than, 0, xoay(i));
    delay(20);
  }
  for (int i = 0; i <= 2; i++) {
    for (int i = 90 + 30; i >= 90 - 30; i--) {
      pwm.setPWM(than, 0, xoay(i));
      delay(10);
    }
    for (int i = 90 - 30; i <= 90 + 30; i++) {
      pwm.setPWM(than, 0, xoay(i));
      delay(10);
    }
  }
  delay(50);
  //7 → 10: R
  Serial.println("7->10");
  pwm.setPWM(taytrai, 0, xoay(90));
  pwm.setPWM(than, 0, xoay(140));
  delay(50);
  for (int i = 90; i <= 180; i++) {
    pwm.setPWM(taytraik, 0, xoay(i));
    delay(2);
  }
  for (int i = 0; i <= 7; i++) {
    for (int i = 180; i >= 90; i--) {
      pwm.setPWM(taytraik, 0, xoay(i));
      delay(2);
    }
    for (int i = 90; i <= 180; i++) {
      pwm.setPWM(taytraik, 0, xoay(i));
      delay(2);
    }
  }
  delay(150);
  //10->13,5: R
  Serial.println("10->13.5");
  pwm.setPWM(taytrai, 0, xoay(180 - 25));
  delay(10);
  pwm.setPWM(tayphai, 0, xoay(15));
  delay(10);
  pwm.setPWM(taytraik, 0, xoay(180));
  delay(10);
  pwm.setPWM(tayphaik, 0, xoay(180));
  delay(10);
  for (int i = 90; i >= 45; i--) {
    pwm.setPWM(chanphai, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 90; i <= 90 + 55; i++) {
    pwm.setPWM(chanphaik, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 0; i <= 3; i++) {
    for (int j = 45; j <= 70; j++) {
      pwm.setPWM(chanphai, 0, xoay(j));
      pwm.setPWM(chanphaik, 0, xoay(90 + j - 20));
      delay(20);
    }
    for (int j = 60; j >= 45; j--) {
      pwm.setPWM(chanphai, 0, xoay(j));
      pwm.setPWM(chanphaik, 0, xoay(90 + j - 20));
      delay(20);
    }
  }
  delay(10);
  pwm.setPWM(chanphai, 0, xoay(90));
  delay(50);
  //14->17:R
  Serial.println("14->17");
  pwm.setPWM(taytrai, 0, xoay(180 - 25));
  delay(10);
  pwm.setPWM(tayphai, 0, xoay(15));
  delay(10);
  pwm.setPWM(taytraik, 0, xoay(180));
  delay(10);
  pwm.setPWM(tayphaik, 0, xoay(180));
  delay(10);
  for (int i = 90; i <= 135; i++) {
    pwm.setPWM(chantrai, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 90; i >= 90 - 55; i--) {
    pwm.setPWM(chantraik, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 0; i <= 3; i++) {
    for (int j = 135; j >= 110; j--) {
      pwm.setPWM(chantrai, 0, xoay(j));
      pwm.setPWM(chantraik, 0, xoay(j - 90 + 20));
      delay(20);
    }
    for (int j = 110; j <= 135; j++) {
      pwm.setPWM(chantrai, 0, xoay(j));
      pwm.setPWM(chantraik, 0, xoay(j - 90 + 20));
      delay(20);
    }
  }
  delay(10);
  pwm.setPWM(chantrai, 0, xoay(90));
  pwm.setPWM(chantraik, 0, xoay(90));
  delay(50);
  //17 → 21
  Serial.println("17->21");
  pwm.setPWM(chanphai, 0, xoay(125));
  delay(20);
  pwm.setPWM(chanphaik, 0, xoay(180 - 125));
  delay(10);
  pwm.setPWM(tayphai, 0, xoay(90));
  pwm.setPWM(taytrai, 0, xoay(90));
  delay(10);
  playa(tayphaik, 90);
  delay(10);
  playa(taytraik, 90);
  for (int i = 0; i <= 5; i++) {
    playa(tayphaik, 45);
    playa(taytraik, 45);
    delay(15);
    playa(tayphaik, 135);
    playa(taytraik, 135);
    delay(15);
  }
  playa(tayphaik, 90);
  delay(10);
  playa(taytraik, 90);
  //21->24:
  Serial.println("21->24");
  pwm.setPWM(chanphai, 0, xoay(180 - 125));
  delay(20);
  pwm.setPWM(chanphaik, 0, xoay(180 - (180 - 125)));
  delay(10);
  playa(chantrai, 115);
  playa(chantraik, 115 - 90 + 30);
  for (int i = 0; i <= 5; i++) {
    playa(tayphaik, 45);
    playa(taytraik, 45);
    delay(250);
    playa(tayphaik, 135);
    playa(taytraik, 135);
    delay(250);
  }
  //24->28
  Serial.println("24->28");
  playa(chanphai, 90);
  playa(chanphaik, 90);
  playa(chantrai, 90);
  playa(chantraik, 90);
  playa(tayphaik, 90);
  delay(500);
  //26
  playa(tayphaik, 180);
  playa(taytraik, 0);
  delay(100);
  for (int i = 180; i >= 90; i--) {
    playa(tayphaik, i);
    playa(taytraik, 180 - i);
    delay(20);
  }
  //28->32
  Serial.println("28->32");
  int countdown = 0;
  playa(chanphai, 90);
  playa(chanphaik, 90);
  playa(chantrai, 90);
  playa(chantraik, 90);
  playa(tayphaik, 90);
  delay(500);
  for (int i = 90; i <= 180; i++) {
    playa(tayphaik, i);
    playa(taytraik, 180 - i);
    delay(20);
    if (i == 90) {
      for (int j = 0; j <= 5; j++) {
        playa(chanphai, 180 - 125);
        playa(chanphaik, 125);
        playa(chantrai, 125);
        playa(chantraik, (180 - 125));
        playa(tayphaik, i + j * (180 - i) / 5);
        playa(taytraik, 180 - (i + j * (180 - i) / 5));
        delay(200);
        playa(chanphai, 70);
        playa(chanphaik, 100);
        playa(chantrai, 100);
        playa(chantraik, 80);
        delay(200);
        // Move arms while legs are moving
      }
      countdown++;
      if (countdown == 1) {
        break;
      }
    }
  }
  countdown = NULL;
  // 32 → 35
  Serial.println("32->35");
  pwm.setPWM(tayphai, 0, xoay(90));
  delay(20);
  pwm.setPWM(tayphaik, 0, xoay(0));
  for (int i = 0; i <= 4; i++) {
    pwm.setPWM(than, 0, xoay(120));
    delay(20);
    pwm.setPWM(than, 0, xoay(40));
    delay(20);
  }
  pwm.setPWM(than, 0, xoay(90));
  delay(50);
  // 35->39
  Serial.println("35->39");
  pwm.setPWM(than, 0, xoay(40));
  delay(20);
  for (int i = 0; i <= 7; i++) {
    pwm.setPWM(taytraik, 0, xoay(90));
    delay(200);
    pwm.setPWM(taytraik, 0, xoay(180));
    delay(200);
  }

  //39 → 43
  Serial.println("39->43");
  pwm.setPWM(taytrai, 0, xoay(90 + 65));
  delay(20);
  pwm.setPWM(tayphai, 0, xoay(25));
  delay(20);
  pwm.setPWM(taytraik, 0, xoay(180));
  delay(20);
  pwm.setPWM(tayphaik, 0, xoay(180));
  delay(20);
  pwm.setPWM(chanphai, 0, xoay(135));
  delay(20);
  for (int i = 90; i >= 45; i--) {
    pwm.setPWM(chanphai, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 90; i <= 90 + 55; i++) {
    pwm.setPWM(chanphaik, 0, xoay(i));
    delay(4.5);
  }
  for (int i = 0; i <= 3; i++) {
    for (int j = 45; j <= 70; j++) {
      pwm.setPWM(chanphai, 0, xoay(j));
      pwm.setPWM(chanphaik, 0, xoay(90 + j - 20));
      delay(20);
    }
    for (int j = 60; j >= 45; j--) {
      pwm.setPWM(chanphai, 0, xoay(j));
      pwm.setPWM(chanphaik, 0, xoay(90 + j - 20));
      delay(20);
    }
  }
  pwm.setPWM(chanphai, 0, xoay(90));
  delay(50);


  //43 → 47
  Serial.println("43->47");
  playa(chanphai, 90);
  playa(chanphaik, 90);
  delay(10);
  pwm.setPWM(taytraik, 0, xoay(0));
  delay(10);
  pwm.setPWM(tayphaik, 0, xoay(0));
  delay(10);
  pwm.setPWM(chantrai, 0, xoay(180 - 70));
  delay(10);
  for (int i = 0; i <= 4; i++) {
    pwm.setPWM(chantraik, 0, xoay(135));
    delay(200);
    pwm.setPWM(chantraik, 0, xoay(90));
    delay(200);
  }
  // 47 → 50
  Serial.println("47->50");
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(tayphai, 0, xoay(90));
    delay(150);
    pwm.setPWM(tayphaik, 0, xoay(0));
    delay(150);
    pwm.setPWM(tayphai, 0, xoay(45));
    delay(150);
    pwm.setPWM(tayphaik, 0, xoay(45));
    delay(150);
  }

  // 50 → 54
  Serial.println("50->54");
  for (int i = 0; i <= 90; i++) {
    pwm.setPWM(0, 0, xoay(i));
    pwm.setPWM(1, 0, xoay(90 - i));
    delay(10);
  }
  int time5057 = 0;
  while (time5057 <= 7) {
    for (int i = 90; i >= 0; i--) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(1, 0, xoay(90 - i));
      pwm.setPWM(4, 0, xoay(i + 90));
      pwm.setPWM(5, 0, xoay(180 - i));
      delay(10);
    }
    for (int i = 0; i <= 90; i++) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(1, 0, xoay(90 - i));
      pwm.setPWM(4, 0, xoay(i + 90));
      pwm.setPWM(5, 0, xoay(180 - i));
      delay(10);
    }
    time5057++;
  }
  time5057 = 0;
  for (int i = 90; i >= 0; i--) {
    pwm.setPWM(0, 0, xoay(i));
  }

  //54 → 58
  Serial.println("54->58");
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(than, 0, xoay(120));
    delay(20);
    pwm.setPWM(than, 0, xoay(40));
    delay(20);
  }
  pwm.setPWM(than, 0, xoay(90));
  delay(50);

  //58 → 1:01
  Serial.println("58->101");
  pwm.setPWM(tayphai, 0, xoay(90));
  delay(200);
  pwm.setPWM(tayphaik, 0, xoay(45));
  delay(200);
  pwm.setPWM(taytrai, 0, xoay(90));
  delay(200);
  pwm.setPWM(taytraik, 0, xoay(135));
  delay(200);
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(than, 0, xoay(120));
    delay(200);
    pwm.setPWM(than, 0, xoay(40));
    delay(200);
  }
  pwm.setPWM(than, 0, xoay(90));
  delay(50);

  //1:01 → 1:06
  Serial.println("101->106");
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chanphaik, 0, xoay(90));
  pwm.setPWM(chantrai, 0, xoay(90));
  pwm.setPWM(chantraik, 0, xoay(90));
  for (int i = 0; i <= 7; i++) {
    playa(chanphai, 180 - 125);
    playa(chanphaik, 90 + 180 - 125);
    delay(175);
    playa(chanphai, 90);
    playa(chanphaik, 90);
    delay(175);
    playa(chantrai, 90 + 45);
    playa(chantraik, 180 - (90 + 45));
    delay(175);
    playa(chantrai, 90);
    playa(chantraik, 90);
    delay(175);
  }
  int time = 20;
  //1:06 → 1:09
  Serial.println("106->109");
  playa(chanphai, (180 - 125));
  playa(chanphaik, (90 + (180 - 125)));
  playa(taytrai, xoay(90));
  playa(than, xoay((40)));
  delay(time);

  //1:09 → 1:15
  Serial.println("109->115");
  playa(taytrai, xoay((15)));
  playa(tayphai, xoay((15)));
  playa(taytraik, xoay((180)));
  playa(tayphaik, xoay((180)));
  for (int i = 0; i <= 7; i++) {
    playa(chantrai, 90);
    playa(chantraik, 90);
    delay(175);
    playa(than, 75);
    playa(taytrai, 0);
    playa(tayphai, 180 - 15);
    playa(chanphai, 180 - 125);
    playa(chanphaik, 90 + 180 - 125);
    delay(400);
    playa(chanphai, 90);
    playa(chanphaik, 90);
    playa(than, 90 + 45);
    playa(taytrai, 180 - 15);
    playa(tayphai, 15);
    playa(chantrai, 90 + 45);
    playa(chantraik, 180 - (90 + 45));
    delay(400);
  }
  // 1:15 → 1:30
  Serial.println("115->130");
  playa(taytrai, 90);
  for (int j = 0; j <= 5; j++) {
    delay(1420 / 3);
    playa(chanphai, 180 - 125);
    playa(chanphaik, 125);
    playa(chantrai, 125);
    playa(chantraik, 180 - 125 + 25);
    playa(taytraik, (90 + j * (180 - 90) / 5));
    delay(1420 / 3);
    playa(chanphai, 70);
    playa(chanphaik, 100);
    playa(chantrai, 100);
    playa(chantraik, 180 - 110);
    delay(1420 / 3);
  }
  //1:30 → 1:45
  Serial.println("130->145");
  playa(chanphai, 45);
  playa(chanphaik, 180 - 45);
  playa(chantrai, 180 - 45);
  playa(chantraik, 45);
  delay(500);
  for (int i = 180; i >= 0; i--) {
    playa(tayphai, i);
    playa(taytrai, 180 - i);
    playa(taytraik, i);
    playa(tayphaik, 180 - i);
    delay(76);
  }

  //1:45 → 1:48
  Serial.println("145->148");
  pwm.setPWM(chanphai, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(chanphaik, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(chantrai, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(chantraik, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(tayphaik, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(taytraik, 0, xoay(90));
  delay(950 / 3);
  pwm.setPWM(taytrai, 0, xoay(180));
  delay(950 / 3);
  pwm.setPWM(tayphai, 0, xoay(0));
  delay(950 / 3);
  pwm.setPWM(12, 0, xoay(90));
  delay(950 / 3);

  //1:48 → 1:52
  Serial.println("148->152");
  pwm.setPWM(taytrai, 0, xoay(0));
  delay(200);
  pwm.setPWM(taytraik, 0, xoay(180));
  for (int i = 0; i <= 10; i++) {
    pwm.setPWM(than, 0, xoay(90 + 45));
    delay(350);
    pwm.setPWM(than, 0, xoay(75));
    delay(350);
  }
  pwm.setPWM(than, 0, xoay(90));
  delay(200);

  //1:52 →1:55
  Serial.println("152->155");
  pwm.setPWM(than, 0, xoay(75));
  delay(800 / 2);
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(taytraik, 0, xoay(180 - 135));
    delay(250);
    pwm.setPWM(taytraik, 0, xoay(180));
    delay(250);
  }
  playa(chanphai, (180 - 125));
  playa(chanphaik, (90 + (180 - 125)));
  //1:55 →1:59
  Serial.println("155->159");
  pwm.setPWM(taytrai, 0, xoay(180 - 35));
  delay(500 / 2);
  pwm.setPWM(tayphai, 0, xoay(30));
  delay(500 / 2);
  pwm.setPWM(taytraik, 0, xoay(180));
  delay(500 / 2);
  pwm.setPWM(tayphaik, 0, xoay(180));
  delay(500 / 2);
  pwm.setPWM(chanphai, 0, xoay(180 - 135));
  delay(500 / 2);
  for (int i = 0; i <= 4; i++) {
    pwm.setPWM(chanphaik, 0, xoay(90 + 45));
    delay(500 / 2);
    pwm.setPWM(chanphaik, 0, xoay(90));
    delay(500 / 2);
  }
  pwm.setPWM(chanphai, 0, xoay(90));
  delay(700);

  //1:59 → 2:03
  Serial.println("159->203");
  playa(tayphai, xoay(0));
  playa(tayphaik, xoay(90));
  playa(taytrai, xoay(180));
  playa(taytraik, xoay(90));
  delay(time);

  //2:03 → 2:09
  Serial.println("203->209");
  playa(taytrai, 90);
  delay(450);
  for (int i = 1; i <= 7; i++) {
    for (int i = 90; i <= 180; i++) {
      playa(taytrai, i);
      playa(taytraik, i);
      delay(4.0);
    }
    for (int i = 180; i >= 90; i--) {
      playa(taytrai, i);
      playa(taytraik, i);
      delay(4.0);
    }
  }
  delay(300);

  //2:09 → 2:14
  Serial.println("209->214");
  playa(tayphai, xoay(0));
  playa(tayphaik, xoay(90));
  playa(taytrai, xoay(180));
  playa(taytraik, xoay(90));
  delay(2800);
  //2:11 -> 2:14
  for (int i = 1; i <= 4; i++) {
    playa(taytraik, 0);
    delay(750);
    playa(tayphaik, 180);
    delay(750);
    playa(taytraik, 180);
    delay(750);
    playa(tayphaik, 0);
    delay(750);
  }
  //2:14 → 2:19
  Serial.println("214->219");
  playa(taytrai, xoay(15));
  delay(time / 2);
  playa(tayphaik, xoay(0));
  delay(time / 2);
  for (int i = 90; i <= 180; i++) {
    playa(tayphai, i);
    delay(time / 2);
  }
  //2:19 → 2:23
  Serial.println("219->223");
  playa(taytrai, 90);
  delay(500);
  playa(tayphai, 0);
  playa(tayphaik, 90);
  for (int i = 0; i <= 4; i++) {
    playa(taytraik, 90);
    delay(250);
    playa(taytraik, 0);
    delay(250);
  }
  playa(taytraik, 90);

  //2:23 → 2:25
  Serial.println("223->225");
  playa(tayphai, xoay(0));
  playa(tayphaik, xoay(90));
  playa(taytrai, xoay(180));
  playa(taytraik, xoay(90));
  delay(2800);

  //2:25 → 2:30
  Serial.println("225->230");
  for (int i = 0; i <= 4; i++) {
    playa(tayphai, 45);
    delay(500);
    playa(tayphai, 135);
    delay(500);
  }

  //2:30 → 2:32
  Serial.println("230->232");
  playa(tayphai, xoay(0));
  playa(tayphaik, xoay(90));
  playa(taytrai, xoay(180));
  playa(taytraik, xoay(90));
  delay(1800);

  //2:33 → 2:36
  Serial.println("233->236");
  playa(chantrai, 125);
  delay(550);
  playa(chantraik, (180 - 125));
  delay(550);
  playa(than, xoay((40)));
  delay(550);
  playa(taytrai, xoay((90)));
  delay(550);
  playa(taytraik, xoay((0)));
  delay(550);
  //2:36 → 2:39
  Serial.println("236->239");
  playa(chantrai, (125));
  delay(550);
  playa(chantraik, (180 - 125));
  delay(550);
  playa(than, xoay((120)));
  delay(550);
  playa(tayphai, xoay((90)));
  delay(550);
  playa(tayphaik, xoay((0)));
  delay(550);

  //2:39 → 2:43
  Serial.println("239->243");
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      if (j % 2 == 1) {
        for (int k = 120; k <= 40; k--) {
          playa(than, k);
          delay(15);
        }
      } else {
        for (int k = 40; k <= 120; k++) {
          playa(than, k);
          delay(15);
        }
      }
    }
  }

  // 2:43 → 2:47
  Serial.println("243->247");
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(tayphai, 0, xoay(45));
    delay(20);
    pwm.setPWM(tayphaik, 0, xoay(135));
    delay(20);
    pwm.setPWM(taytrai, 0, xoay(45));
    delay(20);
    pwm.setPWM(taytraik, 0, xoay(135));
    delay(20);
  }

  // 2:47 → 3:00
  Serial.println("247->300");
  for (int i = 0; i <= 5; i++) {
    pwm.setPWM(than, 0, xoay(90 + 45));
    delay(350);
    pwm.setPWM(than, 0, xoay(75));
    delay(350);
  }
  pwm.setPWM(than, 0, xoay(90));
  delay(150);

  for (int i = 0; i <= 7; i++) {
    playa(chanphai, 180 - 125);
    playa(chanphaik, 90 + 180 - 125);
    delay(170 * 2);
    playa(chanphai, 90);
    playa(chanphaik, 90);
    delay(170 * 2);
    playa(chantrai, 90 + 45);
    playa(chantraik, 180 - (90 + 45));
    delay(170 * 2);
    playa(chantrai, 90);
    playa(chantraik, 90);
    delay(170 * 2);
  }
}
int xoay(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}
void playa(int pin, int goc) {
  pwm.setPWM(pin, 0, xoay(goc));
}