const int joystickBT1 = 4; // Botão do joystick 1
const int joystickBT2 = 2; // Botão do joystick 2
const int fsrPin = A7; // Pino analógico conectado ao FSR

const int motorDir = 3; // Pino para girar motor para a direita
const int motorEsq = 5; // Pino para girar motor para a esquerda

void setup() {
  Serial.begin(9600);
  
  pinMode(joystickBT1, INPUT); // Configura o botão como entrada
  pinMode(joystickBT2, INPUT); // Configura o botão como entrada
  pinMode(motorDir, OUTPUT);
  pinMode(motorEsq, OUTPUT);
}

void loop() {
  int buttonOpenState1 = digitalRead(joystickBT1); // Estado do botão 1
  int buttonOpenState2 = digitalRead(joystickBT2); // Estado do botão 2
  int fsrValue = analogRead(fsrPin);
  float fsrVoltage = fsrValue * (5.0 / 1023.0);

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
    
  }else 
{
    Serial.println("PARA A GARRA");
    digitalWrite(motorDir, LOW);
    digitalWrite(motorEsq, LOW);
}


  // Exibir dados no Serial Monitor para depuração
  Serial.print("fsrValue: ");
  Serial.print(fsrValue);
  Serial.print(" | fsrVoltage: ");
  Serial.println(fsrVoltage);

  delay(50); // Pequena pausa para estabilidade
}
