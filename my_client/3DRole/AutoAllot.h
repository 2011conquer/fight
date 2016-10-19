
//**********************************************************
// ����༭��
//**********************************************************

// AutoAllot.h: interface for the CAutoAlloc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOALLOC_H__D1ACB192_904A_4723_835D_541423CBAEB7__INCLUDED_)
#define AFX_AUTOALLOC_H__D1ACB192_904A_4723_835D_541423CBAEB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

// ��Χ����
typedef struct
{
    DWORD dwForce;
    DWORD dwSpeed;
    DWORD dwHealth;
    DWORD dwSoul;
} FourAttribInfo;

class CAutoAllot
{
public:
    CAutoAllot();
    virtual ~CAutoAllot();
private:
    DWORD			m_dwLevelAmount;				// �ܹ��ж��ٸ��ȼ�
    DWORD			m_dwProfessionalAmount;			// �ܹ��ж��ٸ�ְҵ
    DWORD*			m_pdwProfessionalIndex;			// ְҵ����

private:
    void	BulidIndex();				// ��������

public:
    BOOL	GetAllot(DWORD dwLevel, DWORD dwProfessional, FourAttribInfo& infoAttrib);
};

#endif // !defined(AFX_AUTOALLOC_H__D1ACB192_904A_4723_835D_541423CBAEB7__INCLUDED_)
