
void setProgramacionDefecto() {
  // Inicializacion de array de la programacion
  for (prog = 0; prog < numProgramas; prog++) {
    programacion[prog].estadoPrograma = false;
    for ( i = 0; i < 7; i++)
      programacion[prog].diasSemana[i] = false;
    programacion[prog].horaArranque = 0;
    programacion[prog].minutoArranque = 0;
    programacion[prog].horaParada = 0;
    programacion[prog].minutoParada = 0;
  }

    programacion[0].estadoPrograma = true;
    for ( i = 0; i < 7; i++)
      programacion[0].diasSemana[i] = true;
    programacion[0].horaArranque = 10;
    programacion[0].minutoArranque = 0;
    programacion[0].horaParada = 12;
    programacion[0].minutoParada = 0;
}

bool readJsonProgramacion() {
  // Abriendo el fichero JSON de la programacion
  File progFile = SPIFFS.open("/programacion.json", "r");
  if (!progFile) {
    Serial.println("\nError: al leer el fichero de programacion");
    return false;
  }

  // Allocate the memory pool on the stack.
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t bufferSize = JSON_ARRAY_SIZE(4) + 4 * JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(2) + 4 * JSON_OBJECT_SIZE(6) + 330;
  DynamicJsonDocument doc(bufferSize);

  // Deserializa el fichrero programacion.json y lo mete en el objeto doc
  DeserializationError error = deserializeJson(doc, progFile);

  if (error) {
    Serial.print("deserializeJson() ha fallado con el codigo");
    Serial.println(error.c_str());
    return false;
  }
  //numProgramas=doc["numProg"]; Lo comento porque da un error, para definir el array necesita una constante
  for (prog = 0; prog < numProgramas; prog++) {
    programacion[prog].estadoPrograma = doc["programas"][prog]["estadoPrograma"].as<bool>();
    for ( i = 0; i < 7; i++)
      programacion[prog].diasSemana[i] = doc["programas"][prog]["diasSemana"][i].as<bool>();
    programacion[prog].horaArranque = doc["programas"][prog]["horaArranque"].as<int>();
    programacion[prog].minutoArranque = doc["programas"][prog]["minutoArranque"].as<int>();
    programacion[prog].horaParada = doc["programas"][prog]["horaParada"].as<int>();
    programacion[prog].minutoParada = doc["programas"][prog]["minutoParada"].as<int>();
  }
  progFile.close();
  return true;
}

void inicializacionFS() { // Iniciando el sistema de ficheros SPIFFS

  Serial.println("\nMontando FS...");
  isFSmount = SPIFFS.begin();
  if (isFSmount) {
    if (! readJsonProgramacion())
      setProgramacionDefecto();
  } else {
    Serial.println("\nError al montar el sistema de ficheros");
    setProgramacionDefecto();
  }
}
