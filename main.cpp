#include "mbed.h"

DigitalOut myled(LED1);
DigitalOut runled(LED2);    //動作中点灯
DigitalOut lamp(p23);       //ランプ,回転
PwmOut speed(p22);          //回転速度
DigitalOut volume(p24);     //音量（大小）
AnalogOut speaker(p21);     //スピーカー出力
AnalogIn m_vol(p16);        //回転速度入力
DigitalIn start(p30);       //スタートスイッチ

int main() {
  start.mode(PullUp);   //プルアップ
    while(1) {
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
    }
}
