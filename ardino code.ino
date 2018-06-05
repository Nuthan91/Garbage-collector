#include <NewPing.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
LiquidCrystal lcd(3, 4, 5, 6, 7, 8); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
#define SSID "KALAIVANI S2"   // SSID
#define PASS "ponnis@123"      // Network Password
#define MAX_DISTANCE 30
#define HOST "139.59.94.239"  // Webhost

char data;
const int trigPin = 9;
const int echoPin = 10;
int led_p=13;
int led_n=12;
int Vee=11;
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
long duration;
int distanceCm, distanceInch;
void setup()
{   
    lcd.begin(16, 2);   
    pinMode(led_p, OUTPUT); 
  pinMode(led_n, OUTPUT);
  pinMode(Vee, OUTPUT);
  digitalWrite(Vee,HIGH);
  digitalWrite(led_p,HIGH); 
  digitalWrite(led_n,LOW);  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(115200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  Serial.println("AT");
  delay(5000);
  if (Serial.available()>0) 
  {
    if(connectWiFi()==true)
    {
      Serial.println("wifi connected successfully");
    }
  }
}


void loop() {
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
//lcd.print("Distance: "); // Prints string "Distance" on the LCD
//lcd.print(distanceCm); // Prints the distance value from the sensor
//lcd.print(" cm");
//delay(10);
//lcd.setCursor(0,1);
//lcd.print("Distance: ");
//lcd.print(distanceInch);
//lcd.print(" inch");
//delay(10);

sendData(String(distanceCm),String(529568));
delay(1000);
delay(500);                      
  unsigned int uS = sonar.ping(); 
 
  lcd.print(" ");
  lcd.print(sonar.convert_cm(uS)); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  lcd.println("cm");
lcd.setCursor(0,0);

if (uS == 0 && digitalRead(echoPin) == HIGH) 

{
    lcd.setCursor(1,1);
   
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
      lcd.print("clear dustbin"); 
  
    lcd.setCursor(0,0);
    delay(100);
    pinMode(echoPin, INPUT);    
  }  
}


void sendData(String uss, String code) {

  Serial.println("webhost...");
  // Set up TCP connection.
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += HOST;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  // Send data.
  cmd = "GET /data.php?l=";  
  cmd += uss;
  cmd += "&code=";
  cmd += code;
  cmd += " HTTP/1.1\r\nHost: ";
  cmd += HOST;
  cmd += "\r\n\r\n\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  //Serial.println("Webhost Send");
  if (Serial.find(">")) {
    Serial.print(cmd);
  }
  delay(1000);  
  Serial.println("AT+CIPCLOSE");
}


boolean connectWiFi() {
  Serial.println("AT+CWMODE=3");
  delay(2000);
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  Serial.println(cmd);
  delay(5000);
  if (Serial.find("OK")) {
    return true;
  }
  else {
    return false;
  }
}
