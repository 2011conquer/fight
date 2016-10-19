
//**********************************************************
// ����༭��
//**********************************************************

// MsgDataArray.h: interface for the CMsgCharArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGCHARARRAY_H__9C42BA31_AE9D_493E_9336_BD1BC2615921__INCLUDED_)
#define AFX_MSGCHARARRAY_H__9C42BA31_AE9D_493E_9336_BD1BC2615921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum
{
    _DATAARRAY_ACTION_MEDAL				=	0,	//	unsigned char	// ѫ��
    _DATAARRAY_ACTION_HONORTITLE		=	1,	//	unsigned char	// �ƺ�

    //---jinggy---2004-11-9---����ϵͳ---begin
    _DATAARRAY_ACTION_UPGRADE_QUALITY		= 2, //����װ��Ʒ��
    _DATAARRAY_ACTION_UPGRADE_SUPERADDITION = 3, //����װ��׷��
    _DATAARRAY_ACTION_UPGRADE_EQUIPLEVEL	= 4, //����װ���ȼ�
    _DATAARRAY_ACTION_EMBEDGEM				= 5, //��װ��Ƕ�뱦ʯ
    //---jinggy---2004-11-9---����ϵͳ---end

    // add time -2005-3-21-Xliang
    _DATAARRAY_ACTION_SETSYN_DRESS	= 50,	//�ͻ���������������ð��ɷ�װ��һ���ĸ��ȼ��ķ�װ,������ucAmount��usShort
    _DATAARRAY_SETITEMREBATE	= 60,  //������Ʒ���ۿۣ�������idNPC��nRebate
};

#define MAX_LEVEL_SUPERADDITION 9 //ָ׷�����Ե���߼���

class CMsgDataArray   : public CNetMsg
{
public:
    CMsgDataArray();
    virtual ~CMsgDataArray();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

    BOOL	Create(int nAction, int nAmount, char setChar[]);
    BOOL	Create(int nAction, int nAmount, short setShort[]);
    BOOL	Create(int nAction, int nAmount, long setLong[]);

protected:
    typedef struct
    {
        USHORT			unMsgSize;
        USHORT			unMsgType;
        unsigned char	ucAction;
        unsigned char	ucAmount;
        union
        {
            unsigned char	ucChar[1];
            char			cChar[1];
            unsigned short	usShort[1];
            short			sShort[1];
            unsigned long	dwLong[1];
            long			nLong[1];
        };
    } MSG_Info;
    MSG_Info*	m_pInfo;
};

#endif // !defined(AFX_MSGCHARARRAY_H__9C42BA31_AE9D_493E_9336_BD1BC2615921__INCLUDED_)
