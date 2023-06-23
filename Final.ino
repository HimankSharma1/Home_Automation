#define DEBUG_SW 1

// libraries
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <Espalexa.h> // https://github.com/Aircoookie/Espalexa

Espalexa espalexa;

#define R1 D0
#define R2 D1
#define R3 D2
#define R4 D3
#define S1 D7
#define S2 D6 
#define S3 D5 
#define S4 10 //SD3


bool toggleState_1 = LOW; //Define integer to remember the toggle state for relay 1
bool toggleState_2 = LOW; //Define integer to remember the toggle state for relay 2
bool toggleState_3 = LOW; //Define integer to remember the toggle state for relay 3
bool toggleState_4 = LOW; //Define integer to remember the toggle state for relay 4

bool SwitchState_2 = HIGH;
bool SwitchState_3 = HIGH;
bool SwitchState_1 = HIGH;
bool SwitchState_4 = HIGH;

// WiFi Credentials
const char* ssid = "Wifi Name";
const char* password = "Wifi Password";
#define BLYNK_AUTH_TOKEN "Enter Yours"
const char* auth = BLYNK_AUTH_TOKEN;

// device names
String Appliance1 = "Light 1";
String Appliance2 = "Light 2";
String Appliance3 = "Light 3";
String Appliance4 = "Light 4";


boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);

boolean wifiConnected = false;

//our callback functions
void firstLightChanged(uint8_t brightness)
{

  if (brightness == 255)
  {
    digitalWrite(R1, LOW);
    Blynk.virtualWrite(V0, HIGH);
    Serial.println("Device1 ON");
  }
  else
  {
    digitalWrite(R1, HIGH);
    Blynk.virtualWrite(V0, LOW);
    Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{

  if (brightness == 255)
  {
    Blynk.virtualWrite(V1, HIGH);
    digitalWrite(R2, LOW);
    Serial.println("Device2 ON");
  }
  else
  {
    digitalWrite(R2, HIGH);
    Blynk.virtualWrite(V1, LOW);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{

  if (brightness == 255)
  {
    Blynk.virtualWrite(V2, HIGH);
    digitalWrite(R3, LOW);
    Serial.println("Device3 ON");
  }
  else
  {
    digitalWrite(R3, HIGH);
    Serial.println("Device3 OFF");
    Blynk.virtualWrite(V2, LOW);
  }
}

void fourthLightChanged(uint8_t brightness)
{
  if (brightness == 255)
  {
    digitalWrite(R4, LOW);
    Blynk.virtualWrite(V3, HIGH);
    Serial.println("Device4 ON");
  }
  else
  {
    digitalWrite(R4, HIGH);
    Blynk.virtualWrite(V3, LOW);
    Serial.println("Device4 OFF");
  }
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

void ESPAlexa_Devices()
{
  // Define your devices here.
  espalexa.addDevice(Appliance1, firstLightChanged);
  espalexa.addDevice(Appliance2, secondLightChanged);
  espalexa.addDevice(Appliance3, thirdLightChanged);
  espalexa.addDevice(Appliance4, fourthLightChanged);

  espalexa.begin();
}


BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value1 == 1) {
    digitalWrite(R1, LOW);
  } else {
    digitalWrite(R1, HIGH);
  }
}
BLYNK_WRITE(V1) {
  bool value2 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value2 == 1) {
    digitalWrite(R2, LOW);
  } else {
    digitalWrite(R2, HIGH);
  }
}
BLYNK_WRITE(V2) {
  bool value3 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value3 == 1) {
    digitalWrite(R3, LOW);
  } else {
    digitalWrite(R3, HIGH);
  }
}
BLYNK_WRITE(V3) {
  bool value4 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value4 == 1) {
    digitalWrite(R4, LOW);
  } else {
    digitalWrite(R4, HIGH);
  }
}


//.......................................................................


void Firstmanual(){
  if (digitalRead(S1) == LOW) {
    digitalWrite(R1, LOW);
    Blynk.virtualWrite(V0, HIGH);
    toggleState_1 = HIGH;
    SwitchState_1 = HIGH;
    Serial.println("Switch-1 on");
  }
  else if (digitalRead(S1) == HIGH) {
    digitalWrite(R1, HIGH);
    Blynk.virtualWrite(V0, LOW);
    toggleState_1 = LOW;
    SwitchState_1 = LOW;
    Serial.println("Switch-1 off");
  }
  if (digitalRead(S2) == LOW) {
    digitalWrite(R2, LOW);
    Blynk.virtualWrite(V1, HIGH);
    toggleState_2 = HIGH;
    SwitchState_2 = HIGH;
    Serial.println("Switch-2 on");
  }
  else if (digitalRead(S2) == HIGH) {
    digitalWrite(R2, HIGH);
    Blynk.virtualWrite(V1, LOW);
    toggleState_2 = LOW;
    SwitchState_2 = LOW;
    Serial.println("Switch-2 off");
  }
  if (digitalRead(S3) == LOW) {
    digitalWrite(R3, LOW);
    Blynk.virtualWrite(V2, HIGH);
    toggleState_3 = HIGH;
    SwitchState_3 = HIGH;
    Serial.println("Switch-3 on");
  }
  else if (digitalRead(S3) == HIGH) {
    digitalWrite(R3, HIGH);
    Blynk.virtualWrite(V2, LOW);
    toggleState_3 = LOW;
    SwitchState_3 = LOW;
    Serial.println("Switch-3 off");
  }
  if (digitalRead(S4) == LOW) {
    digitalWrite(R4, LOW);
    Blynk.virtualWrite(V3, HIGH);
    toggleState_4 = HIGH;
    SwitchState_4 = HIGH;
    Serial.println("Switch-4 on");
  }
  else if (digitalRead(S4) == HIGH) {
    digitalWrite(R4, HIGH);
    Blynk.virtualWrite(V3, LOW);
    toggleState_4 = LOW;
    SwitchState_4 = LOW;
    Serial.println("Switch-4 off");
  }
}

void Manual(){
  if (digitalRead(S1) == LOW && SwitchState_1 == LOW) {
    digitalWrite(R1, LOW);
    Blynk.virtualWrite(V0, HIGH);
    toggleState_1 = HIGH;
    SwitchState_1 = HIGH;
    Serial.println("Switch-1 on");
  }
  else if (digitalRead(S1) == HIGH && SwitchState_1 == HIGH) {
    digitalWrite(R1, HIGH);
    Blynk.virtualWrite(V0, LOW);
    toggleState_1 = LOW;
    SwitchState_1 = LOW;
    Serial.println("Switch-1 off");
  }
  if (digitalRead(S2) == LOW && SwitchState_2 == LOW) {
    digitalWrite(R2, LOW);
    Blynk.virtualWrite(V1, HIGH);
    toggleState_2 = HIGH;
    SwitchState_2 = HIGH;
    Serial.println("Switch-2 on");
  }
  else if (digitalRead(S2) == HIGH && SwitchState_2 == HIGH) {
    digitalWrite(R2, HIGH);
    Blynk.virtualWrite(V1, LOW);
    toggleState_2 = LOW;
    SwitchState_2 = LOW;
    Serial.println("Switch-2 off");
  }
  if (digitalRead(S3) == LOW && SwitchState_3 == LOW) {
    digitalWrite(R3, LOW);
    Blynk.virtualWrite(V2, HIGH);
    toggleState_3 = HIGH;
    SwitchState_3 = HIGH;
    Serial.println("Switch-3 on");
  }
  else if (digitalRead(S3) == HIGH && SwitchState_3 == HIGH) {
    digitalWrite(R3, HIGH);
    Blynk.virtualWrite(V2, LOW);
    toggleState_3 = LOW;
    SwitchState_3 = LOW;
    Serial.println("Switch-3 off");
  }
  if (digitalRead(S4) == LOW && SwitchState_4 == LOW) {
    digitalWrite(R4, LOW);
    Blynk.virtualWrite(V3, HIGH);
    toggleState_4 = HIGH;
    SwitchState_4 = HIGH;
    Serial.println("Switch-4 on");
  }
  else if (digitalRead(S4) == HIGH && SwitchState_4 == HIGH) {
    digitalWrite(R4, HIGH);
    Blynk.virtualWrite(V3, LOW);
    toggleState_4 = LOW;
    SwitchState_4 = LOW;
    Serial.println("Switch-4 off");
  }
}
//......................................................................


void BlynkWrite(){
  //Read the switch when connected to internet at the starting and virtual write to blynk server
  if (digitalRead(S1)==0){
    Blynk.virtualWrite(V0,HIGH);
  }
  else{
    Blynk.virtualWrite(V0, LOW);
  }
  
  if (digitalRead(S2)==0){
    Blynk.virtualWrite(V1,HIGH);
  }
  else{
    Blynk.virtualWrite(V1, LOW);
  }

  if (digitalRead(S3)==0){
    Blynk.virtualWrite(V2,HIGH);
  }
  else{
    Blynk.virtualWrite(V2, LOW);
  }

  if (digitalRead(S4)==0){
    Blynk.virtualWrite(V3,HIGH);
  }
  else{
    Blynk.virtualWrite(V3, LOW);
  }
}


void setup()
{
  Serial.begin(115200);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);


  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);


  // Initialise wifi connection
  wifiConnected = connectWifi();
  if (wifiConnected)
  {
    Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
    Firstmanual();
    ESPAlexa_Devices();
  }
  else
  {
    Serial.println("wifi not connected!!!");
    Firstmanual();
    delay(100);
  }
}

void loop()
{
  Manual();
  if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW)Serial.print("Not Connected ");
  }
  else
  {
    if (DEBUG_SW)Serial.print("Connected  ");
    if (wifiConnected)
    {
      espalexa.loop();
      delay(1);
      Blynk.run();
      delay(1);
      
    }
    else
    {
      wifiConnected = connectWifi();
      if (wifiConnected)
      {
        ESPAlexa_Devices();
        Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
      }
    }
  }
}