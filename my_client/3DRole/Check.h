
//**********************************************************
// ����༭��
//**********************************************************

// Check.h: interface for the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECK_H__BD357BB3_6170_4E69_8778_C55BCA1682B8__INCLUDED_)
#define AFX_CHECK_H__BD357BB3_6170_4E69_8778_C55BCA1682B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

class CCheck
{
public:
    enum
    {
        _WS_MAINWINDOW_	= 0x00000001, // ������
    };
    enum
    {
        _TYPE_WS				= 1, // ��˫
        _TYPE_FY				= 2, // ����
        _TYPE_USE_LIFE_MEDICINE	= 3, // �ú�ҩ
        _TYPE_USE_MANA_MEDICINE	= 4, // ����ҩ
    };
public:
    CCheck();
    virtual ~CCheck();
public:
    BOOL Process();
    void Reset();
    void DecLife();
    void DecMana();
    void AddLife();
    void AddMana();
private:
    DWORD	m_dwTimeCheck;				// ���ʱ��Ϊ������5��10�������
    BOOL	m_bReportWSProcess;			// ÿ������ֻ����һ��
    BOOL	m_bReportFYProcess;			// ÿ������ֻ����һ��
    BOOL	m_bReportUseLifeMedicine;	// ÿ������ֻ����һ��
    BOOL	m_bReportUseManaMedicine;	// ÿ������ֻ����һ��
    int		m_nUseLifeMedicineAmount;
    int		m_nUseManaMedicineAmount;
    DWORD	m_dwLastDecLife;
    DWORD	m_dwLastDecMana;
    union
    {
        DWORD	m_dwData;
        struct
        {
            UCHAR	m_ucType; // ��������
        };
    };
};

#endif // !defined(AFX_CHECK_H__BD357BB3_6170_4E69_8778_C55BCA1682B8__INCLUDED_)
