/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */ 

#undef DLGHACK		// HINT: don't even bother turning this on :-)
#ifdef DLGHACK		// see bottom of file for an apology
#ifdef WIN32
#include <windows.h>
#include "ut_debugmsg.h"
#include "pd_Document.h"
#include "fl_DocLayout.h"
#include "gr_Win32Graphics.h"
#endif
#endif /* DLGHACK */

#include "ev_EditMethod.h"
#include "fv_View.h"
#include "fl_Types.h"
#include "ap_EditMethods.h"

/*****************************************************************/
/*****************************************************************/

/* abbreviations:
**   BOL    beginning of line
**   EOL    end of line
**   BOW    beginning of word
**   EOW    end of word
**   BOW    beginning of sentence
**   EOS    end of sentence
**   BOB    beginning of block
**   EOB    end of block
**   BOD    beginning of document
**   EOD    end of document
**
**   warpInsPt    warp insertion point
**   extSel       extend selection
**   del          delete
**   bck          backwards
**   fwd          forwards
**/

class ap_EditMethods
{
public:
	static EV_EditMethod_Fn scrollPageDown;
	static EV_EditMethod_Fn scrollPageUp;
	static EV_EditMethod_Fn scrollPageLeft;
	static EV_EditMethod_Fn scrollPageRight;
	static EV_EditMethod_Fn scrollLineDown;
	static EV_EditMethod_Fn scrollLineUp;
	static EV_EditMethod_Fn scrollLineLeft;
	static EV_EditMethod_Fn scrollLineRight;
	static EV_EditMethod_Fn scrollToTop;
	static EV_EditMethod_Fn scrollToBottom;

	static EV_EditMethod_Fn warpInsPtToXY;
	static EV_EditMethod_Fn warpInsPtLeft;
	static EV_EditMethod_Fn warpInsPtRight;
	static EV_EditMethod_Fn warpInsPtBOL;
	static EV_EditMethod_Fn warpInsPtEOL;
	static EV_EditMethod_Fn warpInsPtBOW;
	static EV_EditMethod_Fn warpInsPtEOW;
	static EV_EditMethod_Fn warpInsPtBOS;
	static EV_EditMethod_Fn warpInsPtEOS;
	static EV_EditMethod_Fn warpInsPtBOB;
	static EV_EditMethod_Fn warpInsPtEOB;
	static EV_EditMethod_Fn warpInsPtBOD;
	static EV_EditMethod_Fn warpInsPtEOD;
	static EV_EditMethod_Fn warpInsPtPrevLine;
	static EV_EditMethod_Fn warpInsPtNextLine;

	static EV_EditMethod_Fn extSelToXY;
	static EV_EditMethod_Fn extSelLeft;
	static EV_EditMethod_Fn extSelRight;
	static EV_EditMethod_Fn extSelBOL;
	static EV_EditMethod_Fn extSelEOL;
	static EV_EditMethod_Fn extSelBOW;
	static EV_EditMethod_Fn extSelEOW;
	static EV_EditMethod_Fn extSelBOS;
	static EV_EditMethod_Fn extSelEOS;
	static EV_EditMethod_Fn extSelBOB;
	static EV_EditMethod_Fn extSelEOB;
	static EV_EditMethod_Fn extSelBOD;
	static EV_EditMethod_Fn extSelEOD;
	static EV_EditMethod_Fn extSelPrevLine;
	static EV_EditMethod_Fn extSelNextLine;
	static EV_EditMethod_Fn extSelPageDown;
	static EV_EditMethod_Fn extSelPageUp;
	static EV_EditMethod_Fn selectAll;
	static EV_EditMethod_Fn selectWord;
	static EV_EditMethod_Fn selectLine;
	static EV_EditMethod_Fn selectBlock;
	
	static EV_EditMethod_Fn singleClick;
	static EV_EditMethod_Fn doubleClick;
	
	static EV_EditMethod_Fn delLeft;
	static EV_EditMethod_Fn delRight;
	static EV_EditMethod_Fn delBOL;
	static EV_EditMethod_Fn delEOL;
	static EV_EditMethod_Fn delBOW;
	static EV_EditMethod_Fn delEOW;
	static EV_EditMethod_Fn delBOS;
	static EV_EditMethod_Fn delEOS;
	static EV_EditMethod_Fn delBOB;
	static EV_EditMethod_Fn delEOB;
	static EV_EditMethod_Fn delBOD;
	static EV_EditMethod_Fn delEOD;

	static EV_EditMethod_Fn insertData;
	static EV_EditMethod_Fn insertTab;
	static EV_EditMethod_Fn insertSoftBreak;
	static EV_EditMethod_Fn insertParagraphBreak;
	static EV_EditMethod_Fn insertLineBreak;
	static EV_EditMethod_Fn insertPageBreak;
	static EV_EditMethod_Fn insertColumnBreak;
	static EV_EditMethod_Fn insFmtBold;
	static EV_EditMethod_Fn insFmtItalic;
	static EV_EditMethod_Fn insFmtUline;
	static EV_EditMethod_Fn insFmtStrike;

	static EV_EditMethod_Fn insFmtFaceTimes; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtFaceCourier; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtFaceArial; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize08; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize10; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize12; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize14; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize16; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize24; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtSize36; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtColorBlack; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtColorRed; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtColorGreen; // TODO we need a better way of doing this
	static EV_EditMethod_Fn insFmtColorBlue; // TODO we need a better way of doing this

	// TODO add functions for all of the standard menu commands.
	// TODO here are a few that i started.

	static EV_EditMethod_Fn fileNew;
	static EV_EditMethod_Fn fileOpen;
	static EV_EditMethod_Fn fileSave;
	static EV_EditMethod_Fn fileSaveAs;
	static EV_EditMethod_Fn print;

	static EV_EditMethod_Fn undo;
	static EV_EditMethod_Fn redo;
	static EV_EditMethod_Fn cut;
	static EV_EditMethod_Fn copy;
	static EV_EditMethod_Fn paste;

	static EV_EditMethod_Fn toggleBold;
	static EV_EditMethod_Fn toggleItalic;
	static EV_EditMethod_Fn toggleUline;
	static EV_EditMethod_Fn toggleStrike;

	static EV_EditMethod_Fn alignLeft;
	static EV_EditMethod_Fn alignCenter;
	static EV_EditMethod_Fn alignRight;
	static EV_EditMethod_Fn alignJustify;

	static EV_EditMethod_Fn cycleWindows;
	static EV_EditMethod_Fn cycleWindowsBck;
	static EV_EditMethod_Fn closeWindow;
	static EV_EditMethod_Fn querySaveAndExit;

	// Test routines
	
	static EV_EditMethod_Fn Test_Dump;
};

/*****************************************************************/
/*****************************************************************/

#define _D_				EV_EMT_REQUIREDATA
#define _M_				EV_EMT_ALLOWMULTIPLIER
#define _DM_			EV_EMT_REQUIREDATA | EV_EMT_ALLOWMULTIPLIER

#define F(fn)			ap_EditMethods::fn
#define N(fn)			#fn
#define NF(fn)			N(fn), F(fn)

static EV_EditMethod s_arrayEditMethods[] = 
	{
		EV_EditMethod(NF(scrollPageDown),		_M_,	""),
		EV_EditMethod(NF(scrollPageUp),			_M_,	""),
		EV_EditMethod(NF(scrollPageLeft),		_M_,	""),
		EV_EditMethod(NF(scrollPageRight),		_M_,	""),
		EV_EditMethod(NF(scrollLineDown),		_M_,	""),
		EV_EditMethod(NF(scrollLineUp),			_M_,	""),
		EV_EditMethod(NF(scrollLineLeft),		_M_,	""),
		EV_EditMethod(NF(scrollLineRight),		_M_,	""),
		EV_EditMethod(NF(scrollToTop),			_M_,	""),
		EV_EditMethod(NF(scrollToBottom),		_M_,	""),

		EV_EditMethod(NF(warpInsPtToXY),		_M_,	""),
		EV_EditMethod(NF(warpInsPtLeft),		_M_,	""),
		EV_EditMethod(NF(warpInsPtRight),		_M_,	""),
		EV_EditMethod(NF(warpInsPtBOL),			_M_,	""),
		EV_EditMethod(NF(warpInsPtEOL),			_M_,	""),
		EV_EditMethod(NF(warpInsPtBOW),			_M_,	""),
		EV_EditMethod(NF(warpInsPtEOW),			_M_,	""),
		EV_EditMethod(NF(warpInsPtBOS),			_M_,	""),
		EV_EditMethod(NF(warpInsPtEOS),			_M_,	""),
		EV_EditMethod(NF(warpInsPtBOB),			_M_,	""),
		EV_EditMethod(NF(warpInsPtEOB),			_M_,	""),
		EV_EditMethod(NF(warpInsPtBOD),			_M_,	""),
		EV_EditMethod(NF(warpInsPtEOD),			_M_,	""),
		EV_EditMethod(NF(warpInsPtPrevLine),	_M_,	""),
		EV_EditMethod(NF(warpInsPtNextLine),	_M_,	""),

		EV_EditMethod(NF(extSelToXY),			_M_,	""),
		EV_EditMethod(NF(extSelLeft),			_M_,	""),
		EV_EditMethod(NF(extSelRight),			_M_,	""),
		EV_EditMethod(NF(extSelBOL),			_M_,	""),
		EV_EditMethod(NF(extSelEOL),			_M_,	""),
		EV_EditMethod(NF(extSelBOW),			_M_,	""),
		EV_EditMethod(NF(extSelEOW),			_M_,	""),
		EV_EditMethod(NF(extSelBOS),			_M_,	""),
		EV_EditMethod(NF(extSelEOS),			_M_,	""),
		EV_EditMethod(NF(extSelBOB),			_M_,	""),
		EV_EditMethod(NF(extSelEOB),			_M_,	""),
		EV_EditMethod(NF(extSelBOD),			_M_,	""),
		EV_EditMethod(NF(extSelEOD),			_M_,	""),
		EV_EditMethod(NF(extSelPrevLine),		_M_,	""),
		EV_EditMethod(NF(extSelNextLine),		_M_,	""),
		EV_EditMethod(NF(extSelPageDown),		_M_,	""),
		EV_EditMethod(NF(extSelPageUp),			_M_,	""),
		EV_EditMethod(NF(selectAll),			_M_,	""),
		EV_EditMethod(NF(selectWord),			_M_,	""),
		EV_EditMethod(NF(selectLine),			_M_,	""),
		EV_EditMethod(NF(selectBlock),			_M_,	""),

		EV_EditMethod(NF(singleClick),			_M_,	""),
		EV_EditMethod(NF(doubleClick),			_M_,	""),

		EV_EditMethod(NF(delLeft),				_M_,	""),
		EV_EditMethod(NF(delRight),				_M_,	""),
		EV_EditMethod(NF(delBOL),				_M_,	""),
		EV_EditMethod(NF(delEOL),				_M_,	""),
		EV_EditMethod(NF(delBOW),				_M_,	""),
		EV_EditMethod(NF(delEOW),				_M_,	""),
		EV_EditMethod(NF(delBOS),				_M_,	""),
		EV_EditMethod(NF(delEOS),				_M_,	""),
		EV_EditMethod(NF(delBOB),				_M_,	""),
		EV_EditMethod(NF(delEOB),				_M_,	""),
		EV_EditMethod(NF(delBOD),				_M_,	""),
		EV_EditMethod(NF(delEOD),				_M_,	""),

		EV_EditMethod(NF(insertData),			_DM_,	""),
		EV_EditMethod(NF(insertTab),			_M_,	""),
		EV_EditMethod(NF(insertSoftBreak),		_M_,	""),
		EV_EditMethod(NF(insertParagraphBreak),	_M_,	""),
		EV_EditMethod(NF(insertLineBreak),		_M_,	""),
		EV_EditMethod(NF(insertPageBreak),		_M_,	""),
		EV_EditMethod(NF(insertColumnBreak),	_M_,	""),
		EV_EditMethod(NF(insFmtBold),			_M_,	""),
		EV_EditMethod(NF(insFmtItalic),			_M_,	""),
		EV_EditMethod(NF(insFmtUline),			_M_,	""),
		EV_EditMethod(NF(insFmtStrike),			_M_,	""),

		EV_EditMethod(NF(insFmtFaceTimes),		_M_,	""),
		EV_EditMethod(NF(insFmtFaceCourier),	_M_,	""),
		EV_EditMethod(NF(insFmtFaceArial),		_M_,	""),
		EV_EditMethod(NF(insFmtSize08),			_M_,	""),
		EV_EditMethod(NF(insFmtSize10),			_M_,	""),
		EV_EditMethod(NF(insFmtSize12),			_M_,	""),
		EV_EditMethod(NF(insFmtSize14),			_M_,	""),
		EV_EditMethod(NF(insFmtSize16),			_M_,	""),
		EV_EditMethod(NF(insFmtSize24),			_M_,	""),
		EV_EditMethod(NF(insFmtSize36),			_M_,	""),
		EV_EditMethod(NF(insFmtColorBlack),		_M_,	""),
		EV_EditMethod(NF(insFmtColorRed),		_M_,	""),
		EV_EditMethod(NF(insFmtColorGreen),		_M_,	""),
		EV_EditMethod(NF(insFmtColorBlue),		_M_,	""),

		EV_EditMethod(NF(fileNew),				_M_,	""),
		EV_EditMethod(NF(fileOpen),				_M_,	""),
		EV_EditMethod(NF(fileSave),				_M_,	""),
		EV_EditMethod(NF(fileSaveAs),			_M_,	""),
		EV_EditMethod(NF(print),				_M_,	""),

		EV_EditMethod(NF(undo),					_M_,	""),
		EV_EditMethod(NF(redo),					_M_,	""),
		EV_EditMethod(NF(cut),					_M_,	""),
		EV_EditMethod(NF(copy),					_M_,	""),
		EV_EditMethod(NF(paste),				_M_,	""),

		EV_EditMethod(NF(toggleBold),			0,		""),
		EV_EditMethod(NF(toggleItalic),			0,		""),
		EV_EditMethod(NF(toggleUline),			0,		""),
		EV_EditMethod(NF(toggleStrike),			0,		""),

		EV_EditMethod(NF(alignLeft),			0,		""),
		EV_EditMethod(NF(alignCenter),			0,		""),
		EV_EditMethod(NF(alignRight),			0,		""),
		EV_EditMethod(NF(alignJustify),			0,		""),

		EV_EditMethod(NF(cycleWindows),			_M_,	""),
		EV_EditMethod(NF(cycleWindowsBck),		_M_,	""),
		EV_EditMethod(NF(closeWindow),			_M_,	""),
		EV_EditMethod(NF(querySaveAndExit),		_M_,	""),
		
		EV_EditMethod(NF(Test_Dump),			_M_,	"")
	};

#define NrElements(a)	((sizeof(a)/sizeof(a[0])))


EV_EditMethodContainer * AP_GetEditMethods(void)
{
	// Construct a container for all of the methods this application
	// knows about.
	
	return new EV_EditMethodContainer(NrElements(s_arrayEditMethods),s_arrayEditMethods);
}

#undef _D_
#undef _M_
#undef _DM_
#undef F
#undef N
#undef NF

/*****************************************************************/
/*****************************************************************/

#define F(fn)		ap_EditMethods::fn
#define Defun(fn)	UT_Bool F(fn)(FV_View* pView, EV_EditMethodCallData * pCallData)
#define EX(fn)		F(fn)(pView, pCallData)


Defun(scrollPageDown)
{
	pView->cmdScroll(DG_SCROLLCMD_PAGEDOWN);
	
	return UT_TRUE;
}

Defun(scrollPageUp)
{
	pView->cmdScroll(DG_SCROLLCMD_PAGEUP);
	
	return UT_TRUE;
}

Defun(scrollPageLeft)
{
	pView->cmdScroll(DG_SCROLLCMD_PAGELEFT);
	
	return UT_TRUE;
}

Defun(scrollPageRight)
{
	pView->cmdScroll(DG_SCROLLCMD_PAGERIGHT);
	
	return UT_TRUE;
}

Defun(scrollLineDown)
{
	pView->cmdScroll(DG_SCROLLCMD_LINEDOWN);
	
	return UT_TRUE;
}

Defun(scrollLineUp)
{
	pView->cmdScroll(DG_SCROLLCMD_LINEUP);
	
	return UT_TRUE;
}

Defun(scrollLineLeft)
{
	pView->cmdScroll(DG_SCROLLCMD_LINELEFT);
	
	return UT_TRUE;
}

Defun(scrollLineRight)
{
	pView->cmdScroll(DG_SCROLLCMD_LINERIGHT);
	
	return UT_TRUE;
}

Defun(scrollToTop)
{
	pView->cmdScroll(DG_SCROLLCMD_TOTOP);
	
	return UT_TRUE;
}

Defun(scrollToBottom)
{
	pView->cmdScroll(DG_SCROLLCMD_TOBOTTOM);
	
	return UT_TRUE;
}

Defun(singleClick)
{
	UT_Bool bRes = UT_TRUE;

	// NOTE: context-free binding mechanism ==> we need this extra layer
	if (pView->isLeftMargin(pCallData->m_xPos, pCallData->m_yPos))
		bRes = EX(selectLine);
	else
		bRes = EX(warpInsPtToXY);
	
	return bRes;
}

Defun(doubleClick)
{
	UT_Bool bRes = UT_TRUE;

	// NOTE: context-free binding mechanism ==> we need this extra layer
	if (pView->isLeftMargin(pCallData->m_xPos, pCallData->m_yPos))
		bRes = EX(selectBlock);
	else
		bRes = EX(selectWord);
	
	return bRes;
}

Defun(warpInsPtToXY)
{
	pView->warpInsPtToXY(pCallData->m_xPos, pCallData->m_yPos);
	
	return UT_TRUE;
}

Defun(warpInsPtLeft)
{
	pView->cmdCharMotion(UT_FALSE,1);
	return UT_TRUE;
}

Defun(warpInsPtRight)
{
	pView->cmdCharMotion(UT_TRUE,1);
	return UT_TRUE;
}

Defun(warpInsPtBOL)
{
	pView->moveInsPtTo(FV_DOCPOS_BOL);
	return UT_TRUE;
}

Defun(warpInsPtEOL)
{
	pView->moveInsPtTo(FV_DOCPOS_EOL);
	return UT_TRUE;
}

Defun(warpInsPtBOW)
{
	pView->moveInsPtTo(FV_DOCPOS_BOW);
	return UT_TRUE;
}

Defun(warpInsPtEOW)
{
	pView->moveInsPtTo(FV_DOCPOS_EOW);
	return UT_TRUE;
}

Defun(warpInsPtBOS)
{
	return UT_TRUE;
}

Defun(warpInsPtEOS)
{
	return UT_TRUE;
}

Defun(warpInsPtBOB)
{
	pView->moveInsPtTo(FV_DOCPOS_BOB);
	return UT_TRUE;
}

Defun(warpInsPtEOB)
{
	pView->moveInsPtTo(FV_DOCPOS_EOB);
	return UT_TRUE;
}

Defun(warpInsPtBOD)
{
	pView->moveInsPtTo(FV_DOCPOS_BOD);
	return UT_TRUE;
}

Defun(warpInsPtEOD)
{
	pView->moveInsPtTo(FV_DOCPOS_EOD);
	return UT_TRUE;
}

Defun(warpInsPtPrevLine)
{
	pView->warpInsPtNextPrevLine(UT_FALSE);

	return UT_TRUE;
}

Defun(warpInsPtNextLine)
{
	pView->warpInsPtNextPrevLine(UT_TRUE);

	return UT_TRUE;
}

Defun(extSelToXY)
{
	pView->extSelToXY(pCallData->m_xPos, pCallData->m_yPos);
	return UT_TRUE;
}
Defun(extSelLeft)
{
	pView->extSelHorizontal(UT_FALSE,1);
	return UT_TRUE;
}

Defun(extSelRight)
{
	pView->extSelHorizontal(UT_TRUE,1);
	return UT_TRUE;
}

Defun(extSelBOL)
{
	pView->extSelTo(FV_DOCPOS_BOL);
	return UT_TRUE;
}

Defun(extSelEOL)
{
	pView->extSelTo(FV_DOCPOS_EOL);
	return UT_TRUE;
}

Defun(extSelBOW)
{
	pView->extSelTo(FV_DOCPOS_BOW);
	return UT_TRUE;
}

Defun(extSelEOW)
{
	pView->extSelTo(FV_DOCPOS_EOW);
	return UT_TRUE;
}

Defun(extSelBOS)
{
	return UT_TRUE;
}

Defun(extSelEOS)
{
	return UT_TRUE;
}

Defun(extSelBOB)
{
	pView->extSelTo(FV_DOCPOS_BOB);
	return UT_TRUE;
}

Defun(extSelEOB)
{
	pView->extSelTo(FV_DOCPOS_EOB);
	return UT_TRUE;
}

Defun(extSelBOD)
{
	pView->extSelTo(FV_DOCPOS_BOD);
	return UT_TRUE;
}

Defun(extSelEOD)
{
	pView->extSelTo(FV_DOCPOS_EOD);
	return UT_TRUE;
}

Defun(extSelPrevLine)
{
	pView->extSelNextPrevLine(UT_FALSE);
	
	return UT_TRUE;
}

Defun(extSelNextLine)
{
	pView->extSelNextPrevLine(UT_TRUE);
	
	return UT_TRUE;
}

Defun(extSelPageDown)
{
	return UT_TRUE;
}

Defun(extSelPageUp)
{
	return UT_TRUE;
}

Defun(selectAll)
{
	pView->moveInsPtTo(FV_DOCPOS_BOD);
	pView->extSelTo(FV_DOCPOS_EOD);
	return UT_TRUE;
}

Defun(selectWord)
{
	pView->cmdSelect(pCallData->m_xPos, pCallData->m_yPos, FV_DOCPOS_BOW, FV_DOCPOS_EOW);
	return UT_TRUE;
}

Defun(selectLine)
{
	pView->cmdSelect(pCallData->m_xPos, pCallData->m_yPos, FV_DOCPOS_BOL, FV_DOCPOS_EOL);
	return UT_TRUE;
}

Defun(selectBlock)
{
	pView->cmdSelect(pCallData->m_xPos, pCallData->m_yPos, FV_DOCPOS_BOB, FV_DOCPOS_EOB);
	return UT_TRUE;
}

Defun(delLeft)
{
	pView->cmdCharDelete(UT_FALSE,1);
	return UT_TRUE;
}

Defun(delRight)
{
	pView->cmdCharDelete(UT_TRUE,1);
	return UT_TRUE;
}

Defun(delBOL)
{
	pView->delTo(FV_DOCPOS_BOL);
	return UT_TRUE;
}

Defun(delEOL)
{
	pView->delTo(FV_DOCPOS_EOL);
	return UT_TRUE;
}

Defun(delBOW)
{
	pView->delTo(FV_DOCPOS_BOW);
	return UT_TRUE;
}

Defun(delEOW)
{
	pView->delTo(FV_DOCPOS_EOW);
	return UT_TRUE;
}

Defun(delBOS)
{
	return UT_TRUE;
}

Defun(delEOS)
{
	return UT_TRUE;
}

Defun(delBOB)
{
	pView->delTo(FV_DOCPOS_BOB);
	return UT_TRUE;
}

Defun(delEOB)
{
	pView->delTo(FV_DOCPOS_EOB);
	return UT_TRUE;
}

Defun(delBOD)
{
	pView->delTo(FV_DOCPOS_BOD);
	return UT_TRUE;
}

Defun(delEOD)
{
	pView->delTo(FV_DOCPOS_EOD);
	return UT_TRUE;
}

Defun(insertData)
{
	pView->cmdCharInsert(pCallData->m_pData,pCallData->m_dataLength);
	return UT_TRUE;
}

Defun(insertTab)
{
	return UT_TRUE;
}

Defun(insertSoftBreak)
{
	return UT_TRUE;
}

Defun(insertParagraphBreak)
{
	pView->insertParagraphBreak();
	
	return UT_TRUE;
}

Defun(insertLineBreak)
{
	return UT_TRUE;
}

Defun(insertPageBreak)
{
	return UT_TRUE;
}

Defun(insertColumnBreak)
{
	return UT_TRUE;
}

Defun(insFmtBold)
{
	const XML_Char * properties[] =	{ "font-weight", "bold", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtItalic)
{
	const XML_Char * properties[] =	{ "font-style", "italic", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtUline)
{
	const XML_Char * properties[] =	{ "text-decoration", "underline", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtStrike)
{
	const XML_Char * properties[] =	{ "text-decoration", "line-through", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}

Defun(insFmtFaceTimes)
{
	const XML_Char * properties[] =	{ "font-family", "Times New Roman", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtFaceCourier)
{
	const XML_Char * properties[] =	{ "font-family", "Courier New", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtFaceArial)
{
	const XML_Char * properties[] =	{ "font-family", "Arial", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize08)
{
	const XML_Char * properties[] =	{ "font-size", "8pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize10)
{
	const XML_Char * properties[] =	{ "font-size", "10pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize12)
{
	const XML_Char * properties[] =	{ "font-size", "12pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize14)
{
	const XML_Char * properties[] =	{ "font-size", "14pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize16)
{
	const XML_Char * properties[] =	{ "font-size", "16pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize24)
{
	const XML_Char * properties[] =	{ "font-size", "24pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtSize36)
{
	const XML_Char * properties[] =	{ "font-size", "36pt", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}

Defun(insFmtColorBlack)
{
	const XML_Char * properties[] =	{ "color", "000000", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtColorRed)
{
	const XML_Char * properties[] =	{ "color", "ff0000", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtColorGreen)
{
	const XML_Char * properties[] =	{ "color", "00ff00", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}
Defun(insFmtColorBlue)
{
	const XML_Char * properties[] =	{ "color", "0000ff", 0};
	pView->insertCharacterFormatting(properties);
	return UT_TRUE;
}

Defun(fileNew)
{
	return UT_TRUE;
}

Defun(fileOpen)
{
	return UT_TRUE;
}

Defun(fileSave)
{
	pView->cmdSave();
	return UT_TRUE;
}

Defun(fileSaveAs)
{
	return UT_TRUE;
}

Defun(print)
{
	return UT_TRUE;
}

Defun(undo)
{
	pView->cmdUndo(1);
	return UT_TRUE;
}

Defun(redo)
{
	pView->cmdRedo(1);
	return UT_TRUE;
}

Defun(cut)
{
	return UT_TRUE;
}

Defun(copy)
{
	return UT_TRUE;
}

Defun(paste)
{
	return UT_TRUE;
}

Defun(cycleWindows)
{
	return UT_TRUE;
}

Defun(cycleWindowsBck)
{
	return UT_TRUE;
}

Defun(closeWindow)
{
	return UT_TRUE;
}

Defun(querySaveAndExit)
{
	return UT_TRUE;
}

// HACK: for now, map toggle* onto insFmt*
// TODO: implement toggle semantics directly
Defun(toggleBold)
{
	return EX(insFmtBold);
}

Defun(toggleItalic)
{
	return EX(insFmtItalic);
}

Defun(toggleUline)
{
	return EX(insFmtUline);
}

Defun(toggleStrike)
{
	return EX(insFmtStrike);
}

Defun(alignLeft)
{
	const XML_Char * properties[] =	{ "text-align", "left", 0};
	pView->cmdFormatBlock(properties);
	return UT_TRUE;
}

Defun(alignCenter)
{
	const XML_Char * properties[] =	{ "text-align", "center", 0};
	pView->cmdFormatBlock(properties);
	return UT_TRUE;
}

Defun(alignRight)
{
	const XML_Char * properties[] =	{ "text-align", "right", 0};
	pView->cmdFormatBlock(properties);
	return UT_TRUE;
}

Defun(alignJustify)
{
	const XML_Char * properties[] =	{ "text-align", "justify", 0};
	pView->cmdFormatBlock(properties);
	return UT_TRUE;
}

Defun(Test_Dump)
{
	pView->Test_Dump();
	return UT_TRUE;
}

/*****************************************************************/
/*****************************************************************/

#ifdef DLGHACK

/*
	Having these platform-specific IFDEFs here is a gruesome HACK.
	The only excuse is that it makes things easier while we figure 
	out a better scheme for calling platform-specific dialogs from 
	XP code.
*/

/*****************************************************************/
/*****************************************************************/

#ifdef WIN32

#if FRAGMENT
{
		case RES_MENU_ITEM_NEW:
			_newFile(hwnd, pG);

			return 0;

		case RES_MENU_ITEM_OPEN:
			_showFile(_promptFile(hwnd, UT_FALSE), hwnd, pG);

			return 0;

#if 0 // TODO: bind save/saveas to exporters when ready
		case RES_MENU_ITEM_SAVE:
			{
				char * pFileName = pDocLayout->getDocument()->getFilename();

				if (pFileName)
				{
					RW_DocWriter dw(pDocLayout->getDocument());
					dw.writeFile(pFileName);
					return 0;
				}
				// fall through
			}

		case RES_MENU_ITEM_SAVEAS:
			{
				char * pNewFile = _promptFile(hwnd, UT_TRUE);

				if (pNewFile)
				{
					RW_DocWriter dw(pDocLayout->getDocument());
					dw.writeFile(pNewFile);
				}
				return 0;
			}
#endif
			
		case RES_MENU_ITEM_PRINT:
			_printDoc(hwnd);
			break;
		}
}
#endif /* FRAGMENT */

char * _promptFile(HWND hwnd, UT_Bool bSaveAs)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename

	szFile[0] = 0;

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST;

	// display the appropriate dialog box. 
	if (bSaveAs)
	{
		if (GetSaveFileName(&ofn)==TRUE) 
			return strdup(szFile);
	}
	else
	{
		ofn.Flags |= OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn)==TRUE) 
			return strdup(szFile);
	}

	DWORD err = CommDlgExtendedError();
	UT_DEBUGMSG(("Didn't get a file: reason=0x%x\n", err));
	UT_ASSERT(!err);

	return NULL;
}

UT_Bool _showFile(char *fileName, HWND hwnd, DG_Graphics *pG)
{
	if (!fileName)
		return UT_FALSE;

	PD_Document * doc = new PD_Document();

	if (!doc->readFromFile(fileName))
	{
		// HACK: for now, keep going
		UT_DEBUGMSG(("_showFile -- falling back to new file\n"));
		doc->newDocument();
	}

	if (fileName)
		free(fileName);

//	return _showDoc(hwnd, pG);
	return UT_FALSE;
} 

UT_Bool _newFile(HWND hwnd, DG_Graphics *pG)
{
	PD_Document * doc = new PD_Document();
	doc->newDocument();

//	return _showDoc(hwnd, pG);
	return UT_FALSE;
} 

UT_Bool _printDoc(HWND hwnd)
{
	PRINTDLG pd;
	DOCINFO di;

	memset(&pd, 0, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner = hwnd;
	pd.Flags = PD_RETURNDC | PD_NOSELECTION | PD_PAGENUMS;

	if(!PrintDlg(&pd))
		return UT_FALSE;

	PD_Document * doc;	// HACK to fake out compiler. otherwise useless

	const char* pname = doc->getFilename();

	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = pname;
	di.lpszOutput = NULL;
	Win32Graphics* ppG = new Win32Graphics(pd.hDC, &di);

	FL_DocLayout* pDL = new FL_DocLayout(doc, ppG);
	pDL->formatAll();
			
	UT_uint32 iHeight = pDL->getHeight();
	FV_View* pV = new FV_View(pDL);

	dg_DrawArgs da;
	da.pG = NULL;
	da.width = pDL->getWidth();
	da.height = pDL->getHeight();

	ppG->startPrint();
	
//TODO allow page ranges
	int nPages = pDL->countPages();
	for(int i = 0; i < nPages; i++)
	{
		ppG->startPage(doc->getFilename(), i, TRUE, da.width,da.height);
		pV->draw(i, &da);
	}
	ppG->endPrint();

	// clean up
	delete ppG;
	// these next 2 cause some asserts...do I need to do these?
	//	delete pDL;
	//	delete pV;
	DeleteDC(pd.hDC);
	// free any memory allocated by StartDoc
	if(pd.hDevMode != NULL)
		GlobalFree(pd.hDevMode);
	if(pd.hDevNames != NULL)
		GlobalFree(pd.hDevNames);

return UT_TRUE;
}

#endif /* WIN32 */


/*****************************************************************/
/*****************************************************************/

#ifdef UNIX

#if FRAGMENT
{
	case MENU_FILE_EXIT:
		exit(0);
		break;
		
	case MENU_FILE_NEW:
		doc = new PD_Document();
		doc->newDocument();
		showDoc();
		break;
		
	case MENU_FILE_OPEN:
		fileDialogOp = which;
		openNewDoc();
		break;

#if 0 // TODO: bind save/saveas to exporters when ready
	case MENU_FILE_SAVE:
		if (!pFileName)
			break;
		
		saveFile(pFileName);
		break;

	case MENU_FILE_SAVEAS:
		fileDialogOp = which;
		openNewDoc();
		break;
#endif
}
#endif /* FRAGMENT */

void fileSelection(GtkWidget* pDlg, GtkFileSelection *pFS)
{
	char *fileName;
	fileName = gtk_file_selection_get_filename(GTK_FILE_SELECTION(pFS));
	
	if (fileDialogOp == MENU_FILE_OPEN)
	{
		pFileName = new char[strlen(fileName) + 1];
		strcpy(pFileName, fileName);
		openFile(pFileName);
	}
	else
	{	
		saveFile(fileName);
	}

	gtk_widget_destroy (GTK_WIDGET(pFS));
}

void openNewDoc(void)
{
	GtkWidget* pFileDlg;
	
	if (fileDialogOp == MENU_FILE_SAVE)
		pFileDlg = gtk_file_selection_new("Open file");
	else
		pFileDlg = gtk_file_selection_new("Save file");

	gtk_widget_show(pFileDlg);

	gtk_file_selection_hide_fileop_buttons (GTK_FILE_SELECTION(pFileDlg));

	gtk_signal_connect(GTK_OBJECT(pFileDlg), "destroy",
					   GTK_SIGNAL_FUNC(gtk_widget_destroyed),
					   &pFileDlg);

	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION (pFileDlg)->ok_button),
					   "clicked", GTK_SIGNAL_FUNC(fileSelection),
					   pFileDlg);
	
	gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION(pFileDlg)->cancel_button),
							  "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy),
							  GTK_OBJECT (pFileDlg));
}	

void saveFile(char* fileName)
{
#if 0 // TODO: bind save/saveas to exporters when ready
	RW_DocWriter dw(pLayout->getDocument());
	dw.writeFile(fileName);
#endif
}

void openFile(char* fileName)
{
	doc = new PD_Document();

	if (!doc)
		return;

	if (!doc->readFromFile(fileName))
	{
		// HACK: for now, keep going
		UT_DEBUGMSG(("_showFile -- falling back to new file\n"));
		doc->newDocument();
	}
  
	pFileName = fileName;

	showDoc();
}

#endif /* UNIX */

/*****************************************************************/
/*****************************************************************/

#endif /* DLGHACK */
