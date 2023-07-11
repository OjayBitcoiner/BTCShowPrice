void Set_state(char index) {
  state = index;

  switch (state) {
    case 1:
    break;

    case 2:
    lcd.setCursor(0,0);
    lcd.print("MENU:");
    lcd.setCursor(0,1);
    lcd.print(">>");
    lcd.setCursor(2,1);
    lcd.print("Voltar");
    lcd.setCursor(2,2);
    lcd.print("Moeda Fiat");
    lcd.setCursor(2,3);
    lcd.print("Tempo Att.");
    break;

    case 3:
    lcd.setCursor(0,0);
    lcd.print("MENU:");
    lcd.setCursor(2,1);
    lcd.print("Voltar");
    lcd.setCursor(0,2);
    lcd.print(">>");
    lcd.setCursor(2,2);
    lcd.print("Moeda Fiat");
    lcd.setCursor(2,3);
    lcd.print("Tempo Att.");
    break;

    case 4:
    lcd.setCursor(0,0);
    lcd.print("MENU:");
    lcd.setCursor(2,1);
    lcd.print("Moeda Fiat");
    lcd.setCursor(0,2);
    lcd.print(">>");
    lcd.setCursor(2,2);
    lcd.print("Tempo Att.");
    lcd.setCursor(2,3);
    lcd.print("Fonte");
    break;

    case 5:
    lcd.setCursor(0,0);
    lcd.print("MENU:");
    lcd.setCursor(2,1);
    lcd.print("Tempo Att.");
    lcd.setCursor(2,2);
    lcd.print("Fonte");
    lcd.setCursor(0,3);
    lcd.print(">>");
    lcd.setCursor(2,3);
    lcd.print("BackLight");
    break;

    case 6:  //==================== tela de mudar moeda fiat
    lcd.setCursor(0,0);
    lcd.print("MOEDA FIAT:");
    lcd.setCursor(4,1);
    lcd.print("BTC -> ");
    lcd.print(fiatArray[fiatPosition]);
    lcd.setCursor(4,3);
    lcd.print("(O)-> Voltar");
    break;

    case 7:  //==================== tela de mudar o tempo de atualização
    lcd.setCursor(0,0);
    lcd.print("TEMPO DE ATT:");
    lcd.setCursor(3,1);
    lcd.print("T. EM SEGUNDOS");
    lcd.setCursor(7,2);
    lcd.print(ler_tempo);
    lcd.print("s");
    lcd.setCursor(4,3);
    lcd.print("(O)-> Voltar");
    break;

    case 8:  //==================== tela de mudar o backlight do display
    lcd.setCursor(0,0);
    lcd.print("BACKLIGHT:");
    lcd.setCursor(4,1);
    lcd.print("LIGADO -> ");
    lcd.print(backk[luzativa]);
    lcd.setCursor(4,3);
    lcd.print("(O) -> Voltar");
    break;

    case 9: 
    lcd.setCursor(0,0);
    lcd.print("MENU:");
    lcd.setCursor(2,1);
    lcd.print("Tempo Att.");
    lcd.setCursor(0,2);
    lcd.print(">>");
    lcd.setCursor(2,2);
    lcd.print("Fonte");
    lcd.setCursor(2,3);
    lcd.print("BackLight");
    break;

    case 10:  //==================== tela de mudar o backlight do display
    lcd.setCursor(0,0);
    lcd.print("FONTE:");
    draw_big_digit(0, 6, 0);
    draw_big_digit(1, 9, 0);
    draw_big_digit(2, 12, 0);
    draw_big_digit(3, 15, 0);
    draw_big_digit(4, 18, 0);
    draw_big_digit(5, 6, 2);
    draw_big_digit(6, 9, 2);
    draw_big_digit(7, 12, 2);
    draw_big_digit(8, 15, 2);
    draw_big_digit(9, 18, 2);
    lcd.setCursor(1,2);
    lcd.print("(O)");
    lcd.setCursor(0,3);
    lcd.print("Voltar");
    break;
  }

}