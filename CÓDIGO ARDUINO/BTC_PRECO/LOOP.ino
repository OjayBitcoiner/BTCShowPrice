void loop() {

  myButtonDOWN.update(digitalRead(DOWN));
  myButtonENTER.update(digitalRead(ENTER));
  myButtonUP.update(digitalRead(UP));

  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    if(state == 1){
      atualizarHora();
      seg --;
      lcd.setCursor(6,0);
      lcd.print("    ");
      lcd.setCursor(6,0);
      lcd.print(seg);
      lcd.print("s");
    }
  }

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Chama a função pegaPreco
    pegaPreco();
    seg = interval / 1000;
    // Atualiza o valor do último millis()
    previousMillis = currentMillis;
  }

}