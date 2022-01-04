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
	// 先配置最後一格，希望是150
	StatusBar1->Panels->Items[4]->Width=150;
	// 計算剩餘空間
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[4]->Width;
	//--
	// 配置隔壁一格，希望是100
	StatusBar1->Panels->Items[3]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[3]->Width)
	{
		StatusBar1->Panels->Items[3]->Width=temp_remain_width;
	}
	// 計算剩餘空間
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[3]->Width;
	//--
	// 配置隔壁一格，希望是100
	StatusBar1->Panels->Items[2]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[2]->Width)
	{
		StatusBar1->Panels->Items[2]->Width=temp_remain_width;
	}
	// 計算剩餘空間
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[2]->Width;
	//--
	//  配置隔壁一格，希望是100
	StatusBar1->Panels->Items[1]->Width=100;
	if (temp_remain_width<StatusBar1->Panels->Items[1]->Width)
	{
		StatusBar1->Panels->Items[1]->Width=temp_remain_width;
	}
	// 計算剩餘空間
	temp_remain_width=temp_remain_width-StatusBar1->Panels->Items[1]->Width;
	//--
	// 最前方一格享受最大空間
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
	AnsiString temp_str="作者: HsiuPoYeh.\n程式版本: "+version_str;
	Application->MessageBox(UnicodeString(temp_str).c_str(),L"關於我",64);
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
		// 調整UI
		ServerPort_Edit->Enabled=false;
		APIURL_Edit->Enabled=false;

		// 設定Server Port
		IdHTTPServer1->DefaultPort=ServerPort_Edit->Text.ToInt();
		// 提示訊息
		Log_Memo->Lines->Add("啟動Server...");
		// 啟動Server
		IdHTTPServer1->Active=true;
		// 調整按鈕文字
		ServerRunStop_Button->Caption="按我停止";
		// 調整狀態文字
		ServerStatus_Label->Caption="伺服器狀態:  運行中";
		// 調整狀態列資訊
		StatusBar1->Panels->Items[1]->Text="Server運行中...";
	}
	else
	{
		// 停止Server
		IdHTTPServer1->Active=false;
		// 提示訊息
		Log_Memo->Lines->Add("關閉Server...");
		// 調整按鈕文字
		ServerRunStop_Button->Caption="按我啟動";
		// 調整狀態文字
		ServerStatus_Label->Caption="伺服器狀態:  停止";
		// 調整狀態列資訊
		StatusBar1->Panels->Items[1]->Text="Server停止...";

		// 調整UI
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
	// 簡單的API回應設計
	//--
	// 只回應以下條件:
	// 1. GET 方法
	// 2. API命名
	//--
	// 回應方式:
	//成功時回傳JSON資料:
	//{
	//"status": "success",
	//"data": { ... },
	//"message": null
	//}
	// 錯誤時回傳JSON資料:
	//{
	//"status": "error",
	//"data": null,
	//"message": "Error xxx has occurred"
	//}
	//--
    // 實際狀況:
	// 成功時回傳JSON資料:
	// {"status":"success","data": "Hello!","message": null}
	// 錯誤時回傳JSON資料:
	// {"status":"error","data":null,"message": "錯誤!只接受GET方法!"}
	// {"status":"error","data":null,"message": "錯誤!不合法的API!"}
	//--------------------------------------------------------------------------
	// 1. GET 方法
	if (ARequestInfo->Command.CompareIC("GET")==0)//命令是GET方法時
	{
		//不做任何事
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
				String(L"\"")+L"Error!錯誤!只接受GET方法!"+String(L"\"")+
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
	// 2.1. API命名: /api/v1/hello
	if (ARequestInfo->URI.Compare(APIURL_Edit->Text)==0)//API正確時
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
				String(L"\"")+L"錯誤!不合法的API!"+String(L"\"")+
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


