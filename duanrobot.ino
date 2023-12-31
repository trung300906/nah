#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 125
#define SERVOMAX 575
int cambienanalog = A0;
unsigned long elapsedTime;
unsigned long lastChangeTime = 0;
int tayphai = 0, tayphaik = 1, taytrai = 4, taytraik = 5, chanphai = 2, chanphaik = 3, chantrai = 6, chantraik = 7, dau = 8;
int dem1 = 0, dem2 = 0, artifact = 0, demdt = 0, randdt;
void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);
  Wire.setClock(400000);
  Serial.begin(31250);
  pinMode(cambienanalog, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
void loop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  int giatri = 0;
  int newGiatri = analogRead(cambienanalog);  // đọc giá trị analog của cảm biến
  int val = digitalRead(2);                   // đọc giá trị digital của cảm biến
  randdt = random(1, 5);
  if (val == 0 && randdt != artifact) {  // xét điều kiện của giá trị input có thỏa hay không, đồng thời loại các trường hợp random độngtacs trùng nhau
    artifact = randdt;
    if (dem1 == 0) {
      int led = random(3, 4);  // random số chân led mà sẽ sáng
      digitalWrite(led, HIGH);
      if (led == 3) {
        digitalWrite(4, HIGH);
      } else if (led == 4) {
        digitalWrite(3, HIGH);
      }
      chao(dem1);
    }
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    if (newGiatri != giatri) {
      giatri = newGiatri;                          // thay giá trị của của biến giá trị tại chân analog
      unsigned long currentTime = millis();        // tính ra thời gian hiện tại dưới dạng số
      elapsedTime = currentTime - lastChangeTime;  // tính ra khoảng thời gian thay dổi thời gian
      lastChangeTime = currentTime;                // lấy dấu thời gian trước
    }
    logic(randdt, elapsedTime, demdt);
  } else if (dem2 == 0 && val == 1) {
    nhaykethuc(dem2);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(3000);
  }
}
void logic(int randdt, int timedelay, int demdt) {
  int randchan;
  switch (randdt) {
    case 1:
      dongtacchan1(timedelay, demdt);
      randchan = random(1, 5);
      logic2(randchan, timedelay, demdt);
      break;
    case 2:
      dongtacchan2(timedelay, demdt);
      randchan = random(1, 5);
      logic2(randchan, timedelay, demdt);
      break;
    case 3:
      dongtacchan3(timedelay, demdt);
      randchan = random(1, 5);
      logic2(randchan, timedelay, demdt);
      break;
    case 4:
      dongtacchan4(timedelay);
      randchan = random(1, 5);
      logic2(randchan, timedelay, demdt);
      break;
    case 5:
      dongtacchan5(timedelay);
      randchan = random(1, 5);
      logic2(randchan, timedelay, demdt);
      break;
    default:
      break;
  }
}
void logic2(int randchan, int timedelay, int demdt) {
  switch (randchan) {
    case 1:
      dongtactay1(timedelay, demdt);
      break;
    case 2:
      dongtactay2(timedelay, demdt);
      break;
    case 3:
      dongtactay3(timedelay, demdt);
      break;
    case 4:
      dongtactay4(timedelay, demdt);
      break;
    case 5:
      dongtactay5(timedelay, demdt);
      break;
    default:
      break;
  }
}
void dongtactay1(int time, int &demdt) {
  for (int i = 0; i <= 180; i++) {
    pwm.setPWM(tayphai, 0, xoay(i));
    delay(time + 10);
    pwm.setPWM(taytrai, 0, xoay(180 - i));
    delay(time + 10);
  }
  pwm.setPWM(1, 0, xoay(90));
  pwm.setPWM(5, 0, xoay(90));
  for (int i = 90; i <= 135; i++) {
    pwm.setPWM(1, 0, xoay(i));
    pwm.setPWM(5, 0, xoay(i));
    delay(time + 10);
  }
  demdt = 0;
  while (demdt <= 5) {
    for (int i = 135; i >= 45; i--) {
      pwm.setPWM(1, 0, xoay(i));
      pwm.setPWM(5, 0, xoay(i));
      delay(time + 10);
    }
    for (int i = 45; i <= 135; i++) {
      pwm.setPWM(1, 0, xoay(i));
      pwm.setPWM(5, 0, xoay(i));
      delay(time + 10);
    }
    demdt++;
  }
  delay(time + 16);
  for (int i = 135; i >= 90; i--) {
    pwm.setPWM(1, 0, xoay(i));
    pwm.setPWM(5, 0, xoay(i));
  }
  delay(time + 15);
}
void dongtactay2(int time, int &demdt) {
  for (int i = 0; i <= 180; i++) {
    pwm.setPWM(0, 0, xoay(i));
    delay(time + 15);
  }
  demdt = 0;
  while (demdt <= 5) {
    for (int i = 180; i >= 0; i--) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(4, 0, xoay(i));
      delay(time + 15);
    }
    for (int i = 0; i <= 180; i++) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(4, 0, xoay(i));
      delay(time + 15);
    }
    demdt++;
  }
  delay(time + 15);
  for (int i = 180; i >= 0; i--) {
    pwm.setPWM(0, 0, xoay(i));
    delay(time + 15);
  }
}
void dongtactay3(int time, int &demdt) {
  for (int i = 0; i <= 90; i++) {
    pwm.setPWM(0, 0, xoay(i));
    pwm.setPWM(1, 0, xoay(90 - i));
    delay(time + 10);
  }
  demdt = 0;
  while (demdt <= 7) {
    for (int i = 90; i >= 0; i--) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(1, 0, xoay(90 - i));
      pwm.setPWM(4, 0, xoay(i + 90));
      pwm.setPWM(5, 0, xoay(180 - i));
      delay(time + 10);
    }
    for (int i = 0; i <= 90; i++) {
      pwm.setPWM(0, 0, xoay(i));
      pwm.setPWM(1, 0, xoay(90 - i));
      pwm.setPWM(4, 0, xoay(i + 90));
      pwm.setPWM(5, 0, xoay(180 - i));
      delay(time + 10);
    }
    demdt++;
  }
  for (int i = 90; i >= 0; i--) {
    pwm.setPWM(0, 0, xoay(i));
  }
}
void dongtactay4(int time, int &demdt) {
  demdt = 0;
  for (int i = 0; i <= 40; i++) {
    pwm.setPWM(0, 0, xoay(i));
    pwm.setPWM(4, 0, xoay(180 - i));
    delay(time+0.725);
  }
  for (int i = 90; i <= 135; i++) {
    pwm.setPWM(1, 0, xoay(i));
    pwm.setPWM(5, 0, xoay(i));
  }
  delay(time);
  while (demdt <= 7) {
    if (demdt == 4 || demdt == 7) {
      for (int i = 40; i <= 90; i++) {
        pwm.setPWM(0, 0, xoay(i));
        pwm.setPWM(4, 0, xoay(180 - i));
        delay(time+0.725);
      }
    }
    for (int i = 135; i >= 45; i--) {
      pwm.setPWM(1, 0, xoay(i));
      pwm.setPWM(5, 0, xoay(i));
      delay(time+0.725);
    }
    for (int i = 45; i <= 135; i++) {
      pwm.setPWM(1, 0, xoay(i));
      pwm.setPWM(5, 0, xoay(i));
      delay(time+0.725);
    }
    if (demdt == 4 || demdt == 7) {
      for (int i = 90; i >= 40; i--) {
        pwm.setPWM(0, 0, xoay(i));
        pwm.setPWM(4, 0, xoay(180 - i));
        delay(time+0.725);
      }
    }
    demdt++;
  }
}
void dongtactay5(int time, int &demdt) {
  demdt = 0;
  while (demdt <= 10) {
    if (demdt <= 3) {
      for (int i = 0; i <= 180; i++) {
        pwm.setPWM(tayphai, 0, xoay(i));
        pwm.setPWM(taytrai, 0, xoay(180 - i));
        delay(16);
      }
      for (int i = 180; i >= 0; i--) {
        pwm.setPWM(tayphai, 0, xoay(i));
        pwm.setPWM(taytrai, 0, xoay(180 - i));
        delay(16);
      }
    } else if (demdt > 3 && demdt <= 6) {
      if (demdt == 4) {
        for (int i = 90; i >= 0; i--) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(i));
          delay(16);
        }
      } else {
        for (int i = 0; i <= 180; i++) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(i));
          delay(16);
        }
        for (int i = 180; i >= 0; i--) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(i));
          delay(16);
        }
      }
    } else if (demdt > 6 && demdt <= 8) {
      if (demdt == 7) {
        for (int i = 90; i <= 180; i++) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(90 - (i - 90)));
          delay(16);
        }
      } else {
        for (int i = 180; i >= 90; i--) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(90 - (i - 90)));
          delay(16);
        }
        for (int i = 90; i <= 180; i++) {
          pwm.setPWM(tayphaik, 0, xoay(i));
          pwm.setPWM(taytraik, 0, xoay(90 - (i - 90)));
          delay(16);
        }
      }
      for (int i = 180; i >= 90; i--) {
        pwm.setPWM(tayphaik, 0, xoay(i));
        pwm.setPWM(taytraik, 0, xoay(90 - (i - 90)));
        delay(16);
      }
    } else if (demdt > 8 && demdt <= 10) {
      if (demdt == 9) {
        for (int i = 0; i <= 90; i++) {
          pwm.setPWM(tayphai, 0, xoay(i));
          pwm.setPWM(taytrai, 0, xoay(180 - i));
          pwm.setPWM(tayphaik, 0, xoay(90 - i));
          delay(16);
        }
      } else {
        for (int i = 90; i >= 0; i--) {
          pwm.setPWM(tayphai, 0, xoay(i));
          pwm.setPWM(taytrai, 0, xoay(180 - i));
          pwm.setPWM(taytraik, 0, xoay(90 - i));
          delay(16);
        }
        for (int i = 0; i <= 90; i++) {
          pwm.setPWM(tayphai, 0, xoay(i));
          pwm.setPWM(taytrai, 0, xoay(180 - i));
          pwm.setPWM(tayphaik, 0, xoay(90 - i));
          delay(16);
        }
      }
    }
    demdt++;
  }
}
void dongtacchan1(int time, int &demdt) {
  demdt = 0;
  while (demdt <= 8) {
    for (int i = 90; i <= 135; i++) {
      pwm.setPWM(chanphai, 0, xoay(i));
      pwm.setPWM(chanphaik, 0, xoay(180 - i));
      delay(10);
    }
    for (int i = 135; i >= 90; i--) {
      pwm.setPWM(chanphai, 0, xoay(i));
      pwm.setPWM(chanphaik, 0, xoay(180 - i));
      delay(10);
    }
    for (int i = 90; i >= 45; i--) {
      pwm.setPWM(chantrai, 0, xoay(i));
      pwm.setPWM(chantraik, 0, xoay(180 - i));
      delay(10);
    }
    for (int i = 45; i <= 90; i++) {
      pwm.setPWM(chantrai, 0, xoay(i));
      pwm.setPWM(chantraik, 0, xoay(180 - i));
      delay(10);
    }
  }
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chanphaik, 0, xoay(90));
  delay(30);
  pwm.setPWM(chantrai, 0, xoay(90));
  pwm.setPWM(chantraik, 0, xoay(90));
}
void dongtacchan2(int time, int &demdt) {
  for (int i = 90; i <= 125; i++) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chantrai, 0, xoay(180 - i));
    delay(time + 16);
  }
  delay(time + 20);
  for (int i = 0; i <= 100; i++) {
    for (int j = 90; j <= 105; j++) {
      pwm.setPWM(chantraik, 0, xoay(j));
      delay(time + 20);
    }
    delay(300);
    for (int j = 105; j >= 90; j--) {
      pwm.setPWM(chantraik, 0, xoay(j));
      delay(time + 20);
    }
    delay(300);
  }
  delay(1000);
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chantrai, 0, xoay(90));
}
void dongtacchan3(int time, int &demdt) {
  for (int i = 90; i <= 125; i++) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chantrai, 0, xoay(180 - i));
    delay(time + 16);
  }
  delay(time + 20);
  for (int i = 0; i <= 100; i++) {
    for (int j = 90; j <= 105; j++) {
      pwm.setPWM(chantraik, 0, xoay(j));
      delay(time + 20);
    }
    delay(300);
    for (int j = 105; j >= 90; j--) {
      pwm.setPWM(chantraik, 0, xoay(j));
      delay(time + 20);
    }
    delay(time + 300);
  }
  delay(1000);
  pwm.setPWM(chanphai, 0, xoay(90));
  pwm.setPWM(chantrai, 0, xoay(90));
}
void dongtacchan4(int time) {
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chanphaik, 0, xoay(180 - i));
    delay(time + 16);
  }
  for (int i = 90 + 45; i >= 90; i--) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chanphaik, 0, xoay(180 - i));
    delay(time + 16);
  }
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(chantrai, 0, xoay(i));
    pwm.setPWM(chantraik, 0, xoay(180 - i));
    delay(time + 16);
  }
  for (int i = 90 + 45; i >= 90; i--) {
    pwm.setPWM(chantrai, 0, xoay(i));
    pwm.setPWM(chantraik, 0, xoay(180 - i));
    delay(time + 16);
  }
}
void dongtacchan5(int time) {
  
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chanphaik, 0, xoay(180 - i));
    delay(time + 16);
  }
  for (int i = 90 + 45; i >= 90; i--) {
    pwm.setPWM(chanphai, 0, xoay(i));
    pwm.setPWM(chanphaik, 0, xoay(180 - i));
    delay(time + 16);
  }
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(chantrai, 0, xoay(180 - i));
    pwm.setPWM(chantraik, 0, xoay(i));
    delay(time + 16);
  }
  for (int i = 90 + 45; i >= 90; i--) {
    pwm.setPWM(chantrai, 0, xoay(180 - i));
    pwm.setPWM(chantraik, 0, xoay(i));
    delay(time + 16);
  }
}
void chao(int &dem1) {
  Serial.println("thực hiện động tác chào");
  for (int i = 0; i <= 90; i++) {
    pwm.setPWM(tayphai, 0, xoay(i));
    delay(15);
  }
  for (int i = 90; i <= 90 + 45; i++) {
    pwm.setPWM(tayphaik, 0, xoay(i));
    delay(15);
  }
  for (int i = 90 + 45; i >= 45; i--) {
    pwm.setPWM(tayphaik, 0, xoay(i));
    delay(15);
  }
  for (int i = 0; i <= 4; i++) {
    for (int j = 45; j <= 135; j++) {
      pwm.setPWM(tayphaik, 0, xoay(j));
      delay(6);
    }
    for (int j = 135; j >= 45; j--) {
      pwm.setPWM(tayphaik, 0, xoay(j));
      delay(6);
    }
  }
  for (int i = 45; i <= 90; i++) {
    pwm.setPWM(tayphaik, 0, xoay(i));
    delay(15);
  }
  for (int i = 90; i >= 0; i--) {
    pwm.setPWM(tayphai, 0, xoay(i));
    delay(15);
  }
  delay(15);
  dem1++;
}
void nhaykethuc(int &dem2) {
  Serial.println("thực hiện động tác kết thúc");
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
int xoay(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}