#include "M5AtomS3.h"
#include <Arduino.h>

#define SWITCH 1    //フットスイッチ
int state = 0;          //フットスイッチの状態定義
int duration_ms = 500.0; //フットスイッチの押し時間

unsigned long start_time; //計測開始時間
unsigned long current_time; //スイッチを押した時間
unsigned long elapsed_time_ms;//スイッチを押して続けてる時間

void setup() {
  M5.begin();
  Serial.begin(9600);                 //シリアル通信のボーレート設定(適宜変更)
  pinMode(SWITCH, INPUT_PULLDOWN);    //フットスイッチの入力設定：押したら入力


  AtomS3.Display.setTextColor(GREEN);                 //AtomS3に表示する文字の"色"
  AtomS3.Display.setTextDatum(middle_center);         //AtomS3に表示する文字の"位置"
  AtomS3.Display.setFont(&fonts::Orbitron_Light_24);  //AtomS3に表示する文字の"フォント"
  AtomS3.Display.setTextSize(1);                      //AtomS3に表示する文字の"サイズ"
}
void loop() {
  int SwitchState = digitalRead(SWITCH);    //フットスイッチのデジタルデータ読み取り

  //フットスイッチがOFFの場合
  if (SwitchState == 0) {
    AtomS3.Display.clear();   //AtomS3のディスプレイをクリア
    AtomS3.Display.drawString("Released", AtomS3.Display.width() / 2,
                                  AtomS3.Display.height() / 2);   //AtomS3のディスプレイに"Pressed"を表示
    start_time = millis();  //計測開始
    state = 0;    //フットスイッチの状態を変更
  }

  //フットスイッチがONの場合
  else if (SwitchState == 1) {
    current_time = millis();  //スイッチ計測開始
    elapsed_time_ms = (current_time - start_time);
    //Serial.print(elapsed_time_ms);
    //Serial.println("[ms]");

    if (elapsed_time_ms > duration_ms) {
      AtomS3.Display.clear();   //AtomS3のディスプレイをクリア
      AtomS3.Display.drawString("Pressed", AtomS3.Display.width() / 2,
                                  AtomS3.Display.height() / 2);   //AtomS3のディスプレイに"Pressed"を表示
      state = 1;    //フットスイッチの状態を変更
    }
  }
  Serial.println(state);    //シリアルモニタにフットスイッチの状態を表示
}