
//**********************************************************
// ����༭��
//**********************************************************

// MsgMagicInfo.h: interface for the CMsgMagicInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGMAGICINFO_H__1188BAEC_D9BF_4F0D_8FEF_316D822FAD5E__INCLUDED_)
#define AFX_MSGMAGICINFO_H__1188BAEC_D9BF_4F0D_8FEF_316D822FAD5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

class CMsgMagicInfo : public CNetMsg
{
public:
    CMsgMagicInfo();
    virtual ~CMsgMagicInfo();

public:
    BOOL	Create		(char* pMsgBuf, DWORD dwSize);
    void	Process		(void* pInfo);

protected:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;

        OBJID			idOwner;	//ħ����������ID ���������Ƿ��ǻ��޵ļ���
        DWORD			dwExp;
        unsigned short	usType;
        unsigned short  usLevel;

    } MSG_Info;

    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGMAGICINFO_H__1188BAEC_D9BF_4F0D_8FEF_316D822FAD5E__INCLUDED_)
