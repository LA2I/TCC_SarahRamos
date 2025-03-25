#include <Servo.h>

const int joystickX1 = A2; // Joystick 1 eixo X
const int joystickY1 = A3; // Joystick 1 eixo Y
const int joystickBT1 = 4; // Botão do joystick 1

const int joystickX2 = A6; // Joystick 2 eixo X
const int joystickY2 = A5; // Joystick 2 eixo Y
const int joystickBT2 = 2; // Botão do joystick 2

const int servo1 = 11; // Pino PWM conectado ao servo 1
const int servo2 = 10; // Pino PWM conectado ao servo 2
const int servo3 = 9;  // Pino PWM conectado ao servo 3
const int servo4 = 6;  // Pino PWM conectado ao servo 4

const int motorDir = 3; // Pino para girar motor para a direita
const int motorEsq = 5; // Pino para girar motor para a esquerda

const int fsrPin = A7; // Pino analógico conectado ao FSR

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

int anguloServo1 = 90;
int anguloServo2 = 90;
int anguloServo3 = 90;
int anguloServo4 = 90;

void setup() {
  Serial.begin(9600);
  
  pinMode(joystickBT1, INPUT); // Configura o botão como entrada
  pinMode(joystickBT2, INPUT); // Configura o botão como entrada
  pinMode(motorDir, OUTPUT);
  pinMode(motorEsq, OUTPUT);

  // Atrela e posiciona todos os servos em 90 graus ao iniciar
  Servo1.attach(servo1);
  Servo2.attach(servo2);
  Servo3.attach(servo3);
  Servo4.attach(servo4);

  Servo1.write(anguloServo1);
  Servo2.write(anguloServo2);
  Servo3.write(anguloServo3);
  Servo4.write(anguloServo4);
}

void loop() {
  int buttonOpenState1 = digitalRead(joystickBT1); // Estado do botão 1
  int buttonOpenState2 = digitalRead(joystickBT2); // Estado do botão 2
  int fsrValue = analogRead(fsrPin);
  float fsrVoltage = fsrValue * (5.0 / 1023.0);

  int valorX1 = analogRead(joystickX1);
  int valorY1 = analogRead(joystickY1);
  int valorX2 = analogRead(joystickX2);
  int valorY2 = analogRead(joystickY2);

  int midValue = 512;
  int faixaNeutra = 20;

  // Controle do Servo 1 e Servo 2 (Joystick 1)
  int incremento = 5;  // Valor de incremento ajustado para aumentar a velocidade

  if (valorX1 > midValue + faixaNeutra || valorX1 < midValue - faixaNeutra) {
    anguloServo1 = constrain(anguloServo1 + (valorX1 > midValue ? incremento : -incremento), 0, 180);
    Servo1.write(anguloServo1);
  }

  if (valorY1 > midValue + faixaNeutra || valorY1 < midValue - faixaNeutra) {
    anguloServo2 = constrain(anguloServo2 + (valorY1 > midValue ? incremento : -incremento), 0, 180);
    Servo2.write(anguloServo2);
  }

  // Controle do Servo 3 e Servo 4 (Joystick 2)
  if (valorX2 > midValue + faixaNeutra || valorX2 < midValue - faixaNeutra) {
    anguloServo3 = constrain(anguloServo3 + (valorX2 > midValue ? incremento : -incremento), 0, 180);
    Servo3.write(anguloServo3);
  }

  if (valorY2 > midValue + faixaNeutra || valorY2 < midValue - faixaNeutra) {
    anguloServo4 = constrain(anguloServo4 + (valorY2 > midValue ? incremento : -incremento), 0, 180);
    Servo4.write(anguloServo4);
  }

  if (fsrVoltage < 2) {
    // Controle do motor DC
    if (buttonOpenState1 == HIGH && buttonOpenState2 == LOW) {
      digitalWrite(motorDir, HIGH);
      digitalWrite(motorEsq, LOW);
    } else if (buttonOpenState2 == HIGH && buttonOpenState1 == LOW) {
      digitalWrite(motorDir, LOW);
      digitalWrite(motorEsq, HIGH);
    } else {
      digitalWrite(motorDir, LOW);
      digitalWrite(motorEsq, LOW);
    }
  } else {
    Serial.println("PARA A GARRA");
    digitalWrite(motorDir, LOW);
    digitalWrite(motorEsq, LOW);
  }

  // Exibir dados no Serial Monitor para depuração
  Serial.print("buttonOpenState1: ");
  Serial.print(buttonOpenState1);
  Serial.print(" | buttonOpenState2: ");
  Serial.print(buttonOpenState2);

}
