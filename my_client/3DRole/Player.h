
//**********************************************************
// ����༭��
//**********************************************************

// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__EF9F33AA_217F_4793_A28A_4F3C56254D27__INCLUDED_)
#define AFX_PLAYER_H__EF9F33AA_217F_4793_A28A_4F3C56254D27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Role.h"
#include <deque>
#include <vector>
#include "EncryptData.h"
#include "ImageString.h"
#include "FDword.h"
using namespace std;


const int RANKAMOUNT = 7;
const int FLASHCRIME_TIME = 100000; //������ʾѪ��ʱ��10��

enum // ��λ����
{
    CIVILIAN	=	0,	// ƽ��
    BARON		=	1,	// ��ʿ
    VISCOUNT	=	2,	// �Ӿ�
    EARL		=	3,	// ����
    MARQUESS	=	4,	// ���
    DUKE		=	5,	// ����
};
typedef struct
{
    DWORD	dwRank;
    OBJID	idTitle;
    //char	szTitle[_MAX_NAMESIZE];
} InfoSyndicateRank;
enum
{
    RANK_LEADER			= 100,
    RANK_ASSISTANT		= 90,
    RANK_SUBLEADER		= 80,
    RANK_SUBASSISTANT	= 70,
    RANK_TEAMLEADER		= 60,
    RANK_SAN			= 50,			// ʥ��ʿ�������ʿ��ʮ�־���ʿ��Ǿޱ��ʿ����ʿ
    RANK_LIGHT			= 40,
    RANK_CROSS			= 30,
    RANK_NEWBIE			= 20,
    RANK_RESERVED		= 10,
    RANK_NONE			= 0,
};
const InfoSyndicateRank SYNDICATERANKINFOSET[RANKAMOUNT] =
{
    {RANK_LEADER , 100079},		//�����ų� 100
    {RANK_SUBLEADER , 100080},	//���ų� 80
    {RANK_TEAMLEADER , 100081}, //�ӳ� 60
    {RANK_NEWBIE , 100120},		//��ͨ��Ա 20
    {RANK_RESERVED , 100121},	//Ԥ����Ա 10
    {RANK_NONE, 100122},		// 0
    //	{RANK_LEADER, 100079},
    //	{RANK_ASSISTANT, 100080},
    //	{RANK_NEWBIE, 100081},
    //	{RANK_NONE, 100021},
    //	{RANK_SUBLEADER, 100120},
    //	{RANK_SUBASSISTANT, 100122},
    //	{RANK_PRESUBLEADER, 100121},
};

struct TimerCmdInfo
{
    CCommand	cmd;
    DWORD		tmExecute;
    std::string	strEffect;
    std::string strSound;
};

// �����Ϣ
class CPlayerInfo
{
public:
    CPlayerInfo()
    {
        Reset();
    }
	~CPlayerInfo()
	{
		setHonorTitle.clear();
        setMedal.clear();
		setCmd.clear();
	}

	void Reset()
	{
		dwProfession			= 0;
		dwPhysicalForce			= 0;	// ����ֵ
		dwMaxPhysicalForce		= 0;	// �������ֵ

		dwLev					= 0;
		dwAddPoint				= 0;
		dwMedalSelect			= 0;
		nPotential				= 0;	//Ǳ��
		nRepute					= 0;
		nDeed					= 0;
		nExp					= 0;
		nPk						= 0;
		idSyndicate				= 0;
		ucSyndicateSynRank		= 0;	//���ŵȼ�
		dwSyndicateRank			= 0;	//���ޣ���������id
		uiSyndicateLevel		= 0;	// �����еĵȼ�
		nSyndicateProffer		= 0;
		dwSyndicateFamer		= 0;
		dwSyndicateFund			= 0;	// ���ɻ���
		dwSyndicatePopulation	= 0;	// �����˿�
		dwKoAmount				= 0;
		dwVirtue				= 0;
		bShowIcon				= 0;

		dwMercenaryLevel		= 0;	// Ӷ���ȼ�
		dwMercenaryExp			= 0;	// Ӷ������
		dwSelectHonorTitle		= 0;	// �ƺš���ʾ�ĳƺ�

		dwNobilityRank			= 0;	// ��λ
		dwExploit				= 0;	// ��ѫ

		dwTutorLevel			= 0;	// ��ʦ�ȼ�
		dwTutorExp				= 0;	// ��ʦ����

		dataLife.Reset();
		dataMana.Reset();
		dataCurLife.Reset();
		dataCurMana.Reset();

		memset(szMate, 0, sizeof(szMate));
		memset(szSyndicateLeader, 0, sizeof(szSyndicateLeader));
		
		setCmd.clear();
		setHonorTitle.clear();
        setMedal.clear();
	}

    char	szMate[_MAX_NAMESIZE];
    DWORD	dwForce, dwDexterity, dwConstitution, dwSpeed, dwHealth, dwSoul, dwXP, dwMaxLife, dwMaxLifePercent;

    CEncryptData dataLife;
    CEncryptData dataMana;
    CEncryptData dataCurLife;
    CEncryptData dataCurMana;

    DWORD	dwProfession;
    DWORD	dwPhysicalForce;			// ����ֵ
    DWORD	dwMaxPhysicalForce;			// �������ֵ

    DWORD	dwLev;
    DWORD	dwAddPoint;
    DWORD	dwMedalSelect;
    int		nPotential;	//Ǳ��
    int		nRepute;
    int		nDeed;
    int		nExp;
    int		nPk;
    OBJID	idSyndicate;
    UCHAR	ucSyndicateSynRank;		//���ŵȼ�
    DWORD	dwSyndicateRank;		//���ޣ���������id
    UINT	uiSyndicateLevel;		// �����еĵȼ�
    int		nSyndicateProffer;
    DWORD	dwSyndicateFamer;
    char	szSyndicateLeader[_MAX_NAMESIZE];	// ����
    DWORD	dwSyndicateFund;			// ���ɻ���
    DWORD	dwSyndicatePopulation;		// �����˿�
    DWORD	dwKoAmount;
    DWORD	dwVirtue;
    BOOL	bShowIcon;

    DWORD	dwMercenaryLevel;			// Ӷ���ȼ�
    DWORD	dwMercenaryExp;				// Ӷ������
    DWORD	dwSelectHonorTitle;			// �ƺš���ʾ�ĳƺ�

    DWORD	dwNobilityRank;				// ��λ
    DWORD	dwExploit;					// ��ѫ

    DWORD	dwTutorLevel;				// ��ʦ�ȼ�
    int		dwTutorExp;					// ��ʦ����

    deque<CCommand>			setCmd;
    vector<unsigned char>	setHonorTitle;
    vector<unsigned char>	setMedal;
} /*CPlayerInfo*/;

class CPlayer: public CRole
{
public:
    enum
    {
        _PLAYER_LIFE		= 1,
        _PLAYER_CURRENTLIFE = 15,
        _PLAYER_MANA		= 9,
        _PLAYER_CURRENTMANA	= 5,
    };
    enum
    {
        PROFSORT_MAGICIAN	= 1,
        PROFSORT_SOLDIER	= 2,
        PROFSORT_ARCHER		= 3,
    };
public:
    DWORD	GetData(DWORD dwDataType);
    virtual void		SetData(DWORD dwDataType, DWORD dwData);
public:	// virtual...
    virtual void	Show		(void* pInfo);
    virtual void	Process		(void* pInfo);

    virtual DWORD	SetCommand	(CCommand* pCommand);

public:
    void SetTimerCommand	(CCommand& cmd, DWORD tmExecute, const char* pszEffect = NULL, const char* pszSound = NULL);
    void ClrTimerCommand	(void);
    bool ProcessTimerCommand(void);

private:
    std::list< TimerCmdInfo > m_setCmdList;

public:
    CPlayer();
    virtual ~CPlayer();

    static	BOOL	s_bShowName;

    void	ShowSyndicate	();
    void	ShowInfo		();
    void	ShowName		();
    void	ShowLife		();

    BOOL	IsSynLeader		()  { return (strcmp(this->GetSyndicateLeaderName(), this->GetName()) == 0);}
    BOOL	IsDead			()	{ return (this->GetStatus()&USERSTATUS_DIE) != 0; }
    BOOL	IsGhost			()	{ return (this->GetStatus()&USERSTATUS_GHOST) != 0; }

    //--------- info ---------
public:

    virtual DWORD			GetHonorTitleAmount();
    virtual const char*		GetHororTitle(int nIndex);
    virtual unsigned char	GetHororTitleIndex(int nIndex);
    virtual void			AddHororTitle(int nIndex);

    virtual DWORD			GetMedalAmount();
    virtual const char*		GetMedale(int nIndex);
    virtual unsigned char	GetMedaleIndex(int nIndex);
    virtual void			AddMedaleTitle(int nIndex);

    void    SetFlashCrime();
    BOOL    IsFlashCrime();
    const CPlayerInfo* GetPlayerInfo() const {return &m_PlayerInfo;}

    DWORD	GetVirtue() {return m_PlayerInfo.dwVirtue;}
    void	SetVirtue(DWORD dwVirtue) {m_PlayerInfo.dwVirtue = dwVirtue;}
    const char*	GetMate() const {return m_PlayerInfo.szMate;}
    void	SetMate(const char* pszMate);

    virtual DWORD	GetMercenaryLevel();
    virtual	void	SetMercenaryLevel(DWORD dwMercenaryLevel);
    virtual DWORD	GetMercenaryExp();
    virtual	void	SetMercenaryExp(DWORD dwMercenaryExp);

    virtual DWORD	GetSelectedHonorTitle();
    virtual	void	SetSelectedHonorTitle(DWORD dwSelectedTitle);

    virtual DWORD	GetNobilityRank();
    virtual	void	SetNobilityRank(DWORD dwNobilityTitle);
    virtual	char*	GetNobilityTitle();

    virtual	DWORD	GetLife();
    virtual void	SetLife(DWORD dwLife);

    virtual	DWORD	GetCurLife();
    virtual	void	SetCurLife(int nLife);

    virtual	DWORD	GetCurMana();
    virtual	void	SetCurMana(int nMana);

    void    SetMaxLifePercent(DWORD  dwMaxLifePercent) {m_PlayerInfo.dwMaxLifePercent = dwMaxLifePercent;}
    DWORD	GetMaxLifePercent() {return m_PlayerInfo.dwMaxLifePercent;}
    DWORD	GetExploit() const {return m_PlayerInfo.dwExploit;}
    void	SetExploit(DWORD dwExploit) {m_PlayerInfo.dwExploit = dwExploit;}

    int		GetRepute() const {return m_PlayerInfo.nRepute;}
    void	SetRepute(int nRepute) {m_PlayerInfo.nRepute = nRepute;}

    int		GetDeed() const	{return m_PlayerInfo.nDeed;}
    void	SetDeed(int nDeed) {m_PlayerInfo.nDeed = nDeed;}

    int		GetExp() const	{return (this->GetLev() >= _MAX_LEVEL ?  0 : m_PlayerInfo.nExp);}
    void	SetExp(int nExp) {m_PlayerInfo.nExp = nExp;}

    int		GetPk() const {return m_PlayerInfo.nPk;}
    void	SetPk(int nPk) {m_PlayerInfo.nPk = nPk; PostCmd(CMD_FLASHPK);}

    DWORD	GetLev() const	{return m_PlayerInfo.dwLev;}
    void	SetLev(DWORD dwLev) {m_PlayerInfo.dwLev = dwLev;}

    DWORD	GetForce() const {return m_PlayerInfo.dwForce;}
    void	SetForce(DWORD dwForce) {m_PlayerInfo.dwForce = dwForce;}

    DWORD   GetConstitution() const {return m_PlayerInfo.dwConstitution;}
    void	SetConstitution(DWORD dwConstitution) {m_PlayerInfo.dwConstitution = dwConstitution;}

    //	DWORD	GetPhysique() const {return m_PlayerInfo.dwPhysique;}
    //	void	SetPhysique(DWORD dwPhysique) {m_PlayerInfo.dwPhysique = dwPhysique;}

    void	SetSpeed(DWORD dwSpeed) {m_PlayerInfo.dwSpeed = dwSpeed;}
    DWORD   GetSpeed() {return m_PlayerInfo.dwSpeed;}

    DWORD	GetHealth() const {return m_PlayerInfo.dwHealth;}
    void	SetHealth(DWORD dwHealth) {m_PlayerInfo.dwHealth = dwHealth;}

    virtual DWORD	GetSoul() const {return m_PlayerInfo.dwSoul;}
    void	SetSoul(DWORD dwSoul) {m_PlayerInfo.dwSoul = dwSoul;}

    virtual	DWORD	GetMana();
    virtual	void	SetMana(DWORD dwMana);

    DWORD	GetProfession() const {return m_PlayerInfo.dwProfession;}
    void	SetProfession(DWORD dwProfession) {m_PlayerInfo.dwProfession = dwProfession;}

    DWORD	GetAddPoint() const {return m_PlayerInfo.dwAddPoint;}
    void	SetAddPoint(DWORD dwAddPoint) {m_PlayerInfo.dwAddPoint = dwAddPoint;}

    DWORD	GetMedalSelect() const {return m_PlayerInfo.dwMedalSelect;}
    virtual	void	SetMedalSelect(DWORD dwMedalSelect) {m_PlayerInfo.dwMedalSelect = dwMedalSelect;}

    DWORD	GetXP() const {return m_PlayerInfo.dwXP;}
    void	SetXP(DWORD dwXP) {m_PlayerInfo.dwXP = __min(100, dwXP);}

    void	SetKoAmount(DWORD dwAmount)	{m_PlayerInfo.dwKoAmount = dwAmount; m_dwKoScale = 100;}
    DWORD	GetKoAmount()	{return m_PlayerInfo.dwKoAmount;}



    DWORD	GetProfessionSort	()	{ return (m_PlayerInfo.dwProfession % 1000) / 10; }
    DWORD	GetProfessionLevel	()	{ return m_PlayerInfo.dwProfession % 10; }

    virtual DWORD GetMaxLife() const {return m_PlayerInfo.dwMaxLife;}
    virtual void SetMaxLife(DWORD dwMaxLife) ;

    virtual void DoLevelUp();

    virtual void ReplaceStatus	(__int64 dwStatus);
    virtual	void	SetSyndicateRank(DWORD dwRank);

    // syndicate interfaces
    OBJID	GetSydicateID();
    void	SetSyndicateID(OBJID idSyndicate);
    DWORD	GetSyndicateRank();
    int		GetSyndicateProffer();
    void	SetSyndicateProffer(int nSyndicateProffer);
    DWORD	GetSyndicateFamer();
    void	SetSyndicateFamer(DWORD dwSyndicateFamer);
    char*	GetSyndicate();
    char*	GetSubSyndicate();
    char*	GetSyndicateTitle();
    UINT	GetSyndicateLevel();
    void	SetSyndicateLevel(UINT uiLevel);
    // additioncal syndicate interfaces
    char*	GetSyndicateLeaderName();
    void	SetSyndicateLeaderName(char* pszLeader);
    DWORD	GetSyndicateFund();
    void	SetSyndicateFund(DWORD dwFund);
    DWORD	GetSyndicatePopulation();
    void	SetSyndicatePopulation(DWORD dwPopulation);
    void	SetSyndicateSynRank(UCHAR ucSynRank) {m_PlayerInfo.ucSyndicateSynRank = ucSynRank;}
    UCHAR	GetSyndicateSynRank() {return m_PlayerInfo.ucSyndicateSynRank;}
    DWORD	GetPhysicalForce() {return __min(m_PlayerInfo.dwPhysicalForce, this->GetMaxPhysicalForce());}
    DWORD	GetMaxPhysicalForce() {return m_PlayerInfo.dwMaxPhysicalForce;}
    void	SetPhysicalForce(DWORD dwForce) {m_PlayerInfo.dwPhysicalForce = dwForce;}
    void	SetMaxPhysicalForce(DWORD dwMaxForce) {m_PlayerInfo.dwMaxPhysicalForce = dwMaxForce;}
    void	SetCryOut(char* pszStr) {if (pszStr) { strcpy(m_szCryOut, pszStr); }}
    char*	GetPkTitle();
    void	AddProfessionalCoolposEffect(DWORD dwProfessional, BOOL bAllNosuch = true);

    BOOL	IsBaddy();

    void	ShowKoAmount	(BOOL bImmedia = true);
    void	AddMoneyEffect	(DWORD dwMoney);

    void	ProcessStatusEffect(__int64 dwStatus);

    void	SetShowIcon(BOOL bShow) {m_PlayerInfo.bShowIcon = bShow;}
    BOOL	GetShowIcon() {return m_PlayerInfo.bShowIcon;}

    void	SetTutorLevel(DWORD dwTutorLevel);
    void	SetTutorExp(int dwTutorExp);

    DWORD   GetTutorLevel();
    int 	GetTutorExp();

    void    SetDexterity(DWORD dwDexterity) {m_PlayerInfo.dwDexterity = dwDexterity;}
    void	SetPotential(int nPotential) {m_PlayerInfo.nPotential = nPotential;}

    DWORD   GetDexterity() {return m_PlayerInfo.dwDexterity;}	//����
    int		GetPotential() {return m_PlayerInfo.nPotential;}    //Ǳ��
    void    SynTrack(BOOL bMove = true);
    void	SetNpcTitle(const char* pszTitle);

    // for pet
    void	SetPetOwnerId(OBJID idOwner) { m_PlayerInfo.dwSyndicateRank = idOwner;}
    OBJID	GetPetOwnerId() {return m_PlayerInfo.dwSyndicateRank;}

    void    SetIDWhoAttackMe(OBJID id) {m_idWhoAttackMe = id; m_dwTimeWhoAttackMe = ::TimeGet();}
    OBJID	GetIDWhoAttackMe() {return m_idWhoAttackMe;}
    DWORD	GetTimeWhoAttackme() {return m_dwTimeWhoAttackMe;}

protected:
    OBJID	m_idWhoAttackMe;
    DWORD   m_dwTimeWhoAttackMe;
    int     m_nAttackTimes;
public:
    void SetAttackTimes(int nTimes) {m_nAttackTimes = nTimes;}
    int  GetAttackTimes(void) { return m_nAttackTimes > 0 ? m_nAttackTimes : 0;}
protected:
    CPlayerInfo		m_PlayerInfo;
    char			m_szCryOut[256];
    char			m_szNpcTitle[128];
    DWORD			m_dwKoScale;
    CImageString	m_objImgNumber;
    BOOL			m_bFlashCrime;
    DWORD           m_dwFlashCrimeTime;

public:
    static HANDLE	s_hHeap;
    static UINT		s_uNumAllocsInHeap;

    static BOOL		IsValidPt	(void* p);

    void*	operator new		(size_t size);
    void	operator delete		(void* p);
private:
    CFDword*	m_pFD;
};

#endif // !defined(AFX_PLAYER_H__EF9F33AA_217F_4793_A28A_4F3C56254D27__INCLUDED_)
