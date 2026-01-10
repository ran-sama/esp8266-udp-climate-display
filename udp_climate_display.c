#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

int values;
const int rck = 4;
const int sck = 12;
const int dio = 14;
char incomingPacket[255];
unsigned int localUdpPort = 8888;
const char* ssid = "name";
const char* password = "password";


byte col[] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000
};

byte seg[] = {
    0b11000000,  // 0
    0b11111001,  // 1
    0b10100100,  // 2
    0b10110000,  // 3
    0b10011001,  // 4
    0b10010010,  // 5
    0b10000010,  // 6
    0b11111000,  // 7
    0b10000000,  // 8
    0b10010000,  // 9
    0b11000110,  // C
    0b10011100,  // degree
    0b10100011,  // percent
};     

int segcnt = 0;
int tester[] = {0, 0, 11, 10, 0, 0, 11, 12};

void LED_irq(void){
    digitalWrite(rck, LOW);
    shiftOut(dio, sck, MSBFIRST, col[segcnt]);
    shiftOut(dio, sck, MSBFIRST, seg[tester[segcnt]]);
    digitalWrite(rck, HIGH);
    segcnt ++;
    segcnt &= 7;
}

void setup(){
    pinMode(rck, OUTPUT);
    pinMode(sck, OUTPUT);
    pinMode(dio, OUTPUT);
    WiFi.begin(ssid, password);
    Udp.begin(localUdpPort);
    timer1_isr_init();
    timer1_attachInterrupt(LED_irq);
    timer1_enable(TIM_DIV16, 0, 1);
    timer1_write((clockCyclesPerMicrosecond() / 16) * 2000);
}

void loop(){
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    values = atoi(incomingPacket);
    tester[0] = ((values / 1000) % 10);
    tester[1] = ((values / 100) % 10);
    tester[4] = ((values / 10) % 10);
    tester[5] = (values % 10);
  }
}
