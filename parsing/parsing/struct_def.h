#pragma once
#include "helper.h"
#define MAX_SUBCONTROL 200 
struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> cons;
};