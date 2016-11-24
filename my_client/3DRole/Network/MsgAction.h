
//**********************************************************
// ����༭��
//**********************************************************

// MsgAction.h: interface for the CMsgAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
#define AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"

enum
{
    actionNone				= 0,
    actionChgDir			= 1,
    actionPosition			= 2,
    actionEmotion			= 3,
    actionBroadcastPos		= 4,
    actionDivorce			= 5,
    actionSelfUnfreeze		= 6,
    actionChgMap			= 7,
    actionFlyMap			= 8,
    actionChgWeather		= 9,
    actionFireworks			= 10,
    actionDie				= 11,
    actionQuitSyn			= 12,
    actionWalk				= 13,
    actionEnterMap			= 14,
    actionGetItemSet		= 15,
    actionGetGoodFriend		= 16,
    actionForward			= 17,
    actionLeaveMap			= 18,		// ������->�ͻ���,idPlayer
    actionJump				= 19,
    actionRun				= 20,
    actionEquip				= 21,
    actionUnequip			= 22,
    actionUplev				= 23,
    actionXpCLear			= 24,
    actionReborn			= 25,
    actionDelRole			= 26,
    actionGetWeaponSkillSet	= 27,
    actionGetMagicSet		= 28,
    actionSetPkMode			= 29,
    actionGetSynAttr		= 30,
    actionGhost				= 31,
    actionSynchro			= 32,
    actionQueryFriendInfo	= 33,
    actionQueryLeaveWord	= 34,
    actionChangeFace		= 35,
    actionMine				= 36,
    actionTeamMemeberPos	= 37,
    actionQueryPlayer		= 38,
    actionAbortMagic		= 39,
    actionMapARGB			= 40,
    actionMapStatus			= 41,		// abandon
    actionQueryTeamMember	= 42,
    actionCreateBooth		= 43,		// ��ʼ��̯ server/client; idUser: playerID; unPosX,unPosY: playerpos; unDir:dirofbooth; idTarget:idnpc;
    actionSuspendBooth		= 44,		// �����̯
    actionResumeBooth		= 45,		// ������̯ server/client; idUser: playerID; unPosX,unPosY: playerpos; unDir:dirofbooth; idTarget:idnpc;
    actionDestroyBooth		= 46,		// ֹͣ��̯
    actionQueryCryOut		= 47,		// ��ѯ��̯ߺ��
    actionPostCmd			= 48,		// to client only
    actionQueryEquipment	= 49,		// to server //idUserΪ��Ҫquery��PlayerID
    actionAbortTransform	= 50,		// to server
    actionCombineSubSyn		= 51,		// to client, idUser-> idSubSyn, idTarget-> idTargetSyn
    actionLanding			= 52,		// to server only
    actionGetMoney			= 53,		// to client only // ��500�Լ�500����Ǯ��ֻ�����Լ���dwDataΪ�񵽵�Ǯ
    actionDischarge			= 54,		// to server
    actionQueryEnemyInfo	= 55,		// to server
    actionMoveStop			= 56,		// data=milli secs.
    actionKickBack			= 57,		// to client	idUser is Player ID, unPosX unPosY is Player pos
    actionDropMagic			= 58,		// to client only, data is magic type
    actionDropSkill			= 59,		// to client only, data is weapon skill type
    actionSoundEffect		= 60,		// to client only, client play sound effect, dwData is monster type

    actionQueryMedal		= 61,		// to server	idUser is Player ID, dwData is medal
    actionDelMedal			= 62,		// to server	idUser is Player ID, dwData is medal
    actionAddMedal			= 63,		// to client	idUser is Player ID, dwData is medal
    actionSelectMedal		= 64,		// to server	idUser is Player ID, dwData is medal

    actionQueryHonorTitle	= 65,		// to server	idUser is Player ID, dwData is title
    actionDelHonorTitle		= 66,		// to server	idUser is Player ID, dwData is title
    actionAddHonorTitle		= 67,		// to client	idUser is Player ID, dwData is title
    actionSelectHonorTitle	= 68,		// to server	idUser is Player ID, dwData is title
    actionOpenDialog		= 69,		// to client only, open a dialog, dwData is id of dialog
    actionFlashStatus		= 70,		// broadcast to client only, team member only. dwData is dwStatus

    actionQuerySynInfo		= 71,		// ��ѯ������Ϣ		// to server synicate id
    actionStudentApply		= 72,		// ʦ����������ͽ��	// to server/client idUserΪʦ��ID dwDataΪͽ��ID
    actionTeacherApply		= 73,		// ͽ�������ʦ		// to server/client idUserΪͽ��ID dwDataΪʦ��ID

    actionAgreeStudentApply	= 74,		// ͬ���ʦ			// to server idUserΪʦ��ID dwDataΪͽ��ID
    actionAgreeTeacherApply	= 75,		// ͬ������ѧ��		// to server idUserΪͽ��ID dwDataΪʦ��ID
    actionDismissStudent    = 76,		// ����ѧ��         // to server idUserΪʦ��ID dwDataΪͽ��ID
    actionLeaveTeacher		= 77,		// ����ʦ��			// to server idUserΪͽ��ID dwDataΪʦ��ID
    actionQuerySchoolMember	= 78,		// ��ѯʦͽ�б�		//to server //
    actionTeacherRequest	= 79,		// �����ֹ����з���ʦ����	// to server


    actionQueryPlayerTaskAcceptedList		= 80,		// ��ѯ������͵��ѽ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
    actionQueryPlayerTaskUnacceptedList		= 81,		// ��ѯ������͵�δ�������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
    actionQueryPlayerTaskCompletedList		= 82,		// ��ѯ������͵�����������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
    actionQueryPlayerMyTaskList				= 83,		// ��ѯ������͵��ҵ������б� // to server // dwDataΪ��һ�β�ѯ�����һ��ID
    actionQueryPlayerTaskDetail				= 84,		// ��ѯ�������������ϸ���� // to server // dwDataΪ��ѯ����ID

    actionAcceptPlayerTask					= 88,		// �������� // to server // dwDataΪ����ID
    actionCompletePlayerTask				= 89,		 // ������� // to server // dwDataΪ����ID
    actionCancelPlayerTask					= 90,		// �������� // to server // dwDataΪ����ID

    actionLockUser							= 91,		// �����ͻ��˲�ͬ�����귽��
    actionUnLockUser						= 92,		// �����ͻ��˲�ͬ�����귽��
    actionMagicTrack						= 93,		// ͬ�����귽��

    actionQueryStudentsOfStudent			= 94,		// ��ѯͽ���б�idTarget = ��Ҫ��ѯͽ���б��ͽ��ID

    actionBurstXp							= 95,		// XP����������ʹ��XP����
    actionChangeToRandomPos					= 96,      // ����ƶ�
    actionDisappear							= 97,
};

class CMsgAction : public CNetMsg
{
public:
    CMsgAction();
    virtual ~CMsgAction();

    BOOL	Create	(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir, USHORT usAction, DWORD dwData = 0);
    BOOL	Create	(OBJID idPlayer, int nPosX, int nPosY, USHORT usDir, USHORT usAction, USHORT usTargetPosX, USHORT usTargetPosY, DWORD dwTimeStamp = 0);

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

protected:
    typedef struct
    {
		USHORT		unMsgSize;
		USHORT		unMsgType;
		DWORD		dwTimeStamp;

		OBJID		idUser;
		USHORT		unPosX, unPosY;
		USHORT		unDir;
		USHORT		flag;
		//union
		//{
		OBJID		idTarget;
		DWORD		dwData;
		INT			iData;

		// struct
		//{
		USHORT usTargetPosX;
		USHORT usTargetPosY;
		// };
		// }; 

		USHORT		usAction;
		USHORT		flag1;
		BOOL		bSucDone;
    } MSG_Info;

    MSG_Info*	m_pInfo;

};

#endif // !defined(AFX_MSGDIR_H__950C0770_DB2D_4D79_970C_E2863ECE9614__INCLUDED_)
