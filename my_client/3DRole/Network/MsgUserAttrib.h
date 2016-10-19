
//**********************************************************
// ����༭��
//**********************************************************

///////////////////////////////////////////////////////////
//
//		CMsgUserAttrib.h
//

#ifndef		_MSGUSERSTATUS_H_
#define		_MSGUSERSTATUS_H_

#include "NetMsg.h"

const int _MAX_MSGATRRIB	= 35;
enum
{
    _USERATTRIB_LIFE = 0,
    _USERATTRIB_MAXLIFE = 1,
    _USERATTRIB_MANA = 2,
    _USERATTRIB_MAXMANA = 3,
    _USERATTRIB_MONEY = 4,
    _USERATTRIB_EXP = 5,
    _USERATTRIB_PK = 6,
    _USERATTRIB_PORFESSION = 7,
    _USERATTRIB_SIZEADD = 8,
    _USERATTRIB_PP = 9,
    _USERATTRIB_MONEYSAVED = 10,
    _USERATTRIB_ADDPOINT = 11,
    _USERATTRIB_LOOK = 12,
    _USERATTRIB_LEV = 13,
    _USERATTRIB_SOUL = 14,
    _USERATTRIB_HEALTH = 15,
    _USERATTRIB_FORCE = 16,
    _USERATTRIB_SPEED = 17,
    _USERATTRIB_NOBILITYRANK = 18, // ��λ
    //_USERATTRIB_DEGREE = 18,
    //_USERATTRIB_MAXLIFE = 18,

    _USERATTRIB_POSE = 19,
    _USERATTRIB_PROFFER = 20,
    _USERATTRIB_LENGTH = 21,
    _USERATTRIB_KO_ORDER = 22,
    _USERATTRIB_METEMPSYCHOSIS = 23,
    //_USERATTRIB_VIRTUE = 24,
    _USERATTRIB_EXPLOIT = 24, // ��ѫֵ

    //_USERATTRIB_CYCLEREBORN = 25,
    _USERATTRIB_MERCENARYLEVEL = 25,
    _USERATTRIB_USERSTATUS = 26,
    _USERATTRIB_HAIR = 27,
    _USERATTRIB_XP = 28,
    _USERATTRIB_ACTIONSPEED = 29,
    //_USERATTRIB_HONORTITLESELECTED = 30,
    _USERATTRIB_MERCENARYEXP = 30,
    _USERATTRIB_FAT = 31,
    _USERATTRIB_TUTOR_EXP = 32, // ��ʦ�ȼ�
    _USERATTRIB_TUTOR_LEVEL = 33, // ��ʦ����
    _USERATTRIB_DEX = 34, // ����
    _USERATTRIB_POTENTIAL = 35, // ����Ǳ��	�ٻ������Ļ���Ǳ��
    _USERATTRIB_KEEPEFFECT2 = 36,
    _USERATTRIB_MAXENERGY = 37, // �������
    _USERATTRIB_MAXEUDEMON = 39, // �����ٻ�������
    _USERATTRIB_MAXLIFEPERCENT = 40, // ���Ѫ��ǧ�ֱ�	1000��ȥ�����ֵ��Ϊ���˶�
};



typedef struct
{
    DWORD	ucAttributeType;
    DWORD	dwAttributeData;
} UserAttribStruct;

class CMsgUserAttrib : public CNetMsg
{
public:
    CMsgUserAttrib();
    virtual ~CMsgUserAttrib();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

private:
    typedef struct
    {
        unsigned short		unMsgSize;
        unsigned short		unMsgType;
        OBJID				idUser;
        DWORD				dwAttributeNum;
        UserAttribStruct	aUserAttrib[_MAX_MSGATRRIB];
    } MSG_Info;

    MSG_Info*	m_pInfo;
};

#endif
