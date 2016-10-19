
//**********************************************************
// ����༭��
//**********************************************************

// LocalEncrypt
// �ɽ��ޣ�2002.3.27

////////////////////////////////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "nb30.h"
#ifdef	PALED_DEBUG
#include "assert.h"

#define LOGERROR printf
#endif
const int	MAX_PASSWORDSIZE	= 16;
const int	MAX_MACADDRSIZE		= 6;



typedef struct tagASTAT
{
    ADAPTER_STATUS adapt;
    NAME_BUFFER    NameBuff [30];
} ASTAT, *LPASTAT;

//�洢������MAC��ַ�Ľṹ
typedef struct tagMAC_ADDRESS
{
    BYTE b1, b2, b3, b4, b5, b6;
} MAC_ADDRESS, *LPMAC_ADDRESS;

//������Ϣ�����ݽṹ��������¼�����ĳ��̼��ͺţ���֮�󶨵�IP��ַ������
//DNS���У���������������ַ
typedef struct tagNET_CARD
{
    TCHAR szDescription[256];
    BYTE  szMacAddr[6];
    TCHAR szGateWay[128];
    TCHAR szIpAddress[128];
    TCHAR szIpMask[128];
    TCHAR szDNSNameServer[128];
} NET_CARD, *LPNET_CARD;


/*********************************************************************
 * ��������:CTcpCfg::GetAddressByIndex
 * ˵��:�õ�������Ϊlana_num��������״̬��Ϣ
 * ��ڲ���:
 * int lana_num -- ������������
 * ASTAT & Adapter -- ���ڷ���������״̬��Ϣ
 * ����: orbit
 * ʱ�� : 2000-12-10 20:14:38
*********************************************************************/
UCHAR GetAddressByIndex(int lana_num, ASTAT& Adapter)
{
    NCB ncb;
    UCHAR uRetCode;
    memset(&ncb, 0, sizeof(ncb) );
    ncb.ncb_command = NCBRESET;
    ncb.ncb_lana_num = lana_num;
    //ָ��������,���ȶ�ѡ������������һ��NCBRESET����,�Ա���г�ʼ��
    uRetCode = Netbios(&ncb );
    memset(&ncb, 0, sizeof(ncb) );
    ncb.ncb_command = NCBASTAT;
    ncb.ncb_lana_num = lana_num;   //ָ��������
    strcpy((char*)ncb.ncb_callname, "*      " );
    ncb.ncb_buffer = (unsigned char*)&Adapter;
    //ָ�����ص���Ϣ��ŵı���
    ncb.ncb_length = sizeof(Adapter);
    //����,���Է���NCBASTAT�����Ի�ȡ��������Ϣ
    uRetCode = Netbios(&ncb );
    return uRetCode;
}


/*********************************************************************
 * ��������:CTcpCfg::GetMacAddress
 * ˵��:�õ�ϵͳ��װ������������Mac��ַ��������������Ŀ
 * ��ڲ���:
 * LPMAC_ADDRESS pMacAddr -- ָ������Mac��ַ�ṹ�����ָ��
 * ����ֵ:
 * int  -- ��������Ŀ
 * ����: orbit
 * ʱ�� : 2000-12-10 19:48:15
*********************************************************************/
bool GetMacAddr(char bufMacAddr[12])
{
    NCB ncb;
    UCHAR uRetCode;
    int num = 0;
    LANA_ENUM lana_enum;
    memset(&ncb, 0, sizeof(ncb) );
    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (unsigned char*)&lana_enum;
    ncb.ncb_length = sizeof(lana_enum);
    //����������NCBENUM����,�Ի�ȡ��ǰ������������Ϣ,���ж��ٸ�����
    //ÿ�������ı�ŵ�
    uRetCode = Netbios(&ncb);
    if (uRetCode == 0)
    {
        num = lana_enum.length;
        //��ÿһ������,�����������Ϊ������,��ȡ��MAC��ַ
        for (int i = 0; i < num; i++)
        {
            ASTAT Adapter;
            if (GetAddressByIndex(lana_enum.lana[i], Adapter) == 0)
            {
                memcpy(bufMacAddr, Adapter.adapt.adapter_address, MAX_MACADDRSIZE);
                return true;
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
bool		SaveUserName(LPCTSTR szUserName)		// return false: can't save.
{
    LONG lRtn;
    HKEY hMainKey;
    lRtn = ::RegCreateKey(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), &hMainKey);
    ::RegCloseKey(hMainKey);
    lRtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), 0, KEY_WRITE, &hMainKey);
    if (lRtn == ERROR_SUCCESS)
    {
        DWORD dwDataSize = MAX_PASSWORDSIZE;
        ::RegSetValueEx(hMainKey, ("NetBarUserName"), 0, REG_BINARY, (LPBYTE)szUserName, MAX_PASSWORDSIZE);
        ::RegCloseKey(hMainKey);
        return true;
    }
    else
    {
        ::RegCloseKey(hMainKey);
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
bool		GetUserName(char* buf16)		// return bool: Don't Found UserName.
{
    LONG lRtn;
    HKEY hMainKey;
    lRtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), 0, KEY_READ, &hMainKey);
    if (lRtn == ERROR_SUCCESS)
    {
        DWORD dwType, dwDataSize = MAX_PASSWORDSIZE;
        ::RegQueryValueEx(hMainKey, ("NetBarUserName"), NULL, &dwType, (LPBYTE)buf16, &dwDataSize);
        ::RegCloseKey(hMainKey);
        return true;
    }
    else
    {
        ::RegCloseKey(hMainKey);
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
bool		SavePassword(LPCTSTR szPassword)		// return false: can't save.
{
    if (!szPassword || !szPassword[0])
    {
        return false;
    }
    try
    {
        char	bufMacAddr[MAX_PASSWORDSIZE];
        if (GetMacAddr(bufMacAddr))
        {
#ifdef	PALED_DEBUG
            {
                LPCTSTR pBuf = bufMacAddr;
                int		nLen = MAX_MACADDRSIZE;
                char	bufText[1024];
                for(int i = 0; i < nLen; i++)
                {
                    sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
                }
                LOGERROR("MAC��%s\n", bufText);
            }
#endif
#ifdef	PALED_DEBUG
            {
                LPCTSTR pBuf = szPassword;
                int		nLen = MAX_PASSWORDSIZE;
                char	bufText[1024];
                for(int i = 0; i < nLen; i++)
                {
                    sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
                }
                LOGERROR("PIN��%s\n", bufText);
            }
#endif
            //			assert(MAX_MACADDRSIZE == 6);
            //			assert(MAX_PASSWORDSIZE == 16);
            memcpy(bufMacAddr + MAX_MACADDRSIZE, bufMacAddr, MAX_MACADDRSIZE);
            memcpy(bufMacAddr + MAX_MACADDRSIZE * 2, bufMacAddr, MAX_PASSWORDSIZE - MAX_MACADDRSIZE);
            for(int i = 0; i < MAX_PASSWORDSIZE; i++)
            {
                char cTemp = bufMacAddr[i];
                bufMacAddr[i] = cTemp ^ szPassword[i];
            }
            LONG lRtn;
            HKEY hMainKey;
            lRtn = ::RegCreateKey(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), &hMainKey);
            ::RegCloseKey(hMainKey);
            lRtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), 0, KEY_WRITE, &hMainKey);
            if (lRtn == ERROR_SUCCESS)
            {
                DWORD dwDataSize = MAX_PASSWORDSIZE;
                ::RegSetValueEx(hMainKey, ("NetBarPassword"), 0, REG_BINARY, (LPBYTE)bufMacAddr, MAX_PASSWORDSIZE);
            }
            ::RegCloseKey(hMainKey);
#ifdef	PALED_DEBUG
            {
                LPCTSTR pBuf = bufMacAddr;
                int		nLen = MAX_PASSWORDSIZE;
                char	bufText[1024];
                for(int i = 0; i < nLen; i++)
                {
                    sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
                }
                LOGERROR("REG��%s\n\n", bufText);
            }
#endif
            return true;
        }
    }
    catch(...)
    {
        //	LOGERROR("CATCH: SavePassword()");
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿ����
bool		GetPassword(char* buf16)		// return bool: Don't Found password.
{
    try
    {
        LONG lRtn;
        HKEY hMainKey;
        char szPassword[MAX_PASSWORDSIZE];
        char szTemp[MAX_PASSWORDSIZE];
        lRtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("SOFTWARE\\��������\\��������"), 0, KEY_READ, &hMainKey);
        if (lRtn == ERROR_SUCCESS)
        {
            DWORD dwType, dwDataSize = MAX_PASSWORDSIZE;
            ::RegQueryValueEx(hMainKey, ("NetBarPassword"), NULL, &dwType, (LPBYTE)szTemp, &dwDataSize);
            memcpy(szPassword, szTemp, MAX_PASSWORDSIZE);
        }
        ::RegCloseKey(hMainKey);
#ifdef	PALED_DEBUG
        {
            LPCTSTR pBuf = szPassword;
            int		nLen = MAX_PASSWORDSIZE;
            char	bufText[1024];
            for(int i = 0; i < nLen; i++)
            {
                sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
            }
            LOGERROR("REG��%s\n", bufText);
        }
#endif
        char	bufMacAddr[MAX_PASSWORDSIZE];
        if (GetMacAddr(bufMacAddr))
        {
#ifdef	PALED_DEBUG
            {
                LPCTSTR pBuf = bufMacAddr;
                int		nLen = MAX_MACADDRSIZE;
                char	bufText[1024];
                for(int i = 0; i < nLen; i++)
                {
                    sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
                }
                LOGERROR("MAC��%s\n", bufText);
            }
#endif
            //			assert(MAX_MACADDRSIZE == 6);
            //			assert(MAX_PASSWORDSIZE == 16);
            memcpy(bufMacAddr + MAX_MACADDRSIZE, bufMacAddr, MAX_MACADDRSIZE);
            memcpy(bufMacAddr + MAX_MACADDRSIZE * 2, bufMacAddr, MAX_PASSWORDSIZE - MAX_MACADDRSIZE);
            for(int i = 0; i < MAX_PASSWORDSIZE; i++)
            {
                char cTmep = szPassword[i];
                szPassword[i] = cTmep ^ bufMacAddr[i];
            }
            szPassword[MAX_PASSWORDSIZE - 1] = 0;
            strcpy(buf16, szPassword);
#ifdef	PALED_DEBUG
            {
                LPCTSTR pBuf = szPassword;
                int		nLen = MAX_PASSWORDSIZE;
                char	bufText[1024];
                for(int i = 0; i < nLen; i++)
                {
                    sprintf(bufText + 3 * i, "%02X ", (unsigned char)pBuf[i]);
                }
                LOGERROR("PIN��%s\n", bufText);
            }
#endif
            return true;
        }
    }
    catch(...)
    {
        //LOGERROR("CATCH: GetPassword()");
    }
    buf16[0] = 0;
    return false;
}
