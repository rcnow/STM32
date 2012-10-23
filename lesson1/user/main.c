/*
 ====================================================================
 @Name:GPIO_Pin_IN & GPIO_Pin_OUT
 @Description:Работа с GPIO на примере led и button
 @Date:29.05.2012
 @Author:DAmlex
 @Site:http://rcnow.ru
 ====================================================================
*/

	//INCLUDE
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

	//VARIBLES
int button=0x00;
uint32_t currentButton = 0x00;



	//FUNCTION DELAY
void Delay(uint32_t sec)
{
	int count;
	count=(SystemCoreClock/10000)*sec;
	while(count!=0) count--;
}
	//FUNCTION DEBOUNCE

uint32_t Debounce(uint32_t last)
{
	GPIOA->IDR&GPIO_Pin_0;
	if (last != (GPIOA->IDR&GPIO_Pin_0))
	{
		Delay(5);
		GPIOA->IDR&GPIO_Pin_0;
	}
	return GPIOA->IDR&GPIO_Pin_0;

}

int main(void)
{



	//LED CONFIG
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);



    //BUTTON CONFIG
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;



    //FUNCTION CHECK BUTTON
void But_check()
{
	currentButton = Debounce(button);
	if (button==0x00 && currentButton==0x01)
	{
		GPIOD->ODR^=GPIO_Pin_14;
	}
	button=currentButton;


}
while (1)
{

	But_check();
}
}
