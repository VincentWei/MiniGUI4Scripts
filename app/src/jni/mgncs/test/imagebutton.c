/*
 ** $Id: imagebutton.c 1617 2011-03-24 09:48:44Z shidazhi $
 **
 ** imagebutton.c:
 **
 ** Copyright (C) 2003 ~ 2010 Beijing Feynman Software Technology Co., Ltd.
 **
 ** All rights reserved by Feynman Software.
 **
 ** Current maintainer: dongjunjie
 **
 ** Create date: 2010年12月24日
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <mgncs/mgncs.h>

#if defined _MGNCSCTRL_IMAGEBUTTON && defined _MGNCSCTRL_DIALOGBOX

#define	ID_GROUP	200
#define	ID_BTN1		101
#define	ID_BTN2		102


static BOOL mymain_onRadioChanged(mMainWnd* self, mButtonGroup* sender,
		int event_id, DWORD param)
{
	mWidget* sel =
		(mWidget*)_c(sender)->getProperty(sender, NCSP_BTNGRP_SELOBJ);

	if (sel) {
		MessageBox(self->hwnd,
				(const char*)_c((mWidget*)sel)->getProperty((mWidget*)sel, NCSP_WIDGET_TEXT),
				"Info", 0);
	}

	return TRUE;
}

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
	//TODO : initialize
	//connect
	ncsAddEventListener((mObject*)(_c(self)->getChild(self, ID_GROUP)),
			(mObject*)self, (NCS_CB_ONOBJEVENT)mymain_onRadioChanged,
			NCSN_BTNGRP_SELCHANGED);

	return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}


//Propties for
static NCS_PROP_ENTRY imgebuttonGroup_props[] = {
	{ NCSP_BUTTON_GROUPID, ID_GROUP },
	{ NCSP_IMGBTN_TOOLIMAGEFILE, (DWORD)"./res/toolbar2.png" },
	{ 0, 0 }
};

static NCS_PROP_ENTRY imagebutton_props [] = {
	{ NCSP_IMGBTN_TOOLIMAGEFILE, (DWORD)"./res/toolbar1.png" },
	{ 0, 0 }
};

static NCS_RDR_INFO btn_rdr_info[] = {
	{ "skin", "skin", NULL },
//	{ "fashion","fashion", btn_rdr_elements }
};


//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_IMAGEBUTTON,
		100,
		10, 10, 20, 20,
		WS_VISIBLE | NCSS_BUTTON_AUTOCHECK,
		WS_EX_TRANSPARENT,
		"",
		imagebutton_props, //props,
		btn_rdr_info, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_IMAGEBUTTON,
		100,
		50, 10, 20, 20,
		WS_VISIBLE | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE,
		WS_EX_TRANSPARENT,
		"",
		imagebutton_props, //props,
		btn_rdr_info, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_BUTTONGROUP,
		ID_GROUP,
		5, 50, 300, 180,
		WS_VISIBLE|NCSS_NOTIFY,
		WS_EX_NONE,
		"buttongroup",
		NULL, //props,
		btn_rdr_info, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_IMAGEBUTTON,
		100,
		50, 80, 20, 20,
		WS_VISIBLE | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE,
		WS_EX_TRANSPARENT,
		"image radio 1",
		imgebuttonGroup_props, //props,
		btn_rdr_info, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_IMAGEBUTTON,
		100,
		50, 120, 20, 20,
		WS_VISIBLE | NCSS_BUTTON_AUTOCHECK | NCSS_BUTTON_CHECKABLE,
		WS_EX_TRANSPARENT,
		"image radio 2",
		imgebuttonGroup_props, //props,
		btn_rdr_info, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
	{ MSG_CREATE,mymain_onCreate },
	{ MSG_CLOSE,mymain_onClose },
	{ 0, NULL }
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_DIALOGBOX,
	1,
	0, 0, 320, 320,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
	"Button Test ....",
	NULL,
	NULL,
	mymain_handlers,
	_ctrl_templ,
	sizeof(_ctrl_templ) / sizeof(NCS_WND_TEMPLATE),
	0,
	0xFF0000FF
};

int MiniGUIMain(int argc, const char* argv[])
{
	if (argc > 1) {
		btn_rdr_info[0].glb_rdr = argv[1];
		btn_rdr_info[0].ctl_rdr = argv[1];
	}

	ncsInitialize();

	mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect(
			&mymain_templ, HWND_DESKTOP);

	_c(mydlg)->doModal(mydlg, TRUE);

	ncsUninitialize();

	return 0;
}

#else //_MGNCSCTRL_IMAGEBUTTON _MGNCSCTRL_DIALOGBOX

int main (void)
{
	printf("\n==========================================================\n");
	printf("======== You haven't enable the imagebutton, dialogbox contorl =====\n");
	printf("==========================================================\n");
	printf("============== ./configure --enable-imagebutton --enable-dialogbox ==========\n");
	printf("==========================================================\n\n");
	return 0;
}
#endif	//_MGNCSCTRL_IMAGEBUTTON _MGNCSCTRL_DIALOGBOX

