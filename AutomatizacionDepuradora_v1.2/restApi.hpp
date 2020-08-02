#include "Utils_APIREST.hpp"

void cambioEstadoPrograma(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String datos = GetBodyContent(data, len);
  StaticJsonDocument<200> variablesEntrada;
  DeserializationError error = deserializeJson(variablesEntrada, datos);
  if (error) { request->send(400); return;}
  uint8_t numPrograma = atol(variablesEntrada["programa"]);
  bool estadoPrograma = variablesEntrada["estado"];
  programacion[numPrograma].estadoPrograma = estadoPrograma;
  
  Serial.print("\nVariable numPrograma: ");
  Serial.print(numPrograma);
  Serial.print("\nVariable estadoPrograma: ");
  Serial.print(estadoPrograma);
  Serial.print("\nVariable programacio.estadoPrograma: ");
  Serial.print(programacion[numPrograma].estadoPrograma);
  Serial.print("\n--------------------------------\n");
  request->send(200);
  
}

void nuevaProgramacion(AsyncWebServerRequest *request)
{
  String numPrograma = request->arg("programa");
  uint16_t minutosAbsoltosArranque = (((request->arg("horaArranque").toInt()) * 60) + (request->arg("minutoArranque").toInt()));
  uint16_t minutosAbsoltosParada = (((request->arg("horaParada").toInt()) * 60) + (request->arg("minutoParada").toInt()));
  if ( minutosAbsoltosArranque >= minutosAbsoltosParada)
  {
    String response = "<h1>La hora de arranque es anterior o igual a la hora de parada</h1><h2>Por favor, intentelo de nuevo</h2><p><a href='/'> Go Back </a></p>";
    request->send(200, "text/html", response);
    return;
  }
  prog = numPrograma.toInt();
  if (prog == 0)
  {
    String response = "<h1>El Numero de programa es incorrecto</h1><h2>Por favor, intentelo de nuevo</h2><p><a href='/'> Go Back </a></p>";
    request->send(200, "text/html", response);
    return;
  }
  
  prog--;
  i = 0;
  if ( request->arg("L") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("M") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("X") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("J") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("V") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("S") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
  if ( request->arg("D") == "Y")
    programacion[prog].diasSemana[i++] = true;
  else
    programacion[prog].diasSemana[i++] = false;
    
  programacion[prog].horaArranque = request->arg("horaArranque").toInt();
  programacion[prog].minutoArranque = request->arg("minutoArranque").toInt();
  programacion[prog].horaParada = request->arg("horaParada").toInt();
  programacion[prog].minutoParada = request->arg("minutoParada").toInt();
  programacion[prog].estadoPrograma = true ;
  
  String response = "<h1>Nueva Programacion Guardada Correctamente</h1><p><a href='/'> Go Back </a></p>";
  request->send(200, "text/html", response);
 
}

void enviarDatos(AsyncWebServerRequest *request)
{
   AsyncResponseStream *response = request->beginResponseStream("application/json");
         
   StaticJsonDocument<2048> datos;
   datos["dia"] = int2Digits(day());
   datos["mes"] = int2Digits(month());
   datos["ano"] = year();
   datos["hora"] = int2Digits(hour());
   datos["minuto"] = int2Digits(minute());
   datos["segundo"] = int2Digits(second());
   datos["depuradora"] = estadoDispositivos[0];
   datos["bomba"] = estadoDispositivos[1];
   datos["depuradora"] = estadoDispositivos[2];
   datos["luz"] = estadoDispositivos[3];
   JsonObject obj1 = datos.createNestedObject("programa1");
   obj1["lunes"] = programacion[0].diasSemana[0] ? String("L") : String("-");
   obj1["martes"] = programacion[0].diasSemana[1] ? String("M") : String("-");
   obj1["miercoles"] = programacion[0].diasSemana[2] ? String("X") : String("-");
   obj1["jueves"] = programacion[0].diasSemana[3] ? String("J") : String("-");
   obj1["viernes"] = programacion[0].diasSemana[4] ? String("V") : String("-");
   obj1["sabado"] = programacion[0].diasSemana[5] ? String("S") : String("-");
   obj1["domingo"] = programacion[0].diasSemana[6] ? String("D") : String("-");
   obj1["horaArranque"] = horaFormatoReloj( programacion[0].horaArranque, programacion[0].minutoArranque );
   obj1["horaParada"] = horaFormatoReloj( programacion[0].horaParada, programacion[0].minutoParada );
   obj1["estadoDepuradora"] = programacion[0].estadoDepuradora;
   obj1["estadoPrograma"] = programacion[0].estadoPrograma;
   JsonObject obj2 = datos.createNestedObject("programa2");
   obj2["lunes"] = programacion[1].diasSemana[0] ? String("L") : String("-");
   obj2["martes"] = programacion[1].diasSemana[1] ? String("M") : String("-");
   obj2["miercoles"] = programacion[1].diasSemana[2] ? String("X") : String("-");
   obj2["jueves"] = programacion[1].diasSemana[3] ? String("J") : String("-");
   obj2["viernes"] = programacion[1].diasSemana[4] ? String("V") : String("-");
   obj2["sabado"] = programacion[1].diasSemana[5] ? String("S") : String("-");
   obj2["domingo"] = programacion[1].diasSemana[6] ? String("D") : String("-");
   obj2["horaArranque"] = horaFormatoReloj( programacion[1].horaArranque, programacion[1].minutoArranque );
   obj2["horaParada"] = horaFormatoReloj( programacion[1].horaParada, programacion[1].minutoParada );
   obj2["estadoDepuradora"] = programacion[1].estadoDepuradora;
   obj2["estadoPrograma"] = programacion[1].estadoPrograma;
   JsonObject obj3 = datos.createNestedObject("programa3");
   obj3["lunes"] = programacion[2].diasSemana[0] ? String("L") : String("-");
   obj3["martes"] = programacion[2].diasSemana[1] ? String("M") : String("-");
   obj3["miercoles"] = programacion[2].diasSemana[2]? String("X") : String("-");
   obj3["jueves"] = programacion[2].diasSemana[3] ? String("J") : String("-");;
   obj3["viernes"] = programacion[2].diasSemana[4] ? String("V") : String("-");
   obj3["sabado"] = programacion[2].diasSemana[5] ? String("S") : String("-");
   obj3["domingo"] = programacion[2].diasSemana[6] ? String("D") : String("-");
   obj3["horaArranque"] = horaFormatoReloj( programacion[2].horaArranque, programacion[2].minutoArranque );
   obj3["horaParada"] = horaFormatoReloj( programacion[2].horaParada, programacion[2].minutoParada );
   obj3["estadoDepuradora"] = programacion[2].estadoDepuradora;
   obj3["estadoPrograma"] = programacion[2].estadoPrograma;
   JsonObject obj4 = datos.createNestedObject("programa4");
   obj4["lunes"] = programacion[3].diasSemana[0] ? String("L") : String("-");
   obj4["martes"] = programacion[3].diasSemana[1] ? String("M") : String("-");
   obj4["miercoles"] = programacion[3].diasSemana[2] ? String("X") : String("-");
   obj4["jueves"] = programacion[3].diasSemana[3] ? String("J") : String("-");
   obj4["viernes"] = programacion[3].diasSemana[4]  ? String("V") : String("-");
   obj4["sabado"] = programacion[3].diasSemana[5] ? String("S") : String("-");
   obj4["domingo"] = programacion[3].diasSemana[6] ? String("D") : String("-");
   obj4["horaArranque"] = horaFormatoReloj( programacion[3].horaArranque, programacion[3].minutoArranque );
   obj4["horaParada"] = horaFormatoReloj( programacion[3].horaParada, programacion[3].minutoParada );
   obj4["estadoDepuradora"] = programacion[3].estadoDepuradora;
   obj4["estadoPrograma"] = programacion[3].estadoPrograma;

   serializeJson(datos, *response);
   request->send(response);
}

void recibirDatos(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
 
 String datos = GetBodyContent(data, len);
 StaticJsonDocument<200> datosDispositivo;
  DeserializationError error = deserializeJson(datosDispositivo, datos);
  if (error) { request->send(400); return;}
 
  String id = datosDispositivo["dispositivo"];
  bool ledStatus = datosDispositivo["estado"];
  Serial.println(id);
  Serial.println(ledStatus);
  if ( datosDispositivo["dispositivo"] == "switchButtonBomba")
    estadoDispositivos[1] = datosDispositivo["estado"];
if ( datosDispositivo["dispositivo"] == "switchButtonDepuradora")
    estadoDispositivos[2] = datosDispositivo["estado"];
if ( datosDispositivo["dispositivo"] == "switchButtonLuz")
    estadoDispositivos[3] = datosDispositivo["estado"];
  request->send(200);


 /* 
 Serial.print(estado);
 Serial.print("Clorador");

 if (estado == "On")
  digitalWrite(D2, HIGH);
 if (estado == "Off")
  digitalWrite(D2, LOW);
 request->redirect("/");
 */
}
