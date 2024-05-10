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
bool relay1 = 0;
bool relay8 = 0;


NexButton b0 = NexButton(2, 7, "b0");
NexButton b1 = NexButton(2, 8, "b1");

NexTouch *nex_listen_list[] = 
{
    &b0,
    &b1,
    NULL
};


void toggle_relay(int relay_num) {
  if ( relay_num == 1) {
    if(relay1==0)
      {digitalWrite(RELAY_PIN_1, HIGH);}
    else if(relay1==1)
      {digitalWrite(RELAY_PIN_1, LOW );}
    relay1 = !relay1;
  }
  else if ( relay_num == 8) {
    if(relay8==0)
      {digitalWrite(RELAY_PIN_8, HIGH);}
    else if(relay8==1)
      {digitalWrite(RELAY_PIN_8, LOW );}
    relay8 = !relay8;
  }
}
void b0PopCallback(void *ptr)
{
    toggle_relay(1);
}
void b1PopCallback(void *ptr)
{
    toggle_relay(8);
}

void setup()
{
    Serial.begin(9600); //USB serial
    Serial1.begin(9600, SERIAL_8N1, 22, 23); // Nextion Device Serial rx = 22 , tx = 23
    delay(10);
    Serial.println("setup");

    nexInit();
    b0.attachPop(b0PopCallback, &b0); // links my custom pop function to b0 button
    b1.attachPop(b1PopCallback, &b1); // links my custom pop function to b1 button

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_8, OUTPUT);
    delay(100);

    //Turn off all relays
    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_8, LOW);

//Turn the relays on and off in turn
    digitalWrite(RELAY_PIN_1, HIGH);
    delay(500);

    digitalWrite(RELAY_PIN_1, LOW);

}

void loop()
{
    nexLoop(nex_listen_list);
}
