#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <Arduino_JSON.h>

ESP8266WiFiMulti WiFiMulti;

int year, month, date, hour, minute, second;

void get_time_from_json (String input)
{
  JSONVar myObject = JSON.parse(input);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  if (myObject.hasOwnProperty("sysTime1")) {
//    Serial.print("myObject[\"sysTime1\"] = ");

//    Serial.println((const char*) myObject["sysTime1"]);
    const char* time_str = (const char*) myObject["sysTime1"];
    char str_buf[3];
    str_buf[2] = '\0';
    str_buf[0] = time_str[2];
    str_buf[1] = time_str[3];
    year = String(str_buf).toInt();
    
    str_buf[0] = time_str[4];
    str_buf[1] = time_str[5];
    month = String(str_buf).toInt();
    
    str_buf[0] = time_str[6];
    str_buf[1] = time_str[7];
    date = String(str_buf).toInt();
    
    str_buf[0] = time_str[8];
    str_buf[1] = time_str[9];
    hour = String(str_buf).toInt();
    
    str_buf[0] = time_str[10];
    str_buf[1] = time_str[11];
    minute = String(str_buf).toInt();
    
    str_buf[0] = time_str[12];
    str_buf[1] = time_str[13];
    second = String(str_buf).toInt();

    Serial.write(year);
    Serial.write(month);
    Serial.write(date);
    Serial.write(hour);
    Serial.write(minute);
    Serial.write(second);
  }
}

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
//    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("geekzjk", "123456788");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    //    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://quan.suning.com/getSysTime.do")) {  // HTTP


      //      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        //        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
//          Serial.println(payload);
          get_time_from_json(payload);
        }
      } else {
        //        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      //      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(5000);
}
