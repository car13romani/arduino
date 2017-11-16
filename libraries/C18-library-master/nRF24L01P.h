/* 
 * File:   nRF24L01P.h
 * Author: Vinh
 *
 * Created on Ngày 12 tháng 8 năm 2012, 11:04
 */

#ifndef NRF24L01P_H
#define	NRF24L01P_H

/*******************************************************************************
 * Definition table: nRF24L01P pins define
 * Define custom pins for communication based on designs
 * MUST configured for approriate operation
 ******************************************************************************/
#define     NRF24_CE    LATCbits.LATC0
#define     NRF24_CSN   LATCbits.LATC1
#define     NRF24_IRQ   PORTCbits.RC2
#define     NRF24_CLK   LATBbits.LATB1
#define     NRF24_MOSI  LATCbits.LATC7
#define     NRF24_MISO  PORTBbits.RB0

#define     DELAY_15US  Delay10TCYx(15)
#define     DELAY_130US Delay10TCYx(60)
#define     DELAY_2MS   Delay10KTCYx(2)

/*******************************************************************************
 * Prototyped functions used in NRF24L01P operation
 ******************************************************************************/
void NRF24_Transmit(void);
unsigned char NRF24_Check_DataSent(void);
unsigned char NRF24_Check_DataReady(void);
unsigned char NRF24_Check_MaxRetry(void);
unsigned char NRF24_Status(void);
unsigned char NRF24_IRQActive(void);
void NRF24_Clear_DataSent(void);
void NRF24_Clear_DataReady(void);
void NRF24_Clear_MaxRetry(void);
void NRF24_Clear_Status(void);

unsigned char NRF24_WriteCommand(unsigned char command);
unsigned char WriteRead_SPI(unsigned char byte);
unsigned char NRF24_WriteByte(unsigned char command, unsigned char value);
unsigned char NRF24_WriteArray(unsigned char command, unsigned char *array, unsigned char length);
unsigned char NRF24_WriteString(unsigned char command, const rom char *string, unsigned char length);
unsigned char NRF24_ReadByte(unsigned char command);
unsigned char NRF24_ReadArray(unsigned char command, unsigned char *array);
/*******************************************************************************
 * Definition table:    nRF24L01P SPI commands
 * Description for each command:
 *  R_REGISTER, W_REGISTER: Used to read and write to nRF24L01P registers.
 *                          Always using bitwise OR with last 5 bits registers
 *                          address to before sending these two commands
 *  R_RX_PAYLOAD: Used in RX mode. Read RX payload: 1-32 bytes.
 *                Payload is deleted from FIFO after this command
 *  W_TX_PAYLOAD: Used in TX mode. Write TX payload: 1-32 bytes.
 *  FLUSH_TX: Used in TX mode. Flush TX FIFO
 *  FLUSH_RX: Used in RX mode. Flush RX FIFO
 *  REUSE_TX_PL: More on this command through datasheet. Rarely used
 *  R_RX_PL_WID: Read the top RX payload width. If read result larger than 32,
 *               flush the RX FIFO
 *  W_ACK_PAYLOAD: Used in RX mode. Write payload together with ACK packet on
 *                 pipe 0-5, choosing pipe using bitwise OR at bit<0:2>, valid
 *                 value from 000 - 101.
 *  W_TX_PAYLOAD_NOACK: Used in TX mode. Disable AUTOACK on this specific packet
 *  NOP: no operation, use this to read STATUS register
 ******************************************************************************/
#define     R_REGISTER           0b00000000
#define     W_REGISTER           0b00100000
#define     R_RX_PAYLOAD         0b01100001
#define     W_TX_PAYLOAD         0b10100000
#define     FLUSH_TX             0b11100001
#define     FLUSH_RX             0b11100010
#define     REUSE_TX_PL          0b11100011
#define     R_RX_PL_WID          0b01100000
#define     W_ACK_PAYLOAD        0b10101000
#define     W_TX_PAYLOAD_NOACK   0b10110000
#define     NOP                  0b11111111

/*******************************************************************************
 * Definition table:    nRF24L01P register map
 * Description: Used these registers' address to OR'ed with R_REGISTER and
 *              W_REGISTER command

 ******************************************************************************/
#define     CONFIG      0x00
#define     EN_AA       0x01
#define     EN_RXADDR   0x02
#define     SETUP_AW    0x03
#define     SETUP_RETR  0x04
#define     RF_CH       0x05
#define     RF_SETUP    0x06
#define     STATUS      0x07
#define     OBSERVE_TX  0x08
#define     RPD         0x09
#define     RX_ADDR_P0  0x0A
#define     RX_ADDR_P1  0x0B
#define     RX_ADDR_P2  0x0C
#define     RX_ADDR_P3  0x0D
#define     RX_ADDR_P4  0x0E
#define     RX_ADDR_P5  0x0F
#define     TX_ADDR     0x10
#define     RX_PW_P0    0x11
#define     RX_PW_P1    0x12
#define     RX_PW_P2    0x13
#define     RX_PW_P3    0x14
#define     RX_PW_P4    0x15
#define     RX_PW_P5    0x16
#define     FIFO_STATUS 0x17
#define     DYNPD       0x1C
#define     FEATURE     0x1D

/*******************************************************************************
 * Definition table:    nRF24L01P sub-register bitwise
 * Description: OR these bitwise together to write to specific register

 ******************************************************************************/
//0x00 - CONFIG register
#define     MASK_RX_DR  0b01000000 //Mask interrupt by RX_DR. 0: enable active low interrupt on IRQ pin
#define     MASK_TX_DS  0b00100000 //Mask interrupt by TX_DS. 0: enable active low interrupt on IRQ pin
#define     MASK_MAX_RT 0b00010000 //Mask interrupt by MAX_RT. 0: enable active low interrupt on IRQ pin
#define     EN_CRC      0b00001000 //Enable CRC checking, forced 1 if one of bits of EN_AA high
#define     CRCO        0b00000100 //1:16bit CRC, 0: 8bit CRC
#define     PWR_UP      0b00000010 //1:PWRUP, 0: PWRDOWN
#define     PRIM_RX     0b00000001 //1: PRX, 0: PTX

//0x01 - EN_AA register
#define     ENAA_P5     0b00100000  //Enable Auto Ack on data pipe 5
#define     ENAA_P4     0b00010000  //Enable Auto Ack on data pipe 5
#define     ENAA_P3     0b00001000  //Enable Auto Ack on data pipe 5
#define     ENAA_P2     0b00000100  //Enable Auto Ack on data pipe 5
#define     ENAA_P1     0b00000010  //Enable Auto Ack on data pipe 5
#define     ENAA_P0     0b00000001  //Enable Auto Ack on data pipe 5
#define     ENAA_ALLP   0b00111111  //Enable Auto Ack on data pipe 5

//0x02 - EN_RXADDR register
#define     ERX_P5      0b00100000  //Enable data pipe 5
#define     ERX_P4      0b00010000  //Enable data pipe 4
#define     ERX_P3      0b00001000  //Enable data pipe 3
#define     ERX_P2      0b00000100  //Enable data pipe 2
#define     ERX_P1      0b00000010  //Enable data pipe 1
#define     ERX_P0      0b00000001  //Enable data pipe 0
#define     ERX_ALLP    0b00111111  //Enable all data pipe

//0x03 - SETUP_AW register
#define     AW_3BYTE    0b00000001  //Address width: 3 bytes
#define     AW_4BYTE    0b00000010  //Address width: 4 bytes
#define     AW_5BYTE    0b00000011  //* Address width: 5 bytes

//0x04 - SETUP_RETR register
#define     ARD_250     0b00000000  // Auto re-transmit delay: 250us
#define     ARD_500     0b00010000  //* 500us
#define     ARD_750     0b00100000  //750us
#define     ARD_1000    0b00110000  //1000us
#define     ARD_1250    0b01000000  //1250us
#define     ARD_1500    0b01010000  //1500us
#define     ARD_1750    0b01100000  //1750us
#define     ARD_2000    0b01110000  //2000us
#define     ARD_2250    0b10000000  //2250us
#define     ARD_2500    0b10010000  //2500us
#define     ARD_2750    0b10100000  //2750us
#define     ARD_3000    0b10110000  //3000us
#define     ARD_3250    0b11000000  //3250us
#define     ARD_3500    0b11010000  //3500us
#define     ARD_3750    0b11100000  //3750us
#define     ARD_4000    0b11110000  //4000us
#define     ARC_0       0b00000000  //* Auto re-transmit disabled
#define     ARC_1       0b00000001  //1 re-transmit on fail of Auto Ack
#define     ARC_2       0b00000010  //2
#define     ARC_3       0b00000011  //3
#define     ARC_4       0b00000100  //4
#define     ARC_5       0b00000101  //5
#define     ARC_6       0b00000110  //6
#define     ARC_7       0b00000111  //7
#define     ARC_8       0b00001000  //8
#define     ARC_9       0b00001001  //9
#define     ARC_10      0b00001010  //10
#define     ARC_11      0b00001011  //11
#define     ARC_12      0b00001100  //12
#define     ARC_13      0b00001101  //13
#define     ARC_14      0b00001110  //14
#define     ARC_15      0b00001111  //* 15 re-transmit on fail of Auto Ack

//0x05 - RF_CH Edit bit <6:0> to choose the frequency to work on (1 - 125 frequency)

//0x06 - RF_SETUP register
#define     CONT_WAVE   0b10000000  //Only sing this to test carrier wave
#define     RF_DR_LOW   0b00100000  //* Low will set Datarate to 250kbps
#define     PLL_LOCK    0b00010000  //PLL lock signal. Used in test only
#define     RF_DR_1M    0b00000000  //* Set datarate to 1Mbps
#define     RF_DR_2M    0b00001000  //* Set datarate to 2Mbps
#define     RF_PWR_M18  0b00000000  //Set RF power in TX mode to -18dBm
#define     RF_PWR_M12  0b00000001  //Set RF power in TX mode to -12dBm
#define     RF_PWR_M6   0b00000010  //Set RF power in TX mode to -6dBm
#define     RF_PWR_M0   0b00000011  //* Set RF power in TX mode to 0dBm

//0x07 - STATUS register
#define     RX_DR       0b01000000  //Read as '1' when new data arrives, write '1' will clear flag
#define     TX_DS       0b00100000  //Read as '1' when packet transmitted on TX, write '1' will clear flag
#define     MAX_RT      0b00010000  //Read as '1' when max ARC reached. Must write '1' to continue operation
#define     RX_P_NO     0b00001110  //OR this with STATUS register to get pipe number of FIFO package
#define     TX_FULL     0b00000001  //Read '1' if TX FIFO is full. Read '0' if available location in FIFO

//0x08 - OBSERVE_TX
#define     PLOS_CNT    0b11110000  //Increment 1 each time MAX_RT set. Maximum 15 times. Write to RF_CH to reset
#define     ARC_CNT     0b00001111  //Re-transmit counter. Reset when transfer new package

//0x09 - RPD. Read bit <0> of this register on RX mode. If RF signal less than -64dBm, RPD = 0

//0x0A - RX_ADDR_P0 --> 0x0F - RX_ADDR_P5.Set RX address of that pipeline

//0x10 - TX_ADDR. Set TX address. Must be the same with RX_ADDR_P0 if using Auto Ack

//0x11 - RX_PW_P0 --> 0x16 - RX_PW_5. Set number of bytes in data pipe

//0x17 - FIFO_STATUS register
#define     TX_FIFO_REUSE   0b01000000  //Indicate REUSE_TX_PL command is active
#define     TX_FIFO_FULL    0b00100000  //TX FIFO full indicator
#define     TX_FIFO_EMPTY   0b00010000  //TX FIFO empty indicator
#define     RX_FIFO_FULL    0b00000010  //RX FIFO full indicator
#define     RX_FIFO_EMPTY   0b00000001  //RX FIFO empty indicator

//0x1C - DYNPD
#define     DPL_P5      0b00100000
#define     DPL_P4      0b00010000
#define     DPL_P3      0b00001000
#define     DPL_P2      0b00000100
#define     DPL_P1      0b00000010
#define     DPL_P0      0b00000001
#define     DPL_ALLP    0b00111111

//0x1D - FEATURE
#define     EN_DPL      0b00000100
#define     EN_ACK_PAY  0b00000010
#define     EN_DYN_ACK  0b00000001

#endif	/* NRF24L01P_H */

