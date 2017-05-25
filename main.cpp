#include "mbed.h"

DigitalOut myled(LED1);    //待機時点灯(暗)
DigitalOut runled(LED2);    //動作中点灯

DigitalOut debug(LED4);

DigitalOut lamp(p23);       //ランプ,回転
PwmOut speed(p22);          //回転速度
DigitalOut volume(p24);     //音量（大小）
PwmOut speaker(p21);        //スピーカー出力
AnalogIn m_vol(p16);        //回転速度入力(12bit)
DigitalIn start(p30);       //スタートスイッチ

Timer maintime;           //タイマ初期化

void siren(double,int); //プロトタイプ宣言

int main() {
    start.mode(PullUp);   //スタートスイッチプルアップ
    while(1)
    {
        maintime.reset();     //タイマリセット
        runled = 0;
        lamp = 0;
        volume = 0;
        speaker.write(0);
        //周期設定(microsec)
        speaker.period_us(2024.3);    //し

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
            maintime.start();   //タイマスタート

            siren(0.25,10);
            siren(0.15,10);

            //三次動作（停止）
            runled = 0;     //LED消灯
            maintime.stop();     //タイマストップ
        }
    }
}

void siren(double inter,int length) //インターバルとサイレンの時間
{
    int starttime;  //サイレン開始時間
    int thistime=0;
    starttime=maintime.read();  //開始時間取得
    while(thistime-starttime<=length)
    {
        speaker.write(0.5);     //サイレンON(デューティ比0.5)
        speaker.period_us(2024.3);  //し
        wait(inter);
        speaker.period_us(2551.0);  //そ
        wait(inter);
        thistime=maintime.read();   //現在時間取得
    }
    speaker.write(0);   //サイレンOFF
}
