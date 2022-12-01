// Projeto de controle do ar e lâmpadas, por temperatura e presença
// última edição: 29/11/2022
#include "DHT.h"
#include <Ultrasonic.h>
#define DHTPIN A1 // pino DHT que estamos conectado
#define DHTTYPE DHT11 // DHT 11
#define Ar1 5 // Motor 1
#define Ar2 11 // Motor 2
#define LED1 4 // Lâmpada 1
#define LED2 8 // Lâmpada 2
#define LED3 9 // Lâmpada 3 
#define LED4 10 // Lâmpada 4
 Ultrasonic ultrassom(6,7); // define o nome do sensor(ultrassom)
 DHT dht(DHTPIN, DHTTYPE);
//e onde está ligado o trig(6) e o echo(7) respectivamente

long distancia;

void setup()
{
  pinMode(Ar1, OUTPUT); // Motor 1
  pinMode(Ar2, OUTPUT); // Motor 2
  pinMode(LED1, OUTPUT); // Lâmpada 1
  pinMode(LED2, OUTPUT); // Lâmpada 2
  pinMode(LED3, OUTPUT); // Lâmpada 3
  pinMode(LED4, OUTPUT); // Lâmpada 4
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
             distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
                                                  // centímetros(CM) ou polegadas(INC)
             Serial.print(distancia); //imprime o valor da variável distancia
             Serial.println("cm");
             delay(1000);

              float h = dht.readHumidity();
              float t = dht.readTemperature();  
 
    if(distancia > 0 && distancia < 20){ //Capta distância a partir de 0 a no máximo 20cm  

           Serial.println("DETECTADO PRESENCA!");
           digitalWrite(Ar1,1);
           digitalWrite(Ar2,1);
           digitalWrite(LED1,1);
           digitalWrite(LED2,1);
           digitalWrite(LED3,1);
           digitalWrite(LED4,1);


              if(t>26){
                digitalWrite(Ar1,0);
              }
           
                if (isnan(t) || isnan(h))
                {
                  Serial.println("Falhou em ler a temperatura");
                }
                else
                {
                  Serial.print("Umidade: ");
                  Serial.print(h);
                  Serial.print(" %t");
                  Serial.print("Temperatura: ");
                  Serial.print(t);
                  Serial.println(" *C");
                  delay(1000);
                }
     
    }

    else{
      Serial.println("_______");
       digitalWrite(Ar1,0);
       digitalWrite(Ar2,0);
       digitalWrite(LED1,0);
       digitalWrite(LED2,0);
       digitalWrite(LED3,0);
       digitalWrite(LED4,0);

    }


}

 //Função para leitura em amostragem
// Faz uma média de leituras de temperatura para estabilizar o resultado
 int analogAvg(int tempPin){
   
  int total = 0;
  int amostras = 20;
   
  for(int n = 0; n < amostras; n ++){
    total += analogRead(tempPin);
    delay(100); // pequeno atraso entre leituras
  }
  return total / amostras;
 }
