void setup() {

  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);

  /************************ FUNÇÃO QUE É NECESSÁRIA QUE SEJA EXECUTADA PELO MENOS UMA VEZ ******************************************/
  /**/                                                                                                                           /**/
  /**/  escreverMemoria(); //função que cria os parametros iniciais do sistema                                                   /**/
  /**/                                                                                                                           /**/
  /*********************************************************************************************************************************/

  lerMemoria(); // lê os dados para funcionamento

  lcd.init();  // INICIA A COMUNICAÇÃO COM O DISPLAY

  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.setBacklight(luzativa);

  setTipoFonte(tipo_fonte);

  lcd.clear(); // LIMPA O DISPLAY

  pinMode(DOWN, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);

   // Conectar-se a uma rede Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  //iniciando o sistema
  lcd.setCursor(6, 1);
  lcd.print("AGUARDE...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Conectado ao Wi-Fi!");

  pegaPreco();

  hora_inicial = pegaHora();

  int posDoisPontos = hora_inicial.indexOf(":");
  horas = hora_inicial.substring(0, posDoisPontos).toInt();
  int posDoisPontos2 = hora_inicial.indexOf(":", posDoisPontos + 1);
  minutos = hora_inicial.substring(posDoisPontos + 1, posDoisPontos2).toInt();
  segundos = hora_inicial.substring(posDoisPontos2 + 1).toInt();

}