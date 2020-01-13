/*
 * MC362-DHT11.cpp
 *
 * Created: 1/13/2020 10:48:29 PM
 * Author : hi
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr-holtek-ht1621-MC362/ht1621-MC362.h>
#include <avr-lib-dht-03/src/dht/dht.h>


int main(void)
{	
	
	LCD_INIT();
	LCD_ALL_OFF();
	LCD_UPDATE();
	
	long GRAPH_SCALE = 0;
	int temperature_max = 35;
	int humidity_max = 60;
	
	int8_t temperature = 0;
	int8_t humidity = 0;
	
    while (1) 
    {
	dht_gettemperaturehumidity(&temperature, &humidity);
	
	LCD_CLEAR();
	LCD_PRINT("TMP   C");
	LCD_PRINT_NUM(temperature,6);
	GRAPH_SCALE = temperature*7/temperature_max;
	LCD_GRAPH(GRAPH_SCALE);
	LCD_UPDATE();
	_delay_ms(3000);
	
	LCD_CLEAR();
	LCD_PRINT("HUM   %");
	LCD_PRINT_NUM(humidity,6);
	GRAPH_SCALE = humidity*7/humidity_max;
	LCD_GRAPH(GRAPH_SCALE);
	LCD_UPDATE();
	_delay_ms(3000);
    }
}

