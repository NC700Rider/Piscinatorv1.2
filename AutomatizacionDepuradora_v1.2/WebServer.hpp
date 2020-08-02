AsyncWebServer server(80);

void inicializacionWebServer()
{
   server.serveStatic("/", SPIFFS, "/").setDefaultFile("main.html");
 
   server.on("/recibirDatos", HTTP_GET, enviarDatos);
   server.on("/enviarDatos", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, recibirDatos);
   server.on("/nuevaProgramacion", HTTP_POST, nuevaProgramacion);
   server.on("/cambioEstadoPrograma", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, cambioEstadoPrograma);
 
   server.onNotFound([](AsyncWebServerRequest *request) {
      request->send(400, "text/plain", "Not found");
   });
 
   server.begin();
    Serial.println("HTTP server started");
}
