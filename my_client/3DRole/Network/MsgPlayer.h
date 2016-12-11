
//**********************************************************
// ����༭��
//**********************************************************

// MsgPlayer.h: interface for the CMsgPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_)
#define AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetMsg.h"
#include "NetStringPacker.h"

class CMsgPlayer : public CNetMsg
{
public:
    CMsgPlayer();
    virtual ~CMsgPlayer();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

protected:
    typedef struct
    {
        unsigned short unMsgSize;
        unsigned short unMsgType;

        OBJID id;
        DWORD dwLookFace;
       // union
       // {
            DWORD dwStatus[2];
      //      struct
      //      {
                USHORT usStatuaryLife; // ��������
                USHORT usStatuaryFrame;// ����֡��
      //      };
       // };

      //  union
      //  {
            DWORD dwSynID_Rank; // �ǻ�����Ч
            OBJID idOwner; // ������Ч
       // };

        DWORD dwArmorType;
        DWORD dwWeaponRType;
      //  union
      //  {
            DWORD dwMantleType;
       //     struct
       //     {
                USHORT	usMaxLife;		// ��PlayerΪMonster��ʱ�򣬱�ʾ�������
                USHORT	usMonsterLife;			// ��PlayerΪMonster��ʱ�򣬱�ʾ��ǰ����
       //     };
      //  };

       // union
       // {
            DWORD dwMountType;
       //     struct
       //     {
                USHORT usLife;		//	������Ч
                USHORT usLevel;		//  ����ȼ�
       //     };
       // };

        USHORT usPosX, usPosY;
        USHORT usHair;

        char cLength; // �߰�
        char cFat; // ����


        UCHAR ucDir;
        UCHAR ucPose;

       // union
        //{
        //    struct
        //    {
                UCHAR ucActionSpeed; // �ж��ٶ�

                unsigned char ucTutorLevel; // ��ʦ�ȼ�
                unsigned char ucMercenaryLevel;	// Ӷ���ȼ�
                unsigned char ucNobilityRank; // ��λϵͳ
				 USHORT flag; //��λ
        //    };
            DWORD dwMonsterType;
       // };
        // for str packer
        char szBuf[1];
    } MSG_Info;



    MSG_Info*	m_pInfo;

private:
    CNetStringPacker	m_StrPacker;

};

#endif // !defined(AFX_MSGPLAYER_H__298DE32A_21B9_41E0_8728_CD895F36A959__INCLUDED_)
