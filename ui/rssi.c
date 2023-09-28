/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>
#include "bitmaps.h"
#include "driver/st7565.h"
#include "functions.h"
#include "misc.h"
#include "settings.h"
#include "ui/rssi.h"
#include "ui/ui.h"
#include "ui/helper.h"
#include "external/printf/printf.h"

/*
static void Render(uint8_t RssiLevel, uint8_t VFO)
{
	uint8_t *pLine;
	uint8_t Line;
	bool bIsClearMode;

	if (gCurrentFunction == FUNCTION_TRANSMIT || gScreenToDisplay != DISPLAY_MAIN) {
		return;
	}

	if (VFO == 0) {
		pLine = gFrameBuffer[2];
		Line = 3;
	} else {
		pLine = gFrameBuffer[6];
		Line = 7;
	}

	memset(pLine, 0, 23);
	if (RssiLevel == 0) {
		pLine = NULL;
		bIsClearMode = true;
	} else {
		memcpy(pLine, BITMAP_Antenna, 5);
		memcpy(pLine + 5, BITMAP_AntennaLevel1, sizeof(BITMAP_AntennaLevel1));
		if (RssiLevel >= 2) {
			memcpy(pLine + 8, BITMAP_AntennaLevel2, sizeof(BITMAP_AntennaLevel2));
		}
		if (RssiLevel >= 3) {
			memcpy(pLine + 11, BITMAP_AntennaLevel3, sizeof(BITMAP_AntennaLevel3));
		}
		if (RssiLevel >= 4) {
			memcpy(pLine + 14, BITMAP_AntennaLevel4, sizeof(BITMAP_AntennaLevel4));
		}
		if (RssiLevel >= 5) {
			memcpy(pLine + 17, BITMAP_AntennaLevel5, sizeof(BITMAP_AntennaLevel5));
		}
		if (RssiLevel >= 6) {
			memcpy(pLine + 20, BITMAP_AntennaLevel6, sizeof(BITMAP_AntennaLevel6));
		}
		char s[8];
		NUMBER_ToDigits(gCurrentRSSI,s);
		UI_DisplaySmallDigits(4, s+4, 50, Line);
		bIsClearMode = false;
	}

	ST7565_DrawLine(0, Line, 23 , pLine, bIsClearMode);
}
*/

void UI_UpdateRSSI(uint16_t RSSI)
{
	if (gEeprom.KEY_LOCK && gKeypadLocked > 0) return;

	char s[8];
	uint8_t Line;
	const int16_t dBm = (RSSI / 2) - 160;

	if (gEeprom.RX_CHANNEL == 0) {
		Line = 3;
	} else {
		Line = 7;
	}

	sprintf(s, "%-3d", dBm);
	UI_PrintStringSmall(s, 2, 0, Line);

	ST7565_BlitFullScreen();
	
}
