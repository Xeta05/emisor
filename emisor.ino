
/*
EMISOR
 
Envia los mensajes "Apagar" y "Encender" en intervalos de un segundo
 
Escrito por Nano en beneficio de los seres humanos
www.robologs.net
*/
 
#include <VirtualWire.h>
#include <LowPower.h>
#include "DHT.h"          // DHT & AM2302 library


// Data pin connected to AM2302
#define DHTPIN 2
#define TEMPMAX 20
#define DHTTYPE DHT22       // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);   //
void setup()
{
  //Iniciamos el Serial y la comunicacion por radio
  Serial.begin(9600);
  Serial.write("Sistema encendido\n");
  vw_setup(2000);
  dht.begin();
}
void loop()
{  
  float temp = dht.readTemperature();
  char msg[24];
  if (isnan(temp) ) {
    Serial.write("Failed to read from DHT");
  }
  else{
   // Serial.write("Temperatura:");
   // Serial.println(temp,DEC);
    int temp1 = (int)temp;
    int temp2 = (int)((temp - temp1) * 100.0); // For two decimal points
    sprintf(msg, "%i.%i", temp1,temp2);
    send(msg);
   // Serial.println(msg);
  }
  
  
  // Wait 3 seconds
 // delay(2000);
 LowPower.powerDown(SLEEP_4S, ADC_OFF,BOD_OFF);
}
 
//Funcion para enviar el mensaje
void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo
  
  Serial.println(message); //Muestra el mensaje por Serial
}
