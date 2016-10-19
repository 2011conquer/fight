
//**********************************************************
// ����༭��
//**********************************************************

#ifndef		_BITMAP_H
#define		_BITMAP_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<assert.h>
#include	<math.h>

#ifdef _BCB
#define sqrtf sqrt
#define	__max max
#endif

#include	<windows.h>
#include	<wingdi.h>

#include	"c3_main.h"
#include	"c3_sprite.h"
#include	"c3_phy.h"
#include	"c3_camera.h"
#include	"AlphaMask.h"
#include    "basefunc.h"
#include	"c3_font.h"

// color define
const int _COLOR_WHITE		= 0x00ffffff;
const int _COLOR_GRAY		= 0x007f7f7f;
const int _COLOR_DARKGRAY	= 0x003f3f3f;
const int _COLOR_BLACK		= 0x00000000;
const int _COLOR_RED		= 0x00ff0000;
const int _COLOR_GREEN		= 0x0000ff00;
const int _COLOR_BLUE		= 0x000000ff;
const int _COLOR_YELLOW		= 0x00ffff00;
const int _COLOR_TRANS		= 0x00ff00ff;

const char _V_ARMET[]		= "v_head";
const char _V_MISC[]		= "v_misc";
const char _V_L_WEAPON[]	= "v_l_weapon";
const char _V_R_WEAPON[]	= "v_r_weapon";
const char _V_L_SHIELD[]	= "v_l_shield";
const char _V_R_SHIELD[]	= "v_r_shield";
const char _V_L_SHOE[]		= "v_l_shoe";
const char _V_R_SHOE[]		= "v_r_shoe";
const char _V_BODY[]		= "v_body";
const char _V_PET[]			= "v_pet";
const char _V_BACK[]		= "v_back";

const char _V_HEAD[]		= "v_armet";
const char _V_L_ARM[]		= "v_l_arm";
const char _V_R_ARM[]		= "v_r_arm";
const char _V_L_LEG[]		= "v_l_leg";
const char _V_R_LEG[]		= "v_r_leg";
const char _V_MANTLE[]		= "v_mantle";



// video mode enum
enum {	modeNone = 0,
        modeSprite,
        modeLine,
        modeElement,
        modeMesh,
        modeShape,
        modePtcl,
        modeText
     };

// struct
#define LINE_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )
struct LineVertex
{
    float		x, y, z;		// ����
    float		rhw;
    D3DCOLOR	color;
};

#include <deque>
using namespace std;

class CMyBitmap
{
public:
    CMyBitmap();
    virtual ~CMyBitmap();

    BOOL	Load	( char* pszBmpFile, DWORD dwLoadWay = _LOADWAY_NORMAL);
    void	Destroy ( void );

    void	Show	( int x, int y, int alpha = 0, DWORD dwShowWay = _SHOWWAY_NORMAL);
    void	ShowEx	( int x, int y, RECT* lpSrc, DWORD dwWidth, DWORD dwHeight, int alpha = 0, DWORD dwShowWay = _SHOWWAY_NORMAL );
    static  void Show	(CMyBitmap* pBmpUp, CMyBitmap* pBmpDn,
                         UCHAR uAlphaA, UCHAR uAlphaB, UCHAR uAlphaC, UCHAR uAlphaD,
                         int x, int y, RECT* lpSrc, DWORD dwWidth, DWORD dwHeight);
    void	GetSize ( int& nWidth, int& nHeight );
    DWORD	GetSize	( void );

    int		GetWidth	( void );
    int		GetHeight	( void );

    void	SetColor	( BYTE a, BYTE r, BYTE g, BYTE b );
    BOOL	IsbTransparentFormat();
    void	SetVertexColor ( DWORD ltColor, DWORD rtColor, DWORD lbColor, DWORD rbColor );

public:	// font
    static C3Font*	s_GameFont;
    static deque	<C3Font*>* s_pOtherFontSet;
    static DWORD	s_dwFontSize;

    static BOOL	GameFontCreate();
    static void GameFontDestroy();

    static C3Font* CreateFont ( const char* pszFontName, int nSize = 14 );
    static void DestroyFont	( C3Font* font );

    static DWORD GetFontSize(void)	{return s_dwFontSize;}
    static void  GetFontSize(CMySize& infoSize);

    static void	ShowTString	( int iPosX, int iPosY, DWORD color, const char* pszString, char* pszFont = NULL, int nFontSize = 0, BOOL bAlpha = false);
    static void	ShowString	( int iPosX, int iPosY, DWORD color, const char* pszString, char* pszFont = NULL, int nFontSize = 0, BOOL bAlpha = false);
    static void ShowEmotionString(int iPosX, int iPosY, DWORD color, const char* pszString,  DWORD dwBeginTime, BOOL bEmotion = true , char* pszFont = NULL, int nFontSize = 0);

    static bool IsDBCSLeadByte		(const char* buf, int nOffset);

public: // camera
    static C3Camera*	s_pCamera;

    static BOOL GameCameraCreate();
    static void GameCameraDestroy();
    static void GameCameraBuild(CMySize sizeScr);
    static void GameCameraSet(float fX, float fZ);

public: // zoom
    static float s_fZoom;


public: // init and destory
    // �������ڲ���ʼ��3d
    static BOOL Init3D ( HINSTANCE hInst,
                         const char* lpTitle,
                         DWORD dwWidth,
                         DWORD dwHeight,
                         BOOL bWindowed,
                         WNDPROC proc,
                         DWORD dwBackCount );
    // ��ʼ��3d
    static BOOL Init3DEx ( HWND hWnd,
                           DWORD dwWidth,
                           DWORD dwHeight,
                           BOOL bWindowed,
                           DWORD dwBackCount );

    static void Quit3D	( void );

public: // opera
    static int s_nShowMode;

    // ��ʼ3d����
    static BOOL Begin3D ( void );

    // ����3d����
    static BOOL End3D ( void );

    // ���zbuffer����Ļ
    static BOOL ClearBuffer ( BOOL bZBuffer, BOOL bTarget, D3DCOLOR color );

    // ��ƿ
    static BOOL Flip ( void );

    // ׼�����ƾ���
    static void PrepareSprite ( void );

    // ���ص�ǰˢ����
    static DWORD CalcRate ( void );

    // ȡ��Ļ�ӿڴ�С
    static void	GetScreenSize(int& nWidth, int& nHeight)	{nWidth = _SCR_WIDTH, nHeight = _SCR_HEIGHT;}

    static void	PrepareLine ( void );
    static void ShowLine ( LineVertex* line, DWORD num );
    static void ShowLine ( int nPosX1, int nPosY1, int nPosX2, int nPosY2, DWORD dwColor);

    static void	ShowRect ( int x1, int y1, int x2, int y2, DWORD color );
    static void ShowBlock( int x1, int y1, int x2, int y2, DWORD color );
    static void ShowBlock( int x1, int y1, int x2, int y2, DWORD color1, DWORD color2, DWORD color3, DWORD color4);
    static void ShowBlock( CMyPos posA, CMyPos posB, CMyPos posC, CMyPos posD, DWORD color );

    static void	ScreenShot	( const char* pszFileName );

public:
    // ͸�����ж�...
    BOOL IsTransparent(CMyPos posPoint);

public:
    C3Sprite*	m_sprite;
    CAlphaMask* m_pMask;
};


//------------------------------------------------------
class C3DTexture
{
public:
    C3DTexture();
    virtual ~C3DTexture();

    BOOL	Create	(const char* pszFileName);
    void	Destroy	(void);

    C3Texture*	GetTexture	(void)	{return m_pTexture;}
private:
    C3Texture*	m_pTexture;
};


//------------------------------------------------------
#define		MOTION_MAX	16
class C3DMotion
{
public:
    C3DMotion ();
    virtual ~C3DMotion ();

    bool IsValid ( void );

    bool Create ( char* filename );
    bool Destroy ( void );

    DWORD	GetFrameAmount();

public:
    DWORD		m_dwMotionNum;
    C3Motion*	m_motion[MOTION_MAX];
};



//------------------------------------------------------
#define		PHY_MAX		16
class C3DObj
{
public:
    C3DObj ();
    virtual ~C3DObj ();

    // ʵ���Ƿ���Ч
    bool IsValid ();
    // ����һ��ģ�� *.c3
    bool Create	( char* filename );
    // �ͷ�
    void Destroy ();

    // ����� x ��Ӧ��Ļ����� x, z ��Ӧ��Ļ����� y, 1 ����λ���� 1 ������
    // �ƶ�
    void Move ( float x, float y, float z );
    // ��ת, ���������ǻ���
    void Rotate	( float x, float y, float z );
    // ���ţ� 1.0 ����ԭ��С
    void Scale	( float x, float y, float z );
    // ��ɫ����Χ�� 0.0f - 1.0f
    void SetARGB ( float alpha, float red, float green, float blue );

    // ͨ���������ֵõ���������
    int GetIndexByName ( char* lpName );

    // ���ö���
    void SetMotion ( C3DMotion* pMotion );

    // ��һ֡ nStep ���� ��ֱΪ����
    void NextFrame ( int nStep );

    // ���õ�ǰ֡��
    void SetFrame (DWORD dwFrame);

    // ����
    void Draw ( int type, float lightx, float lighty, float lightz, float sa, float sr, float sg, float sb );
    void DrawAlpha ( int type, float lightx, float lighty, float lightz, float sa, float sr, float sg, float sb, float height );
    // ����ͼ
    void ChangeTexture ( C3DTexture* pTexture, char* objname = NULL );

    // ׼��3D�������
    static void Prepare ( void );

    void ClearMatrix ( void );

public:
    DWORD		m_dwPhyNum;
    C3Phy*		m_phy[PHY_MAX];

    float		m_x[PHY_MAX];
    float		m_y[PHY_MAX];
    float		m_z[PHY_MAX];
};




//------------------------------------------------------

#ifdef _ANALYSIS_ON
extern DWORD g_dwBitmapLoadAmount;
extern DWORD g_dwBitmapLoadTime;
extern DWORD g_dwBitmapLoadTimeMax;
extern DWORD g_dwBitmapLoadTimeFrame;

extern DWORD g_dw3DObjLoadAmount;
extern DWORD g_dw3DObjLoadTime;
extern DWORD g_dw3DObjLoadTimeMax;
extern DWORD g_dw3DObjLoadTimeFrame;

extern DWORD g_dw3DMotionLoadAmount;
extern DWORD g_dw3DMotionLoadTime;
extern DWORD g_dw3DMotionLoadTimeMax;
extern DWORD g_dw3DMotionLoadTimeFrame;

extern DWORD g_dw3DTextureLoadAmount;
extern DWORD g_dw3DTextureLoadTime;
extern DWORD g_dw3DTextureLoadTimeMax;
extern DWORD g_dw3DTextureLoadTimeFrame;
extern DWORD g_dwFrameInterval;
extern DWORD g_dwBigTexture;
#endif


//------------------------------------------------------
#endif
