#pragma once
#include "tool_includeHelper.h"
#include "tool_staticText.h"

// id:list_XXXX
bool is_list_token(string name) {
	if (name.size() > 4 
		&&name[0] == 'l'
		&& name[1] == 'i'
		&& name[2] == 's'
		&& name[3] == 't'
		)
		return true;
	else return false;
}
// button --- id:btnF__XXXX
bool is_callback_fun_token(string name) {
	if (name.size() > 4 
		&& name[0] == 'b'
		&& name[1] == 't'
		&& name[2] == 'b'
		&& name[3] == 'F'
		)
		return true;
	else return false;
}

string returnType(string id)
{
	string before = id.substr(0, id.find_first_of("_"));
	if (before == H9D_BTN_PREFIX) return H9D_BTN_CLASS;
	if (before == H9D_WND_PREFIX) return H9D_WND_CLASS;
	if (before == H9D_ST_PREFIX) return H9D_ST_CLASS;
	if (before == H9D_SCR_PREFIX) return H9D_SCR_CLASS;
	if (before == H9D_IMG_PREFIX) return H9D_IMG_CLASS;
	if (before == H9D_CHK_PREFIX) return H9D_CHK_CLASS;
	if (before == H9D_EDBX_PREFIX) return H9D_EDBX_CLASS;
	if (before == H9D_EFCT_PREFIX) return H9D_EFCT_CLASS;
	if (before == H9D_PRCCBR_PREFIX) return H9D_PRCCBR_CLASS;
	return "";
}