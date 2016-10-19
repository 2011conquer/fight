
//**********************************************************\\
// ����༭��\\
//**********************************************************\\
\\
// ChatRoom.h: interface for the CChatRoom class.
//
//////////////////////////////////////////////////////////////////////

//Create By:	Wen Yiku
//Create Date:	2005-6-29
#if !defined(AFX_CHATROOM_H__E61FC286_64C3_404C_8322_7C335C42406A__INCLUDED_)
#define AFX_CHATROOM_H__E61FC286_64C3_404C_8322_7C335C42406A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "basefunc.h"

#include "IMSdk.h"

#include <deque>

using namespace std;

typedef deque<CGroupSummary* >  DEQUE_GROUPLIST;

typedef struct
{
    DWORD dwUin;
    DWORD dwStatus;
    DWORD dwEntryTime;
    char  szNick[16];
    char  szDomain[16];
    char  szIdiograph[256];
} GroupMember;
typedef deque<GroupMember* >  DEQUE_GROUPMEMBER;

class CChatRoom
{
public:
    void DeInit();
    void Init();
    void Logout();
    void Login();
    void SendMsg(UINT dwFriendID = 0);
    //	UINT GetMyUin(){ return im_GetMyUin();}
    void ChangeRoomInfo();
    void ChangeMyInfo();
    void AbandonManger();
    void ApplyManager();
    void KickMember();
    void GetRoomInfo();
    void GetRoomList();
    void EnterRoom(int nIndex);		//
    void EnterRoomByID(UINT GroupID);	//����xx������
    void LeaveRoom();	//�˳���ǰ������
    CChatRoom();
    virtual ~CChatRoom();

    //
    void Reset();
    //�������б�
    void SetRoomListInfo(CGroupSummary* pGroupSummary, int iCount);
    CGroupSummary* GetRoomInfoList(int nIndex);
    CGroupSummary* GetRoomInfoListByID(UINT GroupID);
    int	 GetRoomInfoAmount() {return m_setGroupList.size();}

    //��ǰ��������Ϣ
    void SetCurRoomInfo(IGroupInfo* pGroup) {m_curGroup = pGroup;}
    IGroupInfo* GetCurRoomInfo() {return m_curGroup;}
    //��ǰ�����ҳ�Ա�б�
    BOOL AddRoomMember(IGroupInfo* pGroupInfo, IGroupMember* pGroupMember);
    BOOL DelRoomMember(IGroupInfo* pGroupInfo, IGroupMember* pGroupMember);
    BOOL UpdateRoomMember(IGroupMember* pGroupMember);
    int  GetRoomMemberAmount() {return m_setGroupMember.size();}
    GroupMember* GetRoomMemberByIndex(int nIndex);
    GroupMember* GetRoomMemberByUin(int nUin);

    void ClearRoomMembers() ;

private:
    void ClearRoomListInfo();
private:
    DEQUE_GROUPLIST m_setGroupList;				//�������б�
    DEQUE_GROUPMEMBER m_setGroupMember;			//��ǰ�����ҳ�Ա�б�
    IGroupInfo* m_curGroup;						//��ǰ������
    char m_strMsg[256];
    UINT m_dwUin;
    char m_strGroupDomain[64];
    char m_strValue[64];
    UINT m_dwAttrib;
    char m_strGameCode[64];
    char m_strPasswd[32];
    char m_strAccount[32];
    UINT m_dwMyUin;
public:
    UINT m_dwGroupID;

public:
    void SetMsg(char* strMsg) {strcpy(m_strMsg, strMsg);}

};


#ifndef WM_91U_MESSAGE
#define WM_91U_MESSAGE (WM_USER+1000)

const int CMD_91U_LOGIN									= 1000;					//��½�ɹ�
const int CMD_91U_EXIST_UIN								= CMD_91U_LOGIN + 1;	//Uin�ڱ𴦵�¼�ˣ�
const int CMD_91U_LOGINFAILED							= CMD_91U_LOGIN + 2;	//��¼ʧ��
const int CMD_91U_STATUSCHANGED							= CMD_91U_LOGIN + 3; 	//����״̬�ı���
const int CMD_91U_OFFLINEERROR							= CMD_91U_LOGIN + 4;	//������������
const int CMD_91U_OFFLINE								= CMD_91U_LOGIN + 5;	//����������

const int CMD_91U_SEARCHROOMBACK						= CMD_91U_LOGIN + 6;	//��ѯ�������б���

const int CMD_91U_ENTERROOMOK							= CMD_91U_LOGIN + 7;	//����������
const int CMD_91U_ROOMOUTAMOUNT							= CMD_91U_LOGIN + 8;	//����Ⱥ���������Ա����
const int CMD_91U_HASENTERED							= CMD_91U_LOGIN + 9;	//�ó�Ա�Ѿ���Ⱥ���б�֮��
const int CMD_91U_NOTALLOW								= CMD_91U_LOGIN + 10;	//���������Ⱥ����Ա��Ⱥ��
const int CMD_91U_ENTEROUTTIME							= CMD_91U_LOGIN + 11;	//���糬ʱ
const int CMD_91U_ENTERFAILED							= CMD_91U_LOGIN + 12;	//����Ⱥʧ��
const int CMD_91U_KICKOUT								= CMD_91U_LOGIN + 15;    //���߳�������

const int CMD_91U_GETROOMINFOBACK						= CMD_91U_LOGIN + 13;	//�ӷ����ȡȺ��Ϣ
const int CMD_91U_MODIFYROOMNAME						= CMD_91U_LOGIN + 14;	//�޸�Ⱥ��Ϣ -����
const int CMD_91U_MODIFYROOMBULLETIN					= CMD_91U_LOGIN + 15;	//�޸�Ⱥ��Ϣ -�Ĺ���
const int CMD_91U_MODIFYROOMSYNOPSIS					= CMD_91U_LOGIN + 16;	//�޸�Ⱥ��Ϣ -Ⱥ���


const int CMD_91U_MEMBERIN								= CMD_91U_LOGIN + 16;	//��Ա����������
const int CMD_91U_MEMBEROUT								= CMD_91U_LOGIN + 18;	//��Ա�˳�������
const int CMD_91U_MEMBERKICKOUT							= CMD_91U_LOGIN + 19;	//��Ա���߳�������
const int CMD_91U_MEMBEROFFLINE							= CMD_91U_LOGIN + 20;   //��Ա����
const int CMD_91U_MEMBERONLINE							= CMD_91U_LOGIN + 21;   //��Ա����
const int CMD_91U_MODIFYMEMBERNAME						= CMD_91U_LOGIN + 20;	//�޸�Ⱥ��Աname
const int CMD_91U_MODIFYMEMBERIDIOGRAPH					= CMD_91U_LOGIN + 21;	//�޸�Ⱥ��Աǩ��

const int CMD_91U_CHANGEGROUPMANAGER					= CMD_91U_LOGIN + 21;   //�ı�Ⱥ����Ա
const int CMD_91U_ABANDONGROUPMANAGER					= CMD_91U_LOGIN + 22;	//����Ⱥ����Ա


void Post91UCmd(DWORD dwCommand, int nData = 0);
#endif
extern CChatRoom g_obj91Sdk;
#endif // !defined(AFX_CHATROOM_H__E61FC286_64C3_404C_8322_7C335C42406A__INCLUDED_)
