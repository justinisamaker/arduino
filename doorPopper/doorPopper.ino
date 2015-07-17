#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

int lock = 11;

void setup() {
  pinMode(lock, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  YunClient client = server.accept();
  
  if(client){
    process(client);
    client.stop(); 
  }
  
  delay(50);
}

void process(YunClient client){
  String command = client.readStringUntil('/');
 
  if(command == "digital"){
    digitalCommand(client);
  } 
}

void digitalCommand(YunClient client){
  int pin, value;
  
  pin = client.parseInt();
 
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
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
