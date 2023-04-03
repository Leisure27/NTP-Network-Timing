#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "leisure";
const char *password = "shadow27";

const long utcOffsetInSeconds = 28800; // 时区偏移量（以秒为单位），3600*8，偏移8个小时
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup()
{
    Serial.begin(115200);
    delay(10);

    // 连接WiFi网络
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    timeClient.begin(); // 启动NTP客户端
}

void loop()
{

    timeClient.update(); // 更新NTP时间

    unsigned long epochTime = timeClient.getEpochTime(); // 获取当前时间
    // struct tm *currentTime = localtime((time_t *)&epochTime);
    struct tm *currentTime = gmtime((time_t *)&epochTime);
    // 打印当前时间
    Serial.print("Current time: ");
    Serial.print(currentTime->tm_year + 1900); // 存储的是自 1900 年以来经过的年数，因此需要加上 1900 才能得到当前年份
    Serial.print("/");
    Serial.print(currentTime->tm_mon + 1); // 由于 tm_mon 变量存储的是从 0 开始计数的月份数，因此需要加上 1 才能得到当前月份。
    Serial.print("/");
    Serial.print(currentTime->tm_mday);
    Serial.print(" ");
    Serial.print(currentTime->tm_hour);
    Serial.print(":");
    Serial.print(currentTime->tm_min);
    Serial.print(":");
    Serial.println(currentTime->tm_sec);

    delay(1000); // 等待1秒钟
}
