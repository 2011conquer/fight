
//**********************************************************
// ����༭��
//**********************************************************

#ifndef _ROLE_H
#define _ROLE_H

#include "basefunc.h"
#include "Path.h"
#include "MapObj.h"
#include "IRoleView.h"
#include "AniEffect.h"
#include "SayHello.h"
#include "FloatingStr.h"
#include "Game3DEffectEx.h"
#include "ZoomNum.h"
#include <vector>
const int _MAX_LEVEL			= 100;
//----------------------------------------------------------------------------
// ID�ռ�
enum
{
    _PLAYER_ID_NONE		= 0,
    _PLAYER_ID_MONSTER	= 1,
    _PLAYER_ID_PET		= 2,
    _PLAYER_ID_SYSNPC	= 3,
    _PLAYER_ID_DYNNPC	= 4,
    _PLAYER_ID_CALLPET	= 5,
    _PLAYER_ID_PLAYER	= 6,
};
// ID�ռ�
/////////////////////////////////////////////////////////////////////
// ID�ռ�
const OBJID	SCENEID_FIRST		= 000001;			// SCENE�ĵ�һ��ID
const OBJID	SYSNPCID_FIRST		= 00001;			// SYSNPC�ĵ�һ��ID
const OBJID	SYSNPCID_LAST		= 99999;			// SYSNPC�����һ��ID
const OBJID	DYNANPCID_FIRST		= 100001;			// DYNANPC�ĵ�һ��ID
const OBJID	DYNANPCID_LAST		= 199999;			// DYNANPC�����һ��ID
const OBJID	SCENEID_LAST		= 299999;			// SCENE�����һ��ID

const OBJID	NPCSERVERID_FIRST	= 400001;			// NPC�ĵ�һ��ID
const OBJID	MONSTERID_FIRST		= 400001;			// MONSTER�ĵ�һ��ID
const OBJID	MONSTERID_LAST		= 499999;			// MONSTER�����һ��ID
const OBJID	PETID_FIRST			= 500001;			// PET�ĵ�һ��ID
const OBJID	PETID_LAST			= 599999;			// PET�����һ��ID
const OBJID	NPCSERVERID_LAST	= 899999;			// NPC�����һ��ID

const OBJID TRAPID_FIRST		= 900001;			// ħ������ĵ�һ��ID
const OBJID MAGICTRAPID_FIRST	= 900001;			// ���ħ���ĵ�һ��ID
const OBJID MAGICTRAPID_LAST	= 989999;			// ���ħ�������һ��ID
const OBJID SYSTRAPID_FIRST		= 990001;			// ϵͳ����ĵ�һ��ID
const OBJID SYSTRAPID_LAST		= 999999;			// ϵͳ��������һ��ID
const OBJID TRAPID_LAST			= 999999;			// ħ����������һ��ID

const OBJID PLAYER_ID_FIRST		= 1000000;			// Player�ĵ�һ��ID
const OBJID PLAYER_ID_LAST		= 1999999999;		// Player�����һ��ID
const OBJID	CALLPETID_FIRST		= 2000000000;		// CALLPET�ĵ�һ��ID
const OBJID	CALLPETID_LAST		= 3999999999;		// CALLPET�����һ��ID

const OBJID CLIENT_ID_FIRST		= 4000000000;		// Ϊ�ͻ��˱�����ID�ռ�
const OBJID MOUSE_PLAYER_ID		= 4000000001;		// ��NPCʱ���������ʾ

const OBJID _IDMAX_NPC	= 999999;

//----------------------------------------------------------------------------
// ��������
enum
{
    ROLE_ATTRIBUTE_TASK			= 1,			// ������
    ROLE_ATTRIBUTE_RECYCLE		= 2,			// �ɻ�����
    ROLE_ATTRIBUTE_SCENE		= 4,			// ������
};
//----------------------------------------------------------------------------
// ��Ϊ����
enum
{
    _ROLE_NPC_NONE				= 0,			// �Ƿ�NPC
    _ROLE_SHOPKEEPER_NPC		= 1,			// �̵�NPC
    _ROLE_TASK_NPC				= 2,			// ����NPC
    _ROLE_STORAGE_NPC			= 3,			// �Ĵ洦NPC
    _ROLE_TRUNCK_NPC			= 4,			// ����NPC
    _ROLE_FACE_NPC				= 5,			// ��ͷ��NPC
    _ROLE_FORGE_NPC				= 6,			// ����NPC
    _ROLE_EMBED_NPC				= 7,			// ��ǶNPC

    _ROLE_STATUARY_NPC			= 9,			// ����NPC
    _ROLE_SYNFLAG_NPC			= 10,			// ���ɱ��NPC

    _ROLE_PLAYER				= 11,			// �������
    _ROLE_HERO					= 12,			// �Լ�
    _ROLE_MONSTER				= 13,			// ����

    _ROLE_BOOTH_NPC				= 14,			// ̯λNPC
    _SYNTRANS_NPC				= 15,			// ���ɴ���NPC(����00:00�շ�)(LINKIDΪ�̶�NPC��ID��������ʹ��LINKID�Ļ���)
    _ROLE_BOOTH_FLAG_NPC		= 16,			// ̯λ��־NPC
    _ROLE_MOUSE_NPC				= 17,			// ����ϵ�NPC
    _ROLE_MAGICITEM				= 18,			// �����ǽ

    _ROLE_DICE_NPC				= 19,			// ����NPC

    _ROLE_WEAPONGOAL_NPC		= 21,			// ������NPC
    _ROLE_MAGICGOAL_NPC			= 22,			// ħ����������NPC
    _ROLE_BOWGOAL_NPC			= 23,			// ��������NPC

    _ROLE_TARGET_NPC			= 24,			// ���򣬲���������

    _ROLE_FURNITURE_NPC			= 25,			// �Ҿ�NPC
    _ROLE_CITY_GATE_NPC			= 26,			// ����NPC
    _ROLE_NEIGHBOR_DOOR			= 27,			// �ھӵ���
    _ROLE_CALL_PET				= 28,			// �ٻ���

    _TRAINPLACE_NPC				= 29,			// ����ѱ����
    _AUCTION_NPC				= 30,			// ����NPC
    //		_ROLE_WOOD_NPC				= 30,			// ľͷ��
    _ROLE_STONE_MINE			= 31,			// ʯͷ��
    //		_ROLE_METAL_MINE			= 32,			// ������


    _ROLE_PKGAME_NPC			= 32,			// PK������NPC
    _ROLE_3DFURNITURE_NPC		= 101,			// 3D�Ҿ�NPC

    _ROLE_CITY_WALL_NPC			= 102,			// ��ǽNPC
    _ROLE_CITY_MOAT_NPC			= 103,			// ���Ǻ�NPC

    SYN_NPC_WARLETTER			= 110,			//�����µģΣУ����͡�ר����������ս��ġ����ɣΣУ�
};

//----------------------------------------------------------------------------
// ��ͼ����
enum
{
    _ROLE_VIEW_NONE			= 0,
    _ROLE_VIEW_ROLE			= 1,
    _ROLE_VIEW_STATUARY		= 2,
    _ROLE_VIEW_TARGET		= 3,
    _ROLE_VIEW_TASKNPC		= 4,
    _ROLE_VIEW_SYNSTONE		= 5,
    _ROLE_VIEW_BOOTH		= 6,
    _ROLE_VIEW_MAPMAGICOBJ	= 7,
    _ROLE_VIEW_DICENPC		= 8,
    _ROLE_VIEW_TERRAIN		= 9,
};
//----------------------------------------------------------------------------
// command define
const int _COMMAND_NULL			= 0;
const int _COMMAND_STOP			= 1;
const int _COMMAND_STANDBY		= 2;
const int _COMMAND_WALK			= 3;
const int _COMMAND_RUN			= 4;
const int _COMMAND_JUMP         = 5;
const int _COMMAND_EMOTION      = 6;
const int _COMMAND_ACTION		= 7;
const int _COMMAND_ATTACK		= 8;
const int _COMMAND_FOLLOW		= 9;
const int _COMMAND_SHITHAPPEN	= 10;
const int _COMMAND_DIE			= 11;
const int _COMMAND_SPATTACK		= 12;
const int _COMMAND_FAINT		= 13;
const int _COMMAND_RUSHATK		= 14;
const int _COMMAND_WOUND		= 15;
const int _COMMAND_DEFEND		= 16;
const int _COMMAND_WALKFORWARD	= 17;
const int _COMMAND_RUNFORWARD	= 18;
const int _COMMAND_LOCKATK		= 19;
const int _COMMAND_PICKUP		= 20;
const int _COMMAND_TEAMFOLLOW	= 21;
const int _COMMAND_POSE			= 22;
const int _COMMAND_INTONE		= 23;
const int _COMMAND_BUMP			= 24;
const int _COMMAND_MINE			= 25;
const int _COMMAND_SHOOT		= 26;
const int _COMMAND_LOCKBOOTH	= 27;

const int _COMMAND_TAKEOFF		= 28;
const int _COMMAND_LANDING		= 29;
const int _COMMAND_FLOAT		= 30;
const int _COMMAND_FLOAT_DIE	= 31;

const int _COMMAND_CHARGEUP			= 32;
const int _CPMMAND_CHARGEUP_SHOOT	= 33;

const int _COMMAND_KONGFU		= 100;

// command status define
const int _CMDSTATUS_BEGIN		= 0;
const int _CMDSTATUS_DEPART		= 1;
const int _CMDSTATUS_PROGRESS	= 2;
const int _CMDSTATUS_CONTINUE	= 3;
const int _CMDSTATUS_WAITING	= 4;
const int _CMDSTATUS_ACCOMPLISH	= 9;

// user status
const __int64				USERSTATUS_NORMAL			= 0x00000000;		 	// ������״̬
const __int64				USERSTATUS_TEAMLEADER		= 0x00000001;			// �ӳ�
const __int64				USERSTATUS_DIE				= 0x00000002;			// ����
const __int64				USERSTATUS_GHOST			= 0x00000004;			// ���״̬
const __int64				USERSTATUS_DISAPPEARING		= 0x00000008;			// ʬ����ʧ״̬
const __int64				USERSTATUS_CRIME			= 0x00000010;			// ���� // ����ɫ
const __int64				USERSTATUS_RED				= 0x00000020;			// ����
const __int64				USERSTATUS_DARKRED			= 0x00000040;			// ����
const __int64				USERSTATUS_SYNCRIME			= 0x00000080;			// ���ɷ���
const __int64				USERSTATUS_POISON			= 0x00000100;			// �ж�
const __int64				USERSTATUS_INVISIBLE		= 0x00000200;			// ����
const __int64				USERSTATUS_CANNOTMOVE		= 0x00000400;			// ����
const __int64				USERSTATUS_LURKER			= 0x00001000;			// Ǳ��
const __int64				USERSTATUS_DEFENCE1			= 0x00002000;			// �������1
const __int64				USERSTATUS_DEFENCE2			= 0x00004000;			// �������2
const __int64				USERSTATUS_DEFENCE3			= 0x00008000;			// �������3
const __int64				USERSTATUS_ATTACK			= 0x00010000;			// ��������
const __int64				USERSTATUS_ATKSPEED			= 0x00020000;			// �����ٶ����
const __int64				USERSTATUS_MAGICDAMAGE		= 0x00040000;			// ħ���˺����
const __int64				USERSTATUS_MAGICDEFENCE 	= 0x00080000;			// ħ���������
const __int64				USERSTATUS_REFLECT			= 0x00100000;			// ��������
const __int64				USERSTATUS_REFLECTMAGIC		= 0x00200000;			// ħ������
const __int64				USERSTATUS_SLOWDOWN1		= 0x00400000;			// ����״̬ 50%
const __int64				USERSTATUS_SLOWDOWN2		= 0x00800000;			// ����״̬ // Ѫ����һ��ʱ��ʼ���� // 50%
const __int64				USERSTATUS_TEAM_HEALTH		= 0x01000000;			// ҽ�ƽ��״̬
const __int64				USERSTATUS_TEAM_ATTACK		= 0x02000000;			// �������״̬
const __int64				USERSTATUS_TEAM_DEFENCE		= 0x04000000;			// ������״̬
const __int64				USERSTATUS_TEAM_SPEED		= 0x08000000;			// �ٶȽ��״̬
const __int64				USERSTATUS_TEAM_EXP			= 0x10000000;			// �������״̬
const __int64				USERSTATUS_TEAM_SPIRIT		= 0x20000000;			// ������״̬
const __int64				USERSTATUS_TEAM_CLEAN		= 0x40000000;			// �������״̬
const __int64				USERSTATUS_SMOKE			= 0x80000000;			// ����Ч��
const __int64				USERSTATUS_DARKNESS			= 0x0000000100000000;	// �ڰ�Ч��
const __int64				USERSTATUS_PALSY			= 0x0000000200000000;	// ���Ч��
const __int64				USERSTATUS_MAXLIFE			= 0x0000000400000000;	// �����������/����
const __int64				USERSTATUS_MAXENERGY		= 0x0000000800000000;	// �����������/����
const __int64				USERSTATUS_ADD_EXP			= 0x0000001000000000;	// ս����������
const __int64				USERSTATUS_ATTRACT_MONSTER	= 0x0000002000000000;	// ��������
const __int64				USERSTATUS_XPFULL			= 0x0000004000000000;	// XP��
const __int64				USERSTATUS_ADJUST_DODGE		= 0x0000008000000000;	// �����ܵĶ��ֵ
const __int64				USERSTATUS_ADJUST_XP		= 0x0000010000000000;	// ����ÿ������XPֵ
const __int64				USERSTATUS_ADJUST_DROPMONEY	= 0x0000020000000000;	// ���ڹ���ÿ�ε�Ǯ
const __int64				USERSTATUS_PK_PROTECT		= 0x0000040000000000;	// PK����
const __int64				USERSTATUS_PELT				= 0x0000080000000000;	// ����״̬

//������
const __int64				USERSTATUS_ADJUST_EXP		= 0x0000100000000000;	// ս����þ������

const __int64				USERSTATUS_HEAL				= 0x0000200000000000;	// ����״̬
const __int64				USERSTATUS_FAINT			= 0x0000400000000000;	// ��
const __int64				USERSTATUS_TRUCULENCE		= 0x0000800000000000;	// Ұ��
const __int64				USERSTATUS_DAMAGE			= 0x0001000000000000;	// �����ܵ����˺�
const __int64				USERSTATUS_ATKER_DAMAGE		= 0x0002000000000000;	// ������Ŀ����ɵ��˺�
const __int64				USERSTATUS_CONFUSION		= 0x0004000000000000;	// ����
const __int64				USERSTATUS_FRENZY			= 0x0008000000000000;	// ��
const __int64				USERSTATUS_EXTRA_POWER		= 0x0010000000000000;	// ����
const __int64				USERSTATUS_TRANSFER_SHIELD	= 0x0020000000000000;	// ����
const __int64				USERSTATUS_SORB_REFLECT		= 0x0040000000000000;	// ���շ���
const __int64				USERSTATUS_FRENZY2			= 0X0080000000000000;	// ��һ�ֿ�״̬

enum {ANIEFFECT_NORMAL = 0, ANIEFFECT_CASTMAGIC = 1, ANIEFFECT_BLASTMAGIC = 2};
enum {ROLE_PLAYER = 0, ROLE_MONSTER = 1};
enum {SEX_NONE = 0, SEX_MALE, SEX_FEMALE, SEX_ASEXUAL, SEX_ALL};
enum
{
    RACE_NONE	= 0, // δ֪
    RACE_HUMAN	= 2, // ����
    RACE_SPRITE = 3, // ����
    RACE_DARKSPRITE = 1, // ������
};
enum
{
    PROFESSIONAL_ENCHANTER	=	10, // ��ʦ
    PROFESSIONAL_WARRIOR	=	20, // սʿ
    PROFESSIONAL_KORADJI	=	30, // ������
};

// others
const int OFFSET_NAMESHOW	= 120;
const int OFFSET_SYNDICATESHOW	= 102;
const DWORD TIME_INBATTLE	= 10000;

// type define
class C3DObj;
class C3DMotion;
class C3DRoleData;
typedef struct
{
    OBJID	idPlayer;
    DWORD	dwSenderCommandIndex;
    int		nAction;
    int		nFrameIndex;
    int		nLife;
    DWORD	dwColor;
} BeAttackCmdInfo;

class CCommand
{
public:
    CCommand(void)
    {
        memset(this, 0L, sizeof(CCommand));
        bHeroSendMsg = true;
        strcpy(szString0, "");
        strcpy(szString1, "");
        bAddUp = false;
		bUseFrameInterval = false;
    }
	~CCommand()
    {}

	void Format(const char* fmt, ...) { vsprintf( szCmd, fmt, (char*) ((&fmt) + 1) ); }

public:
    union
    {
        char	szCmd[256];

        struct
        {
            OBJID	idTarget;
            CMyPos	posTarget;
            int		nTargetZ;
            int		nDir;
            char	szString[_MAX_NAMESIZE];
            DWORD	dwData;
            int		nData;
            BOOL	bData;
            BOOL	bHeroSendMsg;
            char	szString0[_MAX_STRING];
            char	szString1[_MAX_STRING];
            int		nFrameStart;
            int		nFrameEnd;
            int		nFrameInterval; //���ڲ�ȷ����֡����������ƶ���
			int		timeActionTime; //����õ���֡���Ķ�������������� ���ܵĲ�ȷ����֡����nFrameInterval��
            BOOL	bAddUp;
            DWORD	dwIndex;
			BOOL    bUseFrameInterval;	//�Ƿ�ʹ��nFrameInterval
        };
    };
	
    int		iType;
    int		iStatus;
};

class CPath;

class CRoleInfo
{
public:
	CRoleInfo()
	{
		Reset();
	}

	void Reset()
	{
		id				= 0;
		idMonsterType	= 0;
		usLook			= 0;
		usHair			= 0;
		usFace			= 0;
		usPose			= 0;
		ucSprite		= 0;
		idArmorType		= 0;
		idRWeaponType	= 0;
		idLWeaponType	= 0;
		idMountType		= 0;
		idArmetType		= 0;
		idMantleType	= 0;

		iSize			= 0;
		iAddSize		= 0;
		nSex			= 0;
		nTransformLook	= 0;
		nRace			= 0;
		iDirection		= 0;
		iAngle			= 0;
		iZoomPercent	= 0;

		//posRush			= 0;
		//posMap			= 0;
		//posWorld		= 0;
		//posScr			= 0;
		//posNext			= 0;
		//posActionBegin	= 0;
		//posActionEnd	= 0;	// world pos
		//
		//posDir			= 0;
		iActType		= 0;
		iActFrameIndex	= 0;
		iActFrameAmount	= 0;
		timeFirstFrame	= 0;
		timeFrameInterval	= 0;
		timeActionTime = 0;
		//objPath			= 0;
		//cmdProc			= 0;
		//sizeBase		= 0;
		nFlyOffset		= 0;
		nFlyOffsetGoal	= 0;
		bAdjustDir		= 0;
		bAdjustRun		= 0;
		nNextStep		= 0;
		dwSpeed			= 0;

		memset(szName, 0, sizeof(szName));
	}

    OBJID	id;
    OBJID   idMonsterType;
    USHORT	usLook, usHair, usFace, usPose;
    UCHAR	ucSprite;
    OBJID	idArmorType, idRWeaponType, idLWeaponType, idMountType, idArmetType, idMantleType;
    char	szName[_MAX_NAMESIZE];

    int		iSize, iAddSize, nSex, nTransformLook, nRace;
    int		iDirection, iAngle;
    int		iZoomPercent;

    CMyPos	posRush;
    CMyPos	posMap, posWorld, posScr, posNext;
    CMyPos	posActionBegin, posActionEnd;	// world pos
    int		nPosActionBeginZ, nPosActionEndZ;
    int		nZ;
    CMyPos	posDir;
    int		iActType;
    int		iActFrameIndex;
    int		iActFrameAmount;
    DWORD	timeFirstFrame;
    DWORD	timeFrameInterval;
	DWORD	timeActionTime;	// ��Ϊ���㶯������ʱ�䣬����Ϊ��λ
    CPath		objPath;
    CCommand	cmdProc;
    CMySize		sizeBase;
    int			nFlyOffset;
    int			nFlyOffsetGoal;
    BOOL		bAdjustDir;
    BOOL		bAdjustRun;
    int			nNextStep;
    DWORD		dwSpeed;
};


#include <list>
using namespace std;

typedef list<UINT> LIST_DIR;

class CRole : public CMapObj
{
private:
	// ���¼��㶯������Ҫ����ʱ��
	DWORD	GetActionTotalTime(int nActType);
    void	StaticAction(int nAction, int nDir = -1);

    BOOL	Step		(void);
    BOOL	Walk		(void);
    BOOL	WalkForward	(void);
    BOOL	Run			(void);
    BOOL	RunForward	(void);
    BOOL	Jump		(void);
    BOOL    Emotion		(void);
    BOOL	Attack		(void);
    BOOL	RushAtk		(void);
    BOOL	LockAtk		(void);
    BOOL	TeamFollow	(void);
    BOOL	Follow		(void);
    BOOL	Action		(void);
    BOOL	Die			(void);
    BOOL	DieNormal	(void);
    BOOL	DieDelay	(void);
    BOOL	DieFlying	(void);
    BOOL	DieFloat	(void);

    BOOL	PickUp		(void);
    BOOL	Pose		(void);
    BOOL	InTone		(void);
    BOOL	Bump		(void);
    BOOL	Mine		(void);
    BOOL	LockBooth	(void);
    BOOL	TakeOff		(void);
    BOOL	Landing		(void);
    BOOL	Float		(void);
    BOOL	Kongfu		(void);
protected:
    int		GetOffsetY();
    BOOL	StandBy		(void);

private:
    int		GetStepDir		(void);
    BOOL	IsMapReached	(void);
    int		GetJumpHeight	();
    int		GetJumpShadowHeight();
    DWORD	GetJumpFrameInterval();
    int     GetWalkHeight	();

public:
    CRole(void) {Init();}
    virtual ~CRole(void) {Destroy();}

    void	Init			(void);

    BOOL	Create	(UINT uLook = 1, int nViewType = _ROLE_VIEW_ROLE);
    BOOL	Create	(UINT uLook, int nViewType, OBJID id, CMyPos pos);
    void	Destroy	(void);

    virtual void	GetWorldPos	(int& iPosX, int& iPosY)	{iPosX = m_Info.posWorld.x, iPosY = m_Info.posWorld.y;}
    virtual void	GetScrPos	(int& iPosX, int& iPosY)	{iPosX = m_Info.posScr.x, iPosY = m_Info.posScr.y;}
    virtual void	GetPos		(int& iPosX, int& iPosY)	{iPosX = m_Info.posMap.x, iPosY = m_Info.posMap.y;}

    virtual void	GetSize		(int& iWidth, int& iHeight)	{iWidth = iHeight = m_Info.iSize;}
    virtual void	Show		(void);
    virtual void	Process		(void* pInfo);


    virtual BOOL	ProcessAction	(void);

    virtual BOOL	IsMouseFocus(int evtMouse = _MOUSE_NONE);
    virtual BOOL	IsVisible(void);

    virtual int		GetAtkRange	(void) { return 1; }

    void	SetActionData	(void);
    void	ResetActionData	(void);

    DWORD   GetFrameInterval(int nActType);
	BOOL    IsUseFrameInterval(); //�Ƿ�ʹ��֡���ģʽ
    DWORD	GetDistance	(CRole* pRole);
    BOOL	IsMapAttainable	(int iMapX, int iMapY);
    BOOL	IsWalking	(void);
    BOOL	IsRunning	(void);
    BOOL	IsMoving	(void);
    BOOL	IsStandBy	(void);
    BOOL	IsIdle		(void);		// ����״̬, ��ʾ��ǰ����������������ȼ���
    BOOL	IsBumpBackEnable	(void);

    DWORD	GetActionDelayInfoKey	(CRole* pTarget);
    DWORD	GetWeaponInfoKey		(CRole* pTarget);

    void	AddStepDir	(UINT uDir)	{m_lstStepDir.push_back(uDir % 8);}
    void	ResetStepDir();

    BOOL	SetPos		(int iPosX, int iPosY);
    void    SetNextPos  (int iPosX, int iPosY)  {m_Info.posNext.x = iPosX; m_Info.posNext.y = iPosY;}
    void	SetScrPos	(int iPosX, int iPosY)	{m_Info.posScr.x = iPosX; m_Info.posScr.y = iPosY;}
    void	SetRushPos	(int iPosX, int iPosY)	{m_Info.posRush.x = iPosX, m_Info.posRush.y = iPosY;}
    void	ClrRushPos	(void)	{m_Info.posRush.x = m_Info.posRush.y = 0;}

    void	ShowName	(void);
    void	Say			(const char* pszWords);

    DWORD	GetSpeed() const {return m_Info.dwSpeed;}
    void	SetSpeed(DWORD dwSpeed) {m_Info.dwSpeed = dwSpeed;}


    //	3d feature
    void	SetRGBA		(float alpha, float red, float green, float blue);
    void	SetArmor	(OBJID idType);
    void	SetArmet	(OBJID idType);
    void	SetRWeapon	(OBJID idType);
    void	SetLWeapon	(OBJID idType);
    void	SetMount	(OBJID idType);
    void	SetMantle	(OBJID idType);
    BOOL	HaveBow		();
    OBJID	GetArmor	() {return m_Info.idArmorType;}
    OBJID	GetArmet	() {return m_Info.idArmetType;}
    OBJID	GetRWeapon	() {return m_Info.idRWeaponType;}
    OBJID	GetLWeapon	() {return m_Info.idLWeaponType;}
    OBJID	GetMount	() {return m_Info.idMountType;}
    OBJID	GetMantle	() {return m_Info.idMantleType;}

    // static...
public:
    enum {SHADOW_NONE, SHADOW_SIMPLE, SHADOW_REAL};
    static int s_nShadowType;

public:
    int		GetActionType	(void)	{return m_Info.iActType;}
    BOOL	IsAttacking		(void);
    void	GetActionStartPos	(int& nWorldX, int& nWorldY)	{nWorldX = m_Info.posActionBegin.x, nWorldY = m_Info.posActionBegin.y;}
    void	GetActionEndPos		(int& nWorldX, int& nWorldY)	{nWorldX = m_Info.posActionEnd.x, nWorldY = m_Info.posActionEnd.y;}

    void	GetPrePos	(int& nPosX, int& nPosY);
    void    GetNextPos  (int& nPosX, int& nPosY) {nPosX = m_Info.posNext.x; nPosY = m_Info.posNext.y;};
    int		GetDir		(CMyPos posTarget) const;
    int		GetDir		(CRole* pTarget) const;

    //------------- status -------------
public:
    void	SetStatus	(__int64 dwStatus);
    void	ClrStatus	(__int64 dwStatus);
    __int64	GetStatus	(void)	{return m_dwStatus;}
    BOOL	TestStatus	(__int64 dwStatus);

protected:
    __int64	m_dwStatus;

    //------------- ani effects -------------
public:
    BOOL	AddAniEffectEx (const char* pszEffectTitle,
                            int nTimes = 1,
                            DWORD dwInterval = 50,
                            int nShowWay = _SHOWWAY_NORMAL,
                            DWORD dwLoopInterval = 0,
                            int nOffsetX = 0,
                            int nOffsetY = 0,
                            int nExigence = 0,
                            DWORD dwDelay = 0);

    BOOL	AddAniEffect	(const char* pszEffect);
    void	ClrAniEffect	(const char* pszEffect = NULL);

    void	ShowAniEffect	(int nPosX, int nPosY);
    void	ProcessAniEffect();
    BOOL	TestAniEffect(const char* pszEffect);
private:
    DEQUE_EFFECT	m_dequeAniEffect;

    //------------- command -------------
public:
    virtual DWORD	SetCommand	(CCommand* pCommand);
    virtual BOOL	ProcessCommand	(void);

    void		InitCommand	(void);
    CCommand*	GetCommand	(void)	{return &(m_Info.cmdProc);}

    int			GetCommandType(void);
    BOOL		GetCommandFlag(void) {return m_Info.cmdProc.bData;}
    int			GetLastCommand(void)	{return m_Info.cmdProc.iType;}
    int			GetCommandStatus(void)	{return m_Info.cmdProc.iStatus;}

    //------------- info -------------
public:
    BOOL	IsNpc(void) {return GetID() <= _IDMAX_NPC;}
    BOOL	IsPlayer(void) {return (GetID() >= PLAYER_ID_FIRST && GetID() <= PLAYER_ID_LAST);}

    //	BOOL	IsMonster(void) {return (GetID() >= MONSTERID_FIRST && GetID() <= MONSTERID_LAST);}
    //ACTION������MONSTERҲ����MONSTER   --2005 6- 13 --XUELIANG
    BOOL	IsMonster(void) {return (GetID() >= MONSTERID_FIRST && GetID() <= PETID_LAST);}

    BOOL	IsGuard(void);
    BOOL	IsPet(void) {return (GetID() >= CALLPETID_FIRST && GetID() <= CALLPETID_LAST);}
    BOOL	IsMyPet(void);
    void	SetID		(OBJID id)		{m_Info.id = id;}
    OBJID	GetID		(void) const	{return m_Info.id;}

    void    SetLook		(USHORT usLook);
    USHORT	GetLook		(void) const	{return m_Info.usLook;}

    void    SetHair		(USHORT usHair);
    USHORT	GetHair		(void) const	{return m_Info.usHair;}

    void    SetFace		(USHORT usFace);
    USHORT	GetFace		(void) const	{return m_Info.usFace;}

    void    SetPose		(USHORT usPose)	{m_Info.usPose = usPose;}
    USHORT	GetPose		(void) const	{return m_Info.usPose;}

    void	SetDir		(int nDir);
    int		GetDir		(void) const	{return m_Info.iDirection;}

    const char*	GetName	(void) const	{return m_Info.szName;}
    void	SetName		(const char* pszName);

    DWORD   GetMonsterTypeId(void) {return m_Info.idMonsterType;}
    void	SetMonsterTypeId(DWORD idType) {m_Info.idMonsterType = idType;}

    int		GetAddSize	(void) const	{return m_Info.iAddSize;}
    void	SetAddSize	(int nSize)		{m_Info.iAddSize = nSize;}

    int		GetZoomPercent	(void) const	{return m_Info.iZoomPercent;}
    void	SetZoomPercent	(int nPercent)	{m_Info.iZoomPercent = nPercent;}

    void	AddFStr(char* pszStr, int nMaxHeight = 64, DWORD dwColor = 0x00ffffff, int nStepHeight = 3, int nDelayTime = 0);
    void	AddZoomNum		(int nNum, DWORD dwColor, DWORD dwDelay, int nRandOffset = 0);
    //int		GetType();
    void	SetActionCmd (int nAction, int nDir = -1, DWORD dwType = 0, BOOL bData = false);
    void	SetIntoneCmd (int nAction, int nDir = -1, DWORD dwType = 0, BOOL bData = false);
    void	Transform(int nLook);
    void	SetWorldPos(CMyPos posWorld) {m_Info.posWorld = posWorld;}
    int		GetFrameIndex() {return m_Info.iActFrameIndex;}
    void	ShootArrow(OBJID idTarget, int nHpLose);

    int		GetSex() {return m_Info.nSex;}
    void	SetSex(int nSex) {m_Info.nSex = nSex;}


    int		GetRace() {return m_Info.nRace;}
    void	SetRace(int nRace) {m_Info.nRace = nRace;}

    void	AllotRes();
    int		GetViewType() {return m_nViewType;}

    static  int		GetIDType(OBJID id);
    int		GetRoleType() {return m_nRoleType;}
    void	SetRoleType(int nRoleType) {m_nRoleType = nRoleType;}
    void	SetRoleAttribute(DWORD dwAttribute) {m_dwRoleAttribute = dwAttribute;}
    DWORD	GetRoleAttribute() {return m_dwRoleAttribute;}
    void	SetFlyOffset(int nOffset);
    int		GetFlyOffset();
    void	SetFlyOffsetGoal(int nOffset);
    int		GetFlyOffsetGoal();
    void	FlashLastAttackTime() {m_tmLastAtk = ::TimeGet();}
    BOOL	IsHypersensitive();
    void	AddStep(CMyPos posCell);
protected:
    CRoleInfo		m_Info;
    int				m_nType;
    int				m_nViewType;
    int				m_nRoleType;
    DWORD			m_dwRoleAttribute;
    DWORD			m_tmDisappear;
    DWORD			m_tmLastAtk;
    LIST_DIR		m_lstStepDir;
    int				m_nWhichLeg;
    CMyPos			m_posCellOffset;
public:
    void SetSpriteEffect( UCHAR ucSprite );
    IRoleView*		m_pIRoleView;
    CSayHello		m_objSayHello;
    CFloatingStr	m_objFStr;
    CGame3DEffectEx m_objEffect;
    CZoomNum		m_objZoomNum;

public:
    typedef struct
    {
        int		nAction;
        DWORD	dwFrameInterval;
        char	szEffect[128];
        char	cDir;
        std::deque<char> setStep;
    } KongfuAction;
    std::deque<KongfuAction> m_setKongfu;
    BOOL	LoadKongfu(const char* pszFileName);

public:
    DWORD m_dwDisappear;
    DWORD m_dwDisappearLast;
    void Disappear(DWORD dwLast);
public:
    static float s_fBaseScale;
    std::vector<CCommand*> m_setCmd;
    std::vector<int> m_setLife;
    std::deque<BeAttackCmdInfo*> m_setBeAttackCmdInfo;
    OBJID m_idLocker;
protected:
    DWORD m_dwSpeedRate;
protected:
    DWORD m_dwCommandIndex;
public:
    void SetSpeedRate(int nSpeedRate) {m_dwSpeedRate = nSpeedRate;}
    void AddBeAttackCommandInfo(OBJID idSender, int nSenderCommandIndex, int nAction, int nFrameIndex, int nLife, DWORD dwColor);
    void PerformBeAttackCmd(BeAttackCmdInfo* pInfo);
    DWORD	GetSpeedRate() {return m_dwSpeedRate;}
    //---------------for mapobj----------------
public:
    virtual int  GetObjType()               {return m_nType;}
    virtual BOOL IsFocus()                  {return false;}
    virtual void GetWorldPos(CMyPos& posWorld) {posWorld = m_Info.posWorld;}
    virtual void GetPos(CMyPos& posCell)	{posCell = m_Info.posMap;}
    virtual void SetPos(CMyPos posCell)		{SetPos(posCell.x, posCell.y);}
    virtual void GetBase(CMySize& infoSize)	{infoSize.iWidth = 1; infoSize.iHeight = 1;}
    virtual void SetBase(CMySize& infoSize)	{m_Info.sizeBase = infoSize;}
    //---------------for mapobj----------------
};



#endif
