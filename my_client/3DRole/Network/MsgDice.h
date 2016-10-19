
//**********************************************************
// ����༭��
//**********************************************************

// MsgDice.h: interface for the CMsgDice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDICE_H__B3F539EB_1871_4A23_A7BD_72211205A127__INCLUDED_)
#define AFX_MSGDICE_H__B3F539EB_1871_4A23_A7BD_72211205A127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
enum
{
    _ACTION_CHIPIN				= 0,		//��ע  to server, to client
    //������עͨ�����Action�㲥ͬ��
    //�¼���ľֵ���Ҳͨ�����Actionȡ��Ͷע�б�
    //dwDataΪͶ�˶���Ǯ��ucTypeΪͶ����ע
    // exclude self, �Լ�ͨ��_ACTION_CHIPIN ����
    _ACTION_CHIPIN_CONFIRM		= 1,		//��עȷ��// only to client
    _ACTION_CANCELCHIP			= 2,		//ȡ����עto server, to client
    //dwMoneyΪͶ�˶���Ǯ��ucTypeΪͶ����ע
    // exclude self, �Լ�ͨ��_ACTION_CHIPIN ����
    _ACTION_CANCELCHIP_CONFIRM	= 3,		//�˳���עȷ��// only to client
    _ACTION_BEGINCHIP			= 4,		//��ʼ��ע // to client ����ʱ30s
    _ACTION_ENDCHIP				= 5,		//������ // to client ����ʱ5S
    _ACTION_DICE				= 6,		//������Ϣ // to client ����ʱ5S // MsgName�㲥ӮǮ��Ϣ
};
class CMsgDice : public CNetMsg
{
public:
    CMsgDice();
    virtual ~CMsgDice();
    BOOL	Create	();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);
    BOOL			Create		(OBJID idDice, int nAction, DWORD dwMoney, int nType = 0);
private:
    typedef struct
    {
        unsigned short	unMsgSize;
        unsigned short	unMsgType;
        unsigned char	ucAction;
        union
        {
            unsigned char	ucTime;		// ������ע��ʼ�˶��
            unsigned char	ucAmount;
        };
        OBJID			idDice;
        struct
        {
            unsigned char	ucType;
            union
            {
                DWORD			dwData;
                unsigned char	ucDice[4];
            };
        } Data[1];
    } MSG_Info;

    MSG_Info*	m_pInfo;

};

#endif // !defined(AFX_MSGDICE_H__B3F539EB_1871_4A23_A7BD_72211205A127__INCLUDED_)
