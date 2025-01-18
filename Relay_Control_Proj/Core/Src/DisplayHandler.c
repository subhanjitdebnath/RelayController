/*
 * DisplayHandler.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Subhanjit Debnath
 */
#include "DisplayHandler.h"
#include "bitmap.h"
#include "horse_anim.h"
#include <stdio.h>
#include <string.h>
#include "FlashReadWrite.h"

extern FONT_TYPE __font_type__;

uint8_t RelayStatusVal[2] = {0,0};
static char Line1[20];
static char Line2[20];

extern uint16_t On_delay_R1,On_delay_R2,Off_delay_R1,Off_delay_R2;

char* FixeLable[] = {"    MENU ", " RELAY SETTING ", " UP   OK     DN", " TIME SET", "  Saving...","    LED", " PREV   OK   NEXT ", " DN   OK     UP"};

char* TimeDateLable[] = {"  On Delay","  Off Delay","Day","Month","Year","ms"," s"};

char* MenuName[] = { " 1. RELAY SETTING" ," 2. Timer setting", " 3. Save Setting" };
char* RelayName[] ={" Relay 1"," Relay 2"};
char* RelayStatus[] ={"<Enable>","<Disable>","<Manual>"};


extern uint16_t On_Delay;
extern uint16_t Off_Delay;
//extern ScreenCtrl   Scrn_Ctrl;

volatile uint8_t ScreenPosition;
volatile uint8_t IndexNo;
volatile FlagStatus Ok_Pressed;
volatile FlagStatus Update_req;
//START OF THE MODULES

void Screen_Welcome()
{
	LoadingScreen();
}

void Animation(void)
{
	//// HORSE ANIMATION START //////

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse1,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse2,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse3,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse4,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse5,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse6,128,64,1);
		  SSD1306_UpdateScreen();


		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse7,128,64,1);
		  SSD1306_UpdateScreen();

		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse8,128,64,1);
		  SSD1306_UpdateScreen();


		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse9,128,64,1);
		  SSD1306_UpdateScreen();


		  SSD1306_Clear();
		  SSD1306_DrawBitmap(0,0,horse10,128,64,1);
		  SSD1306_UpdateScreen();


		  //// HORSE ANIMATION ENDS //////
}

void LoadingScreen(void)
{
		SSD1306_Clear();
		SSD1306_GotoXY (0,40);
		SSD1306_Puts ("   NEXT WAVE OF ", &Font_7x10, 1);
		SSD1306_GotoXY (0,50);
		SSD1306_Puts ("    INNOVATION", &Font_7x10, 1);
		SSD1306_UpdateScreen();
	    SSD1306_DrawBitmap(0,0,Logo_Cmp, 128, 38, 1);
	    SSD1306_UpdateScreen();

	    HAL_Delay(2000);

	    SSD1306_ScrollRight(0x00, 0x0f);    // scroll entire screen right

	    HAL_Delay (2000);

	    SSD1306_ScrollLeft(0x00, 0x0f);  // scroll entire screen left

	    HAL_Delay (2000);

	    SSD1306_Scrolldiagright(0x00, 0x0f);  // scroll entire screen diagonal right

	    HAL_Delay (2000);

	    SSD1306_Scrolldiagleft(0x00, 0x0f);  // scroll entire screen diagonal left

	    HAL_Delay (2000);

	    SSD1306_Stopscroll();   // stop scrolling. If not done, screen will keep on scrolling


	    SSD1306_InvertDisplay(1);   // invert the display

	    HAL_Delay(2000);

	    SSD1306_InvertDisplay(0);  // normalize the display
	//
	    SSD1306_Stopscroll();     // stop scrolling

	    HAL_Delay(2000);
}

void MainScreen(SSD1306_COLOR_t sel1 , SSD1306_COLOR_t sel2 ,SSD1306_COLOR_t sel3 )
{
	SSD1306_Clear();
    SSD1306_GotoXY (0,0);
	SSD1306_Puts (FixeLable[0], &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (MenuName[0], &Font_7x10, sel1);
	SSD1306_GotoXY (0,30);
	SSD1306_Puts (MenuName[1], &Font_7x10, sel2);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (MenuName[2], &Font_7x10, sel3);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[2], &Font_7x10, 1);
    SSD1306_UpdateScreen();
}

void RelaySettingScreen(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2 ,SSD1306_COLOR_t sel3 )
{


	UpdateLineText1(Line1,RelayName[0],RelayStatus[RelayStatusVal[0]]);
	UpdateLineText1(Line2,RelayName[1],RelayStatus[RelayStatusVal[1]]);

	SSD1306_Clear();
    SSD1306_GotoXY (0,0);
	SSD1306_Puts (FixeLable[1], &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (Line1, &Font_7x10, sel1);
	SSD1306_GotoXY (0,30);
	SSD1306_Puts (Line2, &Font_7x10, sel2);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (" Save Setting", &Font_7x10, sel3);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[2], &Font_7x10, 1);
    SSD1306_UpdateScreen();

}

void UpdateLineText(char line[] , char* s1 , char* s2)
{
	memset(line,'\0',20);
	int i =0;
	while(*s1 != '\0')
	{
		line[i] = *s1;
		s1++;
		i++;
	}
	line[i] = ' ';
	i++;
	line[i] = '=';
	i++;
	while(*s2 != '\0')
	{
		line[i] = *s2;
		s2++;
		i++;
	}
}

void UpdateLineText1(char line[] , char* s1 , char* s2)
{
	memset(line,'\0',20);
	int i =0;
	while(*s1 != '\0')
	{
		line[i] = *s1;
		s1++;
		i++;
	}
	line[i] = ' ';
	i++;
	while(*s2 != '\0')
	{
		line[i] = *s2;
		s2++;
		i++;
	}
}

void MessageScreen1()
{
	SSD1306_Clear();
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (FixeLable[4], &Font_11x18, 1);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (FixeLable[5], &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void MessageScreen2()
{
	SSD1306_Clear();
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ("SAVING TIME", &Font_11x18, 1);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts ("STATE", &Font_11x18, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(200);
}

void Display_run()
{
	FlagStatus statusOk = SET;
	if(Update_req)
	{
		switch(ScreenPosition)
		{
		case 0: //Main Menu

			switch(IndexNo)
			{
			case 0: //Index - 1 selected
				MainScreen(0,1,1);
				if(Ok_Pressed)
				{
					ScreenPosition = 1;
					statusOk = RESET;
					Ok_Pressed = RESET;
					IndexNo = 0;
				}
				break;
			case 1: //Index - 2 selected
				MainScreen(1,0,1);
				if(Ok_Pressed)
				{
					ScreenPosition = 2;
					statusOk = RESET;
					Ok_Pressed = RESET;
					IndexNo = 0;
				}
				break;
			case 2: //Index - 3 selected
				MainScreen(1,1,0);
				if(Ok_Pressed)
				{
					SaveData();
					ScreenPosition = 0;
					IndexNo = 0;
					Ok_Pressed = RESET;
					statusOk = RESET;
					MessageScreen2();
				}
				break;
			default:
				IndexNo = 0;
				statusOk = RESET;
				break;
			}
			break;

		case 1: //Relay Setting Screen

			switch(IndexNo)
			{
			case 0:
				if(Ok_Pressed)
				{
					UpdateRelaystate(&RelayStatusVal[0]);
					Ok_Pressed = RESET;
				}
				RelaySettingScreen(0,1,1);
				break;
			case 1:
				if(Ok_Pressed)
				{
					UpdateRelaystate(&RelayStatusVal[1]);
					Ok_Pressed = RESET;
				}
				RelaySettingScreen(1,0,1);
				break;
			case 2:
				if(Ok_Pressed)
				{
					ScreenPosition = 0;
					IndexNo = 0;
					Ok_Pressed = RESET;
					statusOk = RESET;
				}
				RelaySettingScreen(1,1,0);
				break;
			default:
				IndexNo = 0;
				statusOk = RESET;
				break;
			}

			break;
			case 2: //Timing Screen

				switch(IndexNo)
				{
				case 0:
					if(Ok_Pressed)
					{
						ScreenPosition = 3;
						IndexNo = 0;
						Ok_Pressed = RESET;
						statusOk = RESET;
					}
					TimeSlection(0,1,1);
					break;
				case 1:
					if(Ok_Pressed)
					{
						ScreenPosition = 4;
						IndexNo = 0;
						Ok_Pressed = RESET;
						statusOk = RESET;
					}
					TimeSlection(1,0,1);
					break;
				case 2:
					if(Ok_Pressed)
					{
						ScreenPosition = 0;
						IndexNo = 0;
						Ok_Pressed = RESET;
						statusOk = RESET;
					}
					TimeSlection(1,1,0);
					break;
				default:
					IndexNo = 0;
					statusOk = RESET;
					break;
				}

				break;
				case 3: //Relay 1 Timing Setting
					switch(IndexNo)
					{
					case 0:
						if(Ok_Pressed)
						{
							ScreenPosition = 5;
							statusOk = RESET;
							Ok_Pressed = RESET;
							IndexNo = On_delay_R1;
						}
						Relay1TimerScreenLayout(0,1,1,On_delay_R1,Off_delay_R1);
						break;
					case 1:
						if(Ok_Pressed)
						{
							ScreenPosition = 6;
							statusOk = RESET;
							Ok_Pressed = RESET;
							IndexNo = Off_delay_R1;
						}
						Relay1TimerScreenLayout(1,0,1,On_delay_R1,Off_delay_R1);
						break;
					case 2:
						if(Ok_Pressed)
						{
							ScreenPosition = 0;
							IndexNo = 0;
							Ok_Pressed = RESET;
							statusOk = RESET;
						}
						Relay1TimerScreenLayout(1,1,0,On_delay_R1,Off_delay_R1);
						break;
					default:
						IndexNo = 0;
						statusOk = RESET;
						break;
					}

					break;
				case 4: //Relay 2 Timing Setting
				switch(IndexNo)
				{
				case 0:
					if(Ok_Pressed)
					{
						ScreenPosition = 7;
						statusOk = RESET;
						Ok_Pressed = RESET;
						IndexNo = On_delay_R2;
					}
					Relay2TimerScreenLayout(0,1,1,On_delay_R2,Off_delay_R2);
					break;
				case 1:
					if(Ok_Pressed)
					{
						ScreenPosition = 8;
						statusOk = RESET;
						Ok_Pressed = RESET;
						IndexNo = Off_delay_R2;
					}
					Relay2TimerScreenLayout(1,0,1,On_delay_R2,Off_delay_R2);
					break;
				case 2:
					if(Ok_Pressed)
					{
						ScreenPosition = 0;
						IndexNo = 0;
						Ok_Pressed = RESET;
						statusOk = RESET;
					}
					Relay2TimerScreenLayout(1,1,0,On_delay_R2,Off_delay_R2);
					break;
				default:
					IndexNo = 0;
					statusOk = RESET;
					break;
				}

				break;

	case 5: //Relay 1 On Delay
		On_delay_R1 = IndexNo;
			if(Ok_Pressed)
			{
				ScreenPosition = 3;
				IndexNo = 0;
				Ok_Pressed = RESET;
				statusOk = RESET;
			}
			OnDelay(On_delay_R1);
		break;

	case 6: //Relay 1 Off Delay
		Off_delay_R1 = IndexNo;
			if(Ok_Pressed)
			{
				ScreenPosition = 3;
				IndexNo = 0;
				Ok_Pressed = RESET;
				statusOk = RESET;
			}
			OffDelay(Off_delay_R1);
		break;

	case 7: //Relay 2 On Delay
			On_delay_R2 = IndexNo;
			if(Ok_Pressed)
			{
				ScreenPosition = 4;
				IndexNo = 0;
				Ok_Pressed = RESET;
				statusOk = RESET;
			}
			OnDelay(On_delay_R2);
		break;

	case 8: //Relay 2 On Delay
			Off_delay_R2 = IndexNo;
			if(Ok_Pressed)
			{
				ScreenPosition = 4;
				IndexNo = 0;
				Ok_Pressed = RESET;
				statusOk = RESET;
			}
			OffDelay(Off_delay_R2);
		break;

		default:
			break;
		}
		if(statusOk )
		{Update_req = RESET;}
	}
}

void UpdateRelaystate(uint8_t *data)
{
	if(*data == 1)
	{
		*data = 0;
	}
	else
	{
		*data = 1;
	}
}

void Relay1TimerScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2,SSD1306_COLOR_t sel3,uint16_t On_Delay,uint16_t Off_Delay )
{
	char OnDelay[20];
	char OffDelay[20];

	sprintf(OnDelay,"%d",On_Delay);
	sprintf(OffDelay,"%d",Off_Delay);

	UpdateLineText(Line1,TimeDateLable[0],OnDelay);
	UpdateLineText(Line2,TimeDateLable[1],OffDelay);

	SSD1306_Clear();
    SSD1306_GotoXY (0,0);
	SSD1306_Puts (RelayName[0], &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (Line1, &Font_7x10, sel1);
	SSD1306_GotoXY (0,30);
	SSD1306_Puts (Line2, &Font_7x10, sel2);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (" Save Setting", &Font_7x10, sel3);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[2], &Font_7x10, 1);
    SSD1306_UpdateScreen();

}

void Relay2TimerScreenLayout(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2,SSD1306_COLOR_t sel3,uint16_t On_Delay, uint16_t Off_Delay )
{
	char OnDelay[20];
	char OffDelay[20];

	sprintf(OnDelay,"%d",On_Delay);
	sprintf(OffDelay,"%d",Off_Delay);

	UpdateLineText(Line1,TimeDateLable[0],OnDelay);
	UpdateLineText(Line2,TimeDateLable[1],OffDelay);

	SSD1306_Clear();
    SSD1306_GotoXY (0,0);
	SSD1306_Puts (RelayName[1], &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (Line1, &Font_7x10, sel1);
	SSD1306_GotoXY (0,30);
	SSD1306_Puts (Line2, &Font_7x10, sel2);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (" Save Setting", &Font_7x10, sel3);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[2], &Font_7x10, 1);
    SSD1306_UpdateScreen();

}

void TimeSlection(SSD1306_COLOR_t sel1, SSD1306_COLOR_t sel2, SSD1306_COLOR_t sel3)
{
	SSD1306_Clear();
    SSD1306_GotoXY (0,0);
	SSD1306_Puts (FixeLable[3], &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (RelayName[0], &Font_7x10, sel1);
	SSD1306_GotoXY (0,30);
	SSD1306_Puts (RelayName[1], &Font_7x10, sel2);
	SSD1306_GotoXY (0,40);
	SSD1306_Puts (" Save Setting", &Font_7x10, sel3);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[2], &Font_7x10, 1);
    SSD1306_UpdateScreen();
}

void OnDelay(uint16_t On_Delay)
{
	char OnDelay_[20];
	sprintf(OnDelay_,"%d",On_Delay);
	UpdateLineText1(Line1,OnDelay_,TimeDateLable[6]);
	SSD1306_Clear();
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (" ON DELAY", &Font_11x18, 1);
	SSD1306_GotoXY (10,20);
	SSD1306_Puts (Line1, &Font_11x18, 1);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[7], &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

void OffDelay(uint16_t Off_Delay)
{
	char OffDelay_[20];
	sprintf(OffDelay_,"%d",Off_Delay);
	UpdateLineText1(Line2,OffDelay_,TimeDateLable[6]);
	SSD1306_Clear();
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (" OFF DELAY", &Font_11x18, 1);
	SSD1306_GotoXY (10,20);
	SSD1306_Puts (Line2, &Font_11x18, 1);
	SSD1306_GotoXY (0,52);
	SSD1306_Puts (FixeLable[7], &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

