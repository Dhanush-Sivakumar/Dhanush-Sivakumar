#include <Keypad.h>

#define Password_Length 4
char Data[Password_Length + 1] = {0}; 
const int relay = 13;
const int AO_Pin=A0;
int AO_Out;
int buzzer = 10;
int IRSensor = 11;
int LED = 12;

byte data_count = 0;
char customKey;
char myPassword[] = "1245";  

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] =  
{
  {'1', '2', '3','A'},
  {'4', '5', '6','B'},
  {'7', '8', '9','C'},
  {'*', '0', '#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8,9};  

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(AO_Pin, INPUT); 
  pinMode(IRSensor, INPUT); 
  pinMode(LED, OUTPUT); 
  Serial.begin(9600);
  digitalWrite(13, HIGH);
}

void loop()   
{  
  customKey = customKeypad.getKey();
  if (customKey != 0x00)
  {
    Data[data_count] = customKey;
    Serial.print(Data[data_count]);
    data_count++;
    if (data_count == 4)
    {
      Serial.println();  
      if (strcmp(myPassword, Data) == 0) 
      {  
        Serial.println("CORRECT PASSWORD");
        AO_Out= analogRead(AO_Pin);
        Serial.println(AO_Out);
        if(AO_Out<=490){        //IF VALUE above 490 ALCOHOL SMELL
        digitalWrite(13, LOW);
        digitalWrite(10, LOW);
        int sensorStatus = digitalRead(IRSensor); 
        Serial.println(sensorStatus);
        if (sensorStatus == 0) 
        {
        digitalWrite(LED, HIGH); 
        Serial.println("Motion Detected!"); 
        data_count = 0;   
        memset(Data, 0, 5); 
        }
        else  {
    
        digitalWrite(LED, LOW); 
        Serial.println("Motion Ended!");
        data_count = 0;   
        memset(Data, 0, 5); 
        }
      } else{
         Serial.println("ALCOHOL SMELL DETECTED ");
         digitalWrite(13, HIGH);
         Serial.println("VEHICLE STOPED ");
         digitalWrite(10, HIGH);
         delay(1000);
         digitalWrite(10, LOW);
         delay(1000);
         digitalWrite(10, HIGH);
         delay(1000);
         digitalWrite(10, LOW);
         delay(1000);
         digitalWrite(10, HIGH);
         delay(1000);
         digitalWrite(10, LOW);
         delay(1000);
         digitalWrite(10, HIGH);
         delay(1000);
         digitalWrite(10, LOW);
         delay(1000);
         digitalWrite(10, HIGH);
         delay(1000);
         digitalWrite(10, LOW);
         data_count = 0;   
         memset(Data, 0, 5); 
      }
      }
      else{
        Serial.println("WRONG PASSWORD");
        digitalWrite(10, HIGH);
        digitalWrite(13, HIGH);
        data_count = 0;   
        memset(Data, 0, 5); 
      }
    }
  }
}
