object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Web API '#20282#26381#22120' '#31684#20363'01'
  ClientHeight = 562
  ClientWidth = 784
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 543
    Width = 784
    Height = 19
    Panels = <
      item
        Width = 120
      end
      item
        Width = 120
      end
      item
        Width = 120
      end
      item
        Width = 120
      end
      item
        Width = 120
      end>
    OnResize = StatusBar1Resize
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 784
    Height = 543
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet3: TTabSheet
      Caption = 'Web Server'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ImageIndex = 2
      ParentFont = False
      object TS3_Panel1: TPanel
        Left = 0
        Top = 0
        Width = 776
        Height = 153
        Align = alTop
        TabOrder = 0
        object TS3_Panel1_Left: TPanel
          Left = 1
          Top = 11
          Width = 10
          Height = 131
          Align = alLeft
          BevelOuter = bvNone
          TabOrder = 0
          ExplicitTop = 1
          ExplicitHeight = 151
        end
        object TS3_Panel1_Right: TPanel
          Left = 765
          Top = 11
          Width = 10
          Height = 131
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 1
          ExplicitLeft = 590
          ExplicitTop = 1
          ExplicitHeight = 151
        end
        object TS3_Panel1_Top: TPanel
          Left = 1
          Top = 1
          Width = 774
          Height = 10
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 2
        end
        object TS3_Panel1_Bottom: TPanel
          Left = 1
          Top = 142
          Width = 774
          Height = 10
          Align = alBottom
          BevelOuter = bvNone
          TabOrder = 3
          ExplicitTop = 147
        end
        object TS3_Panel1_Client: TPanel
          Left = 11
          Top = 11
          Width = 754
          Height = 131
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 4
          ExplicitLeft = 352
          ExplicitTop = 112
          ExplicitWidth = 185
          ExplicitHeight = 41
          object TS3_Panel1_Client_Left: TPanel
            Left = 0
            Top = 0
            Width = 330
            Height = 131
            Align = alLeft
            BevelOuter = bvNone
            TabOrder = 0
            ExplicitLeft = 1
            ExplicitTop = 1
            ExplicitHeight = 129
            object GroupBox1: TGroupBox
              Left = 0
              Top = 0
              Width = 150
              Height = 60
              Caption = 'Server IP Address:'
              TabOrder = 0
              object ServerIP_Edit: TEdit
                Left = 13
                Top = 26
                Width = 121
                Height = 21
                Enabled = False
                TabOrder = 0
                Text = '127.0.0.1'
              end
            end
            object GroupBox2: TGroupBox
              Left = -1
              Top = 60
              Width = 150
              Height = 60
              Caption = 'Server Port:'
              TabOrder = 1
              object ServerPort_Edit: TEdit
                Left = 16
                Top = 24
                Width = 121
                Height = 21
                TabOrder = 0
                Text = '18000'
                OnChange = ServerPort_EditChange
              end
            end
            object GroupBox3: TGroupBox
              Left = 165
              Top = 0
              Width = 150
              Height = 60
              Caption = 'Server Status:'
              TabOrder = 2
              object ServerStatus_Label: TLabel
                Left = 16
                Top = 28
                Width = 94
                Height = 13
                Caption = #20282#26381#22120#29376#24907':  '#20572#27490
              end
            end
            object ServerRunStop_Button: TButton
              Left = 185
              Top = 68
              Width = 113
              Height = 46
              Caption = #25353#25105#21855#21205
              TabOrder = 3
              OnClick = ServerRunStop_ButtonClick
            end
          end
          object TS3_Panel1_Client_Client: TPanel
            Left = 330
            Top = 0
            Width = 424
            Height = 131
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 1
            ExplicitLeft = 344
            ExplicitTop = 56
            ExplicitWidth = 185
            ExplicitHeight = 41
            object GroupBox4: TGroupBox
              Left = 0
              Top = 0
              Width = 424
              Height = 131
              Align = alClient
              Caption = 'API URL:'
              TabOrder = 0
              ExplicitLeft = 37
              ExplicitTop = -7
              ExplicitWidth = 385
              ExplicitHeight = 136
              object Panel1: TPanel
                Left = 2
                Top = 23
                Width = 10
                Height = 106
                Align = alLeft
                BevelOuter = bvNone
                TabOrder = 0
                ExplicitTop = 4
                ExplicitHeight = 121
              end
              object Panel3: TPanel
                Left = 2
                Top = 15
                Width = 420
                Height = 8
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                ExplicitLeft = 3
                ExplicitTop = 10
                ExplicitWidth = 416
              end
              object Panel4: TPanel
                Left = 12
                Top = 23
                Width = 400
                Height = 106
                Align = alClient
                BevelOuter = bvNone
                TabOrder = 2
                ExplicitLeft = 328
                ExplicitTop = 64
                ExplicitWidth = 185
                ExplicitHeight = 41
                object Panel5: TPanel
                  Left = 0
                  Top = 21
                  Width = 400
                  Height = 15
                  Align = alTop
                  BevelOuter = bvNone
                  TabOrder = 0
                  ExplicitLeft = 1
                  ExplicitTop = 22
                  ExplicitWidth = 394
                end
                object Panel6: TPanel
                  Left = 0
                  Top = 36
                  Width = 400
                  Height = 70
                  Align = alClient
                  BevelOuter = bvNone
                  TabOrder = 1
                  ExplicitLeft = 168
                  ExplicitTop = 72
                  ExplicitWidth = 185
                  ExplicitHeight = 41
                  object Label2: TLabel
                    Left = 0
                    Top = 0
                    Width = 400
                    Height = 13
                    Align = alTop
                    Caption = #23436#25972#32178#22336':'
                    ExplicitLeft = 5
                    ExplicitTop = 6
                    ExplicitWidth = 52
                  end
                  object Panel7: TPanel
                    Left = 0
                    Top = 23
                    Width = 400
                    Height = 47
                    Align = alClient
                    BevelOuter = bvNone
                    TabOrder = 0
                    ExplicitLeft = 104
                    ExplicitTop = 48
                    ExplicitWidth = 185
                    ExplicitHeight = 41
                    object FullAPIURL_Edit: TEdit
                      Left = 0
                      Top = 0
                      Width = 400
                      Height = 21
                      Align = alTop
                      ReadOnly = True
                      TabOrder = 0
                      Text = 'http://127.0.0.1:18000/api/v1/hello'
                      ExplicitLeft = 1
                      ExplicitTop = 1
                      ExplicitWidth = 398
                    end
                  end
                  object Panel2: TPanel
                    Left = 0
                    Top = 13
                    Width = 400
                    Height = 10
                    Align = alTop
                    BevelOuter = bvNone
                    TabOrder = 1
                    ExplicitLeft = 1
                    ExplicitTop = 22
                  end
                end
                object APIURL_Edit: TEdit
                  Left = 0
                  Top = 0
                  Width = 400
                  Height = 21
                  Align = alTop
                  TabOrder = 2
                  Text = '/api/v1/hello'
                  OnChange = APIURL_EditChange
                  ExplicitLeft = 1
                  ExplicitTop = 1
                  ExplicitWidth = 183
                end
              end
              object Panel8: TPanel
                Left = 412
                Top = 23
                Width = 10
                Height = 106
                Align = alRight
                BevelOuter = bvNone
                TabOrder = 3
                ExplicitLeft = 237
              end
            end
          end
        end
      end
      object TS3_Panel2: TPanel
        Left = 0
        Top = 153
        Width = 776
        Height = 362
        Align = alClient
        Caption = 'TS3_Panel2'
        TabOrder = 1
        ExplicitTop = 151
        object TS3_Panel2_Bottom: TPanel
          Left = 1
          Top = 351
          Width = 774
          Height = 10
          Align = alBottom
          BevelOuter = bvNone
          TabOrder = 0
          ExplicitTop = 320
        end
        object TS3_Panel2_Client: TPanel
          Left = 11
          Top = 11
          Width = 754
          Height = 340
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          ExplicitLeft = 512
          ExplicitTop = 56
          ExplicitWidth = 185
          ExplicitHeight = 41
          object Label3: TLabel
            Left = 0
            Top = 0
            Width = 754
            Height = 13
            Align = alTop
            Caption = 'API'#35498#26126':'
            ExplicitLeft = 24
            ExplicitTop = 32
            ExplicitWidth = 45
          end
          object Memo1: TMemo
            Left = 0
            Top = 18
            Width = 754
            Height = 322
            Align = alClient
            Lines.Strings = (
              #35373#35336#21407#21063':'
              #25104#21151#26178#22238#20659'JSON'#36039#26009':'
              '{'
              '"status": "success",'
              '"data": { ... },'
              '"message": null'
              '}'
              #37679#35492#26178#22238#20659'JSON'#36039#26009':'
              '{'
              '"status": "error",'
              '"data": null,'
              '"message": "Error xxx has occurred"'
              '}'
              ''
              #23526#38555#29376#27841':'
              #25104#21151#26178#22238#20659'JSON'#36039#26009':'
              '{"status":"success","data": "Hello!","message": null}'
              #37679#35492#26178#22238#20659'JSON'#36039#26009':'
              '{"status":"error","data":null,"message": "'#37679#35492'!'#21482#25509#21463'GET'#26041#27861'!"}'
              '{"status":"error","data":null,"message": "'#37679#35492'!'#19981#21512#27861#30340'API!"}')
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
            ExplicitLeft = 17
            ExplicitTop = 29
            ExplicitWidth = 737
            ExplicitHeight = 297
          end
          object Panel9: TPanel
            Left = 0
            Top = 13
            Width = 754
            Height = 5
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 1
            ExplicitLeft = 1
            ExplicitTop = 14
            ExplicitWidth = 752
          end
        end
        object TS3_Panel2_Right: TPanel
          Left = 765
          Top = 11
          Width = 10
          Height = 340
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 2
          ExplicitLeft = 590
        end
        object TS3_Panel2_Left: TPanel
          Left = 1
          Top = 11
          Width = 10
          Height = 340
          Align = alLeft
          BevelOuter = bvNone
          TabOrder = 3
        end
        object TS3_Panel2_Top: TPanel
          Left = 1
          Top = 1
          Width = 774
          Height = 10
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 4
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = #36939#34892#32000#37636
      object Log_Memo: TMemo
        Left = 0
        Top = 0
        Width = 776
        Height = 515
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
      object CammaText_Memo: TMemo
        Left = 400
        Top = 160
        Width = 185
        Height = 89
        Lines.Strings = (
          'CammaText_Memo')
        TabOrder = 1
        Visible = False
      end
    end
    object TabSheet2: TTabSheet
      Caption = #26356#26032#32000#37636
      ImageIndex = 1
      object Update_Memo: TMemo
        Left = 0
        Top = 0
        Width = 776
        Height = 515
        Align = alClient
        Lines.Strings = (
          'v20220103:'
          #21021#29256#12290)
        TabOrder = 0
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 16
    Top = 496
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 496
    object MainMenu1_1: TMenuItem
      Caption = #35498#26126'(&H)'
      object MainMenu1_1_1: TMenuItem
        Caption = #38364#26044#25105'(&A)'
        OnClick = MainMenu1_1_1Click
      end
    end
  end
  object IdHTTPServer1: TIdHTTPServer
    Bindings = <>
    OnCommandGet = IdHTTPServer1CommandGet
    Left = 92
    Top = 496
  end
end
