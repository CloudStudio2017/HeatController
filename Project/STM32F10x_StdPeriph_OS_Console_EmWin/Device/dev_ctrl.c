#include "Task_DeviceControl.h"
#include "HeatControlSys.h"
#include "stm32f10x.h"

//Control devices file

static void Fire_Control(int Value);
static void Feeder_Control(int Value);
static void LeadFan_Control(int Value);
static void Blower_Control(int Value);
static void Dev_out_init_all(void);

Device_t dev_Fire ={.ControlAdj = Fire_Control, .Init = Dev_out_init_all};
Device_t dev_Feeder ={.ControlAdj = Feeder_Control, .Init = Dev_out_init_all};
Device_t dev_LeadFan ={.ControlAdj = LeadFan_Control, .Init = Dev_out_init_all};
Device_t dev_Blower ={.ControlAdj = Blower_Control, .Init = Dev_out_init_all};

#define DEV_LL_FIRE_GPIO       _OUT_RL3_GPIO
#define DEV_LL_FIRE_PIN        _OUT_RL3_PIN
#define DEV_LL_FEEDER_GPIO     _OUT_RL2_GPIO
#define DEV_LL_FEEDER_PIN      _OUT_RL2_PIN
#define DEV_LL_LEADFAN_GPIO    _OUT_WP1_GPIO
#define DEV_LL_LEADFAN_PIN     _OUT_WP1_PIN
#define DEV_LL_BLOWER_GPIO     _OUT_WP2_GPIO
#define DEV_LL_BLOWER_PIN      _OUT_WP2_PIN


//output device init all in one
static void Dev_out_init_all(void)
{
	static unsigned char is_init = 0;
	
	if(is_init)
		return;
	
	GPIO_InitTypeDef gp;
	
	gp.GPIO_Mode = GPIO_Mode_Out_PP;
	gp.GPIO_Speed = GPIO_Speed_10MHz;
	RCC_APB2PeriphClockCmd(
		GPIO2RCC(DEV_LL_FIRE_GPIO) |
		GPIO2RCC(DEV_LL_FEEDER_GPIO) |
		GPIO2RCC(DEV_LL_LEADFAN_GPIO) |
		GPIO2RCC(DEV_LL_BLOWER_GPIO),
		ENABLE);
	
	gp.GPIO_Pin = DEV_LL_FIRE_PIN;
	GPIO_Init(DEV_LL_FIRE_GPIO, &gp);
	
	gp.GPIO_Pin = DEV_LL_FEEDER_PIN;
	GPIO_Init(DEV_LL_FEEDER_GPIO, &gp);
	
	gp.GPIO_Pin = DEV_LL_LEADFAN_PIN;
	GPIO_Init(DEV_LL_LEADFAN_GPIO, &gp);
	
	gp.GPIO_Pin = DEV_LL_BLOWER_PIN;
	GPIO_Init(DEV_LL_BLOWER_GPIO, &gp);
}

static void Fire_Control(int Value)
{
	if(Value)
	{
		GPIO_SetBits(DEV_LL_FIRE_GPIO, DEV_LL_FIRE_PIN);
	}
	else
	{
		GPIO_ResetBits(DEV_LL_FIRE_GPIO, DEV_LL_FIRE_PIN);
	}
}

static void Feeder_Control(int Value)
{
	if(Value)
	{
		GPIO_SetBits(DEV_LL_FEEDER_GPIO, DEV_LL_FEEDER_PIN);
	}
	else
	{
		GPIO_ResetBits(DEV_LL_FEEDER_GPIO, DEV_LL_FEEDER_PIN);
	}
}

static void LeadFan_Control(int Value)
{
}

static void Blower_Control(int Value)
{
}
