
//**********************************************************
// ����༭��
//**********************************************************


//		ģ��

#ifndef TEMPLATE_LIB
#define TEMPLATE_LIB


#define NULL				0

//typedef unsigned char		BYTE;
//typedef unsigned short		WORD;
//typedef unsigned int		DWORD;

//-----------------------------------------------------------------------------

template < class T, int nSize = 0 >
class STACK 										//ջ
{

private:
    T*					 pStack;					//����ָ������
    int					nPoint;						//ջָ��
    int					nCount;						//ջ�ռ�

protected:
    void Init( int nC )
    {
        if ( nC && ( pStack = new T[ nC ] ) != NULL )
        {
            SetMaxCount( nC );
        }
        else
        {
            SetMaxCount( 0 );
        }
    }
    void Release( void )
    {
        if ( GetMaxCount() )
        {
            delete []pStack, SetMaxCount( 0 ),
                   Clear();
        }
    };
    void SetMaxCount( int nC ) { nCount = nC; };

public:
    STACK( void ) : nPoint( 0 ), nCount( 0 ) { Init( nSize ); };
    ~STACK( void ) { Release(); };

    bool IsEmpty( void )							//ջ�գ�
    { return ( GetCount() <= 0 ); };
    bool IsFull( void )								//ջ����
    { return ( GetCount() >= GetMaxCount() ); };
    int GetCount( void )							//����ջ����������
    { return nPoint; };
    void Push( T t )								//��ջ
    { if ( !IsFull() ) { pStack[ nPoint++ ] = t; } }
    T Pop( void )									//��ջ
    { return ( ( !IsEmpty() ) ? pStack[ --nPoint ] : NULL ); }
    void UnsafePush( T t )							//��ջ(�ǰ�ȫ���)
    { pStack[ nPoint++ ] = t; };
    T UnsafePop( void )								//��ջ(�ǰ�ȫ���)
    { return pStack[ --nPoint ]; };
    void Clear( void )								//���ջ
    { nPoint = 0; };
    void Resize( int nC )							//����ջ�ߴ�
    { Release(); Init( nC ); };
    int GetMaxCount( void )							//�õ�ջ�ߴ�
    { return nCount; };
};

//-----------------------------------------------------------------------------

template < class T, int nSize = 0 >
class FILOMEMORY 									//FILO(ջ)�ڴ����/�ͷ�
{

private:
    T*				 pMemory;						//�ڴ��
    int				nCount;							//����
    int				nPoint;							//�ѷ�������

protected:
    void Init( int nC )
    {
        if ( nC && ( pMemory = new T[ nC ] ) != NULL )
        {
            SetMaxCount( nC );
        }
        else { SetMaxCount( 0 ); }
    }
    void Release( void )		{ if ( GetMaxCount() ) { delete []pMemory, SetMaxCount( 0 ), Clear(); } };
    void SetMaxCount( int nC )	{ nCount = nC; };

public:
    FILOMEMORY( void ) : nPoint( 0 ), nCount( 0 ) { Init( nSize ); };
    ~FILOMEMORY( void ) { Release(); };

    bool IsFull( void )								//������
    { return ( GetCount() >= GetMaxCount() ); }
    int GetCount( void )							//���ض�����������
    { return nPoint; }
    T* GetOne( void )								//����һ��
    { return ( IsFull() ) ? NULL : &pMemory[ nPoint++ ]; };
    T* CGetOne( void )								//����һ��(����)
    {
        T*			 pTemp;
        if ( ( pTemp = GetOne() ) == NULL ) { return NULL; }
        memset( pTemp, 0, sizeof( T ) );
        return pTemp;
    }
    T* UnsafeGetOne( void )						//����һ��(�ǰ�ȫ���)
    { return &pMemory[ nPoint++ ]; };
    T* CUnsafeGetOne( void )						//����һ��(�ǰ�ȫ��飬����)
    {
        T*			 pTemp;
        if ( ( pTemp = UnsafeGetOne() ) == NULL ) { return NULL; }
        memset( pTemp, 0, sizeof( T ) );
        return pTemp;
    }
    void Clear( void )								//��ն�
    { nPoint = 0; };
    void Free( T* pT )								//�ͷ�
    { if ( nPoint && pT == ( pMemory + nPoint - 1 ) ) { nPoint--; } };
    void Resize( int nC )							//����ѳߴ�
    { Release(); Init( nC ); };
    int GetMaxCount( void )		{ return nCount; };
};

//-----------------------------------------------------------------------------

template < class T, int nSize = 0 >
class FIXMEMORY 								//�����ڴ��
{
private:
    T*			pMemory;						//�ڴ��
    char*		pUse;							//ʹ�ñ��
    int			nCount;							//����
    int			nPoint;							//��ǰ������

protected:
    void Init( int nC )
    {
        if ( nC && ( pMemory = new T[ nC ] ) != NULL )
        {
            if ( ( pUse = new char[ nC ] ) != NULL )
            {
                SetMaxCount( nC );
                Clear();
            }
            else
            {
                delete []pMemory;
                SetMaxCount( 0 );
            }
        }
        else
        {
            SetMaxCount( 0 );
        }
    }
    void Release( void )
    {
        if ( GetMaxCount() )
        {
            delete []pUse, delete []pMemory, SetMaxCount( 0 ), SetPoint( 0 );
        }
    }
    void SetMaxCount( int nC )		{ nCount = nC; };
    void SetPoint( int nC )			{ nPoint = nC; }
    int GetPoint( void )			{ return nPoint; }

public:
    FIXMEMORY( void ) : nCount( 0 ), nPoint( 0 ) { Init( nSize ); };
    ~FIXMEMORY( void ) { Release(); };

    bool IsFull( void )								//������
    {
        for( int i = 0; i < GetMaxCount(); i++ )
            if ( !pUse[ i ] )
            {
                return false;
            }
        return true;
    }
    int GetCount( void )							//���ض�����������
    {
        int i, j;
        for( i = j = 0; i < GetMaxCount(); i++ )
            if ( pUse[ i ] ) { j++; }
        return j;
    }
    T* GetOne( void )								//����һ��
    {
        int i;
        for( i = GetPoint(); i < GetMaxCount(); i++ )
            if ( !pUse[ i ] )
            {
                pUse[ i ] = 1;
                SetPoint( i++ );
                return ( t + i );
            }
        for( i = 0; i < GetPoint(); i++ )
            if ( !pUse[ i ] )
            {
                pUse[ i ] = 1;
                SetPoint( i++ );
                return ( t + i );
            }
        return NULL;
    }
    T* CGetOne( void )								//����һ��(����)
    {
        T*			 pTemp;
        if ( ( pTemp = GetOne() ) == NULL ) { return NULL; }
        memset( pTemp, 0, sizeof( T ) );
        return pTemp;
    };
    void Clear( void )								//��ն�
    { 
		memset( pUse, 0, GetMaxCount() ), SetPoint( 0 ); 
	};
    void Free( T* )								//�ͷ�
    {
        int i;
        for( i = GetPoint() - 1; i >= 0; i-- )
            if ( pUse[ i ] && ( pMemory + i ) == pT )
            {
                pUse[ i ] = 0;
                SetPoint( i );
                return;
            }
        for( i = GetMaxCount() - 1; i >= GetPoint(); i-- )
            if ( pUse[ i ] && ( pMemory + i ) == pT )
            {
                pUse[ i ] = 0;
                SetPoint( i );
                return;
            }
        return;
    }
    void Resize( int nC )							//����ѳߴ�
    { Release(); Init( nC ); };
    int GetMaxCount( void )
    { return nCount; };
};

//-----------------------------------------------------------------------------

template< class T >
class CHAIN_S;

template< class T >
class CHAINNODE_S : public T 						//�ṹ�����
{

    friend CHAIN_S< T >;

private:
    CHAINNODE_S< T >	* pNext;

public:
    CHAINNODE_S( void ) : pNext( NULL ) {};
};

template< class T >
class CHAIN_S 										//�ṹ����
{

private:
    CHAINNODE_S< T >	* pFirst;

public:
    CHAIN_S( void ) : pFirst( NULL ) {};
    ~CHAIN_S( void ) { Reset(); };

    void Reset( void )								//��������
    {
        CHAINNODE_S< T >	* pTemp;
        while( pFirst )
        {
            pTemp = pFirst->pNext;
            pFirst->pNext = NULL;
            pFirst = pTemp;
        }
    }
    bool InstertF( CHAINNODE_S< T > * pNode )		//������(ͷ)
    {
        if ( pNode->pNext != NULL ) { return false; }
        if ( pFirst == NULL )
        {
            pFirst = pNode;
            return true;
        }
        pNode->pNext = pFirst;
        pFirst = pNode;
        return true;
    };
    bool Delete( CHAINNODE_S< T > * pNode )			//ɾ��ָ�����
    {
        CHAINNODE_S< T >		* pTemp = pFirst, * pT1 = NULL;
        if ( pTemp == NULL ) { return false; }
        while( pTemp != pNode )
        {
            pT1 = pTemp;
            if ( ( pTemp = pTemp->pNext ) == NULL )
            {
                return false;
            }
        }
        if ( pTemp == pFirst )
        {
            pFirst = pFirst->pNext;
        }
        else
        {
            pT1->pNext = pTemp->pNext;
        }
        pNode->pNext = NULL;
        return true;
    };
    int GetAllNode( CHAINNODE_S< T > * pNode[], int nCount )	//�õ����нڵ�ָ�������
    {
        int					i;
        CHAINNODE< T >		* pTemp = pFirst;
        for( i = 0; pTemp != NULL && i < nCount; pTemp = pTemp->pNext )
        {
            pNode[ i++ ] = pTemp;
        }
        return i;
    };
    int GetCount( void )							//ȡ�������нڵ�����
    {
        int					i;
        CHAINNODE_S< T >	* pTemp = pFirst;
        for( i = 0; pTemp != NULL; i++, pTemp = pTemp->pNext );
        return i;
    };
};

//-----------------------------------------------------------------------------

template< class T >
class CHAIN;

template< class T >
class CHAINNODE
{

    friend CHAIN< T >;

private:
    T*			 pNode;
    CHAINNODE*	 pNext;
};

template< class T >
class CHAIN
{

private:
    CHAINNODE< T >	* pFirst;

public:
    CHAIN( void ) : pFirst( NULL ) {};

    void Reset( void )								//��������
    {
        CHAINNODE< T > * pT1 = pFirst, * pT2;
        while( pT1 ) { pT2 = pT1->pNext; delete pT1; pT1 = pT2; };
        pFirst = NULL;
    };
    bool InstertF( T* pNode )						//������(ͷ)
    {
        if ( pFirst == NULL )
        {
            if ( ( pFirst = new CHAINNODE< T > ) == NULL )
            {
                return false;
            }
            pFirst->pNext = NULL;
            pFirst->pNode = pNode;
            return true;
        }
        CHAINNODE< T > pTemp;
        if ( ( pTemp = new CHAINNODE< T > ) == NULL )
        {
            return false;
        }
        pTemp->pNext = pFirst;
        pTemp->pNode = pNode;
        pFirst = pTemp;
        return true;
    };
    bool Delete( T* pNode )						//ɾ��ָ�����
    {
        CHAINNODE< T >		* pTemp = pFirst, * pT1 = NULL;
        if ( pTemp == NULL ) { return false; }
        while( pTemp->pNode != pNode )
        {
            pT1 = pTemp;
            if ( ( pTemp = pTemp->pNext ) == NULL )
            {
                return false;
            }
        }
        if ( pTemp == pFirst )
        {
            pTemp = pTemp->pNext;
            delete pFirst;
            pFirst = pTemp;
        }
        else
        {
            pT1->pNext = pTemp->pNext;
            delete pTemp;
        }
        return true;
    };
    int GetAllNode( T pNode[], int nCount )			//�õ����нڵ�ָ�������
    {
        int					i;
        CHAINNODE< T >		* pTemp = pFirst;
        for( i = 0; pTemp != NULL && i < nCount; pTemp = pTemp->pNext )
        {
            pNode[ i++ ] = pTemp->pNode;
        }
        return i;
    };
    int GetCount( void )							//ȡ�������нڵ�����
    {
        int					i;
        CHAINNODE< T >		* pTemp = pFirst;
        for( i = 0; pTemp != NULL; i++, pTemp = pTemp->pNext );
        return i;
    };
};

//-----------------------------------------------------------------------------

#endif
