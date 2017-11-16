/* Copyright (c) 2006 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 * $Rev: 1731 $
 *
 */

/** @file
 * Register definitions for the nRF HAL module
 * @defgroup nordic_nrf24l01p_reg nRF24L01 Register definitions
 * @{
 * @ingroup nordic_hal_nrf
 * Header file defining register mapping with bit definitions.\ This file is radio-chip dependent, and are included with the hal_nrf.h
 */

#ifndef NRF24L01P_REG_H__
#define NRF24L01P_REG_H__

typedef enum
{
/** @name - Instruction Set - */
//@{
/* nRF24L01 Instruction Definitions */

    NRF24L01P_NRF_WRITE_REG       = 0x20,  /**< Register write command */
    NRF24L01P_RD_RX_PAYLOAD_WIDTH = 0x60,  /**< Read RX payload command */
    NRF24L01P_RD_RX_PAYLOAD       = 0x61,  /**< Read RX payload command */
    NRF24L01P_WR_TX_PAYLOAD       = 0xA0,  /**< Write TX payload command */
    NRF24L01P_WR_ACK_PAYLOAD      = 0xA8,  /**< Write ACK payload command */
    NRF24L01P_WR_NAC_TX_PAYLOAD   = 0xB0,  /**< Write ACK payload command */
    NRF24L01P_FLUSH_TX            = 0xE1,  /**< Flush TX register command */
    NRF24L01P_FLUSH_RX            = 0xE2,  /**< Flush RX register command */
    NRF24L01P_REUSE_TX_PL         = 0xE3,  /**< Reuse TX payload command */
    NRF24L01P_LOCK_UNLOCK         = 0x50,  /**< Lock/unlcok exclusive features */
    NRF24L01P_NOP                 = 0xFF,  /**< No Operation command, used for reading status register */
//@}
} nrf24l01p_command_t;

enum
{
/** @name  - Register Memory Map - */
//@{
/* nRF24L01 * Register Definitions * */
    NRF24L01P_CONFIG      = 0x00,  /**< nRF24L01 config register */
    NRF24L01P_EN_AA       = 0x01,  /**< nRF24L01 enable Auto-Acknowledge register */
    NRF24L01P_EN_RXADDR   = 0x02,  /**< nRF24L01 enable RX addresses register */
    NRF24L01P_SETUP_AW    = 0x03,  /**< nRF24L01 setup of address width register */
    NRF24L01P_SETUP_RETR  = 0x04,  /**< nRF24L01 setup of automatic retransmission register */
    NRF24L01P_RF_CH       = 0x05,  /**< nRF24L01 RF channel register */
    NRF24L01P_RF_SETUP    = 0x06,  /**< nRF24L01 RF setup register */
    NRF24L01P_STATUS      = 0x07,  /**< nRF24L01 status register */
    NRF24L01P_OBSERVE_TX  = 0x08,  /**< nRF24L01 transmit observe register */
    NRF24L01P_CD          = 0x09,  /**< nRF24L01 carrier detect register */
    NRF24L01P_RX_ADDR_P0  = 0x0A,  /**< nRF24L01 receive address data pipe0 */
    NRF24L01P_RX_ADDR_P1  = 0x0B,  /**< nRF24L01 receive address data pipe1 */
    NRF24L01P_RX_ADDR_P2  = 0x0C,  /**< nRF24L01 receive address data pipe2 */
    NRF24L01P_RX_ADDR_P3  = 0x0D,  /**< nRF24L01 receive address data pipe3 */
    NRF24L01P_RX_ADDR_P4  = 0x0E,  /**< nRF24L01 receive address data pipe4 */
    NRF24L01P_RX_ADDR_P5  = 0x0F,  /**< nRF24L01 receive address data pipe5 */
    NRF24L01P_TX_ADDR     = 0x10,  /**< nRF24L01 transmit address */
    NRF24L01P_RX_PW_P0    = 0x11,  /**< nRF24L01 \# of bytes in rx payload for pipe0 */
    NRF24L01P_RX_PW_P1    = 0x12,  /**< nRF24L01 \# of bytes in rx payload for pipe1 */
    NRF24L01P_RX_PW_P2    = 0x13,  /**< nRF24L01 \# of bytes in rx payload for pipe2 */
    NRF24L01P_RX_PW_P3    = 0x14,  /**< nRF24L01 \# of bytes in rx payload for pipe3 */
    NRF24L01P_RX_PW_P4    = 0x15,  /**< nRF24L01 \# of bytes in rx payload for pipe4 */
    NRF24L01P_RX_PW_P5    = 0x16,  /**< nRF24L01 \# of bytes in rx payload for pipe5 */
    NRF24L01P_FIFO_STATUS = 0x17,  /**< nRF24L01 FIFO status register */
    NRF24L01P_DYNPD       = 0x1C,  /**< nRF24L01 Dynamic payload setup */
    NRF24L01P_FEATURE     = 0x1D   /**< nRF24L01 Exclusive feature setup */
};
//@}

/* nRF24L01 related definitions */
/* Interrupt definitions */
/* Operation mode definitions */

/** An enum describing the radio's irq sources.
 *
 */
typedef enum {
    NRF24L01P_IRQ_MAX_RT = 4,     /**< Max retries interrupt */
    NRF24L01P_IRQ_TX_DS,          /**< TX data sent interrupt */
    NRF24L01P_IRQ_RX_DR           /**< RX data received interrupt */
} nrf24l01p_irq_source_t;

/* Operation mode definitions */
/** An enum describing the radio's power mode.
 *
 */
typedef enum {
    NRF24L01P_PTX,            /**< Primary TX operation */
    NRF24L01P_PRX             /**< Primary RX operation */
} nrf24l01p_operation_mode_t;

/** An enum describing the radio's power mode.
 *
 */
typedef enum {
    NRF24L01P_PWR_DOWN,       /**< Device power-down */
    NRF24L01P_PWR_UP          /**< Device power-up */
} nrf24l01p_pwr_mode_t;

/** An enum describing the radio's output power mode's.
 *
 */
typedef enum {
    NRF24L01P_18DBM,          /**< Output power set to -18dBm */
    NRF24L01P_12DBM,          /**< Output power set to -12dBm */
    NRF24L01P_6DBM,           /**< Output power set to -6dBm  */
    NRF24L01P_0DBM            /**< Output power set to 0dBm   */
} nrf24l01p_output_power_t;

/** An enum describing the radio's on-air datarate.
 *
 */
typedef enum {
    NRF24L01P_1MBPS,          /**< Datarate set to 1 Mbps  */
    NRF24L01P_2MBPS           /**< Datarate set to 2 Mbps  */
} nrf24l01p_datarate_t;

/** An enum describing the radio's PLL mode.
 *
 */
typedef enum {
    NRF24L01P_PLL_UNLOCK,     /**< PLL unlocked, normal operation  */
    NRF24L01P_PLL_LOCK        /**< PLL locked, test mode  */
} nrf24l01p_pll_mode_t;

/** An enum describing the radio's LNA mode.
 *
 */
typedef enum {
    NRF24L01P_LNA_LCURR,      /**< LNA set to low current mode */
    NRF24L01P_LNA_HCURR       /**< LNA set to high current mode */
} nrf24l01p_lna_mode_t;

/** An enum describing the radio's CRC mode.
 *
 */
typedef enum {
    NRF24L01P_CRC_OFF,        /**< CRC check disabled */
    NRF24L01P_CRC_8BIT = 2,   /**< CRC check set to 8-bit */
    NRF24L01P_CRC_16BIT       /**< CRC check set to 16-bit */
} nrf24l01p_crc_mode_t;

/** An enum describing the read/write payload command.
 *
 */
typedef enum {
    NRF24L01P_TX_PAYLOAD = 7,   /**< TX payload definition */
    NRF24L01P_RX_PAYLOAD,        /**< RX payload definition */
    NRF24L01P_ACK_PAYLOAD
} nrf24l01p_payload_command_t;

/** Structure containing the radio's address map.
 * Pipe0 contains 5 unique address bytes,
 * while pipe[1..5] share the 4 MSB bytes, set in pipe1.
 * <p><b> - Remember that the LSB byte for all pipes have to be unique! -</b>
 */
// nRF24L01 Address struct

/*
//typedef struct {
//    uint8_t p0[5];            ///< Pipe0 address, 5 bytes
//    uint8_t p1[5];            ///< Pipe1 address, 5 bytes, 4 MSB bytes shared for pipe1 to pipe5 */
//    uint8_t p2[1];            ///< Pipe2 address, 1 byte
//    uint8_t p3[1];            ///< Pipe3 address, 1 byte
//    uint8_t p4[1];            ///< Pipe3 address, 1 byte
//    uint8_t p5[1];            ///< Pipe3 address, 1 byte
//    uint8_t tx[5];            ///< TX address, 5 byte */
//} nrf24l01p_l01_addr_map;


/** An enum describing the nRF24L01 pipe addresses and TX address.
 *
 */
typedef enum {
    NRF24L01P_PIPE0,              /**< Select pipe0 */
    NRF24L01P_PIPE1,              /**< Select pipe1 */
    NRF24L01P_PIPE2,              /**< Select pipe2 */
    NRF24L01P_PIPE3,              /**< Select pipe3 */
    NRF24L01P_PIPE4,              /**< Select pipe4 */
    NRF24L01P_PIPE5,              /**< Select pipe5 */
    NRF24L01P_TX,                 /**< Refer to TX address*/
    NRF24L01P_ALL = 0XFF          /**< Close or open all pipes*/
                                /**< @see nrf24l01p_set_address @see nrf24l01p_get_address
                                 @see nrf24l01p_open_pipe  @see nrf24l01p_close_pipe */
} nrf24l01p_address_t;

/** An enum describing the radio's address width.
 *
 */
typedef enum {
    NRF24L01P_AW_3BYTES = 3,      /**< Set address width to 3 bytes */
    NRF24L01P_AW_4BYTES,          /**< Set address width to 4 bytes */
    NRF24L01P_AW_5BYTES           /**< Set address width to 5 bytes */
} nrf24l01p_address_width_t;

enum
{
/** @name CONFIG register bit definitions */
//@{

    NRF24L01P_CONFIG_MASK_RX_DR  = 6,     /**< CONFIG register bit 6 */
    NRF24L01P_CONFIG_MASK_TX_DS  = 5,     /**< CONFIG register bit 5 */
    NRF24L01P_CONFIG_MASK_MAX_RT = 4,     /**< CONFIG register bit 4 */
    NRF24L01P_CONFIG_EN_CRC      = 3,     /**< CONFIG register bit 3 */
    NRF24L01P_CONFIG_CRCO        = 2,     /**< CONFIG register bit 2 */
    NRF24L01P_CONFIG_PWR_UP      = 1,     /**< CONFIG register bit 1 */
    NRF24L01P_CONFIG_PRIM_RX     = 0,     /**< CONFIG register bit 0 */
//@}

/** @name RF_SETUP register bit definitions */
//@{
    NRF24L01P_RF_SETUP_PLL_LOCK  = 4,     /**< RF_SETUP register bit 4 */
    NRF24L01P_RF_SETUP_RF_DR     = 3,     /**< RF_SETUP register bit 3 */
    NRF24L01P_RF_SETUP_RF_PWR1   = 2,     /**< RF_SETUP register bit 2 */
    NRF24L01P_RF_SETUP_RF_PWR0   = 1,     /**< RF_SETUP register bit 1 */
    NRF24L01P_RF_SETUP_LNA_HCURR = 0,     /**< RF_SETUP register bit 0 */
//@}

/* STATUS 0x07 */
/** @name STATUS register bit definitions */
//@{
    NRF24L01P_STATUS_RX_DR   = 6,     /**< STATUS register bit 6 */
    NRF24L01P_STATUS_TX_DS   = 5,     /**< STATUS register bit 5 */
    NRF24L01P_STATUS_MAX_RT  = 4,     /**< STATUS register bit 4 */
    NRF24L01P_STATUS_TX_FULL = 0,     /**< STATUS register bit 0 */
//@}

/* FIFO_STATUS 0x17 */
/** @name FIFO_STATUS register bit definitions */
//@{
    NRF24L01P_FIFO_STATUS_TX_REUSE     = 6,     /**< FIFO_STATUS register bit 6 */
    NRF24L01P_FIFO_STATUS_TX_FIFO_FULL = 5,     /**< FIFO_STATUS register bit 5 */
    NRF24L01P_FIFO_STATUS_TX_EMPTY     = 4,     /**< FIFO_STATUS register bit 4 */
    NRF24L01P_FIFO_STATUS_RX_FULL      = 1,     /**< FIFO_STATUS register bit 1 */
    NRF24L01P_FIFO_STATUS_RX_EMPTY     = 0      /**< FIFO_STATUS register bit 0 */
//@}
};

#endif // NRF24L01P_REG_H__
/** @} */
