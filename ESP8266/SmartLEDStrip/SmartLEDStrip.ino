#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smartledstrip.firebaseio.com"
#define FIREBASE_AUTH "MhrQ0tsyktgVcb3U2EKwaCpKxoTUqvz4Ky7lULqG"
#define WIFI_SSID "ZTE1123581321"
#define WIFI_PASSWORD "atulkrishnajiapte9422310296"

#define  key24  true
#define key44  false


#if key24
#define IR_BPLUS  0xF700FF  // 
#define IR_BMINUS 0xF7807F  // 
#define IR_OFF    0xF740BF  // 
#define IR_ON     0xF7C03F  // 
#define IR_R    0xF720DF  // 
#define IR_G    0xF7A05F  // 
#define IR_B    0xF7609F  // 
#define IR_W    0xF7E01F  // 
#define IR_R1   0xF710EF  // 
#define IR_G1   0xF7906F  // 
#define IR_B1   0xF750AF  // 
#define IR_FLASH  0xF7D02F  // 
#define IR_R2   0xF730CF  // 
#define IR_G2   0xF7B04F  // 
#define IR_B2   0xF7708F  // 
#define IR_STROBE 0xF7F00F  // 
#define IR_R3   0xF708F7  // 
#define IR_G3   0xF78877  // 
#define IR_B3   0xF748B7  // 
#define IR_FADE   0xF7C837  // 
#define IR_R4    0xF728D7  // 
#define IR_G4    0xF7A857  // 
#define IR_B4    0xF76897  // 
#define IR_SMOOTH 0xF7E817  // 
#endif

#if key44
#define IR_BPlus  0xFF3AC5  // 
#define IR_BMinus 0xFFBA45  // 
#define IR_ON     0xFF827D  // 
#define IR_OFF    0xFF02FD  // 
#define IR_R    0xFF1AE5  // 
#define IR_G    0xFF9A65  // 
#define IR_B      0xFFA25D  // 
#define IR_W    0xFF22DD  // 
#define IR_B1   0xFF2AD5  // 
#define IR_B2   0xFFAA55  // 
#define IR_B3   0xFF926D  // 
#define IR_B4   0xFF12ED  // 
#define IR_B5   0xFF0AF5  // 
#define IR_B6   0xFF8A75  // 
#define IR_B7   0xFFB24D  // 
#define IR_B8   0xFF32CD  // 
#define IR_B9   0xFF38C7  // 
#define IR_B10    0xFFB847  // 
#define IR_B11    0xFF7887  // 
#define IR_B12    0xFFF807  // 
#define IR_B13    0xFF18E7  // 
#define IR_B14    0xFF9867  // 
#define IR_B15    0xFF58A7  // 
#define IR_B16    0xFFD827  // 
#define IR_UPR    0xFF28D7  // 
#define IR_UPG    0xFFA857  // 
#define IR_UPB    0xFF6897  // 
#define IR_QUICK  0xFFE817  // 
#define IR_DOWNR  0xFF08F7  // 
#define IR_DOWNG  0xFF8877  // 
#define IR_DOWNB  0xFF48B7  // 
#define IR_SLOW   0xFFC837  // 
#define IR_DIY1   0xFF30CF  // 
#define IR_DIY2   0xFFB04F  // 
#define IR_DIY3   0xFF708F  // 
#define IR_AUTO   0xFFF00F  // 
#define IR_DIY4   0xFF10EF  // 
#define IR_DIY5   0xFF906F  // 
#define IR_DIY6   0xFF50AF  // 
#define IR_FLASH  0xFFD02F  // 
#define IR_JUMP3  0xFF20DF  // 
#define IR_JUMP7  0xFFA05F  // 
#define IR_FADE3  0xFF609F  // 
#define IR_FADE7  0xFFE01F  // 
#endif


const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

String color,style,state,type;

void transmitIr(uint32_t code) {
  for(int i=0; i < 2; i++){
        irsend.sendNEC(code, 32);
        delay(300);
      }
}
void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/");  

}


void loop(void) {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
    ESP.reset();
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");

     if(eventType == "put"){
      String data = event.getString("data");
      String path = event.getString("path");


      if(path == "/style"){
        if(data == "flash"){
          transmitIr(IR_FLASH);
          Serial.println("Turning on flash light");
        }
         if(data == "fade"){
          transmitIr(IR_FADE);
          Serial.println("Turning on fade light");
        }
        if(data == "strobe"){
          transmitIr(IR_STROBE);
          Serial.println("Turning on strobe light");
        }
        if(data == "smooth"){
          transmitIr(IR_SMOOTH);
          Serial.println("Turning on smooth light");
        }
      }


      if(path == "/color"){
        if(data == "red"){
          transmitIr(IR_R);
          Serial.println("Turning on red light");
        }
        else if(data == "green"){
          transmitIr(IR_G);
          Serial.println("Turning on green light");
        }
        else if(data == "blue"){
          transmitIr(IR_B);
          Serial.println("Turning on blue light");
        }
        else if(data == "orange"){
          transmitIr(IR_R1);
          Serial.println("Turning on orange light");
        }
        else if(data == "pink"){
          transmitIr(IR_B4);
          Serial.println("Turning on pink light");
        }
        else if(data == "yellow"){
          transmitIr(IR_R4);
          Serial.println("Turning on yellow light");
        }
      }
      
      if(path == "/state"){
        if(data == "on"){
          transmitIr(IR_ON);
          Serial.println("Turning on the light");
        }
        else if(data == "off"){
          transmitIr(IR_OFF);
          Serial.println("Turning off the light");
        }
      }
      
     }
  }
}

