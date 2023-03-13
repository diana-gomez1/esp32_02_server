#include <Arduino.h>
#include "libwifi.h"
#include "Wifi.h"

const char * ssid = "ASUSDCGG";
const char * password = "3164173706Cc";
const char * host = "dweet.io";
const int puerto = 80;
WiFiServer servidor(puerto);//Construimos objeto tipo servidor TCP
//String server="dweet.io"; es redundante con host 
String url="/dweet.io/dweet/for/uceva02?temperatura=32.5";
 


//@author Diana Gomez
/**
 * @brief Esta es la funcion de configuracion del dispositivo
 * 
 * 
*/

 void setup() {
 pinMode(2,OUTPUT); //Coloco el pin 2 como salida
 Serial.begin(115200);
 Serial.println("Inicializando el dispositivo");
 conectarWifi(ssid, password);
 servidor.begin();//Inicializamos el servidor tcp

}
/**
 * @brief Esta funcion con bucle infinito
 prueba
*/
void loop() {
  WiFiClient cliente = servidor.available();//Devolvemos cliente TCP por wifi conectado a servidor
  //paso 1 : Si existe un cliente conectado
  if (cliente){
    Serial.println("Se conecto un cliente");
  //paso 2 : mientras el cliente este conectado reciba peticiones (request)
  while (cliente.connected()){
      String mensaje="";
      if(cliente.available()){//paso 3 ; verifico si el cliente nos ha enviado un caracter
        char letra = cliente.read();//paso 4: leemos el caracter
        Serial.print(letra);
        if(letra=='\n'){//si el caracter es un enter (\n\r: ox10 0x13)
          //paso 6 : devolvemos una respuesta (response)
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-typer:text/html");
          cliente.println();//enviamos linea vacia indiica que la cabecera finalizo cabecera 47/48
          //string variable = "<a href=\"/H\">aqui </a>"; se coloca caracter escape (\")
          cliente.println("Haga click <a href=\"/H\">aqui</a> para encender el LED");
          cliente.println("Haga click <a href=\"/L\">aqui</a>para apagar el LED");
          cliente.println();//finalizamos el envio del cuerpo (body) de la pagina
          break;
        }else{
          if(letra != '\r')
          mensaje += letra;//paso 5 : Concatenamos cada caracter que esta llegando en mensaje
        }
      }
  }
  
  }
     
  
}

