/*=========================================================================
 *    文件名称:     GameUpdateHook.cpp
 *    摘    要:  
 *    当前版本:
 *    作    者:  
 *    创建日期:	    2013年 1月 30日  17:56
 *    修改历史:
/*=======================================================================*/

#include "RebaseStartHook.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// 
DWORD g_OldRebaseStartHookNext = 0;


CRebaseStartHook::CRebaseStartHook(DWORD dwFuncEntryRVA, const BYTE* pCode,DWORD dwCodeSize)
:CHook( dwFuncEntryRVA, pCode,dwCodeSize )
{

}

CRebaseStartHook::~CRebaseStartHook()
{

}


//
void NAKED  RebaseStartHook()
{
    STACK_FRAME_BEGIN
      
    OutputDebugString("RebaseStartHook");

    g_bIsRebasing = TRUE;

//     char szLog[512] = {0};
//     sprintf(szLog, "g_bIsRebasing = %d, &g_bIsRebasing = %08X", g_bIsRebasing, &g_bIsRebasing);
//     OutputDebugStringA(szLog);


    STACK_FRAME_END
    
    //_asm    sub     esp, 20h
    //_asm    push    ebx
    //_asm    push    ebp

    _asm    push    g_OldRebaseStartHookNext
    _asm    ret
}



BOOL CRebaseStartHook::SetHook()
{
    g_OldRebaseStartHookNext = m_dwBackAddr + 0x4DB ; 

    return CHook::SetHook( RebaseStartHook );
}
