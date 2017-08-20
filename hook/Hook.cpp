/*=========================================================================
 *    文件名称:     Hook.cpp
 *    摘    要:  
 *    当前版本:
 *    作    者:  
 *    创建日期:	    2013年 1月 8日  21:46
 *    修改历史:
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

// 重定位
void CHook::Rebase( HMODULE hModule )
{
    m_dwFuncEntryAddr = (DWORD)hModule + m_dwFuncEntryRVA;
    m_dwBackAddr = m_dwFuncEntryAddr + sizeof(tagJmpIns);
    m_dwMuduleBase = (DWORD)hModule;
}


// 判断是否可以Hook
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


// 设置Hook
BOOL CHook::SetHook( PHookFun pHookFun )
{    
    BOOL bRet = FALSE;
    DWORD dwOld = 0;

    if ( IsCanHook() )
    {
        tagJmpIns JmpIns;
        JmpIns.m_dwOffset = (DWORD)pHookFun - m_dwFuncEntryAddr - sizeof(JmpIns);

        // 修改内存属性
        VirtualProtect((LPVOID)m_dwFuncEntryAddr, 0x1000, PAGE_EXECUTE_READWRITE, &dwOld);   
        
        memcpy((void*)m_dwFuncEntryAddr, &JmpIns, sizeof(JmpIns) );
        // 还原内存属性
        VirtualProtect((LPVOID)m_dwFuncEntryAddr, 0x1000, dwOld, &dwOld);
        
        bRet = TRUE;
    }

    return bRet;
}



// 撤销Hook
BOOL CHook::UnSetHook()
{
    return TRUE;
}
