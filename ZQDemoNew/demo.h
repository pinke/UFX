#ifndef __DEMO_H__
#define __DEMO_H__

#include "t2sdk_interface.h"
//////////////////////////////////////////////////////////////
//��
#define SYNCSEND		0	///ͬ������
#define ASYNCSEND		1	///�첽����
#define USERTOKENLEN	256		///���Ƴ���
#define USERSECTION		"user"
#define T2SDK           "t2sdk"
#define ISSUE_TYPE_REALTIME_SECU 	12			///֤ȯ�ɽ�����

//////////////////////////////////////////////////////////////
// ȫ�ֱ���
extern CConnectionInterface *g_pConnection;
extern CConnectionInterface *g_pConnectionHq;

void ShowPacket(int iIssueType, IF2UnPacker *pUnPacker);

///////////////////////////////////////////////////////////////
//CBusiness
class CBusiness
{
public:
	CBusiness();
	virtual ~CBusiness();

	void SetConfig(CConfigInterface *pConfig)
	{
		m_pConfig = pConfig;
		memset(m_cUserToken, 0, USERTOKENLEN);
		m_branch_no = 0;
		memset(m_client_id, 0, USERTOKENLEN);
		memset(m_fund_account, 0, USERTOKENLEN);
	}

	int DealReceive();
	int Subscribe(int issue_type); ///��������
	int CancelSub(int issueType);

	/** 
	* ��¼������331100���ܵ�¼
	* @return >=0 ����ϵͳ���ţ�����ʧ��
	*/
	int Login();

	/** 
	* ֤ȯί��
	* �Ȼ�ȡpack��������д�����ٷ���ί�У��õ�Ӧ���Ժ��ٽ����
	* @param iSystemNo ϵͳ�ڵ�ţ�
	*				����UF2.0����ϵͳ����Ҫ���ݵ�¼����331100���ص��ֶ�sysnode_id������iSystemNo��
	* @return 0: �ɹ�, ����ʧ��!
	*/
	int SecuEntrust(int iSystemNo = 2);

	/** 
	* ֤ȯί�в�ѯ
	* �Ȼ�ȡpack��������д�����ٷ���ί�У��õ�Ӧ���Ժ��ٽ����
	* @param iSystemNo ϵͳ�ڵ�ţ�
	*				����UF2.0����ϵͳ����Ҫ���ݵ�¼����331100���ص��ֶ�sysnode_id������iSystemNo��
	* @return 0: �ɹ�, ����ʧ��!
	*/
	//int SearchSecuEntrust(int iSystemNo = 2);

		/** 
	* ֤ȯί�г���
	* �Ȼ�ȡpack��������д�����ٷ���ί�У��õ�Ӧ���Ժ��ٽ����
	* @param iSystemNo ϵͳ�ڵ�ţ�
	*				����UF2.0����ϵͳ����Ҫ���ݵ�¼����331100���ص��ֶ�sysnode_id������iSystemNo��
	* @return 0: �ɹ�, ����ʧ��!
	*/
	//int SecuEntrustWithdraw(int iSystemNo = 2);

	/** 
	* ֤ȯ�ɽ���ѯ
	* �Ȼ�ȡpack��������д�����ٷ���ί�У��õ�Ӧ���Ժ��ٽ����
	* @param iSystemNo ϵͳ�ڵ�ţ�
	*				����UF2.0����ϵͳ����Ҫ���ݵ�¼����331100���ص��ֶ�sysnode_id������iSystemNo��
	* @return 0: �ɹ�, ����ʧ��!
	*/

	//int SecuRealtimeQry(int iSystemNo  = 2 );


	int CBusiness::SecuStockQry(int iSystemNo  = 2 );

	int CBusiness::ClientFundAllQry(int iSystemNo = 2 );


	int CBusiness::ClientStkacctQry(int iSystemNo = 2 );

    int funcSubscribePush(int nFUnctionNo, int nIssueType);
	
private:
	CConfigInterface *m_pConfig;
	char m_cUserToken[USERTOKENLEN];
	int m_branch_no;
	char m_client_id[USERTOKENLEN];
	char m_fund_account[USERTOKENLEN];
	
};

//////////////////////////////////////////////////////////////////////
//Callback
class CCallback : public CCallbackInterface
{
public:
    // ��ΪCCallbackInterface�����մ��������IKnown��������Ҫʵ��һ����3������
    unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv);
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();
	
    // �����¼�����ʱ�Ļص�������ʵ��ʹ��ʱ���Ը�����Ҫ��ѡ��ʵ�֣����ڲ���Ҫ���¼��ص���������ֱ��return
    // Reserved?Ϊ����������Ϊ�Ժ���չ��׼����ʵ��ʱ��ֱ��return��return 0��
    void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData);
    void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d);
    void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d);
    int  FUNCTION_CALL_MODE Reserved3();
    void FUNCTION_CALL_MODE Reserved4();
    void FUNCTION_CALL_MODE Reserved5();
    void FUNCTION_CALL_MODE Reserved6();
    void FUNCTION_CALL_MODE Reserved7();
    void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult);
		void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult);
		void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg);
};
#endif