#define LED_PIN 52
#define LED_PIN2 47
#define LED_PIN3 45
#define LED_PIN4 49

#define entradaAnalogica 0

int aSensor;

const int LIMITE_CO2 = 1000; // Limite para CO2 em ppm

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
}

void loop() {
  aSensor = analogRead(entradaAnalogica);
  
  // Exibe a leitura do sensor
  Serial.print("Leitura entrada analógica: ");
  Serial.println(aSensor);

  // Exemplo de conversão, ajuste conforme seu sensor
  int co2 = map(aSensor, 0, 1023, 0, 2000); // Mapeia a leitura para 0-2000 ppm

  // Reseta todos os LEDs antes de verificar
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, LOW);  
  digitalWrite(LED_PIN3, LOW);  
  digitalWrite(LED_PIN4, LOW);  

  // Validações para CO2
  if (co2 > LIMITE_CO2) {
    Serial.println("Atenção: O nível de CO2 está contaminado!");
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH);
    digitalWrite(LED_PIN4, HIGH);
  } 
  else if (co2 >= 200) {
    Serial.println("Atenção: Volume de Gás perigoso detectado");
    digitalWrite(LED_PIN4, HIGH);
  } 
  else if (co2 >= 150) {
    Serial.println("Atenção: Gás detectado");
    digitalWrite(LED_PIN3, HIGH);
    digitalWrite(LED_PIN4, HIGH); // Mantém LED 4 aceso
  } 
  else if (co2 >= 100) {
    Serial.println("Atenção: Gás detectado");
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH); // Mantém LED 3 aceso
    digitalWrite(LED_PIN4, HIGH);  // Mantém LED 4 aceso
  } 
  else {
    Serial.println("Qualidade do ar está aceitável.");
  }

  Serial.println();
  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
