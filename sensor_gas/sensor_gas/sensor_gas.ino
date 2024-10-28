#include <LiquidCrystal.h>

// Define os pinos do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define LED_PIN 37
#define LED_PIN2 31
#define LED_PIN3 33
#define LED_PIN4 35
#define BUZZER_PIN 8

#define ENTRADA_ANALOGICA 0

int aSensor;
const int LIMITE_CO2 = 800; // Limite para CO2 em ppm

void setup() {
  Serial.begin(9600);
  
  // Configura os pinos como saída
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Inicializa o LCD
  lcd.begin(16, 2);
  lcd.print("Sistema Pronto");
  delay(2000);
  lcd.clear();
}

void loop() {
  aSensor = analogRead(ENTRADA_ANALOGICA);
  
  // Exibe a leitura do sensor
  Serial.print("Leitura entrada analógica: ");
  Serial.println(aSensor);
  lcd.setCursor(0, 0);
  lcd.print("Leitura: ");
  lcd.print(aSensor);
  
  // Reseta todos os LEDs e o buzzer
  resetIndicators();

  // Validações para CO2
  if (aSensor >= LIMITE_CO2) {
    alertCO2Contaminado();
  } else if (aSensor >= 200) {
    alertGasDetectado(2);
  } else if (aSensor >= 150) {
    alertGasDetectado(1);
  } else if (aSensor >= 100) {
    alertGasPerigoso();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Qualidade OK");
  }

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}

void resetIndicators() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, LOW);
  digitalWrite(LED_PIN3, LOW);
  digitalWrite(LED_PIN4, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void alertCO2Contaminado() {
  Serial.println("Atenção: O nível de CO2 está contaminado!");
  lcd.setCursor(0, 1);
  lcd.print("CO2 Contaminado  ");
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN2, HIGH);
  digitalWrite(LED_PIN3, HIGH);
  digitalWrite(LED_PIN4, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
}

void alertGasDetectado(int level) {
  Serial.println("Atenção: Gás detectado");
  lcd.setCursor(0, 1);
  lcd.print("Gas Detectado");
  if (level == 2) {
    digitalWrite(LED_PIN2, HIGH);
  }
  digitalWrite(LED_PIN3, HIGH);
  digitalWrite(LED_PIN4, HIGH);
}

void alertGasPerigoso() {
  Serial.println("Atenção: Volume de Gás perigoso detectado");
  lcd.setCursor(0, 1);
  lcd.print("Gas Perigoso     ");
  digitalWrite(LED_PIN4, HIGH);
}
