#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>
#include "USBPD_CUST_NVM_API.h"

#define NVM_SIZE  40

uint8_t old_nvm[NVM_SIZE];
uint8_t new_nvm[NVM_SIZE];

extern uint8_t Sector0[];
extern uint8_t Sector1[];
extern uint8_t Sector2[];
extern uint8_t Sector3[];
extern uint8_t Sector4[];

void setup() {
  M5.begin();
  Wire.begin();

  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  memcpy(&new_nvm[0],Sector0,8);
  memcpy(&new_nvm[8],Sector1,8);
  memcpy(&new_nvm[16],Sector2,8);
  memcpy(&new_nvm[24],Sector3,8);
  memcpy(&new_nvm[32],Sector4,8);

  nvm_read(old_nvm,NVM_SIZE);
  bool need_update = false;
  for (int i = 0;i < NVM_SIZE;i++) {
    if (old_nvm[i] != new_nvm[i]) need_update = true;
    M5.Lcd.printf("%02x ",old_nvm[i]);
    if (i % 8 == 7) M5.Lcd.println("");
  }

  if (need_update) {
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.println("Updating...");
    if (nvm_flash() == 0) {
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Success");
    } else {
      M5.Lcd.setTextColor(RED);
      M5.Lcd.println("Failure");
    }
  } else {
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println("Already updated");
  }
}

void loop() {
  delay(1000);
}