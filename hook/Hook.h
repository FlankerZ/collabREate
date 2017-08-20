/*=========================================================================
 *    �ļ�����:     Hook.h
 *    ժ    Ҫ:     Hook����
 *    ��ǰ�汾:
 *    ��    ��:  
 *    ��������:     2013�� 1�� 8��  21:26
 *    �޸���ʷ:
/*=======================================================================*/
#if !defined(AFX_HOOK_H__1B59A4D0_0F94_4361_B31D_06233EFB457E__INCLUDED_)
#define AFX_HOOK_H__1B59A4D0_0F94_4361_B31D_06233EFB457E__INCLUDED_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define STACK_FRAME_BEGIN __asm{\
    _asm    push ebp                \
    _asm    mov  ebp,esp            \
    _asm    sub  esp,__LOCAL_SIZE   \
    _asm    pushad                  \
                                }{

#define STACK_FRAME_END }\
    __asm{              \
    _asm    popad       \
    _asm    mov  esp,ebp\
    _asm    pop  ebp    \
                                 }



// Hook����ָ��
typedef void (*PHookFun)();

#pragma pack(push,1)
// jmpָ��ṹ��
struct tagJmpIns
{
    tagJmpIns() { m_cJmpOpcode = 0xE9; }
    
    BYTE    m_cJmpOpcode;
    DWORD   m_dwOffset;
};
#pragma pack(pop)


#pragma pack(push,1)
// callָ��ṹ��
struct tagCallIns
{
    tagCallIns() { m_cCallOpcode = 0xE8; }
    
    BYTE    m_cCallOpcode;
    DWORD   m_dwOffset;
};
#pragma pack(pop)

#define NAKED __declspec(naked)

// Hook��
class CHook  
{
public:
    CHook( DWORD dwFuncEntryRVA, const BYTE* pCode, DWORD dwCodeSize = 16 );
    ~CHook();
public:
    // �ض�λ
    void Rebase( HMODULE hModule );
    // �ж��Ƿ����Hook
    BOOL IsCanHook();       
    // ����Hook
    virtual BOOL SetHook() = 0;
    // ����Hook
    BOOL UnSetHook();
protected:
    // ����Hook
    BOOL SetHook( PHookFun pHookFun ); 
public:
    DWORD   m_dwFuncEntryRVA;       // ��Hook����������ƫ��
    DWORD   m_dwFuncEntryAddr;      // ��Hook������ڵ�ַ
    DWORD   m_dwBackAddr;           // ��Hook�����������ĵ�ַ
    BYTE    m_aryCode[0x10];        // ��Hook������ڻ�����
    DWORD   m_dwCodeSize;           // ��ڻ����볤��
    DWORD   m_dwMuduleBase;         // ģ���ַ
};

#endif // !defined(AFX_HOOK_H__1B59A4D0_0F94_4361_B31D_06233EFB457E__INCLUDED_)
