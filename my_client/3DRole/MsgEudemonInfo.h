
//**********************************************************
// ����༭��
//**********************************************************

// MsgEudemonInfo.h: interface for the CMsgEudemonInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGEUDEMONINFO_H__2A75E484_1289_47CF_8E73_CCAA01C9A02B__INCLUDED_)
#define AFX_MSGEUDEMONINFO_H__2A75E484_1289_47CF_8E73_CCAA01C9A02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsgEudemonInfo  : public CNetMsg
{
public:
    CMsgEudemonInfo();
    virtual ~CMsgEudemonInfo();

public:
    BOOL			Create		(char* pMsgBuf, DWORD dwSize);
    void			Process		(void* pInfo);

protected:
    typedef struct
    {
        USHORT	unMsgSize;
        USHORT	unMsgType;
        OBJID   id;
        DWORD   dwLookFace;

        //I64 i64Status;
        DWORD	dwStatus[2];
        OBJID	idOwner;			// ������Ч

        USHORT	usMaxLife;			// ��PlayerΪMonster��ʱ�򣬱�ʾ�������
        USHORT	usCurLife;			// ��PlayerΪMonster��ʱ�򣬱�ʾ��ǰ����


        USHORT	usPosX, usPosY;
        UCHAR	ucDir;
        UCHAR	ucPose;
        OBJID	idMonsterType;			// ����ͻ�����Ч

        // for str packer
        char szBuf[1];
    } MSG_Info;
    MSG_Info*	m_pInfo;

private:
    CNetStringPacker	m_StrPacker;
};

#endif // !defined(AFX_MSGEUDEMONINFO_H__2A75E484_1289_47CF_8E73_CCAA01C9A02B__INCLUDED_)
