// Definición de salidas digitales
//#define achique 0       // Bomba de achique conectada al pin GPIO0
#define luz D5           // Luz conectada al pin GPIO2
//#define skimer 4        // Servo del Skimmer conectado al pin GPIO04
//#define sumidero 5      // Servo del Sumidero conectado al pin GPIO5
//#define limpiafondo 16  // Servo del Limpiafondo conectado al pin GPIO16
#define bomba D1        // Bomba conectada al pin GPIO14
#define clorador D2     // Clorador conectado al pin GPIO14

// Definición de entradas digitales
//#define inundacion 10;  // Detector de inundacion conectado al pin GPIO10

// Definición de entradas analógicas
//#define barometro A0;   // El detector de presión del circuito esta conectado al pin ADC0, se lee referenciando el puerto A0

//Definicion de la estructura de datos para retener la informacion de cada uno de los programas
typedef struct {
  bool estadoPrograma;
  bool estadoDepuradora;
  bool diasSemana[7];
  uint8_t horaArranque, minutoArranque, horaParada, minutoParada;
} programa_t;

/*Variable y costantes necesarias para el control de la depuradora*/
const uint8_t numProgramas = 4;              // Definimos el numero de programas a manejar
bool estadoDispositivos [] = {false, false, false, false}; // Arrya donde alamacenamos el estado de los dispositibos (Depuradora, Bomba, DepuradoraManual, Luz)
uint8_t cicloClorador = 0;             // Variable para saber si el clorador ha sido reiniciado
time_t segundosArranqueClorador = now(); //Variable que almacema los segundos a los que se arranco el clorador
programa_t programacion[numProgramas]; // Creacion del array para almacenar la programacion y sus estados
char diasSemana[] = {'L', 'M', 'X', 'J', 'V', 'S', 'D'}; //Dias de la semana
uint8_t i, prog ;                      // Variables utilizadas para ciclos for
bool isFSmount;                        // Si consigue montar el sistema de ficheros SPIFFS, isFSmount valdra true, si no sera false
unsigned int tiempoReconexion = 0;     //Variable para controlar cada cuanto tiempo pedimos la reconexion a la wifi

uint32_t tiempoConsole = millis();
