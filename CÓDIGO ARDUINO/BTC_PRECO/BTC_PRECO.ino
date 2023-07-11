#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>
#include <Arduino_JSON.h>
#include <Arduino.h>
#include <debounce.h>
#include <EEPROM.h>

#define EEPROM_SIZE 4096

// DEFINIÇÕES
#define enderecolcd  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   20
#define linhas    4

/*
TIMEZONES BRASIL
'AC' => 'America/Rio_branco',   'AL' => 'America/Maceio',
'AP' => 'America/Belem',        'AM' => 'America/Manaus',
'BA' => 'America/Bahia',        'CE' => 'America/Fortaleza',
'DF' => 'America/Sao_Paulo',    'ES' => 'America/Sao_Paulo',
'GO' => 'America/Sao_Paulo',    'MA' => 'America/Fortaleza',
'MT' => 'America/Cuiaba',       'MS' => 'America/Campo_Grande',
'MG' => 'America/Sao_Paulo',    'PR' => 'America/Sao_Paulo',
'PB' => 'America/Fortaleza',    'PA' => 'America/Belem',
'PE' => 'America/Recife',       'PI' => 'America/Fortaleza',
'RJ' => 'America/Sao_Paulo',    'RN' => 'America/Fortaleza',
'RS' => 'America/Sao_Paulo',    'RO' => 'America/Porto_Velho',
'RR' => 'America/Boa_Vista',    'SC' => 'America/Sao_Paulo',
'SE' => 'America/Maceio',       'SP' => 'America/Sao_Paulo',
'TO' => 'America/Araguaia',     
*/

#define WIFI_SSID "COLOQUE AQUI O SSID DO SEU WIFI"
#define WIFI_SENHA "COLOQUE AQUI A SENHA DO WIFI"
#define urlhora "https://worldtimeapi.org/api/timezone/America/Sao_Paulo" // ESCOLHA SEU MELHOR TIMEZONE
#define urlBTC "https://blockchain.info/ticker" // URL QUE BUSCA PREÇO DO BTC

//SERÃO USADOS NA MEMÓRIA
#define tempo_att_preco 10
#define btcfiat 11
#define backlightt 12
#define tipofontee 13

static constexpr int DOWN = 5;
static constexpr int ENTER = 25;
static constexpr int UP = 14;

char state=1; 

// INSTANCIANDO OBJETOS
LiquidCrystal_I2C lcd(enderecolcd, colunas, linhas);

int counter = 0;

//ESCOLHE TIPO DA FONTE
int tipo_fonte = 0;

// current_font_digits is storing 4 parts for every digit, this array is only needed once in the sketch
byte current_font_digits[10][4];
byte buffer[8];

//------------------------------------- FONTE TRON BOLD ------------------------------------------------------
// set eight special characters for the font: tron_bold   - updated to be stored in program memory to save some space
const byte tron_bold_00[8] PROGMEM = {B11111,B11000,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte tron_bold_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B11000,B11111}; // bits for special character 2/8
const byte tron_bold_02[8] PROGMEM = {B11111,B00111,B00111,B00111,B00111,B00111,B00111,B00111}; // bits for special character 3/8
const byte tron_bold_03[8] PROGMEM = {B11111,B11100,B11100,B11100,B11100,B11100,B11100,B11111}; // bits for special character 4/8
const byte tron_bold_04[8] PROGMEM = {B11111,B11100,B11100,B11100,B11100,B11100,B11100,B11100}; // bits for special character 5/8
const byte tron_bold_05[8] PROGMEM = {B11100,B11100,B11100,B11100,B11100,B11100,B11100,B11100}; // bits for special character 6/8
const byte tron_bold_06[8] PROGMEM = {B11111,B00000,B00000,B00000,B00000,B00000,B00000,B11111}; // bits for special character 7/8
const byte tron_bold_07[8] PROGMEM = {B11100,B11100,B11100,B11100,B11100,B11100,B11100,B11111}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte tron_bold_digits[10][4] = { {4,2,7,255}, { 254,5,254,5}, { 0,2,3,6}, { 0,2,1,255}, { 7,1,254,5}, { 3,6,1,255}, { 3,6,3,255}, { 0,2,254,5}, { 3,2,3,255}, { 3,2,254,2 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_tron_bold () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = tron_bold_digits[i][j];
  }
 }
 memcpy_P(buffer,tron_bold_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,tron_bold_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,tron_bold_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,tron_bold_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,tron_bold_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,tron_bold_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,tron_bold_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,tron_bold_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FINAL FONTE TRON BOLD ------------------------------------------------------

//------------------------------------- FONTE DOTS BIG ------------------------------------------------------
// set eight special characters for the font: dots_big   - updated to be stored in program memory to save some space
const byte dots_big_00[8] PROGMEM = {B11011,B11011,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte dots_big_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B11011,B11011}; // bits for special character 2/8
const byte dots_big_02[8] PROGMEM = {B11011,B11011,B00000,B00011,B00011,B00000,B11011,B11011}; // bits for special character 3/8
const byte dots_big_03[8] PROGMEM = {B11011,B11011,B00000,B11000,B11000,B00000,B11011,B11011}; // bits for special character 4/8
const byte dots_big_04[8] PROGMEM = {B11011,B11011,B00000,B11000,B11000,B00000,B11000,B11000}; // bits for special character 5/8
const byte dots_big_05[8] PROGMEM = {B11000,B11000,B00000,B11000,B11000,B00000,B11000,B11000}; // bits for special character 6/8
const byte dots_big_06[8] PROGMEM = {B11011,B11011,B00000,B00000,B00000,B00000,B11011,B11011}; // bits for special character 7/8
const byte dots_big_07[8] PROGMEM = {B11000,B11000,B00000,B11000,B11000,B00000,B11011,B11011}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte dots_big_digits[10][4] = { {4,5,7,5}, { 254,5,254,5}, { 6,2,3,6}, { 0,2,1,2}, { 7,1,254,5}, { 3,6,6,2}, { 3,6,3,2}, { 0,2,254,5}, { 3,2,3,2}, { 3,2,6,2 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_dots_big () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = dots_big_digits[i][j];
  }
 }
 memcpy_P(buffer,dots_big_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,dots_big_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,dots_big_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,dots_big_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,dots_big_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,dots_big_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,dots_big_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,dots_big_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FINAL FONTE DOTS BIG ------------------------------------------------------

//------------------------------------- FONTE BLOCKS ------------------------------------------------------
// set eight special characters for the font: blocks   - updated to be stored in program memory to save some space
const byte blocks_00[8] PROGMEM = {B11111,B11111,B11111,B11111,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte blocks_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111}; // bits for special character 2/8
const byte blocks_02[8] PROGMEM = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B00000}; // bits for special character 3/8
const byte blocks_03[8] PROGMEM = {B00000,B11111,B11111,B11111,B11111,B11111,B11111,B11111}; // bits for special character 4/8
const byte blocks_04[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 5/8
const byte blocks_05[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 6/8
const byte blocks_06[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 7/8
const byte blocks_07[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte blocks_digits[10][4] = { {255,255,255,255}, { 254,255,254,255}, { 0,255,255,1}, { 0,255,1,255}, { 255,1,254,255}, { 255,0,1,255}, { 255,0,255,255}, { 0,255,254,255}, { 2,2,3,3}, { 255,255,1,255 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_blocks () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = blocks_digits[i][j];
  }
 }
 memcpy_P(buffer,blocks_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,blocks_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,blocks_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,blocks_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,blocks_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,blocks_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,blocks_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,blocks_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FINAL FONTE BLOCKS ------------------------------------------------------

//------------------------------------- FONTE BLOCKS CUT------------------------------------------------------
// set eight special characters for the font: blocks_cut   - updated to be stored in program memory to save some space
const byte blocks_cut_00[8] PROGMEM = {B11111,B11111,B11111,B11111,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte blocks_cut_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111}; // bits for special character 2/8
const byte blocks_cut_02[8] PROGMEM = {B00001,B00011,B00111,B01111,B11111,B11111,B11111,B11111}; // bits for special character 3/8
const byte blocks_cut_03[8] PROGMEM = {B11111,B11111,B11111,B11111,B01111,B00111,B00011,B00001}; // bits for special character 4/8
const byte blocks_cut_04[8] PROGMEM = {B10000,B11000,B11100,B11110,B11111,B11111,B11111,B11111}; // bits for special character 5/8
const byte blocks_cut_05[8] PROGMEM = {B11111,B11111,B11111,B11111,B11110,B11100,B11000,B10000}; // bits for special character 6/8
const byte blocks_cut_06[8] PROGMEM = {B00000,B00000,B00000,B00000,B00000,B00001,B00011,B00111}; // bits for special character 7/8
const byte blocks_cut_07[8] PROGMEM = {B11100,B11000,B10000,B00000,B00000,B00000,B00000,B00000}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte blocks_cut_digits[10][4] = { {2,255,255,5}, { 254,2,254,255}, { 0,5,2,1}, { 0,255,1,5}, { 2,1,254,255}, { 255,0,1,5}, { 2,7,255,5}, { 0,255,254,5}, { 255,5,2,255}, { 2,255,6,5 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_blocks_cut () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = blocks_cut_digits[i][j];
  }
 }
 memcpy_P(buffer,blocks_cut_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,blocks_cut_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,blocks_cut_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,blocks_cut_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,blocks_cut_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,blocks_cut_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,blocks_cut_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,blocks_cut_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FIBAL FONTE BLOCKS CUT------------------------------------------------------

//------------------------------------- FONTE BLOCKS CROSSED ------------------------------------------------------
// set eight special characters for the font: blocks_crossed   - updated to be stored in program memory to save some space
const byte blocks_crossed_00[8] PROGMEM = {B11111,B11111,B11111,B11111,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte blocks_crossed_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111}; // bits for special character 2/8
const byte blocks_crossed_02[8] PROGMEM = {B11110,B11101,B11011,B10111,B01111,B11111,B11111,B11111}; // bits for special character 3/8
const byte blocks_crossed_03[8] PROGMEM = {B11111,B11111,B11111,B11111,B11110,B11101,B11111,B11111}; // bits for special character 4/8
const byte blocks_crossed_04[8] PROGMEM = {B11111,B11111,B10111,B01111,B11111,B11111,B11111,B11111}; // bits for special character 5/8
const byte blocks_crossed_05[8] PROGMEM = {B11111,B11111,B11111,B11110,B11101,B11011,B10111,B01111}; // bits for special character 6/8
const byte blocks_crossed_06[8] PROGMEM = {B11110,B11101,B11111,B11111,B11111,B11111,B11111,B11111}; // bits for special character 7/8
const byte blocks_crossed_07[8] PROGMEM = {B11111,B11111,B11111,B11111,B11111,B11111,B10111,B01111}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte blocks_crossed_digits[10][4] = { {255,7,6,255}, { 254,2,254,255}, { 0,255,2,1}, { 0,5,1,255}, { 2,1,254,255}, { 255,0,1,2}, { 255,0,3,4}, { 0,255,254,5}, { 3,4,3,4}, { 3,4,1,255 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_blocks_crossed () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = blocks_crossed_digits[i][j];
  }
 }
 memcpy_P(buffer,blocks_crossed_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,blocks_crossed_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,blocks_crossed_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,blocks_crossed_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,blocks_crossed_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,blocks_crossed_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,blocks_crossed_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,blocks_crossed_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FINAL FONTE BLOCKS CROSSED------------------------------------------------------

//------------------------------------- FONTE SQUARE FOUR ------------------------------------------------------
// set eight special characters for the font: square_four   - updated to be stored in program memory to save some space
const byte square_four_00[8] PROGMEM = {B11111,B11111,B11100,B11100,B00000,B00000,B00000,B00000}; // bits for special character 1/8
const byte square_four_01[8] PROGMEM = {B00000,B00000,B00000,B00000,B11100,B11100,B11111,B11111}; // bits for special character 2/8
const byte square_four_02[8] PROGMEM = {B11111,B11111,B01111,B01111,B01111,B01111,B11111,B11111}; // bits for special character 3/8
const byte square_four_03[8] PROGMEM = {B11111,B11111,B11110,B11110,B11110,B11110,B11111,B11111}; // bits for special character 4/8
const byte square_four_04[8] PROGMEM = {B00001,B00011,B00111,B01111,B00000,B00000,B00000,B00000}; // bits for special character 5/8
const byte square_four_05[8] PROGMEM = {B11110,B11110,B11110,B11110,B11110,B11110,B11110,B11110}; // bits for special character 6/8
const byte square_four_06[8] PROGMEM = {B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111}; // bits for special character 7/8
const byte square_four_07[8] PROGMEM = {B11110,B11110,B11110,B11110,B11110,B11110,B11111,B11111}; // bits for special character 8/8

// special character used for the individual digits, each digit is made from 4 special characters. Character 254 is empty, character 255 is fully filled rectangle
byte square_four_digits[10][4] = { {255,255,3,2}, { 4,5,254,5}, { 6,2,3,6}, { 0,2,1,2}, { 7,1,254,5}, { 3,6,6,2}, { 3,6,3,2}, { 0,2,254,5}, { 3,2,3,2}, { 3,2,6,2 } };

// switch font = set special characters and populate current_font_digits with digits from the selected font
void set_font_square_four () {
 for (int i=0; i<10; i++) {
  for (int j=0; j<4; j++) {
   current_font_digits[i][j] = square_four_digits[i][j];
  }
 }
 memcpy_P(buffer,square_four_00, 8);
 lcd.createChar(0 , buffer);
 memcpy_P(buffer,square_four_01, 8);
 lcd.createChar(1 , buffer);
 memcpy_P(buffer,square_four_02, 8);
 lcd.createChar(2 , buffer);
 memcpy_P(buffer,square_four_03, 8);
 lcd.createChar(3 , buffer);
 memcpy_P(buffer,square_four_04, 8);
 lcd.createChar(4 , buffer);
 memcpy_P(buffer,square_four_05, 8);
 lcd.createChar(5 , buffer);
 memcpy_P(buffer,square_four_06, 8);
 lcd.createChar(6 , buffer);
 memcpy_P(buffer,square_four_07, 8);
 lcd.createChar(7 , buffer);
}
//------------------------------------- FINAL FONTE SQUARE FOUR ------------------------------------------------------

// draw_big_digits is only needed once in the sketch
// this function draws a single digit on the xpos, ypos, taking 2x2 cells (using 4 special characters)
// before calling this function, make sure to set the font to populate the current_font_digits array and set special characters
void draw_big_digit(byte digit, byte xpos, byte ypos) {
  lcd.setCursor(xpos,ypos);           
  lcd.write(current_font_digits[digit][0]);
  lcd.write(current_font_digits[digit][1]);
  lcd.setCursor(xpos,ypos+1);           
  lcd.write(current_font_digits[digit][2]);
  lcd.write(current_font_digits[digit][3]);
}
// ------------------------------------------------------------------------------------------------------

//do relógio
String hora_inicial = "";
int horas, minutos, segundos;
unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000;  // Intervalo de 1 segundo

//do preço do btc
static unsigned long previousMillis = 0;  // Variável para armazenar o valor do último millis()
unsigned long interval = 0;    // Intervalo desejado de 1 minuto em milissegundos
int seg = 0, ler_tempo = 0;

unsigned long currentMillis = 0;  // Obtém o valor atual de millis()

boolean inicio = true;

// Da escolha de moeda
char fiatArray[3][4] = {
  "USD",
  "BRL",
  "EUR"
};
char fiatSymbolArray[3] = {
  'U',
  'R',
  'E'
};
char backk[2][4] = {
  "NAO",
  "SIM"
};


int fiatPosition = 0;

//para backlight
int luzativa = 1;

static void buttonHandlerDOWN(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    switch(state){
      case 1:
      break;
      case 2:
      limpa();
      Set_state(3);
      break;
      case 3:
      limpa();
      Set_state(4);
      break;
      case 4:
      limpa();
      Set_state(9);
      break;
      case 5:
      break;
      case 6:
      if(fiatPosition < 2){
        fiatPosition ++;
        EEPROM.write(btcfiat, fiatPosition);
        EEPROM.commit();
        Set_state(6);
      }
      break;
      case 7:
      if(ler_tempo > 20){
        ler_tempo --;
        EEPROM.write(tempo_att_preco, ler_tempo);
        EEPROM.commit();
        if(ler_tempo == 99 || ler_tempo == 100){
          limpa();
        }
        Set_state(7);
      }
      break;
      case 8:
        luzativa = 0;
        EEPROM.write(backlightt, luzativa);
        EEPROM.commit();
        Set_state(8);
        lcd.setBacklight(luzativa);
      break;
      case 9:
      limpa();
      Set_state(5);
      break;
      case 10:
      if(tipo_fonte < 5){
        tipo_fonte ++;
        setTipoFonte(tipo_fonte);
        EEPROM.write(tipofontee, tipo_fonte);
        EEPROM.commit();
        Set_state(10);
      }
      break;
    }
  }
}

static void buttonHandlerENTER(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    switch(state){
      case 1:
        limpa();
        Set_state(2);
      break;
      case 2:
        limpa();
        Set_state(1);
        reinicia();
      break;
      case 3:
        limpa();
        Set_state(6);
      break;
      case 4:
        limpa();
        Set_state(7);
      break;
      case 5:
        limpa();
        Set_state(8);
      break;
      case 6:
        limpa();
        Set_state(3);
      break;
      case 7:
        lerMemoria();
        limpa();
        Set_state(4);
      break;
      case 8:
        limpa();
        Set_state(5);
      break;
      case 9:
        limpa();
        Set_state(10);
      break;
      case 10:
        lerMemoria();
        limpa();
        Set_state(9);
      break;
    }
  }
}

static void buttonHandlerUP(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    switch(state){
      case 1:
      break;
      case 2:
      break;
      case 3:
      limpa();
      Set_state(2);
      break;
      case 4:
      limpa();
      Set_state(3);
      break;
      case 5:
      limpa();
      Set_state(9);
      break;
      case 6:
      if(fiatPosition > 0){
        fiatPosition --;
        EEPROM.write(btcfiat, fiatPosition);
        EEPROM.commit();
        Set_state(6);
      }
      break; 
      case 7:
      if(ler_tempo < 250){
        ler_tempo ++;
        EEPROM.write(tempo_att_preco, ler_tempo);
        EEPROM.commit();
        if(ler_tempo == 99 || ler_tempo == 100){
          limpa();
        }
        Set_state(7);
      }
      break;
      case 8:
        luzativa = 1;
        EEPROM.write(backlightt, luzativa);
        EEPROM.commit();
        Set_state(8);
        lcd.setBacklight(luzativa);
      break;
      case 9:
      limpa();
      Set_state(4);
      break;
      case 10:
      if(tipo_fonte > 0){
        tipo_fonte --;
        setTipoFonte(tipo_fonte);
        EEPROM.write(tipofontee, tipo_fonte);
        EEPROM.commit();
        Set_state(10);
      }
      break;
    }
  }
}

static Button myButtonDOWN(0, buttonHandlerDOWN);
static Button myButtonENTER(1, buttonHandlerENTER);
static Button myButtonUP(2, buttonHandlerUP);