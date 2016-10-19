
//**********************************************************
// ����༭��
//**********************************************************

// MsgTrade.h: interface for the CMsgTrade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTRADE_H__0967762A_20BA_4F08_8C15_CA80AE0E2BD2__INCLUDED_)
#define AFX_MSGTRADE_H__0967762A_20BA_4F08_8C15_CA80AE0E2BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

const unsigned short _TRADE_APPLY			= 1;		// ������		to client/server
const unsigned short _TRADE_QUIT			= 2;		// ȡ������		to server
const unsigned short _TRADE_OPEN			= 3;		// �򿪽��״�	to client
const unsigned short _TRADE_SUCCESS			= 4;		// ���׳ɹ�(ͬʱ�ر�)		to client
const unsigned short _TRADE_FALSE			= 5;		// ����ʧ��(ͬʱ�ر�)		to client
const unsigned short _TRADE_ADDITEM			= 6;		// ����Ʒ		to server(�Է��յ�MSGITEMINFO��Ϣ)
const unsigned short _TRADE_ADDMONEY		= 7;		// ��Ǯ			to server
const unsigned short _TRADE_PLAYERTOTALMONEY = 8;		// Ǯ����		to client(�Է�������Ǯ����)
const unsigned short _TRADE_HEROTOTALMONEY	= 9;		// Ǯ����		to client(�Լ���Ǯ����/ÿ�μ�Ǯ�������᷵��)
const unsigned short _TRADE_OK				= 10;		// ͬ�⽻��		to client/server
const unsigned short _TRADE_ADDITEM_FALSE	= 11;		// ����Ʒʧ��	to client

class CMsgTrade : public CNetMsg
{
public:
    CMsgTrade();
    virtual ~CMsgTrade();

public:
    BOOL	Create(OBJID idPlayer, unsigned short usAction);

    BOOL	Create(char* pbufMsg, DWORD dwMsgSize);
    void	Process(void* pInfo);

private:
    typedef struct
    {
        unsigned short	unMsgSize;
        unsigned short	unMsgType;

        union
        {
            OBJID			id;
            DWORD			dwData;
        };
        unsigned short	usAction;
    } MSG_Info;

    MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGTRADE_H__0967762A_20BA_4F08_8C15_CA80AE0E2BD2__INCLUDED_)
