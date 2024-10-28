#include <LiquidCrystal.h>

// Define os pinos do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2); // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.print("PENIS"); // Mensagem de teste na primeira linha
  lcd.setCursor(0, 1); // Move o cursor para a primeira coluna da segunda linha
  lcd.print("PENIS!"); // Mensagem na segunda linha
}

void loop() {
  // Não faz nada aqui
}
