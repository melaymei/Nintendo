#include "Nintendo.h"
/* 使用了Nicohood的库
*/
//定义手柄发送信号
CGamecubeConsole GamecubeConsole(3);      //定义给主机发送信号的针脚为3
Gamecube_Data_t d = defaultGamecubeData;   //要发送到主机的数据的结构

//命令必须，虚构一个手柄针脚在7，并不需要连接一个真实手柄
CGamecubeController GamecubeController1(7);

//定义数据按键的针脚 
const int A = 0;
const int B = 1;
const int X = 2;
const int Y = 4;
const int Z = 5;
const int START = 6;
const int R = 8;
const int L = 9;
const int DUP = 10;
const int DDOWN = 14;
const int DLEFT = 15;
const int DRIGHT = 16;

//right left扳机模拟中心值，不接按键，如果不工作74加1尝试，本程序不发送扳机模拟数据
const int RLIGHTv = 74;
const int RLIGHT = 36; //doesnt exist

//左右摇杆
int X1 = A0;//左摇杆X
int Y1 = A1;//左摇杆Y
int X2 = A2;//右摇杆X
int Y2 = A3;//右摇杆Y
//int LEFT = A3;//左扳机未启用
//int RIGHT = A3;//右扳机未启用

void setup()
{
  //输入引脚默认为上拉，当同地连接时确认按键动作，一共12个数字按键
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  
  pinMode(R, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  pinMode(RLIGHT, INPUT_PULLUP);//左右扳机中心值 仅用于不启用扳机模拟

  pinMode(DUP, INPUT_PULLUP);
  pinMode(DDOWN, INPUT_PULLUP);
  pinMode(DLEFT, INPUT_PULLUP);
  pinMode(DRIGHT, INPUT_PULLUP);

  //This is needed to run the code.
  GamecubeController1.read();
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinY = 0;
  int pinZ = 0;
  int pinSTART = 0;
  int pinR = 0;
  int pinL = 0;
  int pinRLIGHT = 0;
  int pinDUP = 0;
  int pinDDOWN = 0;
  int pinDLEFT = 0;
  int pinDRIGHT = 0;

//  int pinLEFT = 0;
//  int pinRIGHT = 0;
//  int pinUP = 0;
//  int pinDOWN = 0;

//  int pinX1 = 0;
//  int pinX2 = 0;
//  int pinY1 = 0;
//  int pinY2 = 0;

//  int pinCLEFT = 0;
//  int pinCRIGHT = 0;
//  int pinCUP = 0;
//  int pinCDOWN = 0;

  int pinxAxisC = analogRead(X2);
  int pinyAyisC = analogRead(Y2);
  
  int pinxAxis = analogRead(X1);
//  int xmod = 0;
  int pinyAyis = analogRead(Y1);
   
//  if (digitalRead(A) == LOW)pinxAxis = analogRead(X1)/4; //左摇杆X轴 将读取到的模拟0-1024转化为0-256
//  if (digitalRead(A) == LOW)pinxAyis = analogRead(Y1)/4; //左摇杆Y轴
//  if (digitalRead(A) == LOW)pinyAxisC = analogRead(X2)/4; //右摇杆X轴
//  if (digitalRead(A) == LOW)pinyAyisC = analogRead(Y2)/4; //右摇杆Y轴
  
  if (digitalRead(A) == LOW)pinA = 1;//反馈数字信号数据0/1
  if (digitalRead(B) == LOW)pinB = 1;
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Y) == LOW)pinY = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;
  if (digitalRead(RLIGHT) == LOW)pinRLIGHT = RLIGHTv;
  if (digitalRead(R) == LOW)pinR = 1;
  if (digitalRead(L) == LOW)pinL = 1;
  if (digitalRead(DUP) == LOW)pinDUP = 1;
  if (digitalRead(DDOWN) == LOW)pinDDOWN = 1;
  if (digitalRead(DLEFT) == LOW)pinDLEFT = 1;
  if (digitalRead(DRIGHT) == LOW)pinDRIGHT = 1;


  //发送到主机
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.y = pinY;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.r = pinR;
  d.report.l = pinL;
  d.report.left = pinRLIGHT;
  d.report.dup = pinDUP;
  d.report.ddown = pinDDOWN;
  d.report.dleft = pinDLEFT;
  d.report.dright = pinDRIGHT;
  d.report.xAxis = pinxAxis/4;//左摇杆X轴 将读取到的模拟0-1024转化为0-256
  d.report.yAxis = pinyAyis/4;
  d.report.cxAxis = pinxAxisC/4;
  d.report.cyAxis = pinyAyisC/4;
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);


}
