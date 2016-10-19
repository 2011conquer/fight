
//**********************************************************
// ����༭��
//**********************************************************

//--------------------------------------------------------------------------------------
// File Name: MsgSchoolMember.h
// Create by: Huang Yuhang
// Create on: 2004/9/4 15:53
//--------------------------------------------------------------------------------------
#ifndef _MSGSCHOOLMEMBER_H
#define _MSGSCHOOLMEMBER_H

#include "NetMsg.h"
#include "NetStringPacker.h"
enum
{
    MESSAGEBOARD_DELMEMBER				= 1,	//ɾ��
    MESSAGEBOARD_ADDMEMBER				= 2,	//���
    MESSAGEBOARD_UPDATEMEMBER			= 3,	//����
};

class CMsgSchoolMember : public CNetMsg
{
public:
    CMsgSchoolMember();
    virtual ~CMsgSchoolMember();


public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);
    //	BOOL			Create		(unsigned short usIndex, unsigned char ucAction, unsigned short usChannel, char* pszStr = NULL);
    typedef struct
    {
        OBJID idMember; // ��ԱID
        char szName[_MAX_NAMESIZE]; // ��Ա����
        char szMate[_MAX_NAMESIZE]; // ��ż����
        UCHAR ucLevel; // �ȼ�
        UCHAR ucProfession; // ְҵ���
        USHORT usPkValue; // PKֵ
        UCHAR ucNobilityRank; // ��ݣ���λ��
        UCHAR ucRelation; // ����ҹ�ϵ
        UCHAR ucStatus; // ״̬ ���� �����ߡ�����
        DWORD dwSynID_Rank; // ����ID & ְλ (��MsgPlayerһ������8λΪְλ��ţ���24λΪ����ID)
    } ST_MEMBERINFO;

    typedef struct
    {
        USHORT unMsgSize;
        USHORT unMsgType;

        UCHAR ucAction; // ��Ϊģʽ
        UCHAR ucAmount; // ����
        ST_MEMBERINFO setMember[1]; // ��Ա�б�
    } MSG_Info;
    MSG_Info*	m_pInfo;
};

#endif
