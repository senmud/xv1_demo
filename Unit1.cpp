//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Text = "";
	step = 0;
	pcurNode = NULL;
    pInfoNode = NULL;
	curDom = "";
    infoDom = "";
	pcurDown = NULL;
	stop = false;
	concurrent = 1;

	TDateTime dt = Sysutils::Now();
	filebase = UnicodeString("d:\\dv_")+Sysutils::FormatDateTime(L"yyyy_mm_dd_hh_", dt);
	fileidx = 0;

	Edit2->Text = filebase;

	SpinEdit1->MaxValue = 10;
    SpinEdit1->MinValue = 1;
	SpinEdit1->Value = concurrent;

	InitRec();

    Application->OnMessage = KeyMessage;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{

	if (Edit1->Text.Compare("http") <= 0) {
		Edit1->Text = "https://www.xv-videos1.com";
	}

    linklist.Add(Edit1->Text);

	//Memo1->Text = "";

	if (isLoadLink == False) {
        isLoadLink = True;
		Button1->Caption = "Sending...";
		NetHTTPRequest1->Get(linklist.LoadNext());
		NetHTTPRequest1->Execute();
	} else {
		Button1->Caption = "Waiting...";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NetHTTPRequest1RequestCompleted(TObject * const Sender, IHTTPResponse * const AResponse)

{
	int code = AResponse->StatusCode;
	UnicodeString rst = AResponse->ContentAsString();
	int pos = -1;
    bool done = False;

	if (Step() != 0) {
        Log("Got download");
		if ( (pos=rst.Pos("hls-1440p")) > 0 || (pos=rst.Pos("hls-1080p")) > 0 || (pos=rst.Pos("hls-720p")) > 0) {
			UnicodeString m3 = rst.SubString(pos, 20);
			Button1->Caption = "video..";
			int extpos = 0;
			if ((extpos=m3.Pos(".m3u8")) > 0) {
				UnicodeString tsurl = m3.SubString(0, extpos+4);
				TreeView1->Items->AddChild(pInfoNode, tsurl);
				NetHTTPRequest1->Get(infoDom+tsurl);
				NetHTTPRequest1->Execute();
			} else {
				int len = rst.Length();
                int bias = 19;
				pos += bias;
				while (pos > 0 && (pos+bias) < len) {
					UnicodeString left = rst.SubString(pos, len-pos);
					int cur = 0;
					if ((cur=left.Pos("hls-1440p")) > 0 || (cur=left.Pos("hls-1080p")) > 0 || (cur=left.Pos("hls-720p")) > 0) {
                        UnicodeString end = left.SubString(cur, left.Length()-cur);
						if ((bias=end.Pos(".ts")) > 0) {
							bias = bias + 3;
						} else {
                            break;
						}

						m3 = left.SubString(cur, bias);
						TreeView1->Items->AddChild(pInfoNode, m3);
						pos += cur + bias;
					} else {
                        break;
					}
				}

				Button1->Caption = "Go Next";
				if (pcurNode == NULL) {
					pcurNode = pInfoNode;
				}
            }
		} else {
			Log("no valid info: " + infoDom);
			Button1->Caption = "no m3u8";
		}

		if (linklist.IsLoadDone() == False) {
            NetHTTPRequest1->Get(linklist.LoadNext());
			NetHTTPRequest1->Execute();
		} else {
            isLoadLink = False;
        }
		return;
	}

	pos = rst.Pos("hls.m3u8");

	if ( pos > 2 ) {
		for ( int cur=pos-2; cur>0; cur--) {
			if (rst[cur] == '\'') {
				UnicodeString val = rst.SubString(cur+1, pos+7-cur);
				UnicodeString title="M3U8";
                Log("Got link: "+val);
				pos = 0;

				int last = -1;
				for (int i = val.Length()-1; i >= 0; i--) {
					if (val[i] == '/') {
						last = i;
                        break;
					}
				}
				if (last > 0) {
					infoDom = val.SubString(0, last);
				} else {
                    infoDom = val;
				}

				for (int i = Edit1->Text.Length()-1; i >= 0; i--) {
					if (Edit1->Text[i] == '/') {
						title = Edit1->Text.SubString(i+1, Edit1->Text.Length());
                        break;
					}
				}
                pInfoNode = TreeView1->Items->Add(NULL, title);
				pInfoNode = TreeView1->Items->AddChild(pInfoNode, infoDom);

				Button1->Caption = "get m3u8..";
				NetHTTPRequest1->Get(val);
				NetHTTPRequest1->Execute();
				break;
			}
		}

	} else {
		//TreeView1->Items->Add(NULL, "Lost");
		//pos = -2;
		UnicodeString str;
		str = str.sprintf(L"Lost£º%d", pos);
		Button1->Caption = str;

		if (linklist.IsLoadDone() == False) {
            NetHTTPRequest1->Get(linklist.LoadNext());
			NetHTTPRequest1->Execute();
		} else {
            isLoadLink = False;
		}
        return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NetHTTPRequest1RequestError(TObject * const Sender, const UnicodeString AError)

{
	UnicodeString info;
	info = info.sprintf(L"Bt1 error: %s, cur que: %d, %d", AError.c_str(), linklist.GetCurLoadID(), linklist.GetCurID());
	Log(info);
	//Memo1->Text = "Error:\n" + AError;
	Button1->Caption = "Error!";
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Memo1Change(TObject *Sender)
{
    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (pcurNode == NULL) {
		Log("nothing download..");
        return;
	}

	if (pcurDown == NULL) {
		ProgressBar1->Max = pcurNode->Count;
		ProgressBar1->Step = 1;
		pcurDown = pcurNode->getFirstChild();
		Edit2->Text = filebase + fileidx++ + ".ts";
		curDom = pcurNode->Text;
        Edit3->Text = pcurNode->Parent->Text;
        Log("set dom " + curDom + ", file " + Edit2->Text);

		for (; pcurDown != NULL; pcurDown = pcurDown->GetNextChild(pcurDown)) {
            ProgressBar1->StepIt();
			if (pcurDown->Text.Pos(".ts") == 0) {
				Log("ignore " + pcurDown->Text);
				continue;
			}
            break;
		}

		if (pcurDown == NULL) {
			if (UpdateNode() == false) {
				Log("Nothing to down..");
			}
            return;
		}

        Log("downloading "+pcurDown->Text+"...");

		NetHTTPRequest2->Get(curDom + pcurDown->Text);
        NetHTTPRequest2->Execute();
	} else {
		stop = !stop;
		if (stop) {
			Log("stop downloading ..");
			Button2->Caption = "Conti";
			NetHTTPRequest2->Cancel();
		} else {
			Log("continue downloading " + pcurDown->Text + "..");
			Button2->Caption = "Download";

			NetHTTPRequest2->Get(curDom+pcurDown->Text);
            NetHTTPRequest2->Execute();
        }

    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NetHTTPRequest2RequestCompleted(TObject * const Sender, IHTTPResponse * const AResponse)

{
	if (pcurDown == NULL) {
		Log("invalid cur down ...");
        return;
	}

	if (AResponse->GetStatusCode() != 200 || stop == TRUE) {
		Log("request abort ...");
        return;
	} else {
    	//Log("request code " + AResponse->GetStatusText() + " ..");
    }

    TFileStream *pfs = NULL;
	UnicodeString fn = Edit2->Text;

	try {
		pfs = new TFileStream(fn.Trim(), fmOpenReadWrite);
		pfs->Seek(0, soFromEnd);

	} catch (...) {
        pfs = new TFileStream(fn.Trim(), fmCreate);
	}

	pfs->CopyFrom(AResponse->GetContentStream());
	Log("file " + fn);
	pfs->Free();

	ProgressBar1->StepIt();

	pcurDown = pcurDown->GetNextChild(pcurDown);
	if (pcurDown != NULL) {
        Log("continue downloading " + pcurDown->Text);
		NetHTTPRequest2->Get(curDom + pcurDown->Text);
        NetHTTPRequest2->Execute();
	} else {
		ResetDvStatus(fn);
		UpdateNode();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NetHTTPRequest2RequestException(TObject * const Sender, Exception * const AError)

{
	Log("net2 exp: "+AError->ToString()+" eee");
}

void __fastcall TForm1::NetHTTPRequest2RequestError(TObject * const Sender, const UnicodeString AError)

{
	Log("net2 err: "+AError+" eee");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyMessage(tagMSG &msg, bool &handle)
{
	if (msg.message == WM_KEYDOWN) {
		if ((GetKeyState(VK_CONTROL) & 0x80) && (msg.wParam == 'v' || msg.wParam == 'V')) {
			Edit1->Clear();
			Edit1->PasteFromClipboard();
			if (CheckBox2->Checked) {
				SendMsg(Button1);
			}
		}

	}
}
void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
	TCanvas *pc = PaintBox1->Canvas;
	int h = PaintBox1->Height;
	int w = PaintBox1->Width;

	pc->Pen->Color = clBlack;
	pc->Brush->Color = clBlack;
	pc->Rectangle(0, 0, w, h);
	pc->Pen->Color = clBlue;

	for (int x=0; x<w; x+=20) {
		for (int y=0; y<h; y+=20) {
			pc->Pixels[x][y] = clWhite;
		}
	}

	for (int i=0; i<rec_size; i++) {
		pc->Pen->Color = robj[i].color;
		pc->Brush->Color = robj[i].color;
        pc->FillRect(*robj[i].rec);
	}
	//Log("painted");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (robj == NULL) {
		return;
	}

	for (int i=0; i < rec_size; i++) {
        robj[i].MoveWithRandom();
	}

	PaintBox1->Refresh();

	//Log(UnicodeString().sprintf(L"update pos: %d.%d", pos.X, pos.Y));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if (stop != TRUE) {
		this->SendMsg(Button2);
	}

	if (stop == TRUE) {
		ResetDvStatus(Edit2->Text, 1);
		UpdateNode();
	}
}
//---------------------------------------------------------------------------


