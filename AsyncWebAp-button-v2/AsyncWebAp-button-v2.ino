#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "Stepper_28BYJ_48.h"

#include "html.h"

#define LED_BUILTIN 25 
const char *ssid = "MyESP32AP";
const char *password = "";
const char* PARAM_DIR_1 = "output";
const char* PARAM_DIR_2 = "state";
const char* PARAM_SLIDER = "value";

int dir=1;
 
AsyncWebServer server(80);
Stepper_28BYJ_48 stepper(26,27,14,12);
 
void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
 
  WiFi.softAP(ssid);
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_DIR_1) && request->hasParam(PARAM_DIR_2)) {
      inputMessage1 = request->getParam(PARAM_DIR_1)->value();
      inputMessage2 = request->getParam(PARAM_DIR_2)->value();
      digitalWrite(LED_BUILTIN, inputMessage2.toInt());
      if (inputMessage2.toInt()){
        dir=1;
      } else dir=-1;

    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("LED: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });  

server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_SLIDER)) {
      sliderValue = request->getParam(PARAM_SLIDER)->value();
      //sliderValue = inputMessage;
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
 
  server.begin();
}
 
void loop(){
  stepper.step(dir);
  delayMicroseconds(map(sliderValue.toInt(), 0, 255, 50, 00)*1000);}
