#define CLOCKDELAY_MICROS 4

bool ID[] = {1,0,1,0};
bool ADDRESS[] = {0,0,0,0,0};
bool CMD[] = {0,0,0,0,0,0,0,0};
bool DATA[135] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int seg_A = 0, seg_B = 0, seg_C = 0, seg_D = 0, seg_E = 0, seg_F = 0, seg_G = 0, 
    seg_H = 0, seg_I = 0, seg_J = 0, seg_K = 0, seg_L = 0, seg_M = 0;

void LCD_INIT(){ 
  pinMode(MOSI,OUTPUT); pinMode(SCK,OUTPUT); pinMode(CS,OUTPUT);
  digitalWrite(MOSI,LOW); digitalWrite(SCK,LOW); digitalWrite(CS,HIGH);
  delay(100);
  
  ID[0] = 1; ID[1] = 0; ID[2] = 0; //BIAS
  CMD[0] = 0;
  CMD[1] = 1;
  CMD[2] = 0;
  CMD[3] = 1;
  CMD[4] = 0;
  CMD[5] = 0;
  CMD[6] = 0;
  CMD[7] = 0;
  LCD_UPDATE_CMD();

  ID[0] = 1; ID[1] = 0; ID[2] = 0; //RC256
  CMD[0] = 0;
  CMD[1] = 0;
  CMD[2] = 0;
  CMD[3] = 0;
  CMD[4] = 1;
  CMD[5] = 1;
  CMD[6] = 0;
  CMD[7] = 0;
  LCD_UPDATE_CMD();

  ID[0] = 1; ID[1] = 0; ID[2] = 0; //SYS DIS
  CMD[0] = 0;
  CMD[1] = 0;
  CMD[2] = 0;
  CMD[3] = 0;
  CMD[4] = 0;
  CMD[5] = 0;
  CMD[6] = 0;
  CMD[7] = 0;
  LCD_UPDATE_CMD();

  ID[0] = 1; ID[1] = 0; ID[2] = 0; //WDD1 DIS
  CMD[0] = 0;
  CMD[1] = 0;
  CMD[2] = 0;
  CMD[3] = 0;
  CMD[4] = 1;
  CMD[5] = 0;
  CMD[6] = 1;
  CMD[7] = 0;
  LCD_UPDATE_CMD();

  ID[0] = 1; ID[1] = 0; ID[2] = 0; //SYS EN
  CMD[0] = 0;
  CMD[1] = 0;
  CMD[2] = 0;
  CMD[3] = 0;
  CMD[4] = 0;
  CMD[5] = 0;
  CMD[6] = 1;
  CMD[7] = 0;
  LCD_UPDATE_CMD();
  
  ID[0] = 1; ID[1] = 0; ID[2] = 0; //LCD ON
  CMD[0] = 0;
  CMD[1] = 0;
  CMD[2] = 0;
  CMD[3] = 0;
  CMD[4] = 0;
  CMD[5] = 1;
  CMD[6] = 1;
  CMD[7] = 0;
  LCD_UPDATE_CMD();

}

void LCD_ALL_ON(){
  for (int COUNT = 0; COUNT < 131; COUNT++){
    DATA[COUNT] = 1;
  }
}

void LCD_ALL_OFF(){
  for (int COUNT = 0; COUNT < 131; COUNT++){
    DATA[COUNT] = 0;
  }
}

void LCD_CLEAR(){
  for (int COUNT = 0; COUNT < 131; COUNT++){
    DATA[COUNT] = 0;
  }
  LCD_UPDATE();
}

void LCD_UPDATE_CMD(){
digitalWrite(MOSI,HIGH); digitalWrite(SCK,HIGH); delayMicroseconds(CLOCKDELAY_MICROS*2);
digitalWrite(CS,LOW); delayMicroseconds(CLOCKDELAY_MICROS*2);
for (int COUNT = 0; COUNT < 4; COUNT++){
  digitalWrite(SCK,LOW);
  digitalWrite(MOSI,ID[COUNT]);
  delayMicroseconds(CLOCKDELAY_MICROS);
  digitalWrite(SCK,HIGH);
  delayMicroseconds(CLOCKDELAY_MICROS);
  digitalWrite(SCK,LOW);
}

for (int COUNT = 0; COUNT < 8; COUNT++){
  digitalWrite(SCK,LOW);
  digitalWrite(MOSI,CMD[COUNT]);
  delayMicroseconds(CLOCKDELAY_MICROS);
  digitalWrite(SCK,HIGH);
  delayMicroseconds(CLOCKDELAY_MICROS);
  digitalWrite(SCK,LOW);
}
digitalWrite(MOSI,LOW); digitalWrite(SCK,LOW); digitalWrite(CS,HIGH);
delayMicroseconds(CLOCKDELAY_MICROS);
}

void LCD_UPDATE(){
digitalWrite(MOSI,HIGH); digitalWrite(SCK,HIGH); delayMicroseconds(CLOCKDELAY_MICROS*2);
digitalWrite(CS,LOW); delayMicroseconds(CLOCKDELAY_MICROS*2);
ID[0] = 1; ID[1] = 0; ID[2] = 1;
//for (int j = 0, j < 32, j++){
    for (int COUNT = 0; COUNT < 4; COUNT++){
      digitalWrite(SCK,LOW);
      digitalWrite(MOSI,ID[COUNT]);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,HIGH);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,LOW);
    }
    for (int COUNT = 0; COUNT < 5; COUNT++){
      digitalWrite(SCK,LOW);
      digitalWrite(MOSI,ADDRESS[COUNT]);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,HIGH);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,LOW);
    }
    for (int COUNT = 0; COUNT < 128; COUNT++){
      digitalWrite(SCK,LOW);
      digitalWrite(MOSI,DATA[COUNT]);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,HIGH);
      delayMicroseconds(CLOCKDELAY_MICROS);
      digitalWrite(SCK,LOW);
    }
//}
digitalWrite(MOSI,LOW); digitalWrite(SCK,LOW); digitalWrite(CS,HIGH);
delayMicroseconds(CLOCKDELAY_MICROS);
}

void LCD_AF(bool STATE){
  DATA[30] = STATE;
}
void LCD_TA(bool STATE){
  DATA[61] = STATE;
}
void LCD_TP(bool STATE){
  DATA[62] = STATE;
}
void LCD_PTY(bool STATE){
  DATA[63] = STATE;
}
void LCD_DP(int STATE){
  switch (STATE){ //77 78
  case 0 : DATA[77] = 0; DATA[78] = 0; break;
  case 1 : DATA[77] = 0; DATA[78] = 1; break;
  case 2 : DATA[77] = 1; DATA[78] = 0; break;
  case 3 : DATA[77] = 1; DATA[78] = 1; break;
  }
}
void LCD_SD(bool STATE){
  DATA[109] = STATE;
}
void LCD_USB(bool STATE){
  DATA[110] = STATE;
}
void LCD_TC(bool STATE){
  DATA[119] = STATE;
}
void LCD_AUX(bool STATE){
  DATA[29] = STATE;
}
void LCD_LOUD(bool STATE){
  DATA[79] = STATE;
}
void LCD_CD(int STATE){
  switch (STATE){ //45 46 47
  case 0 : DATA[45] = 0; DATA[46] = 0; DATA[47] = 0; break;
  case 1 : DATA[45] = 1; DATA[46] = 0; DATA[47] = 0; break;
  case 2 : DATA[45] = 1; DATA[46] = 1; DATA[47] = 0; break;
  case 3 : DATA[45] = 1; DATA[46] = 1; DATA[47] = 1; break;
  }
}
void LCD_MUTE(bool STATE){
  DATA[31] = STATE;
}
void LCD_INT(bool STATE){
  DATA[15] = STATE;
}
void LCD_RDM(bool STATE){
  DATA[14] = STATE;
}
void LCD_RPT(bool STATE){
  DATA[13] = STATE;
}
void LCD_GRAPH(int ROWS){
  switch (ROWS){ 
  case 0 : DATA[123] = 0; DATA[122] = 0; DATA[121] = 0; DATA[120] = 0; DATA[124] = 0; DATA[125] = 0; break;
  case 1 : DATA[123] = 1; DATA[122] = 0; DATA[121] = 0; DATA[120] = 0; DATA[124] = 0; DATA[125] = 0; break;
  case 2 : DATA[123] = 1; DATA[122] = 1; DATA[121] = 0; DATA[120] = 0; DATA[124] = 0; DATA[125] = 0; break;
  case 3 : DATA[123] = 1; DATA[122] = 1; DATA[121] = 1; DATA[120] = 0; DATA[124] = 0; DATA[125] = 0; break;
  case 4 : DATA[123] = 1; DATA[122] = 1; DATA[121] = 1; DATA[120] = 1; DATA[124] = 0; DATA[125] = 0; break;
  case 5 : DATA[123] = 1; DATA[122] = 1; DATA[121] = 1; DATA[120] = 1; DATA[124] = 1; DATA[125] = 0; break;
  case 6 : DATA[123] = 1; DATA[122] = 1; DATA[121] = 1; DATA[120] = 1; DATA[124] = 1; DATA[125] = 1; break;
  }
}

void LCD_DIGIT(int DIGIT, char DISP_DATA){
  switch (DIGIT){
    case 1 : seg_A = 4; seg_B = 12; seg_C = 11; seg_D = 7; seg_E = 3; seg_F = 0; seg_G = 2; 
             seg_H = 9; seg_I = 5; seg_J = 8; seg_K = 1; seg_L = 10; seg_M = 6;
             break;
    case 2 : seg_A = 20; seg_B = 28; seg_C = 27; seg_D = 23; seg_E = 19; seg_F = 16; seg_G = 18; 
             seg_H = 25; seg_I = 21; seg_J = 24; seg_K = 17; seg_L = 26; seg_M = 22;
             break;
    case 3 : seg_A = 36; seg_B = 44; seg_C = 43; seg_D = 39; seg_E = 35; seg_F = 32; seg_G = 34; 
             seg_H = 41; seg_I = 37; seg_J = 40; seg_K = 33; seg_L = 42; seg_M = 38;
             break;
    case 4 : seg_A = 52; seg_B = 60; seg_C = 59; seg_D = 55; seg_E = 51; seg_F = 48; seg_G = 50; 
             seg_H = 57; seg_I = 53; seg_J = 56; seg_K = 49; seg_L = 58; seg_M = 54;
             break;
    case 5 : seg_A = 68; seg_B = 76; seg_C = 75; seg_D = 71; seg_E = 67; seg_F = 64; seg_G = 66; 
             seg_H = 73; seg_I = 69; seg_J = 72; seg_K = 65; seg_L = 74; seg_M = 70;
             break;
    case 6 : seg_A = 84; seg_B = 92; seg_C = 91; seg_D = 87; seg_E = 83; seg_F = 80; seg_G = 82; 
             seg_H = 89; seg_I = 85; seg_J = 88; seg_K = 81; seg_L = 90; seg_M = 86;
             break;
    case 7 : seg_A = 100; seg_B = 108; seg_C = 107; seg_D = 103; seg_E = 99; seg_F = 96; seg_G = 98; 
             seg_H = 105; seg_I = 101; seg_J = 104; seg_K = 97; seg_L = 106; seg_M = 102;
             break;
    case 8 : seg_A = 116; seg_B = 117; seg_C = 118; seg_D = 115; seg_E = 114; seg_F = 112; seg_G = 113;
             seg_H = 111; seg_I = 111; seg_J = 111; seg_K = 111; seg_L = 111; seg_M = 111;
             break;                                                                              
  }
  
  switch (DISP_DATA){
    case 0 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 32 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 36 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 37 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 38 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 39 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 40 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 41 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 42 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 1; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 43 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 44 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 45 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 46 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 47 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 48 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 49 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 50 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 51 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 52 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 53 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 54 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 55 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 56 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 57 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;                                                                                                        
   case 58 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 60 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 61 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 62 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 63 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 64 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 65 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 66 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 67 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 68 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 69 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 70 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 71 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 72 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 73 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 74 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 75 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 76 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 77 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 78 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 79 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 80 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 81 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 82 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 83 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 84 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 85 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 86 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 87 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 88 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 89 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 90 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 91 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 92 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 93 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 94 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 95 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 96 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 97 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 98 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 99 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 100 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 101 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 102 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 103 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 104 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 105 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 106 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 107 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 108 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 109 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 110 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 111 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 112 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 113 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 114 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 115 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 116 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 117 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 118 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 119 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 1; DATA[seg_D] = 0; DATA[seg_E] = 1; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 120 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   case 121 : DATA[seg_A] = 0; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 122 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 123 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 1; DATA[seg_L] = 0;
             DATA[seg_M] = 1; break;
   case 124 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 1; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 125 : DATA[seg_A] = 1; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 1; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 1; DATA[seg_K] = 0; DATA[seg_L] = 1;
             DATA[seg_M] = 0; break;
   case 126 : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
   case 127 : DATA[seg_A] = 1; DATA[seg_B] = 1; DATA[seg_C] = 1; DATA[seg_D] = 1; DATA[seg_E] = 1; DATA[seg_F] = 1;
             DATA[seg_G] = 1; DATA[seg_H] = 1; DATA[seg_I] = 1; DATA[seg_J] = 1; DATA[seg_K] = 1; DATA[seg_L] = 1;
             DATA[seg_M] = 1; break;
   default : DATA[seg_A] = 0; DATA[seg_B] = 0; DATA[seg_C] = 0; DATA[seg_D] = 0; DATA[seg_E] = 0; DATA[seg_F] = 0;
             DATA[seg_G] = 0; DATA[seg_H] = 0; DATA[seg_I] = 0; DATA[seg_J] = 0; DATA[seg_K] = 0; DATA[seg_L] = 0;
             DATA[seg_M] = 0; break;
             }
  
  LCD_UPDATE();
}

void LCD_PRINT(String PRINTED_STRING){
  for (int COUNT = 1; COUNT < 9; COUNT++){
     LCD_DIGIT(COUNT,PRINTED_STRING[COUNT-1]);
  }
}

void LCD_PRINT_NUM(long NUMBER){
  if(NUMBER > 9999999){
    NUMBER = 9999999;
  }
  if(NUMBER < -999999){
    NUMBER = 9999999;
  }
  if(NUMBER < 0){
    NUMBER = NUMBER*-1;
    String FORMED_NUMBER = "-000000";
    FORMED_NUMBER[1] = char(floor(NUMBER/pow(10,5))+48);
    FORMED_NUMBER[2] = char((floor(NUMBER/pow(10,4))) - (floor(NUMBER/pow(10,5))*10) +48);
    FORMED_NUMBER[3] = char((floor(NUMBER/pow(10,3))) - (floor(NUMBER/pow(10,4))*10) +48);
    FORMED_NUMBER[4] = char((floor(NUMBER/pow(10,2))) - (floor(NUMBER/pow(10,3))*10) +48);
    FORMED_NUMBER[5] = char((floor(NUMBER/pow(10,1))) - (floor(NUMBER/pow(10,2))*10) +48);
    FORMED_NUMBER[6] = char((floor(NUMBER/pow(10,0))) - (floor(NUMBER/pow(10,1))*10) +48);
    LCD_PRINT(FORMED_NUMBER);
  } else {
  String FORMED_NUMBER = "0000000";
  FORMED_NUMBER[0] = char(floor(NUMBER/pow(10,6))+48);
  FORMED_NUMBER[1] = char((floor(NUMBER/pow(10,5))) - (floor(NUMBER/pow(10,6))*10) +48);
  FORMED_NUMBER[2] = char((floor(NUMBER/pow(10,4))) - (floor(NUMBER/pow(10,5))*10) +48);
  FORMED_NUMBER[3] = char((floor(NUMBER/pow(10,3))) - (floor(NUMBER/pow(10,4))*10) +48);
  FORMED_NUMBER[4] = char((floor(NUMBER/pow(10,2))) - (floor(NUMBER/pow(10,3))*10) +48);
  FORMED_NUMBER[5] = char((floor(NUMBER/pow(10,1))) - (floor(NUMBER/pow(10,2))*10) +48);
  FORMED_NUMBER[6] = char((floor(NUMBER/pow(10,0))) - (floor(NUMBER/pow(10,1))*10) +48);
  LCD_PRINT(FORMED_NUMBER);
  }
}

void LCD_PRINT_SNUM(long NUMBER){
  if(NUMBER > 9){
    NUMBER = 9;
  }
  char FORMED_NUMBER = '0';
  FORMED_NUMBER = char(floor(NUMBER/1)+48);
  LCD_DIGIT(8,FORMED_NUMBER);
}
