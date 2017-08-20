
#if !defined(AFX_GAMEUPDATEHOOK_H__3412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_)
#define AFX_GAMEUPDATEHOOK_H__3412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Hook.h"
#include "../collabreate.h"

// CGameUpdateHook¿‡
class CRebaseStartHook : public CHook  
{
public:
	CRebaseStartHook( DWORD dwFuncEntryRVA, const BYTE* pCode,DWORD dwCodeSize );
	virtual ~CRebaseStartHook();
public:
    virtual BOOL SetHook();
};

#endif // !defined(AFX_GAMEUPDATEHOOK_H__43412884_DDDC_4881_8ED3_DC2962C13007__INCLUDED_)
