
//**********************************************************
// ����༭��
//**********************************************************

// MsgTeam.cpp: implementation of the CMsgTeam class.
//
//////////////////////////////////////////////////////////////////////

#include "MsgTeam.h"
#include "Hero.h"
#include "GameMsg.h"
#include "GameDataSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgTeam::CMsgTeam()
{
    Init();
    m_pInfo	= (MSG_Info* )m_bufMsg;
}

CMsgTeam::~CMsgTeam()
{
}

//-------------------------------------------------------------------
BOOL CMsgTeam::Create(char* pbufMsg, DWORD dwMsgSize)
{
    if (!pbufMsg)
    {
        return false;
    }
    if ((unsigned short)dwMsgSize != GetSize(pbufMsg, dwMsgSize))
    {
        return false;
    }
    if (_MSG_TEAM != GetType(pbufMsg, dwMsgSize))
    {
        return false;
    }
    memcpy(this->m_bufMsg, pbufMsg, dwMsgSize);
    return true;
}
//-------------------------------------------------------------------
BOOL CMsgTeam::Create(OBJID idPlayer, int nAction)
{
    this->Init();
    // fill info now
    m_pInfo->unMsgSize	= sizeof(MSG_Info);
    m_pInfo->unMsgType	= _MSG_TEAM;
    m_pInfo->idPlayer = idPlayer;
    m_pInfo->unAction = nAction;
    return true;
}
//-------------------------------------------------------------------
void CMsgTeam::Process(void* pInfo)
{
    switch(m_pInfo->unAction)
    {
    case _MSGTEAM_CREATE:
        {
            // ��������֪�Ҷ��鴴���ɹ�
            g_objHero.ClearTeamMember();
            TeamMemberInfo* pInfo = CTeam::CreateNewMemberInfo((char*)g_objHero.GetName(),
                                    g_objHero.GetID(),
                                    g_objHero.GetFace(),
                                    g_objHero.GetData(CPlayer::_PLAYER_LIFE),
                                    g_objHero.GetMaxLife(),
                                    g_objHero.GetLook());
            g_objHero.AddTeamMember(pInfo);
            ::PostCmd(CMD_FLASHTEAM, 1);
        }
        break;
    case _MSGTEAM_APPLYJOIN:
        {
            // ����������������Ҫ������ҵĶ���
            if (g_objHero.SetTeamLastApply(m_pInfo->idPlayer))
            {
                ::PostCmd(CMD_TEAMAPPLY);
            }
        }
        break;
    case _MSGTEAM_LEAVE:
        {
            // ����˸����������뿪�˶���
            if (g_objHero.GetID() == m_pInfo->idPlayer)
            {
                g_objHero.ClearTeamMember();
                OBJID idLeaveTeam = 100107;
                g_objGameMsg.AddMsg(g_objGameDataSet.GetStr(idLeaveTeam));
            }
            else
            {
                TeamMemberInfo* pInfo = g_objHero.GetTeamMemberInfoByID(m_pInfo->idPlayer);
                if (pInfo)
                {
                    char szMsg[128];
                    OBJID idLeaveTeam = 100108;
                    sprintf(szMsg, g_objGameDataSet.GetStr(idLeaveTeam), pInfo->szName);
                    g_objGameMsg.AddMsg(szMsg);
                    g_objHero.DelTeamMember(m_pInfo->idPlayer);
                }
            }
            ::PostCmd(CMD_FLASHTEAM);
        }
        break;
    case _MSGTEAM_ACCEPTINVITE:
        break;
    case _MSGTEAM_INVITE:
        {
            // ����������������Ҫ���Ҽ������
            if (g_objHero.SetTeamLastApply(m_pInfo->idPlayer))
            {
                ::PostCmd(CMD_TEAMINVITE);
            }
        }
        break;
    case _MSGTEAM_AGREEJOIN:
        break;
    case _MSGTEAM_DISMISS:
        {
            // �����������Ҷ����ɢ��
            g_objHero.ClearTeamMember();
            const OBJID idDismiss = 100109;
            g_objGameMsg.AddMsg(g_objGameDataSet.GetStr(idDismiss));
            ::PostCmd(CMD_FLASHTEAM);
        }
        break;
    case _MSGTEAM_KICKOUT:
        {
            // ���������������˱��߳�����
            if (g_objHero.GetID() == m_pInfo->idPlayer)
            {
                const OBJID idKickOut = 100110;
                g_objGameMsg.AddMsg(g_objGameDataSet.GetStr(idKickOut));
                g_objHero.ClearTeamMember();
            }
            else
            {
                TeamMemberInfo* pInfo = g_objHero.GetTeamMemberInfoByID(m_pInfo->idPlayer);
                if (pInfo)
                {
                    const OBJID idKickOut = 100111;
                    char szMsg[128];
                    sprintf(szMsg, g_objGameDataSet.GetStr(idKickOut), pInfo->szName);
                    g_objGameMsg.AddMsg(szMsg);
                }
                g_objHero.DelTeamMember(m_pInfo->idPlayer);
            }
            ::PostCmd(CMD_FLASHTEAM);
        }
        break;
    case _MSGTEAM_CLOSETEAM:
        {
            // �����������Ҷ����Ѿ����ر�
            g_objHero.CloseTeam();
            const OBJID idClose = 100112;
            g_objGameMsg.AddMsg(g_objGameDataSet.GetStr(idClose));
            ::PostCmd(CMD_FLASHTEAM);
        }
        break;
    case _MSGTEAM_OPENTEAM:
        {
            // �����������Ҷ����Ѿ�����
            g_objHero.OpenTeam();
            const OBJID idOpen = 100113;
            g_objGameMsg.AddMsg(g_objGameDataSet.GetStr(idOpen));
            ::PostCmd(CMD_FLASHTEAM);
        }
        break;
    }
}
//-------------------------------------------------------------------
