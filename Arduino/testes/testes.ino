#include <Servo.h>

const int joystickX1 = A2; // Joystick 1 eixo X
const int servo1 = 11;     // Pino PWM conectado ao servo 1

Servo Servo1;

int anguloServo1 = 90; // Posição inicial do servo

void setup() {
  Serial.begin(9600);
  Servo1.attach(servo1);        // Atrela o servo ao pino
  Servo1.write(anguloServo1);   // Inicializa o servo em 90 graus
}

void loop() {
  int valorX1 = analogRead(joystickX1); // Leitura do eixo X do joystick
  int midValue = 512;                  // Valor central do joystick
  int faixaNeutra = 20;                // Faixa neutra do joystick
  int incremento = 1;                  // Valor de incremento para ajuste de posição

  // Ajusta o ângulo do servo baseado no valor do joystick, dentro do limite de 60 a 120 graus
  if (valorX1 > midValue + faixaNeutra) {
    anguloServo1 = constrain(anguloServo1 + incremento, 60, 120); // Limita entre 60 e 120 graus
  } else if (valorX1 < midValue - faixaNeutra) {
    anguloServo1 = constrain(anguloServo1 - incremento, 60, 120); // Limita entre 60 e 120 graus
  }

  Servo1.write(anguloServo1); // Aplica o novo ângulo ao servo

    // Exibir dados no Serial Monitor para depuração
  Serial.print("anguloServo1: ");
  Serial.print(anguloServo1);
  Serial.print(" | valorX1: ");
  Serial.println(valorX1);
}
