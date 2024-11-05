#include <Servo.h>

int ledAzul = 3; 
int touch = 2;

Servo servoPuerta;
bool activado = false; // Variable para controlar si el touch ha sido activado

void setup() {
  pinMode(ledAzul, OUTPUT);
  pinMode(touch, INPUT); 

  servoPuerta.attach(9);
  Serial.begin(9600);
}


void activarServo() {
  // Gira el servo en una dirección
  servoPuerta.write(0); // Gira el servo hacia una dirección
  delay(500); // Espera 1 segundo

  // Gira el servo en la dirección opuesta
  servoPuerta.write(180); // Gira el servo hacia la dirección opuesta
  delay(500); // Espera 1 segundo

  // Detiene el servo en el medio (90 grados) si se necesita detenerlo después del giro
  servoPuerta.write(90); 
}

void loop() {
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
