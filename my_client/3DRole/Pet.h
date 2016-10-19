
//**********************************************************
// ����༭��
//**********************************************************

//--------------------------------------------------------------------------------------
// File Name: pet.h
// Create by: Huang Yuhang
// Create on: 2003/8/25 15:00
//--------------------------------------------------------------------------------------
#ifndef _PET_H
#define _PET_H

#include "Player.h"
#include "Magic.h"
#include "3DRoleData.h"
const int NUM_SCALE = 4;  //��Ҫÿ��ѭ����ִ�е�AI����
class CPet	: public CPlayer
{
public:
    // ״̬
    enum {_PET_IDLE, _PET_BEHAVIOR_READY, _PET_BEHAVIOR_FIND_HOST, _PET_ATTACK, _PET_MAGICATTACK};
    // Ѱ�ķ�ʽ
    enum
    {
        _PET_SE_STATUS_ASSISTANT	=	1,	//	Ŀ��ΪHero������״̬�������ٻ���
        _PET_SE_ATTACK_ASSISTANT	=	2,	//	��Hero��Ŀ��ΪĿ�꣬���ڹ��������ٻ���
        _PET_SE_REVENGE				=	3,	//	�Թ�����ΪĿ�꣬��������
        _PET_SE_GUARD				=	4,	//	�Կ���Hero�Ĺ���ΪĿ�꣬��ս����
        _PET_SE_WARLIKE				=	5,	//	Ѱ�����Լ�����ĵ���ս��, ��ս����
        _PET_SE_JUSTICAL_A			=	6,	//	Ѱ�Һ��������ս������������A
        _PET_SE_JUSTICAL_B			=	7,	//	Ѱ�Һ��������ս������������B
        _PET_SE_JUSTICAL_C			=	8,	//	Ѱ�����������ս������������C
    };
    // ��������
    enum
    {
        _PET_ENV_ELUDE				=	1,	// ��ܵ���		 ���ʺ�Զ�̹�����
        _PET_ENV_FEARLESS			=	2,	// ��η��		 ���ʺϽ��̹�����
    };
    enum {_NORMAL_MAGIC = 1, _ALTITUTE_MAGIC = 2, _UITIMATE_MAGIC = 3, _COMBO_MAGIC = 4};
    //��ͨ����			�߼�����			 �ռ�����			  ���弼��
public:
    CPet();
    virtual ~CPet();

    void	Init	(void);
    void	Reset	(void);
    int		GetAtkRange	(void);
    //void	SetAlignPos(int nX, int nY);
public:
    void	LockAttack		(CPlayer* pTarget);
    void	Walk			(int nPosX, int nPosY);
    void	Run				(int nPosX, int nPosY);
    void	Transfer		(int nPosX, int nPosY);
    void	Jump			(int nPosX, int nPosY);

    //	void	Direction		(int nPosX, int nPosY);
    //	void	Stop			(void);
    DWORD	SetCommand		(CCommand* pCommand);
    BOOL	ProcessCommand	();

    void	Process		(void* pInfo);
    void	ProcessAI	();

    BOOL	CanJump(CMyPos posTarGet);
    void	SetAIType(int nType);

    void	SetAtkTarget(OBJID idTarget) ;
    int		GetAtkTime(OBJID idTarget) {if (idTarget == m_idAtkTarget) { return m_nAtkTime; } else { return 0; }}
public:
    static CPet*	CreateNewPet	(OBJID idPet, int nType, OBJID idItem);
    void	SetItemID (OBJID idItem) {m_idItem = idItem;}
    OBJID   GetItemID ( ) { return m_idItem;}
public:
    void	ReplaceStatus(__int64 dwStatus);
    void    ProcessMagic();
    void    ProcessMagicBusy();
    void    StartMagicBusy(DWORD dwDuration);
    void	EndMagicBusy();
    BOOL	IsMagicAttackBusy() {return m_bMagicAttackBusy || this->IsMagicLock();}

    BOOL   CanMagicAtk();	//���ؿ���ʹ�õ�ħ��id
    BOOL	CheckMagicAI(OBJID idMagicType);  //���ħ����ai
    void	MagicLock() {m_bMagicLock = true;}
    void	UnMagicLock() {m_bMagicLock = false;}
    BOOL	IsMagicLock() {return m_bMagicLock;}

    BOOL	MagicAttack(OBJID idMagicType, OBJID idPlayer, BOOL bForce = false);
    void	MagicAttack(OBJID idMagicType, CMyPos posTarget);
    int		GetPetMagicSort(OBJID idMagicType);
    void	AddMagic(OBJID idMagic, DWORD dwLevel, DWORD dwExp);
    int		GetMagicAmount(int nSort = 0);
    CMagic*   GetMagicByIndex(int nIndex, int nSort = 0);
    CMagic*   GetMagic(OBJID idMagicType);
    OBJID   GetIDMyTarget() {return m_idAtkTarget;}
    void	AddPetSoul(int nAmount);
private:
    OBJID   m_idItem;		//���޵���ƷID

    OBJID   m_idAtkTarget;
    OBJID	m_idMagicType;
    int		m_nAtkTime;

    DWORD	m_AliveLook;

    VECTOR_MAGIC		m_setMagic;
    DWORD				m_dwMagicAttackBegin;
    DWORD				m_dwMagicAttackBusy;
    BOOL				m_bMagicAttackBusy;
    BOOL				m_bMagicLock;

    void   DestroyMagicSet();
    // for AI
private:
    int		m_nBehaviorType;
    DWORD	m_dwIdleEnd;
    OBJID	m_idTarget;
    PetInfo m_AIInfo;

    OBJID	m_idHeroTarget;
    BOOL	m_bRevengeID;
    int     m_nAll[NUM_SCALE];//�Ƿ�ÿ��ѭ������AI
public:
    BOOL	m_bFirstAtk;
    void	SetHeroTarget(OBJID idTarger) {m_idHeroTarget = idTarger;}
private:
    // Ѱ�Ĳ���
    BOOL	SearchEnemy();
    void	SearchEnemy(int nMethod);

    void	SearchStatusAsistant();
    void	SearchAttackAsistant();
    void	SearchEnemyRevenge();
    void	SearchEnemyGuard();
    void	SearchEnemyWarlike();
    void	SearchEnemyJusticalA();
    void	SearchEnemyJusticalB();
    void	SearchEnemyJusticalC();

    void	AttackAI_1();
    void	AttackAI_2();
    void	AttackAI_3();
    void	AttackAI_4();
    void	AttackAI_5();
    void	AttackAI_6();
    void	AttackAI_7();
    void	AttackAI_8();
    void	AttackAI_9();
    void	AttackAI_10();
    void	AttackAI_11();
    void	AttackAI_12();
    void	AttackAI_13();
    void	AttackAI_14();
    void	AttackAI_15();
    void	AttackAI_16To24(int nMethod);
    void    AttackAI_25();
    // ����ս���Լ���̴���
    BOOL	CheckEnemy(CPlayer* pPlayer, int nRange = 12 , BOOL bHero = true);

    void	CheckTarget();
    BOOL	CheckTargetDie();
    BOOL	CheckTargetNotFound();
    BOOL	CheckTargetTooFar();
    BOOL	CheckTargetSpecialCommand();
    BOOL	CheckTargetElude();



    void	Idle(DWORD dwDelay);
private:
    void	ProcessAI_Idle();
    void	ProcessAI_Ready();
    void	ProcessAI_GenerateNewBehavior();
    void	ProcessAI_FindHost(int nDistance = 6);
    void	ProcessAI_Attack();
    BOOL    ProcessAI_MagicAtk();

};

#endif
