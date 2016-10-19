
//**********************************************************
// ����༭��
//**********************************************************

// MsgNpc.h: interface for the CMsgNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGNPC_H__CBF5FF3C_C1ED_4A7B_B31B_5E9057824185__INCLUDED_)
#define AFX_MSGNPC_H__CBF5FF3C_C1ED_4A7B_B31B_5E9057824185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum
{
    EVENT_BEACTIVED = 0,				// to server		// ����
    EVENT_ADDNPC,						// to server		// ���
    EVENT_LEAVEMAP,						// to client		// ɾ��
    EVENT_DELNPC,						// to server		// ɾ��
    EVENT_CHANGEPOS,					// to server/client	// �ƶ�
    EVENT_LAYNPC,						// to client		// ֪ͨ�ͻ��˿�ʼ����
    // to client(id=region,data=lookface), answer MsgNpcInfo(CMsgPlayer for statuary)
};

class CMsgNpc : public CNetMsg
{
public:
    CMsgNpc();
    virtual ~CMsgNpc();

    BOOL	Create	(int nAction, OBJID id, DWORD dwData = 0, USHORT usType = 0);
public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

protected:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;
        OBJID id;
        union
        {
            DWORD			dwData;
            struct
            {
                USHORT			usPosX;
                USHORT			usPosY;
            };
        };

        USHORT usAction;
        USHORT usType;
    } MSG_Info;

    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGNPC_H__CBF5FF3C_C1ED_4A7B_B31B_5E9057824185__INCLUDED_)
