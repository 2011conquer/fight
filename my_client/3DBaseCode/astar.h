
//**********************************************************
// ����༭��
//**********************************************************

#ifndef PROGRAM_ASTAR
#define PROGRAM_ASTAR


#include "template.h"


//-----------------------------------------------------------------------------

const int MAXSEARCHSTEP		= 400;				//�Ѱ·����

enum BODYSIZE
{
    BODILY0					= 0,					//��ռ����
    BODILY1					= 1,					//ռ1������
    BODILY4					= 4,					//ռ4������
};

class STEPDATA 										//��·����
{

private:
    int					nStepCount;							//��¼����
    char				cStepWay[ MAXSEARCHSTEP * 2 + 3 ];	//��������
    BODYSIZE			eBodySize;							//����

public:
    STEPDATA( void ) : nStepCount( 0 ) {};
    STEPDATA( BODYSIZE bs ) : nStepCount( 0 ), eBodySize( bs ) {};

    int RemainSteps( void )							//ʣ�ಽ��
    { return nStepCount; }
    void ClearStep( void )							//���
    { nStepCount = 0; }
    void AddStep( int nC )							//���Ӳ���
    { nStepCount += nC; };
    void SetStep( int nC )							//���ò���
    { nStepCount = nC; };
    char GetNextStep( void )						//ȡ��һ��
    { return cStepWay[ --nStepCount ]; }
    char* GetStepArray( void )						//�õ���������
    { return cStepWay; }
    char* GetStepArrayTail( void )					//�õ���������ĩβ��ַ
    { return cStepWay + nStepCount; }
    void SetBodySize( BODYSIZE eSize )				//�������ͳߴ�
    { eBodySize = eSize; }
    BODYSIZE GetBodySize( void )					//�õ����ͳߴ�
    { return eBodySize; }
};

//-----------------------------------------------------------------------------

#define ASTAR_UNSTAY		( ASTAR_NODE * )0xffffffffL	//����ͣ��
#define ASTAR_INSTAY		( ASTAR_NODE * )NULL		//��ͣ��

const int ASTACKBUFFSIZE	= MAXSEARCHSTEP * 8 * 8 + 10;	//A*ջ����
const int ASTARBUFFSIZE		= MAXSEARCHSTEP * 8 + 10;		//A*��㻺��������
const unsigned int ASTAR_HASMAN		= 0x00000001L;			//��ͣ�����

const char INSTAY			= 0;				//��ͣ��
const char UNSTAY			= 1;				//����ͣ��

const char INOPEN			= 1;					//��OPEN������
const char INCLOSE			= 2;					//��CLOSE������
const char OTHERWISE		= 0;					//����������

struct ASTAR_NODE
{
    int				nG, nH, nF;					//����ֵ
    int				nX, nY;						//����
    int				nNumber;					//������
    ASTAR_NODE*		 pParent;					//�����ָ��
    ASTAR_NODE*		 pChild[8];				//�ӽ��ָ��
    ASTAR_NODE*		 pNextNode;				//����ָ��
    char			cWhere, cDirect;			//λ�á�����
};

class ASTAR_8WAY
{

private:
    class ASTAR_IDX
    {
    private:
        ASTAR_NODE*			 pAN;					//���ָ��
        unsigned int		unCount;				//�����������
    public:

        void SetUnstay( void )						//���ò�����
        { pAN = ASTAR_UNSTAY; };
        void SetStay( void )						//���ÿ���
        { pAN = ASTAR_INSTAY; };
        void SetStay( char cS )						//���ÿ���
        { pAN = ( cS == UNSTAY ) ? ASTAR_UNSTAY : ASTAR_INSTAY; };
        void SetHasman( void )						//��������
        { unCount |= ASTAR_HASMAN; };
        void SetNoman( void )						//����û��
        { unCount = unCount & ( ~ASTAR_HASMAN ); };
        void SetCount( unsigned int unC )			//���ü�����
        { unCount = ( unCount & 0xf ) | unC; };
        bool IsAvail( unsigned int unC )			//��������Ч��
        { return ( unCount >= unC ); };
        bool IsUnstay( void )						//���Բ���ͣ�����������ˣ�
        { return ( pAN == ASTAR_UNSTAY ); };
        bool IsUnstayCM( void )						//���Բ���ͣ���������ˣ�
        { return ( ( pAN == ASTAR_UNSTAY ) || ( unCount & ASTAR_HASMAN ) ); };
        void SetNode( ASTAR_NODE* pN )				//���ý��ָ��
        { pAN = pN; };
        ASTAR_NODE* GetNode( void )				//�õ����ָ��
        { return pAN; };
        char GetStay( void )						//�õ�ͣ�����
        { return ( pAN == ASTAR_UNSTAY ); };
    };

    class CHAINASN_C 								//CLOSE����
    {
    protected:
        ASTAR_NODE*			 pNode;

    public:
        CHAINASN_C( void ) : pNode( NULL ) {};

        bool IsEmpty( void )						//���Ϊ��
        { return ( pNode == NULL ); };
        ASTAR_NODE* Get( void )					//ȡ��
        {
            if ( pNode == NULL ) { return NULL; }
            ASTAR_NODE* pTemp = pNode;
            pNode = pNode->pNextNode;
            return pTemp;
        }
        void Insert( ASTAR_NODE* pN )				//����
        { pN->pNextNode = pNode; pNode = pN; pNode->cWhere = INCLOSE; };
        void Clear( void )							//���
        { pNode = NULL; };
    };

    class CHAINASN_O : public CHAINASN_C 			//OPEN����
    {
    public:
        void Insert( ASTAR_NODE* );				//����
    };


    int						nMapWidth;				//��ͼ��
    int						nMapHeight;				//��ͼ��
    ASTAR_IDX* 				pAStarIdx;				//��ͼ��С���߱��
    unsigned int			unPathCount;			//Ѱ·������

    int						MAN_BODILY_OFFSET[ BODILY4 ];		//
    int						MAN_BODILY_AROUND[ 8 ];				//��Χ��������ĵ�ƫ��
    int						LINEOFF[ 8 ];						//

    STACK< ASTAR_NODE*, ASTACKBUFFSIZE >		AstarStack;		//A*ջ
    FILOMEMORY< ASTAR_NODE, ASTARBUFFSIZE >		AstarNode;		//A*����

    CHAINASN_O				OpenChain;			//OPEN����
    CHAINASN_C				CloseChain;			//CLOSE����

    int					nEndX, nEndY;			//�յ�����
    ASTAR_IDX*			 pEndASI;				//�յ��ַ
    STEPDATA*			 pStepPtr;				//����������ָ��
    BODYSIZE			BSize;					//����������

protected:
    ASTAR_NODE* ReturnBestNode( void );				//�õ���һ�����
    int GenerateSuccessorsNoMan( ASTAR_NODE* );		//�˲����ϰ�
    int GenerateSuccessorsHasMan( ASTAR_NODE* );		//�����ϰ�
    void FreeNodes( void );									//��Ѱ·�ڵ�
    void PropagateDown( ASTAR_NODE* );

    inline void ClearAstarIdx( void );
    int CheckContinue( int, int, int&, int& );		//
    int CheckFront( int, int, int, int, int );			//
    char CalculateWay( ASTAR_NODE*, ASTAR_NODE* );
    char CalculateMirrWay( ASTAR_NODE*, ASTAR_NODE* );
    int Calculate( int nSX, int nSY, int nTX, int nTY )		//���ƺ���
    { return ( ( nTX - nSX ) * ( nTX - nSX ) + ( nTY - nSY ) * ( nTY - nSY ) ) << 2; }

    bool TestStayHasMan( ASTAR_IDX*, BODYSIZE );			//����ͣ����������
    bool TestStayNoMan( ASTAR_IDX*, BODYSIZE );			//����ͣ������������

public:
    ASTAR_8WAY( void );
    ~ASTAR_8WAY( void ) { Release(); }

    int InitAStar( int, int );								//��ʼ����ͼ�ߴ�
    void SetSafelyZone( void );								//���ð�ȫ��
    void Release( void );									//�ͷ�

    void SetAStarAtr( int nX, int nY, char cArt )			//������������
    { SetAStarAtr( nMapWidth * nY + nX, cArt ); }
    void SetAStarAtr( int nCount, char cArt )				//������������
    { pAStarIdx[ nCount ].SetStay( cArt ); };
    char GetAStarAtr( int nX, int nY )						//ȡͣ�����
    { return GetAStarAtr( nMapWidth * nY + nX ); }
    char GetAStarAtr( int nC )								//ȡͣ�����
    { return pAStarIdx[ nC ].GetStay(); };
    void SetManInAStarAtr( int nX, int nY, BODYSIZE cType )	//������ռ��
    { SetManInAStarAtr( nMapWidth * nY + nX, cType ); }
    void SetManInAStarAtr( int, BODYSIZE );					//������ռ��
    void ClrManInAStarAtr( int nX, int nY, BODYSIZE cType )	//�����ռ��
    { ClrManInAStarAtr( nMapWidth * nY + nX, cType ); }
    void ClrManInAStarAtr( int, BODYSIZE );					//�����ռ��

    int FindPath( int, int, int, int, STEPDATA*, int );	//Ѱ·
};


//-------------------------����------------------------------------------------

const int NO_MAN			= 0;				//��������
const int HAS_MAN			= 1;				//������

const int E_TO_S			= 0;				//��������
const int S_TO_E			= 0x10;				//��������

const int NOCHECKFRONT		= 0x1000;			//��������
const int CONTINUESEARCH	= 0x2000;			//��ǰ�ֲ�·������

//-----------------------����ֵ------------------------------------------------

const int NOFOUND			= 1;				//û�ҵ�Ŀ��
const int NOPATH			= 2;				//û·
const int HAVEPATH			= 4;				//�ҵ�
const int ATTARGET			= 8;				//վ��Ŀ����

const int TARGETHASMAN		= 0x10;				//Ŀ�����������
const int TARGETNOPATH		= 0x20;				//Ŀ��㲻��ͣ��(�类������������)
const int TARGETCLOSE		= 0x40;				//Ŀ����
const int SOURCECLOSE		= 0x80;				//Դ���
const int UNWALKABLE		= TARGETHASMAN | TARGETNOPATH | TARGETCLOSE | SOURCECLOSE;

const int NOENOUGHSTEP		= 0x200;			//ʣ�ಽ�����������ֲܾ�����

const int RECORDPATH		= 0x1000;			//��¼·��
//        CONTINUESEARCH	0x2000				//��ǰ�ֲ�·������
const int SHARELAST			= 0x4000;			//ʹ����ǰ·��
const int MAXSTEP			= 0x8000;			//�������

#endif
