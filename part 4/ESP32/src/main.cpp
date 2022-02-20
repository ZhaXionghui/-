/*接线
 * SSD1309/OLED128X64---NODE MCU32/arduino iic
 * OLED VCC----------------3.3v
 * GND---------------------GND
 * OLED SCL----------------5
 * OLED SDA----------------18
 * Other-------------------NODE MCU32/arduino iic
 * buzzer--------------------19
 * BUTTON_A----------------12
 * BUTTON_B----------------14
 * BUTTON_C----------------27
 * BUTTON_D----------------26
 */


#include <Arduino.h>           // Arduino架构库
#include <U8g2lib.h>           // 基于Arduino架构的显示驱动库
#include <Button2.h>           // 基于Arduino架构的的多按钮驱动库
#include <EasyBuzzer.h>        // 基于Arduino架构的蜂鸣器动库
#include <WiFi.h>              // 基于Arduino架构的WIFI连接库
#include <WebSocketClient.h>   // 基于Arduino架构的Webscoket协议库

#ifdef U8X8_HAVE_HW_SPI        // SPI通讯
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define WIFI_SSID "1231123"   // 2.4G WiFi名称
#define WIFI_PASS "123123"  // 对应的WiFi密码
#define WEBSOCKET_SERVER "namotechnology.cn" //Websocket服务器域名/IP地址
#define WEBSOCKET_PORT 2333                  //Websocket服务器端口
#define WEBSOCKET_PATH "/"                   //Websocket方法路由

U8G2_SSD1309_128X64_NONAME2_2_SW_I2C u8g2(U8G2_R0, /* SCL=*/ 5, /* SDA=*/ 18, /* RST=*/ U8X8_PIN_NONE); // 显示屏对象定义

// 定义按键引脚
#define BUTTON_A_PIN 12
#define BUTTON_B_PIN 14
#define BUTTON_C_PIN 27
#define BUTTON_D_PIN 26

Button2 buttonA, buttonB, buttonC, buttonD; // 定义按键对象

WiFiClient client;// 定义WiFi连接对象
WebSocketsClient webSocket;// 定义websocket连接对象

int beep = 19 ; //定义蜂鸣器接口
String message = "欢迎使用求助机";// 初始化显示内容，后通过更改此值实时更新


// 二次封装WiFi连接函数
char connect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("等待连接WIFI");
  int timeout_s = 30;
  while (WiFi.status() != WL_CONNECTED && timeout_s-- > 0)
  {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("无法连接，请检查密码");
    message = "无法连接，请检查密码"；
    return 0;
  }
  else
  {
    Serial.println("WIFI连接成功！");
    message = "WIFI连接成功！"；
    Serial.print(WiFi.localIP());
    return 1;
  }
}


// 二次封装蜂鸣器函数
void buzzer(int time)
{
  if (time < 1)
    return;
  if (time == 1)
  {
    EasyBuzzer.singleBeep(
      1000, // Frequency in hertz(HZ).
      1000  // Duration of the beep in milliseconds(ms).
    );
  }
  else
  {
    EasyBuzzer.beep(
      1000, // Frequency in hertz(HZ).
      1000, // On Duration of the beep in milliseconds(ms).
      1000, // Off Duration of the beep in milliseconds(ms).
      time, // The number  of beeps per cycle.
      1000, // Pause duration.
      1     // The number of cycle.
    );
  }
}


// websocket事件逻辑定义
void webSocketEvent(WStype_t type, unit8_t * payload, size_t length)
{
  switch(type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("Websocket断开连接! \n");
      message = "服务器断开连接";
      buzzer(2);
      break;
    case WStype_CONNECTED:
      Serial.printf("Websocket已连接至路由: %s\n", payload);
      message = "服务器已连接";
      break;
    case WStype_TXT:
      Serial.printf("Websocket收到信息: %s\n", payload);
      message = String((const char*)payload);
      buzzer(1);
      break;
  }
}


// 按钮按下时，定义触发逻辑
void cilck(Buttton2 &btn)
{
  if (btn == buttonA)
  {
    Serial.println("按键A按下")；
    message = "我生病了"；
    buzzer(1);
    webSocket.sendTXT("我生病了");
  }
  if (btn == buttonB)
  {
    Serial.println("按键B按下")；
    message = "失火了"；
    buzzer(1);
    webSocket.sendTXT("失火了");
  }
  if (btn == buttonC)
  {
    Serial.println("按键C按下")；
    message = "电路故障"；
    buzzer(1);
    webSocket.sendTXT("电路故障");
  }
  if (btn == buttonD)
  {
    Serial.println("按键D按下")；
    message = "其他求助"；
    buzzer(1);
    webSocket.sendTXT("其他求助");
  }
  
}


void setup() 
{
  // 显示屏初始化
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontDirection(0);
  u8g2.setCursor(0, 15);
  u8g2.print(message);
  u8g2.sendBuffer();
  
  // 尝试连接WIFI
  connect();

  // 尝试连接服务器
  webSocket.begin(WEBSOCKET_SERVER, WEBSOCKET_PORT, WEBSOCKET_PATH);
  webSocket.setReconnectInterval(5000);
  webSocket.onEvent(webSocketEvent);

  // 蜂鸣器初始化
  EasyBuzzer.setPin(beep);
  buzzer(3);

  // 设置波特率为115200
  Serial.begin(115200);

  // 按键初始化
  buttonA.begin(BUTTON_A_PIN);
  buttonA.setClickHandler(click);
  buttonB.begin(BUTTON_B_PIN);
  buttonB.setClickHandler(click);
  buttonC.begin(BUTTON_C_PIN);
  buttonC.setClickHandler(click);
  buttonD.begin(BUTTON_D_PIN);
  buttonD.setClickHandler(click);
}

void loop() 
{
  // 显示屏实时显示消息
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(message);
  u8g2.sendBuffer();
  
  // 按键实时监测
  buttonA.loop();
  buttonB.loop();
  buttonC.loop();
  buttonD.loop();  

  // 蜂鸣器状态实时更新
  EasyBuzzer.update();

  // websocket状态实时检查
  webSocket.loop();
}