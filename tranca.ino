#include <Servo.h>

//Programa: Leitor RFID RDM6300
//Alteracoes e adaptacoes: Arduino e Cia
//Baseado no programa original de Stephane Driussi
#include <SoftwareSerial.h>
#include <RDM6300.h>

//Inicializa a serial nos pinos 2 (RX) e 3 (TX)
SoftwareSerial RFID(3, 2);

int leds[2] = {5, 6};
int buzz = 13;

const int pinoServo = 4; //PINO DIGITAL UTILIZADO PELO SERVO

Servo s; //OBJETO DO TIPO SERVO

int code[5] = {46, 0, 36, 21, 109};
int hit = 0;

uint8_t Payload[6]; // used for read comparisons

RDM6300 RDM6300(Payload);


void setup()
{
  for (int i = 0; i < 2; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(buzz, OUTPUT);

  s.attach(pinoServo); //ASSOCIAÇÃO DO PINO DIGITAL AO OBJETO DO TIPO SERVO
  s.write(135); //INICIA O MOTOR NA POS

  //Inicializa a serial para o leitor RDM6300
  RFID.begin(9600);

  //Inicializa a serial para comunicacao com o PC
  Serial.begin(9600);

  //Informacoes iniciais
  Serial.println("Leitor RFID RDM6300n");
}
void loop()
{
  while (RFID.available() <= 0) {
    Serial.println(".");
    Serial.println("..");
  }

  //Aguarda a aproximacao da tag RFID
  while (RFID.available() > 0)
  {
    uint8_t c = RFID.read();
    if (RDM6300.decode(c))
    {
      //      for (int i = 0; i < 5; i++) {
      //        if (code[i] == Payload[i]) {
      //          hit++;
      //        }
      //      }

      if (code[0] == Payload[0] && code[1] == Payload[1] && code[2] == Payload[2] && code[3] == Payload[3] && code[4] == Payload[4]) {

        digitalWrite(leds[1], HIGH);

        tone(buzz, 700, 250);
        delay(250);
        tone(buzz, 900, 250);
        delay(500);

        digitalWrite(leds[1], LOW);

        s.write(45);

        //hit = 0;
      }
      else {


        digitalWrite(leds[0], HIGH);

        tone(buzz, 500, 250);
        delay(250);
        tone(buzz, 300, 250);
        delay(500);

        digitalWrite(leds[0], LOW);

        s.write(135);

        //hit = 0;
      }
    }

    delay(15);
  }
}
