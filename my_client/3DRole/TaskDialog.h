
//**********************************************************
// ����༭��
//**********************************************************

// TaskDialog.h: interface for the CTaskDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKDIALOG_H__9E7E3639_6462_47E2_B177_8B81CFAF046B__INCLUDED_)
#define AFX_TASKDIALOG_H__9E7E3639_6462_47E2_B177_8B81CFAF046B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

// ������ʾ���ı���һ�����������// szStr �ı�
const int _TASKDIALOG_TEXT		= 0;	// �ı�

// �ش�ѡ�����Ժ�ش� //  szStr ѡ�� // nIndex ѡ���
const int _TASKDIALOG_LINK		= 1;	// �ش�

// �ش������ // szStr �������� // nIndex ѡ��� //  dwData ������󳤶�
const int _TASKDIALOG_EDIT		= 2;	// �����

// Npc ͷ�� // dwData ͷ����
const int _TASKDIALOG_PIC		= 3;	// ͷ��

// ֱ�ӹرնԻ��� // nIndex ѡ���
const int _TASKDIALOG_DEFAULT	= 4;	// û�лش�

// �б��� // szStr �ı�
const int _TASKDIALOG_LIST	= 5;	// �ش��б���

typedef struct
{
    int		nType;	// ����
    DWORD	dwData; // ����
    int		nIndex; // ����
    char	szStr[_MAX_STRING]; // �ַ���
    CMyPos	posLine; // Ԥ��
} TaskDialogLine;

#include <deque>
using namespace std;
typedef deque<TaskDialogLine*> DEQUE_TASKDIALOGLINE;

class CTaskDialog
{
public:
    CTaskDialog();
    virtual ~CTaskDialog();
private:
    BOOL	m_bCreate;
    DEQUE_TASKDIALOGLINE	m_setTaskDialogLine;
public:
    void			AddLine(TaskDialogLine* pLine);
    void			Destroy();
    int				GetLineAmount() {return m_setTaskDialogLine.size();}
    TaskDialogLine*	GetLineByIndex(int nIndex);
    void			AddLine(int nType, DWORD dwData, int nIndex, char* szStr, CMyPos posLine);
    void			Create() {m_bCreate = true;}
};

#endif // !defined(AFX_TASKDIALOG_H__9E7E3639_6462_47E2_B177_8B81CFAF046B__INCLUDED_)
