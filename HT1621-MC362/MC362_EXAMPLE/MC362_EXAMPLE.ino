#define MOSI 11
#define SCK 13
#define CS 9

void setup() {
//Serial.begin(9600);
LCD_INIT();
LCD_CLEAR();
LCD_PRINT("STARTED");
delay(1000);
LCD_ALL_ON();
LCD_UPDATE();
delay(1000);
LCD_CLEAR();
}

void loop() {
LCD_PRINT_NUM(millis());
delay(10);
}








