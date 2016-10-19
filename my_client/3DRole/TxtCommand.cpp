
//**********************************************************
// ����༭��
//**********************************************************

// TxtCommand.cpp: implementation of the CTxtCommand class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)
#include "TxtCommand.h"
#include "Hero.h"
#include "Shop.h"
#include "GamePlayerSet.h"
#include "Gamemsg.h"
#include "3DGameMap.h"
#include "XpCounterDown.h"
#include "GameDataSet.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int g_nLMouseOperate;

CTxtCommand::CTxtCommand()
{
    m_setCommand.clear();
}

CTxtCommand::~CTxtCommand()
{
    this->Clear();
}
//-------------------------------------------------------------------
void	CTxtCommand::Clear()
{
    int nAmount = m_setCommand.size();
    for(int i = 0; i < nAmount; i++)
    {
        delete(m_setCommand[i]);
    }
    m_setCommand.clear();
}
//-------------------------------------------------------------------
int		CTxtCommand::GetAmount()
{
    return m_setCommand.size();
}
//-------------------------------------------------------------------
char*	CTxtCommand::GetTxt(int nIndex)
{
    if (nIndex < 0)
    {
        return NULL;
    }
    if (nIndex >= this->GetAmount())
    {
        return NULL;
    }
    return m_setCommand[nIndex];
}
//-------------------------------------------------------------------
void CTxtCommand::AddCommand(char* pszCommand)
{
    int nMaxTxtCommand = 20;
    char szMyTxtCommand[20][64] =
    {
        "setheropos",	// ������������ X Y
        "openshop",		// ���̵� ID
        "closeshop",	// �ر��̵�
        "listshop",		// �鿴��Ʒ nIndex
        "who",			// �鿴��Χ���
        "walk",			// ��·ģʽ
        "run",			// �ܲ�ģʽ
        "jump",			// �Ṧģʽ
        "package",		// ������
        "buy",			// ���� nIndex
        "sell",			// ������ nIndex
        "cls",			// ����Ļ
        "setmsgline",	// �������� nLines
        "hp",			// �鿴��������
        "test",			// ����ר��
        "say",			// ˵�� ����
        "tell",			// ˵�� Ŀ�� ����
        "makefriend",   // ��� Ŀ��
        "listfriend",	// ����б�
        "breakofffriend"// ����
    };
    if (!pszCommand)
    {
        return;
    }
    int nIndex = -1;
    for(int i = 0; i < nMaxTxtCommand; i++)
    {
        if (strstr(pszCommand, szMyTxtCommand[i]) != NULL)
        {
            if (strlen(strstr(pszCommand, szMyTxtCommand[i])) == strlen(pszCommand))
            {
                nIndex = i;
                break;
            }
        }
    }
    extern int g_nLMouseOperate;
    switch(nIndex)
    {
    case 0:
        this->SetHeroPos(pszCommand);
        break;
    case 1:
        this->OpenShop(pszCommand);
        break;
    case 2:
        this->CloseShop();
        break;
    case 3:
        this->ListShop();
        break;
    case 4:
        this->ListPlayer();
        break;
    case 5:
        g_nLMouseOperate = 0;
        break;
    case 6:
        g_nLMouseOperate = 2;
        break;
    case 7:
        g_nLMouseOperate = 1;
        break;
    case 8:
        this->ListPackage();
        break;
    case 9:
        this->Buy(pszCommand);
        break;
    case 10:
        this->Sell(pszCommand);
        break;
    case 11:
        g_objGameMsg.ClearMsg();
        break;
    case 12:
        this->SetMsgLine(pszCommand);
        break;
    case 13:
        this->ShowStatus();
        break;
    case 14:
        this->Test(pszCommand);
        break;
    case 15:
        this->Say(pszCommand);
        break;
    case 16:
        this->Tell(pszCommand);
        break;
    case 17:
        this->MakeFriend(pszCommand);
        break;
    case 18:
        this->ListFriend();
        break;
    case 19:
        this->BreakOffFriend(pszCommand);
        break;
    default:
        break;
    }
}
//----------------------------------------------------------------------------
void CTxtCommand::SetHeroPos(char* pszCommand)
{
    char szCommand[64];
    CMyPos posHero = {0, 0};
    if (sscanf(pszCommand, "%s %u %u", szCommand, &posHero.x, &posHero.y) != 3)
    {
        return;
    }
    g_objHero.SetPos(posHero.x, posHero.y);
    char* szMsg = new char[128];
    sprintf(szMsg, "��������λ�á�%d,%d��", posHero.x, posHero.y);
    m_setCommand.push_back(szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::OpenShop(char* pszCommand)
{
    char szCommand[64];
    OBJID idShop;
    if (sscanf(pszCommand, "%s %u", szCommand, &idShop) != 2)
    {
        return;
    }
    char* szMsg = new char[128];
    if (g_objShop.Open(idShop))
    {
        sprintf(szMsg, "���̵�%u�ɹ�", idShop);
    }
    else
    {
        sprintf(szMsg, "���̵�%uʧ��", idShop);
    }
    m_setCommand.push_back(szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::CloseShop()
{
    char* szMsg = new char[128];
    g_objShop.Close();
    strcpy(szMsg, "�̵�رգ�");
    m_setCommand.push_back(szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::ListShop()
{
    char* szMsg = new char[128];
    if (!g_objShop.GetShopName())
    {
        return;
    }
    strcpy(szMsg, g_objShop.GetShopName());
    m_setCommand.push_back(szMsg);
    szMsg = new char[128];
    sprintf(szMsg, "�̵�����Ϊ��%d", g_objShop.GetShopType());
    m_setCommand.push_back(szMsg);
    szMsg = new char[128];
    sprintf(szMsg, "��Ʒ����Ϊ��%d", g_objShop.GetItemAmount());
    m_setCommand.push_back(szMsg);
    for(DWORD i = 0; i < g_objShop.GetItemAmount(); i++)
    {
        CItem* pItem = g_objShop.GetItem(i);
        if (pItem)
        {
            szMsg = new char[128];
            sprintf(szMsg, "(%d)%s/%d", i, pItem->GetName(), pItem->GetPrice());
            m_setCommand.push_back(szMsg);
        }
    }
}
//----------------------------------------------------------------------------
void CTxtCommand::ListPlayer()
{
    int nAmount = g_objPlayerSet.GetPlayerAmount();
    char* szMsg = new char[128];
    sprintf(szMsg, "��Χ�������%d", nAmount);
    m_setCommand.push_back(szMsg);
    for(int i = 0; i < nAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        char* szMsg = new char[128];
        sprintf(szMsg, "(%d)%s:%u", i, pPlayer->GetName(), pPlayer->GetID());
        m_setCommand.push_back(szMsg);
    }
}
//----------------------------------------------------------------------------
void CTxtCommand::ListPackage()
{
    /*	int nAmount = g_objHero.GetItemAmount();
    	char* szMsg = new char[128];
    	sprintf(szMsg, "������Ʒ����%d", nAmount);
    	m_setCommand.push_back(szMsg);

    	szMsg = new char[128];
    	sprintf(szMsg, "��Ǯ��%d", g_objHero.GetMoney());
    	m_setCommand.push_back(szMsg);

    	for(int i = 0; i < nAmount; i ++)
    	{
    		CItem* pItem = g_objHero.GetItemByIndex(i);
    		if (pItem)
    		{
    			char* szMsg = new char[128];
    			sprintf(szMsg, "(%d)%s:%u", i, pItem->GetName(), pItem->GetID());
    			m_setCommand.push_back(szMsg);
    		}
    	}
    */
}
//----------------------------------------------------------------------------
void CTxtCommand::Buy(char* pszCommand)
{
    char szCommand[64];
    int nIndex;
    if (sscanf(pszCommand, "%s %u", szCommand, &nIndex) != 2)
    {
        return;
    }
    char* szMsg = new char[128];
    CItem* pItem = g_objShop.GetItem(nIndex);
    if (!pItem)
    {
        strcpy(szMsg, "û����Ӧ��Ʒ��");
    }
    else
    {
        sprintf(szMsg, "��������������%s������", pItem->GetName());
        g_objHero.BuyItem(pItem->GetTypeID());
    }
    m_setCommand.push_back(szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::Sell(char* pszCommand)
{
    /*	char szCommand[64];
    	int nIndex;
    	if (sscanf(pszCommand, "%s %u", szCommand, &nIndex) != 2)
    		return;
    	char* szMsg = new char[128];

    	CItem* pItem = g_objHero.GetItemByIndex(nIndex);
    	if (!pItem)
    	{
    		strcpy(szMsg, "û����Ӧ��Ʒ��");
    	}
    	else
    	{
    		sprintf(szMsg, "��������������%s������", pItem->GetName());
    		g_objHero.SellItem(pItem->GetID());
    	}
    	m_setCommand.push_back(szMsg);*/
}
//----------------------------------------------------------------------------

void CTxtCommand::SetMsgLine(char* pszCommand)
{
    char szCommand[64];
    int nLines;
    if (sscanf(pszCommand, "%s %u", szCommand, &nLines) != 2)
    {
        return;
    }
    g_objGameMsg.SetShowLines(nLines);
}
//----------------------------------------------------------------------------
void CTxtCommand::ShowStatus()
{
    char* szMsg = new char[128];
    sprintf(szMsg, "HP:%d/%d", g_objHero.GetLife(), g_objHero.GetMaxLife());
    m_setCommand.push_back(szMsg);
    szMsg = new char[128];
    sprintf(szMsg, "MANA:%d/%d", g_objHero.GetMana(), g_objHero.GetMaxMana());
    m_setCommand.push_back(szMsg);
    szMsg = new char[128];
    sprintf(szMsg, "XP:%d/%d", g_objHero.GetXP(), g_objHero.GetMaxXP());
    m_setCommand.push_back(szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::Say(char* pszCommand)
{
    char szCommand[64];
    char szMsg[256];
    if (sscanf(pszCommand, "%s %s", szCommand, szMsg) != 2)
    {
        return;
    }
    //	g_objHero.Talk(NULL, szMsg);
}
//----------------------------------------------------------------------------
void CTxtCommand::Tell(char* pszCommand)
{
    char szCommand[64];
    char szTarget[256];
    char szWords[256];
    if (sscanf(pszCommand, "%s %s %s", szCommand, szTarget, szWords) != 3)
    {
        return;
    }
    //	g_objHero.Talk(NULL, szWords);
}
//----------------------------------------------------------------------------
void CTxtCommand::MakeFriend(char* pszCommand)
{
    char szCommand[64];
    char szTarget[256];
    if (sscanf(pszCommand, "%s %s", szCommand, szTarget) != 2)
    {
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(szTarget);
    if (pPlayer)
    {
        g_objHero.MakeFriend(pPlayer->GetID());
    }
}
//----------------------------------------------------------------------------
void CTxtCommand::BreakOffFriend(char* pszCommand)
{
    char szCommand[64];
    char szTarget[256];
    if (sscanf(pszCommand, "%s %s", szCommand, szTarget) != 2)
    {
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(szTarget);
    if (pPlayer)
    {
        g_objHero.BreakOffFriend(pPlayer->GetID());
    }
}
//----------------------------------------------------------------------------
void CTxtCommand::ListFriend()
{
    int nAmount = g_objHero.GetFriendAmount();
    for(int i = 0; i < nAmount; i ++)
    {
        CFriend* pFriend = g_objHero.GetFriendByIndex(i);
        if (pFriend)
        {
            char* szMsg = new char[128];
            sprintf(szMsg, "(%d)%s(%d)", i, pFriend->GetName(), pFriend->IsOnline());
            m_setCommand.push_back(szMsg);
        }
    }
}
//----------------------------------------------------------------------------


void CTxtCommand::Test(char* pszCommand)
{
    /*	TeamMemberInfo* pInfo = CTeam::CreateNewMemberInfo("����", 1,
    		0, 10, 20);
    	g_objHero.AddTeamMember(pInfo);

    	pInfo = CTeam::CreateNewMemberInfo("����", 2,
    		1, 10, 20);
    	g_objHero.AddTeamMember(pInfo);

    	pInfo = CTeam::CreateNewMemberInfo("����", 3,
    		2, 10, 20);
    	g_objHero.AddTeamMember(pInfo);

    	pInfo = CTeam::CreateNewMemberInfo("��������������", 4,
    		3, 10, 20);
    	g_objHero.AddTeamMember(pInfo);*/
    /*	if (g_objHero.TestStatus(64))
    		g_objHero.ReplaceStatus(0);
    	else
    		g_objHero.ReplaceStatus(64);*/
    //	g_objHero.AddZoomNum(::RandGet(100), 0xff0000, 300, 30);
    //	g_objGameMap.AddMagicEffect();
    //	g_objHero.m_objEffect.Add("Thunder");
    CMagicEffect* pEffect =
        CMagicEffect::CreateNew(g_objHero.GetID(), g_objHero.GetID(),
                                1, 1);
    pEffect->AddRoleInfo(g_objHero.GetID(), 1);
    g_objGameMap.AddMagicEffect(pEffect);
    /*	if (pEffect)
    	{
    		for(int i = 0; i < m_pInfo->ucEffectNum; i ++)
    			pEffect->AddRoleInfo(m_pInfo->setEffectRole[i].idRole,
    						m_pInfo->setEffectRole[i].dwData);
    		g_objGameMap.AddMagicEffect(pEffect);
    	}*/
}
//----------------------------------------------------------------------------
