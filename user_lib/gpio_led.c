/**
 * @author Park Donghyeon
 * @DATA   2017-05-17
 */

#include "gpio_led.h"
#include "stm32f10x_gpio.h"

void gpio_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure GPIOA Tx (PA.11) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}

void led_on(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

void led_off(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}

void led_toggle(void){
	static uint16_t v = 0x0000;
	GPIO_Write(GPIOA, v);
	v ^= 0x0800;
}
