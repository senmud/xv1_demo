//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include <Vcl.NumberBox.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TTreeView *TreeView1;
	TNetHTTPClient *NetHTTPClient1;
	TNetHTTPRequest *NetHTTPRequest1;
	TEdit *Edit1;
	TMemo *Memo1;
	TButton *Button2;
	TNetHTTPRequest *NetHTTPRequest2;
	TNetHTTPClient *NetHTTPClient2;
	TEdit *Edit2;
	TProgressBar *ProgressBar1;
	TSpinEdit *SpinEdit1;
	TCheckBox *CheckBox1;
	TEdit *Edit3;
	TCheckBox *CheckBox2;
	TPaintBox *PaintBox1;
	TTimer *Timer1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall NetHTTPRequest1RequestCompleted(TObject * const Sender, IHTTPResponse * const AResponse);
	void __fastcall NetHTTPRequest1RequestError(TObject * const Sender, const UnicodeString AError);
	void __fastcall Memo1Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall NetHTTPRequest2RequestCompleted(TObject * const Sender, IHTTPResponse * const AResponse);
	void __fastcall NetHTTPRequest2RequestException(TObject * const Sender, Exception * const AError);
    void __fastcall KeyMessage(tagMSG &msg, bool &handle);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);








private:	// User declarations
	int step;
	UnicodeString curDom, infoDom;
	TTreeNode *pcurDown;
	TTreeNode *pcurNode, *pInfoNode;
	bool stop;
	UnicodeString filebase;
	int fileidx;
	int concurrent;

	class rec_obj {
		public:
		TRect *rec;
		int size;
		TPoint pos;
		TPoint scale;
        TColor color;

		rec_obj() {}

		rec_obj(const TPoint &scale, int size=10) {
            Init(scale, size);
		}

		~rec_obj() {
            delete rec;
		}

        void Init(const TPoint &scale, int size=10, TColor color = clGreen) {
			this->scale = scale;
			this->size = size;
			this->rec = new TRect();
			this->rec->SetHeight(this->size);
			this->rec->SetWidth(this->size);
            this->color = color;
		}

		void SetPos(const TPoint &pos) {
			this->pos = pos;
            this->rec->SetLocation(this->pos);
		}

		void SetRandomPos() {
			Randomize();
			pos.X = Random(scale.X - size);
			pos.Y = Random(scale.Y - size);
            rec->SetLocation(pos);
		}

		void MoveWithRandomY() {
			TPoint curpos = rec->GetLocation();
			curpos.X = _getBias(curpos.X, pos.X, scale.X-size);
			curpos.Y = _getRandomBias(curpos.Y, scale.Y-size);

			rec->SetLocation(curpos);
		}

		void MoveWithRandom() {
			TPoint curpos = rec->GetLocation();
			curpos.X = _getRandomBias(curpos.X, scale.X-size);
			curpos.Y = _getRandomBias(curpos.Y, scale.Y-size);
            rec->SetLocation(curpos);
		}

		private:
		int bias = 3;
		int _getRandomBias(int val, int limit) {
			int curbias = bias;
			if (Random(100) >= 50) {
                curbias = -bias;
			}
			val += curbias;
			if (val >= limit) {
				val -= curbias + 1;
			} else if (val < 0) {
				val -= curbias - 1;
			}

            return val;
		}
		int _getBias(int val, int beginpos, int limit) {
			val += bias;
			return val > limit ? beginpos : val;
        }
	};

	rec_obj *robj;
    int rec_size = 5;

	int Step() {
		int ret = step;
		if (step > 1) {
			step = 0;
		} else {
			step++;
		}
		return ret;
	}

	void Log(const UnicodeString &info) {
		Memo1->Lines->Add(info);
		TObject *send;
		Memo1->OnChange(send);
	}

	void SendMsg(TButton *btn) {
        PostMessage(btn->Handle, WM_LBUTTONDOWN, 0, 0);
		PostMessage(btn->Handle, WM_LBUTTONUP, 0, 0);
	}

	bool UpdateNode() {
        if (CheckBox1->Checked) {
			pcurNode = pcurNode->Parent->getNextSibling();
			if (pcurNode != NULL) {
				pcurNode = pcurNode->getFirstChild();
			}

			Log("continue next dv ..");
			SendMsg(Button2);
            return true;
		}
        return false;
	}

	void InitRec() {
		robj = new rec_obj[rec_size];
		for (int i=0; i < rec_size; i++) {
			robj[i].Init(TPoint(PaintBox1->Width, PaintBox1->Height));
            robj[i].SetRandomPos();
		}

		this->DoubleBuffered = true;
    }
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
