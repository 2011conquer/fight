
//**********************************************************
// ����༭��
//**********************************************************

// SchoolMember.h: interface for the CSchoolMember class.
//
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------
// File Name: SchoolMember.h
// Create by: Xue liang
// Create on: 2004/10/10 9:10
//--------------------------------------------------------------------------------------

#if !defined(AFX_SCHOOLMEMBER_H__EFDFD5FF_944B_4BF9_A820_77640CD8959A__INCLUDED_)
#define AFX_SCHOOLMEMBER_H__EFDFD5FF_944B_4BF9_A820_77640CD8959A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BaseFunc.h"

enum
{
    MEMBERSTATUS_OFFLINE = 0, // ����״̬
    MEMBERSTATUS_ONLINE, // ����״̬
};

class CSchoolMember
{
public:
    CSchoolMember();
    virtual ~CSchoolMember();

private:
    OBJID	m_idMember; // ��ԱID
    UCHAR	m_ucStatus; // ״̬ ���� �����ߡ�����
    UCHAR	m_ucRelation; // ����ҹ�ϵ
    char	m_szName[_MAX_NAMESIZE]; // ��Ա����
    char	m_szMate[_MAX_NAMESIZE]; // ��ż����
    UCHAR	m_ucLevel; // �ȼ�
    UCHAR	m_ucProfession; // ְҵ���
    USHORT	m_usPkValue; // PKֵ
    UCHAR	m_ucNobilityRank; // ��ݣ���λ��
    DWORD	m_dwSynID_Rank; // ����ID & ְλ (��MsgPlayerһ������8λΪְλ��ţ���24λΪ����ID)

    //for the operate interface(s)
public:
    static CSchoolMember* CreateNew(OBJID id, UCHAR ucStatus, char* pszName, UCHAR ucRelation, char* pszMate, UCHAR ucLevel, UCHAR ucProfession, USHORT usPkValue, UCHAR ucNobilityRank, DWORD dwSynID_Rank);
    //get
    OBJID GetID() {return m_idMember;}
    UCHAR GetStatus() { return m_ucStatus;}
    char* GetName() {return m_szName;}
    UCHAR GetRelation() {return m_ucRelation;}
    char* GetMate() {return m_szMate;}
    UCHAR GetLevel() {return m_ucLevel;}
    USHORT GetPk() {return m_usPkValue;}
    char* GetProfession() ;
    char* GetNobilityRank();
    char* GetSynName();
    char* GetSynRank();
    //set
    void SetID(OBJID idMember) {m_idMember = idMember;}
    void SetStatus(UCHAR ucStatus) {m_ucStatus = ucStatus;}
    void SetName(char* pszName) {assert(pszName); strcpy(m_szName, pszName);}
    void SetRelation(UCHAR ucRelation) {m_ucRelation = ucRelation;}
    void SetMate(char* pszMate) {assert(pszMate); strcpy(m_szMate, pszMate);}
    void SetLevel(UCHAR ucLevel) {m_ucLevel = ucLevel;}
    void SetProfession(UCHAR ucProfession) {m_ucProfession = ucProfession;}
    void SetPk(USHORT usPkValue) {m_usPkValue = usPkValue;}
    void SetNobilityRank(UCHAR ucNobilityRank) {m_ucNobilityRank = ucNobilityRank;}
    void SetSynRank(DWORD dwSynID_Rank) {m_dwSynID_Rank = dwSynID_Rank;}
};
#include <deque>
using namespace std;
class CPlayer;
typedef deque<CSchoolMember* >  DEQUE_SCHOOLMEMBER;
#endif // !defined(AFX_SCHOOLMEMBER_H__EFDFD5FF_944B_4BF9_A820_77640CD8959A__INCLUDED_)
