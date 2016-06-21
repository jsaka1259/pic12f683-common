#include <common.h>

void lcd_init(void)
{
    delay_100ms(1);
    lcd_cmd(0x38);                      // 8bit 2line Noraml mode
    lcd_cmd(0x39);                      // 8bit 2line Extend mode
    lcd_cmd(0x14);                      // OSC 183Hz BIAS 1/5
    lcd_cmd(0x70 + (CONTRAST & 0x0F));  // CONTRAST
    lcd_cmd(0x50 + (CONTRAST >> 4));    // CONTRAST
    lcd_cmd(0x6C);                      // Follower for 3.3V
    delay_100ms(3);
    lcd_cmd(0x38);                      // Set Normal mode
    lcd_cmd(0x0C);                      // Display On
    lcd_cmd(0x01);                      // Clear Display
}

void lcd_cmd(uint8_t cmd)
{
    i2c_start();                        // I2C Start Condition
    i2c_send(ST7032_ADRES);             // LCD Device Address
    i2c_send(0x00);                     // Set Command Mode
    i2c_send(cmd);                      // Output Command
    i2c_stop();                         // I2C Stop Condition
    
    /* Clear or Home */
    if((cmd == 0x01) || (cmd == 0x02))
    {
        __delay_us(2);                  // Wait 2usec
    }
    else
    {
        __delay_us(30);                 // Wait 30usec
    }
}

void lcd_putch(uint8_t data)
{
    i2c_start();                        // I2C Start Condition
    i2c_send(ST7032_ADRES);             // LCD Device Address
    i2c_send(0x40);                     // Set Data Mode
    i2c_send(data);                     // Output Data
    i2c_stop();                         // I2C Stop Condition
    __delay_us(30);                     // Wait 30usec
}

void lcd_puts(const uint8_t *ptr)
{
    while(*ptr != 0)                    // Get a Charctor
    {
        lcd_putch(*ptr++);              // Display a Charctor and Increment Pointer
    }
}

void lcd_clear(void)
{
    lcd_cmd(0x01);                      // Clear Display
}

void delay_100ms(uint16_t time)
{
    time *= 4;                          // 4 times
    while(time)
    {
        __delay_ms(25);                 // 25msec
        time--;                         // 100msec X time
    }
}
