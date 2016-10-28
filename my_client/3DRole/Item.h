
//**********************************************************
// ����༭��
//**********************************************************

#ifndef _ITEM_H
#define _ITEM_H

#include "basefunc.h"
#include "ItemData.h"
//#include "3DSimpleObj.h"
#include "2DMapItem.h"
#include "IItemPackage.h"

const int _ARROW	=	170001;	// ��
const int _DART		=	171001;	// ���

// monopoly define ��ռ��Ʒ����
const int _NOT_MONOPOLY_NOT_DISAPPEAR	=	0;//0���Ƕ�ռ��һ����Ʒ
const int _NOT_MONOPOLY_DISAPPEAR		=	1;//1���Ƕ�ռ���뿪������ʧ ���ԼĴ�,���ɽ���
const int _MONOPOLY_NOT_DISAPPEAR		=	2;//2����ռ�������ԼĴ棬�뿪���岻��ʧ
const int _MONOPOLY_DISAPPEAR			=	3;//3����ռ�������ԼĴ棬�뿪������ʧ
const int _MONOPOLY_DROPCONFIRM			=   4;//4: ������ʾ-����ʱ�ͻ�������ȷ�ϴ��ڣ���ʾ���ݣ���ȷ��Ҫ����
const int _MONOPOLY_SELLCONFIRM			=   8;//8:������ʾ-���۸��̵�ʱ�ͻ�������ȷ�ϴ��ڣ���ʾ���ݣ���ȷ��Ҫ����
const int _MONOPOLY_NOTDROP				=  16;//16:�����������
const int _MONOPOLY_NOT_SELL			=  32;//32:���ɳ���

const int _MAX_EQUIPMENT				=	11;	// ����������7������λ�ô���

// requre sex define
const unsigned char _MAN_USEABLE		=	0x01;// �еĿ���
const unsigned char _WOMAN_USEABLE		=	0x02;// Ů�Ŀ���
const unsigned char _EUNUCH_USEABLE		=	0x04;// ̫�����

// Item Position define
//const int	ITEMPOSITION_BACKPACK	=	0;	// ����
const int	ITEMPOSITION_HELMET		=	1;	// ͷ��
const int	ITEMPOSITION_NECKLACE	=	2;	// ����
const int	ITEMPOSITION_ARMOR		=	3;	// ����
const int	ITEMPOSITION_WEAPONR	=	4;	// ������
const int	ITEMPOSITION_WEAPONL	=	5;	// ������
const int	ITEMPOSITION_RINGR		=	6;	// �ҽ�ָ
const int	ITEMPOSITION_TREASURE	=	7;	// ����
const int	ITEMPOSITION_SHOES		=	8;	// Ь��
const int	ITEMPOSITION_MOUNT		=	9;	// ����
const int	ITEMPOSITION_SPRITE		=	10;	// ����
const int ITEMPOSITION_MANTLE		=	11; // ����

const int ITEMPOSITION_BACKPACK			=	50; // ��ͨ��Ʒ����
const int ITEMPOSITION_GHOSTGEM_PACK	=	51; // ħ�걦ʯ����
const int ITEMPOSITION_EUDEMONEGG_PACK	=	52; // ���޵�����
const int ITEMPOSITION_EUDEMON_PACK		=	53; // ���ޱ���


const int	ITEMPOSITION_USER_LIMIT	=	199;// ������Ʒ�ֽ�
const int	ITEMPOSITION_STORAGE	=	201;// �Ĵ洦
const int	ITEMPOSITION_TRUNK		=	202;// ����
const int	ITEMPOSITION_CHEST		=	203;// �ٱ���
const int   ITEMPOSITION_AUCTION_STORAGE = 207; //����

const int	ITEMPOSITION_GROUND		=	254;// ����
const int	ITEMPOSITION_NONE		=	255;// �Ƿ�λ��

// Type Define
const int	ITEMSORT_INVALID				=	-1;
const int	ITEMSORT_EXPEND					=	0;	// �׺�Ʒ
const int	ITEMSORT_HELMET					=	1;	// ͷ��
const int	ITEMSORT_NECKLACE				=	2;	// ����
const int	ITEMSORT_ARMOR					=	3;	// ����
const int	ITEMSORT_WEAPON_SINGLE_HAND		=	4;	// ��������
const int	ITEMSORT_WEAPON_DOUBLE_HAND		=	5;	// ˫������
const int	ITEMSORT_SHIELD					=	6;	// ����
const int	ITEMSORT_RING					=	7;	// ��ָ
const int	ITEMSORT_SHOES					=	8;	// Ь��
const int	ITEMSORT_OTHER					=	9;	// ����, ����ֱ��ʹ��
const int	ITEMSORT_MOUNT					=	10;	// ����
const int	ITEMSORT_SPRITE					=	11;	// ����
const int	ITEMSORT_TREASURE				=	12; // �鱦

// money define
const int	ITEMTYPEMONEY_MIN			= 1090000;	// ��С��Ǯ
const int	ITEMTYPEMONEY_MAX			= 1091020;	// ����Ǯ

const int	SMALLHEAPMONEY_LIMIT		= 10;		// С��Ǯ
const int	SMALLHEAPMONEY_TYPE			= 1090000;	// С��ǮITEMTYPE
const int	MIDDLEHEAPMONEY_LIMIT		= 100;		// �ж�Ǯ
const int	MIDDLEHEAPMONEY_TYPE		= 1090010;	// �ж�ǮITEMTYPE
const int	BIGHEAPMONEY_LIMIT			= 1000;		// ���Ǯ
const int	BIGHEAPMONEY_TYPE			= 1090020;	// ���ǮITEMTYPE

const int	SMALLHEAPGOLD_LIMIT			= 2000;		// С�ѽ���
const int	SMALLHEAPGOLD_TYPE			= 1091000;	// С�ѽ���ITEMTYPE
const int	MIDDLEHEAPGOLD_LIMIT		= 5000;		// �жѽ���
const int	MIDDLEHEAPGOLD_TYPE			= 1091010;	// �жѽ���ITEMTYPE
const int	BIGHEAPGOLD_LIMIT			= 10000;	// ��ѽ���
const int	BIGHEAPGOLD_TYPE			= 1091020;	// ��ѽ���ITEMTYPE

//	1050000 ~ 1059999���Ǿ���/���鵰
const int	ITEMTYPE_SPRITE		=	50000;// ���顢���鵰

// Other type define
const int	OTHER_GEM					=	00000;
const int	OTHER_TASKITEM				=	10000;
const int	OTHER_ACTIONITEM			=	20000;

// Expend type define
const int	EXPEND_INVALID				=	-1;	  // �Ƿ�
const int	EXPEND_MEDICINE				=	00000;// ��ҩ
const int	EXPEND_POISON				=	10000;// ��ҩ
const int	EXPEND_DART					=	20000;// ����
const int	EXPEND_BOOK					=	30000;// ����
const int	EXPEND_NOTUSE				=	40000;// ���ţ�����
const int	EXPEND_ARROW				=	50000;// ��ʸ
const int	EXPEND_SPELL				=	60000;// ������
const int	EXPEND_NOT_DIRECTUSE		=	70000;// ������˫��ʹ�õģ���������Ʒ����ʯ��ľ�ĵ���Դ�࣬ǧλ�������ࣩ

// Necklace type define
const int	NECKLACE_NECKLACE			=	00000;// ����
const int	NECKLACE_SACHET				=	10000;// ���
const int	NECKLACE_AMULET				=	20000;// �����

// Ring type define
const int	RING_RING				=	00000;// ��ָ
const int	RING_THUMB_RING			=	10000;// ��ָ
const int	RING_BANGLE				=	20000;// ����

// Singlehand Weapon define
const int	SWEAPON_NONE				=	00000;// ����
const int	SWEAPON_BLADE				=	10000;// ��
const int	SWEAPON_AXE					=	20000;// ��
const int	SWEAPON_HAMMER				=	30000;// ��
const int	SWEAPON_HOOK				=	40000;// ��
const int	SWEAPON_CLUB				=	50000;// ��/��
const int	SWEAPON_SWORD				=	60000;// ��
const int	SWEAPON_CRUTCH				=	70000;// ��
const int	SWEAPON_SCOURGE				=	80000;// ��/�
const int	SWEAPON_SHORT				=	90000;// �̱���

// Doublehand Weapon define
const int	DWEAPON_BOW					=	00000;// ��
const int	DWEAPON_BLADE				=	10000;// ��
const int	DWEAPON_AXE					=	20000;// ��
const int	DWEAPON_HAMMER				=	30000;// ��
const int	DWEAPON_HOOK				=	40000;// ��
const int	DWEAPON_STAFF				=	50000;// ��
const int	DWEAPON_SHOVEL				=	60000;// ��
const int	DWEAPON_HALBERD				=	70000;// �
const int	DWEAPON_FORK				=	80000;// ��
const int	DWEAPON_SPEAR				=	90000;// ǹ

const int ITEMTYPE_GHOSTGEM = 30000; // ħ�걦ʯ
const int ITEMTYPE_GHOSTGEM_ACTIVE_ATK = 31000; // ״̬������
const int ITEMTYPE_GHOSTGEM_PASSIVE_ATK = 32000; // ״̬������
const int ITEMTYPE_GHOSTGEM_EUDEMON = 33000; // ������
const int ITEMTYPE_GHOSTGEM_RELEASE = 34000; // �����
const int ITEMTYPE_GHOSTGEM_TRACE = 35000; // ׷ɱ��
const int ITEMTYPE_GHOSTGEM_PROTECTIVE = 36000; // ������
const int ITEMTYPE_GHOSTGEM_SPECIAL = 37000; // ������
const int ITEMTYPE_GHOSTGEM_INVITE = 38000; //������

const int ITEMTYPE_EUDEMON = 70000; //����
const int ITEMTYPE_EUDEMONEGG = 80000;//���޵�

enum
{
    _ITEM_STATUS_NONE			=	0,	//	��
    _ITEM_STATUS_NOT_IDENT		=	1,	//	δ����
    _ITEM_STATUS_CANNOT_REPAIR	=	2,	//	�����޸�
    _ITEM_STATUS_NEVER_DAMAGE	=	4,	//	����ĥ��
    _ITEM_STATUS_MAGIC_ADD		=	8,	//	ħ��׷��

};

// ��target�ֶ�Ϊ0��ʱ�򣬲�����ʹ������
const unsigned short TARGET_NONE = 0x0000; // ���޶�����
// Ŀ������
// ��������������ϳ��֣��Կ�������Զ���Ŀ��ʹ��
const unsigned short TARGET_USER = 0x0001; // ���Զ����ʹ��
const unsigned short TARGET_MONSTER = 0x0002; // ���ԶԹ���ʹ��
const unsigned short TARGET_EUDEMON = 0x0004; // ���ԶԻ���ʹ��
// TARGET_SELF��TARGET_OTHERS�ǻ����ϵ�����Զ���ָ�������ǲ�����ͬʱ����
// ���ָ����TARGET_BODY����ֻ�ܶ�ʬ��ʹ�ã�����ֻ�ܶԻ��ŵ�Ŀ��ʹ��
const unsigned short TARGET_SELF = 0x0010; // ����ֻ�ܶ��Լ��������Լ���Ŀ��
const unsigned short TARGET_OTHERS = 0x0020; // ����ֻ�ܶԱ��˻����ڱ��˵�Ŀ��
const unsigned short TARGET_BODY = 0x0040; // ����ֻ�ܶ�ʬ��ʹ��
// �������ͼ��
const unsigned short TARGET_CHK_PKMODE = 0x0100; // ��Ҫ���pkģʽ
const unsigned short TARGET_FORBIDDEN = 0x0200; // ��ֹ���κ�Ŀ��ʹ��

const OBJID MONEYITEM_TYPE = 720000;   //������Ʒ����

//declare class here
class CItem	:	public IItem
{
public:
    CItem();
    virtual ~CItem();

    static	CItemData s_ItemData;
    static  int ItemGetSort		(OBJID idType);
    static  int ItemGetSubType	(OBJID idTyep);

protected:
    OBJID			m_idItem;
    OBJID			m_idOwner;
    ItemTypeInfo	m_infoType;
    unsigned char	m_ucPosition;
    DWORD			m_dwSellPrice;
    int				m_nMaxAttackModify;
    int				m_nMinAttackModify;
    int				m_nDefenceModify;
    int				m_nDexterityModify;
    int				m_nDodgeModify;
    int				m_nMagicAttackModify;
    int				m_nMagicDefenceModify;
    int				m_nFrameIndex;
    unsigned short	m_usPercent;
    unsigned short  m_usOriginalAmount;
    unsigned short  m_usOriginalAmountLimit;
    DWORD			m_dwWarGhostExp;	// ս�꾭�� //���޵�ǰ����
    DWORD			m_dwGemAtkType;		// ��ʯ����	//���޾���
    DWORD			m_dwAvailabeTime;	// ʹ�ô���
    DWORD			m_dwGrow;			//�ɳ���	//����Ķһ��۸�
    char			m_szMonsterName[16];	//��������
    BOOL			m_bMonsterDie;		//�����Ƿ�����
public:
    void			SetMonsterDie(BOOL bDie) {m_bMonsterDie = bDie;}
    BOOL			IsMonsterDie() {return m_bMonsterDie;}

    DWORD			GetWarGhostExp() {return m_dwWarGhostExp;}
    int				GetWarGhostLevel() {return (int)powf((float)m_dwWarGhostExp / (float)2, (float)1 / (float)3);}

    void			SetMonsterGrow(DWORD dwGrow) {m_dwGrow = dwGrow;}
    int				GetMonsterGrow() {return m_dwGrow;}

    int				GetMonsterMaxAtk();
    int				GetMonsterMinAtk();
    int				GetMonsterMagicMaxAtk();
    int				GetMonsterMagicMinAtk();
    int				GetMonsterMagicDef();
    int				GetMonsterDef();
    int				GetMonsterMaxLife();

    DWORD			IsMonsterCanEvolve(int nMode);	//�����Ƿ��ܽ���

    void			SetWarGhostExp(DWORD dwWarGhostExp) {m_dwWarGhostExp = dwWarGhostExp;}
    DWORD			GetGemAtkType() {return m_dwGemAtkType;}
    void			SetGemAtkType(DWORD dwGemAtkType) {m_dwGemAtkType = dwGemAtkType;}
    DWORD			GetAvailabeTime() {return m_dwAvailabeTime;}
    void			SetAvailabeTime(DWORD dwAvailabeTime) {m_dwAvailabeTime = dwAvailabeTime;}
    void			SetMonsterName(char* szName) {strcpy(m_szMonsterName, szName);}
    char*			GetMonsterName();

    unsigned short	GetPercent() {return m_usPercent;}
    BOOL			Create(OBJID idItem, OBJID idItemType);
    void			SetAmount(unsigned short usAmount) {m_infoType.usAmount = usAmount;}
    void			SetAmountLimit(unsigned short usAmountLimit) {m_infoType.usAmountLimit = usAmountLimit;}
    void			SetGem1(unsigned char ucGem1) {m_infoType.ucGem1 = ucGem1;}
    void			SetGem2(unsigned char ucGem2) {m_infoType.ucGem2 = ucGem2;}
    void			SetMagic1(unsigned char ucMagic1) {m_infoType.ucMagic1 = ucMagic1;}
    void			SetMagic2(unsigned char ucMagic2) {m_infoType.ucMagic2 = ucMagic2;}
    void			SetMagic3(unsigned char ucMagic3) {m_infoType.ucMagic3 = ucMagic3;}
    void			SetPosition(unsigned char ucPosition) {m_ucPosition = ucPosition;}

    void			SetStatus(unsigned char ucStatus);
    unsigned char	GetStatus();
    BOOL			TestStatus(unsigned char ucStatus);

    OBJID			GetID() {return m_idItem;}
    unsigned long	Release() {delete this; return 0;}
    int				GetSort();
    int				GetSubType();
    OBJID			GetTypeID() {return m_infoType.uID;}
    char*			GetName() {return m_infoType.szName;}
    unsigned char	GetProfessionRequired() {return m_infoType.ucRequiredProfession;}
    unsigned char	GetWeaponSkillRequired() {return m_infoType.ucRequiredWeaponSkill;}
    unsigned char	GetLevelRequired() {return m_infoType.ucRequiredLevel;}
    unsigned char	GetSexRequried() {return m_infoType.ucRequiredSex;}
    unsigned short	GetForceRequired() {return m_infoType.usRequiredForce;}
    unsigned short	GetSpeedRequired() {return m_infoType.usRequiredSpeed;}
    unsigned short	GetHealthRequired() {return m_infoType.usRequiredHealth;}
    unsigned short	GetSoulRequired() {return m_infoType.usRequiredSoul;}
    unsigned char	GetMonopoly() {return (unsigned char)m_infoType.ucMonopoly;}
    unsigned short	GetWeight();
    unsigned int	GetPrice() {return m_infoType.uPrice;}
    unsigned short	GetMaxAttack() {return m_infoType.usMaxAttack;}
    unsigned short	GetMinAttack() {return m_infoType.usMinAttack;}
    short			GetDefense() {return m_infoType.usDefense;}
    short			GetDexterity() {return m_infoType.usDexterity;}
    short			GetDodge() {return m_infoType.usDodge;}
    short			GetLife() {return m_infoType.sLife;}
    short			GetMana() {return m_infoType.sMana;}
    unsigned short	GetAmount() {return m_infoType.usAmount;}
    unsigned short	GetOriginalAmountLimit() {return m_usOriginalAmountLimit;}
    unsigned short	GetOriginalAmount() {return m_usOriginalAmount;}

    unsigned short	GetAmountLimit() {return m_infoType.usAmountLimit;}
    unsigned char	GetGem1() {return m_infoType.ucGem1;}
    unsigned char	GetGem2() {return m_infoType.ucGem2;}
    unsigned char	GetMagic1() {return m_infoType.ucMagic1;}
    unsigned char	GetLucky() {return m_infoType.ucMagic2;}
    unsigned char	GetAddition() {return m_infoType.ucMagic3;}
    unsigned char	GetPosition() {return m_ucPosition;}
    DWORD			GetSellPrice();
    DWORD			GetRepairCost();

    DWORD			GetWeaponSkillType();

    int				GetAtkRange () { return m_infoType.usRange; }
    int				GetHitarte() {return m_infoType.nHitarte;}

    unsigned short  GetTarget() {return m_infoType.usTarget;}
    BOOL			TestTarget(unsigned short usTarget) ;

    unsigned short	GetMinMagicAttack() {return m_infoType.usDexterity;}
    unsigned short	GetMaxMagicAttack() {return m_infoType.usMagicAttack;}
    unsigned short	GetSoul() {return m_infoType.usDodge;}
    unsigned short	GetMagicDefence();
    unsigned short  GetAttackSpeed() {return m_infoType.usAttackSpeed;}


    //����Ʒ�ʱ�ʯtype��1037160
    //����ħ��ȼ���ʯtype��1037150
    enum {TREASURE_DRAGONBALL = 1037160, TREASURE_SHOOTINGSTAR = 1037170, TREASURE_SOULSTONE = 1037150};

    BOOL	IsDragonBall(void)		{ return (TREASURE_DRAGONBALL == GetTypeID()); }
    BOOL	IsShootingStar(void)	{ return (TREASURE_SHOOTINGSTAR == GetTypeID()); }
    BOOL	IsSoulStone(void)		{return (TREASURE_SOULSTONE == GetTypeID()); }


    //������ޱ�ʯtype: 1033020
    //ǿ�����ޱ�ʯtype: 1033030
    enum {SOULSTONE_ALIVE = 1033020, SOULSTONE_IMPROVE = 1033030};
    BOOL	IsAliveSoulStone(void)   {return (SOULSTONE_ALIVE == GetTypeID()); }
    BOOL	IsImproveSoulStone(void) {return (SOULSTONE_IMPROVE == GetTypeID()); }

    char*	GetDesc();

    BOOL	IsActionItem(void)	{ return ITEMSORT_OTHER == GetSort() && OTHER_ACTIONITEM == GetSubType(); }
    BOOL	IsTaskItem	(void)	{ return ITEMSORT_OTHER == GetSort() && OTHER_TASKITEM == GetSubType(); }
    BOOL	IsMonopolyItem(void) {return this->GetMonopoly() == _MONOPOLY_NOT_DISAPPEAR || this->GetMonopoly() == _MONOPOLY_DISAPPEAR; }
    BOOL	TestMonopolyItem(unsigned char ucMonopoly);
    BOOL	IsGem		(void)	{ return ITEMSORT_OTHER == GetSort() && OTHER_GEM == GetSubType(); }
    BOOL	IsArrow		(void)	{ return ITEMSORT_EXPEND == GetSort() && EXPEND_ARROW == GetSubType(); }
    BOOL	IsBow		(void)	{ return ITEMSORT_WEAPON_DOUBLE_HAND == GetSort() && DWEAPON_BOW == GetSubType(); }

    BOOL    IsMoneyItem() { return GetTypeID () == MONEYITEM_TYPE;}	//�ǲ��ǳ���
    DWORD   GetMoneyItemPrice() {return m_dwGrow;}

    void	SetBoothSellPrice(DWORD dwPrice);
    DWORD	GetBoothSellPrice();
    void	SetOwnerID(OBJID idOwner);
    OBJID	GetOwnerID();

    int		GetMaxAttackModify();
    int		GetMinAttackModify();
    int		GetDefenceModify();
    int		GetDexterityModify();
    int		GetDodgeModify();
    int		GetMagicAttackModify();
    int		GetMagicDefenceModify();
    void	ShowMiniItem(int nX, int nY , BOOL bScale = true);
    static	BOOL	IsNonsuchItem(OBJID idItemType);
    int		GetQuality(void);
    BOOL	WantCombin();

    int		GetPackageType();
};

#include <deque>
using namespace std;
typedef deque<CItem*>DEQUE_ITEM;

//end class declaration
#endif
