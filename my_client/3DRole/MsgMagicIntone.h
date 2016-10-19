
//**********************************************************
// ����༭��
//**********************************************************

// MsgMagicIntone.h: interface for the MsgMagicIntone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGMAGICINTONE_H__CA975F3E_ECD3_4C5D_97BB_077A791AC3AC__INCLUDED_)
#define AFX_MSGMAGICINTONE_H__CA975F3E_ECD3_4C5D_97BB_077A791AC3AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetMsg.h"
#include "Magic.h"


enum MAGIC_GROUP_TYPE
{
    MAGICGROUP_NONE	= 0,
    MAGICGROUP_ATTACK_NOMOVE,	// �ϻ�1����������ԭ�ع���
    MAGICGROUP_ATTACK_MOVE,		// �ϻ�2��������λ��������
    MAGICGROUP_ATTACK_RAND,		// ���޹�����ҺϷ���Χ�ڵ�ĳһ�������
    MAGICGROUP_ATTACK_SAME,		// ���޹����������ͬ��Ŀ��
};

typedef struct
{
    DWORD	idEudemon;
    USHORT	usOffsetX, usOffsetY;
} EudemonPos_ST;


class CMsgMagicIntone  : public CNetMsg
{
public:
    CMsgMagicIntone();
    virtual ~CMsgMagicIntone();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

private:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;

        OBJID	idUser;
        USHORT	usPosX, usPosY;

        USHORT	usMagicType;
        USHORT	usMagicLevel;
        UCHAR	ucIntoneType;
        UCHAR	ucDir;
        UCHAR	ucEudemonNum;		// ����Ϊ0
        EudemonPos_ST	setEudemonPos[1];	// �䳤
    } MSG_Info;

    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGMAGICINTONE_H__CA975F3E_ECD3_4C5D_97BB_077A791AC3AC__INCLUDED_)
