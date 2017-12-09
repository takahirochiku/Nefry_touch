#include <Nefry.h>
#include <NefryIFTTT.h>
String Event, SecretKey;

void setup() {
  Nefry.setStoreTitle("SecretKey",0); //Nefry DataStoreのタイトルを指定
  Nefry.setStoreTitle("Event",1);     //Nefry DataStoreのタイトルを指定
  SecretKey = Nefry.getStoreStr(0);   //Nefry DataStoreからデータを取得
  Event = Nefry.getStoreStr(1);       //Nefry DataStoreからデータを取得
  Nefry.println("Nefry Setup!!");

  pinMode(A2,INPUT_PULLUP);//入力モード切り替え
}

void loop() {
  if(digitalRead(A2)==HIGH) {               //センサーが静電気を検知した時
    bool sendData = IFTTT.send(Event, SecretKey,"Nefry",(String)(micros()/1000000)+"秒");//IFTTTにデータを送信
                                      //Value1:Nefry,Value2:Nefryが起動してからの秒数,Value3:送信カウンタ
     Nefry.println("A2 HIGH");
    if (!sendData) {//IFTTTにデータを送信が成功したか失敗したかの判定
      Nefry.setLed(255, 0, 0);        //Errの時、赤色点灯
    }
    Nefry.ndelay(1000);               //送信後1秒間待つ
  }
}
