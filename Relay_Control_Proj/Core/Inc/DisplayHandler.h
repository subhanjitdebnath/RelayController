/*
 * DisplayHandler.h
 *
 *  Created on: Jul 28, 2024
 *      Author: Subhanjit Debnath
 */

#ifndef INC_DISPLAYHANDLER_H_
#define INC_DISPLAYHANDLER_H_
#include "fonts.h"
#include "ssd1306.h"

typedef struct
{
	uint8_t ScreenPosition;
	uint8_t IndexNo;
	FlagStatus Ok_Pressed;
	FlagStatus Update_req;


}ScreenCtrl;

typedef enum
{
	MENU = 0,
	LABLE ,
}FONT_TYPE;
void Display_run();
void Screen_Welcome();
void LoadingScreen();
void Animation();
void RelaySettingScreen(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2, SSD1306_COLOR_t sel3 );
void MainScreen(SSD1306_COLOR_t sel1 , SSD1306_COLOR_t sel2 ,SSD1306_COLOR_t sel3 );
void LedScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2, SSD1306_COLOR_t sel3, uint8_t led_num );

void SeqScreenLayout(uint8_t number, uint8_t *pos );
void LedScreen(uint8_t *SubIndex, uint8_t *ledNumSel);

void UpdateLineText(char line[] , char* s1 , char* s2);
void UpdateLineText1(char line[] , char* s1 , char* s2);

void MessageScreen(uint8_t ledNum , uint8_t ledPos);

void TimerScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2 );
void TimerSettings(uint8_t *SubIndex);
void TimeChangeLayout(uint8_t timePos, uint8_t *SubIndex);
void UpdateRelaystate(uint8_t *data);
void MessageScreen1();
void MessageScreen2();
void PumpStatus(void);
void Relay1TimerScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2,SSD1306_COLOR_t sel3,uint16_t On_Delay, uint16_t Off_Delay );
void Relay2TimerScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2,SSD1306_COLOR_t sel3,uint16_t On_Delay, uint16_t Off_Delay );

void TimeSlection(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2, SSD1306_COLOR_t sel3);
void OnDelay(uint16_t On_Delay);
void OffDelay(uint16_t Off_Delay);
void ConfigurationScreen(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2 ,SSD1306_COLOR_t sel3 );
#endif /* INC_DISPLAYHANDLER_H_ */
