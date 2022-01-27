#ifndef __DHT11_H__
#define __DHT11_H__
#include "headfile.h"

//DHT11 DATA PB10

//����DATA�ܽţ�
#define DHT11_CLK  RCC_APB2Periph_GPIOB
#define DHT11_PIN  GPIO_Pin_10
#define DHT11_PORT GPIOB
//




//��ȡ��ƽ
#define DHT11_DATA_IN() GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN)

//�����ƽ
#define DHT11_DATA_OUT(a) if(a) \
														GPIO_SetBits(DHT11_PORT,DHT11_PIN); \
                          else  \
														GPIO_ResetBits(DHT11_PORT,DHT11_PIN)

typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;

void DHT11_init(void);
u8 Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);

#endif

