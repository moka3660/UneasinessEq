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
        speaker.write(0);

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
            speaker.period_us(3816.7);  //周期設定(microsec) ど
            speaker.write(0.5);   //デューティ比0.5
            wait(0.2);
            speaker.period_us(3401.4);    //れ
            wait(0.2);
            speaker.period_us(3030.3);    //み
            wait(0.2);
            speaker.period_us(2865.3);    //ふぁ
            wait(0.2);
            speaker.period_us(2551.0);    //そ
            wait(0.2);
            speaker.period_us(2272.7);    //ら
            wait(0.2);
            speaker.period_us(2024.3);    //し
            wait(0.2);
            speaker.period_us(1912.0);    //ど
            wait(0.2);          

            //三次動作（停止）
            speaker.write(0);
            runled = 0;
            //maintime.stop();
        }
    }
}
