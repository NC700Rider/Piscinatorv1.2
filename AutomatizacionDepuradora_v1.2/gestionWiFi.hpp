//Inicializacion de la connexion WiFi
void inicializacionWiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet, dns);
  WiFi.begin(ssid, pass);
  for ( i = 0; WiFi.status() != WL_CONNECTED && i < 600 ; i++) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
	  Serial.print("\nConectado a WiFi");
}
