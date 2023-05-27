#include <Arduino.h>
#include <HardwareSerial.h>
#include <Servo.h>

#include "Button.h"
#include "Ramp.h"

void carPassed();
void carEntered();
void onClickButton();

Servo servo;
Ramp rampa(&servo, PB1, PE8, &carEntered, &carPassed);
Button dugme(PB3, 5, &onClickButton);

void setup()
{
  Serial.begin(115200);
  Serial.println("Program started");
  pinMode(PD13, OUTPUT);
  servo.attach(PB0);
}
bool state = false;

void loop()
{


  dugme.run();

  static uint32_t lastTimestamp2 = 0;
  uint32_t elapsed2 = millis() - lastTimestamp2;
  if (elapsed2 > 100)
  {
    rampa.run();
    lastTimestamp2 = millis();
  }
}

void carEntered()
{

  static int counter1 = 0;
  counter1++;

  Serial.print("auto je doslo ");
  Serial.print(counter1);
  Serial.println(" puta");
}

void carPassed()
{

  static int counter2 = 0;
  counter2++;

  Serial.print("auto je proslo na rampi");
  Serial.print(counter2);
  Serial.println(" puta");
  rampa.close_ramp();
}

void onClickButton()
{
  static int counter = 0;
  counter++;

  Serial.print("Klik 1 detektovan ");
  Serial.print(counter);
  Serial.println(" puta");

  if (!rampa.get_car_on_rump())
  {
    rampa.open_ramp();
  }
}
