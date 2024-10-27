unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  IdHTTP;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Edit1: TEdit;
    IdHTTP1: TIdHTTP;
    Memo1: TMemo;
    Panel1: TPanel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
var
  myHTTPResponseStream : TStringStream;
  myHTTPResponseStr : string;
  myHTTPErrorStr : string;
begin
  myHTTPResponseStream:=TStringStream.Create('', TEncoding.UTF8);
  myHTTPResponseStr:='';
  myHTTPErrorStr:='';
  IdHTTP1.ConnectTimeout:=2000;
  try
    IdHTTP1.Get(Edit1.Text,myHTTPResponseStream);
  except
    on E: Exception do
      begin
        myHTTPErrorStr:=E.Message;
      end
  end;
  if myHTTPErrorStr.Length>0 Then begin
    Memo1.Lines.Add('--');
    Memo1.Lines.Add('連線異常，原因:');
    Memo1.Lines.Add(myHTTPErrorStr);
    Memo1.Lines.Add('--');
  end
  else begin
    myHTTPResponseStr := myHTTPResponseStream.DataString;
    Memo1.Lines.Add(myHTTPResponseStr);
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Memo1.Clear;
end;

end.

