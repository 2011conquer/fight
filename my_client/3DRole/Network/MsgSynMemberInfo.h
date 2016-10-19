
//**********************************************************
// ����༭��
//**********************************************************

// MsgSynMemberInfo.h: interface for the CMsgSynMemberInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGSYNMEMBERINFO_H__CB607DAF_CB16_40F2_A459_E8963D4B91AD__INCLUDED_)
#define AFX_MSGSYNMEMBERINFO_H__CB607DAF_CB16_40F2_A459_E8963D4B91AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetMsg.h"


class CMsgSynMemberInfo  : public CNetMsg
{
public:
    CMsgSynMemberInfo();
    virtual ~CMsgSynMemberInfo();
public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);
    BOOL			Create		(char* pszName);
protected:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;
        int		nProffer; // ���׶�
        UCHAR	ucRank; // ְλ
        UCHAR	ucProfession; // ְҵ
        UCHAR	ucNobilityRank; // ��λ
        UCHAR	ucLevel; // �ȼ�
        SHORT	sPk; // PKֵ
        DWORD	dwLookFace; // ͷ��
        char	szName[_MAX_NAMESIZE]; // ����
        char	szMate[_MAX_NAMESIZE]; // ��ż����

    } MSG_Info;

    MSG_Info*	m_pInfo;
};


#endif // !defined(AFX_MSGSYNMEMBERINFO_H__CB607DAF_CB16_40F2_A459_E8963D4B91AD__INCLUDED_)
