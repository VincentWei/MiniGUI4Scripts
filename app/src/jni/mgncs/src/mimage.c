
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "mgncsconfig.h"
#include "mcommon.h"
#include "mobject.h"
#include "mcomponent.h"
#include "mwidget.h"
#include "mstatic.h"
#include "mimage.h"
#include "mrdr.h"
#include "piece.h"

static mObject* mImage_createBody(mImage *self)
{
	return (mObject*)NEWPIECE(mImagePiece);
}

#if 0
static void free_image(mImage *self)
{
	if(self->autoFree && self->pbmp)
	{
        UnloadBitmap(self->pbmp);
        free(self->pbmp);
	}
	self->autoFree = 0;
	self->pbmp = NULL;
}
#endif

#if 0
static void mImage_onPaint(mImage *self, HDC hdc, const PCLIPRGN pinv_clip)
{
    RECT rc;

/*	if(self->pbmp == NULL)
		return;
  */  
    GetClientRect (self->hwnd, &rc);
	
	/*ncsDrawImage(hdc, self->pbmp, &rc, self->drawMode);*/

	DWORD bkcolor;
	gal_pixel old;
	bkcolor = GetWindowBkColor(self->hwnd);

	old = SetBrushColor(hdc, bkcolor/*ncsColor2Pixel(hdct, bkcolor)*/);
	FillBox(hdc, rc.left, rc.top, RECTW(rc), RECTH(rc));

	ncsImageDrawInfoDraw(&self->bkimg, hdc, &rc, self->align, self->valign, NULL);

	SetBrushColor(hdc, old);

}

#define IS_THIS_FILE(file, type)		(strcasecmp(strrchr(file,'.') + 1, type) == 0)
#endif 

#include "iconview_content_data.c"

static BOOL mImage_setProperty(mImage *self, int id, DWORD value)
{
#ifdef _MGNCS_GUIBUILDER_SUPPORT
	if(id == NCSP_DEFAULT_CONTENT)
	{
		if(Body)
		{
			PBITMAP pbmp;

			pbmp = get_iconview_content();

			SetBodyProp(NCSP_IMAGEPIECE_IMAGE, (DWORD)pbmp);
			SetBodyProp(NCSP_IMAGEPIECE_ALIGN, 2);
			SetBodyProp(NCSP_IMAGEPIECE_VALIGN, 2);
		}
		InvalidateRect(self->hwnd, NULL, TRUE);
		return TRUE;
	}
#endif

	if(id >= NCSP_IMAGE_MAX)
		return FALSE;

	switch(id)
	{
	case NCSP_IMAGE_IMAGE:
        {
			if(Body && SetBodyProp(NCSP_IMAGEPIECE_IMAGE, value))
			{
				InvalidateRect(self->hwnd, NULL, TRUE);
				return TRUE;
			}
			return FALSE;
        }
	case NCSP_IMAGE_IMAGEFILE:
		if(Body && SetBodyProp(NCSP_IMAGEPIECE_IMAGEFILE, value))
		{
			InvalidateRect(self->hwnd, NULL, TRUE);
			return TRUE;
		}
		return FALSE;
	case NCSP_IMAGE_DRAWMODE:
		if(Body && SetBodyProp(NCSP_IMAGEPIECE_DRAWMODE, value))
       	{
		   InvalidateRect(self->hwnd, NULL, TRUE);
		   return TRUE;
    	}
		return FALSE;
 	case NCSP_STATIC_ALIGN:
		if(Body && SetBodyProp(NCSP_IMAGEPIECE_ALIGN, value))
		{
			InvalidateRect(self->hwnd, NULL, TRUE);
			return TRUE;
		}
		return FALSE;
	case NCSP_STATIC_VALIGN:
		if(Body&& SetBodyProp(NCSP_IMAGEPIECE_VALIGN, value)){
			InvalidateRect(self->hwnd, NULL, TRUE);
			return TRUE;
		}
		return FALSE;
	}

	return Class(mStatic).setProperty((mStatic*)self, id, value);
}

static DWORD mImage_getProperty(mImage *self, int id)
{
	if(id >= NCSP_IMAGE_MAX)
		return 0;

	switch(id)
    {
       case NCSP_IMAGE_IMAGE:
	   		return Body?GetBodyProp(NCSP_IMAGEPIECE_IMAGE):0;
       case NCSP_IMAGE_DRAWMODE:
	   		return Body?GetBodyProp(NCSP_IMAGEPIECE_DRAWMODE):0;
       case NCSP_STATIC_ALIGN:
			return Body?GetBodyProp(NCSP_IMAGEPIECE_ALIGN):0;
        case NCSP_STATIC_VALIGN:
			return Body?GetBodyProp(NCSP_IMAGEPIECE_VALIGN):0;
    }

	return Class(mStatic).getProperty((mStatic*)self, id);
}

BEGIN_CMPT_CLASS(mImage, mStatic)
	CLASS_METHOD_MAP(mImage, createBody)
	//CLASS_METHOD_MAP(mImage, destroy)
	//CLASS_METHOD_MAP(mImage, onPaint);
	CLASS_METHOD_MAP(mImage, setProperty)
	CLASS_METHOD_MAP(mImage, getProperty)
END_CMPT_CLASS


