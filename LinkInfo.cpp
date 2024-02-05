//---------------------------------------------------------------------------

#pragma hdrstop

#include "LinkInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

int LinkInfo::Add(const UnicodeString &link) {
	_LinkNode node;
	node.link = link;
	_list[_curID] = node;

	int ret = _curID;
	_curID++;
    return ret;
}

void LinkInfo::Update(int id, bool isload, bool isjump, const UnicodeString &picUrl) {
	if (id < _list.Low || id > _list.High) {
		return;
	}

	_list[id].picURL = picUrl;
	_list[id].isJump = isjump;
    _list[id].isLoad = isload;
}

const UnicodeString& LinkInfo::LoadNext() {
	const UnicodeString &rst = _list[_curLoadID].link;
	_curLoadID++;
	return rst;
}

const UnicodeString& LinkInfo::DownloadNext() {
	const UnicodeString &rst = _list[_curDownID].link;
	_curDownID++;
    return rst;
}
