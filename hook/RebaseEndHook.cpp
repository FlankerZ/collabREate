
#include "RebaseEndHook.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


DWORD g_OldRebaseEndHookNext = 0;


CRebaseEndHook::CRebaseEndHook(DWORD dwFuncEntryRVA, const BYTE* pCode,DWORD dwCodeSize)
:CHook( dwFuncEntryRVA, pCode,dwCodeSize )
{

}

CRebaseEndHook::~CRebaseEndHook()
{

}


//
void NAKED  RebaseEndHook()
{
    STACK_FRAME_BEGIN
      
    OutputDebugString("RebaseEndHook");

    g_bIsRebasing = FALSE;

//     char szLog[512] = {0};
//     sprintf(szLog, "g_bIsRebasing = %d, &g_bIsRebasing = %08X", g_bIsRebasing, &g_bIsRebasing);
//     OutputDebugStringA(szLog);

    STACK_FRAME_END

    _asm    pop     ecx
    _asm    pop     edi
    _asm    pop     esi
    _asm    pop     ebp
    _asm    pop     ebx

    _asm push    g_OldRebaseEndHookNext
    _asm ret
}



BOOL CRebaseEndHook::SetHook()
{
    g_OldRebaseEndHookNext = m_dwBackAddr; 

    return CHook::SetHook( RebaseEndHook );
}
