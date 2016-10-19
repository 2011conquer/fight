
//**********************************************************
// ����༭��
//**********************************************************

//--------------------------------------------------------------------------------------
// File Name: MsgPlayerTask.h
// Create by: Huang Yuhang
// Create on: 2004/10/9 10:36
//--------------------------------------------------------------------------------------
#ifndef _MSGPLAYERTASK_H
#define _MSGPLAYERTASK_H
//--------------------------------------------------------------------------------------

#include "NetMsg.h"
#include "NetStringPacker.h"
#include "Hero.h"


class CMsgPlayerTask : public CNetMsg
{
public:
    CMsgPlayerTask();
    virtual ~CMsgPlayerTask();

public:
    void			WantPk(const char* pszName, const char* pszTitle, const char* pszDesc,
                           DWORD dwMoney, UCHAR ucRankReq, OBJID idItem0,
                           OBJID idItem1, OBJID idItem2, OBJID idItem3,
                           OBJID idItem4);
    void			WantItem(const char* pszName,  const char* pszTitle, const char* pszDesc,
                             UCHAR ucType, DWORD dwDurability,
                             UCHAR ucAddition,
                             UCHAR ucDegree,
                             WORD dwMoney, UCHAR ucRankReq, OBJID idItem0,
                             OBJID idItem1, OBJID idItem2, OBJID idItem3,
                             OBJID idItem4);
public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

private:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;

        DWORD	dwMoney;

        OBJID idTask;

        // �������Ʒ ��Ҫ��Ʒ�ĸ�������
        DWORD dwDurability;	// �;�
        UCHAR ucAddition;	// ׷�� // ���޳ɳ�
        UCHAR ucDegree;		// �ȼ� // ���޵ȼ�

        UCHAR ucType;		// ��������
        UCHAR ucRankReq; // ��Ҫ��Ӷ���ȼ�

        ST_PLAYERTASK_ITEM infoItem[_MAX_PRIZE]; // ��Ʒ��Ϣ -- dwItemType = ID_NONE��ʾ����û��

        char	szBuf[1];//to client �µ������� ������ϸ���� ����ɱ�˻���Ʒ����
        //to server ����title ������ϸ���� ����ɱ�˻���Ʒ����
    } MSG_Info;

    MSG_Info*	m_pInfo;
private:
    CNetStringPacker	m_StrPacker;
};

//--------------------------------------------------------------------------------------
#endif
