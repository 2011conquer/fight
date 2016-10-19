
//**********************************************************
// ����༭��
//**********************************************************

// MsgSyndicateAttributeInfo.h: interface for the CMsgSyndicateAttributeInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGSYNDICATEATTRIBUTEINFO_H__BEACEA82_5569_4645_BC2D_A5BB94E67C57__INCLUDED_)
#define AFX_MSGSYNDICATEATTRIBUTEINFO_H__BEACEA82_5569_4645_BC2D_A5BB94E67C57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"


class CMsgSyndicateAttributeInfo  : public CNetMsg
{
public:
    CMsgSyndicateAttributeInfo();
    virtual ~CMsgSyndicateAttributeInfo();
public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);
protected:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;
        OBJID	idSyndicate;				// ����id
        int		nProffer;					// ���׶�
        DWORD	dwSyndicateFund;			// ���ɻ���
        DWORD	dwSyndicatePopulation;		// �����˿�
        DWORD   dwSyndicateFamer;			// ��������
        USHORT	usMantle;					// �ű�
        UCHAR	ucSynRank;					//���ɼ���
        UCHAR	ucRank;						// ����ְ��
        UCHAR	ucLevel;					// ���ɵȼ�
        char	szLeader[_MAX_NAMESIZE];	// ����
    } MSG_Info;

    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGSYNDICATEATTRIBUTEINFO_H__BEACEA82_5569_4645_BC2D_A5BB94E67C57__INCLUDED_)
