/*! \file font.c */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 21.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//*****************************************************************************

#include "font.h"

#define FONTREGULARELEMENTS 102
#define FONTTINYELEMENTS 102
#define FONTNANOELEMENTS 102

static const uint8_t fontregular[FONTREGULARELEMENTS][6] = {
		{ 32, 0x00, 0x00, 0x00, 0x00, 0x00 }, //32/ -->
		{ 33, 0x00, 0x4F, 0x00, 0x00, 0x00 }, //33/ --> !
		{ 34, 0x00, 0x07, 0x00, 0x07, 0x00 }, //34/ --> "
		{ 35, 0x14, 0x7F, 0x14, 0x7F, 0x14 }, //35/ --> #
		{ 36, 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, //36/ --> $
		{ 37, 0x23, 0x13, 0x08, 0x64, 0x62 }, //37/ --> %
		{ 38, 0x36, 0x49, 0x55, 0x22, 0x40 }, //38/ --> &
		{ 39, 0x00, 0x05, 0x03, 0x00, 0x00 }, //39/ --> '
		{ 40, 0x00, 0x1C, 0x22, 0x41, 0x00 }, //40/ --> (
		{ 41, 0x00, 0x41, 0x22, 0x1C, 0x00 }, //41/ --> )
		{ 42, 0x14, 0x08, 0x3E, 0x08, 0x14 }, //42/ --> *
		{ 43, 0x08, 0x08, 0x3E, 0x08, 0x08 }, //43/ --> +
		{ 44, 0x00, 0x50, 0x30, 0x00, 0x00 }, //44/ --> ,
		{ 45, 0x08, 0x08, 0x08, 0x08, 0x08 }, //45/ --> -
		{ 46, 0x00, 0x60, 0x60, 0x00, 0x00 }, //46/ --> .
		{ 47, 0x20, 0x10, 0x08, 0x04, 0x02 }, //47/ --> /
		{ 48, 0x3E, 0x51, 0x49, 0x45, 0x3E }, //48/ --> 0
		{ 49, 0x00, 0x42, 0x7F, 0x40, 0x00 }, //49/ --> 1
		{ 50, 0x42, 0x61, 0x51, 0x49, 0x46 }, //50/ --> 2
		{ 51, 0x21, 0x41, 0x45, 0x4B, 0x31 }, //51/ --> 3
		{ 52, 0x18, 0x14, 0x12, 0x7F, 0x10 }, //52/ --> 4
		{ 53, 0x27, 0x45, 0x45, 0x45, 0x39 }, //53/ --> 5
		{ 54, 0x3C, 0x4A, 0x49, 0x49, 0x30 }, //54/ --> 6
		{ 55, 0x01, 0x71, 0x09, 0x05, 0x03 }, //55/ --> 7
		{ 56, 0x36, 0x49, 0x49, 0x49, 0x36 }, //56/ --> 8
		{ 57, 0x06, 0x49, 0x49, 0x29, 0x1E }, //57/ --> 9
		{ 58, 0x00, 0x36, 0x36, 0x00, 0x00 }, //58/ --> :
		{ 59, 0x00, 0x56, 0x36, 0x00, 0x00 }, //59/ --> ;
		{ 60, 0x08, 0x14, 0x22, 0x41, 0x00 }, //60/ --> <
		{ 61, 0x24, 0x24, 0x24, 0x24, 0x24 }, //61/ --> =
		{ 62, 0x41, 0x22, 0x14, 0x08, 0x00 }, //62/ --> >
		{ 63, 0x02, 0x01, 0x51, 0x09, 0x06 }, //63/ --> ?
		{ 64, 0x32, 0x49, 0x79, 0x41, 0x3E }, //64/ --> @
		{ 65, 0x7E, 0x11, 0x11, 0x11, 0x7E }, //65/ --> A
		{ 66, 0x7F, 0x49, 0x49, 0x49, 0x36 }, //66/ --> B
		{ 67, 0x3E, 0x41, 0x41, 0x41, 0x22 }, //67/ --> C
		{ 68, 0x7F, 0x41, 0x41, 0x22, 0x1C }, //68/ --> D
		{ 69, 0x7F, 0x49, 0x49, 0x49, 0x41 }, //69/ --> E
		{ 70, 0x7F, 0x09, 0x09, 0x09, 0x01 }, //70/ --> F
		{ 71, 0x3E, 0x41, 0x49, 0x49, 0x3A }, //71/ --> G
		{ 72, 0x7F, 0x08, 0x08, 0x08, 0x7F }, //72/ --> H
		{ 73, 0x00, 0x41, 0x7F, 0x41, 0x00 }, //73/ --> I
		{ 74, 0x20, 0x41, 0x41, 0x3F, 0x01 }, //74/ --> J
		{ 75, 0x7F, 0x08, 0x14, 0x22, 0x41 }, //75/ --> K
		{ 76, 0x7F, 0x40, 0x40, 0x40, 0x00 }, //76/ --> L
		{ 77, 0x7F, 0x02, 0x0C, 0x02, 0x7F }, //77/ --> M
		{ 78, 0x7F, 0x04, 0x08, 0x10, 0x7F }, //78/ --> N
		{ 79, 0x3E, 0x41, 0x41, 0x41, 0x3E }, //79/ --> O
		{ 80, 0x7F, 0x09, 0x09, 0x09, 0x06 }, //80/ --> P
		{ 81, 0x3E, 0x41, 0x51, 0x21, 0x5E }, //81/ --> Q
		{ 82, 0x7F, 0x09, 0x19, 0x29, 0x46 }, //82/ --> R
		{ 83, 0x46, 0x49, 0x49, 0x49, 0x31 }, //83/ --> S
		{ 84, 0x01, 0x01, 0x7F, 0x01, 0x01 }, //84/ --> T
		{ 85, 0x3F, 0x40, 0x40, 0x40, 0x3F }, //85/ --> U
		{ 86, 0x1F, 0x20, 0x40, 0x20, 0x1F }, //86/ --> V
		{ 87, 0x3F, 0x40, 0x30, 0x40, 0x3F }, //87/ --> W
		{ 88, 0x63, 0x14, 0x08, 0x14, 0x63 }, //88/ --> X
		{ 89, 0x07, 0x08, 0x70, 0x08, 0x07 }, //89/ --> Y
		{ 90, 0x61, 0x51, 0x49, 0x45, 0x43 }, //90/ --> Z
		{ 91, 0x00, 0x7F, 0x41, 0x41, 0x00 }, //91/ --> [
		{ 92, 0x02, 0x04, 0x08, 0x10, 0x20 }, //92/ --> \   /
		{ 93, 0x00, 0x41, 0x41, 0x7F, 0x00 }, //93/ --> ]
		{ 94, 0x04, 0x02, 0x01, 0x02, 0x04 }, //94/ --> ^
		{ 95, 0x40, 0x40, 0x40, 0x40, 0x40 }, //95/ --> _
		{ 96, 0x00, 0x01, 0x02, 0x00, 0x00 }, //96/ --> `
		{ 97, 0x20, 0x54, 0x54, 0x54, 0x78 }, //97/ --> a
		{ 98, 0x7F, 0x44, 0x44, 0x44, 0x38 }, //98/ --> b
		{ 99, 0x38, 0x44, 0x44, 0x44, 0x00 }, //99/ --> c
		{ 100, 0x38, 0x44, 0x44, 0x48, 0x7F }, //100/ --> d
		{ 101, 0x38, 0x54, 0x54, 0x54, 0x18 }, //101/ --> e
		{ 102, 0x10, 0x7E, 0x11, 0x01, 0x02 }, //102/ --> f
		{ 103, 0x0C, 0x52, 0x52, 0x52, 0x3E }, //103/ --> g
		{ 104, 0x7F, 0x08, 0x04, 0x04, 0x78 }, //104/ --> h
		{ 105, 0x00, 0x44, 0x7D, 0x40, 0x00 }, //105/ --> i
		{ 106, 0x20, 0x40, 0x40, 0x3D, 0x00 }, //106/ --> j
		{ 107, 0x7F, 0x10, 0x28, 0x44, 0x00 }, //107/ --> k
		{ 108, 0x00, 0x41, 0x7F, 0x40, 0x00 }, //108/ --> l
		{ 109, 0x7C, 0x04, 0x18, 0x04, 0x78 }, //109/ --> m
		{ 110, 0x7C, 0x08, 0x04, 0x04, 0x78 }, //110/ --> n
		{ 111, 0x38, 0x44, 0x44, 0x44, 0x38 }, //111/ --> o
		{ 112, 0x7C, 0x14, 0x14, 0x14, 0x08 }, //112/ --> p
		{ 113, 0x08, 0x14, 0x14, 0x18, 0x7C }, //113/ --> q
		{ 114, 0x7C, 0x08, 0x04, 0x04, 0x08 }, //114/ --> r
		{ 115, 0x48, 0x54, 0x54, 0x54, 0x24 }, //115/ --> s
		{ 116, 0x04, 0x3F, 0x44, 0x40, 0x20 }, //116/ --> t
		{ 117, 0x3C, 0x40, 0x40, 0x20, 0x7C }, //117/ --> u
		{ 118, 0x1C, 0x20, 0x40, 0x20, 0x1C }, //118/ --> v
		{ 119, 0x3C, 0x40, 0x20, 0x40, 0x3C }, //119/ --> w
		{ 120, 0x44, 0x28, 0x10, 0x28, 0x44 }, //120/ --> x
		{ 121, 0x0C, 0x50, 0x50, 0x50, 0x3C }, //121/ --> y
		{ 122, 0x44, 0x64, 0x54, 0x4C, 0x44 }, //122/ --> z
		{ 123, 0x00, 0x08, 0x36, 0x41, 0x00 }, //123/ --> 	{
		{ 124, 0x00, 0x00, 0x7F, 0x00, 0x00 }, //124/ --> |
		{ 125, 0x00, 0x41, 0x36, 0x08, 0x00 }, //125/ --> }
		{ 126, 0x10, 0x08, 0x10, 0x20, 0x10 }, //126/ --> ~
		{ 196, 0x78, 0x15, 0x14, 0x15, 0x78 }, //142/ --> Ä
		{ 214, 0x38, 0x45, 0x44, 0x45, 0x38 }, //153/ --> Ö
		{ 220, 0x3C, 0x41, 0x40, 0x41, 0x3C }, //154/ --> Ü
		{ 223, 0x7E, 0x01, 0x29, 0x29, 0x16 }, //225/ --> ß
		{ 228, 0x20, 0x55, 0x54, 0x55, 0x78 }, //132/ --> ä
		{ 246, 0x38, 0x45, 0x44, 0x45, 0x38 }, //148/ --> ö
		{ 252, 0x3C, 0x41, 0x40, 0x21, 0x7C } //129/ --> ü
		};

static const uint8_t fonttiny[FONTTINYELEMENTS][5] = {
		{ 32,  0x00, 0x00, 0x00, 0x00}, //32/ -->
		{ 33,  0x00, 0x00, 0x00, 0x00}, //33/ --> !
		{ 34,  0x00, 0x00, 0x00, 0x00}, //34/ --> "
		{ 35,  0x00, 0x00, 0x00, 0x00}, //35/ --> #
		{ 36,  0x00, 0x00, 0x00, 0x00}, //36/ --> $
		{ 37,  0x00, 0x00, 0x00, 0x00}, //37/ --> %
		{ 38,  0x00, 0x00, 0x00, 0x00}, //38/ --> &
		{ 39,  0x00, 0x00, 0x00, 0x00}, //39/ --> '
		{ 40,  0x00, 0x00, 0x00, 0x00}, //40/ --> (
		{ 41,  0x00, 0x00, 0x00, 0x00}, //41/ --> )
		{ 42,  0x00, 0x00, 0x00, 0x00}, //42/ --> *
		{ 43,  0x00, 0x00, 0x00, 0x00}, //43/ --> +
		{ 44,  0x00, 0x00, 0x00, 0x00}, //44/ --> ,
		{ 45,  0x00, 0x00, 0x00, 0x00}, //45/ --> -
		{ 46,  0x00, 0x00, 0x00, 0x00}, //46/ --> .
		{ 47,  0x00, 0x00, 0x00, 0x00}, //47/ --> /
		{ 48,  0x70, 0x88, 0x88, 0x70}, //48/ --> 0
		{ 49,  0x00, 0x00, 0xF8, 0x00}, //49/ --> 1
		{ 50,  0x90, 0xC8, 0xA8, 0x90}, //50/ --> 2
		{ 51,  0x50, 0x88, 0xA8, 0x50}, //51/ --> 3
		{ 52,  0x60, 0x50, 0xE8, 0x40}, //52/ --> 4
		{ 53,  0xB8, 0xA8, 0xA8, 0x48}, //53/ --> 5
		{ 54,  0x70, 0xA8, 0xA8, 0x48}, //54/ --> 6
		{ 55,  0x88, 0x48, 0x28, 0x18}, //55/ --> 7
		{ 56,  0x50, 0xA8, 0xA8, 0x50}, //56/ --> 8
		{ 57,  0x90, 0xA8, 0xA8, 0x70}, //57/ --> 9
		{ 58,  0x00, 0x00, 0x00, 0x00}, //58/ --> :
		{ 59,  0x00, 0x00, 0x00, 0x00}, //59/ --> ;
		{ 60,  0x00, 0x00, 0x00, 0x00}, //60/ --> <
		{ 61,  0x00, 0x00, 0x00, 0x00}, //61/ --> =
		{ 62,  0x00, 0x00, 0x00, 0x00}, //62/ --> >
		{ 63,  0x00, 0x00, 0x00, 0x00}, //63/ --> ?
		{ 64,  0x00, 0x00, 0x00, 0x00}, //64/ --> @
		{ 65,  0x00, 0x00, 0x00, 0x00}, //65/ --> A
		{ 66,  0x00, 0x00, 0x00, 0x00}, //66/ --> B
		{ 67,  0x00, 0x00, 0x00, 0x00}, //67/ --> C
		{ 68,  0x00, 0x00, 0x00, 0x00}, //68/ --> D
		{ 69,  0x00, 0x00, 0x00, 0x00}, //69/ --> E
		{ 70,  0x00, 0x00, 0x00, 0x00}, //70/ --> F
		{ 71,  0x00, 0x00, 0x00, 0x00}, //71/ --> G
		{ 72,  0x00, 0x00, 0x00, 0x00}, //72/ --> H
		{ 73,  0x00, 0x00, 0x00, 0x00}, //73/ --> I
		{ 74,  0x00, 0x00, 0x00, 0x00}, //74/ --> J
		{ 75,  0x00, 0x00, 0x00, 0x00}, //75/ --> K
		{ 76,  0x00, 0x00, 0x00, 0x00}, //76/ --> L
		{ 77,  0x00, 0x00, 0x00, 0x00}, //77/ --> M
		{ 78,  0x00, 0x00, 0x00, 0x00}, //78/ --> N
		{ 79,  0x00, 0x00, 0x00, 0x00}, //79/ --> O
		{ 80,  0x00, 0x00, 0x00, 0x00}, //80/ --> P
		{ 81,  0x00, 0x00, 0x00, 0x00}, //81/ --> Q
		{ 82,  0x00, 0x00, 0x00, 0x00}, //82/ --> R
		{ 83,  0x00, 0x00, 0x00, 0x00}, //83/ --> S
		{ 84,  0x00, 0x00, 0x00, 0x00}, //84/ --> T
		{ 85,  0x00, 0x00, 0x00, 0x00}, //85/ --> U
		{ 86,  0x00, 0x00, 0x00, 0x00}, //86/ --> V
		{ 87,  0x00, 0x00, 0x00, 0x00}, //87/ --> W
		{ 88,  0x00, 0x00, 0x00, 0x00}, //88/ --> X
		{ 89,  0x00, 0x00, 0x00, 0x00}, //89/ --> Y
		{ 90,  0x00, 0x00, 0x00, 0x00}, //90/ --> Z
		{ 91,  0x00, 0x00, 0x00, 0x00}, //91/ --> [
		{ 92,  0x00, 0x00, 0x00, 0x00}, //92/ --> \   /
		{ 93,  0x00, 0x00, 0x00, 0x00}, //93/ --> ]
		{ 94,  0x00, 0x00, 0x00, 0x00}, //94/ --> ^
		{ 95,  0x00, 0x00, 0x00, 0x00}, //95/ --> _
		{ 96,  0x00, 0x00, 0x00, 0x00}, //96/ --> `
		{ 97,  0x00, 0x00, 0x00, 0x00}, //97/ --> a
		{ 98,  0x00, 0x00, 0x00, 0x00}, //98/ --> b
		{ 99,  0x00, 0x00, 0x00, 0x00}, //99/ --> c
		{ 100, 0x00, 0x00, 0x00, 0x00 }, //100/ --> d
		{ 101, 0x00, 0x00, 0x00, 0x00 }, //101/ --> e
		{ 102, 0x00, 0x00, 0x00, 0x00 }, //102/ --> f
		{ 103, 0x00, 0x00, 0x00, 0x00 }, //103/ --> g
		{ 104, 0x00, 0x00, 0x00, 0x00 }, //104/ --> h
		{ 105, 0x00, 0x00, 0x00, 0x00 }, //105/ --> i
		{ 106, 0x00, 0x00, 0x00, 0x00 }, //106/ --> j
		{ 107, 0x00, 0x00, 0x00, 0x00 }, //107/ --> k
		{ 108, 0x00, 0x00, 0x00, 0x00 }, //108/ --> l
		{ 109, 0x00, 0x00, 0x00, 0x00 }, //109/ --> m
		{ 110, 0x00, 0x00, 0x00, 0x00 }, //110/ --> n
		{ 111, 0x00, 0x00, 0x00, 0x00 }, //111/ --> o
		{ 112, 0x00, 0x00, 0x00, 0x00 }, //112/ --> p
		{ 113, 0x00, 0x00, 0x00, 0x00 }, //113/ --> q
		{ 114, 0x00, 0x00, 0x00, 0x00 }, //114/ --> r
		{ 115, 0x00, 0x00, 0x00, 0x00 }, //115/ --> s
		{ 116, 0x00, 0x00, 0x00, 0x00 }, //116/ --> t
		{ 117, 0x00, 0x00, 0x00, 0x00 }, //117/ --> u
		{ 118, 0x00, 0x00, 0x00, 0x00 }, //118/ --> v
		{ 119, 0x00, 0x00, 0x00, 0x00 }, //119/ --> w
		{ 120, 0x00, 0x00, 0x00, 0x00 }, //120/ --> x
		{ 121, 0x00, 0x00, 0x00, 0x00 }, //121/ --> y
		{ 122, 0x00, 0x00, 0x00, 0x00 }, //122/ --> z
		{ 123, 0x00, 0x00, 0x00, 0x00 }, //123/ --> {
		{ 124, 0x00, 0x00, 0x00, 0x00 }, //124/ --> |
		{ 125, 0x00, 0x00, 0x00, 0x00 }, //125/ --> }
		{ 126, 0x00, 0x00, 0x00, 0x00 }, //126/ --> ~
		{ 196, 0x00, 0x00, 0x00, 0x00 }, //142/ --> Ä
		{ 214, 0x00, 0x00, 0x00, 0x00 }, //153/ --> Ö
		{ 220, 0x00, 0x00, 0x00, 0x00 }, //154/ --> Ü
		{ 223, 0x00, 0x00, 0x00, 0x00 }, //225/ --> ß
		{ 228, 0x00, 0x00, 0x00, 0x00 }, //132/ --> ä
		{ 246, 0x00, 0x00, 0x00, 0x00 }, //148/ --> ö
		{ 252, 0x00, 0x00, 0x00, 0x00 }  //129/ --> ü
		};

static const uint8_t fontnano[FONTNANOELEMENTS][4] = {
		{ 32,  0x00, 0x00, 0x00}, //32/ -->
		{ 33,  0x00, 0x00, 0x00}, //33/ --> !
		{ 34,  0x00, 0x00, 0x00}, //34/ --> "
		{ 35,  0x00, 0x00, 0x00}, //35/ --> #
		{ 36,  0x00, 0x00, 0x00}, //36/ --> $
		{ 37,  0x00, 0x00, 0x00}, //37/ --> %
		{ 38,  0x00, 0x00, 0x00}, //38/ --> &
		{ 39,  0x00, 0x00, 0x00}, //39/ --> '
		{ 40,  0x00, 0x00, 0x00}, //40/ --> (
		{ 41,  0x00, 0x00, 0x00}, //41/ --> )
		{ 42,  0x00, 0x00, 0x00}, //42/ --> *
		{ 43,  0x00, 0x00, 0x00}, //43/ --> +
		{ 44,  0x00, 0x00, 0x00}, //44/ --> ,
		{ 45,  0x00, 0x00, 0x00}, //45/ --> -
		{ 46,  0x00, 0x00, 0x00}, //46/ --> .
		{ 47,  0x00, 0x00, 0x00}, //47/ --> /
		{ 48,  0xE0, 0x90, 0x70}, //48/ --> 0
		{ 49,  0x20, 0xF0, 0x00}, //49/ --> 1
		{ 50,  0xD0, 0xD0, 0xA0}, //50/ --> 2
		{ 51,  0x90, 0xB0, 0x60}, //51/ --> 3
		{ 52,  0x70, 0x40, 0xE0}, //52/ --> 4
		{ 53,  0xB0, 0xD0, 0xD0}, //53/ --> 5
		{ 54,  0xE0, 0xD0, 0xD0}, //54/ --> 6
		{ 55,  0x10, 0xD0, 0x30}, //55/ --> 7
		{ 56,  0xF0, 0xB0, 0xF0}, //56/ --> 8
		{ 57,  0xB0, 0xB0, 0x70}, //57/ --> 9
		{ 58,  0x00, 0x00, 0x00}, //58/ --> :
		{ 59,  0x00, 0x00, 0x00}, //59/ --> ;
		{ 60,  0x00, 0x00, 0x00}, //60/ --> <
		{ 61,  0x00, 0x00, 0x00}, //61/ --> =
		{ 62,  0x00, 0x00, 0x00}, //62/ --> >
		{ 63,  0x00, 0x00, 0x00}, //63/ --> ?
		{ 64,  0x00, 0x00, 0x00}, //64/ --> @
		{ 65,  0x00, 0x00, 0x00}, //65/ --> A
		{ 66,  0x00, 0x00, 0x00}, //66/ --> B
		{ 67,  0x00, 0x00, 0x00}, //67/ --> C
		{ 68,  0x00, 0x00, 0x00}, //68/ --> D
		{ 69,  0x00, 0x00, 0x00}, //69/ --> E
		{ 70,  0x00, 0x00, 0x00}, //70/ --> F
		{ 71,  0x00, 0x00, 0x00}, //71/ --> G
		{ 72,  0x00, 0x00, 0x00}, //72/ --> H
		{ 73,  0x00, 0x00, 0x00}, //73/ --> I
		{ 74,  0x00, 0x00, 0x00}, //74/ --> J
		{ 75,  0x00, 0x00, 0x00}, //75/ --> K
		{ 76,  0x00, 0x00, 0x00}, //76/ --> L
		{ 77,  0x00, 0x00, 0x00}, //77/ --> M
		{ 78,  0x00, 0x00, 0x00}, //78/ --> N
		{ 79,  0x00, 0x00, 0x00}, //79/ --> O
		{ 80,  0x00, 0x00, 0x00}, //80/ --> P
		{ 81,  0x00, 0x00, 0x00}, //81/ --> Q
		{ 82,  0x00, 0x00, 0x00}, //82/ --> R
		{ 83,  0x00, 0x00, 0x00}, //83/ --> S
		{ 84,  0x00, 0x00, 0x00}, //84/ --> T
		{ 85,  0x00, 0x00, 0x00}, //85/ --> U
		{ 86,  0x00, 0x00, 0x00}, //86/ --> V
		{ 87,  0x00, 0x00, 0x00}, //87/ --> W
		{ 88,  0x00, 0x00, 0x00}, //88/ --> X
		{ 89,  0x00, 0x00, 0x00}, //89/ --> Y
		{ 90,  0x00, 0x00, 0x00}, //90/ --> Z
		{ 91,  0x00, 0x00, 0x00}, //91/ --> [
		{ 92,  0x00, 0x00, 0x00}, //92/ --> \   /
		{ 93,  0x00, 0x00, 0x00}, //93/ --> ]
		{ 94,  0x00, 0x00, 0x00}, //94/ --> ^
		{ 95,  0x00, 0x00, 0x00}, //95/ --> _
		{ 96,  0x00, 0x00, 0x00}, //96/ --> `
		{ 97,  0x00, 0x00, 0x00}, //97/ --> a
		{ 98,  0x00, 0x00, 0x00}, //98/ --> b
		{ 99,  0x00, 0x00, 0x00}, //99/ --> c
		{ 100, 0x00, 0x00, 0x00}, //100/ --> d
		{ 101, 0x00, 0x00, 0x00}, //101/ --> e
		{ 102, 0x00, 0x00, 0x00}, //102/ --> f
		{ 103, 0x00, 0x00, 0x00}, //103/ --> g
		{ 104, 0x00, 0x00, 0x00}, //104/ --> h
		{ 105, 0x00, 0x00, 0x00}, //105/ --> i
		{ 106, 0x00, 0x00, 0x00}, //106/ --> j
		{ 107, 0x00, 0x00, 0x00}, //107/ --> k
		{ 108, 0x00, 0x00, 0x00}, //108/ --> l
		{ 109, 0x00, 0x00, 0x00}, //109/ --> m
		{ 110, 0x00, 0x00, 0x00}, //110/ --> n
		{ 111, 0x00, 0x00, 0x00}, //111/ --> o
		{ 112, 0x00, 0x00, 0x00}, //112/ --> p
		{ 113, 0x00, 0x00, 0x00}, //113/ --> q
		{ 114, 0x00, 0x00, 0x00}, //114/ --> r
		{ 115, 0x00, 0x00, 0x00}, //115/ --> s
		{ 116, 0x00, 0x00, 0x00}, //116/ --> t
		{ 117, 0x00, 0x00, 0x00}, //117/ --> u
		{ 118, 0x00, 0x00, 0x00}, //118/ --> v
		{ 119, 0x00, 0x00, 0x00}, //119/ --> w
		{ 120, 0x00, 0x00, 0x00}, //120/ --> x
		{ 121, 0x00, 0x00, 0x00}, //121/ --> y
		{ 122, 0x00, 0x00, 0x00}, //122/ --> z
		{ 123, 0x00, 0x00, 0x00}, //123/ --> {
		{ 124, 0x00, 0x00, 0x00}, //124/ --> |
		{ 125, 0x00, 0x00, 0x00}, //125/ --> }
		{ 126, 0x00, 0x00, 0x00}, //126/ --> ~
		{ 196, 0x00, 0x00, 0x00}, //142/ --> Ä
		{ 214, 0x00, 0x00, 0x00}, //153/ --> Ö
		{ 220, 0x00, 0x00, 0x00}, //154/ --> Ü
		{ 223, 0x00, 0x00, 0x00}, //225/ --> ß
		{ 228, 0x00, 0x00, 0x00}, //132/ --> ä
		{ 246, 0x00, 0x00, 0x00}, //148/ --> ö
		{ 252, 0x00, 0x00, 0x00}  //129/ --> ü
		};

uint8_t* font_getChar(uint8_t ascii, uint8_t font) {
	uint8_t i = 0;
	if (ascii < 32)
		return 0;

	switch (font) {
		case FONT_REGULAR:
		default:
			for (i = 0; i < FONTREGULARELEMENTS; i++) {
				if (fontregular[i][0] == ascii)
					return (uint8_t*)&(fontregular[i][1]);
			}
			break;

		case FONT_TINY:
			for (i = 0; i < FONTTINYELEMENTS; i++) {
				if (fonttiny[i][0] == ascii)
					return (uint8_t*)&(fonttiny[i][1]);
			}
			break;

		case FONT_NANO:
			for (i = 0; i < FONTNANOELEMENTS; i++) {
				if (fontnano[i][0] == ascii)
					return (uint8_t*)&(fontnano[i][1]);
			}
			break;
	}

	return 0;
}

uint8_t font_getWidth(uint8_t font) {
	switch (font) {
		case FONT_REGULAR:
		default:
			return 5;
		case FONT_TINY:
			return 4;
		case FONT_NANO:
			return 3;
	}
}

uint8_t font_getHeight(uint8_t font) {
	switch (font) {
		case FONT_REGULAR:
		default:
			return 8;
		case FONT_TINY:
			return 5;
		case FONT_NANO:
			return 4;
	}
}
