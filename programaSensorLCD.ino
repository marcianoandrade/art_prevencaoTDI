#include <SD.h>
#include <LiquidCrystal.h>    
#include <virtuabotixRTC.h>
#include <string.h>

File file;
virtuabotixRTC relogio(6,7,8);
LiquidCrystal lcd(0,1,2,3,4,5);
const int SDPin = 10;
String hora = "";
String data = "";
int quantidadeLeituras = 20;
const int pinoSensor = A5;

void setup(){
  pinMode(SDPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.home(); 
  if (!SD.begin(SDPin)) {
    lcd.print("SD NOT");
    delay(2000);
  }
  else {    
    lcd.print("SD YES");
    delay(2000);
  }
}

void loop(){
  relogio.updateTime(); 
  String dia = String(relogio.dayofmonth);
  data = dia + "/" + String(relogio.month) + "/17";
  if (relogio.hours < 10)
  {
    hora = "0";
    hora = hora + relogio.hours;
  }    
  else{
    hora = relogio.hours;
  }
  hora = hora + ":" ;
  if (relogio.minutes < 10)
  {
    hora = hora + "0";
  }
  hora = hora + relogio.minutes;
  hora = hora + ":";    
  if (relogio.seconds < 10)
  {
    hora = hora + "0";
  }
  hora = hora + relogio.seconds;  
  int totalSensor = 0;
  int contador = 0;
  for(int i=0;i<quantidadeLeituras;i++){
    totalSensor += analogRead(pinoSensor);
    contador++;
  }
  int analogSensor = totalSensor/contador;
  lcd.home();  
  lcd.clear();
  lcd.print("Vlr:");
  lcd.print(analogSensor);
  lcd.print(" ");
  file = SD.open("leitura_"+dia+".csv", FILE_WRITE);
  lcd.print(file.size());
  lcd.setCursor(0, 1);
  lcd.print(data);
  lcd.print(" ");
  lcd.print(hora);
  file.println(String(analogSensor)+";"+data+";"+hora);
  file.close(); // close file
  delay(900); 
}
