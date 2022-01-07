# Web-API-Server-Example-01
Web API 伺服器 範例01

![image](https://github.com/HsiupoYeh/Web-API-Server-Example-01/blob/main/ScreenShot/ScreenShot_001.png)  

## 開發環境:
- Windows 7 SP1 64bit 繁體中文版
- Embarcadero® C++Builder 10.2 Version 25.0.28979.1978

## 運行需求:
- Windosw作業系統。
- 可運行32位元應用程式。
- 允許程式通過防火牆。

## 注意事項:
- 本專案有使用IdHTTPServer元件。其中OnCommandGet方法是以多執行緒處理，在C++Builder的VCL中並不是執行緒安全的(thread-safe)，主要是指主執行緒控制的UI元件隨時可被其他執行緒操作，但是不保證同時只有一個執行緒操作這個元件，最終可能造成程式發生不可預期的錯誤。因此，可以使用Indy提供的「TIdSync」和「TIdNotify」的類別(class)，將操作UI的工作包裝為同步或非同步的工作，委託給主執行緒執行，以達到執行緒安全的設計。片段範例程式碼如下:
    ```cpp
    //--------------------------------------------------------------------------
    // 使用Indy提供的「TIdSync」和「TIdNotify」的類別(class)必須自行引入標頭檔案
    #include <IdSync.hpp>
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    // TIdSync類別的特色是同步處理(阻塞式)，會將工作交給主執行緒，等待主執行緒完成後才返回控制權。
    class TAddMemo1Sync : public TIdSync
    {
    	protected:
    		String str;
    		void __fastcall DoSynchronize()
    		{
    			Form1->Memo1->Lines->Add(str);
    		}
    	public:
    		__fastcall TAddMemo1Sync(const String &s) : TIdSync(), str(s) {}
    		static void DoIt(const String &s)
    		{
    			TAddMemo1Sync *sync = new TAddMemo1Sync(s);
    			sync->Synchronize();
    			delete sync;
    		}
    };
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    // TIdNotify類別的特色是非同步處理(非阻塞式)，會將工作放到主執行緒排程，立刻返回控制權。
    class TAddMemo1Notify : public TIdNotify
    {
    	protected:
    		String str;
    		void __fastcall DoNotify()
    		{
    			Form1->Memo1->Lines->Add(str);
    		}
    	public:
    		__fastcall TAddMemo1Notify(const String &s) : TIdNotify(), str(s) {}
    		static void DoIt(const String &s)
    		{
    			TAddMemo1Notify *notify = new TAddMemo1Notify(s);
    			notify->Notify();
    			delete notify;
    		}
    };
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------   
    void __fastcall TForm1::IdHTTPServer1CommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo)
    {
        //阻塞式呼叫 
        TAddMemo1Sync::DoIt("some text...");
        
        //非阻塞式呼叫 
        TAddMemo1Notify::DoIt("some text...");
    }
    //--------------------------------------------------------------------------
    ```
- IdHTTPServer元件的IdHTTPServer1CommandGet方法:
    ```cpp
    //--
    ARequestInfo->RawHTTPCommand //HTTP連線中原始文字資料，例如:「GET /api/v1/hello?a=1&b=3 HTTP/1.0」
    ARequestInfo->Command // HTTP方法，例如:「GET」
    ARequestInfo->URI // 伺服器端網址，例如:「/api/v1/hello」
    ARequestInfo->RemoteIP // 用戶端IP，例如:「192.168.0.1」
    //--
    ARequestInfo->QueryParams //查詢參數文字資料，例如「a=1&b=3」
    ARequestInfo->Params->Values["a"] //參數a的字串值
    ARequestInfo->Params->Values["a"].IsEmpty() //參數a的字串是否為空
    
    ```
## 開發紀錄:
1. 選擇32bit版本開發(因為目前沒用到64bit才能執行的功能，記憶體需求也不大)。
    + **1.1 按下「New->VCL Forms Application - C++ Builder」。並確認「Target Platforms」是「Win32」。**
2. 獨立把專案存到指定資料夾中，以利日後管理。大部分自訂程式碼都會是相對路徑，未來只需要帶走這個資料夾即可在其他地方重新使用。
    + **2.1 按下「File->Save Project As」。**
3. 專案有許多常用設定需要調整，可使專案產生獨立執行檔、編譯器選擇、程式碼自動完成與提示等等。
    + **3.1 按下「Project->Options」，進行以下操作:**
    + **3.1.1 檢查「C++ (Shared Options)」頁面下「_TCHAR map to」為「wchar_t」。**
3.1.1.1 說明:「wchar_t」表示使用「UNICODE」。「char」表示使用「ANSI」。非英文語系的程式建議都選UNICODE。
    + **3.1.2 檢查「C++ Compiler」頁面下「Classic Compiler->Use 'classic' Borland compiler」為「true」。**
    + 3.1.2.1 說明:僅有32位元平台有此設定。「true」表示使用「Borland編譯器」，不支援C++ 11。選「false」表示使用「clang編譯器」，支援C++ 11以上(不確定最新支援到哪)，但可能會導致程式碼自動完成與提示功能異常。
    + **3.1.3 設定「C++ Linker」頁面下「Link with Dynamic RTL」為「false」。**
    + 3.1.3.1 說明: 表示把功能都編譯到程式中，執行時不需要外部dll就可獨立運行。
    + **3.1.4 設定「Application」頁面下利用「Load Icon 」按鈕更換自訂圖示。**
    + 3.1.4.1 說明: 程式圖示。
    + **3.1.5 檢查「Application」頁面下「Execution Level 」為「As Invoker」。**
    + 3.1.5.1 說明: 「As Invoker、Highest Available」都是普通權限就可以執行，「requireAdministrator」是執行前請求獲得管理者權限才能執行。
    + **3.1.6 設定「Application->Appearance」頁面下「Application settings->Title 」為「Web API 伺服器 範例01」。**
    + 3.1.6.1 說明: 此參數是專屬本應用程式的欄位，可做為找到此程式的依據之一，常見可以在運行程式前先檢查是否有相同Title的程式正在執行，以達到禁止重複運行的功能。
    + **3.1.7 設定「Packages->Runtime Packages」頁面下「Link with runtime packages」為「false」。**
    + 3.1.7.1 說明: 表示把元件都編譯到程式中，執行時不需要外部bpl及dll就可以獨立運行。
4. 編輯工具有部分設定可以協助撰寫程式碼，不過非必要。
    + **4.1 按下「Tools->Options」，進行以下操作:**
    + **4.1.1 設定「Formatter->C++->Line breaks」頁面下「Line breaks for braces->Line break before open brace」為「Yes」。**
    + 4.1.1.1 說明: 左大括號前面是否換行，預設是不換行比較精簡，但我喜歡換行，比較好讀。

    >以上都是比較基礎的設定，與程式設計無關，每個專案開始都類似，照做即可。接下來則是開始進行設計:

5. 預設狀況下就有一個Form元件存在，預設名稱叫做「Form1」，先做一些基礎設定以利後續排版。
    + 5.1 設定「Form1」的「properties」。這裡主要列出常用的一些。
    + **5.1.1 檢查「Form1」的「properties」頁面下「BorderIcon」為「[biSystemMenu,biMinimize,biMaximize]」。**
    + 5.1.1.1 說明:設定窗體右上角的按鈕如果存在的話要不要被啟用。「[biSystemMenu,biMinimize,biMaximize]」表示這三個被打勾。
    + **5.1.2 檢查「Form1」的「properties」頁面下「BorderStyle」為「bsSizeable」。**
    + 5.1.2.1 說明:設定窗體的樣式。可依需求嘗試不同風格決定是否符合需求。
    + **5.1.2 設定「Form1」的「properties」頁面下「Caption」為「Web API 伺服器 範例01」。**
    + 5.1.2.1 說明:設定窗體的標題列文字。
    + **5.1.3 設定「Form1」的「properties」頁面下「Color」為「clWindow」。**
    + 5.1.3.1 說明:設定成白色使工具列元件底色是白色。
    + **5.1.4 設定「Form1」的「properties」頁面下「Height」為「600」。**
    + 5.1.4.1 說明:設定窗體的外框高度。
    + **5.1.5 設定「Form1」的「properties」頁面下「Position」為「poScreenCenter」。**
    + 5.1.5.1 說明:設定窗體的出現位置，建議是用「poScreenCenter」，在螢幕中央。
    + **5.1.6 設定「Form1」的「properties」頁面下「Width」為「800」。**
    + 5.1.6.1 說明:設定窗體的外框寬度。

    >以上預設尺寸確定後就可以開始排版。

6. 經典的Windows應用程式會在下方放置一個狀態列。如果不趕時間應該避免當作SimplePanel來使用。建議使用標準的(TStatusPanels)來規劃出多分隔的狀態列。可參考經典軟體「記事本」與「NotePad++」的狀態列規劃。
    + **6.1 拖拉一個「TStatusBar」到「Form1」中。預設名稱會是「StatusBar1」。**
    + 6.2 設定「TStatusBar」的「Properties」。這裡主要列出常用的一些。
    + **6.2.1 檢查「StatusBar1」的「Properties」頁面下「Align」為「alBottom」。**
    + 6.2.1.1 說明:設定狀態列位置緊貼窗體下方。
    + **6.2.2 設定「StatusBar1」的「Properties」頁面下「Panel」，按下「...」後會出現編輯介面。從編輯介面建立5個TStatusPanels。**
    + 6.2.2.1 說明:建立狀態列中多個小版面。
    + 6.2.3 設定各「TStatusPanels」的「Properties」。
    + **6.2.3.1 檢查「TStatusPanels」的「Properties」頁面下「Alignment」為「taLeftJustify」。**
    + 6.2.3.1.1 說明:「taLeftJustify」是文字靠左對齊，「taCenter」是文字水平置中，「taRightJustify」是文字靠右對齊。注意，如果有人改掉「BiDiMode」可能會顛倒，所以建議不要動「BiDiMode」這個屬性。
    + **6.2.3.2 檢查「TStatusPanels」的「Properties」頁面下「Style」為「psText」。**
    + 6.2.3.2.1 說明:「psText」是可寫文字，「psOwnerDraw」是用另外的函數處理非文字。
    + **6.2.3.3 設定「TStatusPanels」的「Properties」頁面下「Text」為「初始文字」。**
    + 6.2.3.3.1 說明:初始文字可以預先在排版階段測試顯示效果，其中最靠右會被吃掉字元，請依需求測試設定文字內容。
    + **6.2.3.4 設定「TStatusPanels」的「Properties」頁面下「Width」為「120」。**
    + 6.2.3.4.1 說明:可以搭配初始文字來調整Width，以利排版。預設只能靠右對齊來分配欄位，其他效果則需要利用程式碼做調整。
    + **6.2.4 設定「StatusBar1」的「Properties」頁面下「SimplePanel」為「false」。**
    + 6.2.4.1 說明:要使前面設定的TStatusPanels有效，須將「SimplePanel」設為「false」。
    + 6.3 設定「TStatusBar」的「Event」。
    + **6.3.1 設定「StatusBar1」的「Event」頁面下「OnResize」為如下程式碼。**
    ```cpp
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
    // 配置隔壁一格，希望是100
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
    ```
7. 設定時鐘
    + **7.1 拖拉一個「TTimer」到「Form1」中。預設名稱會是「Timer1」。**
    + 7.2 設定「TTimer」的「Event」。
    + **7.2.1 設定「TTimer」的「Event」頁面下「OnTimer」為如下程式碼。**
    ```cpp
    void __fastcall TForm1::Timer1Timer(TObject *Sender)
    {
    AnsiString temp_str=FormatDateTime("yyyy-mm-dd HH:MM:SS" ,Now());
    StatusBar1->Panels->Items[4]->Text=temp_str;
    }
    ```
8. 設計主選單
    + **8.1 拖拉一個「TMainMenu」到「Form1」中。預設名稱會是「MainMenu1」。**
    + **8.2 點兩下元件，進入編輯模式，建立第一層第一個選單「說明(&H)」，「Caption」設為「說明(&H)」，「Name」設為「MainMenu1_1」。**
    + **8.3 繼續建立子選單「說明(&H)->關於我(&A)」，「Caption」設為「關於我(&A)」，「Name」設為「MainMenu1_1_1」。**
    + 8.3.1 設定「MainMenu1_1_1」的「Event」。
    + **8.3.1.1 原始碼最前面部分先宣告為如下程式碼。**
    ```cpp
    AnsiString version_str="v20220103a";
    ```
    **8.3.1.2 設定「MainMenu1_1_1」的「Event」頁面下「OnClick」為如下程式碼。**
    ```cpp
    void __fastcall TForm1::MainMenu1_1_1Click(TObject *Sender)
    {
    AnsiString temp_str="作者: HsiuPoYeh.\n程式版本: "+version_str;
    Application->MessageBox(UnicodeString(temp_str).c_str(),L"關於我",64);
    }
    ```
9. 設定分頁
    + **9.1 拖拉一個「TPageControl」到「Form1」中。預設名稱會是「PageControl1」。**
    + **9.2 設定「PageControl1」的「Properties」頁面下「Align」選為「alClient」。**
    + **9.3 用右鍵新增頁面，可以先新增個10頁之後再刪掉不要用的。**

    >以上頁面未來都可以調整順序。

    + **9.4.把新增的第1頁「TabPage1」的「Properties」頁面下「Caption」設定為「運行紀錄」。**
    + **9.4.1 放上一個TMemo。設定「Properties」頁面下「Name」設定為「Log_Memo」。**
    + **9.4.1.1 設定「Log_Memo」的「Properties」頁面下「Align」設定為「AlClient」。**
    + **9.4.1.2 設定「Log_Memo」的「Properties」頁面下「Lines」的內容清空。**
    + **9.4.1.3 設定「Log_Memo」的「Properties」頁面下「ReadOnly」設定為「true」。**
    + **9.4.1.3 設定「Log_Memo」的「Properties」頁面下「ScrollBars」設定為「ssBoth」。**
    + **9.4.2 放上一個TMemo。設定「Properties」頁面下「Name」設定為「CammaText_Memo」。**
    + **9.4.2.1 設定「CammaText_Memo」的「Properties」頁面下「Visible」設定為「false」。**
    + **9.4.2.2 「CammaText_Memo」位置和尺寸隨意放，開發時期看得清楚就好。**
    
     >以上是第1頁。
    
    + **9.5.把新增的第2頁「TabPage2」的「Properties」頁面下「Caption」設定為「更新紀錄」。**
    + **9.5.1 放上一個TMemo。設定「Properties」頁面下「Name」設定為「Update_Memo」。**
    + **9.5.1.1 設定「Log_Memo」的「Properties」頁面下「Align」設定為「AlClient」。**
    + **9.5.1.2 設定「Log_Memo」的「Properties」頁面下「Lines」的內容。清空後填入版本紀錄。**
    ```cpp
    v20220103:
    初版。
    ```
    
    >以上是第2頁。

    + **9.6.把新增的第3頁「TabPage3」的「Properties」頁面下「Caption」設定為「Web Server」。**
    + **9.6.1 設定「TabPage3」的「Properties」頁面下「PageIndex」設定為「0」。**
    + **9.6.2 開始進行設計...**

    >以上是第3頁。單獨修改一個頁面的PageIndex會影響所有的頁面，可能使其他頁面的PageIndex值改變。
    設計時可考慮使用TPanel元件進行響應式設計，不想看到分隔線就把BevelOuter設為bvNone。

