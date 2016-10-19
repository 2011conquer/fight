
//**********************************************************
// ����༭��
//**********************************************************

// ShopData.h: interface for the CShopData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOPDATA_H__45ED140A_2659_4F82_BA24_D28F6495A364__INCLUDED_)
#define AFX_SHOPDATA_H__45ED140A_2659_4F82_BA24_D28F6495A364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BaseFunc.h"
// �߻���Ϊ�̵겻�ᳬ��36��������һ�μ���
const int _MAX_ITEMTYPE_AMOUNT_OF_SHOP = 256;
typedef struct
{
    OBJID	idShop;
    int		nType;
    char	szName[_MAX_NAMESIZE];
    DWORD	dwItemAmount;
    OBJID*	pidItem;
} ShopDataInfo;

#include <deque>
using namespace std;
typedef deque<ShopDataInfo* >  DEQUE_SHOPDATA;

#include "Item.h"
class CShopData
{
public:
    CShopData();
    virtual ~CShopData();

private:
    DEQUE_SHOPDATA m_setShopData;
private:
    void Create();
    void Destroy();
public:
    BOOL GetItemList(OBJID idShop, DEQUE_ITEM& setItem, char* pszName, int& nType);
};

#endif // !defined(AFX_SHOPDATA_H__45ED140A_2659_4F82_BA24_D28F6495A364__INCLUDED_)
