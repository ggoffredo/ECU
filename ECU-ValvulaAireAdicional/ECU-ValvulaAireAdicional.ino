/*
  Proyecto ECU

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Defino constantes
const int valvulaAireAdicional = 13;
const int sensorTempAgua = A0;

// Inicializo variables
int pAceite = 0;
int tAceite = 0;
int tAgua = 0;
float volt = 0.0;
int amp = 0;
String estadoValvulaAireAdicional = "";

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);

  pinMode(valvulaAireAdicional, OUTPUT);
}

void loop() {

  calcularValores();

  controlarValvulaAireAdicional();
  
  pantalla();

  delay(1000);
}


//Metodos privados

int calcularTempAgua(){
  // read the input on analog pin 0:
  return analogRead(sensorTempAgua)/10;
}

void controlarValvulaAireAdicional(){

  if(tAgua < 25 && digitalRead(valvulaAireAdicional) == LOW){
    digitalWrite(valvulaAireAdicional, HIGH);
    estadoValvulaAireAdicional = "ABIERTA";
  }
  if(tAgua >= 25 && digitalRead(valvulaAireAdicional) == HIGH){
    digitalWrite(valvulaAireAdicional, LOW);
    estadoValvulaAireAdicional = "CERRADA";
  }
}

void calcularValores(){
  tAgua = calcularTempAgua();
}

void pantalla(){
    
  // TEMPERATURA DE AGUA
  lcd.setCursor(0, 0);
  lcd.print("TEMP. AGUA: ");
  lcd.print(tAgua);

  // ESTADO VAA
  lcd.setCursor(0, 2);
  lcd.print("VAA: ");
  lcd.print(estadoValvulaAireAdicional);

}

