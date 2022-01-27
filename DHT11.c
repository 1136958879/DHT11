#include "DHT11.h"

//PB10 Data

/*
 * ��������DHT11_init
 * ����  ��DHT11�ĳ�ʼ����ֻ���޸�.h�ļ��Ĺܽ�
 * ����  ��QС��
 * ����  ����
 * ���  ����
 */

void DHT11_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	
	GPIO_SetBits(DHT11_PORT, DHT11_PIN);	
}

//����������Ϊ��������ģʽ
static void DHT11_DIR_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

//����������Ϊ�������ģʽ
static void DHT11_DIR_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

//��DHT11��ȡһ���ֽڣ�MSB����
static u8 DHT11_Read_Byte()
{
	u8 i,temp = 0;
	for(i=0;i<8;i++){
		while(DHT11_DATA_IN() == 0);//�ȴ�50us�͵�ƽ����
		
		//DHT11 ��26-28us�ĸߵ�ƽ��ʾ0����70us�ߵ�ƽ��ʾ1
		//ͨ�����x us ��ĵ�ƽ��������������״̬
		
		delay_us(40);//��ʱx us�������ʱ��Ҫ��������0������ʱ�伴��
		
		if(DHT11_DATA_IN() == 1){
			while(DHT11_DATA_IN() == 1);//�ȴ�����1�ĸߵ�ƽ����
			temp|=(u8)(0x01<<(7-i));//�ѵ�7-iλ��1��MSB����
		}
		else{
			temp&=(u8)~(0x01<<(7-i));//�ѵ�7-iλ��0��MSB����
		}
		
	}
	return temp;
}

/*
 * ��������Read_DHT11
 * ����  ��DHT11�����ݶ�ȡ�����Զ�ȡʪ�Ⱥ��¶ȵ�����
 * ����  ��QС��
 * ����  ������һ���ṹ��
 * ���  �����ʪ�Ⱥ��¶ȵ�����
 */
u8 Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{
	//���ģʽ
	DHT11_DIR_OUT();
	
	//��������
	DHT11_DATA_OUT(0);
	
	//��ʱ18ms
	delay_ms(18);
	
	//�������ߣ�������ʱ30us
	DHT11_DATA_OUT(1);
	delay_us(30);//��ʱ30us
	
	//������Ϊ���룬�жϴӻ���Ӧ�ź�
	DHT11_DIR_IN();
	
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�źţ��������Ӧ����������Ӧ����������
	if(DHT11_DATA_IN() == 0){
		//ѭ������ֱ���ӻ�����80us�ĵ͵�ƽ����־�źŽ���
		while(DHT11_DATA_IN() == 0);
		
		//ѭ������ֱ���ӻ�����80us�ĸߵ�ƽ����־�źŽ���
		while(DHT11_DATA_IN() == 1);
		
		//��ʼ��������
		DHT11_Data->humi_int = DHT11_Read_Byte();
		DHT11_Data->humi_deci = DHT11_Read_Byte();
		
		DHT11_Data->temp_int = DHT11_Read_Byte();
		DHT11_Data->temp_deci = DHT11_Read_Byte();
		
		DHT11_Data->check_sum = DHT11_Read_Byte();
		
		//��ȡ���������Ÿ�Ϊ���ģʽ
		DHT11_DIR_OUT();
		
		//��������
		DHT11_DATA_OUT(1);
		
		//����ȡ�������Ƿ���ȷ
		if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
			return 1;
		else 
			return 0;
			
	}
	
	else return 0;
	
}


