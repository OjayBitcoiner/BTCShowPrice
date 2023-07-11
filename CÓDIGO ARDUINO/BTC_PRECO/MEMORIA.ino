void lerMemoria(){
  ler_tempo = EEPROM.read(tempo_att_preco);
  interval = ler_tempo * 1000;
  seg = interval / 1000;

  fiatPosition = EEPROM.read(btcfiat);

  luzativa = EEPROM.read(backlightt);

  tipo_fonte = EEPROM.read(tipofontee);
}

void escreverMemoria(){
  EEPROM.write(tempo_att_preco, 60); //TEMPO DE ATUALIZAÇÃO DO PREÇO
  EEPROM.commit();

  EEPROM.write(btcfiat, 0); //TIPO DE MOEDA CONVERSAO
  EEPROM.commit();

  EEPROM.write(backlightt, 1); //BACKLIGHT LIGADO DESLIGADO
  EEPROM.commit();

  EEPROM.write(tipofontee, 0); //TIPO DE MOEDA CONVERSAO
  EEPROM.commit();
}