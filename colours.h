/******************************************************************************
**
** File           :  colours.h
**
** Module         :  None
**
** Description    :  Defines several standard colours
**
**
** Derived from   :  None
**
**============================================================================
**============================================================================
**
** Notes          :  None
**
******************************************************************************
*****************************************************************************/
#ifndef COLOURS_H
#define COLOURS_H

const COLORREF RGBLtBlue = RGB(0, 0, 255);                //1
const COLORREF RGBSkyBlue = RGB(166,202,255);                
const COLORREF RGBDkBlue = RGB(0, 0, 155);  
const COLORREF RGBCyan = RGB(65, 235, 221);
const COLORREF RGBDkRed = RGB(229, 36, 10);
const COLORREF RGBLtYellow = RGB(255, 255, 0);				//5
const COLORREF RGBWashedRed = RGB(235, 189, 182);
const COLORREF RGBWhite = RGB(255, 255, 255);
const COLORREF RGBLtGray = RGB(192, 192, 192);
const COLORREF RGBGray = RGB(132, 130, 132);
const COLORREF RGBAmber = RGB(255, 192, 0);					//10
const COLORREF RGBLtGreen = RGB(0, 255, 0);
const COLORREF RGBLtPurple = RGB(200, 86, 188);
const COLORREF RGBDkPurple = RGB(152, 74, 140);
const COLORREF RGBLtPink = RGB(255, 192, 255);				//15
const COLORREF RGBLimeGreen = RGB(25, 192, 140);
const COLORREF RGBLtRed = RGB(247, 100, 100);
const COLORREF RGBDarkerRed = RGB(156, 10, 20);
const COLORREF RGBLtPurp2 = RGB(232, 186, 226);
const COLORREF RGBLeafGreen = RGB(165, 195, 148);
const COLORREF RGBDkCyan = RGB(44,168,158);
const COLORREF RGBWashedYellow = RGB(244,237,197);
const COLORREF RGBDkBlue2 = RGB(78,111,137);
const COLORREF RGBDkBrown = RGB(137,78,78);
const COLORREF RGBBlack = RGB(0, 0, 0);

const int RGBcolours[] = {RGBLtBlue, RGBSkyBlue, RGBDkBlue, RGBCyan, RGBDkRed , 
						RGBLtYellow,RGBWashedRed,  RGBWhite, RGBLtGray, RGBGray, 
						RGBAmber, RGBLtGreen,  RGBLtPink, RGBDkCyan, RGBWashedYellow,
						RGBLimeGreen, RGBLtRed, RGBDarkerRed, RGBLtPurp2, RGBLeafGreen,
						RGBLtPurple, RGBDkPurple, RGBDkBlue2, RGBDkBrown, 
						
						RGBBlack };
const int numOfColours = 25;

enum colours
{
	LtBlue=0, SkyBlue, DkBlue, Cyan, DkRed, 
	LtYellow, WashedRed, White, LtGray, Gray, 
	Amber, LtGreen, DkCyan, WashedYellow, LtPink,
	LimeGreen, LtRed, DarkerRed, LtPurp2, LeafGreen,
	LtPurple, DkPurple, DkBlue2, DkBrown,
	Black,
};



#endif   // end of COLOURS_H

//****************************************************************************
//************************* End of Module ************************************      
//****************************************************************************
