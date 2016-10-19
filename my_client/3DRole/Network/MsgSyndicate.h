
//**********************************************************
// ����༭��
//**********************************************************

// MsgSyndicate.h: interface for the CMsgSyndicate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGSYNDICATE_H__6D5AF55F_20CC_4A86_931B_878B4A787FEC__INCLUDED_)
#define AFX_MSGSYNDICATE_H__6D5AF55F_20CC_4A86_931B_878B4A787FEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetMsg.h"
#include "NetStringPacker.h"

enum
{
    ACTION_NONE			= 0,			// ����ֵ
    APPLY_JOIN			= 1,			// �����������, id
    INVITE_JOIN			= 2,			// �����������, id
    LEAVE_SYN			= 3,			// ��������
    KICKOUT_MEMBER		= 4,			// ����������Ա,id	(ע�⣺�ĳ�ID��)
    QUERY_SYN_NAME		= 6,			// ��ѯ��������
    ALLY_APPLY			= 7,			// ����/ͬ�����
    CLEAR_ALLY			= 8,			// �������
    ANTAGONIZE			= 9,			// ����
    CLEAR_ANTAGONIZE	= 10,			// �������
    DONATE_MONEY		= 11,			// ���ھ�Ǯ
    QUERY_SYNATTR		= 12,			// ��ѯ��������
    //		SET_MAINSYN			= 13,			// ��������ɵ�ID
    SET_SYN				= 14,			// ��Ӿ��ŵ�ID
    //		SET_SUBSUBSYN		= 15,			// ���С�ӵ�ID
    //		UNITE_SUBSYN		= 15,			// �ϲ��ÿ� // to client // dwData���ϲ�, target������
    //		UNITE_SYN			= 16,			// �ϲ����� // to client // dwData���ϲ�, target������
    SET_WHITE_SYN		= 17,			// �װ����ID // δ��ռ���뷢ID_NONE
    SET_BLACK_SYN		= 18,			// �ڰ����ID // δ��ռ���뷢ID_NONE
    DESTROY_SYN			= 19,			// ��ɢ���� // ��ͬ��
    SET_MANTLE			= 20,			// ��������

    APPLY_ALLY			= 21,			// �������			// to server client
    _CLEAR_ALLY			= 22,			//�������//client to server

    _SET_ANTAGONIZE		= 23,			//���� client to server
    _CLEAR_ANTAGONIZE   = 24,			//������� client to server

    _CREATE_SYN			= 101,			// ֪ͨNPC��������Ӱ���	// to npc
    _DESTROY_SYN		= 102,			// ֪ͨNPC������ɾ������	// to npc

    SYN_SET_PUBLISHTIME = 119, //���ù���ʱ��

    //add time:2005-3-21
    KICKOUT_MEMBER_INFO_QUERY = 110, //������ѯ���뿪���ĳ�Ա
    KICKOUT_MEMBER_AGREE = 111,   //����ͬ�⿪����Ա
    KICKOUT_MEMBER_NOTAGREE = 112,   //����ͬ�⿪����Ա

    SYNMEMBER_ASSIGN	= 113,	//���ɳ�Ա����

    SYN_CHANGE_SUBNAME = 114, //���Ÿ���
    SYN_CHANGE_SUBSUBNAME = 115, //�ֶӸ���
    SYN_DEMISE = 116,	 //����
    SYN_SET_ASSISTANT = 117, //���ø�����
    SYN_SET_TEAMLEADER = 118, //���ð��ɶӳ�
};

class CMsgSyndicate  : public CNetMsg
{
public:
    CMsgSyndicate();
    virtual ~CMsgSyndicate();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);
    BOOL			Create		(unsigned short usAction, OBJID idTarget);
    BOOL			Create		(unsigned short usAction, char* pMsgBuf);
    BOOL			Create      (unsigned short usAction, char* szName, OBJID idTarget);
protected:
    typedef struct
    {
        unsigned short	unMsgSize;
        unsigned short	unMsgType;

        unsigned short	usAction;
        union
        {
            OBJID idTarget;
            DWORD dwData;
        };
        union
        {
            OBJID idFealty; // �ϼ�����ID
            OBJID idUser;
        };

        char	szBuf[1];
    } MSG_Info;

    CNetStringPacker m_sName;

    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGSYNDICATE_H__6D5AF55F_20CC_4A86_931B_878B4A787FEC__INCLUDED_)
