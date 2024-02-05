//---------------------------------------------------------------------------

#ifndef LinkInfoH
#define LinkInfoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

class LinkInfo {
	public:
	int Add(const UnicodeString &link);
	void Update(int id, bool isload, bool isjump, const UnicodeString &picUrl);
	const UnicodeString& LoadNext();
	const UnicodeString& DownloadNext();

	bool IsLoadDone() {
		return _curLoadID >= _curID;
	}

	int GetCurID() {
        return _curID;
	}

	int GetCurLoadID() {
        return _curLoadID;
    }

	private:
	struct _LinkNode {
		UnicodeString link;
		UnicodeString picURL;
		bool isLoad, isJump;
    };
	private:
	int _curID, _curLoadID, _curDownID;
	DynamicArray<_LinkNode> _list;

	public:
	LinkInfo() {
		_curID = _curLoadID = _curDownID = 0;
        _list.set_length(100);
    }
};

#endif
