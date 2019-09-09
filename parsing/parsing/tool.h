#pragma once
#include "helper.h"

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