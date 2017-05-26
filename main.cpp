#include "mbed.h"

DigitalOut myled(LED1);    //待機時点灯(暗)
DigitalOut runled(LED2);    //動作中点灯
DigitalOut debug(LED4);

DigitalOut lamp(p23);       //ランプ,回転
PwmOut speed(p22);          //回転速度
DigitalOut volume(p24);     //音量（大小）
DigitalOut speaker(p21);    //スピーカー出力
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
            speed.period_us(60);    //回転周期設定
            //一次動作（開始）
            lamp = 1;       //回転灯動作開始
            speed.write(0.5);   //回転速度
            siren(0.25,10);

            //二次動作（加速）
            speed.write(1.0);
            siren(0.15,10);


            //三次動作（停止）
            lamp = 0;       //回転灯停止
            speed.write(0);
            runled = 0;     //LED消灯
            maintime.stop();     //タイマストップ
        }
    }
}

//サイレン鳴らす関数
void siren(double inter,int length) //インターバルとサイレンの時間
{
    int starttime;  //サイレン開始時間
    int thistime=0;
    starttime=maintime.read();  //開始時間取得
    while(thistime-starttime<=length)
    {
        int loop_shi,loop_so; //それぞれの繰り返し回数
        loop_shi = static_cast<int>(inter/0.0020243);
        loop_so  = static_cast<int>(inter/0.002551);
        for (int i=0;i<=loop_shi;i++) //し
        {
          speaker = 1;
          wait_us(1012.2);
          speaker = 0;
          wait_us(1012.2);
        }
        for (int i=0;i<=loop_so;i++)  //そ
        {
          speaker = 1;
          wait_us(1275.5);
          speaker = 0;
          wait_us(1275.5);
        }
        thistime=maintime.read();   //現在時間取得
    }
    speaker=0;   //サイレンOFF
}
