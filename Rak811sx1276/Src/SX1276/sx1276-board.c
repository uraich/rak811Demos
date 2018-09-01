/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: SX1276 driver specific target board functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
//#include "board.h"
#include "radio.h"
#include "sx1276.h"
#include "sx1276-board.h"
#include "stm32l1xx_hal.h"

/*!
 * Flag used to set the RF switch control pins in low power mode when the radio is not active.
 */
static bool RadioIsActive = false;

/*!
 * Radio driver structure initialization
 */
#ifdef READY
const struct Radio_s Radio =
{
    SX1276Init,
    SX1276GetStatus,
    SX1276SetModem,
    SX1276SetChannel,
    SX1276IsChannelFree,
    SX1276Random,
    SX1276SetRxConfig,
    SX1276SetTxConfig,
    SX1276CheckRfFrequency,
    SX1276GetTimeOnAir,
    SX1276Send,
    SX1276SetSleep,
    SX1276SetStby,
    SX1276SetRx,
    SX1276StartCad,
    SX1276SetTxContinuousWave,
    SX1276ReadRssi,
    SX1276Write,
    SX1276Read,
    SX1276WriteBuffer,
    SX1276ReadBuffer,
    SX1276SetMaxPayloadLength,
    SX1276SetPublicNetwork
};

/*!
 * Antenna switch GPIO pins objects
 */
Gpio_t AntCtxPa;
Gpio_t AntCbtHf;
Gpio_t AntCrxRx;

void SX1276IoInit( void )
{
    GpioInit( &SX1276.Spi.Nss, RADIO_NSS, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 1 );

    GpioInit( &SX1276.DIO0, RADIO_DIO_0, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &SX1276.DIO1, RADIO_DIO_1, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &SX1276.DIO2, RADIO_DIO_2, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &SX1276.DIO3, RADIO_DIO_3, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &SX1276.DIO4, RADIO_DIO_4, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
}

void SX1276IoIrqInit( DioIrqHandler **irqHandlers )
{
    GpioSetInterrupt( &SX1276.DIO0, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[0] );
    GpioSetInterrupt( &SX1276.DIO1, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[1] );
    GpioSetInterrupt( &SX1276.DIO2, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[2] );
    GpioSetInterrupt( &SX1276.DIO3, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[3] );
    GpioSetInterrupt( &SX1276.DIO4, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[4] );
    GpioSetInterrupt( &SX1276.DIO5, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[5] );
}

void SX1276IoDeInit( void )
{
    GpioInit( &SX1276.Spi.Nss, RADIO_NSS, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1 );

    GpioInit( &SX1276.DIO0, RADIO_DIO_0, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO1, RADIO_DIO_1, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO2, RADIO_DIO_2, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO3, RADIO_DIO_3, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO4, RADIO_DIO_4, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
}

void SX1276SetRfTxPower( int8_t power )
{
    uint8_t paConfig = 0;
    uint8_t paDac = 0;

    paConfig = SX1276Read( REG_PACONFIG );
    paDac = SX1276Read( REG_PADAC );

    paConfig = ( paConfig & RF_PACONFIG_PASELECT_MASK ) | SX1276GetPaSelect( SX1276.Settings.Channel );
    paConfig = ( paConfig & RF_PACONFIG_MAX_POWER_MASK ) | 0x70;

    if( ( paConfig & RF_PACONFIG_PASELECT_PABOOST ) == RF_PACONFIG_PASELECT_PABOOST )
    {
        if( power > 17 )
        {
            paDac = ( paDac & RF_PADAC_20DBM_MASK ) | RF_PADAC_20DBM_ON;
        }
        else
        {
            paDac = ( paDac & RF_PADAC_20DBM_MASK ) | RF_PADAC_20DBM_OFF;
        }
        if( ( paDac & RF_PADAC_20DBM_ON ) == RF_PADAC_20DBM_ON )
        {
            if( power < 5 )
            {
                power = 5;
            }
            if( power > 20 )
            {
                power = 20;
            }
            paConfig = ( paConfig & RF_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power - 5 ) & 0x0F );
        }
        else
        {
            if( power < 2 )
            {
                power = 2;
            }
            if( power > 17 )
            {
                power = 17;
            }
            paConfig = ( paConfig & RF_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power - 2 ) & 0x0F );
        }
    }
    else
    {
        if( power < -1 )
        {
            power = -1;
        }
        if( power > 14 )
        {
            power = 14;
        }
        paConfig = ( paConfig & RF_PACONFIG_OUTPUTPOWER_MASK ) | ( uint8_t )( ( uint16_t )( power + 1 ) & 0x0F );
    }
    SX1276Write( REG_PACONFIG, paConfig );
    SX1276Write( REG_PADAC, paDac );
}

uint8_t SX1276GetPaSelect( uint32_t channel )
{
//    if( channel < RF_MID_BAND_THRESH )
//    {
//        return RF_PACONFIG_PASELECT_PABOOST;
//    }
//    else
//    {
//        return RF_PACONFIG_PASELECT_RFO;
//    }
	
  	return RF_PACONFIG_PASELECT_PABOOST;
}
#endif
void SX1276SetAntSwLowPower( bool status )
{
    if( RadioIsActive != status )
    {
        RadioIsActive = status;

        if( status == false )
        {
            SX1276AntSwInit( );
        }
        else
        {
            SX1276AntSwDeInit( );
        }
    }
}

void SX1276AntSwInit( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pin : RADIO_RF_CTX_PA_Pin */
	GPIO_InitStruct.Pin = RADIO_RF_CTX_PA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(RADIO_RF_CTX_PA_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RADIO_RF_CRX_RX_Pin RADIO_RF_CBT_HF_Pin */
	GPIO_InitStruct.Pin = RADIO_RF_CRX_RX_Pin|RADIO_RF_CBT_HF_Pin;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
/*
    GpioInit( &AntCtxPa, RADIO_RF_CTX_PA, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &AntCbtHf, RADIO_RF_CBT_HF, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioInit( &AntCrxRx, RADIO_RF_CRX_RX, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
*/
}

void SX1276AntSwDeInit( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pin : RADIO_RF_CTX_PA_Pin */
	GPIO_InitStruct.Pin = RADIO_RF_CTX_PA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RADIO_RF_CTX_PA_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RADIO_RF_CRX_RX_Pin RADIO_RF_CBT_HF_Pin */
	GPIO_InitStruct.Pin = RADIO_RF_CRX_RX_Pin|RADIO_RF_CBT_HF_Pin;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/*
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GpioInit( &AntCtxPa, RADIO_RF_CTX_PA, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0 );
    GpioInit( &AntCbtHf, RADIO_RF_CBT_HF, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0 );
    GpioInit( &AntCrxRx, RADIO_RF_CRX_RX, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0 );
*/
}

void SX1276SetAntSw( uint8_t opMode )
{
    switch( opMode )
    {
    case RFLR_OPMODE_TRANSMITTER:
    	HAL_GPIO_WritePin(RADIO_RF_CTX_PA_GPIO_Port, RADIO_RF_CTX_PA_Pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(RADIO_RF_CRX_RX_GPIO_Port, RADIO_RF_CRX_RX_Pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(RADIO_RF_CBT_HF_GPIO_Port, RADIO_RF_CBT_HF_Pin, GPIO_PIN_RESET);
/*
        GpioWrite( &AntCtxPa, 1 ); 
        GpioWrite( &AntCbtHf, 0 ); 
        GpioWrite( &AntCrxRx, 0 );
*/
        printf("-Tx-\r\n");
        break;
    case RFLR_OPMODE_RECEIVER:
    case RFLR_OPMODE_RECEIVER_SINGLE:
    case RFLR_OPMODE_CAD:
    default:
    	HAL_GPIO_WritePin(RADIO_RF_CTX_PA_GPIO_Port, RADIO_RF_CTX_PA_Pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(RADIO_RF_CRX_RX_GPIO_Port, RADIO_RF_CRX_RX_Pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(RADIO_RF_CBT_HF_GPIO_Port, RADIO_RF_CBT_HF_Pin, GPIO_PIN_SET);

/*
        GpioWrite( &AntCtxPa, 0 );
        GpioWrite( &AntCbtHf, 0 );
        GpioWrite( &AntCrxRx, 1 );
*/
        printf("-Rx-\r\n");
        break;
    }
}

bool SX1276CheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}
