
//**********************************************************
// ����༭��
//**********************************************************

// MsgAnnounceList.h: interface for the CMsgAnnounceList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGANNOUNCELIST_H__17B2F84C_5064_4F0F_A15A_FA09616053A8__INCLUDED_)
#define AFX_MSGANNOUNCELIST_H__17B2F84C_5064_4F0F_A15A_FA09616053A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Netmsg.h"
#include "Hero.h"

const int _MAX_ANNOUNCE_PER_PAGE = 20; // ÿҳ����20���������

class CMsgAnnounceList : public CNetMsg
{
public:
    CMsgAnnounceList();
    virtual ~CMsgAnnounceList();
    BOOL Create(char* pbufMsg, DWORD dwMsgSize);

    BOOL Create(USHORT usType, int nIndex, OBJID idAnnounce = 0);
    void Process (void* pInfo);

protected:
    typedef struct
    {
        unsigned short	unMsgSize;
        unsigned short	unMsgType;

        USHORT			usType; //to server // ����
        union
        {
            USHORT	usAmount; // ����
            OBJID	idAnnounce;
            int		nIndex; //to serverҪ��ʼ��ѯ������
        };
        ST_ANNOUNCE_TITLE setAnnounce[1];//to client
    } MSG_Info;

    MSG_Info* m_pInfo;
};

#endif // !defined(AFX_MSGANNOUNCELIST_H__17B2F84C_5064_4F0F_A15A_FA09616053A8__INCLUDED_)
