#include <Servo.h>

// Definición de variables
int trigPin = 8;
int echoPin = 7;
int ledVerde = 4;     // LED Verde
int ledAmarillo = 5;  // LED Amarillo
int ledRojo = 6;      // LED Rojo
int ledAzul = 3;      // LED Azul

int touch = 2;

Servo servoPuerta;
bool activado = false; // Variable para controlar si el touch ha sido activado


// Configuración de los pines
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  
  servoPuerta.attach(9);
  digitalWrite(trigPin, LOW);
  pinMode(touch, INPUT);

  // Inicialización del puerto serial
  Serial.begin(9600);
}

void activarServo() {
  // Gira el servo en una dirección
  servoPuerta.write(0); // Gira el servo hacia una dirección
  delay(300); // Espera 1 segundo

  // Gira el servo en la dirección opuesta
  servoPuerta.write(180); // Gira el servo hacia la dirección opuesta
  delay(300); // Espera 1 segundo

  // Detiene el servo en el medio (90 grados) si se necesita detenerlo después del giro
  servoPuerta.write(90); 
}

void loop() {

  digitalWrite(trigPin, HIGH); // Activamos el pin trig
  delay(10);                   // Esperamos un poco
  digitalWrite(trigPin, LOW);  // Lo apagamos

  long t = pulseIn(echoPin, HIGH); // Long para precisión, activamos la lectura del echo
  int distancia = t / 59;          // Distancia según el manual

  // Mostrar la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Control de los LEDs en función de la distancia
  if (distancia < 16) {
    // Cerca: Encender LED verde
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
  } else if (distancia >= 16 && distancia < 18) {
    // Medio: Encender LED amarillo
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledRojo, LOW);
  } else {
    // Lejos: Encender LED rojo
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);

  if (digitalRead(touch) == HIGH && !activado) { // Si el sensor táctil está activado y aún no se ha activado
    digitalWrite(ledAzul, HIGH);
    activarServo(); // Llama a la función para mover el servo
    activado = true; // Cambia el estado para evitar múltiples activaciones
  } 
  else if (digitalRead(touch) == LOW) { // Si el sensor táctil no está activado
    digitalWrite(ledAzul, LOW);
    activado = false; // Resetea la variable para permitir la próxima activación
  }
  }
  
  // Pequeña pausa antes de la siguiente medición

}
