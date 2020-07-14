#include "test.h"
SD_Card_t sd_info;

//==============================================================//
//================ Initialize GPIO SPI Mode ====================//
//==============================================================//
void Init_SPI_GPIO_Mode(void) {
		GPIO_InitTypeDef Init_SPI;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); 
		if (GPIO_SPI == GPIOA) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		}
		else if (GPIO_SPI == GPIOB) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		}
		else if (GPIO_SPI == GPIOC) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		}

    //Config pin MISO, MOSI, SCK
		GPIO_PinAFConfig(GPIO_SPI, SD_AF_SCK, GPIO_AF_SDCARD);
		GPIO_PinAFConfig(GPIO_SPI, SD_AF_MISO, GPIO_AF_SDCARD);
		GPIO_PinAFConfig(GPIO_SPI, SD_AF_MOSI, GPIO_AF_SDCARD);

		Init_SPI.GPIO_Pin = SD_SCK | SD_MISO | SD_MOSI;
		Init_SPI.GPIO_Speed = GPIO_Speed_50MHz;
    Init_SPI.GPIO_OType = GPIO_OType_PP;
    Init_SPI.GPIO_PuPd = GPIO_PuPd_NOPULL;
		Init_SPI.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIO_SPI, &Init_SPI);

    //Config pin CS 
    Init_SPI.GPIO_Pin = SD_CS;
    Init_SPI.GPIO_Speed = GPIO_Speed_50MHz;   
    Init_SPI.GPIO_OType = GPIO_OType_PP;
    Init_SPI.GPIO_PuPd = GPIO_PuPd_NOPULL;
		Init_SPI.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIO_SPI, &Init_SPI);

}

void Initialize_Pin_MOSI(void) {
		GPIO_InitTypeDef Init_SPI_SD_MOSI;

		Init_SPI_SD_MOSI.GPIO_Pin = SD_MOSI;
		Init_SPI_SD_MOSI.GPIO_Speed = GPIO_Speed_50MHz;
    Init_SPI_SD_MOSI.GPIO_OType = GPIO_OType_PP;
    Init_SPI_SD_MOSI.GPIO_PuPd = GPIO_PuPd_DOWN;
		Init_SPI_SD_MOSI.GPIO_Mode = GPIO_Mode_AF;

		GPIO_Init(GPIO_SPI, &Init_SPI_SD_MOSI);

    //Config pin MOSI
		GPIO_PinAFConfig(GPIO_SPI, GPIO_PinSource15, GPIO_AF_SPI2);
}

void Init_SPI_Register(void) {
		SPI_InitTypeDef SPI_Str_Init;

    SPI_Str_Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
		SPI_Str_Init.SPI_CPHA = SPI_CPHA_1Edge;
		SPI_Str_Init.SPI_CPOL = SPI_CPOL_Low;
    SPI_Str_Init.SPI_DataSize = SPI_DataSize_8b;
		SPI_Str_Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_Str_Init.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_Str_Init.SPI_Mode = SPI_Mode_Master;
		SPI_Str_Init.SPI_NSS = SPI_NSS_Soft;

		SPI_Init(SPI_SDCARD, &SPI_Str_Init);
    SPI_Cmd(SPI_SDCARD, ENABLE);

		//SPI_SSOutputCmd(SPI_SDCARD, ENABLE);
}

void Init_Counter_SDCard(TIM_TypeDef *TIMx) {
    uint32_t multipler, TIM_SDCard_Frequency, TIM_Counter_Frequency, APB_Peripheral;
		TIM_TimeBaseInitTypeDef TIM_Base_Init_SDCard;

    if (TIMx == TIM2) {
        APB_Peripheral = RCC_APB1Periph_TIM2;    
    }
    else if (TIMx == TIM3) {
        APB_Peripheral = RCC_APB1Periph_TIM3;
    }
    else if (TIMx == TIM4) {
        APB_Peripheral = RCC_APB1Periph_TIM4;
    }
    else if (TIMx == TIM5) {
        APB_Peripheral = RCC_APB1Periph_TIM5;
    }

    RCC_APB1PeriphClockCmd(APB_Peripheral, ENABLE);
    TIM_InternalClockConfig(TIMx);
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    if (RCC_Clocks.PCLK1_Frequency == RCC_Clocks.SYSCLK_Frequency) {
        multipler = 1;
    }
    else {
        multipler = 2;
    }
    TIM_Counter_Frequency = multipler * RCC_Clocks.PCLK1_Frequency;
    TIM_SDCard_Frequency = 1000000;//1MHz = 1us

    TIM_Base_Init_SDCard.TIM_Period = 999;
    TIM_Base_Init_SDCard.TIM_Prescaler = TIM_Counter_Frequency/TIM_SDCard_Frequency - 1;
    TIM_Base_Init_SDCard.TIM_ClockDivision = 0;
    TIM_Base_Init_SDCard.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIMx, &TIM_Base_Init_SDCard);

}

void Delay_us(TIM_TypeDef *TIMx, uint32_t micro) {
    volatile uint32_t count_first = TIMx->CNT;
    while (micro--) {
        while (TIMx->CNT - count_first) {
        } 
        count_first = TIMx->CNT;
    }
}

void Set_Pin_CS(uint8_t cs_pin) {
    assert_param((cs_pin == HIGH) || (cs_pin == LOW));
    if (cs_pin == HIGH) {
        GPIO_SetBits(GPIO_SPI, SD_CS);
    }
    else {
        GPIO_ResetBits(GPIO_SPI, SD_CS);
    }
}

void DeSelect_Card(void) {
    Set_Pin_CS(HIGH);
    Send_Host_Command(0xFF);
}

void Select_Card(void) {
    Set_Pin_CS(LOW);
}

void Prepare_Host_Command(uint8_t command, uint32_t argument, uint8_t crc) {
    uint8_t dat, count_arg;
    uint32_t mask; 
    char str[10];
 
    mask = 0xFF000000;
    count_arg = 3;

    while (SPI_I2S_GetFlagStatus (SPI_SDCARD, SPI_I2S_FLAG_BSY) != RESET) {
    }
    Select_Card();
    for (int i = 0; i < COMMAND_LENGTH/8; i++) {
        dat = 0x0;
        if (i == 0) {
           dat = 0x40 | command; 
        }
        else if (i == COMMAND_LENGTH/8 -1) {
           dat = crc | 0x1; 
        }
        else {
           dat = (argument & mask) >> (count_arg * 8);
           mask >>= 8;
           count_arg--;
        } 
        //sprintf(str, "%#X\r\n", dat);
        //Transmit_string_UART(USART6, str);
        Send_Host_Command(dat);
    }
    //Send_Host_Command(0xFF);
    //Select_Card();
}

void Send_Host_Command(uint8_t dat) {
    while (SPI_I2S_GetFlagStatus (SPI_SDCARD, SPI_I2S_FLAG_TXE) != SET) {
    }
    SPI_I2S_SendData(SPI_SDCARD, (uint16_t)dat);
}

uint16_t Receive_Response(void) {
    while (SPI_I2S_GetFlagStatus (SPI_SDCARD, SPI_I2S_FLAG_RXNE) != SET) {
    }
    return SPI_I2S_ReceiveData(SPI_SDCARD);  
}

bool Wait_One_Response(uint32_t expected_response) {
    uint32_t tmout_res = 0, actual;
    bool ret = false;
    do {
        actual = Receive_Response();
        if (actual == expected_response) {
            return true;
        }
        //char str[10];
        //sprintf(str, "%#X\r\n", actual);
        //Transmit_string_UART(USART6, str);
        Send_Host_Command(0xFF);
        Delay_us(TIM_SDCARD, 0x1);

        tmout_res++;
    } while (tmout_res < NCR_TIME);
    return false;
}
bool Wait_Response_R1(uint8_t command, uint32_t arg, uint32_t expected_response) {
    uint32_t tmout_cmd;
    uint16_t response;

    tmout_cmd = response = 0;
    do {
        Prepare_Host_Command(command, arg);    
        if (Wait_One_Response(expected_response)) {
            return true;
        }
        tmout_cmd++;
    } while (tmout_cmd < MAX_TRY);
    return false;
}

bool Proceed_CMD8(uint16_t pattern) {
    uint32_t response = 0; 
    bool ret = true;

    //do {
        Prepare_Host_Command(SEND_IF_COND, pattern);
        
        if (!Wait_One_Response(0x1)) {//Wait for valid response
           Transmit_string_UART(USART6, "Wrong response CMD8\r\n");
           return false;
            //continue;
        }
    //} while (true);
  Transmit_string_UART(USART6, "Correct response CMD8\r\n");
    for (int i = 0; i < 2; i++) {
        Receive_Response();//ignore info byte
    }
    
    for (int i = 0; i < 2; i++) {
        response = response | Receive_Response();
    }
    //Receive_Response();//ignore CRC byte
    //Check pattern 
    if ((response & 0x0FFF) != pattern) {
        return false;
    }
  Transmit_string_UART(USART6, "ITACHI\r\n");
    return true;
}

bool Wait_Timeout_ACMD41(void) {
    uint32_t timeout;
    uint16_t response;

    timeout = response = 0;
    
    //Wait for first response R1
    do {
        if ((timeout > NCR_TIME) || ((response = Receive_Response()) != 0xFF && response != 0x1)){
            break;
        }
        //response = Receive_Response();
        //if ((response != 0xFF) && (response != 0x1)) {
        //     break;
        //}
        Send_Host_Command(0xFF);
        Delay_us(TIM_SDCARD, 0x1);
        timeout++;
    } while (true);

    if (response) {
        return false;
    }
    else {
        return true;
    }   
}

uint32_t Get_Extended_Response(uint8_t byte) {
    uint32_t response = 0;
    for (int i = 0; i < byte; i++) {
        response = response | Receive_Response(); 
    }
    return response;
}

void Power_Up_Sequence(void) {
    DeSelect_Card();
    Delay_us(TIM_SDCARD, POWER_UP_TIME);//Wait for at least 1ms

    for (int i = 0; i < 10; i++) {
        Send_Host_Command(0xFF);
    }
    //DeSelect_Card();
}

ERR_SD_Init_t Init_SD_Card(void) {
    uint32_t timeout, response, pattern;
    bool power_up_status, capacity_bit;
    
    timeout = response = 0;
    power_up_status = 0;
    pattern = 0x1AA;

    //Enter SPI Mode
    Init_Counter_SDCard(TIM_SDCARD);
    //Initialize peripheral, counter and SPI mode
    Init_SPI_GPIO_Mode();
    Init_SPI_Register();

    Power_Up_Sequence();

    //Reset command
    if (!Wait_Response_R1(RESET_IDLE, 0x0, 0x1)) {
        Set_Pin(GPIO_DBG, GPIO_DBG_Pin_5);
        return ERR_CMD_TIMEOUT;
    }
    //DeSelect_Card();
    Set_Pin(GPIO_DBG, GPIO_DBG_Pin_4);
    if (!Proceed_CMD8(0x1AA)) {
        Set_Pin(GPIO_DBG, GPIO_Pin_5);
        return ERR_PATTERN_NOT_MATCH;
    }
    Reset_Pin(GPIO_DBG, GPIO_DBG_Pin_4);
    //
    //Send_ACMD_Command(SD_SEND_OP_COND, 0x40000000);
    //if (!Wait_Timeout_ACMD41()) {
    //    return TIMEOUT_INITIALIZE;
    //}
    //
    ////Read OCR register
    //timeout = 0;
    //do {
    //    //Prepare_Host_Command(READ_OCR, 0xFFFFFFFF);//Read OCR register
    //    if ((!Wait_Response_R1(READ_OCR, 0xFFFFFFFF, 0x0)) || (timeout > NCR_TIME)) {
    //        return TIMEOUT_INITIALIZE;
    //    }
    //    response = Get_Extended_Response(0x4);
    //    power_up_status = (response & 0x80000000) >> 31;
    //    timeout++; 
    //} while (power_up_status);
    //
    ////Get card type
    //capacity_bit = (response & 0x40000000) >> 30;
    //if (capacity_bit) {
    //    sd_info.sd_type = HIGH_CAPACITY;
    //}
    //else {
    //    sd_info.sd_type = STANDARD_CAPACITY;
    //}

    return ERR_OK;
}

void Send_ACMD_Command(uint8_t command, uint32_t argument) {
    Prepare_Host_Command(APP_CMD, 0xFFFFFFFF);
    Prepare_Host_Command(command, argument);
}
