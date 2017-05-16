#include "mbed.h"

#define runtime1 20;    //sec
#define runtime2 10;    //sec

DigitalOut myled(LED1);
DigitalOut runled(LED2);    //動作中点灯
DigitalOut lamp(p23);       //ランプ,回転
PwmOut speed(p22);          //回転速度
DigitalOut volume(p24);     //音量（大小）
AnalogOut speaker(p21);     //スピーカー出力
AnalogIn m_vol(p16);        //回転速度入力(12bit)
DigitalIn start(p30);       //スタートスイッチ

Timer maintime;           //タイマ初期化

//float moter = 0;
int thistime = 0;

int main()
{
  start.mode(PullUp);   //スタートスイッチプルアップ
  while(1)
  {
    maintime.reset();     //タイマリセット
    thistime = 0;   //こっちもリセット
    runled = 0;
    lamp = 0;
    volume = 0;

    while(start == 0)  //入力待ち
    {
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
        if(start == 1)
          break;
    }

    //以下メイン動作
    //一次動作(開始)
    maintime.start();   //タイマスタート
    runled = 1;     //LED点灯
    speed.period(0.000005);   //周期設定
    /*  回転速度　入力に対応   */
    lamp = 1;     //回転灯動作開始
    speed.write(0.5);     //回転速度
    /*   警報器スタート  */

    //runtime1待機
    while (thistime <= runtime1)
    {
      thistime = maintime.read(); //時間取得
    }

    //二次動作(加速)
    speed.write(1.0);     //回転速度はやく
    volume = 1;     //音量大きく

    //runtime2待機
    while (thistime <= (runtime1 + runtime2))
    {
      thistime = maintime.read(); //時間取得
    }

    //三次動作(停止)
    lamp = 0;   //回転灯停止
    speed.write(0); //pwm停止
    /*  警報機ストップ  */
    runled = 0;
    maintime.stop();
  }
}
