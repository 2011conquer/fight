
//**********************************************************
// ����༭��
//**********************************************************

// Pet.cpp: implementation of the CPet class.
//
//////////////////////////////////////////////////////////////////////

#include "Pet.h"
#include "Hero.h"
#include "AllMsg.h"
#include "3DGameMap.h"
#include "GamePlayerSet.h"
#include "GameMsg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPet::CPet()
{
    m_nBehaviorType	=	_PET_BEHAVIOR_READY;
    m_idTarget		=	ID_NONE;
    m_idHeroTarget	=	ID_NONE;
    m_idItem		=   ID_NONE;
    m_bMagicLock = false;
    m_bMagicAttackBusy = false;
    ZeroMemory(m_nAll, sizeof(m_nAll));
}

CPet::~CPet()
{
    DestroyMagicSet();
}

//--------------------------------------------------------------------------------------
CPet*	CPet::CreateNewPet	(OBJID idPet, int nType, OBJID idItem)
{
    CPet* pPet = new CPet;
    MYASSERT(pPet);
    pPet->SetID(idPet);
    pPet->SetAIType(nType);
    pPet->SetItemID (idItem);
    pPet->DestroyMagicSet();
    return pPet;
}
//--------------------------------------------------------------------------------------
int		CPet::GetAtkRange	(void)
{
    return m_AIInfo.nAttackRange;
}
//--------------------------------------------------------------------------------------

void	CPet::SetAIType(int nType)
{
    PetInfo* pInfo = g_obj3DRoleData.GetPetInfo(nType);
    MYASSERT(pInfo);
    m_AIInfo.setLocateTargetMethod.clear();
    m_AIInfo.nEnvMethod = pInfo->nEnvMethod;
    m_AIInfo.nScale = pInfo->nScale;
    m_AIInfo.nAttackRange = pInfo->nAttackRange;
    m_Info.iAddSize = pInfo->nAddSize;
    m_AIInfo.nAddSize = pInfo->nAddSize;
    m_AIInfo.dwAttackInterval = pInfo->dwAttackInterval;
    int nAmount = pInfo->setLocateTargetMethod.size();
    for(int i = 0, j = 0; i < nAmount; i  ++)
    {
        int nMethod = pInfo->setLocateTargetMethod[i];
        m_AIInfo.setLocateTargetMethod.push_back(nMethod);
        if ((nMethod >= 9 && nMethod <= 10) || nMethod == 4 || nMethod == 5)
        {
            m_nAll[j++] = nMethod;
        }
    }
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckEnemy(CPlayer* pPlayer, int nRange, BOOL bHero)
{
    //const int _PET_SEARCH_ENEMY_RANGE = 12;
    if (!pPlayer)
    {
        return false;
    }
    if (pPlayer->IsMyPet())
    {
        return false;
    }
    if (pPlayer->IsDead())
    {
        return false;
    }
    CMyPos posHero, posTarget;
    if (bHero)
    {
        g_objHero.GetPos(posHero);
    }
    else
    {
        this->GetPos (posHero);
    }
    pPlayer->GetPos(posTarget);
    if (abs(posHero.x - posTarget.x) > nRange ||
            abs(posHero.y - posTarget.y) > nRange)
    {
        return false;
    }
    return true;
}
//--------------------------------------------------------------------------------------

void	CPet::SearchStatusAsistant()
{
    // Ŀ����Զ��Hero ...
    m_idTarget = g_objHero.GetID();
}
//--------------------------------------------------------------------------------------
void	CPet::SearchAttackAsistant()
{
    // ��Hero��Ŀ��ΪĿ��
    OBJID id = m_idHeroTarget;
    if (id == ID_NONE)
    {
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(id);
    if (!pPlayer)
    {
        return;
    }
    if (this->CheckEnemy(pPlayer))
    {
        m_idTarget = id;
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyRevenge()
{
    // �Թ���Hero��ΪĿ��
    OBJID id = g_objHero.GetIDWhoAttackMe();
    if (id == ID_NONE)
    {
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(id);
    if (!pPlayer)
    {
        return;
    }
    if (pPlayer->IsDead())
    {
        return;
    }
    if (this->CheckEnemy(pPlayer))
    {
        m_idTarget = id;
        m_bRevengeID = true;
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyGuard()
{
    // ������Hero�����Monster
    DWORD dwPlayerAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pTarget = NULL;
    DWORD dwDistance = 100;
    for(DWORD i = 0; i < dwPlayerAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && pPlayer->IsMonster() && !pPlayer->IsGuard() && !pPlayer->IsDead()
                && !pPlayer->IsMyPet())
        {
            DWORD dwMyDistance = g_objHero.GetDistance(pPlayer);
            if (dwMyDistance < dwDistance)
            {
                dwDistance = dwMyDistance;
                pTarget = pPlayer;
            }
        }
    }
    if (pTarget && this->CheckEnemy(pTarget))
    {
        m_idTarget = pTarget->GetID();
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyWarlike()
{
    DWORD dwPlayerAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pTarget = NULL;
    DWORD dwDistance = 100;
    for(DWORD i = 0; i < dwPlayerAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && pPlayer->IsMonster() && !pPlayer->IsGuard() && !pPlayer->IsDead()
                && !pPlayer->IsMyPet())
        {
            DWORD dwMyDistance = this->GetDistance(pPlayer);
            if (dwMyDistance < dwDistance)
            {
                dwDistance = dwMyDistance;
                pTarget = pPlayer;
            }
        }
    }
    if (pTarget && this->CheckEnemy(pTarget))
    {
        m_idTarget = pTarget->GetID();
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyJusticalA()
{
    // �����Լ�����ĺ���
    DWORD dwPlayerAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pTarget = NULL;
    DWORD dwDistance = 100;
    for(DWORD i = 0; i < dwPlayerAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && pPlayer->TestStatus(USERSTATUS_DARKRED) && !pPlayer->IsGuard() && !pPlayer->IsDead()
                && !pPlayer->IsMyPet())
        {
            DWORD dwMyDistance = this->GetDistance(pPlayer);
            if (dwMyDistance < dwDistance)
            {
                dwDistance = dwMyDistance;
                pTarget = pPlayer;
            }
        }
    }
    if (pTarget && this->CheckEnemy(pTarget))
    {
        m_idTarget = pTarget->GetID();
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyJusticalB()
{
    // �����Լ�����ĺ���
    DWORD dwPlayerAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pTarget = NULL;
    DWORD dwDistance = 100;
    for(DWORD i = 0; i < dwPlayerAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && pPlayer->TestStatus(USERSTATUS_RED) && !pPlayer->IsGuard() && !pPlayer->IsDead()
                && !pPlayer->IsMyPet())
        {
            DWORD dwMyDistance = this->GetDistance(pPlayer);
            if (dwMyDistance < dwDistance)
            {
                dwDistance = dwMyDistance;
                pTarget = pPlayer;
            }
        }
    }
    if (pTarget && this->CheckEnemy(pTarget))
    {
        m_idTarget = pTarget->GetID();
    }
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemyJusticalC()
{
    // �����Լ����������
    DWORD dwPlayerAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pTarget = NULL;
    DWORD dwDistance = 100;
    for(DWORD i = 0; i < dwPlayerAmount; i ++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && pPlayer->TestStatus(USERSTATUS_CRIME) && !pPlayer->IsGuard() && !pPlayer->IsDead()
                && !pPlayer->IsMyPet())
        {
            DWORD dwMyDistance = this->GetDistance(pPlayer);
            if (dwMyDistance < dwDistance)
            {
                dwDistance = dwMyDistance;
                pTarget = pPlayer;
            }
        }
    }
    if (pTarget && this->CheckEnemy(pTarget))
    {
        m_idTarget = pTarget->GetID();
    }
}
//--------------------------------------------------------------------------------------
BOOL	CPet::SearchEnemy()
{
    int nAmount = m_AIInfo.setLocateTargetMethod.size();
    if (nAmount > 0 && m_AIInfo.setLocateTargetMethod[0] != _PET_SE_STATUS_ASSISTANT)
    {
        OBJID idSpecial = g_objHero.GetSpecialTarget();
        if (idSpecial != ID_NONE)
        {
            CPlayer* pTarget = g_objPlayerSet.GetPlayer(idSpecial, true);
            if (pTarget && 	this->CheckEnemy(pTarget))
            {
                m_idTarget	= idSpecial;
                return true;
            }
        }
    }
    for(int i = 0; i < nAmount; i ++)
    {
        int nMethod = m_AIInfo.setLocateTargetMethod[i];	//���⴦��
        if (m_idTarget && nMethod != 9 && nMethod != 10)
        {
            continue;
        }
        this->SearchEnemy(nMethod);
    }
    if (m_idTarget	!= ID_NONE)
    {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------
void	CPet::SearchEnemy(int nMethod)
{
    m_bRevengeID = false;
    switch(nMethod)
    {
    case 1:
        this->AttackAI_1 ();
        //		this->SearchStatusAsistant();
        break;
    case 2:
        this->AttackAI_2 ();
        //		this->SearchAttackAsistant();
        break;
    case 3:
        this->AttackAI_3 ();
        //		this->SearchEnemyRevenge();
        break;
    case 4:
        this->AttackAI_4 ();
        //		this->SearchEnemyGuard();
        break;
    case 5:
        this->AttackAI_5 ();
        //		this->SearchEnemyWarlike();
        break;
    case 6:
        //		this->SearchEnemyJusticalA();
        this->AttackAI_6();
        break;
    case 7:
        //		this->SearchEnemyJusticalB();
        this->AttackAI_7();
        break;
    case 8:
        //		this->SearchEnemyJusticalC();
        this->AttackAI_8();
        break;
    case 9:
        this->AttackAI_9();
        break;
    case 10:
        this->AttackAI_10();
        break;
    case 11:
        this->AttackAI_11();
        break;
    case 12:
        this->AttackAI_12();
        break;
    case 13:
        this->AttackAI_13();
        break;
    case 14:
        this->AttackAI_14();
        break;
    case 15:
        this->AttackAI_15();
        break;
    case 25:
        this->AttackAI_25();
        break;
    default:
        if (nMethod >= 16 && nMethod <= 24)
        {
            this->AttackAI_16To24(nMethod);
        }
        break;
    }
}
//--------------------------------------------------------------------------------------
void	CPet::CheckTarget()
{
    BOOL bProcess =  false;
    if (!bProcess)
    {
        bProcess = this->CheckTargetDie();
    }
    if (!bProcess)
    {
        bProcess = this->CheckTargetNotFound();
    }
    if (!bProcess)
    {
        bProcess = this->CheckTargetTooFar();
    }
    //	if (!bProcess)
    //		bProcess = this->CheckTargetSpecialCommand();
    //	if (!bProcess)
    //		bProcess = this->CheckTargetElude();
    if (bProcess)
    {
        bProcess = this->SearchEnemy ();
    }
    if (!bProcess)
    {
        m_nBehaviorType = _PET_BEHAVIOR_FIND_HOST;
    }
    else
    {
        this->ProcessAI_FindHost(10);
    }
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckTargetDie()
{
    CPlayer* pTarget = g_objPlayerSet.GetPlayer(m_idTarget, true);
    if (pTarget && pTarget->IsDead())
    {
        m_idTarget = ID_NONE;
        return true;
        //		this->SearchEnemy();
        //		if (m_idTarget != ID_NONE)
        //			return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckTargetNotFound()
{
    CPlayer* pTarget = g_objPlayerSet.GetPlayer(m_idTarget, true);
    if (!pTarget)
    {
        m_idTarget = ID_NONE;
        return true;
        //		this->SearchEnemy();
        //		if (m_idTarget != ID_NONE)
        //			return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckTargetTooFar()
{
    CMyPos posHero, posPet;
    g_objHero.GetPos(posHero);
    this->GetPos(posPet);
    if (abs(posPet.x - posHero.x) > 14 || abs(posPet.y - posHero.y) > 14)
    {
        m_idTarget = ID_NONE;
        return true;
        //		this->SearchEnemy();
        //		if (m_idTarget != ID_NONE)
        //			return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckTargetSpecialCommand()
{
    if (m_idTarget != g_objHero.GetSpecialTarget() && g_objHero.GetSpecialTarget() != ID_NONE)
    {
        OBJID idSpecial = g_objHero.GetSpecialTarget();
        CPlayer* pTarget = g_objPlayerSet.GetPlayer(idSpecial);
        if (pTarget && this->CheckEnemy(pTarget))
        {
            m_idTarget = g_objHero.GetSpecialTarget();
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CheckTargetElude()
{
    return false;
}
//--------------------------------------------------------------------------------------

void	CPet::Idle(DWORD dwDelay)
{
    m_dwIdleEnd = ::TimeGet() + dwDelay;
    m_nBehaviorType = _PET_IDLE;
}
//--------------------------------------------------------------------------------------
void	CPet::Process (void* pInfo)
{
    if (g_objHero.GetIDWhoAttackMe() != m_idTarget && m_bRevengeID)
    {
        m_idTarget = ID_NONE;
        this->StandBy();
    }
    if (this->IsMyPet())
    {
        this->ProcessAI();
    }
    CPlayer::Process(pInfo);
    this->ProcessMagicBusy();
    this->ProcessMagic();
}
//--------------------------------------------------------------------------------------
void	CPet::ProcessAI	()
{
    if (this->IsGhost())
    {
        this->ProcessAI_FindHost();
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(m_idTarget, true);
    if (pPlayer && pPlayer->IsDead())
    {
        this->SetIDWhoAttackMe(ID_NONE);
    }
    if (this->IsAttacking() && pPlayer && !pPlayer->IsDead())
    {
        for(int i = 0; i < NUM_SCALE; i++)
        {
            if (m_nAll[i])
            {
                SearchEnemy(m_nAll[i]);
            }
        }
        this->Idle(1000);
    }
    switch(m_nBehaviorType)
    {
    case _PET_IDLE:
        this->ProcessAI_Idle();
        break;
    case _PET_BEHAVIOR_READY:
        this->ProcessAI_Ready();
        break;
    case _PET_BEHAVIOR_FIND_HOST:
        this->ProcessAI_FindHost();
        break;
    case _PET_MAGICATTACK:
        this->ProcessAI_MagicAtk();
        break;
    case _PET_ATTACK:
        this->ProcessAI_Attack();
        break;
    default:
        break;
    }
    this->ProcessAI_GenerateNewBehavior();
}
//--------------------------------------------------------------------------------------
void	CPet::ProcessAI_Idle()
{
    if (::TimeGet() > m_dwIdleEnd)
    {
        m_nBehaviorType = _PET_BEHAVIOR_READY;
    }
}
//--------------------------------------------------------------------------------------
void	CPet::ProcessAI_Ready()
{
}
//--------------------------------------------------------------------------------------
void	CPet::ProcessAI_Attack()
{
    if (this->IsAttacking())
    {
        return;
    }
    else if (m_idTarget == ID_NONE)
    {
        return;
    }
    else
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(m_idTarget, true);
        if (pPlayer && !pPlayer->IsDead())
        {
            this->LockAttack(pPlayer);
        }
        else
        {
            m_idTarget = ID_NONE;
        }
    }
}
//--------------------------------------------------------------------------------------

void	CPet::ProcessAI_GenerateNewBehavior()
{
    CMyPos posHero, posPet;
    g_objHero.GetPos(posHero);
    this->GetPos(posPet);
    if (m_nBehaviorType == _PET_IDLE)
    {
        return;
    }
    this->CheckTarget();
    /*
    	if (this->CanMagicAtk())
    	{
    		m_nBehaviorType = _PET_MAGICATTACK;
    		return;
    	}*/
    //	else
    if (m_idTarget != ID_NONE)
    {
        m_nBehaviorType = _PET_ATTACK;
        return;
    }
}
//--------------------------------------------------------------------------------------
void	CPet::ProcessAI_FindHost(int nDistance)
{
    CMyPos posPet, posNext, posHero;
    g_objHero.GetPos(posHero);
    this->GetPos(posPet);
    this->GetNextPos(posNext.x, posNext.y);
    if (posNext.x == 0)
    {
        return;
    }
    CellInfo* pCellInfo = g_objGameMap.GetCell(posNext.x, posNext.y);
    CPath objPath;
    g_objGameMap.FindPath(objPath, posPet, posNext);
    if (!pCellInfo || g_objGameMap.GetGroundMask(pCellInfo) == 1 || (!objPath.GetStepAmount() && posPet.x != posNext.x && posPet.y != posNext.y))
    {
        posNext.x = posHero.x + _DELTA_X[::RandGet(8)] * 4 -::RandGet(2);
        posNext.y = posHero.y + _DELTA_Y[::RandGet(8)] * 4 -::RandGet(2);
        g_objGameMap.FindPath(objPath, posPet, posNext);
        if (objPath.GetStepAmount())
        {
            this->SetNextPos(posNext.x, posNext.y);
        }
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(posPet.x, posPet.y);
    if (abs(posHero.x - posPet.x) < nDistance && abs(posHero.y - posPet.y) < nDistance && pPlayer == this
            && posPet.x == posNext.x && posPet.y == posNext.y )
    {
        m_nBehaviorType = _PET_BEHAVIOR_READY;
    }
    else if (!this->IsAttacking())
    {
        /*CellInfo* */pCellInfo = g_objGameMap.GetCell(posPet.x, posPet.y);
        if (!pCellInfo || g_objGameMap.GetGroundMask(pCellInfo) == 1 )
        {
            return;
        }
        if (abs(posHero.x - posPet.x) < 8 && abs(posHero.y - posPet.y) < 8)
        {
            if (this->GetCommandType() == _COMMAND_WALK || this->GetCommandType() == _COMMAND_RUN)
            {
                this->AddStep(posNext);
            }
            else
            {
                this->Run(posNext.x, posNext.y);
            }
        }
        else if (!this->IsMoving() )
        {
            this->Transfer(posNext.x, posNext.y);
        }
    }
}
//--------------------------------------------------------------------------------------
void CPet::AddPetSoul(int nAmount)
{
    OBJID idPetItem = this->GetItemID();
    CItem* pItem  = g_objHero.GetItem(idPetItem);
    if (!pItem)
    {
        return;
    }
    if (!this->IsGhost())
    {
        pItem->SetWarGhostExp(pItem->GetMonsterMaxLife());
        return;
    }
    else
    {
        if (nAmount > 100)
        {
            nAmount = 100;
        }
        DWORD dwCurLife = pItem->GetWarGhostExp() + pItem->GetMonsterMaxLife() * nAmount / 100;
        pItem->SetWarGhostExp(dwCurLife);
    }
    ::PostCmd(CMD_FLASH_MYPETINFO);
}
//--------------------------------------------------------------------------------------
void CPet::ReplaceStatus(__int64 dwStatus)
{
    // die
    if (dwStatus & USERSTATUS_GHOST) //
    {
        if (this->IsPet() && !this->TestStatus(USERSTATUS_GHOST)) //û�������ǻ���
        {
            if (this->GetLook() != 999)
            {
                m_AliveLook = this->GetLook();
            }
            this->m_objEffect.Add("baby_d3");
            this->SetLook(999);
            if (this->IsMyPet())
            {
                this->StandBy();
                CItem* pPet = g_objHero.GetItem(this->GetItemID());
                if (pPet)
                {
                    pPet->SetMonsterDie(true);
                }
                ::PostCmd(CMD_PET_DIE, this->GetID());
            }
        }
    }
    else
    {
        if (this->IsPet() && this->TestStatus(USERSTATUS_GHOST)) //�����ǻ���
        {
            this->m_objEffect.Add("baby_d10");
            this->SetLook((USHORT)m_AliveLook);
            if (this->IsMyPet())
            {
                this->StandBy();
                CItem* pPet = g_objHero.GetItem(this->GetItemID());
                if (pPet)
                {
                    pPet->SetMonsterDie(false);
                }
                ::PostCmd(CMD_PET_ALIVE, this->GetID());
            }
        }
    }
    CPlayer::ReplaceStatus(dwStatus);
}
//--------------------------------------------------------------------------------------
void CPet::LockAttack (CPlayer* pTarget)
{
    if (!pTarget)
    {
        return;
    }
    if (this->IsAttacking())
    {
        return;
    }
    if (this->IsDead() || pTarget->IsDead())
    {
        return;
    }
    if (g_objGameMap.GetType() & MAPTYPE_BOOTH_ENABLE)
    {
        return;
    }
    this->Idle(4000);
    // attack now
    {
        // set lock attck command
        CCommand cmd;
        cmd.iType		= _COMMAND_LOCKATK;
        cmd.iStatus		= _CMDSTATUS_BEGIN;
        cmd.idTarget	= pTarget->GetID();
        this->SetCommand(&cmd);
        m_bFirstAtk = true;
    }
}
//--------------------------------------------------------------------------------------

void	CPet::Transfer(int nPosX, int nPosY)
{
    CMyPos posPet;
    posPet.x = nPosX;
    posPet.y = nPosY;
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(nPosX, nPosY);
    CellInfo* pCellInfo = g_objGameMap.GetCell(nPosX, nPosY);
    if (!pCellInfo ||
            g_objGameMap.GetGroundMask(pCellInfo) == 1 )
    {
        return;
    }
    CMsgAction msg;
    if (msg.Create(this->GetID(), posPet.x, posPet.y, m_Info.cmdProc.nDir, actionJump, posPet.x, posPet.y, m_Info.cmdProc.dwData))
    {
        msg.Send();
    }
    this->SetPos(posPet);
}
//--------------------------------------------------------------------------------------
BOOL	CPet::CanJump(CMyPos posTarGet)
{
    // Can I Jump Over It?
    int nCanJumpHeight =  200;
    //	if (this->TestStatus(USERSTATUS_FLY))
    //		nCanJumpHeight = 100;
    CMyPos posStart, posEnd;
    posEnd = posTarGet;
    DEQUE_CELL setCell;
    this->GetPos(posStart);
    CMyPos posHighest;
    g_objGameMap.Sampling(setCell, posHighest, posStart, posEnd, 32);
    CellInfo* pTargetCell = g_objGameMap.GetCell(posHighest.x, posHighest.y);
    if (!pTargetCell)
    {
        return false;
    }
    CellInfo* pCellInfo = g_objGameMap.GetCell(posStart.x, posStart.y);
    if (!pCellInfo)
    {
        return false;
    }
    if (g_objGameMap.GetGroundAltitude(pTargetCell) - g_objGameMap.GetGroundAltitude(pCellInfo) > nCanJumpHeight)
    {
        return false;
    }
    return true;
}
//--------------------------------------------------------------------------------------
void	CPet::Walk(int nPosX, int nPosY)
{
    int nCommandType = this->GetCommandType();
    if (nCommandType == _COMMAND_ATTACK ||
            nCommandType == _COMMAND_ACTION ||
            nCommandType == _COMMAND_EMOTION ||
            nCommandType == _COMMAND_WOUND ||
            nCommandType == _COMMAND_DEFEND)
    {
        this->ResetActionData();
    }
    if (this->GetCommandType() == _COMMAND_ATTACK)
    {
        this->ResetActionData();
    }
    extern UINT	g_uStatus;
    if (_STATUS_NORMAL != g_uStatus)
    {
        return;
    }
    //	this->AbortIntone();
    if (this->IsDead() && !this->TestStatus(USERSTATUS_GHOST))
    {
        return;
    }
    // prevent repeat the same target point
    CCommand* pcmdNow	= this->GetCommand();
    if (_COMMAND_WALK == pcmdNow->iType)
    {
        if (nPosX ==  pcmdNow->posTarget.x &&
                nPosY ==  pcmdNow->posTarget .y)
        {
            return;
        }
    }
    // set command of role
    CCommand cmd;
    cmd.iType			= _COMMAND_WALK;
    cmd.iStatus			= _CMDSTATUS_BEGIN;
    cmd.posTarget.x		= nPosX;
    cmd.posTarget.y		= nPosY;
    this->SetCommand(&cmd);
}
//--------------------------------------------------------------------------------------
void	CPet::Run(int nPosX, int nPosY)
{
    //	if (this->IsMagicLock())
    //		return;
    if (this->TestStatus(USERSTATUS_CANNOTMOVE))
    {
        return;
    }
    //	this->StopChargeUp();
    int nCommandType = this->GetCommandType();
    if (nCommandType == _COMMAND_ATTACK ||
            nCommandType == _COMMAND_ACTION ||
            nCommandType == _COMMAND_EMOTION ||
            nCommandType == _COMMAND_WOUND ||
            nCommandType == _COMMAND_DEFEND)
    {
        this->ResetActionData();
    }
    //	if (this->TestStatus(USERSTATUS_FLY))
    //	{
    //		this->Jump(nPosX, nPosY);
    //		return;
    //	}
    if (this->GetCommandType() == _COMMAND_ATTACK)
    {
        this->ResetActionData();
    }
    //	if (m_objBoothManager.IsActive())
    //		return;
    extern UINT	g_uStatus;
    if (_STATUS_NORMAL != g_uStatus)
    {
        return;
    }
    //	this->AbortIntone();
    /*
    	if (this->IsDead())
    	{
    		if (this->TestStatus(USERSTATUS_GHOST))
    			this->Walk(nPosX, nPosY);

    		return;
    	}*/
    // prevent repeat the same target point
    CCommand* pcmdNow	= this->GetCommand();
    if (_COMMAND_RUN == pcmdNow->iType)
    {
        if (nPosX ==  pcmdNow->posTarget.x &&
                nPosY ==  pcmdNow->posTarget .y)
        {
            return;
        }
    }
    // here got player already
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(nPosX, nPosY);
    if (pPlayer && !pPlayer->IsDead())
    {
        return;
    }
    // set command of role
    CCommand cmd;
    cmd.iType			= _COMMAND_RUN;
    cmd.iStatus			= _CMDSTATUS_BEGIN;
    cmd.posTarget.x		= nPosX;
    cmd.posTarget.y		= nPosY;
    this->SetCommand(&cmd);
}
//--------------------------------------------------------------------------------------

DWORD	CPet::SetCommand(CCommand* pCommand)
{
    if (!pCommand)
    {
        return 0;
    }
    m_dwCommandIndex++;
    pCommand->dwIndex = m_dwCommandIndex;
    // lock attack ����ɻ���
    if (pCommand->iType == _COMMAND_LOCKATK ||
            pCommand->iType == _COMMAND_WALK ||
            pCommand->iType == _COMMAND_RUN)
    {
        for(int i = 0; i < (int)m_PlayerInfo.setCmd.size(); i ++)
        {
            if (m_PlayerInfo.setCmd[i].iType ==  _COMMAND_LOCKATK ||
                    pCommand->iType == _COMMAND_WALK ||
                    pCommand->iType == _COMMAND_RUN)
            {
                m_PlayerInfo.setCmd.erase(m_PlayerInfo.setCmd.begin() + i);
                break;
            }
        }
    }
    // ���˶������ۻ�
    // dodge�������ۻ�
    if (pCommand->iType == _COMMAND_ACTION)
        if (pCommand->nData == _ACTION_DODGE0 || pCommand->nData == _ACTION_BRUISE0)
        {
            if (m_PlayerInfo.setCmd.size() != 0)
            {
                return false;
            }
        }
    if (pCommand->iType == _COMMAND_INTONE && !pCommand->bAddUp)
    {
        if (m_PlayerInfo.setCmd.size() != 0)
        {
            return false;
        }
    }
    m_PlayerInfo.setCmd.push_back(*pCommand);
    if (_COMMAND_STANDBY != pCommand->iType)
    {
        // attack can be interrupted by Jump, Walk, Run, at any time.
        if (_COMMAND_ATTACK == m_Info.cmdProc.iType ||
                _COMMAND_SHOOT == m_Info.cmdProc.iType ||
                _COMMAND_WOUND == m_Info.cmdProc.iType ||
                _COMMAND_DEFEND == m_Info.cmdProc.iType ||
                _COMMAND_ACTION == m_Info.cmdProc.iType)
        {
            if (pCommand->iType == _COMMAND_WALK ||
                    pCommand->iType == _COMMAND_RUN ||
                    pCommand->iType == _COMMAND_JUMP)
            {
                this->ResetActionData();
            }
        }
        // emotion, standby and action can be interrupted at any time.
        if (_COMMAND_STANDBY == m_Info.cmdProc.iType
                || _COMMAND_EMOTION == m_Info.cmdProc.iType
                || _COMMAND_INTONE == m_Info.cmdProc.iType)
        {
            this->ResetActionData();
        }
        // cmd accomplished can be interrupted at andy time
        if (_CMDSTATUS_ACCOMPLISH == m_Info.cmdProc.iStatus)
        {
            if (_ACTION_STANDBY == m_Info.iActType
                    || _ACTION_ALERT == m_Info.iActType
                    || _ACTION_REST1 == m_Info.iActType
                    || _ACTION_REST2 == m_Info.iActType
                    || _ACTION_REST3 == m_Info.iActType)
            {
                this->ResetActionData();
            }
        }
        // die command can interrupt any command
        if (_COMMAND_DIE == pCommand->iType)
        {
            this->ResetActionData();
        }
    }
    memcpy(&(m_Info.cmdProc), pCommand, sizeof(CCommand));
    return m_dwCommandIndex;
}


//--------------------------------------------------------------------------------------
void	CPet::Jump(int nPosX, int nPosY)
{
    int nCommandType = this->GetCommandType();
    if (nCommandType == _COMMAND_ATTACK ||
            nCommandType == _COMMAND_ACTION ||
            nCommandType == _COMMAND_EMOTION ||
            nCommandType == _COMMAND_WOUND ||
            nCommandType == _COMMAND_DEFEND)
    {
        this->ResetActionData();
    }
    extern UINT	g_uStatus;
    if (_STATUS_NORMAL != g_uStatus)
    {
        return;
    }
    if (this->IsDead())
    {
        return;
    }
    CMyPos posTarget;
    posTarget.x = nPosX;
    posTarget.y = nPosY;
    const OBJID idCanNotJump = 100022;
    const OBJID idCanNotStay = 100023;
    CMyPos posPet;
    this->GetPos(posPet);
    CONST int MAX_JUMPDISTANCE = 16;
    if (MAX_JUMPDISTANCE < g_objGameMap.GetDistance(posPet.x, posPet.y, nPosX, nPosY))
    {
        return;
    }
    if (!this->CanJump(posTarget))
    {
        g_objGameMsg.AddMsg((char*)g_objGameDataSet.GetStr(idCanNotJump));
        return;
    }
    CellInfo* pCellInfo = g_objGameMap.GetCell(nPosX, nPosY);
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(nPosX, nPosY);
    if (!pCellInfo ||
            g_objGameMap.GetGroundMask(pCellInfo) == 1 ||
            (pPlayer && !pPlayer->IsDead()))
    {
        g_objGameMsg.AddMsg((char*)g_objGameDataSet.GetStr(idCanNotStay));
        return;
    }
    if (posPet.x == nPosX && posPet.y == nPosY)
    {
        return;
    }
    // set command of role
    CCommand cmd;
    cmd.iType			= _COMMAND_JUMP;
    cmd.iStatus			= _CMDSTATUS_BEGIN;
    cmd.posTarget.x		= nPosX;
    cmd.posTarget.y		= nPosY;
    cmd.dwData			=::TimeGet();
    this->SetCommand(&cmd);
}
//--------------------------------------------------------------------------------------
BOOL	CPet::ProcessCommand()
{
    int iPosX, iPosY;
    this->GetPos(iPosX, iPosY);
    //--------------------------------------------------------
    if (_COMMAND_JUMP == m_Info.cmdProc.iType)
    {
        if (_CMDSTATUS_BEGIN == m_Info.cmdProc.iStatus)		// is a new jump cmd
        {
            CMsgAction msg;
            if (msg.Create(this->GetID(), iPosX, iPosY, m_Info.cmdProc.nDir, actionJump, m_Info.cmdProc.posTarget.x, m_Info.cmdProc.posTarget.y, m_Info.cmdProc.dwData))
            {
                msg.Send();
            }
        }
    }
    //--------------------------------------------------------
    if (_COMMAND_EMOTION == m_Info.cmdProc.iType)
    {
        if (_CMDSTATUS_BEGIN == m_Info.cmdProc.iStatus)		// is a new emotion cmd
        {
            CMsgAction	msg;
            if (msg.Create(this->GetID(), iPosX, iPosY, m_Info.cmdProc.nDir, actionEmotion, m_Info.cmdProc.nData))
            {
                msg.Send();
            }
        }
    }
    //--------------------------------------------------------
    if (_COMMAND_ATTACK == m_Info.cmdProc.iType)
    {
        if (_CMDSTATUS_BEGIN == m_Info.cmdProc.iStatus)		// is a new atk cmd
        {
            CMsgInteract msg;
            if (msg.Create(INTERACT_ATTACK, this->GetID(), m_Info.cmdProc.idTarget, iPosX, iPosY))
            {
                msg.Send();
            }
        }
    }
    //--------------------------------------------------------
    if (_COMMAND_SHOOT == m_Info.cmdProc.iType)
    {
        if (_CMDSTATUS_BEGIN == m_Info.cmdProc.iStatus)		// is a new atk cmd
        {
            // ת�Ƶ���ͨ����
            m_Info.cmdProc.iType = _COMMAND_ATTACK;
            CMsgInteract msg;
            if (msg.Create(INTERACT_SHOOT, this->GetID(), m_Info.cmdProc.idTarget, m_Info.cmdProc.dwData))
            {
                msg.Send();
                CMagicEffect* pEffect = CMagicEffect::CreateNewArrow(this->GetID(), m_Info.cmdProc.idTarget, m_Info.cmdProc.nData);
                g_objGameMap.AddMagicEffect(pEffect);
            }
        }
    }
    //--------------------------------------------------------
    if (_COMMAND_RUSHATK == m_Info.cmdProc.iType)
    {
        if (_CMDSTATUS_BEGIN == m_Info.cmdProc.iStatus)
        {
            CMsgInteract msg;
            if (msg.Create(INTERACT_RUSHATK, this->GetID(), m_Info.cmdProc.idTarget, iPosX, iPosY, m_Info.cmdProc.posTarget.x, m_Info.cmdProc.posTarget.y))
            {
                msg.Send();
            }
        }
    }
    //--------------------------------------------------------
    // do command now
    //int iStatusBk	=m_Info.cmdProc.iStatus;
    BOOL bAcomplished	= CRole::ProcessCommand();
    //--------------------------------------------------------
    this->GetPos(iPosX, iPosY);
    switch(this->GetActionType())
    {
    case _ACTION_WALKL:
    case _ACTION_WALKR:
        {
            CMyPos posPet;
            this->GetPos(posPet);
            CMsgWalk msg;
            if (msg.Create(this->GetID(), this->GetDir() + 8 *::RandGet(31)))
            {
                msg.Send();
            }
            /*
            			CMsgWalkEx msg;
            			if (msg.Create(this->GetID(),posPet.x, posPet.y, this->GetDir()+8*::RandGet(31)))
            				msg.Send();
            */
        }
        break;
    case _ACTION_RUNL:
    case _ACTION_RUNR:
        {
            CMyPos posPet;
            this->GetPos(posPet);
            CMsgWalk msg;
            if (msg.Create(this->GetID(), this->GetDir() + 8 *::RandGet(31), m_Info.nNextStep))
            {
                msg.Send();
            }
            /*
            			CMsgWalkEx msg;
            			if (msg.Create(this->GetID(),posPet.x, posPet.y ,this->GetDir()+8*::RandGet(31), m_Info.nNextStep))
            				msg.Send();
            */
        }
        break;
    }
    if (this->GetLastCommand() == _COMMAND_LOCKATK &&
            this->GetCommandStatus() == _CMDSTATUS_ACCOMPLISH)
    {
        if (!this->HaveBow())
        {
            CMsgInteract msg;
            if (msg.Create(INTERACT_ATTACK, this->GetID(), m_Info.cmdProc.idTarget, iPosX, iPosY))
            {
                msg.Send();
            }
        }
        else
        {
            CMsgInteract msg;
            if (msg.Create(INTERACT_SHOOT, this->GetID(), m_Info.cmdProc.idTarget, m_Info.cmdProc.dwData))
            {
                msg.Send();
            }
        }
    }
    //--------------------------------------------------------
    return bAcomplished;
}

//--------------------------------------------------------------------------------------
void CPet::AttackAI_1()
{
    OBJID id = g_objHero.GetIDWhoAttackMe ();	//�������˵Ķ���
    if ( id != ID_NONE)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer (id);
        if (pPlayer && this->CheckEnemy (pPlayer, 3))		//�Ƿ������˵�3��֮��
        {
            m_idTarget = id;
            return;
        }
    }
    id = this->GetIDWhoAttackMe ();		//�����Լ��Ķ���
    if (id != ID_NONE)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer (id); //�Ƿ���
        if (pPlayer && !pPlayer->IsDead())
        {
            m_idTarget = id;
            return;
        }
    }
    int nAmount = g_objPlayerSet.GetPlayerAmount ();
    DWORD dwDistance = 100;
    for(int i = 0; i < nAmount; i++)		//�������Լ�����Ķ���
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex (i);
        if (pPlayer && pPlayer->IsMonster () && !pPlayer->IsDead() && !pPlayer->IsGuard ())
        {
            DWORD dwTmpDistance = this->GetDistance (pPlayer);
            if (dwDistance > dwTmpDistance)
            {
                dwDistance = dwTmpDistance;
                m_idTarget = pPlayer->GetID ();
            }
        }
    }
}

void CPet::AttackAI_2 ()
{
    OBJID id = this->GetIDWhoAttackMe (); //�����Լ��Ķ���
    if (id != ID_NONE)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer (id);	//�Ƿ���
        if (pPlayer && !pPlayer->IsDead())
        {
            m_idTarget = id;
            return;
        }
    }
    int nAmount = g_objPlayerSet.GetPlayerAmount ();
    DWORD dwDistance = 100;
    for(int i = 0; i < nAmount; i++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex (i);
        if (pPlayer && !pPlayer->IsDead() && this->CheckEnemy(pPlayer, 5, false)
                && pPlayer->IsMonster () && !pPlayer->IsGuard ())		//�Լ�5��֮�ھ����Լ�����Ķ���
        {
            DWORD dwTmpDistance = this->GetDistance (pPlayer);
            if (dwDistance > dwTmpDistance)
            {
                dwDistance = dwTmpDistance;
                m_idTarget = pPlayer->GetID ();
            }
        }
    }
}

void CPet::AttackAI_3 ()
{
    int nAmount = g_objPlayerSet.GetPlayerAmount ();
    int nWhiteBlack = 0;
    for(int i = 0; i < nAmount; i++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex (i);
        if (pPlayer && pPlayer->IsMonster () && !pPlayer->IsDead() && !pPlayer->IsGuard ())
        {
            CMonsterInfo* pInfo = (CMonsterInfo*)g_obj3DRoleData.GetMonsterInfo(pPlayer->GetName());
            if (pInfo)
            {
                int nTmpWhiteBlack = pInfo->nWhiteBlack;
                if (nWhiteBlack > nTmpWhiteBlack)
                {
                    nWhiteBlack = nTmpWhiteBlack;		//�����ƶ�ֵΪ��ֵ��а�������ȹ�����Ұ��Χ����а��Ĺ���
                    m_idTarget = pPlayer->GetID ();
                }
            }
        }
    }
}

void CPet::AttackAI_4 ()
{
    BOOL bCanAtk = false;
    if (m_idTarget != ID_NONE )
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(m_idTarget);
        if (pPlayer && !pPlayer->IsDead())
        {
            if (this->GetAtkTime(m_idTarget) >= 3) //�������¾ͻỻһ������Ŀ��
            {
                m_nAtkTime = 0;
                bCanAtk = true;
            }
        }
        else
        {
            m_idTarget = ID_NONE;
        }
    }
    if (m_idTarget == ID_NONE)
    {
        bCanAtk = true;
    }
    if (!bCanAtk)
    {
        return;
    }
    if (bCanAtk)
    {
        OBJID idWhoAttackMe = g_objHero.GetIDWhoAttackMe();	//�������ڹ������˵Ĺ���
        if (idWhoAttackMe != m_idTarget)
        {
            CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idWhoAttackMe);
            if (pPlayer && !pPlayer->IsDead())
            {
                m_idTarget = idWhoAttackMe;
                return;
            }
        }
        int i = 0, nAmount = g_objPlayerSet.GetPlayerAmount();
        for(; i < nAmount ; i++)
        {
            CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
            if (pPlayer
                    && pPlayer->GetID() != this->GetID() && !pPlayer->IsDead()//�������ڹ������˵Ĺ���
                    && ( pPlayer->IsPlayer() || pPlayer->IsPet()) )
            {
                idWhoAttackMe = pPlayer->GetIDWhoAttackMe();
                CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idWhoAttackMe);
                if (pPlayer && !pPlayer->IsDead())
                {
                    if (m_idTarget != idWhoAttackMe)
                    {
                        m_idTarget = idWhoAttackMe;
                        return;
                    }
                }
            }
        }
        if (i == nAmount)
        {
            m_idTarget = ID_NONE;
            this->Idle(4000);
        }
    }
}

void CPet::AttackAI_5 ()
{
    int nLevHero, nLevMe, nLevOther;
    OBJID idWhoAttackHero, idWhoAttackMe, idWhoAttackOther;
    idWhoAttackHero = 0;
    idWhoAttackMe = 0;
    idWhoAttackOther = 0;
    nLevOther = nLevHero = nLevMe = 120;
    OBJID idWhoAttack = g_objHero.GetIDWhoAttackMe();	//�������ڹ������˵Ĺ���
    if (idWhoAttack != m_idTarget)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idWhoAttack);
        if (pPlayer && !pPlayer->IsDead())
        {
            idWhoAttackHero = idWhoAttack;
            nLevHero = pPlayer->GetLev();
        }
    }
    idWhoAttack = this->GetIDWhoAttackMe();		//�����Լ��Ļ���
    if (idWhoAttack != m_idTarget)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idWhoAttack);
        if (pPlayer && !pPlayer->IsDead() )
        {
            idWhoAttackMe = idWhoAttack;
            nLevMe = pPlayer->GetLev();
        }
    }
    int nAmount = g_objPlayerSet.GetPlayerAmount();
    for(int i = 0 ; i < nAmount ; i++)
    {
        CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer
                && pPlayer->GetID() != this->GetID()	//�������ڹ������˱�Ļ��޵Ĺ���
                && pPlayer->IsMyPet() )
        {
            idWhoAttack = pPlayer->GetIDWhoAttackMe();
            CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idWhoAttackMe);
            if (pPlayer && !pPlayer->IsDead() )
            {
                if ( (int)pPlayer->GetLev() < nLevOther )
                {
                    idWhoAttackOther = idWhoAttack;
                    nLevOther = pPlayer->GetLev();
                }
            }
        }
    }
    int nLevPet = 0;
    CItem* pPet = g_objHero.GetItem(this->GetItemID());
    if (pPet == NULL)
    {
        return;
    }
    else
    {
        nLevPet = pPet->GetAmountLimit();
    }
    OBJID idRunAway = 0;	//�Ƿ�Ҫ����?
    if (idWhoAttackHero && nLevHero <= nLevMe && nLevHero <= nLevOther )	 //���ȹ���Ŀ����ȼ���͵ĵ���
    {
        if (nLevPet >= nLevHero - 5)
        {
            m_idTarget = idWhoAttackHero;
            return;
        }
        else
        {
            idRunAway = idWhoAttackHero;
        }
    }
    if (idWhoAttackMe && nLevMe < nLevHero && nLevMe <= nLevOther)
    {
        if (nLevPet >= nLevMe - 5)
        {
            m_idTarget = idWhoAttackMe;
            return;
        }
        else
        {
            idRunAway = idWhoAttackMe;
        }
    }
    if (idWhoAttackOther && nLevOther < nLevMe && nLevOther < nLevHero)
    {
        if (nLevPet >= nLevOther - 5)
        {
            m_idTarget = idWhoAttackOther;
            return;
        }
        else
        {
            idRunAway = idWhoAttackOther;
        }
    }
    if (idRunAway)	//���ܴ���
    {
        CMyPos posTarget, posPet;
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idRunAway);
        if (pPlayer && !pPlayer->IsDead())
        {
            pPlayer->GetPos(posTarget);
        }
        else
        {
            return;
        }
        this->GetPos(posPet);
        const int MIN_DISTANCE = 8;
        if (g_objGameMap.GetDistance(posTarget.x, posTarget.y, posPet.x, posPet.y) <= MIN_DISTANCE)
            //	if (abs(posTarget.x - posPet.x) < 8 && abs(posTarget.y - posPet.y) < 8 && pPlayer== this)
        {
            if (!this->IsMoving())
            {
                CMyPos posPetTarget;
                int nDir = ::RandGet(8);
                posPetTarget.x = posTarget.x + _DELTA_X[nDir] * 4 -::RandGet(2);
                posPetTarget.y = posTarget.y + _DELTA_Y[nDir] * 4 -::RandGet(2);
                CellInfo* pCellInfo = g_objGameMap.GetCell(posPet.x, posPet.y);
                if (!pCellInfo ||
                        g_objGameMap.GetGroundMask(pCellInfo) == 1 )
                {
                    return;
                }
                //				if (abs(posPetTarget.x - posPet.x) < 8 && abs(posPetTarget.y - posPet.y) < 8)
                this->Run(posPetTarget.x, posPetTarget.y);
            }
        }
        else
        {
            return;
        }
    }
}

//���޹���ͬһĿ��Ĺ������� --���3��
void CPet::SetAtkTarget (OBJID idTarget)
{
    if ( 0 == idTarget)
    {
        return;
    }
    if (idTarget == m_idAtkTarget)
    {
        //		if (m_nAtkTime < 3)
        {
            m_nAtkTime++;
        }
    }
    else
    {
        m_idAtkTarget = idTarget;
        m_nAtkTime = 0;
    }
}
/**************************************************************************
*void CPet::AttackAI_6()	lw
*����������Ұ��Χ�ڵĹ�����ȳ嵽��Ұ��Χ�ڹ������ܼ��ĵ��˹�����
**************************************************************************/
void CPet::AttackAI_6()
{
    typedef struct PlayerInfo
    {
        int nNum;
        OBJID nTargetID;
    } PLAYERINFO;
    int nAmount = g_objPlayerSet.GetPlayerAmount(), nDir;
    if (nAmount <= 0)
    {
        return;
    }
    PLAYERINFO setPlayer[8];
    ZeroMemory(setPlayer, sizeof(PLAYERINFO) * 8);
    CPlayer* pPlayer = NULL;
    CMyPos posPlayer, posHero;
    g_objHero.GetPos(posHero);
    const int MAX_PLAYER = 9;
    //���PLAYER�����ڣ����������ѡ����Ŀ�꣬���ڣ���ֱ����PLAYER�������Ŀ��
    if (nAmount > MAX_PLAYER)
    {
        for(int i = 0, j = 0; i < MAX_PLAYER && j < nAmount; j++)
        {
            pPlayer = g_objPlayerSet.GetPlayerByIndex(RandGet(nAmount));
            if (pPlayer && pPlayer->IsMonster() && !pPlayer->IsGuard () && this->CheckEnemy(pPlayer))
            {
                i++;
                pPlayer->GetPos(posPlayer);
                nDir = g_objGameMap.GetDirection(posHero.x, posHero.y, posPlayer.x, posPlayer.y);
                setPlayer[nDir].nNum++;
                setPlayer[nDir].nTargetID = pPlayer->GetID();
            }
        }
    }
    else
    {
        for(int i = 0; i < nAmount ; i++)
        {
            pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
            if (pPlayer && pPlayer->IsMonster() && !pPlayer->IsGuard () && this->CheckEnemy(pPlayer))
            {
                pPlayer->GetPos(posPlayer);
                nDir = g_objGameMap.GetDirection(posHero.x, posHero.y, posPlayer.x, posPlayer.y);
                setPlayer[nDir].nNum++;
                setPlayer[nDir].nTargetID = pPlayer->GetID();
            }
        }
    }
    //�ж��Ǹ������Ŀ����࣬ȷ��������Ŀ��
    OBJID id = ID_NONE;
    int nNum = 0;
    for(int i = 0; i < 8; i++)
    {
        if (setPlayer[i].nNum > nNum)
        {
            nNum = setPlayer[i].nNum;
            id = setPlayer[i].nTargetID;
        }
    }
    m_idTarget = id;
#ifdef LW_DEBUG
    if (m_idTarget == ID_NONE)
    {
        return;
    }
    static int n = 0;
    n++;
    g_objGameMsg.AddMsg(_TXTATR_TALK, "ִ��attack_6������%d\n", n);
#endif
}
/**************************************************************************
*void CPet::AttackAI_7()	lw
*������Ұ��Χ�ڵĹ�����ȹ������ڹ����Լ��ĵ��ˣ�������ȹ������ڹ������˵ĵ��ˡ�
**************************************************************************/
void CPet::AttackAI_7()
{
    // �Թ����Լ���ΪĿ��
    OBJID id = this->GetIDWhoAttackMe();
    // ���û�й����Լ���Ŀ�꣬�ҹ���Hero��ΪĿ��
    if (id == ID_NONE)
    {
        id = g_objHero.GetIDWhoAttackMe();
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(id);
    if (pPlayer && !pPlayer->IsDead())
    {
        m_idTarget = pPlayer->GetID();
    }
    else
    {
        int nAmount = g_objPlayerSet.GetPlayerAmount();
        for(int i = 0; i < nAmount ; i++)
        {
            pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
            if (pPlayer && !pPlayer->IsDead() && pPlayer->IsMonster() && !pPlayer->IsGuard ())
            {
                m_idTarget = pPlayer->GetID();
                return;
            }
        }
    }
}
/**************************************************************************
*void CPet::AttackAI_8()	lw
*������Ұ�ڵ��κε��ˣ�û�й̶�����Ŀ�꣬ÿ�ζ����������Ұ��Χ�ڵ�һ�����ˡ�
**************************************************************************/
void CPet::AttackAI_8()
{
    // �Ȳ��ҹ���Hero��
    OBJID id = g_objHero.GetIDWhoAttackMe();
    // ���û�У����ҹ����Լ���
    if (id == ID_NONE)
    {
        id = this->GetIDWhoAttackMe();
    }
    if (id == ID_NONE)
    {
        return;
    }
    int nAmount = g_objPlayerSet.GetPlayerAmount();
    CPlayer* pPlayer = g_objPlayerSet.GetPlayerByIndex(RandGet(nAmount));
    if (!pPlayer)
    {
        return;
    }
    if (pPlayer->IsDead())
    {
        return;
    }
    if (this->CheckEnemy(pPlayer))
    {
        m_idTarget = id;
    }
}
/**************************************************************************
*void CPet::AttackAI_9()	lw
*Ŀ�꿿���Լ�5��ͻ��ܿ�5��Ȼ���ٹ�������ʼ�ձ��ָ�Ŀ�����5�����ϡ�
**************************************************************************/
void CPet::AttackAI_9()
{
    if (m_idTarget == ID_NONE)
    {
        return;
    }
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(m_idTarget);
    CMyPos posTarget, posPet;
    pPlayer->GetPos(posTarget);
    this->GetPos(posPet);
    const int MIN_DISTANCE = 5;
    if (g_objGameMap.GetDistance(posTarget.x, posTarget.y, posPet.x, posPet.y) <= MIN_DISTANCE)
    {
        CMyPos posMove, posHero;
        g_objHero.GetPos(posHero);
        int nDir = g_objGameMap.GetDirection(posHero.x, posHero.y, posTarget.x, posTarget.y);
        CellInfo* pCellInfo = NULL;
        //�����һ���������ҵ���λ�ò��ɴ������һ��������������
        for(int i = 0; i < 5; i++)
        {
            posMove.x = posTarget.x + _DELTA_X[nDir] * MIN_DISTANCE;
            posMove.y = posTarget.y + _DELTA_Y[nDir] * MIN_DISTANCE;
            //       OBJID id = m_idTarget;
            pCellInfo = g_objGameMap.GetCell(posMove.x, posMove.y);
            if (!pCellInfo || g_objGameMap.GetGroundMask(pCellInfo) == 1)
            {
                nDir = (++nDir) % 8;
            }
            else
            {
                break;
            }
        }
        //����ҵ����ƶ���λ�ã����ߵ�Ŀ�괦
        if (pCellInfo && g_objGameMap.GetGroundMask(pCellInfo) != 1)
        {
            this->Run(posMove.x, posMove.y);
        }
        //		m_idTarget = id;
    }
}
/**************************************************************************
*void CPet::AttackAI_10()	lw
*ÿ����һ�ξ������8�������е�һ�������ƶ�3�񣬵������뿪����10��ķ�Χ��
**************************************************************************/
void CPet::AttackAI_10()
{
    if (m_idTarget == ID_NONE)
    {
        return;
    }
    const int MAX_SEARCH = 5, MOVE_DISTANE = 3;
    CellInfo* pCellInfo = NULL;
    int nDir = RandGet(8);
    CMyPos posMove, posPet, posHero;
    g_objHero.GetPos(posHero);
    //�����һ���������ҵ���λ�ò��ɴ������һ��������������
    for(int i = 0; i < MAX_SEARCH; i++)
    {
        this->GetPos(posPet);
        posMove.x = posPet.x + _DELTA_X[nDir] * MOVE_DISTANE;
        posMove.y = posPet.y + _DELTA_Y[nDir] * MOVE_DISTANE;
        //       OBJID id = m_idTarget;
        pCellInfo = g_objGameMap.GetCell(posMove.x, posMove.y);
        if (!pCellInfo || g_objGameMap.GetGroundMask(pCellInfo) == 1 ||
                g_objGameMap.GetDistance(posMove.x, posMove.y, posHero.x, posHero.y) > 10)
        {
            nDir = (++nDir) % 8;
        }
        else
        {
            break;
        }
    }
    //����ҵ����ƶ���λ�ã����ߵ�Ŀ�괦
    if (pCellInfo && g_objGameMap.GetGroundMask(pCellInfo) != 1 )
    {
        this->Run(posMove.x, posMove.y);
#ifdef LW_DEBUG
        static int n = 0;
        n++;
        g_objGameMsg.AddMsg(_TXTATR_TALK, "ִ��attack_10������%d\n", n);
#endif
    }
}
/**************************************************************************
*void CPet::AttackAI_11()	lw
*ʼ�����������3���ڣ������뿪�����Χ������Ǽ�����ͣ����������
**************************************************************************/
void CPet::AttackAI_11()
{
    const int MAX_DISTANCE = 3;
    CMyPos posHero, posPet;
    g_objHero.GetPos(posHero);
    this->GetPos(posPet);
    CPlayer* pPlayer = g_objPlayerSet.GetPlayer(posPet.x, posPet.y);
    if (abs(posHero.x - posPet.x) <= MAX_DISTANCE && abs(posHero.y - posPet.y) <= MAX_DISTANCE )
    {
        m_nBehaviorType = _PET_BEHAVIOR_READY;
    }
    else if (!this->IsMoving())
    {
        CMyPos posPetTarget;
        int nDir = ::RandGet(8);
        posPetTarget.x = posHero.x + _DELTA_X[nDir] * 3 -::RandGet(2);
        posPetTarget.y = posHero.y + _DELTA_Y[nDir] * 3 -::RandGet(2);
        CellInfo* pCellInfo = g_objGameMap.GetCell(posPet.x, posPet.y);
        if (!pCellInfo ||
                g_objGameMap.GetGroundMask(pCellInfo) == 1 )
        {
            return;
        }
        if (abs(posHero.x - posPet.x) < 8 && abs(posHero.y - posPet.y) < 8)
        {
            this->Run(posPetTarget.x, posPetTarget.y);
        }
        else
        {
            this->Transfer(posPetTarget.x, posPetTarget.y);
        }
    }
}
/**************************************************************************
*void CPet::AttackAI_12()	lw
*�������ƶ���ʱ���е��˿�������8���ڣ�����5�����ʱ�����ڵ��˿������Ǹ���
*��������4����Ѳ�ߡ�ÿ��3��Ѳ��һ�Ρ�����е��˿�������5���ڣ���������Ч��
**************************************************************************/
void CPet::AttackAI_12()
{
    //	if (_COMMAND_STANDBY == g_objHero.GetLastCommand())
    //		return;
    CMyPos posHero, posFind, posTarget;
    g_objHero.GetPos(posHero);
    CPlayer* pPlayer;
    bool isPatrol = false;
    //�����Ƿ��е��˿�������5����,���򷵻�
    for(int i = 0; i < g_objPlayerSet.GetPlayerAmount(); i++)
    {
        pPlayer = g_objPlayerSet.GetPlayerByIndex(i);
        if (pPlayer && this->CheckEnemy(pPlayer))
        {
            pPlayer->GetPos(posFind);
            if (abs(posHero.x - posFind.x) < 5 && abs(posHero.y - posFind.y) < 5)
            {
                return;
            }
            if (!isPatrol && abs(posHero.x - posFind.x) < 8 && abs(posHero.y - posFind.y) < 8)
            {
                posTarget = posFind;
                isPatrol = true;
            }
        }
    }
    //���û�а˸����ڵĵ��ˣ�Ҳ��ҪѲ�ߣ�����
    if (!isPatrol)
    {
        return;
    }
    // set command of role
    //	int nDistance = g_objGameMap.GetDistance(posHero.x,posHero.y,posTarget.x,posTarget.y);
    isPatrol = false;
    int nDir = g_objGameMap.GetDirection(posHero.x, posHero.y, posTarget.x, posTarget.y);
    CellInfo* pCellInfo = NULL;
    CMyPos posMove;
    for (int i = 0; i < 3; i++)
    {
        posMove.x = posHero.x + _DELTA_X[nDir] * (abs(posHero.x - posTarget.x) / 2 + i);
        posMove.y = posHero.y + _DELTA_Y[nDir] * (abs(posHero.y - posTarget.y) / 2 + i);
        pCellInfo = g_objGameMap.GetCell(posMove.x, posMove.y);
        if (pCellInfo && g_objGameMap.GetGroundMask(pCellInfo) != 1)
        {
            isPatrol = true;
            break;
        }
    }
    //����ҵ����ƶ���λ�ã����ߵ�Ŀ�괦
    if (isPatrol)
    {
        this->Run(posMove.x, posMove.y);
#ifdef LW_DEBUG
        static int n = 0;
        n++;
        g_objGameMsg.AddMsg(_TXTATR_TALK, "ִ��attack_12������%d\n", n);
#endif
    }
    CCommand cmd;
    cmd.iType			= _COMMAND_STANDBY;
    cmd.iStatus			= _CMDSTATUS_BEGIN;
    cmd.posTarget.x		= 0;
    cmd.posTarget.y		= 0;
    cmd.dwData			=::TimeGet();
    this->SetCommand(&cmd);
}
/**************************************************************************
*void CPet::AttackAI_13()	lw
*�����˳������ƶ�ʱ��ʼ�����������6���ڣ������뿪�����Χ���������������룬������ȥ��
**************************************************************************/
void CPet::AttackAI_13()
{
    ProcessAI_FindHost();
}
/**************************************************************************
*void CPet::AttackAI_14()	lw
*û�й���Ŀ��ʱ������������8���ڵĵط���Ϣ��
**************************************************************************/
void CPet::AttackAI_14()
{
    //�����Ŀ���򷵻�
    if (m_idTarget)
    {
        return;
    }
    // set command of role
    CCommand cmd;
    cmd.iType		= _COMMAND_EMOTION;
    cmd.iStatus		= _CMDSTATUS_BEGIN;
    cmd.nData		= _ACTION_SITDOWN;
    this->SetCommand(&cmd);
}
/**************************************************************************
*void CPet::AttackAI_15()	lw
*��������ʱ����70%�Ļ����ƿ�5����30%�Ļ��ʹ�����
**************************************************************************/
void CPet::AttackAI_15()
{
    OBJID id  = this->GetIDWhoAttackMe();
    if (id == ID_NONE)
    {
        return;
    }
    if (RandGet(100) >= 70)
    {
#ifdef LW_DEBUG
        g_objGameMsg.AddMsg(_TXTATR_TALK, "AttackAI_15 ����\n");
#endif
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(id);
        if (!pPlayer)
        {
            return;
        }
        if (pPlayer->IsDead())
        {
            return;
        }
        if (this->CheckEnemy(pPlayer))
        {
            m_idTarget = id;
        }
    }
    else
    {
        CMyPos posMove, posTarget, posPet;
        CPlayer* pPlayer = g_objPlayerSet.GetPlayer(id);
        if (!pPlayer)
        {
            return;
        }
        pPlayer->GetPos(posTarget);
        this->GetPos(posPet);
        int nDir = g_objGameMap.GetDirection(posTarget.x, posTarget.y, posPet.x, posPet.y);
        CellInfo* pCellInfo = NULL;
        for(int i = 0; i < 3; i++)
        {
            this->GetPos(posPet);
            posMove.x = posPet.x + _DELTA_X[nDir] * 5;
            posMove.y = posPet.y + _DELTA_Y[nDir] * 5;
            pCellInfo = g_objGameMap.GetCell(posMove.x, posMove.y);
            if (!pCellInfo || g_objGameMap.GetGroundMask(pCellInfo) == 1	)
            {
                //ֻ������������Ŀ����Լ������ϵķ������ڵ����ҷ���
                if (i == 1)
                {
                    nDir = (nDir + 1) % 8;
                }
                else if (i == 2)
                {
                    nDir = (nDir - 2) % 8;
                }
            }
            else
            {
                break;
            }
        }
        //����ҵ����ƶ���λ�ã����ߵ�Ŀ�괦
        if (pCellInfo && g_objGameMap.GetGroundMask(pCellInfo) != 1 )
        {
            this->Run(posMove.x, posMove.y);
            this->SetIDWhoAttackMe(ID_NONE);
            m_idTarget = ID_NONE;
#ifdef LW_DEBUG
            static int n = 0;
            n++;
            g_objGameMsg.AddMsg(_TXTATR_TALK, "ִ��attack_15�ƿ���%d\n", n);
#endif
        }
    }
}
/**************************************************************************
*void CPet::AttackAI_25 (int nMethod)	lw
**************************************************************************/
void    CPet::AttackAI_25()
{
    OBJID idAttack;
    idAttack = g_objHero.GetIDMyTarget();
    if (idAttack && g_objPlayerSet.GetPlayer(idAttack) && !g_objPlayerSet.GetPlayer(idAttack)->IsDead())
    {
        m_idTarget = idAttack;
        return;
    }
    idAttack = g_objHero.GetIDWhoAttackMe();	//�������ڹ������˵Ĺ���
    if (idAttack && g_objPlayerSet.GetPlayer(idAttack) && !g_objPlayerSet.GetPlayer(idAttack)->IsDead())
    {
        m_idTarget = idAttack;
        return;
    }
    idAttack = this->GetIDWhoAttackMe();		//�����Լ��Ļ���
    if (idAttack && g_objPlayerSet.GetPlayer(idAttack) && !g_objPlayerSet.GetPlayer(idAttack)->IsDead())
    {
        m_idTarget = idAttack;
        return;
    }
    int nAmount = g_objHero.GetCallPetAmount();
    for(int i = 0 ; i < nAmount ; i++)
    {
        CPet* pPet = g_objHero.GetPetByIndex(i);
        if (pPet && pPet->GetID() != this->GetID())	//�������ڹ������˱�Ļ��޵Ĺ���
        {
            idAttack = pPet->GetIDWhoAttackMe();
            CPlayer* pPlayer = g_objPlayerSet.GetPlayer(idAttack);
            if (idAttack && pPlayer && !pPlayer->IsDead())
            {
                m_idTarget = idAttack;
                return;
            }
        }
    }
    m_idTarget = NULL;
}
/**************************************************************************
*void CPet::AttackAI_16To24 (int nMethod)	lw
**************************************************************************/
void CPet::AttackAI_16To24 (int nMethod)
{
    OBJID id = g_objHero.GetIDWhoAttackMe();
    if (id == ID_NONE)
    {
        id = m_idHeroTarget;
    }
    if (id == ID_NONE)
    {
        return;
    }
    CPlayer* pPet, *pPlayer = g_objPlayerSet.GetPlayer(id);
    if (!pPlayer || !pPlayer->IsPlayer() || pPlayer->IsDead())
    {
        return;
    }
    if (nMethod != 24)
    {
        int nAmount = g_objPlayerSet.GetPlayerAmount();
        OBJID idPet;
        bool isFind = false;
        //��������ָ����ҵ��ض����͵Ļ���
        for(int n = 0; n < nAmount; n++)
        {
            pPet = g_objPlayerSet.GetPlayerByIndex(n);
            if (!pPet)
            {
                continue;
            }
            if (pPet->IsPet() && pPet->GetPetOwnerId() == pPlayer->GetID())
            {
                idPet = pPet->GetMonsterTypeId();
                if (idPet == ID_NONE)
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
            if (nMethod == 16) //�ٶ��ͻ���
            {
                if (idPet == 90022 || idPet == 90023 || idPet == 90111 ||
                        idPet == 90112 || idPet == 90113 || idPet == 90114 ||
                        idPet == 90115 || idPet == 90116 || idPet == 90117 ||
                        idPet == 90118
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 17)//ħ���ͻ���
            {
                if (idPet == 90008 || idPet == 90028 || idPet == 90029 ||
                        idPet == 90141 || idPet == 90142 || idPet == 90143 ||
                        idPet == 90144 || idPet == 90145 || idPet == 90146 ||
                        idPet == 90147 || idPet == 90148
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 18)//�����ͻ���
            {
                if (idPet == 90012 || idPet == 90032 || idPet == 90033 ||
                        idPet == 90161 || idPet == 90162 || idPet == 90163 ||
                        idPet == 90164 || idPet == 90165 || idPet == 90166 ||
                        idPet == 90167 || idPet == 90168
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 19)//�����ͻ���
            {
                if (idPet == 90000 || idPet == 90020 || idPet == 90021 ||
                        idPet == 90101 || idPet == 90102 || idPet == 90103 ||
                        idPet == 90104 || idPet == 90105 || idPet == 90106 ||
                        idPet == 90107 || idPet == 90108
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 20)//�����ͻ���
            {
                if (idPet == 90010 || idPet == 90030 || idPet == 90031 ||
                        idPet == 90151 || idPet == 90152 || idPet == 90153 ||
                        idPet == 90154 || idPet == 90155 || idPet == 90156 ||
                        idPet == 90157 || idPet == 90158
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 21)//�����ͻ���
            {
                if (idPet == 90014 || idPet == 90034 || idPet == 90035 ||
                        idPet == 90171 || idPet == 90172 || idPet == 90173 ||
                        idPet == 90174 || idPet == 90175 || idPet == 90176 ||
                        idPet == 90177 || idPet == 90178
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 22)//�����ͻ���
            {
                if (idPet == 90004 || idPet == 90024 || idPet == 90025 ||
                        idPet == 90121 || idPet == 90122 || idPet == 90123 ||
                        idPet == 90124 || idPet == 90125 || idPet == 90126 ||
                        idPet == 90127 || idPet == 90128
                   )
                {
                    isFind = true;
                    break;
                }
            }
            else if (nMethod == 23)//�����ͻ���
            {
                if (idPet == 90006 || idPet == 90026 || idPet == 90027 ||
                        idPet == 90131 || idPet == 90132 || idPet == 90133 ||
                        idPet == 90134 || idPet == 90135 || idPet == 90136 ||
                        idPet == 90137 || idPet == 90138
                   )
                {
                    isFind = true;
                    break;
                }
            }
        }
        if (isFind)
        {
            m_idTarget = pPet->GetID();
        }
    }
    else//��������ڹ���������һ�������ҹ�����ʱ�򡣹��������ҡ�
    {
        m_idTarget = id;
    }
}

