
//**********************************************************
// ����༭��
//**********************************************************

// MagicData.h: interface for the CMagicData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGICDATA_H__B1F17B6C_5DC6_4DC8_ACBC_598255551440__INCLUDED_)
#define AFX_MAGICDATA_H__B1F17B6C_5DC6_4DC8_ACBC_598255551440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

enum
{
    MAGIC_SORT_ATTACK_SINGLE_HP			= 1,	// �������ˣ��Է�ȥѪ
    MAGIC_SORT_RECOVER_SINGLE_HP		= 2,	// �ظ����ˣ��Է���Ѫ
    MAGIC_SORT_ATTACK_CROSS_HP			= 3,	// ʮ��������Ŀ��ȥѪ
    MAGIC_SORT_ATTACK_SECTOR_HP			= 4,	// ��������Ŀ��ȥѪ
    MAGIC_SORT_ATTACK_ROUND_HP			= 5,	// Բ������Ŀ��ȥѪ
    MAGIC_SORT_ATTACK_SINGLE_STATUS		= 6,	// �������ˣ��Է���״̬
    MAGIC_SORT_RECOVER_SINGLE_STATUS	= 7,	// �ظ����ˣ��Է�ȥ״̬
    MAGICSORT_SQUARE					= 8,	// ���ι���
    MAGICSORT_JUMPATTACK				= 9,	// ����
    MAGICSORT_RANDOMTRANS				= 10,	// �������
    MAGICSORT_DISPATCHXP				= 11,	// ŭ��
    MAGICSORT_COLLIDE					= 12,	// ���
    MAGICSORT_SERIALCUT					= 13,	// ����
    MAGICSORT_LINE						= 14,	// ����ħ��
    MAGICSORT_ATKRANGE					= 15,	// ���ӹ�����Χ
    MAGICSORT_ATKSTATUS					= 16,	// ~!@#$%^&*()_+
    MAGICSORT_CALL_TEAMMEMBER			= 17,	// �ٻ���Ա
    MAGICSORT_RECORDTRANSSPELL			= 18,	// record map position to trans spell.
    MAGICSORT_TRANSFORM					= 19,	// ����
    MAGICSORT_ADDMANA					= 20,	// ��Mana// support self target only.
    MAGICSORT_LAYTRAP					= 21,
    MAGICSORT_DANCE						= 22,	// ����
    MAGICSORT_CALLPET			= 23,			// �ٻ���
    MAGICSORT_VAMPIRE			= 24,			// ��Ѫ��power is percent award. use for call pet
    MAGICSORT_INSTEAD			= 25,			// ����. use for call pet
    MAGICSORT_DECLIFE			= 26,			// ��Ѫ(��ǰѪ�ı���)
    MAGICSORT_GROUNDSTING		= 27,			// �ش�
    MAGICSORT_REBORN			= 28,			// ���� -- zlong 2004.5.14
    MAGICSORT_TEAM_MAGIC		= 29,			// ���ħ������ ��MAGICSORT_ATTACHSTATUS��ͬ����
    //				�����������ֻ��Ϊ�˷���ͻ���ʶ��
    MAGICSORT_BOMB_LOCKALL		= 30,			// ��MAGICSORT_BOMB������ͬ��ֻ������ȫ��Ŀ��
    MAGICSORT_SORB_SOUL			= 31,			// ����ħ��
    MAGICSORT_STEAL				= 32,			// ͵���������Ŀ������͵ȡpower����Ʒ
    MAGICSORT_LINE_PENETRABLE	= 33,			// �����߹켣���Դ��˵����Թ���

    //////////////////////////////////////////////
    // ��������ħ������
    MAGICSORT_BLAST_THUNDER			= 34,			// ħ��
    MAGICSORT_MULTI_ATTACHSTATUS	= 35,			// Ⱥ��ʩ��״̬
    MAGICSORT_MULTI_DETACHSTATUS	= 36,			// Ⱥ����״̬
    MAGICSORT_MULTI_CURE			= 37,			// Ⱥ�岹Ѫ
    MAGICSORT_STEAL_MONEY			= 38,			// ͵Ǯ
    MAGICSORT_KO					= 39,			// ��ɱ����Ŀ��ѪС��15%�Զ�����
    MAGICSORT_ESCAPE				= 40,			// ����/����
    //		MAGICSORT_FLASH_ATTACK			= 41,			// ���λ�λ
    MAGICSORT_ATTRACK_MONSTER		= 42,			// ��������
};

enum
{
    MAGIC_SHAKENORMAL		  = 0x00000001, // ��Ч��
    MAGIC_COLORNORMAL		  = 0x00000002, // �䰵Ч��
    MAGIC_SCALENORMAL		  = 0x00000004, // ����Ч��
};

enum
{
    MAGIC_TARGET_SELF		  = 0x00000001,	// ���Զ��Լ�ʹ��
    MAGIC_TARGET_NONE		  = 0x00000002, // ����Ҫ��Ŀ��
    MAGIC_TARGET_TERRAIN      = 0x00000004, // �Ե�ʹ��
    MAGIC_PASSIVE			  = 0x00000008, // ����ħ��������ʹ��
    MAGIC_TARGET_BODY		  = 0x00000010, // ֻ�ܶ�δ��ʧ��ʬ��ʹ�� //������Ч
};

enum
{
    TYPE_MAGIC		= 0, // ħ��
    TYPE_XPSKILL	= 1, // xp��
    TYPE_KONGFU		= 2, // �书��ʽ
};
#include <vector>
using namespace std;

typedef struct
{
    OBJID	idMagicType;			// ����ID
    DWORD	dwActionSort;			// ��Ϊ����
    char	szName[_MAX_NAMESIZE];	// ħ������
    DWORD	dwCrime;				// �Ƿ���������
    DWORD	dwGround;				// �Ƿ��Чħ��
    DWORD	dwMulti;				// �Ƿ�����
    DWORD	dwTarget;				// ��������
    DWORD	dwLevel;				// ħ���ȼ�
    DWORD	dwMpCost;				// ����MP
    DWORD	dwPotential;			// ����Ǳ��
    DWORD	dwPower;				// ����
    DWORD	dwIntoneDuration;		// ����ʱ��
    DWORD	dwHitPoint;				// ���б���
    DWORD	dwDuration;				// ����ʱ�� // ����
    DWORD	dwRange;				// �˺���Χ // X= %100 , y=%10000-x*100
    DWORD	dwDistance;				// ��Ч����
    DWORD	dwStatus;				// ����״̬
    DWORD	dwProfessionalRequired;	// Ҫ��ְҵ
    DWORD	dwExpRequired;			// Ҫ����ֵ // ���� // 0��������
    DWORD	dwMonsterLevelRequired;	// Ҫ��������ȼ� // ����

    DWORD	dwXp;					// �Ƿ�ʹ��XP
    DWORD	dwWeaponSubType;		// ��Ҫ����������

    DWORD	dwActiveTime;			// ����ʱ��
    DWORD	dwAutoActive;			// �Զ�����
    DWORD	dwFloorAttribute;		// �ذ�����
    DWORD	dwAutoLearn;			// �Զ�ѧ��
    DWORD	dwLearnLevel;			// ѧϰ��Ҫ�ȼ�
    DWORD	dwDropWeapon;			// ������
    DWORD	dwUsePP;				// ʹ������ֵ
    DWORD	dwWeaponHit;			// �Ƿ���������
    OBJID	idUseItem;				// ������Ʒ
    OBJID	idNextMagic;			// ��һħ��
    DWORD	dwMagicBreak;			// ħ�����

    DWORD	dwClientRepresent;		// �ͻ��˱���
    DWORD	dwSenderAction;			// ʩ�ŷ����ߵĶ���
    DWORD   dwNeedLevel;			// �¼�ħ����Ҫ����ҵȼ� �Ƿ����¸�ħ���ȼ� 0: û����һ�ȼ�
    char	szDisc[64];				// ����
    char	szIntoneEffect[64];			// ������Ч
    char	szIntoneSound[_MAX_PATH];	// ������Ч
    char	szSenderEffect[64];			// ������Ч
    char	szSenderSound[_MAX_PATH];	// ������Ч
    DWORD	dwTargetDelay;				// �ܻ���ʱ
    char	szTargetEffect[64];			// �ܻ���Ч
    char	szTargetSound[_MAX_PATH];	// �ܻ���Ч
    char	szGroundEffect[64];			// ��Ч����
    char	szTraceEffect[64];			// �켣��Ч
    DWORD	dwScreenRepresent;			// ��Ļ����
    DWORD	dwCanBeusedInMarket;		// �Ƿ��ܹ����г�ʹ��// 0�������ã� 1������
    DWORD	dwTargetWoundDelay;			// �ܻ������˶�����ʱ
    DWORD	dwDelay;					// ��ʼħ�����ֵ�ħ���ӳٽ�����ʱ��
    BOOL    bTrack;						// �Ƿ�����
    vector<int> setAction;
} MagicTypeInfo;


typedef vector<MagicTypeInfo* >VECTOR_MAGICTYPE;

class CMagicData
{
public:
    CMagicData();
    virtual ~CMagicData();
private:
    VECTOR_MAGICTYPE m_setMagicType;
private:
    void Create();
    void CreateAction();
    void Destroy();
public:
    BOOL GetMagicTypeInfo(OBJID dwIDType, DWORD dwLevel, MagicTypeInfo& infoMagic);
};

#endif // !defined(AFX_MAGICDATA_H__B1F17B6C_5DC6_4DC8_ACBC_598255551440__INCLUDED_)
