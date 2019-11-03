bool activado = false;
bool gasactivado = false;
bool panicoactivado = false;

bool buzzeractivado = false;

int SENSOR_PIR = 7; //pin para el sensor pir
int SENSOR_GAS = A0; //pin para el sensor de gas
int SENSOR_PANICO = 6; //pin para el sensor de panico
int LEDPROXIMIDAD = 12; // habilitar encendido de led
int LEDGAS = 11;
int LEDPANICO = 10;
int BOMBILLAS = 3;

int PING_BUZZER = 4; //salida senoidal del buzzer
float sinVal;
int toneVal;

unsigned long previousMillis = 0;
unsigned long previousMillisBuzzer = 0;
long interval = 2000;

long intervalBuzzer = 10000;

int ledEncendido = 0;
unsigned long ledMillis = 0;

void setup() {
  pinMode(SENSOR_PIR,INPUT);//configurar la entrada del pulso del PIR
  pinMode(SENSOR_PANICO,INPUT);//configurar la entrada del pulso de PANICO
  pinMode(LEDPROXIMIDAD,OUTPUT);
  pinMode(LEDGAS,OUTPUT);
  pinMode(LEDPANICO,OUTPUT);
  pinMode(BOMBILLAS,OUTPUT);
   
  Serial.begin(9600); //configurar los baudios del serial
}

void loop() {
  sensores();
}

void sensores(){
  /*------------- sensor PIR------------------*/  
  if(activado == false){
    if(digitalRead(SENSOR_PIR) == HIGH)
    {
      activado = true;
      Serial.println("Movimiento detectado");
      digitalWrite(LEDPROXIMIDAD,HIGH);
      Serial.write("2");
      encender_buzzer();
    }
  }

  if(digitalRead(SENSOR_PIR) == LOW){
      activado = false;
      digitalWrite(LEDPROXIMIDAD,LOW);
    }
/*---------------------------------------------*/

/*-------------- sensor GAS -------------------*/
  int valor = analogRead(A0);

  if(gasactivado == false){
    if(valor >= 300){
      digitalWrite(LEDGAS,HIGH);
      Serial.println("Gas detectado");
      Serial.write("3");
      gasactivado = true;
      encender_buzzer();
    }

 }

  if(valor < 300){
    digitalWrite(LEDGAS,LOW);
    gasactivado = false;
  }
/*---------------------------------------------*/

/*--------------- sensor PANICO-------------------*/
    if(digitalRead(SENSOR_PANICO) == HIGH)
    {
        if(panicoactivado == false)
        {
            panicoactivado = true;
            
            digitalWrite(LEDPANICO,HIGH);
            Serial.println("BOTON DE PANICO ACTIVADO");
            Serial.write("4");
            encender_buzzer();
         }
    }
  

  if(digitalRead(SENSOR_PANICO) == LOW){
       panicoactivado = false;
       digitalWrite(LEDPANICO,LOW);
  }
/*------------------------------------------------*/
}

void encender_buzzer()
{
  pinMode(PING_BUZZER, OUTPUT); // Definimos el pin 4 como salida.
  digitalWrite(BOMBILLAS,HIGH);
  
  unsigned long currentMillisBuzzer = millis();

  intervalBuzzer = (currentMillisBuzzer + 10000);
  
  while((currentMillisBuzzer - previousMillisBuzzer) < intervalBuzzer)
  { 
    for(int x=0; x<180; x++){
            // convertimos grados en radianes para luego obtener el valor.
            sinVal = (sin(x*(3.1412/180)));
            // generar una frecuencia a partir del valor sin
            toneVal = 2000+(int(sinVal*1000));
             
            tone(PING_BUZZER, toneVal);
            delay(2); 
             
   }
    currentMillisBuzzer = millis();
  }

  Serial.println("Apagado");

  pinMode(PING_BUZZER, INPUT); // Definimos el pin 4 como entrada.
  digitalWrite(BOMBILLAS,LOW);
}
