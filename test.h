#ifndef __TEST_H__
#define __TEST_H__

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"


#define COMMAND_LENGTH 48
//#define START_BIT 0
//#define TRANMISSION_BIT 1
//#define END_BIT 1

#define Set_Pin(GPIO, Pin)    GPIO_SetBits(GPIO, Pin)
#define Reset_Pin(GPIO, Pin)  GPIO_ResetBits(GPIO, Pin)

#define SD_CS         GPIO_Pin_12
#define SD_SCK        GPIO_Pin_13
#define SD_MISO       GPIO_Pin_14
#define SD_MOSI       GPIO_Pin_15
#define LED_YELLOW    GPIO_Pin_12

#define SD_AF_SCK     GPIO_PinSource13
#define SD_AF_MISO    GPIO_PinSource14
#define SD_AF_MOSI    GPIO_PinSource15

#define HIGH 1
#define LOW  0

#define GPIO_SPI          GPIOB
#define SPI_SDCARD        SPI2
#define GPIO_AF_SDCARD    GPIO_AF_SPI2
#define TIM_SDCARD        TIM2
#define NCR_TIME          1000
#define MAX_TRY           100
#define POWER_UP_TIME     2000



typedef enum SD_command {
    RESET_IDLE = 0,
    SEND_IF_COND = 0x8,
    SD_SEND_OP_COND = 41,
    APP_CMD = 55,
    READ_OCR = 58
} SD_command_t;

typedef enum ERR_SD_Init{
    ERR_OK = 0,
    ERR_CMD_TIMEOUT = -1, //Timeout response command
    ERR_CARD_INVALID = -2, //Unknown Card
    ERR_PATTERN_NOT_MATCH = -3, //Pattern not match
    TIMEOUT_INITIALIZE = -4 //Timeout initialization procedure
} ERR_SD_Init_t;

typedef enum Type_Capacity_Card {
    UNKNOWN_CARD = -1,
    STANDARD_CAPACITY = 0,
    HIGH_CAPACITY = 1
} Type_Capacity_Card_t;

typedef struct SD_Card {
    ERR_SD_Init_t error;
    Type_Capacity_Card_t sd_type;       
} SD_Card_t;

void Init_SPI_GPIO_Mode(void);
void Initialize_Pin_MOSI(void);
void Init_SPI_Register(void);
void Delay_us(TIM_TypeDef *TIMx, uint32_t micro);
void Power_Up_Sequence(void);
void DeSelect_Card(void);
void Select_Card(void);
void Prepare_Host_Command(uint8_t command, uint32_t argument, uint8_t crc);
void Send_Host_Command(uint8_t dat);
void Send_ACMD_Command(uint8_t command, uint32_t argument);
void Set_Pin_CS(uint8_t cs_pin);
bool Wait_TimeOut_CMD0(void);
bool Wait_Response_R1(uint8_t command, uint32_t arg, uint32_t expected_response);
bool Parse_OCR_Response(uint32_t response);
ERR_SD_Init_t Init_SD_Card(void);
uint16_t Receive_Response(void);
//uint16_t Wait_One_Response(uint32_t expected_response);
bool Wait_One_Response(uint32_t expected_response);
uint32_t Get_Extended_Response(uint8_t byte);

#endif
