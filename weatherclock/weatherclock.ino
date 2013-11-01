
// Modified from code for GE Garage Chicago 2013

#include <Servo.h>
#include <SPI.h>
#include <WiFi.h>

const boolean DEBUG = false;

enum conditionType {
  GE = 0,
  CLEAR,
  CLOUDY,
  RAIN,
  THUNDERSTORM,
  SNOW
};

Servo dial;

int conditionsIndex[6] = { 
  GE, CLEAR, CLOUDY, RAIN, THUNDERSTORM, SNOW}; 

const char *conditions[][20] = {
  // GE
  { 
    "THINKING"   }
  ,
  // CLEAR
  {
    "Clear"    }
  ,
  // CLOUDY
  {
    "Overcast",
    "Scattered Clouds", 
    "Partly Cloudy",
    "Shallow Fog",
    "Partial Fog",
    "Mostly Cloudy",
    "Fog",
    "Fog Patches",
    "Smoke"    }
  ,
  // RAIN
  {
    "Drizzle",
    "Rain",
    "Hail",
    "Mist",
    "Freezing Drizzle",
    "Patches of Fog",
    "Rain Mist",
    "Rain Showers",
    "Unknown Precipitation",
    "Unknown",
    "Low Drifting Widespread Dust",
    "Low Drifting Sand"    }
  ,
  // THUNDERSTORM
  {
    "Thunderstorm",
    "Thunderstorms and Rain",
    "Thunderstorms and Snow",
    "Thunderstorms and Ice Pellets",
    "Thunderstorms with Hail",
    "Thunderstorms with Small Hail",
    "Blowing Widespread Dust",
    "Blowing Sand",
    "Small Hail",
    "Squalls",
    "Funnel Cloud"    }
  ,
  // SNOW
  {
    "Volcanic Ash",
    "Widespread Dust",
    "Sand",
    "Haze",
    "Spray",
    "Dust Whirls",
    "Sandstorm",
    "Freezing Rain",
    "Freezing Fog",
    "Blowing Snow",    
    "Snow Showers",
    "Snow Blowing Snow Mist",
    "Ice Pellet Showers",
    "Hail Showers",
    "Small Hail Showers",
    "Snow",
    "Snow Grains",
    "Low Drifting Snow",
    "Ice Crystals",
    "Ice Pellets"    }
};

/*
*  FILL IN THESE VARIABLES
*/
char ssid[] = "CM60";           //  your network SSID (name) 
char pass[] = "CMguest-2013";            //  your network password
String apiState = "IL";                 //  the state where you want to montitor weather (in a two letter format)
String apiCity = "Chicago";         //  the state where you want to monitor weather (each word should be capitalized, replace space with an underscore i.e. New_York).
String apiKey  = "5e74b09365ca85d0";    //  the wunderground api token

int status = WL_IDLE_STATUS;            // the Wifi radio's status
WiFiClient client;

const unsigned long requestInterval = 600000; // Update every 60 minutes

char serverName[] = "api.wunderground.com";  
String GETReqeuest = "GET /api/" + apiKey + "/conditions/q/"+ apiState + "/" + apiCity +".xml HTTP/1.1";
boolean requested;
unsigned long lastAttemptTime = 0;            

String currentLine = "";           
String weatherCondition = "";      
String forecast;

boolean readingWeather = false;      
boolean processingData = true;
boolean clockOriented  = true;
int currentCondition;


void setup() {

  dial.attach(9);
  dial.write(30);  // sets servo to thinking orientation
  delay(4000);
  currentLine.reserve(256);
  weatherCondition.reserve(150);

  if(DEBUG) {
    Serial.begin(9600);

    while (!Serial) {
      ; 
    }
  }

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) { 
    if(DEBUG) Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  } 
  else {
    if (DEBUG) Serial.println("Connected to wifi");
    if (DEBUG) Serial.println("Starting connection...");
    delay(10000);
    connectToServer();
  }
}



void loop()
{
  checkRequest();
  processWeather();
}


void checkRequest() {
  if (client.available()) {
    char inChar = client.read();
    currentLine += inChar; 
    if (inChar == '\n') {
      currentLine = "";
    } 
    if ( currentLine.endsWith("<weather>")) {
      readingWeather = true; 
      weatherCondition = "";
    }
    if (readingWeather) {
      if (inChar != '<') {
        weatherCondition += inChar;
      } 
      else {
        readingWeather = false;
        weatherCondition = weatherCondition.substring(1, weatherCondition.length());
        forecast = weatherCondition;
        if(DEBUG) Serial.print("SERVER CONDITION: ");
        if(DEBUG) Serial.print(weatherCondition);   
        client.stop(); 
        clockOriented  = false;
        processingData = false;
      }
    }
  }   
  else if (millis() - lastAttemptTime > requestInterval) {
    connectToServer();
  }
}


void connectToServer() {
  if(DEBUG) Serial.println("connecting to server...");
  if (client.connect(serverName, 80)) {
    if(DEBUG) Serial.println("connected to server");
    client.println(GETReqeuest);

    client.println("Host: api.wunderground.com");
    client.println("Connection: close");
    client.println();
    clockOriented = true;
  }
  lastAttemptTime = millis();
}   

void processWeather(){
  if (!processingData && clockOriented == false ){
    calculateCondition();
    clockOriented = true;
  }
}

void calculateCondition(){
  if (forecast.indexOf("Light ") >= 0 ) {
    forecast.replace("Light ", "");
  } 
  else if (forecast.indexOf("Heavy ") >= 0 ) {
    forecast.replace("Heavy ", "");
  }

  if(DEBUG) Serial.print("forecast: ");
  if(DEBUG) Serial.print(forecast);
  if(DEBUG) Serial.println();
  
  for ( int i = 0; i < ( sizeof(conditionsIndex) / sizeof(int) ); i++ ) {
    int idx = conditionsIndex[i];
    for (int j = 0; j < ( sizeof(conditions[idx]) / sizeof(String) ); j++ ) {
      if ( forecast.equals(conditions[idx][j])) {
        currentCondition = idx;
      }
    }
  }
  orientClock();
}

void orientClock(){
  int pos = 25;
  int idx = currentCondition;
  switch(idx){
  case 0:
    if(DEBUG) Serial.println("THINKING");
    pos = 30;
    break;
  case 1:
    if(DEBUG) Serial.println("CLEAR");
    pos = 60;
    break;
  case 2:
    if(DEBUG) Serial.println("CLOUDY");    
    pos = 90;
    break;
  case 3:
    if(DEBUG) Serial.println("RAIN");        
    pos = 120;
    break;
  case 4:
    if(DEBUG) Serial.println("THUNDERSTORM");        
    pos = 150;
    break;
  case 5:
    if(DEBUG) Serial.println("SNOW");        
    pos = 180;
    break;
  default:
    pos = 0;
    break;
  }
  for(int i = 0; i < pos; i ++)  
  {                              
    dial.write(i); // i              
    delay(15);                  
  } 
  delay(5000);
}

void printWifiData() {
  if(DEBUG) {
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    Serial.println(ip);
  
    // print your MAC address:
    byte mac[6];  
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    Serial.print(mac[5],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.println(mac[0],HEX);
  }
}


