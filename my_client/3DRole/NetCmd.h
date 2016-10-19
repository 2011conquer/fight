
//**********************************************************
// ����༭��
//**********************************************************

//--------------------------------------------------------------------------------------
// File Name: NetCmd.h
// Create by: Huang Yuhang
// Create on: 2004/1/14 10:28
//--------------------------------------------------------------------------------------
#ifndef _NETCMD_H
#define _NETCMD_H

#include "BaseFunc.h"

class CNetCmd
{
private:
    enum
    {
        _ID_BEGIN						= 1500000,				// �Ƿ�ID	// �ͻ�����ʼID // ��ʹ��
        _ID_SYN_DONATE					= _ID_BEGIN + 1,		// ���		// Ǯ����
        _ID_SYN_DEMISE					= _ID_BEGIN + 2,		// ����		// ��������
        _ID_SYN_UNAPPOINT				= _ID_BEGIN + 3,		// ��ְ		// ��������
        _ID_SYN_CREATE_SUBSYN			= _ID_BEGIN + 4,		// ���Ӱ���	// �Ӱ���id  ��������(���Ȳ�����2������)
        _ID_SYN_UPDATE_SUBSYN_LEADER	= _ID_BEGIN + 5,		// �����Ӱ��ɵİ��� // �Ӱ���id ��������
        _ID_SYN_ANTAGONIZE				= _ID_BEGIN + 6,		// ����		// ��������
        _ID_SYN_UNANTAGONIZE			= _ID_BEGIN + 7,		// ȡ������	// ��������
        _ID_SYN_ALLY					= _ID_BEGIN + 8,		// ����		// ��������
        _ID_SYN_UNALLY					= _ID_BEGIN + 9,		// ȡ������	// ��������
        _ID_SYN_FIRE_MEMBER				= _ID_BEGIN + 10,		// �������� // ��������
        _ID_SYN_MOVE_MEMBER				= _ID_BEGIN + 11,		// �ÿ�ת�� // ���ID Ŀ���ÿ�����
        _ID_SYN_BUY_EMBLEM				= _ID_BEGIN + 12,		// ���ű�   // �ű���
    };
private:
    static void SendCmd(int nIndex, const char* fmt, ...);

public:
    static BOOL SynDonate(DWORD dwMoney);
    static BOOL SynDemise(const char* pszName);
    static BOOL SynUnAppoint(const char* pszName);
    static BOOL SynCreateSubsyn(OBJID idSubLeader, const char* pszSynName);
    static BOOL SynUpdateSubsyn(OBJID idSubLeader, const char* pszSynName);
    static BOOL SynAntagonize(const char* pszSynName);
    static BOOL SynUnAntagonize(const char* pszSynName);
    static BOOL SynAlly(const char* pszSynName);
    static BOOL SynUnAlly(const char* pszSynName);
    static BOOL SynFireMember(const char* pszMemberName);
    static BOOL SynMoveMember(const OBJID idMember, const char* pszSubSynName);
    static BOOL SynBuyEmblem(DWORD dwIndex);
};

#endif
