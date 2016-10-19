
//**********************************************************
// ����༭��
//**********************************************************

// MsgAuction.h: interface for the CMsgAuction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGAUCTION_H__5FC288AD_505C_4132_A530_06AFD4FF7C1F__INCLUDED_)
#define AFX_MSGAUCTION_H__5FC288AD_505C_4132_A530_06AFD4FF7C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "Hero.h"

enum
{
    AUCTION_ADD = 0,//to server//����������Ʒ ������id(NPC) ,idItem dwValue
    AUCTION_BID ,//to server//��Ҿ������ ������id(NPC) idItem dwValue
    AUCTION_NEW ,//to client//��ʼ�µ����� ������idUser idItem dwValue
    AUCTION_HINT_USER,//to client �㲥��Ҿ���м� ������idUser idItem dwValue
    //		AUCTION_HINT, //to client���㲥���ֽм�dwDataΪ�ڼ��νУ�ǰ���Σ�������dwData idItem dwValue
    AUCTION_HAMMER,//to client���㲥���ֽм�dwDataΪ�ڼ��νУ����γɽ�������idUser,idItem,dwValue��
    AUCTION_ITEM_INFO,//to server/to client ������id(NPC),idItem ���أ�idItem,idUser,dwValue
    //		AUCTION_SYS, //to client �㲥������ϵͳ���򣬲���������ټ���������Ʒ
};

class CMsgAuction : public CNetMsg
{
public:
    CMsgAuction();
    virtual ~CMsgAuction();

    BOOL Create (OBJID idUser , OBJID idItem, int dwValue, int nAction);
    BOOL Create (OBJID idUser , OBJID idItem, int nAction);

    BOOL Create (char* pbufMsg, DWORD dwMsgSize);
    void Process (void* pInfo);
protected:
    typedef struct
    {
        USHORT			unMsgSize;
        USHORT			unMsgType;

        OBJID id; //����NPC��id
        OBJID idItem;
        int nAuction;
        int dwValue;
        union
        {
            char name[1];//�ɷ���ID��Ϊ����
            OBJID dwData;
        };
    } MSG_Info;

    MSG_Info* m_pInfo;
private:
    CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGAUCTION_H__5FC288AD_505C_4132_A530_06AFD4FF7C1F__INCLUDED_)
