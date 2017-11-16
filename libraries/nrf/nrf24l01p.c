/* Copyright (c) 2007 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT. 
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRENTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 * $LastChangedRevision: 2132 $
 */ 

 /** @file
 *
 * @author Runar Kjellhaug
 *
 */

#include <stdint.h>
#include <stdbool.h>

//#include "nordic_common.h"
#include "nrf24l01p.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BIT(index) ((uint8_t)1 << (uint8_t)(index))
#define BIT_COND(data,index,condition) (((uint8_t)(data) & ~BIT(index)) | ((condition) ? BIT(index) : (uint8_t)0))

void nrf24l01p_set_irq_mode(nrf24l01p_irq_source_t int_source, bool irq_state)
{
  nrf24l01p_write_reg(NRF24L01P_CONFIG, BIT_COND(nrf24l01p_read_reg(NRF24L01P_CONFIG), int_source, !irq_state));
}

uint8_t nrf24l01p_get_clear_irq_flags(void)
{
  enum { IRQ_FLAGS = BIT(NRF24L01P_IRQ_MAX_RT) | BIT(NRF24L01P_IRQ_TX_DS) | BIT(NRF24L01P_IRQ_RX_DR) };
  return nrf24l01p_write_reg(NRF24L01P_STATUS, IRQ_FLAGS) & IRQ_FLAGS;
}

void nrf24l01p_clear_irq_flag(nrf24l01p_irq_source_t int_source)
{
  nrf24l01p_write_reg(NRF24L01P_STATUS, BIT(int_source));
}
 
bool nrf24l01p_get_irq_mode(nrf24l01p_irq_source_t int_type)
{
  return !(nrf24l01p_read_reg(NRF24L01P_CONFIG) & BIT(int_type));
}

uint8_t nrf24l01p_get_irq_flags(void)
{
  return nrf24l01p_nop() & (BIT(6)|BIT(5)|BIT(4));
}

void nrf24l01p_set_crc_mode(nrf24l01p_crc_mode_t crc_mode)
{
  nrf24l01p_write_reg(NRF24L01P_CONFIG, (nrf24l01p_read_reg(NRF24L01P_CONFIG) & ~(BIT(3)|BIT(2))) | ((uint8_t)crc_mode<<2u));
}

void nrf24l01p_open_pipe(nrf24l01p_address_t pipe_num, bool auto_ack)
{
  switch(pipe_num)
  {
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
    case NRF24L01P_PIPE2:
    case NRF24L01P_PIPE3:
    case NRF24L01P_PIPE4:
    case NRF24L01P_PIPE5:
      nrf24l01p_write_reg(NRF24L01P_EN_RXADDR, nrf24l01p_read_reg(NRF24L01P_EN_RXADDR) | BIT(pipe_num));
      nrf24l01p_write_reg(NRF24L01P_EN_AA, BIT_COND(nrf24l01p_read_reg(NRF24L01P_EN_AA), pipe_num, auto_ack));
      break;

    case NRF24L01P_ALL:
      nrf24l01p_write_reg(NRF24L01P_EN_RXADDR, (uint8_t)~(BIT(7)|BIT(6)));

      if(auto_ack)
        nrf24l01p_write_reg(NRF24L01P_EN_AA, (uint8_t)~(BIT(7)|BIT(6)));
      else
        nrf24l01p_write_reg(NRF24L01P_EN_AA, 0);
      break;
      
    default:
      break;
  }
}

void nrf24l01p_close_pipe(nrf24l01p_address_t pipe_num)
{
  switch(pipe_num)
  {
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
    case NRF24L01P_PIPE2:
    case NRF24L01P_PIPE3:
    case NRF24L01P_PIPE4:
    case NRF24L01P_PIPE5:
      nrf24l01p_write_reg(NRF24L01P_EN_RXADDR, nrf24l01p_read_reg(NRF24L01P_EN_RXADDR) & ~BIT(pipe_num));
      nrf24l01p_write_reg(NRF24L01P_EN_AA, nrf24l01p_read_reg(NRF24L01P_EN_AA) & ~BIT(pipe_num));
      break;
    
    case NRF24L01P_ALL:
      nrf24l01p_write_reg(NRF24L01P_EN_RXADDR, 0);
      nrf24l01p_write_reg(NRF24L01P_EN_AA, 0);
      break;
      
    default:
      break;
  }
}

void nrf24l01p_set_address(nrf24l01p_address_t address, const uint8_t *addr)
{
  switch(address)
  {
    case NRF24L01P_TX:
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
      nrf24l01p_write_multibyte_reg((uint8_t) address, addr, 0);
      break;

    case NRF24L01P_PIPE2:
    case NRF24L01P_PIPE3:
    case NRF24L01P_PIPE4:
    case NRF24L01P_PIPE5:
      nrf24l01p_write_reg(NRF24L01P_RX_ADDR_P0 + (uint8_t)address, *addr);
      break;

    default:
      break;
  }
}

void nrf24l01p_set_auto_retr(uint8_t retr, uint16_t delay)
{
  nrf24l01p_write_reg(NRF24L01P_SETUP_RETR, (((delay/250)-1)<<4) | retr);
}

void nrf24l01p_set_address_width(nrf24l01p_address_width_t address_width)
{
  nrf24l01p_write_reg(NRF24L01P_SETUP_AW, (uint8_t)address_width - 2);
}

void nrf24l01p_set_rx_payload_width(uint8_t pipe_num, uint8_t payload_width)
{
  nrf24l01p_write_reg(NRF24L01P_RX_PW_P0 + pipe_num, payload_width);
}

uint8_t nrf24l01p_get_crc_mode(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_CONFIG) & (BIT(3)|BIT(2))) >> NRF24L01P_CONFIG_CRCO;
}

uint8_t nrf24l01p_get_pipe_status(uint8_t pipe_num)
{
  uint8_t en_rx, en_aa;

  en_rx = nrf24l01p_read_reg(NRF24L01P_EN_RXADDR) & (1<<pipe_num);
  en_aa = nrf24l01p_read_reg(NRF24L01P_EN_AA) & (1<<pipe_num);

  en_rx >>= pipe_num;
  en_aa >>= pipe_num;

  return (en_aa << 1) + en_rx;
}

uint8_t nrf24l01p_get_address(uint8_t address, uint8_t *addr)
{
  switch(address)
  {
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
    case NRF24L01P_TX:
      return nrf24l01p_read_multibyte_reg(address, addr);

    default:
      *addr = nrf24l01p_read_reg(NRF24L01P_RX_ADDR_P0 + address);
      return nrf24l01p_get_address_width();
  }
}

uint8_t nrf24l01p_get_auto_retr_status(void)
{
  return nrf24l01p_read_reg(NRF24L01P_OBSERVE_TX);
}

uint8_t nrf24l01p_get_packet_lost_ctr(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_OBSERVE_TX) & (BIT(7)|BIT(6)|BIT(5)|BIT(4))) >> 4;
}

uint8_t nrf24l01p_get_address_width(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_SETUP_AW) + 2);
}

uint8_t nrf24l01p_get_rx_payload_width(uint8_t pipe_num)
{
  return nrf24l01p_read_reg(NRF24L01P_RX_PW_P0 + pipe_num);
}

void nrf24l01p_set_operation_mode(nrf24l01p_operation_mode_t op_mode)
{
  nrf24l01p_write_reg(NRF24L01P_CONFIG, BIT_COND(nrf24l01p_read_reg(NRF24L01P_CONFIG), NRF24L01P_CONFIG_PRIM_RX, op_mode == NRF24L01P_PRX));
}

void nrf24l01p_set_power_mode(nrf24l01p_pwr_mode_t pwr_mode)
{
  nrf24l01p_write_reg(NRF24L01P_CONFIG, BIT_COND(nrf24l01p_read_reg(NRF24L01P_CONFIG), NRF24L01P_CONFIG_PWR_UP, pwr_mode == NRF24L01P_PWR_UP));
}

void nrf24l01p_set_rf_channel(uint8_t channel)
{
  nrf24l01p_write_reg(NRF24L01P_RF_CH, channel);
}

void nrf24l01p_set_output_power(nrf24l01p_output_power_t power)
{
  nrf24l01p_write_reg(NRF24L01P_RF_SETUP, (nrf24l01p_read_reg(NRF24L01P_RF_SETUP) & ~((1<<NRF24L01P_RF_SETUP_RF_PWR1)|(1<<NRF24L01P_RF_SETUP_RF_PWR0))) | ((uint8_t)power<<1));
}

void nrf24l01p_set_datarate(nrf24l01p_datarate_t datarate)
{
  nrf24l01p_write_reg(NRF24L01P_CONFIG, BIT_COND(nrf24l01p_read_reg(NRF24L01P_RF_SETUP), NRF24L01P_RF_SETUP_RF_DR, datarate != NRF24L01P_1MBPS));
}

uint8_t nrf24l01p_get_operation_mode(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_CONFIG) & (1<<NRF24L01P_CONFIG_PRIM_RX)) >> NRF24L01P_CONFIG_PRIM_RX;
}

uint8_t nrf24l01p_get_power_mode(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_CONFIG) & (1<<NRF24L01P_PWR_UP)) >> NRF24L01P_PWR_UP;
}

uint8_t nrf24l01p_get_rf_channel(void)
{
  return nrf24l01p_read_reg(NRF24L01P_RF_CH);
}

uint8_t nrf24l01p_get_output_power(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_RF_SETUP) & ((1<<NRF24L01P_RF_SETUP_RF_PWR1)|(1<<NRF24L01P_RF_SETUP_RF_PWR0))) >> NRF24L01P_RF_SETUP_RF_PWR0;
}

uint8_t nrf24l01p_get_datarate(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_RF_SETUP) & (1<<NRF24L01P_RF_SETUP_RF_DR)) >> NRF24L01P_RF_SETUP_RF_DR;
}

bool nrf24l01p_rx_fifo_empty(void)
{
  return nrf24l01p_get_rx_data_source() == 7;
}

bool nrf24l01p_rx_fifo_full(void)
{
  return (bool)((nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS) >> NRF24L01P_FIFO_STATUS_RX_EMPTY) & 1);
}

bool nrf24l01p_tx_fifo_empty(void)
{
  return (bool)((nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS) >> NRF24L01P_FIFO_STATUS_TX_EMPTY) & 1);
}

bool nrf24l01p_tx_fifo_full(void)
{
  return (bool)((nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS) >> NRF24L01P_FIFO_STATUS_TX_FIFO_FULL) & 1);
}

uint8_t nrf24l01p_get_tx_fifo_status(void)
{
  return ((nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS) & ((1<<NRF24L01P_FIFO_STATUS_TX_FIFO_FULL)|(1<<NRF24L01P_FIFO_STATUS_TX_EMPTY))) >> 4);
}

uint8_t nrf24l01p_get_rx_fifo_status(void)
{
  return (nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS) & ((1<<NRF24L01P_FIFO_STATUS_RX_FULL)|(1<<NRF24L01P_FIFO_STATUS_RX_EMPTY)));
}

uint8_t nrf24l01p_get_fifo_status(void)
{
  return nrf24l01p_read_reg(NRF24L01P_FIFO_STATUS);
}

uint8_t nrf24l01p_get_transmit_attempts(void)
{
  return nrf24l01p_read_reg(NRF24L01P_OBSERVE_TX) & (BIT(3)|BIT(2)|BIT(1)|BIT(0));
}

bool nrf24l01p_get_carrier_detect(void)
{
  return nrf24l01p_read_reg(NRF24L01P_CD) & 1;
}

void nrf24l01p_write_tx_payload(const uint8_t *tx_payload, uint8_t length)
{
  nrf24l01p_write_multibyte_reg(NRF24L01P_TX_PAYLOAD, tx_payload, length);
}

void nrf24l01p_setup_dyn_pl(uint8_t setup)
{
  nrf24l01p_write_reg(NRF24L01P_DYNPD, setup & ~0xC0);
}

void nrf24l01p_enable_dynamic_pl(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) | 0x04));
}

void nrf24l01p_disable_dynamic_pl(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) & ~0x04));
}

void nrf24l01p_enable_ack_pl(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) | 0x02));
}

void nrf24l01p_disable_ack_pl(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) & ~0x02));
}

void nrf24l01p_enable_dynamic_ack(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) | 0x01));
}

void nrf24l01p_disable_dynamic_ack(void)
{
  nrf24l01p_write_reg(NRF24L01P_FEATURE, (nrf24l01p_read_reg(NRF24L01P_FEATURE) & ~0x01));
}

void nrf24l01p_write_ack_payload(uint8_t pipe, const uint8_t *tx_payload, uint8_t length)
{
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);

  nrf24l01p_spi_rw(NRF24L01P_WR_ACK_PAYLOAD | pipe);
  while(length--)
    nrf24l01p_spi_rw(*tx_payload++);

  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);
}

uint8_t nrf24l01p_read_rx_fifo_payload_width()
{
  uint8_t temp;
  
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);

  nrf24l01p_spi_rw(NRF24L01P_RD_RX_PAYLOAD_WIDTH);
  temp = nrf24l01p_spi_rw(0);
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);

  return temp;
}

void nrf24l01p_lock_unlock()
{
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);

  nrf24l01p_spi_rw(NRF24L01P_LOCK_UNLOCK);
  nrf24l01p_spi_rw(0x73);

  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);
}

uint8_t nrf24l01p_get_rx_data_source(void)
{
  return ((nrf24l01p_nop() & (BIT(3)|BIT(2)|BIT(1))) >> 1);
}

// Fixed: returns length==0 and pipe==7 means FIFO empty

uint16_t nrf24l01p_read_rx_payload(uint8_t *rx_payload)
{
  return nrf24l01p_read_multibyte_reg(NRF24L01P_RX_PAYLOAD, rx_payload);
}

void nrf24l01p_reuse_tx(void)
{
  nrf24l01p_write_reg(NRF24L01P_REUSE_TX_PL, 0);
}

bool nrf24l01p_get_reuse_tx_status(void)
{
  return (bool)((nrf24l01p_get_fifo_status() & (1<<NRF24L01P_FIFO_STATUS_TX_REUSE)) >> NRF24L01P_FIFO_STATUS_TX_REUSE);
}

void nrf24l01p_flush_rx(void)
{
  nrf24l01p_write_reg(NRF24L01P_FLUSH_RX, 0);
}

void nrf24l01p_flush_tx(void)
{
  nrf24l01p_write_reg(NRF24L01P_FLUSH_TX, 0);
}

uint8_t nrf24l01p_nop(void)
{
  return nrf24l01p_write_reg(NRF24L01P_NOP,0);
}

void nrf24l01p_set_pll_mode(nrf24l01p_pll_mode_t pll_mode)
{
  nrf24l01p_write_reg(NRF24L01P_RF_SETUP, BIT_COND(nrf24l01p_read_reg(NRF24L01P_RF_SETUP), NRF24L01P_PLL_LOCK, pll_mode == NRF24L01P_PLL_LOCK));
}

nrf24l01p_pll_mode_t nrf24l01p_get_pll_mode(void)
{
  return (nrf24l01p_pll_mode_t)((nrf24l01p_read_reg(NRF24L01P_RF_SETUP) & (1<<NRF24L01P_PLL_LOCK)) >> NRF24L01P_PLL_LOCK);
}

void nrf24l01p_set_lna_gain(nrf24l01p_lna_mode_t lna_gain)
{
  nrf24l01p_write_reg(NRF24L01P_RF_SETUP, BIT_COND(nrf24l01p_read_reg(NRF24L01P_RF_SETUP), NRF24L01P_LNA_HCURR, lna_gain == NRF24L01P_LNA_HCURR));
}

nrf24l01p_lna_mode_t nrf24l01p_get_lna_gain(void)
{
  return (nrf24l01p_lna_mode_t) ( (nrf24l01p_read_reg(NRF24L01P_RF_SETUP) & (1<<NRF24L01P_LNA_HCURR)) >> NRF24L01P_LNA_HCURR );
}

uint8_t nrf24l01p_read_reg(uint8_t reg)
{
uint8_t temp;
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
  nrf24l01p_spi_rw(reg);
  temp = nrf24l01p_spi_rw(0);
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);

  return temp;
}

uint8_t nrf24l01p_write_reg(uint8_t reg, uint8_t value)
{
  uint8_t retval;
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
  if(reg < NRF24L01P_NRF_WRITE_REG)   // i.e. this is a register access
  {
    retval = nrf24l01p_spi_rw(NRF24L01P_NRF_WRITE_REG + reg);
    nrf24l01p_spi_rw(value);
  }
  else            // single byte cmd OR future command/register access
  {
    if(!(reg == NRF24L01P_FLUSH_TX) && !(reg == NRF24L01P_FLUSH_RX) && !(reg == NRF24L01P_REUSE_TX_PL) && !(reg == NRF24L01P_NOP))
    {
      retval = nrf24l01p_spi_rw(reg);
      nrf24l01p_spi_rw(value);
    }
    else          // single byte L01 command
    {
      retval = nrf24l01p_spi_rw(reg);
    }
  }
  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);

  return retval;
}

uint16_t nrf24l01p_read_multibyte_reg(uint8_t reg, uint8_t *pbuf)
{
uint8_t ctr, length;
  switch(reg)
  {
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
    case NRF24L01P_TX:
      length = ctr = nrf24l01p_get_address_width();
      nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
      nrf24l01p_spi_rw(NRF24L01P_RX_ADDR_P0 + reg);
      break;
      
    case NRF24L01P_RX_PAYLOAD:
      if( (reg = nrf24l01p_get_rx_data_source()) < 7)
      {
        length = ctr = nrf24l01p_read_rx_fifo_payload_width();

        nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
        nrf24l01p_spi_rw(NRF24L01P_RD_RX_PAYLOAD);
      }
      else
      {
       ctr = length = 0;
      }
      break;

    default:
      ctr = length = 0;
      break;
  }

  while(ctr--)
  {
    *pbuf++ = nrf24l01p_spi_rw(0);
  }

  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);

  return (((uint16_t) reg << 8) | length);
}

void nrf24l01p_write_multibyte_reg(uint8_t reg, const uint8_t *pbuf, uint8_t length)
{
  switch(reg)
  {
    case NRF24L01P_PIPE0:
    case NRF24L01P_PIPE1:
    case NRF24L01P_TX:
      length = nrf24l01p_get_address_width();
      nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
      nrf24l01p_spi_rw(NRF24L01P_NRF_WRITE_REG + NRF24L01P_RX_ADDR_P0 + reg);
      break;
      
    case NRF24L01P_TX_PAYLOAD:
      nrf24l01p_spi_ss(NRF24L01P_SPI_SS_LOW);
      nrf24l01p_spi_rw(NRF24L01P_WR_TX_PAYLOAD);
      break;      
    default:
      break;
  }

  while(length--)
    nrf24l01p_spi_rw(*pbuf++);

  nrf24l01p_spi_ss(NRF24L01P_SPI_SS_HIGH);
}

#ifdef __cplusplus
} // extern "C"
#endif
