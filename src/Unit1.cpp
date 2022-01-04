//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString version_str="v20220103a";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StatusBar1Resize(TObject *Sender)
{
	int temp_remain_width=StatusBar1->Width;
	//--
	// ���t�m�̫�@��A�Ʊ�O150
	StatusBar1->Panels->Items[4]->Width=150;
	// �p��Ѿl�Ŷ�
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[4]->Width;
	//--
	// �t�m�j���@��A�Ʊ�O100
	StatusBar1->Panels->Items[3]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[3]->Width)
	{
		StatusBar1->Panels->Items[3]->Width=temp_remain_width;
	}
	// �p��Ѿl�Ŷ�
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[3]->Width;
	//--
	// �t�m�j���@��A�Ʊ�O100
	StatusBar1->Panels->Items[2]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[2]->Width)
	{
		StatusBar1->Panels->Items[2]->Width=temp_remain_width;
	}
	// �p��Ѿl�Ŷ�
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[2]->Width;
	//--
	//  �t�m�j���@��A�Ʊ�O100
	StatusBar1->Panels->Items[1]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[1]->Width)
	{
		StatusBar1->Panels->Items[1]->Width=temp_remain_width;
	}
	// �p��Ѿl�Ŷ�
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[1]->Width;
	//--
	// �̫e��@��ɨ��̤j�Ŷ�
	StatusBar1->Panels->Items[0]->Width=temp_remain_width;
	//--
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	AnsiString temp_str=FormatDateTime("yyyy-mm-dd HH:MM:SS" ,Now());
	StatusBar1->Panels->Items[4]->Text=temp_str;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MainMenu1_1_1Click(TObject *Sender)
{
	AnsiString temp_str="�@��: HsiuPoYeh.\n�{������: "+version_str;
	Application->MessageBox(UnicodeString(temp_str).c_str(),L"�����",64);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::APIURL_EditChange(TObject *Sender)
{
	FullAPIURL_Edit->Text="http://"+ServerIP_Edit->Text+":"+ServerPort_Edit->Text+APIURL_Edit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerPort_EditChange(TObject *Sender)
{
	FullAPIURL_Edit->Text="http://"+ServerIP_Edit->Text+":"+ServerPort_Edit->Text+APIURL_Edit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerRunStop_ButtonClick(TObject *Sender)
{
	if (IdHTTPServer1->Active==false)
	{
		// �վ�UI
		ServerPort_Edit->Enabled=false;
		APIURL_Edit->Enabled=false;

		// �]�wServer Port
		IdHTTPServer1->DefaultPort=ServerPort_Edit->Text.ToInt();
		// ���ܰT��
		Log_Memo->Lines->Add("�Ұ�Server...");
		// �Ұ�Server
		IdHTTPServer1->Active=true;
		// �վ���s��r
		ServerRunStop_Button->Caption="���ڰ���";
		// �վ㪬�A��r
		ServerStatus_Label->Caption="���A�����A:  �B�椤";
		// �վ㪬�A�C��T
		StatusBar1->Panels->Items[1]->Text="Server�B�椤...";
	}
	else
	{
		// ����Server
		IdHTTPServer1->Active=false;
		// ���ܰT��
		Log_Memo->Lines->Add("����Server...");
		// �վ���s��r
		ServerRunStop_Button->Caption="���ڱҰ�";
		// �վ㪬�A��r
		ServerStatus_Label->Caption="���A�����A:  ����";
		// �վ㪬�A�C��T
		StatusBar1->Panels->Items[1]->Text="Server����...";

		// �վ�UI
		ServerPort_Edit->Enabled=true;
		APIURL_Edit->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IdHTTPServer1CommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo)
{
	UnicodeString api_return_json_str;
	//--------------------------------------------------------------------------
	Log_Memo->Lines->Add("==============================");
	Log_Memo->Lines->Add(FormatDateTime("yyyy-mm-dd HH:MM:SS" ,Now()));
	Log_Memo->Lines->Add("IdHTTPServer1CommandGet:");
	Log_Memo->Lines->Add("RawHTTPCommand: "+ARequestInfo->RawHTTPCommand);
	Log_Memo->Lines->Add("Command: "+ARequestInfo->Command);
	Log_Memo->Lines->Add("URI: "+ARequestInfo->URI);
	Log_Memo->Lines->Add("RemoteIP: "+ARequestInfo->RemoteIP);
	Log_Memo->Lines->Add("--");
	//--------------------------------------------------------------------------
	// ²�檺API�^���]�p
	//--
	// �u�^���H�U����:
	// 1. GET ��k
	// 2. API�R�W
	//--
	// �^���覡:
	//���\�ɦ^��JSON���:
	//{
	//"status": "success",
	//"data": { ... },
	//"message": null
	//}
	// ���~�ɦ^��JSON���:
	//{
	//"status": "error",
	//"data": null,
	//"message": "Error xxx has occurred"
	//}
	//--
    // ��ڪ��p:
	// ���\�ɦ^��JSON���:
	// {"status":"success","data": "Hello!","message": null}
	// ���~�ɦ^��JSON���:
	// {"status":"error","data":null,"message": "���~!�u����GET��k!"}
	// {"status":"error","data":null,"message": "���~!���X�k��API!"}
	//--------------------------------------------------------------------------
	// 1. GET ��k
	if (ARequestInfo->Command.CompareIC("GET")==0)//�R�O�OGET��k��
	{
		//���������
	}
	else
	{
		api_return_json_str=
			String(L"{")+
				String(L"\"")+L"status"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"error"+String(L"\"")+
			String(L",")+
				String(L"\"")+L"data"+String(L"\"")+
				String(L":")+
				L"null"+
			String(L",")+
				String(L"\"")+L"message"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"Error!���~!�u����GET��k!"+String(L"\"")+
			String(L"}");
		Log_Memo->Lines->Add("api_return_json_str:");
		Log_Memo->Lines->Add(api_return_json_str);
		AResponseInfo->ContentType="text/plain";
		AResponseInfo->CharSet="utf-8" ;
		AResponseInfo->ContentText=api_return_json_str;
		Log_Memo->Lines->Add("==============================");
		return;
	}
	//--------------------------------------------------------------------------
	// 2.1. API�R�W: /api/v1/hello
	if (ARequestInfo->URI.Compare(APIURL_Edit->Text)==0)//API���T��
	{
		api_return_json_str=
			String(L"{")+
				String(L"\"")+L"status"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"success"+String(L"\"")+
			String(L",")+
				String(L"\"")+L"data"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"Hello!"+String(L"\"")+
			String(L",")+
				String(L"\"")+L"message"+String(L"\"")+
				String(L":")+
				L"null"+
			String(L"}");
		Log_Memo->Lines->Add("api_return_json_str:");
		Log_Memo->Lines->Add(api_return_json_str);
		AResponseInfo->ContentType="text/plain";
		AResponseInfo->CharSet="utf-8" ;
		AResponseInfo->ContentText=api_return_json_str;
	}
	else
	{
		api_return_json_str=
			String(L"{")+
				String(L"\"")+L"status"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"error"+String(L"\"")+
			String(L",")+
				String(L"\"")+L"data"+String(L"\"")+
				String(L":")+
				L"null"+
			String(L",")+
				String(L"\"")+L"message"+String(L"\"")+
				String(L":")+
				String(L"\"")+L"���~!���X�k��API!"+String(L"\"")+
			String(L"}");
		Log_Memo->Lines->Add("api_return_json_str:");
		Log_Memo->Lines->Add(api_return_json_str);
		AResponseInfo->ContentType="text/plain";
		AResponseInfo->CharSet="utf-8" ;
		AResponseInfo->ContentText=api_return_json_str;
		Log_Memo->Lines->Add("==============================");
		return;
	}
	Log_Memo->Lines->Add("==============================");
    return;
}
//---------------------------------------------------------------------------


