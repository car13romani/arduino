/* 
 * File:   main_nRF24L01_receiver.c
 * Author: Vinh
 *
 * Created on Ngày 15 tháng 9 năm 2012, 14:23
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18F4550.h>
#include <delays.h>
#include <spi.h>
#include "nRF24L01P.h"
#include "nRF24L01P.c"

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC4_PLL6// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = ON      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)
/*
 *
 */

/*
 *
 */
unsigned char buf[];
void main(void)
{
    ADCON1bits.PCFG = 0x0F; //All analog pin are digital
    TRISA = 0x00;
	TRISB = 0x01; //RB0 input, RB1 output
    TRISC = 0x04; //RC0,RC1,RC7 output. RC2 input
    TRISD = 0x00; //PORTD output bit for testing
	TRISE = 0x00;

    SSPSTAT = 0xC0; //Sample at the end, transmit on falling edge
    SSPCON1 = 0x20; //Idle state low, FOSC/4

    LATD = 0;
    Delay10KTCYx(255);
    NRF24_WriteByte(W_REGISTER | CONFIG, 0b00001111);
    DELAY_2MS;
    NRF24_WriteByte(W_REGISTER | EN_AA, 0x01);
    NRF24_WriteByte(W_REGISTER | EN_RXADDR, 0x01);
    NRF24_WriteByte(W_REGISTER | SETUP_AW, 0x03); //5 byte address width
    NRF24_WriteByte(W_REGISTER | SETUP_RETR, ARD_1000 | ARC_15);
    NRF24_WriteByte(W_REGISTER | RF_CH, 55);
    NRF24_WriteByte(W_REGISTER | RF_SETUP, 0b00000110); //1Mbps, 0dBm
    NRF24_WriteString(W_REGISTER | RX_ADDR_P0, "0rdda", 5);
    NRF24_WriteString(W_REGISTER | TX_ADDR, "0rdda", 5);
    NRF24_WriteByte(W_REGISTER | RX_PW_P0, 0x01);

    /* Testing only
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | CONFIG);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | EN_AA);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | EN_RXADDR);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | SETUP_AW);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | SETUP_RETR);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | RF_CH);
    LATD = buf[0];
    Delay10KTCYx(250);
    *buf = NRF24_ReadByte(R_REGISTER | RF_SETUP);
    LATD = buf[0];
    Delay10KTCYx(250);
    NRF24_ReadArray(R_REGISTER | RX_ADDR_P0, buf);
    LATD = buf[0];
    Delay10KTCYx(250);
    NRF24_ReadArray(R_REGISTER | TX_ADDR, buf);
    LATD = buf[0];
    Delay10KTCYx(250);
    LATD = 0x00;
    Delay10KTCYx(250);
    */
    while(1)
    {
        NRF24_START;
        while( !(NRF24_IRQActive() && NRF24_Check_DataReady()) );
        NRF24_STOP;
        LATD = NRF24_ReadByte(R_RX_PAYLOAD);
        NRF24_WriteCommand(FLUSH_RX);
        NRF24_Clear_Status();
        Delay10KTCYx(250);
    }
}

