/*
 * RelayHandler.c
 *
 *  Created on: Jan 19, 2025
 *      Author: Subhanjit Debnath
 */
#include "RelayHandler.h"

extern FlagStatus SequenceStart;
extern uint8_t RelayStatusVal[2];
extern uint8_t RelayStartAsVal[2];
extern FlagStatus SequenceStart;
extern uint16_t On_delay_R1,On_delay_R2,Off_delay_R1,Off_delay_R2;
extern GPIO_PinState RELAY1,RELAY2;

uint32_t relay1time,relay1diff,relay2time,relay2diff;
void RelaySequence()
{
	if(SequenceStart)
	{
		Relay1seq();
		Relay2seq();

	}
	else
	{
		relay1time = HAL_GetTick();
		relay1diff = 0;
		relay2time = HAL_GetTick();
		relay2diff = 0;
		RELAY1 = GPIO_PIN_RESET;
		RELAY2 = GPIO_PIN_RESET;
	}
}

void Relay1seq()
{
	if(RelayStatusVal[0] == 0)
	{
		if(RELAY1)
		{
			if(relay1diff > On_delay_R1*1000)
			{
				RELAY1 = GPIO_PIN_RESET;
				relay1diff = 0;
				relay1time = HAL_GetTick();
			}
			else
			{
				relay1diff = Absolute(relay1time, HAL_GetTick());
			}
		}
		else
		{
			if(relay1diff > Off_delay_R1*1000)
			{
				RELAY1 = GPIO_PIN_SET;
				relay1diff = 0;
				relay1time = HAL_GetTick();
			}
			else
			{
				relay1diff = Absolute(relay1time, HAL_GetTick());
			}

		}


	}
	else
	{
		RELAY1 = GPIO_PIN_RESET;
	}
}

void Relay2seq()
{
	if(RelayStatusVal[1] == 0)
	{
		if(RELAY2)
		{
			if(relay2diff > On_delay_R2*1000)
			{
				RELAY2 = GPIO_PIN_RESET;
				relay2diff = 0;
				relay2time = HAL_GetTick();
			}
			else
			{
				relay2diff = Absolute(relay2time, HAL_GetTick());
			}
		}
		else
		{
			if(relay2diff > Off_delay_R2*1000)
			{
				RELAY2 = GPIO_PIN_SET;
				relay2diff = 0;
				relay2time = HAL_GetTick();
			}
			else
			{
				relay2diff = Absolute(relay2time, HAL_GetTick());
			}

		}

	}
	else
	{
		RELAY2 = GPIO_PIN_RESET;
	}
}

uint32_t Absolute(uint32_t val1, uint32_t val2)
{
	return (val1 > val2 ? (val1 - val2):(val2 - val1));
}
