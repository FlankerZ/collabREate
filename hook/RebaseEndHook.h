/*=========================================================================
 *    文件名称:     GameUpdateHook.h
 *    摘    要:     
 *    当前版本:
 *    作    者:  
 *    创建日期:	    2013年 1月 30日  17:56
 *    修改历史:
/*=======================================================================*/

#if !defined(AFX_GAMEUPDATEHOOK_H__412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_)
#define AFX_GAMEUPDATEHOOK_H__412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Hook.h"
#include "../collabreate.h"


// 
class CRebaseEndHook : public CHook  
{
public:
	CRebaseEndHook( DWORD dwFuncEntryRVA, const BYTE* pCode,DWORD dwCodeSize );
	virtual ~CRebaseEndHook();
public:
    virtual BOOL SetHook();
};

#endif // !defined(AFX_GAMEUPDATEHOOK_H__43412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_)
