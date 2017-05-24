#include "mbed.h"

DigitalOut myled(LED1);    //待機時点灯(暗)
DigitalOut runled(LED2);    //動作中点灯

DigitalOut debug(LED4);

DigitalOut lamp(p23);       //ランプ,回転
PwmOut speed(p22);          //回転速度
DigitalOut volume(p24);     //音量（大小）
PwmOut speaker(p21);     //スピーカー出力
AnalogIn m_vol(p16);        //回転速度入力(12bit)
DigitalIn start(p30);       //スタートスイッチ

Timer maintime;           //タイマ初期化
//float moter = 0;
int thistime = 0;

int main() {
    start.mode(PullUp);   //スタートスイッチプルアップ
    while(1)
    {
        maintime.reset();     //タイマリセット
        thistime = 0;   //こっちもリセット
        runled = 0;
        lamp = 0;
        volume = 0;

        runled=0;       //スタート待機
        debug=0;
        myled=1;        //待機中点灯（暗）
        wait(0.01);
        myled=0;
        wait(0.01);

        if(start == 1)
        {
            //以下メイン動作
            //一次動作（開始）
            runled = 1;     //LED点灯
            wait(1.0);
            //maintime.start();   //タイマスタート
            speed.period_us(60);    //周期設定

            lamp = 1;       //回転灯動作開始
            speed.write(0.5);   //回転速度

            //待機その一
            wait(5.0);

            //二次動作（加速）
            speed.write(1.0);

            //待機その二
            wait(5.0);


            //三次動作（停止）
            lamp = 0;
            speed.write(0);
            runled = 0;
            //maintime.stop();
        }
    }
}
