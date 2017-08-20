/*=========================================================================
 *    �ļ�����:     Hook.cpp
 *    ժ    Ҫ:  
 *    ��ǰ�汾:
 *    ��    ��:  
 *    ��������:	    2013�� 1�� 8��  21:46
 *    �޸���ʷ:
/*=======================================================================*/

#include "Hook.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHook::CHook( DWORD dwFuncEntryRVA, const BYTE* pCode, DWORD dwCodeSize  )
{
    m_dwFuncEntryRVA = dwFuncEntryRVA;
    memcpy( m_aryCode, pCode, dwCodeSize );
    m_dwCodeSize = dwCodeSize;
}

CHook::~CHook()
{
}

// �ض�λ
void CHook::Rebase( HMODULE hModule )
{
    m_dwFuncEntryAddr = (DWORD)hModule + m_dwFuncEntryRVA;
    m_dwBackAddr = m_dwFuncEntryAddr + sizeof(tagJmpIns);
    m_dwMuduleBase = (DWORD)hModule;
}


// �ж��Ƿ����Hook
BOOL CHook::IsCanHook()
{
    if ( memcmp( (LPVOID)m_dwFuncEntryAddr, (LPVOID)m_aryCode, m_dwCodeSize ) == 0 )
    {
        return TRUE;
    }
    else
    {        
        return FALSE;
    }
}


// ����Hook
BOOL CHook::SetHook( PHookFun pHookFun )
{    
    BOOL bRet = FALSE;
    DWORD dwOld = 0;

    if ( IsCanHook() )
    {
        tagJmpIns JmpIns;
        JmpIns.m_dwOffset = (DWORD)pHookFun - m_dwFuncEntryAddr - sizeof(JmpIns);

        // �޸��ڴ�����
        VirtualProtect((LPVOID)m_dwFuncEntryAddr, 0x1000, PAGE_EXECUTE_READWRITE, &dwOld);   
        
        memcpy((void*)m_dwFuncEntryAddr, &JmpIns, sizeof(JmpIns) );
        // ��ԭ�ڴ�����
        VirtualProtect((LPVOID)m_dwFuncEntryAddr, 0x1000, dwOld, &dwOld);
        
        bRet = TRUE;
    }

    return bRet;
}



// ����Hook
BOOL CHook::UnSetHook()
{
    return TRUE;
}
