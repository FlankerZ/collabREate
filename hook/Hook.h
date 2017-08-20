/*=========================================================================
 *    文件名称:     Hook.h
 *    摘    要:     Hook基类
 *    当前版本:
 *    作    者:  
 *    创建日期:     2013年 1月 8日  21:26
 *    修改历史:
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



// Hook函数指针
typedef void (*PHookFun)();

#pragma pack(push,1)
// jmp指令结构体
struct tagJmpIns
{
    tagJmpIns() { m_cJmpOpcode = 0xE9; }
    
    BYTE    m_cJmpOpcode;
    DWORD   m_dwOffset;
};
#pragma pack(pop)


#pragma pack(push,1)
// call指令结构体
struct tagCallIns
{
    tagCallIns() { m_cCallOpcode = 0xE8; }
    
    BYTE    m_cCallOpcode;
    DWORD   m_dwOffset;
};
#pragma pack(pop)

#define NAKED __declspec(naked)

// Hook类
class CHook  
{
public:
    CHook( DWORD dwFuncEntryRVA, const BYTE* pCode, DWORD dwCodeSize = 16 );
    ~CHook();
public:
    // 重定位
    void Rebase( HMODULE hModule );
    // 判断是否可以Hook
    BOOL IsCanHook();       
    // 设置Hook
    virtual BOOL SetHook() = 0;
    // 撤销Hook
    BOOL UnSetHook();
protected:
    // 设置Hook
    BOOL SetHook( PHookFun pHookFun ); 
public:
    DWORD   m_dwFuncEntryRVA;       // 被Hook函数入口相对偏移
    DWORD   m_dwFuncEntryAddr;      // 被Hook函数入口地址
    DWORD   m_dwBackAddr;           // 从Hook函数调回来的地址
    BYTE    m_aryCode[0x10];        // 被Hook函数入口机器码
    DWORD   m_dwCodeSize;           // 入口机器码长度
    DWORD   m_dwMuduleBase;         // 模块基址
};

#endif // !defined(AFX_HOOK_H__1B59A4D0_0F94_4361_B31D_06233EFB457E__INCLUDED_)
