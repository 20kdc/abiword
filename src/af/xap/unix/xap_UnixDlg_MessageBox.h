/* AbiSource Application Framework
 * Copyright (C) 1998 AbiSource, Inc.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

#ifndef XAP_UNIXDIALOG_MESSAGEBOX_H
#define XAP_UNIXDIALOG_MESSAGEBOX_H

#include "xap_UnixFrame.h"
#include "xap_Dlg_MessageBox.h"
#include <glib.h>
class XAP_UnixFrame;

/*****************************************************************/

class XAP_UnixDialog_MessageBox : public XAP_Dialog_MessageBox
{
public:
	XAP_UnixDialog_MessageBox(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~XAP_UnixDialog_MessageBox(void);

	virtual void			runModal(XAP_Frame * pFrame);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);

	// must let static callbacks read our bindings
	UT_Vector * 		_getBindingsVector();
	void 				_setAnswer(XAP_Dialog_MessageBox::tAnswer answer);
		
	// Export for use by s_key_pressed()
   	struct keyBinding
	{
		guint key;
		XAP_Dialog_MessageBox::tAnswer answer;
	};

protected:
	XAP_UnixFrame *			m_pUnixFrame;
	UT_Vector 				m_keyBindings;

	void _bindKey(guint key, XAP_Dialog_MessageBox::tAnswer answer);
	
};

#endif /* XAP_UNIXDIALOG_MESSAGEBOX_H */
