
//**********************************************************
// ����༭��
//**********************************************************

// DlgRoleChoose.cpp : implementation file
//

#include "stdafx.h"
#include "MyShell.h"
#include "DlgRoleChoose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _SOUND_DISABLE
#define DXPlaySound //
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlgRoleChoose dialog


CDlgRoleChoose::CDlgRoleChoose(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgRoleChoose::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgRoleChoose)
    m_bLoad = false ;
    m_bShow = false ;
    m_btRoleType = 0 ;
    m_b1024 = false ;
    //}}AFX_DATA_INIT
}


void CDlgRoleChoose::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRoleChoose)
    DDX_Control(pDX, IDC_ROLECHOOSE_STA_DATA, m_RoleChooseDataSta ) ;
    DDX_Control(pDX, IDC_ROLECHOOSE_BTN_RETURN, m_RoleChooseReturnBtn);
    DDX_Control(pDX, IDC_ROLECHOOSE_BTN_OK, m_RoleChooseOkBtn);
    DDX_Control(pDX, IDC_BTN_HELP, m_HelpBtn);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRoleChoose, CDialog)
    //{{AFX_MSG_MAP(CDlgRoleChoose)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_ROLECHOOSE_BTN_RETURN, OnRolechooseBtnReturn)
    ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
    ON_BN_CLICKED(IDC_ROLECHOOSE_BTN_OK, OnRolechooseBtnOk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoleChoose message handlers

LRESULT CDlgRoleChoose::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_SHOWWINDOW )
    {
        m_bShow = wParam ;
    }
    else if ( message == WM_COMMAND )
    {
        if ( wParam == 1 )
        {
            //			CDlgRoleChoose::OnRolechooseBtnOk () ;
            return true ;
        }
        else if ( wParam == 2 )
        {
            CDlgRoleChoose::OnRolechooseBtnReturn () ;
            return true ;
        }
    }
    return CDialog::WindowProc(message, wParam, lParam);
}

HBRUSH CDlgRoleChoose::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    pDC->SetBkMode ( TRANSPARENT ) ;
    return g_StockBrush;
}

BOOL CDlgRoleChoose::OnInitDialog()
{
    CDialog::OnInitDialog();
    // Init the image
    // Init the static
    if ( ! ( m_RoleChooseDataSta.Init ( 0, 0 ) ) )
    {
        return false ;
    }
    m_RoleChooseDataSta.SetFontColor ( 0xffffff ) ;
    // Init the button
    if ( ! ( m_RoleChooseOkBtn.Init ( 0, 0, "Button20" ) ) )
    {
        return false ;
    }
    if ( ! ( m_RoleChooseReturnBtn.Init ( 0, 0, "Button14" ) ) )
    {
        return false ;
    }
    if ( ! ( m_HelpBtn.Init ( 0, 0, "Button15" ) ) )
    {
        return false ;
    }
    m_bLoad = true ;
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRoleChoose::Show()
{
    if ( m_bLoad && m_bShow )
    {
        // Show the owner
        CAni* ShowAni = g_objGameDataSet.GetDataAni ( ( char* )g_strControlAni,
                        "Dialog2",
                        EXIGENCE_IMMEDIATE ) ;
        if ( ShowAni != NULL )
        {
            if ( !m_b1024 )
            {
                ShowAni->Show ( 0, 0, 0 );
            }
            else
            {
                ShowAni->Show ( 1, 0, 0 );
            }
        }
        else
        {
            return ;
        }
        // Show the simple role
        CMyPos pos ;
        if ( !m_b1024 )
        {
            pos.x = 400 ;
            pos.y = 350 ;
        }
        else
        {
            pos.x = 512 ;
            pos.y = 420 ;
        }
        m_ShowRole.Show ( m_btRoleType, pos, 160 ) ;
        // Show the Image
        // Show the static
        switch ( m_btRoleType % 4 )
        {
        case 1:
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10022 ) ) ;//"����һ������ʹ�ø������������ߣ���ʹ�ð�����˫�����ڵĸ���ս�����ܵ�ְҵ������" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 20,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10023 ) ) ;//"˵����һ����ѡ����ң�Ŀ�Ľ�����Ϊ��ӵ��һ��������ӵ��һ��ֵ����Ѫ�����ɡ�����" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 40,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10024 ) ) ;//"���Ǹ��Լ�װ���˺��Ŀ��ף������Լ��ڱ��˺���ʱ����һ��������С�" ) ;
            break ;
        case 0:
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10025 ) ) ;//"��ʿ����ν��ӵ���������ϵ����ܡ�˫�ֿ�ʹ�ø���������ӵ�зḻ��ս�����ܡ�ͬʱ��" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 20,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10026 ) ) ;//"Ҳ��ζ����Զ�����ǰ����������û�а���ɻ󡭡���ζ���������ˣ�������ڡ���" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 40,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10027 ) ) ;//"���ԣ���������˵����ʿ��һ�ֳƺ���Ҳ��һ�ֹ��١�" ) ;
            break ;
        case 2:
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10028 ) ) ;//"�ںڰ��У���Զ����һ˫�۾���ע�����㣬ֻҪ��ֵ��һ��������Ǽ��ֵ�ʹ����������" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 20,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10029 ) ) ;//"��һ˲�����������ܼ��ļ��꣬���������Ƽס�һ�����ġ�������Ҫ�ģ������������" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 40,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10030 ) ) ;//"��Զ�������죬�����޷����ӽ������Ѿ���ʬ·�ϡ�" ) ;
            break ;
        case 3:
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10031 ) ) ;//"����������������һ�����������ʥ�������ģ��߹�����ͼ��ģ���������п�" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 20,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10032 ) ) ;//"�ģ�����������ݵġ�����Ȼ������֮�ϵ�����ȴ���������дʣ������ǣ������Ǵ���" ) ;
            CMyBitmap::ShowString ( m_RoleChooseDataSta.m_IntPoint.x,
                                    m_RoleChooseDataSta.m_IntPoint.y + 40,
                                    0xffffff,
                                    g_objGameDataSet.GetStr ( 10033 ) ) ;//"�漣���˶��ѡ�" ) ;
            break ;
        }
        // Show the button
        m_RoleChooseOkBtn.Show ( 0, 0 ) ;
        m_RoleChooseReturnBtn.Show ( 0, 0 ) ;
        m_HelpBtn.Show ( 0, 0 ) ;
    }
}

void CDlgRoleChoose::OnRolechooseBtnReturn()
{
    DXPlaySound ( "Sound/BtnClick.wav" ) ;
    CDlgRoleChoose::GetParent ()->PostMessage ( WM_MY_MESSAGE, ON_EXIT ) ;
}

void CDlgRoleChoose::CreateRole(BYTE btRoleType)
{
    LPARAM lParam = btRoleType ;
    CDlgRoleChoose::ShowWindow (SW_HIDE ) ;
    CDlgRoleChoose::GetParent ()->PostMessage ( WM_MY_MESSAGE, ON_ROLECHOOSE_CHOOSE, lParam ) ;
}

void CDlgRoleChoose::OnRolechooseBtnOk()
{
    DXPlaySound ( "Sound/BtnClick.wav" ) ;
    CreateRole ( m_btRoleType ) ;
    return ;
}

void CDlgRoleChoose::OnBtnHelp()
{
    CDlgRoleChoose::GetParent ()->PostMessage ( WM_MY_MESSAGE, ON_HELPDLG_SHOW, DLG_ROLECHOOSE ) ;
}

void CDlgRoleChoose::ReInit()
{
    m_RoleChooseDataSta.Init ( 0, 0 ) ;
    m_RoleChooseOkBtn.Init ( 0, 0, "Button20" ) ;
    m_RoleChooseReturnBtn.Init ( 0, 0, "Button14" ) ;
    m_HelpBtn.Init ( 0, 0, "Button15" ) ;
    m_b1024 = true ;
}
















