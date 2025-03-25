#include <Servo.h> 
Servo myservo;  // cria o objeto servo para controlar o servo motor

void setup() {
  Serial.begin(9600);
  myservo.attach(7);  // conecta o servo no pino 7
  Serial.println("servo 90 graus e depois desativar");
}

void loop() {
  if (Serial.available()) { 
    String command = Serial.readString();  // lê o comando da porta serial
    
    if (command == "girar") {
      myservo.write(90);  // gira o servo para a posição de 90 graus
      delay(1000);        // espera 1 segundo para garantir que ele completou o movimento
      myservo.detach();   // desativa o servo para economizar energia
      Serial.println("Servo girou 90 graus e foi desativado");
    }
  }
}
