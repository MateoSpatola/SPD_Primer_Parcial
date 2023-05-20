//Primer Parcial SPD | Parte Práctica Domiciliaria

//Alumno: Mateo Spatola
//Division: 1D

//Enunciado:
/*
https://drive.google.com/file/d/1Sw-SRcPhOr7WwCJGMePt5Ni875fzqPKj/view
*/

//Leds display 7 segmentos
#define LED_A 12
#define LED_B 13
#define LED_C 7
#define LED_D 8
#define LED_E 9
#define LED_F 11
#define LED_G 10

//Leds encendido/apagado
#define LED_VERDE 3
#define LED_ROJO 2

//Pulsadores
#define BOTON_SUBIR 6
#define BOTON_DETENER 5
#define BOTON_BAJAR 4

bool flagLedVerdeEncendido;
bool flagLedRojoEncendido;

int estadoBotonSubir = 0;
int estadoBotonDetener = 0;
int estadoBotonBajar = 0;

bool subiendo = false;
bool detenido = true;
bool bajando = false;

int pisoActual;
bool flagMensajeSubir;
bool flagMensajeDetener;
bool flagMensajeBajar;


void setup()
{
  //Salida digital
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  
  //Entrada digital
  pinMode(BOTON_SUBIR, INPUT);
  pinMode(BOTON_DETENER, INPUT);
  pinMode(BOTON_BAJAR, INPUT);
  
  Serial.begin(9600);
  Serial.println("Montacargas listo para usar :)");
}

void loop()
{
  leerEstadoBotones();
  
  if(subiendo == true)
  {
    subir();
  }
  if(detenido == true)
  {
    detener();
  }
  if(bajando == true)
  {
    bajar();
  }  
}

//Funciones
void prenderLed(int led)
{
  switch(led)
  {
    case LED_VERDE:
    if(flagLedVerdeEncendido == false)
    {
      Serial.println("Led verde encendido");
      flagLedVerdeEncendido = true;
    }
    break;
    case LED_ROJO:
    if(flagLedRojoEncendido == false)
    {
      Serial.println("Led rojo encendido");
      flagLedRojoEncendido = true;
    }
    break;
  }
  digitalWrite(led, HIGH);
}

void apagarLed(int led)
{
  switch(led)
  {
    case LED_VERDE:
    if(flagLedVerdeEncendido == true)
    {
      Serial.println("Led verde apagado");
      flagLedVerdeEncendido = false;
    }
    break;
    case LED_ROJO:
    if(flagLedRojoEncendido == true)
    {
      Serial.println("Led rojo apagado");
      flagLedRojoEncendido = false;
    }
  }
  digitalWrite(led, LOW);
}

void estadoLedsDisplay(int A, int B, int C, int D, int E, int F, int G)
{
  digitalWrite(LED_A, A);
  digitalWrite(LED_B, B);
  digitalWrite(LED_C, C);
  digitalWrite(LED_D, D);
  digitalWrite(LED_E, E);
  digitalWrite(LED_F, F);
  digitalWrite(LED_G, G);
}

void estadoNumeroDisplay(int numero, int estado)
{
  switch(numero)
  {
    case 0:
    	estadoLedsDisplay(estado,estado,estado,estado,estado,estado,0);
    	break;
    case 1:
    	estadoLedsDisplay(0,estado,estado,0,0,0,0);
    	break;
    case 2:
    	estadoLedsDisplay(estado,estado,0,estado,estado,0,estado);
    	break;
    case 3:
    	estadoLedsDisplay(estado,estado,estado,estado,0,0,estado);
    	break;
    case 4:
    	estadoLedsDisplay(0,estado,estado,0,0,estado,estado);
    	break;
    case 5:
    	estadoLedsDisplay(estado,0,estado,estado,0,estado,estado);
    	break;
    case 6:
    	estadoLedsDisplay(estado,0,estado,estado,estado,estado,estado);
    	break;
    case 7:
    	estadoLedsDisplay(estado,estado,estado,0,0,0,0);
    	break;
    case 8:
    	estadoLedsDisplay(estado,estado,estado,estado,estado,estado,estado);
    	break;
    case 9:
    	estadoLedsDisplay(estado,estado,estado,estado,0,estado,estado);
    	break;
  }
}

void leerEstadoBotonSubir()
{
  estadoBotonSubir = digitalRead(BOTON_SUBIR);
  if(estadoBotonSubir == 1)
  {
    if(subiendo == false)
    {
      Serial.println("Boton subir presionado");
      subiendo = true;
      detenido = false;
      bajando = false;
      if(pisoActual == 9)
      {
        Serial.println("Ya estas en el ultimo piso!");
      }
    }
  }
}

void leerEstadoBotonDetener()
{
  estadoBotonDetener = digitalRead(BOTON_DETENER);
  if(estadoBotonDetener == 1)
  {
    if(detenido == false)
    {
      Serial.println("Boton detener presionado");
      subiendo = false;
      detenido = true;
      bajando = false;
      if(flagMensajeDetener == true)
      {
        Serial.println("Ya estas detenido");
      }
    }
  }
}

void leerEstadoBotonBajar()
{
  estadoBotonBajar = digitalRead(BOTON_BAJAR);
  if(estadoBotonBajar == 1)
  {
    if(bajando == false)
    {
      Serial.println("Boton bajar presionado");
      subiendo = false;
      detenido = false;
      bajando = true;
      if(pisoActual == 0)
      {
        Serial.println("Ya estas en planta baja!");
      }
    }
  }
}

void leerEstadoBotones()
{
  leerEstadoBotonSubir();
  leerEstadoBotonDetener();
  leerEstadoBotonBajar();
}

void habilitarBotonesPorUnTiempo(int tiempo)
{
  int acumuladorTiempo = 0;
  while(acumuladorTiempo < tiempo)
  {
    delay(50);
    leerEstadoBotones();
    acumuladorTiempo += 50;
  }
}

void subir()
{
  if(pisoActual != 9)
  {
    apagarLed(LED_ROJO);
    prenderLed(LED_VERDE);
    flagMensajeDetener = false;
    flagMensajeBajar = false;
    
    estadoNumeroDisplay(pisoActual,1);
    Serial.println("Subiendo...");
    habilitarBotonesPorUnTiempo(3000);
    pisoActual ++;
    estadoNumeroDisplay(pisoActual,1);
    Serial.print("Estas en el piso: ");
    Serial.println(pisoActual);
  }
  else
  {
    if(flagMensajeSubir == false)
    {
      Serial.println("Montacargas detenido en ultimo piso.");
      subiendo = false;
      detenido = true;
      flagMensajeSubir = true;
    }
  }
}

void detener()
{
  prenderLed(LED_ROJO);
  apagarLed(LED_VERDE);
  if(flagMensajeDetener == false)
  {
    estadoNumeroDisplay(pisoActual,1);
    Serial.print("Montacargas detenido. Estas en el piso: ");
    Serial.println(pisoActual);
    flagMensajeDetener = true;
    if(pisoActual == 0)
  	{
      flagMensajeBajar = true;
    }
    if(pisoActual == 9)
  	{
      flagMensajeSubir = true;
    }
  }
}

void bajar()
{
  if(pisoActual != 0)
  {
    apagarLed(LED_ROJO);
  	prenderLed(LED_VERDE);
    flagMensajeSubir = false;
  	flagMensajeDetener = false;
    
    estadoNumeroDisplay(pisoActual,1);
    Serial.println("Bajando...");
    habilitarBotonesPorUnTiempo(3000);
    pisoActual --;
    estadoNumeroDisplay(pisoActual,1);
    Serial.print("Estas en el piso: ");
    Serial.println(pisoActual);
  }
  else
  {
    if(flagMensajeBajar == false)
    {
      Serial.println("Montacargas detenido en planta baja.");
      bajando = false;
      detenido = true;
      flagMensajeBajar = true;
    }
  }
}
