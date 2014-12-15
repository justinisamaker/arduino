/*
  LIVE FILTERING
  --
  
  Listen for incoming calls through the Bridge, call corresponding pin
  Utilizes code from the Bridge example and the Wifi-Status example
  
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Process.h>

int itemOne = 9;
int itemTwo = 7;
int itemThree = 4;
int testPin = 13;

YunServer server;

void setup() {
  // Bridge startup
  pinMode(itemOne, OUTPUT);
  pinMode(itemTwo, OUTPUT);
  pinMode(itemThree, OUTPUT);
  pinMode(testPin, OUTPUT);

  digitalWrite(testPin, LOW);
  Bridge.begin();
  digitalWrite(testPin, HIGH);

  server.listenOnLocalhost();
  server.begin();

  // STARTUP PATTERN
  blink(itemOne, 150);
  blink(itemTwo, 150);
  blink(itemThree, 150);
}

void loop() {
  // BRIDGE STARTUP
  YunClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  
  // WIFI CHECK STARTUP
  Process wifiCheck;
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }
  Serial.println();
  delay(50); // Poll every 50ms
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }
}

void digitalCommand(YunClient client) {
  int pin, value;
  pin = client.parseInt();
  
  if (client.read() == '/') {
    value = client.parseInt();
    callPin(pin, value);
  }
  else {
    value = digitalRead(pin);
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  // Update datastore key with the current pin value
  String key = "D";
  key += pin;
  Bridge.put(key, String(value));
}

void blink(int blinkPin, int pause){
  digitalWrite(blinkPin,LOW); 
  delay(pause);
  digitalWrite(blinkPin,HIGH); 
  delay(pause);
  digitalWrite(blinkPin,LOW); 
  delay(pause);
}

void sequenceBlink(int sequencePause){
  blink(itemOne, sequencePause);
  blink(itemTwo, sequencePause);
  blink(itemThree, sequencePause);
  blink(itemTwo, sequencePause);
  blink(itemOne, sequencePause);
  blink(itemTwo, sequencePause);
  blink(itemThree, sequencePause);
  resetPins();
}

void resetPins(){
  digitalWrite(itemOne, LOW);
  digitalWrite(itemTwo, LOW);
  digitalWrite(itemThree, LOW);
}

void callPin(int pin, int callState){
  resetPins();
  blink(pin, 150);
  digitalWrite(pin, callState);
  delay(3000);
  sequenceBlink(50);
}


