/*
 * FlashReadWrite.h
 *
 *  Created on: Aug 4, 2024
 *      Author: Subhanjit Debnath
 */

#ifndef INC_FLASHREADWRITE_H_
#define INC_FLASHREADWRITE_H_
#include "main.h"
#include <string.h>

typedef struct
{
	uint16_t 	OnTime1;
	uint16_t 	OffTime1;
	uint16_t 	OnTime2;
	uint16_t 	OffTime2;
	uint8_t		Relay1state;
	uint8_t		Relay2state;

}Timesetting;

typedef union
{
	Timesetting Timeset;
	uint64_t 	DataToSave[2];
}SavingData;

typedef union
{
	uint64_t Data64[2];
	uint8_t  data[16];
}data_to_retive;

void SaveData(void);
void EraseFlash(void);
void WriteData(void);
void RetriveData(void);
void UpdateLedDataBeforeSaving(void);

#endif /* INC_FLASHREADWRITE_H_ */
