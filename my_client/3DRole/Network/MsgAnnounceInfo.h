
//**********************************************************
// ����༭��
//**********************************************************

// MsgAnnounceInfo.h: interface for the CMsgAnnounceInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGANNOUNCEINFO_H__B692E49E_1A88_4A84_BB46_E8BAAC61FFC6__INCLUDED_)
#define AFX_MSGANNOUNCEINFO_H__B692E49E_1A88_4A84_BB46_E8BAAC61FFC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "Hero.h"

class CMsgAnnounceInfo : public CNetMsg
{
public:
    CMsgAnnounceInfo();
    virtual ~CMsgAnnounceInfo();
public:
    BOOL QueryMyAnnounceInfo();
    BOOL QueryAnnounceInfo(OBJID idAnnounce);
    BOOL CancelAnnounce(OBJID idAnnounce);
    BOOL Create (char* pMsgBuf, DWORD dwSize);
    BOOL UpAnnounce (const char* szTitle, const char* szDesc);
    void Process (void* pInfo);
protected:
    typedef struct
    {
        unsigned short	unMsgSize;
        unsigned short	unMsgType;
        int				usType;
        OBJID			idAnnounce;
        OBJID			user_id;
        int				level;// ���������˵ĵȼ�
        int				teacher_level;// ��ʦ�ȼ�
        int				profession; //��ʦְҵ
        char			szBuf[1];//to client ������������⣬��������
    } MSG_Info;

    MSG_Info* m_pInfo;
private:
    CNetStringPacker m_StrPacker;
};

#endif // !defined(AFX_MSGANNOUNCEINFO_H__B692E49E_1A88_4A84_BB46_E8BAAC61FFC6__INCLUDED_)
