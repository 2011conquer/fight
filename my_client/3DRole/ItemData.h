
//**********************************************************
// ����༭��
//**********************************************************

// ItemData.h: interface for the CItemData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDATA_H__B6A8F74E_31AA_46B4_BF3C_03AF450B1E90__INCLUDED_)
#define AFX_ITEMDATA_H__B6A8F74E_31AA_46B4_BF3C_03AF450B1E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
enum // ������������ö��
{
    _SPRITE_ADDITION_PATK	= 0,	//	��Ԫ�ؾ���--������������
    _SPRITE_ADDITION_PDEF	= 1,	//  ��Ԫ�ؾ���--�������������
    _SPRITE_ADDITION_MATK	= 2,	//  ��Ԫ�ؾ���--����ħ��������
    _SPRITE_ADDITION_MDEF	= 3,	//  ˮԪ�ؾ���--����ħ��������
    _SPRITE_ADDITION_SOUL	= 4,	//  ��Ԫ�ؾ���--���Ӿ���
};
typedef struct
{
    unsigned int	uID;					//0 item type �� ID		//  �����lookface����itemtype ����
    char			szName[_MAX_NAMESIZE];	//1 ��Ʒ����
    unsigned char	ucRequiredProfession;	//2 Ҫ��ְҵ			������������
    unsigned char	ucRequiredWeaponSkill;	//3 Ҫ�����������
    unsigned char	ucRequiredLevel;		//4 Ҫ��ĵȼ�			// ����ȼ� װ���������ҵĵȼ����벻�����ھ���ĵȼ���2��
    unsigned char	ucRequiredSex;			//5 Ҫ����Ա�
    unsigned short	usRequiredForce;		//6 Ҫ������
    unsigned short	usRequiredSpeed;		//7 Ҫ���ٶ�
    unsigned short	usRequiredHealth; 		//8 Ҫ�󽡿�
    unsigned short	usRequiredSoul; 		//9 Ҫ����
    unsigned char	ucMonopoly;				//10 ��ռ��Ʒ��־
    unsigned short	usWeight;				//11 ��Ʒ����
    unsigned int	uPrice;					//12 �۸�
    int				uLuck;					//13 ����ֵ				//	��������һ����Ҫ�ľ���ֵ
    unsigned short	usMaxAttack;			//14 ��󹥻�
    unsigned short	usMinAttack;			//15 ��С����
    short			usDefense;				//16 ����
    short			usDexterity;			//17 ����				// ��Сħ����
    short			usDodge;				//18 ����				// add soul
    short			sLife;					//19 ����
    short			sMana;					//20 ħ����
    unsigned short	usAmount;				//21 ����				//	�������ܶ�=�ҳ�
    unsigned short	usAmountLimit;			//22 ����				//  ���鸽������ // ��ʾʱӦ�� /100
    unsigned char	ucStatus;				//23 ״̬
    unsigned char	ucGem1;					//24 ��Ƕ��ʯ1
    unsigned char	ucGem2;					//25 ��Ƕ��ʯ2
    unsigned char	ucMagic1;				//26 ����ħ��1
    unsigned char	ucMagic2;				//27 ����
    unsigned char	ucMagic3;				//28 ׷��
    unsigned short	usMagicAttack;			//29 ħ��				// ���ħ��
    unsigned short	usMagicDefence;			//30 ħ��
    unsigned short  usRange;				//31 ������Χ
    unsigned short  usAttackSpeed;			//32 �����ٶ�
    int		     	nHitarte;				//33 ����
    unsigned short  usTarget;				//34 ʹ�ö���
    char			szDesc[128];			//35 ����
} ItemTypeInfo;

typedef struct
{
    int nLife;
    int nAttackMax;
    int nAttackMin;
    int nDefense;
    int nMAttackMax;
    int nMAttackMin;
    int nMDef;
    int nDexterity;
    int nDodge;
} ItemAdditionInfo;

typedef map<OBJID, ItemTypeInfo> MAP_ITEMINFO;
typedef map<__int64, ItemAdditionInfo> MAP_ITEMADDITIONINFO;

class CItemData
{
public:
    CItemData();
    virtual ~CItemData();


  
	void LoadAllItemInfo();
	void ExportItemData(); //�����������ݿ�
private:
    BOOL	CreateIndexTable();
    void	CreateAdditionalInfo();
	DWORD m_dwRecordAmount;
public:
    BOOL	GetItemTypeInfo(OBJID idType, ItemTypeInfo& infoItemType);
    BOOL	GetItemAdditionInfo(OBJID idType, int nLevel, ItemAdditionInfo& infoAdditional);
    BOOL	CheckItem(const char* pszItemName);
    static MAP_ITEMINFO s_mapItemType;
    MAP_ITEMADDITIONINFO m_mapItemAdditional;
    std::vector<string> m_setItemName;
};

#endif // !defined(AFX_ITEMDATA_H__B6A8F74E_31AA_46B4_BF3C_03AF450B1E90__INCLUDED_)
