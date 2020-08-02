//Funciones de gestion de la depuradora
//--------------------------------------------------------
void controlCicloDepuracion(){
    bool estadoProgramas = false; //Variable que nos almacena el estado en el que debe estar la depuradora como resultado del analisis de las horas de programadas
    for (prog = 0; prog < numProgramas; prog++) {
      uint8_t diaSemana = weekday() - 2;
      if (diaSemana == 255)
        diaSemana = 7;
      uint16_t horaActual = hour() * 60 + minute();
      if (programacion[prog].estadoPrograma == false )
        programacion[prog].estadoDepuradora = false ;
     
      if (  millis() > (tiempoConsole + 1000) )
      {
        Serial.print("\nHora de Arranque Normalizada: ");
        Serial.print(programacion[prog].horaArranque * 60 + programacion[prog].minutoArranque);
        Serial.print("\nHora de Parada Normalizada: ");
        Serial.print(programacion[prog].horaParada * 60 + programacion[prog].minutoParada);
        Serial.print("\nHora de Actual Normalizada: ");
        Serial.print(horaActual);
        Serial.print("\n---------------------------------------------------------------------\n");
        tiempoConsole = millis();
      }
        
      if (programacion[prog].diasSemana[diaSemana] == true && programacion[prog].estadoPrograma == true ) { //Comprobacion de si el dia en el que estamos hay que encender la depuradora y el programa esta activo
        uint16_t horaArranque=programacion[prog].horaArranque * 60 + programacion[prog].minutoArranque; //Calculo del momento de arranque en minutos desde las 00:00 del dia actual
        uint16_t horaParada=programacion[prog].horaParada * 60 + programacion[prog].minutoParada; //Calculo del momento de parada en minutos desde las 00:00 del dia actual
        if (horaActual >= horaArranque && horaActual < horaParada){
          programacion[prog].estadoDepuradora = true;
        }      
        if (horaActual >= horaParada){
          programacion[prog].estadoDepuradora = false;
        }
     }
     estadoProgramas =  estadoProgramas || programacion[prog].estadoDepuradora ;
    }

    if (estadoDispositivos[0] == false && estadoProgramas == true) {
      digitalWrite(bomba, HIGH); //Arrancamos la bomba de filtracion
      digitalWrite(clorador,HIGH); //Arranca el clorador
      cicloClorador = 1;
      segundosArranqueClorador = now(); //millis();
      estadoDispositivos[0] = true;
    }
	
    if (estadoDispositivos[0] == true && estadoProgramas== false) {
      if (estadoDispositivos[1] == false && estadoDispositivos[2] == false) //Comprobamos si la bomba no ha sido encendida manualmente ni la depuradora y en tal caso no se debe parar
      digitalWrite(bomba, LOW); //Paramos la bomba de filtracion
      if (estadoDispositivos[2] == false) //Comprobamos si la depuradora ha sido encendida manualmente y en tal caso no se debe parar
      digitalWrite(clorador,LOW); //Parar el clorador
      cicloClorador = 0;
      estadoDispositivos[0] = false;
    }
	
    if (cicloClorador == 1 && now() > (segundosArranqueClorador + 10)){ //Paramos el clorador 10 segundos despues de haberlo arrancado
      digitalWrite(clorador,LOW); //Para el clorador
      cicloClorador = 2;
    }
    if (cicloClorador == 2 && now() > (segundosArranqueClorador + 20)){ //Arrancamos el clorador 10 segundos despues de haberlo parado para completar el ciclo de "cebado"
      digitalWrite(clorador,HIGH); //Arranca el clorador
      cicloClorador = 3;
    }
}

void controlManualDispositivos()
{
    if (estadoDispositivos[1] == true && estadoDispositivos[0] == false)
      digitalWrite(bomba, HIGH); //Arrancamos la bomba de filtracion
    if (estadoDispositivos[2] == true && estadoDispositivos[0] == false && cicloClorador == 0) {
      digitalWrite(bomba, HIGH); //Arrancamos la bomba de filtracion
      digitalWrite(clorador,HIGH); //Arranca el clorador
      cicloClorador = 1;
      segundosArranqueClorador = now();
    }
    if (estadoDispositivos[3] == true)
      digitalWrite(luz, HIGH); //Encendemos la luz
    if (estadoDispositivos[2] == false && estadoDispositivos[1] == false && estadoDispositivos[0] == false)
      digitalWrite(bomba, LOW); //Parar la bomba de filtracion
    if (estadoDispositivos[2] == false && estadoDispositivos[0] == false) {
      if (estadoDispositivos[1] == false)
        digitalWrite(bomba, LOW); //Parar la bomba de filtracion
      digitalWrite(clorador,LOW); //Parar el clorador
      cicloClorador = 0;
    }
    if (estadoDispositivos[3] == false)
      digitalWrite(luz, LOW); //Apagamos la luz
}
//Fin funciones de gestion de la depuradora
//------------------------------------------------------------
