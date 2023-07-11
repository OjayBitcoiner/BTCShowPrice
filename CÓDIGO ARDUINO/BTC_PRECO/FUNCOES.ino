void pegaPreco(){
    // Real{izar a solicitação HTTP
  HTTPClient http;
  http.begin(urlBTC);  // URL da página com o JSON

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    String response = http.getString();

    // Remover espaços em branco e quebras de linha da string
    response.replace(" ", "");
    response.replace("\n", "");

    // Criar um vetor para armazenar os elementos
    std::vector<String> elements;

    // Quebrar a string no caractere de vírgula e adicionar os elementos ao vetor
    char* token = strtok((char*)response.c_str(), "}");
    while (token != NULL) {
      // Adicionar o caractere de chave fechando '}' para cada parte do array
      String arrayElement = String(token) + "}";
      elements.push_back(arrayElement);
      token = strtok(NULL, "}");
    }

    //PEGA DO ARRAY O PREÇO EM BRL
    String str = elements[2];
    String dadosBRL[6];
    splitString(str, ",", dadosBRL, 6);
    String valorBRL[2];
    splitString(dadosBRL[2], ":", valorBRL, 2);
    int pontoIndex = valorBRL[1].indexOf(".");
    String valorAntesDoPontoBRL = valorBRL[1].substring(0, pontoIndex);
    Serial.println(valorAntesDoPontoBRL);

    //PEGA DO ARRAY O PREÇO EM EUR
    String streur = elements[9]; // Altere o índice para 9 para buscar o preço em Euro
    String dadosEUR[6];
    splitString(streur, ",", dadosEUR, 6);
    String valorEUR[2];
    splitString(dadosEUR[2], ":", valorEUR, 2);
    int pontoIndexEUR = valorEUR[1].indexOf(".");
    String valorAntesDoPontoEUR = valorEUR[1].substring(0, pontoIndexEUR);
    Serial.println(valorAntesDoPontoEUR);

    //PEGA DO ARRAY O PREÇO EM USD
    String strusd = elements[elements.size() - 1];
    String dadosUSD[6];
    splitString(strusd, ",", dadosUSD, 6);
    String valorUSD[2];
    splitString(dadosUSD[2], ":", valorUSD, 2);
    int pontoIndexUSD = valorUSD[1].indexOf(".");
    String valorAntesDoPontoUSD = valorUSD[1].substring(0, pontoIndexUSD);
    Serial.println(valorAntesDoPontoUSD);

    /*
    fiatPosition -> 0 == COTAÇÃO EM USD
    fiatPosition -> 1 == COTAÇÃO EM BRL
    fiatPosition -> 2 == COTAÇÃO EM EUR
    */
    //MOSTRA PRECO DO BTC NO DISPLAY
    String preco = valorAntesDoPontoUSD;

    switch(fiatPosition){
      case 0:
      preco = valorAntesDoPontoUSD;
      break;
      case 1:
      preco = valorAntesDoPontoBRL;
      break;
      case 2:
      preco = valorAntesDoPontoEUR;
      break;
    }

    int unidade = preco.substring(preco.length() - 1).toInt();
    int dezena = preco.substring(preco.length() - 2, preco.length() - 1).toInt();
    int centena = preco.substring(preco.length() - 3, preco.length() - 2).toInt();
    int milhar = preco.substring(preco.length() - 4, preco.length() - 3).toInt();
    int dezenaMilhar = preco.substring(preco.length() - 5, preco.length() - 4).toInt();
    int centenaMilhar = preco.substring(0, preco.length() - 5).toInt();

    if(inicio){
      lcd.clear();
      inicio = false;
    }

    if(state == 1){
      //PROXIMA ATUALIZAÇÃO DO PREÇO
      lcd.setCursor(0,0);
      lcd.print("Prox: ");

      //DIFERENCIA DE REAL PARA DOLAR
      lcd.setCursor(0,2);
      lcd.print(fiatSymbolArray[fiatPosition]);
      lcd.setCursor(0,3);
      lcd.print("$");

      if(centenaMilhar > 0){
        printDigits(centenaMilhar,2);
      }
      printDigits(dezenaMilhar,5);
      printDigits(milhar,8);
      lcd.setCursor(11,3);
      lcd.print(","); 
      printDigits(centena,12);
      printDigits(dezena,15);
      printDigits(unidade,18);
    }

  } else {
    Serial.print("Erro na solicitação HTTP. Código de resposta: ");
    Serial.println(httpResponseCode);
    if(state == 1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Prox: ");
      lcd.setCursor(6,3);
      lcd.print("ERRO DE HTTP!"); 
    }
  }

  http.end();
}

String pegaHora(){
  String hora = "00:00:00";
  HTTPClient http;
  http.begin(urlhora);  // URL da página com o JSON

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    String response = http.getString();

    JSONVar json = JSON.parse(response);  // Analisa a resposta JSON
    
    String datetime = JSON.stringify(json["datetime"]);  // Obtém a data e hora do JSON
    datetime.remove(0, 12);  // Remove os primeiros 12 caracteres ("2023-07-07T")
    
    String hora_inicial = datetime.substring(0, 8);  // Extrai a hora, os minutos e os segundos ("11:36:40")
    
    Serial.println(hora_inicial);  // Imprime a string no formato desejado ("hora:minutos:segundos")
    hora = hora_inicial;
  }

  return hora;
}

// Função para dividir uma string em tokens com base em um delimitador
int splitString(String str, String delimiter, String* tokens, int maxTokens) {
  int count = 0;
  int delimiterIndex = -1;
  int startIndex = 0;
  
  while ((delimiterIndex = str.indexOf(delimiter, startIndex)) != -1) {
    if (count >= maxTokens) {
      break;
    }
    
    tokens[count] = str.substring(startIndex, delimiterIndex);
    count++;
    startIndex = delimiterIndex + delimiter.length();
  }
  
  if (count < maxTokens) {
    tokens[count] = str.substring(startIndex);
    count++;
  }
  
  return count;
}

void custom0(int x){
  draw_big_digit(0, x, 2);
}
void custom1(int x){
  draw_big_digit(1, x, 2);
}
void custom2(int x){
  draw_big_digit(2, x, 2);
}
void custom3(int x){
 draw_big_digit(3, x, 2);
}
void custom4(int x){
  draw_big_digit(4, x, 2);
}
void custom5(int x){
  draw_big_digit(5, x, 2);
}
void custom6(int x){
  draw_big_digit(6, x, 2);
}
void custom7(int x){
  draw_big_digit(7, x, 2);
}
void custom8(int x){
  draw_big_digit(8, x, 2);
}
void custom9(int x){
  draw_big_digit(9, x, 2);
}

void printDigits(int digits, int x){
  // utility function for digital clock display: prints preceding colon and leading 0
  switch (digits) {
  case 0: 
    custom0(x);
    break;
  case 1: 
    custom1(x);
    break;
  case 2: 
    custom2(x);
    break;
  case 3: 
    custom3(x);
    break;
  case 4: 
    custom4(x);
    break;
  case 5: 
    custom5(x);
    break;
  case 6: 
    custom6(x);
    break;
  case 7: 
    custom7(x);
    break;
  case 8: 
    custom8(x);
    break;
  case 9: 
    custom9(x);
    break;
  }
}

void atualizarHora() {


  segundos++;

  if (segundos >= 60) {
    segundos = 0;
    minutos++;

    if (minutos >= 60) {
      minutos = 0;
      horas++;

      if (horas >= 24) {
        horas = 0;
      }
    }
  }

  lcd.setCursor(12, 0);
  if (horas < 10) {
    lcd.print("0");
  }
  lcd.print(horas);
  lcd.print(":");
  if (minutos < 10) {
    lcd.print("0");
  }
  lcd.print(minutos);
  lcd.print(":");
  if (segundos < 10) {
    lcd.print("0");
  }
  lcd.print(segundos);
}

void limpa(){
  lcd.clear();
}

void reinicia(){
  inicio = true;
  lcd.setCursor(6, 1);
  lcd.print("AGUARDE...");

  pegaPreco();

  hora_inicial = pegaHora();

  int posDoisPontos = hora_inicial.indexOf(":");
  horas = hora_inicial.substring(0, posDoisPontos).toInt();
  int posDoisPontos2 = hora_inicial.indexOf(":", posDoisPontos + 1);
  minutos = hora_inicial.substring(posDoisPontos + 1, posDoisPontos2).toInt();
  segundos = hora_inicial.substring(posDoisPontos2 + 1).toInt();
}

void setTipoFonte(int fonte){
  //DEFINE TIPO DA FONTE
  switch(fonte){
    case 0:
    set_font_tron_bold();
    break;
    case 1:
    set_font_blocks();
    break;
    case 2:
    set_font_blocks_cut();
    break;
    case 3:
    set_font_blocks_crossed();
    break;
    case 4:
    set_font_dots_big();
    break;
    case 5:
    set_font_square_four();
    break;
    default:
    set_font_tron_bold();
  }
}