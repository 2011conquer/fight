
//**********************************************************
// ����༭��
//**********************************************************

// Shop.h: interface for the CShop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOP_H__88CEAC05_7669_4BC3_A2ED_34645D2E75B5__INCLUDED_)
#define AFX_SHOP_H__88CEAC05_7669_4BC3_A2ED_34645D2E75B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Item.h"
#include "ShopData.h"

//Shop Type Define
const int _SHOP_NONE		=	0;	// �����̵�����
const int _WEAPON_SHOP		=	1;	// �����̵�
const int _DEFENCE_SHOP		=	2;	// �����̵�
const int _FORGE_SHOP		=	3;	// �����̵�
const int _MEDICINE_SHOP	=	4;	// ҩƷ�̵�
const int _BANK_SHOP		=	5;	// �����̵�
const int _SMALLWARES_SHOP	=	6;	// �ӻ��̵�
const int _ORE_SHOP			=	7;	// ��ʯ�̵�
const int _JEWELRY_SHOP		=	8;	// �����̵�


class CShop
{
private:
    static CShopData s_ShopData;
public:
    CShop();
    virtual ~CShop();

    DWORD	GetItemAmount	();
    CItem*	GetItem			(DWORD dwIndex);
    BOOL	Open			(OBJID idNpc);
    void	Close			();
    void	ClearItem		();
    char*	GetShopName		();
    OBJID	GetShopID();
    int		GetShopType();
private:
    OBJID	m_idNpc;
    char	m_szName[_MAX_NAMESIZE];
    BOOL	m_bActive;
    int		m_nShopType;
    DEQUE_ITEM m_dequeItem;
};

extern CShop	g_objShop;

#endif // !defined(AFX_SHOP_H__88CEAC05_7669_4BC3_A2ED_34645D2E75B5__INCLUDED_)
