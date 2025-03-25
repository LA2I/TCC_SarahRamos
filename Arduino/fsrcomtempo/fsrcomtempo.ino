const int fsrPin = A7;  // Pino onde o FSR está conectado

void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do sensor FSR
  int fsrValue = analogRead(fsrPin);
  
  // Converte o valor do FSR para tensão (em volts)
  float fsrVoltage = fsrValue * (5.0 / 1023.0);
  
  // Obtém o tempo em milissegundos desde que o Arduino foi ligado
  unsigned long tempoMillis = millis();
  
  // Converte o tempo para segundos
  float tempoSegundos = tempoMillis / 1000.0;
  
  // Exibe o tempo e a tensão no monitor serial
  Serial.print("Tempo (s): ");
  Serial.print(tempoSegundos);
  Serial.print("\tTensão do FSR (V): ");
  Serial.println(fsrVoltage, 3);  // Imprime a tensão com 3 casas decimais
  
  // Aguarda 100 ms antes de atualizar os valores
  delay(100);
}

