
//**********************************************************
// ����༭��
//**********************************************************

#ifndef _BASEFUNC_H
#define _BASEFUNC_H
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include <windows.H>

#include "mouse.H"

#ifdef _ANALYSIS_ON
extern DWORD g_dwIniGetAmount;
extern DWORD g_dwIniSearchLineAmount;
extern DWORD g_dwIniGetAmountFrame;
extern DWORD g_dwIniSearchLineAmountFrame;
#endif

//#define _NOTUSETRY
#pragma warning(disable: 4786)
extern int _SCR_WIDTH, _SCR_HEIGHT;
extern int PUZZLE_SCRX ,PUZZLE_SCRY;	

extern int  _FRAME_SIZE;

const DWORD _SHOWWAY_NORMAL		 = 0;
const DWORD _SHOWWAY_ADDITIVE	 = 1;

const DWORD _LOADWAY_NORMAL	 = 0;
const DWORD _LOADWAY_MASK	 = 0xff000000;
const DWORD _LOADWAY_TRANS   = 0xffff00ff;

enum {CRITICAL_FALSE = false, CRITICAL_TRUE = true};
//----------------------------------------------------------
int		Double2Int	(double dValue);

BOOL	IniStrGet	(const char* pszFileName, const char* pszTitle, const char* pszSubTitle, char* pszStr, BOOL bCritical = false);
BOOL	IniDataGet	(const char* pszFileName, const char* pszTitle, const char* pszSubTitle, int& iData, BOOL bCritical = false);

BOOL	TxtStrGet	(const char* pszFileName, const char* pszTitle, char* pszStr, BOOL bCritical = false);
BOOL	TxtDataGet	(const char* pszFileName, const char* pszTitle, int& iData, BOOL bCritical = false);

DWORD	TimeGet		(void);
DWORD	SysTimeGet  (void);
int		RandGet		(int nMax, BOOL bRealRand = false);

void	ErrorMsg	(const char* fmt, ...);
void	ErrorOut	(const char* fmt, ...);
void	LogMsg		(const char* fmt, ...);
void	DebugMsg	(const char* fmt, ...);
BOOL	StringCheck	(char* pszString);

void	MouseInit		(void);
void	MouseSet		(int x, int y, int event);
void	MouseProcess	(void);
int		MouseCheck		(int& iMouseX, int& iMouseY);

void	KeyClearBuffer	(void);
int		KeyAppend		(void);
int		KeyGet			(void);
bool	KeyUnGet		(void);

void	RepairString	(char* pszString);
void	ReplaceString	(char* pszString, char cFind, char cReplace);
DWORD	GetDate			();
BOOL	IsDBCSLeadByte	(const char* pszString, int idx);


//----------------------------------------------------------
typedef DWORD OBJID;

typedef struct
{
    int	x, y;
} CMyPos;

typedef struct
{
    int t, l, r, b;
} CMyRect;

typedef struct
{
    float fHorizontal;
    float fVertical;
} CMy3DDir;

typedef struct
{
    int	x, y, z;
} CMy3DPos;

typedef struct
{
    float		fRadianX;			// �ҷ����ᣬ˳ʱ��
    float		fRadianY;			// �Ϸ����ᣬ˳ʱ��
    float		fRadianZ;			// �ڷ����ᣬ˳ʱ��
} CMy3DPose;



typedef struct
{
    int	iWidth, iHeight;
} CMySize;

//----------------------------------------------------------
const int _MAX_STRING		= 256;
const int _MAX_NAMESIZE		= 16;
const int _MAX_NAMESIZE_CLI	= 32;
const int _MAX_TITLESIZE	= 128;
const OBJID	ID_NONE	= 0;


//----------------------------------------------------------
#ifndef SAFE_DELETE
#ifdef _DEBUG
#define SAFE_DELETE(p) { if (p) delete p; p=NULL; }
#else
#define SAFE_DELETE(p) { if (p){ try{ delete p; } catch(...){} p=NULL; }}
#endif
#endif

//----------------------------------------------------------
#ifndef MYASSERT
#ifdef _DEBUG
#define	MYASSERT(x) assert(x)
#else
#define	MYASSERT(x)	{if (!(x)) LogMsg("��ASSERT(" #x ") in %d line of %s��", __LINE__, __FILE__); }
#endif
#endif

//----------------------------------------------------------
#ifndef IF_SUC
#ifdef _DEBUG
#define	IF_SUC(x)  if ( ((x)) ? true : ( assert(!("IF_SUC: " #x)), false ) )
#else
#define	IF_SUC(x)  if ( ((x)) ? true : ( LogMsg("��IF_SUC(%s)�� failed in %s, %d", #x, __FILE__, __LINE__), false ) )
#endif
#endif

#define IF_TRUE	IF_SUC
#define IF_YES	IF_SUC
#define IF_OK	IF_SUC

//----------------------------------------------------------
#ifndef IF_NOT
#ifdef _DEBUG
#define	IF_NOT(x)  if ( (!(x)) ? ( assert(!("IF_NOT: " #x)),1 ) : 0 )
#else
#define	IF_NOT(x)  if ( (!(x)) ? ( LogMsg("��IF_NOT(%s)�� in %s, %d", #x, __FILE__, __LINE__),1 ) : 0 )
#endif
#endif
//---------------------------------------------------------------------
inline unsigned int	ExchangeShortBits(unsigned long nData, int nBits)
{
    MYASSERT(nBits >= 0 && nBits < 16);
    nData	&= 0xFFFF;
    return ((nData >> nBits) | (nData << (16 - nBits))) & 0xFFFF;
}
inline unsigned int	ExchangeLongBits(unsigned long nData, int nBits)
{
    MYASSERT(nBits >= 0 && nBits < 32);
    return (nData >> nBits) | (nData << (32 - nBits));
}
//---------------------------------------------------------------------
// version define
const int _VERSION		= 108;
const int _FRAMEINTERVAL = 35;		// ���� [THEONE 2008-8-21 23:18]
// game status define
const unsigned int	_STATUS_NONE		= 1000;
const unsigned int	_STATUS_ACCOUNT		= _STATUS_NONE + 1;
const unsigned int	_STATUS_CONNECT		= _STATUS_NONE + 2;
const unsigned int	_STATUS_LOGIN		= _STATUS_NONE + 3;
const unsigned int	_STATUS_REGISTER	= _STATUS_NONE + 4;
const unsigned int	_STATUS_MAINTAINROLE = _STATUS_NONE + 5;

const unsigned int	_STATUS_WAITING		= _STATUS_NONE + 8;
const unsigned int	_STATUS_FIGHTING	= _STATUS_NONE + 9;
const unsigned int	_STATUS_NORMAL		= _STATUS_NONE + 10;
const unsigned int	_STATUS_TASK		= _STATUS_NONE + 11;
const unsigned int	_STATUS_GAMBLE		= _STATUS_NONE + 12;

const unsigned int	_STATUS_EXIT		= _STATUS_NONE + 100;
const unsigned int	_STATUS_DESTROY		= _STATUS_NONE + 101;

//---------------------------------------------------------------------
// action define

const int _ACTION_DANCE1		= 001;
const int _ACTION_DANCE2		= 002;
const int _ACTION_DANCE3		= 003;
const int _ACTION_DANCE4		= 004;
const int _ACTION_DANCE5		= 005;
const int _ACTION_DANCE6		= 006;
const int _ACTION_DANCE7		= 007;
const int _ACTION_DANCE8		= 8;

const int _ACTION_STANDBY		= 100;
const int _ACTION_REST1			= 101;
const int _ACTION_REST2			= 102;
const int _ACTION_REST3			= 103;
const int _ACTION_STANDBY_I		= 105;

const int _ACTION_WALKL			= 110;
const int _ACTION_WALKR			= 111;
const int _ACTION_WALKL_I		= 115;
const int _ACTION_WALKR_I		= 116;


const int _ACTION_RUNL			= 120;
const int _ACTION_RUNR			= 121;

const int _ACTION_TRANSFORM		= 122;

const int _ACTION_RUNL_I		= 125;
const int _ACTION_RUNR_I		= 126;

const int _ACTION_JUMP	        = 130;
const int _ACTION_JUMP_BACK	    = 131;
const int _ACTION_JUMP_RUN	    = 132;

const int _ACTION_JUMP_ATK		= 140;
const int _ACTION_JUMP_ATKEND	= 141;

const int _ACTION_LAUGH			= 140;
const int _ACTION_GUFFAW		= 151;
const int _ACTION_FURY          = 160;
const int _ACTION_SAD	        = 150;
const int _ACTION_EXCITEMENT	= 180;
const int _ACTION_SAYHELLO		= 190;
const int _ACTION_SALUTE		= 160;
const int _ACTION_GENUFLECT     = 170;
const int _ACTION_KNEEL			= 220;
const int _ACTION_COOL			= 230;
const int _ACTION_COOLPOSE		= 231;
const int _ACTION_SWIM			= 240;
const int _ACTION_SITDOWN       = 250;
const int _ACTION_SITDOWN_STATIC = 251;

const int _ACTION_ZAZEN			= 260;
const int _ACTION_ZAZENCOOL		= 261;
const int _ACTION_FAINT	        = 190;
const int _ACTION_LIE	        = 200;

const int _ACTION_PICKUP		= 262;
const int _ACTION_MINE			= 360;


const int _ACTION_ALERT			= 340;
const int _ACTION_ALERT_I		= 305;

const int _ACTION_DODGE0		= 311;

const int _ACTION_BRUISE0		= 321;
const int _ACTION_BRUISE1		= 321;


const int _ACTION_DIE0			= 330;
const int _ACTION_BODY0			= 331;
const int _ACTION_DIE1			= 332;
const int _ACTION_BODY1			= 333;
const int _ACTION_DIE2			= 334;
const int _ACTION_BODY2			= 335;
const int _ACTION_DIE3			= 336;
const int _ACTION_BODY3			= 337;

const int _ACTION_DIEFLY		= 340;
const int _ACTION_DIEFLYEND		= 341;
const int _ACTION_WALKBACK      = 342;

const int _ACTION_ATTACK0	    = 350;
const int _ACTION_ATTACK1	    = 351;
const int _ACTION_ATTACK2	    = 352;

const int _ACTION_RELIVE		= 400;

const int _ACTION_PUNCTURE	    = 451;
const int _ACTION_AIRSTRIKE		= 452;
const int _ACTION_TORNADO	    = 453;

const int _ACTION_BODYSHIELD	= 460;
const int _ACTION_GODBELIEVE	= 465;
const int _ACTION_BUMP			= 470;
const int _ACTION_POPOFF		= _ACTION_BRUISE0;

const int _ACTION_INTONE			= 390;
const int _ACTION_INTONE_DURATION	= 391;
const int _ACTION_INTONE_LAUNCH		= 392;

const int _ACTION_FLY_STANDBY	= 501;
const int _ACTION_FLY_ALERT		= 502;
const int _ACTION_FLY_MOVE		= 510;
const int _ACTION_FLY_ATTACK	= 520;

const int _ACTION_FLY_DOWN		= 530;
const int _ACTION_FLY_UP		= 540;
const int _ACTION_FLY_DIE		= 550;
const int _ACTION_FLY_WOUND		= 560;
const int _ACTION_JUMPBACK_SHOOT = 610;
const int _ACTION_FAST_SHOOT	= 620;
const int _ACTION_CHARGEUP_BEGIN = 630;
const int _ACTION_CHARGEUP_END	= 631;

const int _ACTION_TM_FAST_SHOOT			= 800;
const int _ACTION_TM_DISPERSION_SHOOT	= 801;






//---------------------------------------------------------------------
// my win message define
#ifndef WM_MY_MESSAGE
#define WM_MY_MESSAGE (WM_USER+100)

const int CMD_NORMAL			= 1000;
const int CMD_OPENSHOP			= CMD_NORMAL + 1;	// ���̵�
const int CMD_CLOSESHOP			= CMD_NORMAL + 2;	// �ر��̵�

const int CMD_FLASHITEM			= CMD_NORMAL + 3;	// ˢ����Ʒ��
const int CMD_FLASHMONEY		= CMD_NORMAL + 4;	// ˢ��Ǯ

const int CMD_OPENTRADE			= CMD_NORMAL + 5;	// �򿪽��״���
const int CMD_TRADEOK			= CMD_NORMAL + 6;	// ���׳ɹ� // ��ʾ���׳ɹ�//�رս��״���
const int CMD_TRADEFALSE		= CMD_NORMAL + 7;	// ����ȡ�� // ��ʾ����ȡ��//�رս��״���

const int CMD_TRADPLAYERMONEY	= CMD_NORMAL + 8;	// ˢ�½��׽���Է���Ǯ
const int CMD_TRADHEROEMONEY	= CMD_NORMAL + 9;	// ˢ�½��׽����Լ���Ǯ

const int CMD_TRADEPLAYERITEM	= CMD_NORMAL + 10;	// ˢ�½��׽���Է�����Ʒ
const int CMD_TRADEHEROITEM		= CMD_NORMAL + 12;	// ˢ�½��׽����Լ�����Ʒ

const int CMD_TRADEPLAYERAGREE	= CMD_NORMAL + 13;	// �Է�ͬ�⽻�� // �����Է�ͳһ���ױ�ʶ
const int CMD_TRADEPLAYERAPPLY	= CMD_NORMAL + 14;	// �Է����뽻�� // �����Ƿ�Ը��ͶԷ����׵Ĵ���

const int CMD_FLASHPACKAGEITEM	= CMD_NORMAL + 15;	// ˢ��Package ����Ʒ
const int CMD_FLASHBANKMONEY	= CMD_NORMAL + 16;	// ˢ�����еĴ��

const int CMD_TASKDIALOGOPEN	= CMD_NORMAL + 17;	// ��������Ի���
const int CMD_FLASHFRIENDLIST	= CMD_NORMAL + 18;	// ˢ�º����б�

const int CMD_FLASHEQUIPMENT	= CMD_NORMAL + 19;	// ˢ��װ����

const int CMD_FLASHTEAM			= CMD_NORMAL + 20;	// ˢ����Խ���
const int CMD_TEAMINVITE		= CMD_NORMAL + 21;	// ��������������
const int CMD_TEAMAPPLY			= CMD_NORMAL + 22;	// ��������������

const int CMD_FLASHWEAPONSKILL	= CMD_NORMAL + 23;	// ˢ����������
const int CMD_CHANGEPKMODE		= CMD_NORMAL + 24;	// �ı�PKģʽ
const int CMD_SETPKMODE			= CMD_NORMAL + 25;	// ����PKģʽ

const int CMD_LEVELUP			= CMD_NORMAL + 26;	// ��������
const int CMD_FLASHPK			= CMD_NORMAL + 27;	// ˢ��PKֵ

const int CMD_FLASHCHATLOGFILELIST			= CMD_NORMAL + 28;	// ˢ�������¼�ļ��б�
const int CMD_FLASHCURRENTCHATLOGLINELIST	= CMD_NORMAL + 29;	// ˢ�´򿪵������¼���б�

const int CMD_FLASH_MAGIC					= CMD_NORMAL + 30;  // ˢ��ħ���б�
const int CMD_FLASH_MAGIC_EXP				= CMD_NORMAL + 31;  // ˢ��ħ������

const int CMD_SYNDICATE_APPLY				= CMD_NORMAL + 32;  // ������������������
const int CMD_SYNDICATE_INVITE				= CMD_NORMAL + 33;  // ����������������
const int CMD_FLASH_SYNDICATE				= CMD_NORMAL + 34;  // ˢ�����ǵİ�����Ϣ�������������ƣ��ƺţ�

const int CMD_START_MAGIC_BUSY				= CMD_NORMAL + 35;	// ��ʼħ����ʱ
const int CMD_END_MAGIC_BUSY				= CMD_NORMAL + 36;	// ����ħ����ʱ

const int CMD_XPFULL						= CMD_NORMAL + 37;	// XP����
const int CMD_XPEMPTY						= CMD_NORMAL + 38;	// XP����
const int CMD_XPCHANGE						= CMD_NORMAL + 39;	// XP�ı�

const int CMD_QUERYFRIEND_OK				= CMD_NORMAL + 40;	// ��ѯ���ѳɹ�
const int CMD_QUERYFRIEND_TIMEOUT			= CMD_NORMAL + 41;	// ��ѯ���ѳ�ʱ

const int CMD_FLASH_TEAM_FACE				= CMD_NORMAL + 42;	// ˢ�¶�Աͷ��
const int CMD_FLASH_HERO_FACE				= CMD_NORMAL + 43;	// ˢ������ͷ��

const int CMD_FLASH_SYNDICATE_WORD			= CMD_NORMAL + 44;	// ˢ�°�������

const int CMD_DIE							= CMD_NORMAL + 50;	// ��������
const int CMD_REBORN						= CMD_NORMAL + 51;	// ���Ǹ���

const int CMD_FRIEND_APPLY					= CMD_NORMAL + 52;	// ��������Ӻ���

const int CMD_GHOST_BEGIN					= CMD_NORMAL + 53;	// ��ʼ���״̬
const int CMD_GHOST_END						= CMD_NORMAL + 54;	// �������״̬

const int CMD_PPCHANGE						= CMD_NORMAL + 55;	// ���������仯
const int CMD_MAXPPCHANGE					= CMD_NORMAL + 56;	// �����������

const int CMD_FLASH_LEAVE_WORD				= CMD_NORMAL + 57;	// ˢ������
const int CMD_NEW_LEAVE_WORD				= CMD_NORMAL + 58;	// �µ�����

const int CMD_FLASH_SYN_WAR_REPORT			= CMD_NORMAL + 59;	// ˢ�°���ս��

const int CMD_CHANGE_MAP					= CMD_NORMAL + 60;	// ����

const int CMD_FLASH_BOOTH_ITEM				= CMD_NORMAL + 62;	// ˢ�±��˰�̯��Ʒ
const int CMD_FLASH_BOOTHMANAGER_ITEM		= CMD_NORMAL + 63;	// ˢ���Լ���̯��Ʒ

const int CMD_FLASH_BULLETIN_LIST			= CMD_NORMAL + 64;	// ˢ�¹����б�
const int CMD_FLASH_BULLETIN_NOTE			= CMD_NORMAL + 65;	// ˢ�¹�������

const int CMD_OPEN_PLACE_STATUARY_DIALOG	= CMD_NORMAL + 66;	// �򿪷��õ������
const int CMD_COURT							= CMD_NORMAL + 67;	// ���
const int CMD_BECOURT						= CMD_NORMAL + 68;	// �����

const int CMD_OPEN_PLACE_NPC_INFO_DIALOG	= CMD_NORMAL + 69;	// �򿪷���npc��ʾ����
const int CMD_OPEN_PLACE_NPC_MODIFY_DIALOG	= CMD_NORMAL + 70;	// �򿪵���npc����

const int CMD_OPEN_FLASH_SYN_MEMBER			= CMD_NORMAL + 71;	// ˢ�°��ɳ�Ա�б�
const int CMD_OPEN_FLASH_SYN_MEMBER_INFO	= CMD_NORMAL + 72;	// ˢ�°��ɳ�Ա��Ϣ

const int CMD_FLASH_MAGIC_STATUS			= CMD_NORMAL + 73;	// ˢ��ħ��״̬
const int CMD_FLASH_OTHERPLAYER_EQUIPMENT	= CMD_NORMAL + 74;	// ˢ�¿�����װ������

const int CMD_OPEN_ABORT_TRANSFORM_DLG		= CMD_NORMAL + 75;	// ��ȡ���������
const int CMD_CLOSE_ABORT_TRANSFORM_DLG		= CMD_NORMAL + 76;	// �ر�ȡ���������

const int CMD_DICE_JOIN						= CMD_NORMAL + 77;	// ����ľ�
const int CMD_DICE_QUIT						= CMD_NORMAL + 78;	// �뿪�ľ�
const int CMD_DICE_FLASH_PLAYERLIST			= CMD_NORMAL + 79;	// ˢ�ľ�����б�
const int CMD_DICE_FLASH_ANTES				= CMD_NORMAL + 80;	// ˢ�ľֶ�ע�б�

const int CMD_FLASHENEMYLIST				= CMD_NORMAL + 81;	// ˢ�³����б�
const int CMD_QUERYENEMY_OK					= CMD_NORMAL + 82;	// ��ѯ���˳ɹ�
const int CMD_QUERYENEMY_TIMEOUT			= CMD_NORMAL + 83;	// ��ѯ���˳�ʱ

const int CMD_RESET							= CMD_NORMAL + 84;	// ����

const int CMD_RESOURCE_LOSE					= CMD_NORMAL + 85;  // �ڶ�����Դ������
const int CMD_ACTION_MESSAGEBOX				= CMD_NORMAL + 86;  // ��Ϣ��
const int CMD_ACTION_IDENTBOX				= CMD_NORMAL + 87;  // ������
const int CMD_FRIEND_ACCEPT					= CMD_NORMAL + 88;  // �ύ���ѳɹ�

const int CMD_ACTION_SELECTEMBLEM			= CMD_NORMAL + 89;  // ���ɻ���ѡ���
const int CMD_ACTION_OPENDIALOG				= CMD_NORMAL + 90;  // �򿪶Ի���

const int CMD_ACTION_TEACHAPPLY				= CMD_NORMAL + 91;  // ���������ʦ��
const int CMD_ACTION_STUDENTAPPLY			= CMD_NORMAL + 92;  // ����Ҫ������ͽ��
const int CMD_FLASH_SCHOOLINFO				= CMD_NORMAL + 93;  // ˢ��ʦͽ�б�

const int CMD_FLASH_PLAYERTASKLIST			= CMD_NORMAL + 94;	// ˢ����������б�
const int CMD_FLASH_PLAYERTASKDETIAL		= CMD_NORMAL + 95;	// ˢ�����������ϸ��Ϣ

const int CMD_ACTION_ACCEPTEDTASKLIST			= CMD_NORMAL + 96;  // ��Ӷ�������б�-δ���
const int CMD_ACTION_UNACCEPTEDTASKLIST			= CMD_NORMAL + 97;  // ��Ӷ�������б�-δ���
const int CMD_ACTION_COMPLETEDTASKLIST			= CMD_NORMAL + 98;  // ��Ӷ�������б�-δ���
const int CMD_ACTION_MYTASKLIST					= CMD_NORMAL + 99;  // ��Ӷ�������б�-δ���
const int CMD_ACTION_PLAYERTASKUP				= CMD_NORMAL + 100; // ��Ӷ�������´����
const int CMD_ACTION_OPENSHOP					= CMD_NORMAL + 101; // ���̵����
const int CMD_ACTION_OPENEMBED					= CMD_NORMAL + 103; // װ����������
const int CMD_ACTION_OPENDEPOT					= CMD_NORMAL + 104;	// �ֿ����

const int CMD_ACTION_OPENUPANNOUNCE					= CMD_NORMAL + 105;		//���ֹ��ᷢ������
const int CMD_ACTION_OPENANNOUNCELIST				= CMD_NORMAL + 106;     //���ֹ��ṫ���б�
const int CMD_ACTION_OPENMYANNOUNCE					= CMD_NORMAL + 107;		//���ֹ����ҵĹ���

const int CMD_FLASH_ANNOUNCEINFO					= CMD_NORMAL + 108;		//ˢ�¹�����Ϣ
const int CMD_FLASH_ANNOUNCELIST					= CMD_NORMAL + 109;		//ˢ�¹����б�

const int CMD_ACTION_OPENMONSTERHATCH				= CMD_NORMAL + 110;		//�򿪻ó������
const int CMD_ACTION_OPENMONSTERALIVE				= CMD_NORMAL + 111;		//�򿪻ó踴��
const int CMD_ACTION_OPENMONSTERIMPROVE				= CMD_NORMAL + 112;		//�򿪻ó�ǿ��
const int CMD_ACTION_OPENMONSTERDEPOT				= CMD_NORMAL + 113;		//�򿪻ó�ֿ�
const int CMD_FLASH_SECSCHOOLLIST					= CMD_NORMAL + 114;		//ˢ�¶���ͽ���б�

const int CMD_ACTION_OPENNPCFACE					= CMD_NORMAL + 115;		//��NPC FACE DIALOG
const int CMD_ACTION_OPENBOOTH						= CMD_NORMAL + 116;		//�򿪰�̯����
const int CMD_ACTION_OPENBOOTHFLAG					= CMD_NORMAL + 117;		//�򿪰�̯ȷ������
const int CMD_ACTION_OPENDICECFM					= CMD_NORMAL + 118;		//�򿪶���ȷ������

const int CMD_ACTION_OPENADDAUCTION					= CMD_NORMAL + 119;		//��������Ʒ�������
const int CMD_ACTION_OPENAUCTIONBID					= CMD_NORMAL + 120;		//��������Ʒ�������
const int CMD_ACTION_FLASHAUCTION					= CMD_NORMAL + 121;		//ˢ��������Ʒ�������
const int CMD_ACTION_NEWAUCTION						= CMD_NORMAL + 122;		//��ʼ�µ�������Ʒ
const int CMD_ACTION_OVERAUCTION					= CMD_NORMAL + 123;		//��ǰ��������

const int CMD_ACTION_OPENIMPROVE					= CMD_NORMAL + 124;	// װ��Ʒ����������
const int CMD_ACTION_OPENIMPROVESOUL				= CMD_NORMAL + 125;	// װ��ħ����������
const int CMD_ACTION_OPENIMPROVELEVEL				= CMD_NORMAL + 126;	// װ���ȼ���������
const int CMD_ACTION_OPENIMPROVEGEM					= CMD_NORMAL + 127;	// װ����ʯ��Ƕ����

const int CMD_ACTION_CLOSEBOOTH						= CMD_NORMAL + 128; // �رմ򿪵�̯λ

const int CMD_ACTION_OPENAUCPACKAGE					= CMD_NORMAL + 129; // ����������ֿ�

const int CMD_FLASH_MYPETINFO						= CMD_NORMAL + 130; // �������»��޵ľ���ֵ��HPֵ
const int CMD_FLASH_PETSTATUS						= CMD_NORMAL + 131; // ˢ�»�����Ϣ-�ٻ�������

const int CMD_FLASH_SYNDOC							= CMD_NORMAL + 150; // ˢ�¾��Ź����б�
const int CMD_FLASH_SYNALLY							= CMD_NORMAL + 151; // ˢ�µ��Ѿ����б�

const int CMD_EVOMONSTER_SUC						= CMD_NORMAL + 152;	// ���޽����ɹ�

const int CMD_ACTION_EVOMONSTERG						= CMD_NORMAL + 153; // ����һ�ν�������-ʥ��
const int CMD_ACTION_EVOMONSTERS						= CMD_NORMAL + 154;	// ����һ�ν�������-ħ��

const int CMD_ACTION_EVOMONSTER1						= CMD_NORMAL + 155; // ���޶��ν�������-����֮��
const int CMD_ACTION_EVOMONSTER2						= CMD_NORMAL + 156;	// ���޶��ν�������-��������
const int CMD_ACTION_EVOMONSTER3						= CMD_NORMAL + 157; // ���޶��ν�������-����֮��
const int CMD_ACTION_EVOMONSTER4						= CMD_NORMAL + 158;	// ���޶��ν�������-��ı֮��
const int CMD_ACTION_EVOMONSTER5						= CMD_NORMAL + 159; // ���޶��ν�������-�ǻ�֮��
const int CMD_ACTION_EVOMONSTER6						= CMD_NORMAL + 160; // ���޶��ν�������-ս��֮��
const int CMD_ACTION_EVOMONSTER7						= CMD_NORMAL + 161; // ���޶��ν�������-����֮��
const int CMD_ACTION_EVOMONSTER8						= CMD_NORMAL + 162; // ���޶��ν�������-����֮��

const int CMD_OPEN_FLASH_SYNINFO						= CMD_NORMAL + 163;	// ��ѯ������Ϣ����
const int CMD_ACTION_ADDALLY							= CMD_NORMAL + 164; // �յ���������
const int CMD_CALL_PET_OUT                              = CMD_NORMAL + 165; // ��ҽ����ͼ�������еĻ��޳���
const int CMD_PET_DIE                                   = CMD_NORMAL + 166;
const int CMD_PET_ALIVE                                 = CMD_NORMAL + 167;
void PostCmd(DWORD dwCommand, int nData = 0);
#endif

extern HWND g_hGameWnd;
extern BOOL g_bLocalVersion;
//---------------------------------------------------------------------
#endif
