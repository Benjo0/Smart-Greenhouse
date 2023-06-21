#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 6
#define sensorPin A0


Servo myServo;
SoftwareSerial mySerial(3, 2);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
int FloatSensor = 15;
int waterLevel = 1; 
int relay = 5;
int tempS = 6;
int led1 = 7;
int led2 = 11;
int enginePin = 10;
int LDRSensor = 8;
int humiditySensor = 16;
int sms_lowWaterLever = 0;
int sms_HighWaterLevel = 0;
int humidity = 0;
float tempCelsius;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
int pos = 150;
int sun=0;

void setup() {
  //Communication of Arduino with Arduino IDE
  Serial.begin(9600);
  tempSensors.begin();
  myServo.attach(enginePin);
  myServo.write(pos);
  Serial.println("Initializing..."); 
  delay(1000);
  Serial.println("AT"); //Checking the GSM and Arduino connection
  updateSerial();
  Serial.println("AT+CPIN=0000");
  updateSerial();
  _delay_ms(100);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode (LDRSensor, INPUT);
  pinMode(FloatSensor, INPUT_PULLUP);
  lcd.begin(2,16);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0); 
  lcd.print("Welcome!"); 
  _delay_ms(1000);
  lcd.clear();
  lcd.setCursor(1, 0); 
  lcd.print("Greenhouse project"); 
  lcd.setCursor(1, 1); 
  lcd.print("By Benjamin");
  _delay_ms(3000);
  lcd.clear();
}

void loop() {
            humidity = 0;
        
          humidity = analogRead(humiditySensor);
          Serial.print(humidity);
        _delay_ms(1000);
        Serial.print("       \n");
        Serial.print("Light:   ");
          sun = digitalRead (LDRSensor);
          Serial.print(sun);
          Serial.print("       \n");
          tempSensors.requestTemperatures();             
          tempCelsius = tempSensors.getTempCByIndex(0);
              if (humidity<500){
                lcd.clear();
                  _delay_ms(100);
                lcd.setCursor(0, 0); 
              lcd.print("Too much water!"); 
              lcd.setCursor(1, 1); 
              lcd.print("Temperature: ");
              lcd.print(tempCelsius);
              _delay_ms(10000);
              }//soil is wet too much
              if(humidity>500 && humidity<750){
                lcd.clear();
                  _delay_ms(100);
              lcd.setCursor(0, 0); 
              lcd.print("Optimally moist!"); 
              lcd.setCursor(1, 1); 
              lcd.print("Temperature: ");
              lcd.print(tempCelsius);
            _delay_ms(10000);
              } //optimally water in soil
                if(humidity>750){
                  lcd.clear();
                  _delay_ms(100);
                lcd.setCursor(1, 0); 
                lcd.print("Needs watering!"); 
                lcd.setCursor(1, 1); 
                lcd.print("Temperature: ");
                lcd.print(tempCelsius);
                _delay_ms(2000);
                turnOnPump();  
              _delay_ms(5000);
              } //dry
          if(tempCelsius>27){
           //Opening window
           if(pos==150){
           Serial.print("Window is opening");
            for(pos= 150; pos>=0; pos--){
              myServo.write(pos);
              _delay_ms(15);}
              pos=55;
           }
            }else{
              //Colsing window (activating servo)
              if(pos==0){
                 Serial.print("Window is closing");
                for(pos= 0; pos<=150; pos++){
              myServo.write(pos);
              _delay_ms(15);} }
            }//temperature check for opening or closing window if it's needed
      if ( sun == HIGH ) {
        //Turning on LED if there is no sun
      turnOnLight();  
      }else{
        turnOffLight();        
      }
  _delay_ms(9000);

} //Loop


void turnOnLight(){
  //Turning on led diods
  Serial.print("Turning on led diode \n");
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  _delay_ms(8000);
}

void turnOffLight(){
  //Turning of light
  Serial.print("Led diode is turning off \n");
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void SendMessageTankFull()
{
  Serial.println("AT+CMGF=1"); 
  updateSerial();
  Serial.println("AT+CMGS=\"+38762987268\"");
  updateSerial();
  Serial.print("Watering soil in process !!"); 
  updateSerial();
  Serial.write(26);
}

 
void SendMessageTankNotFull()
{
  Serial.println("AT+CMGF=1");
  updateSerial();
 Serial.println("AT+CMGS=\"+38762987268\"");
  updateSerial();
  Serial.print("Tank is empty, water is needed !!"); 
  updateSerial();
  Serial.write(26);
}


void turnOnPump(){
      waterTankLevel = digitalRead(FloatSensor);
      if (waterTankLevel == HIGH) {
        _delay_ms(1000);
        lcd.clear();
        _delay_ms(500);
        digitalWrite(relay, LOW);
        Serial.println("NEEDS WATERING\r");
        lcd.setCursor(0, 0); // Placing the cursor in the first line of the LCD
      lcd.print("Soil needs watering"); 
      lcd.setCursor(0, 1); //Positioning the cursor in the second row
      lcd.print("PUMP: OFF");
      if(sms_lowWaterLever==0){
        SendMessageTankNotFull();
        Serial.println("SMS SENT THERE IS NO WATER IN TANK");
        sms_lowWaterLever=1;
        sms_HighWaterLevel=0;
      }
      _delay_ms(10000);
        }else{
      _delay_ms(1000);
          lcd.clear();
          _delay_ms(500);
        digitalWrite(relay, HIGH);
        Serial.println("Watering soil");
        lcd.setCursor(1, 0); 
        lcd.print("Watering soil"); 
        lcd.setCursor(0, 1); 
        lcd.print("PUMP: ON");
        if(sms_HighWaterLevel==0){
          _delay_ms(100);
          SendMessageTankFull();
          _delay_ms(250);
          Serial.println("SMS Sent that watering is done");
          sms_HighWaterLevel=1;
          sms_lowWaterLever=0;
        }
        _delay_ms(10000);
        humidity = analogRead(humiditySensor);
          if(humidity>750){
            turnOnPump();
          }else{
            digitalWrite(relay, LOW);
          }
      }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial.write(Serial.read());
  }
  while(Serial.available()) 
  {
    Serial.write(Serial.read());
  }
}