

/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WiFiManager.h>
#include <DNSServer.h>
#define USE_SERIAL Serial
ESP8266WebServer server(80);

const uint16_t kIrLed = 14;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
/*
//definir taula de codis
#define Power 0x1EE1F40B //0
#define Alarm 0x1EE105FA //1
#define Snooze 0x1EE1F20D //2
#define CD 0x1EE152AD //3
#define Bluetooth 0x1EE17B84
#define USB 0x1EE13DC2
#define Radio 0x1EE1D22D
#define Aux 0x1EE1FB04
#define Option 0x1EE1D42B
#define Display 0x1EE150AF
#define Mute 0x1EE139C6
#define up 0x1EE1718E
#define down 0x1EE1F10E
#define left 0x1EE120DF
#define right 0x1EE1C03F
#define enter 0x1EE1837C
#define aturar 0x1EE1807F //stop
#define playpause 0x1EE140BF
#define volumup 0x1EE17887
#define volumdown 0x1EE1F807
#define Ltunning 0x1EE1956A
#define Rtunning 0x1EE155AA
#define Lpreset 0x1EE138C7
#define Rpreset 0x1EE1D827
#define memory 0x1EE14DB2
#define volta 0x1EE130CF // loop
#define aleatori 0x1EE1E01F //random
#define hold 0xFFFFFFFFFFFFFFFF //aguantar apretat


*/
const uint64_t Power=0x1EE1F40B; //0
const uint64_t Alarm=0x1EE105FA; //1
const uint64_t Snooze=0x1EE1F20D; //2
const uint64_t CD=0x1EE152AD; //3
const uint64_t Bluetooth=0x1EE17B84;
const uint64_t USB=0x1EE13DC2;
const uint64_t Radio=0x1EE1D22D;
const uint64_t Aux=0x1EE1FB04;
const uint64_t Option=0x1EE1D42B;
const uint64_t Display=0x1EE150AF;
const uint64_t Mute=0x1EE139C6;
const uint64_t Up=0x1EE1718E;
const uint64_t Down=0x1EE1F10E;
const uint64_t left=0x1EE120DF;
const uint64_t right=0x1EE1C03F;
const uint64_t enter=0x1EE1837C;
const uint64_t aturar=0x1EE1807F; //stop
const uint64_t playpause=0x1EE140BF;
const uint64_t volumup=0x1EE17887;
const uint64_t volumdown=0x1EE1F807;
const uint64_t Ltunning=0x1EE1956A;
const uint64_t Rtunning=0x1EE155AA;
const uint64_t Lpreset=0x1EE138C7;
const uint64_t Rpreset=0x1EE1D827;
const uint64_t memory=0x1EE14DB2;
const uint64_t volta=0x1EE130CF; // loop
const uint64_t aleatori=0x1EE1E01F; //random
const uint64_t hold=0xFFFFFFFFFFFFFFFF; //aguantar apretat

String TaulaCodis[]={"0x1EE1F40B","0x1EE105FA","0x1EE1F20D","0x1EE152AD","0x1EE17B84","0x1EE13DC2","0x1EE1D22D","0x1EE1FB04","0x1EE1D42B","0x1EE150AF","0x1EE139C6","0x1EE1718E""0x1EE1F10E","0x1EE120DF","0x1EE1C03F","0x1EE1837C","0x1EE1807F","0x1EE140BF","0x1EE17887","0x1EE1F807","0x1EE1956A","0x1EE155AA","0x1EE138C7","0x1EE1D827","0x1EE14DB2","0x1EE130CF","0x1EE1E01F"};
//uint64_t TaulaCodis[]={0x1EE1F40B,0x1EE105FA,0x1EE1F20D,0x1EE152AD,0x1EE17B84,0x1EE13DC2,0x1EE1D22D,0x1EE1FB04,0x1EE1D42B,0x1EE150AF,0x1EE139C6,0x1EE1718E0x1EE1F10E,0x1EE120DF,0x1EE1C03F,0x1EE1837C,0x1EE1807F,0x1EE140BF,0x1EE17887,0x1EE1F807,0x1EE1956A,0x1EE155AA,0x1EE138C7,0x1EE1D827,0x1EE14DB2,0x1EE130CF,0x1EE1E01F};




void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

//Config Wifi Manager
    WiFiManager wifiManager;
    //first parameter is name of access point, second is the password
    wifiManager.autoConnect("yamaha");
    wifiManager.setConfigPortalTimeout(180);
  //fi config wifi


  //inici web server
  server.on("/", handle_index); //Handle Index page

  server.begin(); //Start the server
  Serial.println("Server listening");
  //fi web server

 //EnviarCodi(volumup, 1); //1 aguantar apretat // 0 un sol pols
}



/*
void EnviarCodi(int codi, int aguantar){
  Serial.println(codi);
  irsend.sendNEC(codi);
  if (aguantar == 1){
    for (int i = 0; i <= 20; i++) {
        irsend.sendNEC(hold);
        delay(10);
    }
  }   
}
*/
void EnviarCodi(String codi){
    Serial.println("Dins funcio EnviarCodi");
  Serial.println(codi);

if (codi=="Power") {
    irsend.sendNEC(0x1EE1F40B);
}
else if (codi=="Alarm") {
    irsend.sendNEC(0x1EE105FA);
}
else if (codi=="Snooze") {
    irsend.sendNEC(0x1EE1F20D);
}
else if (codi=="CD") {
    irsend.sendNEC(0x1EE152AD);
}
else if (codi=="Bluetooth") {
    irsend.sendNEC(0x1EE17B84);
}
else if (codi=="USB") {
    irsend.sendNEC(0x1EE13DC2);
}
else if (codi=="Radio") {
    irsend.sendNEC(0x1EE1D22D);
}
else if (codi=="Aux") {
    irsend.sendNEC(0x1EE1FB04);
}
else if (codi=="Option") {
    irsend.sendNEC(0x1EE1D42B);
}
else if (codi=="Display") {
    irsend.sendNEC(0x1EE150AF);
}
else if (codi=="Mute") {
    irsend.sendNEC(0x1EE139C6);
}
else if (codi=="Up") {
    irsend.sendNEC(0x1EE1718E);
}
else if (codi=="Down") {
    irsend.sendNEC(0x1EE1F10E);
}
else if (codi=="left") {
    irsend.sendNEC(0x1EE120DF);
}
else if (codi=="right") {
    irsend.sendNEC(0x1EE1C03F);
}
else if (codi=="enter") {
    irsend.sendNEC(0x1EE1837C);
}
else if (codi=="aturar") {
    irsend.sendNEC(0x1EE1807F);
}
else if (codi=="playpause") {
    irsend.sendNEC(0x1EE140BF);
}
else if (codi=="volumup") {
    irsend.sendNEC(0x1EE17887);
}
else if (codi=="volumdown") {
    irsend.sendNEC(0x1EE1F807);
}
else if (codi=="Ltunning") {
    irsend.sendNEC(0x1EE1956A);
        for (int i = 0; i <= 5; i++) {
          irsend.sendNEC(0xFFFFFFFFFFFFFFFF);
        delay(10);
    }
}
else if (codi=="Rtunning") {
    irsend.sendNEC(0x1EE155AA);
        for (int i = 0; i <= 5; i++) {
          irsend.sendNEC(0xFFFFFFFFFFFFFFFF);
        delay(10);
    }
}
else if (codi=="Lpreset") {
    irsend.sendNEC(0x1EE138C7);
}
else if (codi=="Rpreset") {
    irsend.sendNEC(0x1EE1D827);
}
else if (codi=="memory") {
    irsend.sendNEC(0x1EE14DB2);
}
else if (codi=="AUTOPRESET") {
    irsend.sendNEC(0x1EE14DB2);
        for (int i = 0; i <= 30; i++) {
          irsend.sendNEC(0xFFFFFFFFFFFFFFFF);
        delay(10);
    }
}
else if (codi=="volta") {
    irsend.sendNEC(0x1EE130CF);
}
else if (codi=="aleatori") {
    irsend.sendNEC(0x1EE1E01F);
}
else if (codi=="pair") {
    irsend.sendNEC(0x1EE17B84);
        for (int i = 0; i <= 20; i++) {
        irsend.sendNEC(0xFFFFFFFFFFFFFFFF);
        delay(10);
    }
}
else {
  // do Thing C
}
  
}

//https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/
void loop() {
  //codi loop
    server.handleClient(); //Handling of incoming client requests


}



void handle_index() {
      
  String tecla = server.arg("tecla");
  Serial.println(tecla);
  EnviarCodi(tecla);

  server.send(200, "text/html", SendHTML());

}


String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Remot Yamaha MCR-B020</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 0px;} h1 {color: #444444;margin: 1px auto 1px;} h3 {color: #444444;margin: 1px auto 1px;}\n";
  ptr +=".button {display: inline-block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 10px;text-decoration: none;font-size: 15px;margin: 0px auto 5px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-vermell {background-color: #FF4136;}\n";
  ptr +=".button-gris {background-color: #AAAAAA;}\n";
  ptr +=".button-volum {background-color: #7FDBFF;}\n";
  ptr +=".button-cursor {background-color: #0074D9;}\n";
  ptr +=".button-tunning {background-color: #85144b;}\n";
  ptr +=".button-emparellar {background-color: #0074D9;}\n";
  ptr +=".button-taronja {background-color: #FF851B;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";







  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h3>Remot Yamaha MCR-B020</h3>\n";

ptr +="<a class=\"button button-volum\" href=\"/?tecla=volumup\">Vol +</a>\n";
ptr +="<a class=\"button button-volum\" href=\"/?tecla=volumdown\">Vol -</a>\n";
ptr +="<a class=\"button button-taronja\" href=\"/?tecla=Mute\">Mute</a>\n";

ptr +="<a class=\"button button-on\" href=\"/?tecla=Rpreset\">Preset +</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=Lpreset\">Preset -</a>\n";
ptr +="<a class=\"button button-vermell\" href=\"/?tecla=Power\">Power</a>\n";

ptr +="<a class=\"button button-tunning\" href=\"/?tecla=Ltunning\">&lt;&lt; tunning</a>\n";
ptr +="<a class=\"button button-tunning\" href=\"/?tecla=Rtunning\">tunning &gt;&gt;</a>\n";
ptr +="<a class=\"button button-taronja\" href=\"/?tecla=Alarm\">Alarm</a>\n";
ptr +="<a class=\"button button-gris\" href=\"/?tecla=CD\">CD</a>\n";
ptr +="<a class=\"button button-gris\" href=\"/?tecla=Bluetooth\">Bluetooth</a>\n";
ptr +="<a class=\"button button-emparellar\" href=\"/?tecla=pair\">Emparellar</a>\n";

ptr +="<a class=\"button button-gris\" href=\"/?tecla=USB\">USB</a>\n";
ptr +="<a class=\"button button-gris\" href=\"/?tecla=Radio\">Radio</a>\n";
ptr +="<a class=\"button button-gris\" href=\"/?tecla=Aux\">Aux</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=Option\">Option</a>\n";
ptr +="<a class=\"button button-cursor\" href=\"/?tecla=Up\">&uarr;</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=Display\">Display</a>\n";
ptr +="<a class=\"button button-cursor\" href=\"/?tecla=left\">&larr;</a>\n";
ptr +="<a class=\"button button-cursor\" href=\"/?tecla=enter\">&crarr;</a>\n";
ptr +="<a class=\"button button-cursor\" href=\"/?tecla=right\">&rarr;</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=aturar\">Stop</a>\n";

ptr +="<a class=\"button button-cursor\" href=\"/?tecla=Down\">&darr;</a>\n";

ptr +="<a class=\"button button-on\" href=\"/?tecla=playpause\">Playpause</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=memory\">memory</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=volta\">Loop</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=aleatori\">Random</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=Snooze\">Snooze</a>\n";
ptr +="<a class=\"button button-on\" href=\"/?tecla=AUTOPRESET\">Auto Preset</a>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
