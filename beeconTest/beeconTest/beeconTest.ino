/*
  BEECON TEST
  --
  
  Blink a LED when a phone running the Beecon app gets within range of an iBeacon.
  The iBeacon is configured to make an API call to an Arduino Yun when a phone
  gets in range.
  
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Process.h>

int ledPin = 13;

YunServer server;

void setup() {
  // Bridge startup
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  Bridge.begin();
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);

  server.listenOnLocalhost();
  server.begin();
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
  for(int count = 0; count < 10; count++){
    digitalWrite(blinkPin,LOW); 
    delay(pause);
    digitalWrite(blinkPin,HIGH); 
    delay(pause);
    digitalWrite(blinkPin,LOW);
  }
}

void resetPins(){
  digitalWrite(ledPin, LOW);
}

void callPin(int pin, int callState){
  resetPins();
  blink(ledPin, 100);
}


