//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <IdContext.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TTimer *Timer1;
	TMainMenu *MainMenu1;
	TMenuItem *MainMenu1_1;
	TMenuItem *MainMenu1_1_1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TMemo *Log_Memo;
	TMemo *CammaText_Memo;
	TMemo *Update_Memo;
	TGroupBox *GroupBox1;
	TEdit *ServerIP_Edit;
	TGroupBox *GroupBox2;
	TEdit *ServerPort_Edit;
	TGroupBox *GroupBox3;
	TLabel *ServerStatus_Label;
	TButton *ServerRunStop_Button;
	TGroupBox *GroupBox4;
	TEdit *APIURL_Edit;
	TLabel *Label2;
	TEdit *FullAPIURL_Edit;
	TMemo *Memo1;
	TLabel *Label3;
	TIdHTTPServer *IdHTTPServer1;
	TPanel *TS3_Panel1;
	TPanel *TS3_Panel2;
	TPanel *TS3_Panel1_Left;
	TPanel *TS3_Panel1_Right;
	TPanel *TS3_Panel1_Top;
	TPanel *TS3_Panel1_Bottom;
	TPanel *TS3_Panel1_Client;
	TPanel *TS3_Panel1_Client_Left;
	TPanel *TS3_Panel1_Client_Client;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *TS3_Panel2_Bottom;
	TPanel *TS3_Panel2_Client;
	TPanel *TS3_Panel2_Right;
	TPanel *TS3_Panel2_Left;
	TPanel *TS3_Panel2_Top;
	TPanel *Panel9;
	void __fastcall StatusBar1Resize(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall MainMenu1_1_1Click(TObject *Sender);
	void __fastcall APIURL_EditChange(TObject *Sender);
	void __fastcall ServerPort_EditChange(TObject *Sender);
	void __fastcall ServerRunStop_ButtonClick(TObject *Sender);
	void __fastcall IdHTTPServer1CommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
