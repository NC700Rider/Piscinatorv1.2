/* Este proyecto persigue la automatización de todas las funciones de una depuradora de piscina
    Las funciones a gestionar se iran incorporando en diferentes versiones. La agrupacion de funciones en diferentes versiones es como se describe a continuacion:
      V1.0
        Bomba
        Clorador Salino
        Luz
        Web Browser
      V2.0
        Manometro de presion de agua
      V3.0
*/

#include <TimeLib.h>;         //Añado la libreria de funciones de control de hora
#include <ESP8266WiFi.h>      //Añado la libreria de gestion del protocolo WiFi
#include <WiFiUdp.h>          //Añado la libreria de gestion del protocolo UDP sobre el que corre NTP
#include <ESPAsyncWebServer.h> //Libreria para web server asincrono
#include <ArduinoOTA.h>        //Libreria para la gestion On The Air
#include <FS.h>               // Libreria para usar SPIFFS
#include <ArduinoJson.h>      // Libreria para manejar objetos JSON
#include "utilidades.hpp"     //Fichero con funciones varias
#include "configWiFi.h"       // Fichero de configuracion de la red WiFi
#include "variablesConstantes.h" //Variable y Constantes generales
#include "ntp.hpp"  //Variable y funciones NTP
#include "OTA.hpp" //Funciones gestion On The Air
#include "controlDepuradora.hpp"  //Funciones para el control de la programacion
#include "gestionWiFi.hpp"  //Funciones para el control de la WiFi
#include "jsonParser.hpp"  //Funciones de gestion del fichero json
#include "restApi.hpp" //Funciones de la REST API
#include "WebServer.hpp"  //Funciones de gestion de Servidor Web

 

void setup() {

  //Inicialicacion de los puerto a utilizar
  pinMode(luz, OUTPUT);      // Configuracion del pin donde esta conectado la luz como salida
  pinMode(clorador, OUTPUT); // Configuracion del pin donde esta conectado el clorador como salida
  pinMode(bomba, OUTPUT);    // Configuracion del pin donde esta conectado la bomba como salida

  Serial.begin(115200);      //Inicializacion del puerto serie

  inicializacionWiFi(); // Inicializacion la conexion WiFi
  inicializacionFS();  //Inicializacion del file system  
  inicializacionWebServer();
  InitOTA();
  inicializacionNTP(); //Inicializacion y configuracion de la sincronizacion de hora por NTP

}

void loop() {

  //Comprobacion recurrente del estado de la conexion WiFi
  if (WiFi.status() != WL_CONNECTED)
    if (millis() > (tiempoReconexion+30000))
    {
      WiFi.reconnect();
      tiempoReconexion = millis();
    }

  ArduinoOTA.handle();
  controlCicloDepuracion(); //Gestion de los ciclos de programacion de la depuradora
  controlManualDispositivos();
}
