#include "nRF24L01P.h"
/*******************************************************************************
 * Basic macro commands on controlling pins
 * ****************************************************************************/
#define     NRF24_SELECT      NRF24_CSN = 0
#define     NRF24_UNSELECT    NRF24_CSN = 1
#define     NRF24_START       NRF24_CE = 1
#define     NRF24_STOP        NRF24_CE = 0

/*******************************************************************************
 * NRF24L01P operating commands
 ******************************************************************************/
void NRF24_Transmit(void)
{
    NRF24_START;
    DELAY_15US;
    NRF24_STOP;
}
/*******************************************************************************
 * NRF24L01P checking status commands
 ******************************************************************************/
unsigned char NRF24_Check_DataSent(void)
{
    unsigned char temp;
    temp = NRF24_Status();
    return (temp & TX_DS);
}
unsigned char NRF24_Check_DataReady(void)
{
    unsigned char temp;
    temp = NRF24_Status();
    return (temp & RX_DR);
}
unsigned char NRF24_Check_MaxRetry(void)
{
    unsigned char temp;
    temp = NRF24_Status();
    return (temp & MAX_RT);
}
unsigned char NRF24_Status(void)
{
    unsigned char temp;
    NRF24_SELECT;
    temp = WriteRead_SPI(NOP);
    NRF24_UNSELECT;
    return (temp);
}
unsigned char NRF24_IRQActive(void)
{
    return (!NRF24_IRQ);
}
/*******************************************************************************
 * NRF24L01P status respond commands
 ******************************************************************************/
void NRF24_Clear_DataSent(void)
{
    NRF24_SELECT;
    NRF24_WriteByte(W_REGISTER | STATUS, TX_DS);
    NRF24_UNSELECT;
}
void NRF24_Clear_DataReady(void)
{
    NRF24_SELECT;
    NRF24_WriteByte(W_REGISTER | STATUS, RX_DR);
    NRF24_UNSELECT;
}
void NRF24_Clear_MaxRetry(void)
{
    NRF24_SELECT;
    NRF24_WriteByte(W_REGISTER | STATUS, MAX_RT);
    NRF24_UNSELECT;
}
void NRF24_Clear_Status(void)
{
    NRF24_SELECT;
    NRF24_WriteByte(W_REGISTER | STATUS, TX_DS | RX_DR | MAX_RT);
    NRF24_UNSELECT;
}
/*******************************************************************************
 * SPI data commands for NRF24L01P
 ******************************************************************************/
unsigned char NRF24_WriteCommand(unsigned char command)
{
    NRF24_SELECT;
    WriteRead_SPI(command);
    NRF24_UNSELECT;
}
unsigned char NRF24_WriteByte(unsigned char command, unsigned char value)
{
    unsigned char temp;
    NRF24_SELECT;
    temp = WriteRead_SPI(command);
    WriteRead_SPI(value);
    NRF24_UNSELECT;
    return (temp);
}

unsigned char NRF24_WriteArray(unsigned char command, unsigned char *array, unsigned char length)
{
    unsigned char temp, i;
    NRF24_SELECT;
    temp = WriteRead_SPI(command);
    for (i=0;i<length;i++)
    {
        WriteSPI(*array++);
    }
    NRF24_UNSELECT;
    return (temp);
}

unsigned char NRF24_WriteString(unsigned char command, const rom char *string, unsigned char length)
{
    unsigned char i, temp;
    NRF24_SELECT;
    temp = WriteRead_SPI(command);
    for(i=0; i< length; i++)
    {
        WriteSPI(*string++);
    }
    NRF24_UNSELECT;
    return (temp);
}

unsigned char NRF24_ReadByte(unsigned char command)
{
    unsigned char temp;
    NRF24_SELECT;
    WriteRead_SPI(command);
    temp = ReadSPI();
    NRF24_UNSELECT;
    return (temp);
}

unsigned char NRF24_ReadArray(unsigned char command, unsigned char *array)
{
    unsigned char temp, i;
    unsigned char *length;
    if (command == R_RX_PAYLOAD)    //if is read rx payload
    {
        *length = NRF24_ReadByte(R_RX_PL_WID);  //determine the width of that payload
    }
    else
    {
        *length = (NRF24_ReadByte(R_REGISTER | SETUP_AW) + 2); //else read address width, read SETUP_AW register
    }

    NRF24_SELECT;
    temp = WriteRead_SPI(command);

    for(i=0; i < *length; i++)
    {
        *array = ReadSPI();
        array++;
    }
    NRF24_UNSELECT;
    return (temp);
}
/*******************************************************************************
 * Custom SPI command to send and receive command at the same time
 ******************************************************************************/
unsigned char WriteRead_SPI(unsigned char byte)
{
    PIR1bits.SSPIF = 0;         // Clear interrupt flag
    SSPCON1bits.WCOL = 0;	//Clear any previous write collision
    SSPBUF = byte;
    while(!SSPSTATbits.BF);
    return (SSPBUF);
}


