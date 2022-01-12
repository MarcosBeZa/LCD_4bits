#include "LCD_4bits.h"

void Lcd_Init(void) {
    char SR = TRIS_LCD & 0x03;
    char data = PORT_LCD & 0x03;
    TRIS_LCD = (0x00 | SR);
    PORT_LCD = (0x00 | data);
    for(char a = 0; a < 4; a++) delay_5ms_LCD();
    PORT_LCD = (0x38 | data);
    delay_5ms_LCD();;
    PORT_LCD = (0x30 | data);
    PORT_LCD = (0x38 | data);
    for(char a = 0; a < 3; a++) delay_40us_LCD();
    PORT_LCD = (0x30 | data);
    PORT_LCD = (0x38 | data);
    delay_5ms_LCD();;
    PORT_LCD = (0x30 | data);
    PORT_LCD = (0x28 | data);
    delay_5ms_LCD();;
    PORT_LCD = (0x20 | data);
    
    Lcd_Cmd(LCD_4BITS_2LINES_5X8);
    Lcd_Cmd(LCD_DISPLAY_ON_CURSOR_OFF_CHARACTER_BLINK_OFF);
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_INCREASE_DDRAM_DISPLAY_SHIFT_OFF);
}
void Lcd_Cmd(char cmd)  {
    char nibble_high, nibble_high_enable, nibble_low, nibble_low_enable;
    char data;
    data = PORT_LCD & 0x03;
    nibble_high = (cmd & 0xF0) | data;
    nibble_high_enable = nibble_high | 0x08;
    nibble_low = ((cmd << 4) & 0xF0) | data;
    nibble_low_enable = nibble_low | 0x08;
    
    PORT_LCD = nibble_high_enable,
    delay_2ms_LCD();
    PORT_LCD = nibble_high;
    PORT_LCD = nibble_low_enable;
    delay_2ms_LCD();
    PORT_LCD = nibble_low;
}
void Lcd_SetCursor(char row, char column)   {
    char address;
    address = 0x80+((row-1)*0x40)+(column-1);
    Lcd_Cmd(address);
}
void Lcd_Chr_Cp(char out_char)  {
    char nibble_high, nibble_high_enable, nibble_low, nibble_low_enable;
    char data;
    data = PORT_LCD & 0x03;
    nibble_high = (out_char & 0xF0) | 0x04 | data;;
    nibble_high_enable = nibble_high | 0x08;
    nibble_low = ((out_char << 4) & 0xF0) | 0x04 | data;
    nibble_low_enable = nibble_low | 0x08;
    
    PORT_LCD = nibble_high_enable;
    delay_40us_LCD();
    PORT_LCD = nibble_high;
    PORT_LCD = nibble_low_enable;
    delay_40us_LCD();
    PORT_LCD = nibble_low;
}
void Lcd_Chr(char row, char column, char out_char)  {
    char address;
    address = 0x80+((row-1)*0x40)+(column-1);
    Lcd_Cmd(address);
    Lcd_Chr_Cp(out_char);
}
void Lcd_String_Cp(char *txt)  {
    for(char a = 0; txt[a] != '\0'; a++)    {
        Lcd_Chr_Cp(txt[a]);
    }
}
void Lcd_String(char row, char column, char *txt)   {
    char address;
    address = 0x80+((row-1)*0x40)+(column-1);
    Lcd_Cmd(address);
    for(char a = 0; txt[a] != '\0'; a++)    {
        Lcd_Chr_Cp(txt[a]);
    }
    
}
