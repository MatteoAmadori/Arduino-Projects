/*      pin:
 *       Vcc - 5V
 *       Gnd - Gnd
 *      Echo - 22
 *      Trig - 2
 *      
 *      Misuratore utilizzabile solo in casi dove il periodo del pendolo è maggiore di 0,3s (300ms)
 */


#include <SPI.h> 
#include <SD.h>
const int chipSelect = 53;  
const int echoPin = 22;
const int trigPin = 2;
long duration;
int distance;
byte state;
float t10 [10];
int t10Row;
unsigned long prevTime;
unsigned long prevTime2;
unsigned long t;
float errore;
float tbest;
float maxT;
float minT;

void setup() {
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Serial.begin(9600);
// if (!SD.begin(chipSelect)) {
//    Serial.println("Card failed, or not present");
//    while (1);
//  }
 state = 0;
 t10Row = 0;
}

void loop() {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
// Serial.print("Distance: ");
// Serial.print(distance);
// Serial.print("    state: ");
// Serial.print(state);
// Serial.print("    Time: ");
// Serial.println(t);

 if(distance < 15 && state == 0){
   prevTime = millis();
   state = 1;
 }else if(distance < 15 && state == 1 && (millis() - prevTime) > 300){
    state = 2;
    prevTime2 = millis();
 }else if(distance < 15 && state == 2 && (millis() - prevTime2) > 300){
    state = 0;
    t = millis() - prevTime;
    t10[t10Row] = t;
    t10Row++;
    Serial.print("Periodo: ");
    Serial.print(t);
    Serial.println("ms");
    t = 0;
    if(t10Row == 10){
      tbest= (t10[0] + t10[1] + t10[2] + t10[3] + t10[4] + t10[5] + t10[6] + t10[7] + t10[8] + t10[9]) / 10;
      maxT = t10[0];
      minT = t10[0];
      for(int i = 1; i < 10; i++){
        maxT = max(maxT, t10[i]);
        minT = min(minT, t10[i]);
        
//        if(t10[i] > maxT){
//          maxT = t10[i];}
//        if(t10[i] < minT){
//          minT = t10[i];}
      }
      errore = (maxT - minT)/2;
      Serial.print("t: ");
      Serial.print(tbest);
      Serial.print("±");
      Serial.print(errore);
      Serial.println("ms");
//      Serial.print("max t:");
//      Serial.print(maxT);
//      Serial.println("ms");
//      Serial.print("min t:");
//      Serial.print(minT);
//      Serial.println("ms"); 
      while(1);    
    }



    
//    for(int i = 0; i < 10; i++){
//      Serial.println(t10[i]);
//    }
//    if(t10Row == 11){
//      File dataFile = SD.open("datalog.txt", FILE_WRITE);                                                 //stampiamo sulla schedina SD la temperatura, l'umidità e la pressione
//    if(dataFile){  
//      for(int i = 0; i < 10; i++){
//        dataFile.println(t10[i]);
//      }
//      dataFile.close();
//    }else {
//      Serial.println("error opening datalog.txt");
//    }
//  }
    }
 }
 
