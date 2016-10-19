
//**********************************************************
// ����༭��
//**********************************************************

// MsgName.h: interface for the CMsgName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_)
#define AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "NetStringPacker.h"

enum
{
    NAMEACT_NONE				= 0,
    NAMEACT_FIREWORKS			= 1,
    NAMEACT_CREATE_SYN			= 2,
    NAMEACT_CHANGE_SYN			= 3,
    NAMEACT_CHANGE_SYNTITLE		= 4,
    NAMEACT_DELROLE				= 5,
    NAMEACT_MATE				= 6,
    NAMEACT_QUERY_NPC			= 7,
    NAMEACT_WANTED				= 8,
    NAMEACT_MAPEFFECT			= 9,
    NAMEACT_ROLEEFFECT			= 10,
    NAMEACT_MEMBERLIST			= 11,		//dwData==-1 ��ʾ��һ��QUERY
    MANEACT_KICKOUT_SYNMEM		= 12,
    NAMEACT_QUERY_WANTED		= 13,
    NAMEACT_QUERY_POLICEWANTED	= 14,
    NAMEACT_POLICEWANTED		= 15,
    NAMEACT_QUERY_MATE			= 16,

    NAMEACT_ADDDICE_PLAYER		= 17, //ToClient �����������// dwDataΪ����̯ID // To Server ���� ��Ҫԭ��Ϣ����
    NAMEACT_DELDICE_PLAYER		= 18, //ToClient ɾ���������// dwDataΪ����̯ID // To Server �뿪 ��Ҫԭ��Ϣ����
    NAMEACT_DICE_BONUS			= 19, // �����ӽ��� ���// dwDataΪMoney

    NAMEACT_PLAYER_WAVE			= 20, // ����Ч // ���usPosX = usPosY = 0; �ǵ�ͼ��Ч

    NAMEACT_MEMBERLIST_SPECIFYSYN = 21,			//��ѯָ�����ɵĳ�Ա�б�
    //		NAMEACT_SYN_FRIEND			= 21, 				//
    NAMEACT_SYN_HOSTILE			= 22, 				//

    NAMEACT_PLAYERTASKLIST		= 23, // �����ѯ����
    NAMEACT_CHANGE_EUDEMON_NAME = 24, // ���޸�����idTarget=������ƷID����һ���ַ���Ϊ����������
};

class CMsgName : public CNetMsg
{
public:
    CMsgName();
    virtual ~CMsgName();

    BOOL	Create(int nType, const char* pszName, DWORD dwData = 0);
    BOOL	Create(int nType, const char* pszName, USHORT usPosX, USHORT usPosY);

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

private:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;

        union
        {
            OBJID	idTarget;
            DWORD	dwData;
            struct
            {
                USHORT  usPosX, usPosY;
            };
        };
        UCHAR	ucType;
        char	szBuf[1];
    } MSG_Info;

    MSG_Info*	m_pInfo;
private:
    CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGNAME_H__62DB03E2_7185_4BDF_B9B0_5AE64B03DFDB__INCLUDED_)
