#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //Green LED
#define LED_R 4 //Red LED

float Total = 0;
float Last_add =0;
int a=0,b=0; 

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup()
{
Serial.begin(9600);  
SPI.begin();   
mfrc522.PCD_Init();  
lcd.begin();
lcd.backlight(); 
pinMode(LED_G, OUTPUT);
pinMode(LED_R, OUTPUT);


}
void loop()
{

if ( ! mfrc522.PICC_IsNewCardPresent())
{
lcd.setCursor(3,0);
lcd.print("Next Item : ");
lcd.setCursor(4,1);
lcd.print("Scanning...");
return;
}
else{
lcd.clear();
}
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
content.toUpperCase();

if (content.substring(1) == "70 33 7E 21") //New Customer Arrival 
{
  if(a==0)
  {
    lcd.print("Welcome to");
    lcd.setCursor(5,1);
    lcd.print("ABC Store");
    Total = 0;
    Last_add =0;
    a=a+1;
    digitalWrite(LED_G, HIGH);
    delay(2000);
    digitalWrite(LED_G, LOW);
    lcd.clear();
  }
  else if(a==1)
  {
    lcd.print("Total : ");
    lcd.print(Total);
    lcd.setCursor(0,1);
    lcd.print("Have  Good Day");
    Total = 0;
    Last_add =0;
    a=a+1;
    digitalWrite(LED_G, HIGH);
    delay(2000);
    Total = 0;
    digitalWrite(LED_G, LOW);
    lcd.clear();    
  }
  else 
  {
    a=0;
  }
}
else if (content.substring(1) == "73 B5 FD 2E") //Butter
{
lcd.print("Butter : 375.25");
lcd.setCursor(0,1);
Total = Total + 375.25;
Last_add = 375.25;
b=0;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_G, HIGH);
delay(3000);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "C1 15 02 1C") //Sugar
{
lcd.print("Sugar 1kg : 255.55");
lcd.setCursor(0,1);
Total = Total + 255.55;
Last_add = 255.55;
b=0;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_G, HIGH);
delay(3000);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "04 07 5B D2 9F 65 81") //Dhal 
{
lcd.print("Dhal 1kg : 420.12");
lcd.setCursor(0,1);
Total = Total + 420.12;
Last_add = 420.12;
b=0;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_G, HIGH);
delay(3000);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "04 F7 70 D2 9F 65 80") //Flour
{
lcd.print("Flour 1kg : 270.00");
lcd.setCursor(0,1);
Total = Total + 270.00;
Last_add = 270.00;
b=0;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_G, HIGH);
delay(3000);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "04 1F 7A D2 9F 65 81") //Rice
{
lcd.print("Rice 1kg : 230.00");
lcd.setCursor(0,1);
Total = Total + 230.00;
Last_add = 230.00;
b=0;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_G, HIGH);
delay(3000);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "04 78 A5 D2 9F 65 81") //Clear Card 
{
  if(b==0)
  {
lcd.print("Last Item Removed");
lcd.setCursor(0,1);
Total = Total - Last_add;
Last_add = 0;
b=b+1;
lcd.print("Total : ");
lcd.print(Total);
digitalWrite(LED_R, HIGH);
delay(3000);
digitalWrite(LED_R, LOW);
lcd.clear();    
  }
else
{
lcd.print("You only can ");
lcd.setCursor(1,1);
lcd.print("Remove one item");
digitalWrite(LED_R, HIGH);
delay(3000);
digitalWrite(LED_R, LOW);
lcd.clear();   
}
}
}
