#include <Arduino.h>
#include <Nextion.h>

#define RELAY_PIN_1 33
#define RELAY_PIN_2 32
#define RELAY_PIN_3 13
#define RELAY_PIN_4 12
#define RELAY_PIN_5 21
#define RELAY_PIN_6 19
#define RELAY_PIN_7 18
#define RELAY_PIN_8 5
#define LED_PIN     25
#define MY_POT     27

String my_str = "";
long int start = 0;
long int pot_time = 0;
int pot_val = 0;
int pot_old_val = 0;
int prog_bar = 0;
void setup()
{
    Serial.begin(9600); //rx = 22 , tx = 23
    Serial1.begin(9600, SERIAL_8N1, 22, 23); //rx = 22 , tx = 23
    delay(10);
    Serial.println("setup");

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(MY_POT, INPUT);
    pinMode(RELAY_PIN_8, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    delay(100);

    //Turn off all relays
    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_8, LOW);
    digitalWrite(LED_PIN, LOW);

//Turn the relays on and off in turn
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_8, HIGH);
    delay(500);

    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_8, LOW);

}

void loop()
{
  if (Serial1.available() > 0) {
    start = millis();
    //read incoming byte
    my_str += char(Serial1.read());

    //print what was just read
    Serial.print("I recieved: ");
    Serial.println(my_str);
  }

  digitalRead(MY_POT);
  if(millis() - pot_time > 100) 
  {
    if (prog_bar >= 100) {
      prog_bar = 0;
    }
    prog_bar++;
    Serial1.print("j0.val=");
    Serial1.print(prog_bar);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
  }
  //error case where string is above 25 chars
  if (my_str.length() > 25) {
    my_str.clear();
  }
  // case where data hasn't been sent in 1 second.
  if (millis() - start > 5000) {
    my_str.clear();
  }



  if (my_str == "Turn off relay 1")
  {digitalWrite(RELAY_PIN_1, LOW);
  my_str = "";}
  else if (my_str == "Turn on relay 1")
  {digitalWrite(RELAY_PIN_1, HIGH);
  my_str = "";}
  else if (my_str == "Turn off relay 8")
  {digitalWrite(RELAY_PIN_8, LOW);
  my_str = "";}
  else if (my_str == "Turn on relay 8")
  {digitalWrite(RELAY_PIN_8, HIGH);
  my_str = "";}
}
