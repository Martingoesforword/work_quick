#include "UINewGardenHandbook.h"
#include "modules\new_garden\client\new_garden_client_interface.h"
#include "NewGardenUIConfig.h"
#include "..\..\hall\rank_global_dance\UIRGDRankRewardWnd.h"
#include "NewGardenEntityConfig.h"
#include "modules\item\client\ClientItemManager.h"
#include "UINewGardenWnds.h"
#include "UINewGardenCartoon.h"

namespace
{
	H3D_CLIENT::UIGlobalLock::UIKey enter_handbook = "new_garden_enter_handbook";
	H3D_CLIENT::UIGlobalLock::UIKey change_tabs = "new_garden_change_tabs";
	H3D_CLIENT::UIGlobalLock::UIKey change_page = "new_garden_change_pages";
	H3D_CLIENT::UIGlobalLock::UIKey change_coll_pages = "new_garden_change_coll_pages";
	H3D_CLIENT::UIGlobalLock::UIKey enter_handbook_set = "new_garden_enter_handbook_set";
	H3D_CLIENT::UIGlobalLock::UIKey enter_handbook_take_reward = "new_garden_enter_handbook_take_reward";
	H3D_CLIENT::UIGlobalLock::UIKey enter_handbook_query_quest = "enter_handbook_query_quest";
	const int progress_length = atoi(FindString("str_new_garden_handbook_set_progress_length"));//宝箱节点进度最长长度
	const int max_percent = 100;
}

CUINewGardenHandbookMainWnd::CUINewGardenHandbookMainWnd()
	: CUIBase(L"wnd_newgarden_handbook")
	, m_collectWnd(NULL)
{
	//初始化控件
	InitControl(this, m_st_page, m_stateWnd, L"st_page");
	InitControl(this, m_btn_close, m_stateWnd, L"btn_close", SetPressFunc(&CUINewGardenHandbookMainWnd::OnBtnClose));
	InitControl(this, m_btn_next, m_stateWnd, L"btn_next", SetPressFunc(&CUINewGardenHandbookMainWnd::OnBtnPage));
	InitControl(this, m_btn_pre, m_stateWnd, L"btn_prev", SetPressFunc(&CUINewGardenHandbookMainWnd::OnBtnPage));
	InitControl(this, m_btnCollectReward, m_stateWnd, L"btn_1", SetPressFunc(&CUINewGardenHandbookMainWnd::OnBtnCollectReward));

	InitControl(this, m_stCollectAnimal, m_stateWnd,L"stCollectAnimal");
	InitControl(this, m_stCollectSSR, m_stateWnd, L"stCollectSSR");
	InitControl(this, m_stCollectSR, m_stateWnd, L"stCollectSR");
	InitControl(this, m_stCollectR, m_stateWnd, L"stCollectR");
	InitControl(this, m_stCollectBaby, m_stateWnd, L"stCollectBaby");
	m_vec_cb_cat.resize(CNGHMW_CAT_NUM);
	for (int i = 0; i < m_vec_cb_cat.size(); ++i)
	{
		InitControl(this, m_vec_cb_cat[i], m_stateWnd, CombineStr("checkBox_cat_",i), SetPressFunc(&CUINewGardenHandbookMainWnd::OnCBCat));
	}
	m_vec_img_cat.resize(CNGHMW_CAT_NUM);
	for (int i = 0; i < m_vec_img_cat.size(); ++i)
	{
		InitControl(this, m_vec_img_cat[i], m_stateWnd, CombineStr("imgNew_", i));
	}

	m_vec_ui.resize(CNGHMW_CAT_ITEM_NUM_PER_PAGE);
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		H3D_CLIENT::IUIWnd* cur_wnd = m_stateWnd->FindControl(CombineStr("wnd_cat_item_",i).c_str());
		UIMainWndSingleItem tmp_item;
		tmp_item.m_wnd = cur_wnd;
		if (cur_wnd)
		{
			InitControl(this, tmp_item.m_img, cur_wnd, L"img_icon");
			InitControl(this, tmp_item.m_st_has, cur_wnd, L"st_coll");
			InitControl(this, tmp_item.m_st_name, cur_wnd, L"st_name");
			InitControl(this, tmp_item.m_cb_enter, cur_wnd, L"checkBox_enter", SetPressFunc(&CUINewGardenHandbookMainWnd::OnCBEnterSet));
			InitControl(this, tmp_item.m_eff_has, cur_wnd, L"effect_has");
			InitControl(this, tmp_item.m_img_full, cur_wnd, L"img_full");
			InitControl(this, tmp_item.m_img_tips, cur_wnd, L"imgTip");
			//InitControl(this, tmp_item.m_img_box, cur_wnd, L"imgBox");
			InitControl(this, tmp_item.m_btn_box, cur_wnd, L"btnBox",SetPressFunc(&CUINewGardenHandbookMainWnd::OnCBEnterSet));
		}
		m_vec_ui[i] = tmp_item;
	}
}

CUINewGardenHandbookMainWnd::~CUINewGardenHandbookMainWnd()
{

}

void CUINewGardenHandbookMainWnd::ShowCatWnd(int type)
{

}

void CUINewGardenHandbookMainWnd::RequestShowWnd(int64 pstid)
{
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook);
		getClientHall()->GetNewGardenClient()->EnterHandBook(pstid);
		m_pstid = pstid;
	}
}

void CUINewGardenHandbookMainWnd::ShowWnd(const NewGardenHandBookTabsInfo& res_info)
{
	ParseTabInfo(res_info);
	RefreshTabWnd();
	RefreshCollect(res_info);
	Show();

	//更新一下田园后院的奖励小红点显示
	if (getClientHall()->GetUIHall()->GetUINewGardenField()->IsShow())
	{
		getClientHall()->GetUIHall()->GetUINewGardenField()->ShowHandbookRewardTip(res_info.m_animal_tabs_have_reward || res_info.m_partner_tabs_have_reward
																					|| res_info.m_animal_tabs_have_new_collection || res_info.m_partner_tabs_have_new_collection);
	}
	if (getClientHall()->GetUIHall()->GetUINewGardenBackyard()->IsShow())
	{
		getClientHall()->GetUIHall()->GetUINewGardenBackyard()->ShowHandbookRewardTip(res_info.m_animal_tabs_have_reward || res_info.m_partner_tabs_have_reward
																					|| res_info.m_animal_tabs_have_new_collection || res_info.m_partner_tabs_have_new_collection);
	}
}

void CUINewGardenHandbookMainWnd::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
}

void CUINewGardenHandbookMainWnd::OnBtnPage(H3D_CLIENT::IUIWnd* wnd)
{
	bool add = false;
	if (wnd == m_btn_next)
	{
		add = true;
	}
	if (getClientHall()->GetNewGardenClient())
	{
		int next_page = add ? m_cur_mainwnd_page_data.m_cur_page + 1 : m_cur_mainwnd_page_data.m_cur_page - 1;
		next_page = next_page < 0 ? 0 : next_page;
		next_page = next_page > m_cur_mainwnd_page_data.m_max_page ? m_cur_mainwnd_page_data.m_max_page : next_page;
		GetWndManager()->catchLock()->lock_ui(change_page);
		getClientHall()->GetNewGardenClient()->ChangeHandBookTabsPage(m_pstid, m_cur_mainwnd_page_data.m_cur_tab_type, next_page);
	}
}

void CUINewGardenHandbookMainWnd::OnBtnCollectReward(H3D_CLIENT::IUIWnd * wnd)
{
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook_query_quest);
		getClientHall()->GetNewGardenClient()->QueryQuestInfo(m_pstid, 1);
		getCollectUI()->SetPstid(m_pstid);
	}
}

void CUINewGardenHandbookMainWnd::OnCBCat(H3D_CLIENT::IUIWnd* wnd)
{
	int type = wnd == m_vec_cb_cat[CNGHMW_CAT_ANI] ? NGCT_ANIMAL : NGCT_PARTNER;
	for(int i=0;i<m_vec_cb_cat.size();++i)
	{
		m_vec_cb_cat[i]->Check((m_tab_info.m_tabs_id-NGCT_ANIMAL)==i);//请求消息返回前不改变页签
	}
	if (type == m_tab_info.m_tabs_id)//若选中的是当前打开的界面
	{
		return;
	}
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(change_tabs);
		getClientHall()->GetNewGardenClient()->ChangeHandBookTabs(m_pstid, type);
	}
}

void CUINewGardenHandbookMainWnd::ParseTabInfo(const NewGardenHandBookTabsInfo& res_info)
{
	m_tab_info = res_info;
	m_cur_mainwnd_page_data.Reset();
	m_cur_mainwnd_page_data.m_max_page = res_info.m_total_pages;
	m_cur_mainwnd_page_data.m_cur_page = res_info.m_cur_page_id;
	m_cur_mainwnd_page_data.m_cur_tab_type = res_info.m_tabs_id;
	m_cur_mainwnd_page_data.m_has_cat_rewards[CNGHMW_CAT_ANI] = res_info.m_animal_tabs_have_reward;
	m_cur_mainwnd_page_data.m_has_cat_rewards[CNGHMW_CAT_PARTENER] = res_info.m_partner_tabs_have_reward;
	m_cur_mainwnd_page_data.m_has_new_animal[CNGHMW_CAT_ANI] = res_info.m_animal_tabs_have_new_collection;
	m_cur_mainwnd_page_data.m_has_new_animal[CNGHMW_CAT_PARTENER] = res_info.m_partner_tabs_have_new_collection;

	//填充单个的数据
	for (int i = 0; i < res_info.m_tabs_set_infos.size(); ++i)
	{
		const NewGardenHandBookTabsSetInfo& cur_data = res_info.m_tabs_set_infos[i];
		UIMainWndSingleItemData single_data;
		single_data.m_has_num = cur_data.m_cur_count; 
		single_data.m_total = cur_data.m_all_count;
		single_data.m_name = cur_data.m_name;
		single_data.m_id = cur_data.m_id;
		single_data.m_has_reward = cur_data.m_have_reward;
		single_data.m_has_new_animal = cur_data.m_have_new_collection;
		single_data.m_collect_effect_num =  cur_data.m_collect_effect_num;
		m_cur_mainwnd_page_data.m_vec_data.push_back(single_data);
	}
}
void CUINewGardenHandbookMainWnd::RefreshCollect(const NewGardenHandBookTabsInfo& Info)
{
	HandBookProcessInfo process_info = Info.m_process_info;
	int total_collected = process_info[NGRT_R].first + process_info[NGRT_SR].first + process_info[NGRT_SSR].first;
	int total = process_info[NGRT_R].second + process_info[NGRT_SR].second + process_info[NGRT_SSR].second;
	std::string progress;
	if(Info.m_tabs_id == NGCT_ANIMAL)
	{
		progress = EvaluateString("str_animal_collect_text"
			, StrPair("COLLECTED", total_collected), StrPair("ALL", total));
	}
	else if (Info.m_tabs_id == NGCT_PARTNER)
	{
		progress = EvaluateString("str_partner_collect_text"
			, StrPair("COLLECTED", total_collected), StrPair("ALL", total));
	}
	m_stCollectAnimal->SetText(H3D_CLIENT::ANSIToUnicode(progress).c_str());
	progress = EvaluateString("str_ssr_collect_text"
		, StrPair("COLLECTED", process_info[NGRT_SSR].first), StrPair("ALL", process_info[NGRT_SSR].second));
	m_stCollectSSR->SetText(H3D_CLIENT::ANSIToUnicode(progress).c_str());
	progress = EvaluateString("str_sr_collect_text"
		, StrPair("COLLECTED", process_info[NGRT_SR].first), StrPair("ALL", process_info[NGRT_SR].second));
	m_stCollectSR->SetText(H3D_CLIENT::ANSIToUnicode(progress).c_str());
	progress = EvaluateString("str_r_collect_text"
		, StrPair("COLLECTED", process_info[NGRT_R].first), StrPair("ALL", process_info[NGRT_R].second));
	m_stCollectR->SetText(H3D_CLIENT::ANSIToUnicode(progress).c_str());
	progress = EvaluateString("str_new_garden_perfect_collected_2"
		, StrPair("num", Info.m_total_activate_effect_num));
	m_stCollectBaby->SetText(H3D_CLIENT::ANSIToUnicode(progress).c_str());
}
void CUINewGardenHandbookMainWnd::RefreshTabWnd()
{
	//更新页签表现
	for (int i = 0; i < m_vec_cb_cat.size(); ++i)
	{
		int cur_ui_type = m_cur_mainwnd_page_data.m_cur_tab_type - NGCT_ANIMAL + CNGHMW_CAT_ANI;
		m_vec_cb_cat[i]->Check(i == cur_ui_type);
	}
	for (int i = 0; i < m_vec_img_cat.size() && i<m_cur_mainwnd_page_data.m_has_cat_rewards.size()
											 && i< m_cur_mainwnd_page_data.m_has_new_animal.size(); ++i)
	{
		m_vec_img_cat[i]->ShowWindow((m_cur_mainwnd_page_data.m_has_cat_rewards[i]|| m_cur_mainwnd_page_data.m_has_new_animal[i])
									 && !getClientHall()->GetUIHall()->GetUINewGardenBackyard()->isPreviewWnd());
	}

	//更新翻页按钮
	if (m_cur_mainwnd_page_data.m_cur_page <= 1)
	{
		m_btn_pre->Disable();
	}
	else
	{
		m_btn_pre->Enable();
	}
	if (m_cur_mainwnd_page_data.m_cur_page >= m_cur_mainwnd_page_data.m_max_page)
	{
		m_btn_next->Disable();
	}
	else
	{
		m_btn_next->Enable();
	}
	if (m_cur_mainwnd_page_data.m_max_page <=1 )
	{
		m_btn_next->ShowWindow(false);
		m_btn_pre->ShowWindow(false);
	}
	else
	{
		m_btn_next->ShowWindow(true);
		m_btn_pre->ShowWindow(true);
	}
	std::string page = EvaluateString("str_new_garden_handbook_page", StrPair("cur", m_cur_mainwnd_page_data.m_cur_page), StrPair("total", m_cur_mainwnd_page_data.m_max_page));
	m_st_page->SetCaption(H3D_CLIENT::UMConverter(page.c_str()).GetUnicode());

	//更新集合封面显示
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		m_vec_ui[i].m_wnd->ShowWindow(false);
	}
	for (int i = 0; i < m_cur_mainwnd_page_data.m_vec_data.size(); ++i)
	{
		const UIMainWndSingleItemData& cur_data = m_cur_mainwnd_page_data.m_vec_data[i];
		m_vec_ui[i].m_wnd->ShowWindow(true);
		m_vec_ui[i].m_img->SetResourceID(CNewGardenUIConfig::Instance()->GetSetResID(cur_data.m_id));
		m_vec_ui[i].m_st_name->SetCaption(H3D_CLIENT::UMConverter(cur_data.m_name.c_str()).GetUnicode());
		if (cur_data.m_has_num >= cur_data.m_total)
		{
			//Todo:新花园优化QA
			if (cur_data.m_collect_effect_num >= cur_data.m_total)
			{
				m_vec_ui[i].m_img_full->SetResourceID(L"uir_huayuan_wmjq");
			}
			else
			{
				m_vec_ui[i].m_img_full->SetResourceID(L"uir_huayuan_yijiqi");
			}
			//已集齐
			m_vec_ui[i].m_st_has->ShowWindow(false);

			m_vec_ui[i].m_img_full->ShowWindow(true);
		}
		else
		{
			m_vec_ui[i].m_st_has->ShowWindow(true);
			std::string coll_progress = EvaluateString("str_new_garden_handbook_page", StrPair("cur", cur_data.m_has_num), StrPair("total", cur_data.m_total));
			m_vec_ui[i].m_st_has->SetCaption(H3D_CLIENT::UMConverter(coll_progress.c_str()).GetUnicode());
			m_vec_ui[i].m_img_full->ShowWindow(false);
		}
		std::string coll_progress = cur_data.m_has_num >= cur_data.m_total ? FindString("str_new_garden_handbook_set_full") : EvaluateString("str_new_garden_handbook_page", StrPair("cur", cur_data.m_has_num), StrPair("total", cur_data.m_total));
		m_vec_ui[i].m_st_has->SetCaption(H3D_CLIENT::UMConverter(coll_progress.c_str()).GetUnicode());
		if (cur_data.m_has_reward && !getClientHall()->GetUIHall()->GetUINewGardenBackyard()->isPreviewWnd())
		{
			m_vec_ui[i].m_eff_has->PlayEffect();
			//m_vec_ui[i].m_img_box->ShowWindow(true);
			m_vec_ui[i].m_btn_box->ShowWindow(true);
		}
		else
		{
			m_vec_ui[i].m_eff_has->StopEffect();
			m_vec_ui[i].m_btn_box->ShowWindow(false);
			//m_vec_ui[i].m_img_box->ShowWindow(false);
		}

		m_vec_ui[i].m_img_tips->ShowWindow(cur_data.m_has_new_animal && !getClientHall()->GetUIHall()->GetUINewGardenBackyard()->isPreviewWnd());
	}
	Show();
}

void CUINewGardenHandbookMainWnd::OnCBEnterSet(H3D_CLIENT::IUIWnd* wnd)
{
	int index = 0;
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		if (wnd == m_vec_ui[i].m_cb_enter || wnd == m_vec_ui[i].m_btn_box)
		{
			index = i;
		}
		m_vec_ui[i].m_cb_enter->Check(false);
	}
	if (index < m_cur_mainwnd_page_data.m_vec_data.size())
	{
		if (getClientHall()->GetNewGardenClient())
		{
			GetWndManager()->catchLock()->lock_ui(enter_handbook_set);
			getClientHall()->GetNewGardenClient()->EnterHandBookSet(m_pstid, m_cur_mainwnd_page_data.m_cur_tab_type, m_cur_mainwnd_page_data.m_vec_data[index].m_id);
		}
	}
}

void CUINewGardenHandbookMainWnd::ShowCollDetailInfo(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& res_info)
{
	m_wnd_coll_set.ShowCollDetailWnd(target_pstid,res_info);
}

void CUINewGardenHandbookMainWnd::ShowHandbookSetInfo(int64 target_pstid, const NewGardenHandBookTabsSetDetailInfo& res_info)
{
	m_wnd_coll_set.ShowWnd(target_pstid, res_info);
}

void CUINewGardenHandbookMainWnd::OnTakeProgressReward(const NewGardenHandBookTabsSetRewardResInfo& res_info)
{
	m_wnd_coll_set.OnTakeProgressReward(res_info);
}

void CUINewGardenHandbookMainWnd::OnTakeQuestReward(const RewardBasicItems& rewards)
{
	// 放入全局队列
	CUINewgardenRewardData* data = new CUINewgardenRewardData();
	data->rewards = rewards;

	if (GetWndManager()->catchLock()->query_key("NewGardenClient::HarvestPlant") || GetWndManager()->catchLock()->query_key("NewGardenClient::CatchPartner"))
	{
		m_vecRewardCache.push_back(data);
	}
	else
	{
		getClientHall()->GetUIHall()->GetUIQueuePopupManager()->RegisterPopupWnd(m_wnd_coll_set.getRewardWnd(), data);
	}
}

bool CUINewGardenHandbookMainWnd::IsShow()
{
	if (m_stateWnd)
	{
		return m_stateWnd->IsShow();
	}
	return false;
}

void CUINewGardenHandbookMainWnd::RefreshHandbookSet()
{
	if (m_wnd_coll_set.getStateWnd()->IsShow())
	{
		m_wnd_coll_set.RefreshWndInfo();
	}
}

CUINewGardenHandbookCollectWnd * CUINewGardenHandbookMainWnd::getCollectUI(bool ForceCreate)
{
	if (ForceCreate && !m_collectWnd)
	{
		m_collectWnd = new CUINewGardenHandbookCollectWnd();
	}
	return m_collectWnd;
}

void CUINewGardenHandbookMainWnd::RequstCurTabInfo()
{
	GetWndManager()->catchLock()->lock_ui(change_page);
	getClientHall()->GetNewGardenClient()->ChangeHandBookTabsPage(m_pstid, m_cur_mainwnd_page_data.m_cur_tab_type, m_cur_mainwnd_page_data.m_cur_page);
}

void CUINewGardenHandbookMainWnd::OnShow()
{
	if(!getClientHall()->GetUIHall()->GetUINewGardenBackyard()->IsShow()
		&& !getClientHall()->GetUIHall()->GetUINewGardenField()->IsShow())
	{
		m_stateWnd->ShowWindow(false);
		return; //只在上两个界面显示时才弹出
	}

	GetWndManager()->ShowModalWnd(L"wnd_newgarden_handbook");
	//ShieldWnds(true);
}

void CUINewGardenHandbookMainWnd::OnHide()
{
	m_wnd_coll_set.Hide();
	GetWndManager()->HideModalWnd(false, m_stateWnd);

	if (m_collectWnd && m_collectWnd->IsShow())
	{
		m_collectWnd->Hide();
	}
}

CUINewGardenHandbookSet::CUINewGardenHandbookSet()
	: CUIBase(L"wnd_newgarden_handbook_detail")
{
	//翻页按钮
	InitControl(this, m_btn_pre, m_stateWnd, L"btn_prev", SetPressFunc(&CUINewGardenHandbookSet::OnBtnPage));
	InitControl(this, m_btn_next, m_stateWnd, L"btn_next", SetPressFunc(&CUINewGardenHandbookSet::OnBtnPage));
	InitControl(this, m_st_page, m_stateWnd, L"st_page");
	InitControl(this, m_btn_close, m_stateWnd, L"btn_close", SetPressFunc(&CUINewGardenHandbookSet::OnBtnClose));

	//宝箱进度条相关
	InitControl(this, m_progress_wnd.m_wnd, m_stateWnd, L"wnd_progress");
	InitControl(this, m_progress_wnd.m_st_progress, m_progress_wnd.m_wnd, L"st_progress");
	InitControl(this, m_progress_wnd.m_img_progress, m_progress_wnd.m_wnd, L"img_progress");
	m_progress_wnd.m_vec_item.resize(CNGHS_CHEST_NUM);
	for (int i = 0; i < m_progress_wnd.m_vec_item.size(); ++i)
	{
		SProgressWndItem cur_item;
		InitControl(this, cur_item.m_wnd, m_progress_wnd.m_wnd, CombineStr("wnd_node_item_", i));
		InitControl(this, cur_item.m_btn, cur_item.m_wnd, L"btn_chest", SetPressFunc(&CUINewGardenHandbookSet::OnBtnChest));
		InitControl(this, cur_item.m_st_num, cur_item.m_wnd, L"st_num");
		InitControl(this, cur_item.m_eff, cur_item.m_wnd, L"effect_active");
		m_progress_wnd.m_vec_item[i] = cur_item;
	}

	m_begin_page_index = 0;
	m_tab_id = -1;
	m_set_id = -1;
	//分类相关
	m_vec_ui.resize(CNGHS_CAT_ITEM_NUM_PER_PAGE);
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		UIHandebookSetSingleItem tmp_item;
		InitControl(this, tmp_item.m_wnd, m_stateWnd, CombineStr("wnd_cat_item_",i));
		InitControl(this, tmp_item.m_img_icon, tmp_item.m_wnd, L"img_icon");
		InitControl(this, tmp_item.m_imgbb, tmp_item.m_wnd, L"imgbb");
		InitControl(this, tmp_item.m_st_name, tmp_item.m_wnd, L"st_name");
		InitControl(this, tmp_item.m_cb_enter, tmp_item.m_wnd, L"checkBox_enter", SetPressFunc(&CUINewGardenHandbookSet::OnCBDetail));
		InitControl(this, tmp_item.m_img_rarity, tmp_item.m_wnd, L"img_rarity");
		m_vec_ui[i] = tmp_item;
	}

	//标题
	InitControl(this, m_st_title, m_stateWnd, L"st_title");
}

CUINewGardenHandbookSet::~CUINewGardenHandbookSet()
{

}

void CUINewGardenHandbookSet::ShowWnd(int64 target_pstid, const NewGardenHandBookTabsSetDetailInfo& res_info)
{
	m_pstid = target_pstid;
	m_cur_page_data.Reset();
	ParseUIInfo(res_info);
	RefreshPageWnd();
	m_begin_page_index = 0;

	//QA制作，如果是预览界面需要隐藏一部分控件和图标
	if (getClientHall()->GetUIHall()->GetUINewGardenBackyard()->isPreviewWnd())
	{
		m_progress_wnd.m_wnd->ShowWindow(false);
	}
	else
	{
		m_progress_wnd.m_wnd->ShowWindow(true);
	}
	
	Show();
}

void CUINewGardenHandbookSet::RefreshWndInfo()
{
	//刷新一下当前界面
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook_set);
		getClientHall()->GetNewGardenClient()->EnterHandBookSet(m_pstid, m_tab_id, m_set_id);
	}
}

void CUINewGardenHandbookSet::OnTakeProgressReward(const NewGardenHandBookTabsSetRewardResInfo& res_info)
{
	std::string first_title = FindString("str_ui_new_garden_backyard_text_4");
	std::string title = FindString("str_new_garden_handbook_set_rewarad_title_get");
	m_reward_wnd.ShowWnd(first_title, title, res_info.m_reward_items);

	//刷新一下当前界面
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook_set);
		getClientHall()->GetNewGardenClient()->EnterHandBookSet(m_pstid, m_tab_id, m_set_id);
	}
}

void CUINewGardenHandbookSet::OnTakeQuestReward(const RewardBasicItems & rewards)
{
	
}

void CUINewGardenHandbookSet::ParseUIInfo(const NewGardenHandBookTabsSetDetailInfo& res_info)
{
	m_cur_page_data.Reset();
	m_coll_infos = res_info.m_collection_infos;
	//标题
	m_cur_page_data.m_set_name = res_info.m_name;
	//进度条
	m_cur_page_data.m_progress_data.m_cur_num = res_info.m_cur_collection_count;
	m_cur_page_data.m_progress_data.m_max_num = res_info.m_total_collection_count;
	if (m_cur_page_data.m_progress_data.m_max_num > 0)
	{
		m_cur_page_data.m_progress_data.m_cur_ratio = m_cur_page_data.m_progress_data.m_cur_num * 1.0f / m_cur_page_data.m_progress_data.m_max_num;
	}
	//进度条宝箱位置
	H3D_CLIENT::CLPoint origin_pos;
	origin_pos.x = atoi(FindString("str_new_handbook_process_ori_pos_x"));
	origin_pos.y = atoi(FindString("str_new_handbook_process_ori_pos_y"));
	for (int i = 0; i < res_info.m_process_reward_infos.size(); ++i)
	{
		SSingleProgressItem cur_item;
		const NGHBTSetProcessRewardInfo& cur_data = res_info.m_process_reward_infos[i];
		cur_item.m_num = cur_data.m_count;
		cur_item.m_state = cur_data.m_state - NGRS_NoReward + CNGHS_INACTIVE;
		cur_item.m_pos = origin_pos;
		//cur_item.m_pos.x += progress_length * cur_data.m_count * 1.0f / m_cur_page_data.m_progress_data.m_max_num;	
		if (m_cur_page_data.m_progress_data.m_max_num > 0)
		{
			cur_item.m_pos.x += m_progress_wnd.m_img_progress->GetWidth()* cur_data.m_count * 1.0f / m_cur_page_data.m_progress_data.m_max_num;
		}
		cur_item.m_rewards = cur_data.m_rewards;
		cur_item.m_id = cur_data.m_id;
		m_cur_page_data.m_progress_data.m_vec_node.push_back(cur_item);
	}

	//小动物信息
	for (int i = 0; i < res_info.m_collection_infos.size(); ++i)
	{
		const NewGardenHandBookTabsSetCollectionSimpleInfo& cur_info = res_info.m_collection_infos[i];
		UISetSingleItemData item_data;
		item_data.m_id = cur_info.m_id;
		item_data.m_effect_id = cur_info.m_effect_id; 
		item_data.m_is_collected_full =  cur_info.m_is_collected_full;
		item_data.m_name = cur_info.m_name;
		item_data.m_rarity = cur_info.m_rarity;
		item_data.m_has = cur_info.m_is_own;
		m_cur_page_data.m_vec_data.push_back(item_data);
	}

	m_tab_id = res_info.m_tabs_id;
	m_set_id = res_info.m_set_id;
}

void CUINewGardenHandbookSet::RefreshPageWnd()
{
	//更新翻页按钮
	if (m_begin_page_index <= 0)
	{
		m_btn_pre->Disable();
	}
	else
	{
		m_btn_pre->Enable();
	}
	int max_page = m_cur_page_data.m_vec_data.size() / CNGHS_CAT_ITEM_NUM_PER_PAGE;
	if (m_cur_page_data.m_vec_data.size() % CNGHS_CAT_ITEM_NUM_PER_PAGE)
	{
		max_page++;
	}
	if (m_begin_page_index >= max_page)
	{
		m_btn_next->Disable();
	}
	else
	{
		m_btn_next->Enable();
	}
	if (max_page <= 1)
	{
		m_btn_next->ShowWindow(false);
		m_btn_pre->ShowWindow(false);
	}
	else
	{
		m_btn_pre->ShowWindow(true);
		m_btn_next->ShowWindow(true);
	}
	std::string page = EvaluateString("str_new_garden_handbook_page", StrPair("cur", m_begin_page_index+1), StrPair("total", max_page));
	m_st_page->SetCaption(H3D_CLIENT::UMConverter(page.c_str()).GetUnicode());
	
	//更新进度条
	for (int i = 0; i < m_progress_wnd.m_vec_item.size(); ++i)
	{
		m_progress_wnd.m_vec_item[i].m_wnd->ShowWindow(false);
	}

	for (int i = 0; i < m_cur_page_data.m_progress_data.m_vec_node.size() && i<m_progress_wnd.m_vec_item.size(); ++i)
	{
		const SSingleProgressItem& cur_data = m_cur_page_data.m_progress_data.m_vec_node[i];
		m_progress_wnd.m_vec_item[i].m_wnd->SetPosition(cur_data.m_pos);
		m_progress_wnd.m_vec_item[i].m_wnd->ShowWindow(true);
		std::string btn_uir_id;
		switch (cur_data.m_state)
		{
		case CNGHS_INACTIVE:
			btn_uir_id = FindString("str_new_garden_chest_inactive");
			m_progress_wnd.m_vec_item[i].m_eff->StopEffect();
			break;
		case CNGHS_ACTIVE:
			btn_uir_id = FindString("str_new_garden_chest_active");
			m_progress_wnd.m_vec_item[i].m_eff->PlayEffect();
			break;
		case CNGHS_GET:
			btn_uir_id = FindString("str_new_garden_chest_get");
			m_progress_wnd.m_vec_item[i].m_eff->StopEffect();
			break;
		default:
			break;
		}
		m_progress_wnd.m_vec_item[i].m_btn->SetResourceID(H3D_CLIENT::UMConverter(btn_uir_id.c_str()).GetUnicode());
		m_progress_wnd.m_vec_item[i].m_st_num->SetCaption(H3D_CLIENT::UMConverter(EvaluateString("str_new_garden_handbook_num", StrPair("num", cur_data.m_num))).GetUnicode());
	}
	std::string progress = EvaluateString("str_new_garden_handbook_page", StrPair("cur", m_cur_page_data.m_progress_data.m_cur_num), StrPair("total", m_cur_page_data.m_progress_data.m_max_num));
	m_progress_wnd.m_st_progress->SetCaption(H3D_CLIENT::UMConverter(progress.c_str()).GetUnicode());
	m_progress_wnd.m_img_progress->SetImageRenderRatio(m_cur_page_data.m_progress_data.m_cur_ratio);

	//更新界面
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		m_vec_ui[i].m_wnd->ShowWindow(false);
	}
	int i = m_begin_page_index*CNGHS_CAT_ITEM_NUM_PER_PAGE;
	for ( int index = 0; i < m_cur_page_data.m_vec_data.size() && index<m_vec_ui.size(); ++i, ++index)
	{
		m_vec_ui[index].m_wnd->ShowWindow(true);
		const UISetSingleItemData& data = m_cur_page_data.m_vec_data[i];
		const EntityConfigDataMap& config = CNewGardenEntityConfig::Instance()->GetEntityConfig();
		EntityConfigDataMap::const_iterator itr = config.find(data.m_id);
		if (itr == config.end())
		{
			continue;
		}		
		std::string  uir_id = itr->second.m_app_id + "_mature_static";
		if (!data.m_has)
		{
			m_vec_ui[index].m_img_icon->SetResourceID(GetTChar("str_new_garden_not_has_res"));
			m_vec_ui[index].m_imgbb->SetResourceID(L"");
			//m_vec_ui[index].m_st_name->SetCaption(GetTChar("str_new_garden_not_has_txt"));
		}
		else
		{
			m_vec_ui[index].m_img_icon->SetResourceID(H3D_CLIENT::UMConverter(uir_id.c_str()).GetUnicode());
			if (data.m_is_collected_full)
			{
				std::string uir_effect_id = CNewGardenBabyEffectConfig::Instance()->GetAppBBId(data.m_effect_id);
				m_vec_ui[index].m_imgbb->SetResourceID(H3D_CLIENT::UMConverter(uir_effect_id.c_str()).GetUnicode());
			}
			else
			{
				m_vec_ui[index].m_imgbb->SetResourceID(L"");
			}
			//m_vec_ui[index].m_st_name->SetCaption(H3D_CLIENT::UMConverter(data.m_name.c_str()).GetUnicode());
		}
		m_vec_ui[index].m_st_name->SetCaption(H3D_CLIENT::UMConverter(data.m_name.c_str()).GetUnicode());
		
		std::string rarity_uir("");
		std::string cb_uir("");
		switch (data.m_rarity)
		{
		case NGRT_R:
			rarity_uir = FindString("str_new_handbook_rarity_uir_R");
			cb_uir = "uir_huayuan_rdibanbutton";
			break;
		case NGRT_SR:
			rarity_uir = FindString("str_new_handbook_rarity_uir_SR");
			cb_uir = "uir_huayuan_srdibanbutton";
			break;
		case NGRT_SSR:
			rarity_uir = FindString("str_new_handbook_rarity_uir_SSR");
			cb_uir = "uir_huayuan_ssrdibanbutton";
			break;
		default:
			break;
		}
		m_vec_ui[index].m_img_rarity->SetResourceID(H3D_CLIENT::UMConverter(rarity_uir.c_str()).GetUnicode());
		if (data.m_has)
		{
			m_vec_ui[index].m_cb_enter->SetResourceID(H3D_CLIENT::UMConverter(cb_uir.c_str()).GetUnicode());
		}
		else
		{
			m_vec_ui[index].m_cb_enter->SetResourceID(L"uir_huayuan_weizhidibanbutton");
		}
	}

	//标题
	m_st_title->SetCaption(H3D_CLIENT::UMConverter(m_cur_page_data.m_set_name.c_str()).GetUnicode());
}

void CUINewGardenHandbookSet::OnBtnPage(H3D_CLIENT::IUIWnd* wnd)
{
	bool add = wnd == m_btn_next;
	if (add)
	{
		//向后翻页
		int max_page = m_cur_page_data.m_vec_data.size() / CNGHS_CAT_ITEM_NUM_PER_PAGE;
		if (max_page%CNGHS_CAT_ITEM_NUM_PER_PAGE)
		{
			max_page++;
		}
		if (m_begin_page_index + 1 > max_page)
		{
			return;
		}
		m_begin_page_index++;
	}
	else
	{
		//向前翻页
		if (m_begin_page_index - 1 < 0)
		{
			return;
		}
		m_begin_page_index--;
	}
	RefreshPageWnd();
}

void CUINewGardenHandbookSet::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
	//重新刷新一下集合界面信息
	if (getClientHall()->GetUIHall()->GetUINewGardenHandbook()->IsShow())
	{
		getClientHall()->GetUIHall()->GetUINewGardenHandbook()->RequstCurTabInfo();
	}
}

void CUINewGardenHandbookSet::OnBtnChest(H3D_CLIENT::IUIWnd* wnd)
{
	//判断是哪个宝箱
	int i = 0;
	for (; i < m_progress_wnd.m_vec_item.size(); ++i)
	{
		if (wnd == m_progress_wnd.m_vec_item[i].m_btn)
		{
			break;
		}
	}

	if (i>m_cur_page_data.m_progress_data.m_vec_node.size())
	{
		return;
	}
	std::string title = FindString("str_new_garden_handbook_set_rewarad_title_get");
	if (NGRS_NoReward ==  m_cur_page_data.m_progress_data.m_vec_node[i].m_state)
	{
		std::string first_title = FindString("str_ui_new_garden_backyard_text_4");
		title = EvaluateString("str_new_garden_handbook_set_reward_title_inactive", StrPair("x", m_cur_page_data.m_progress_data.m_vec_node[i].m_num));
		m_reward_wnd.ShowWnd(first_title, title, m_cur_page_data.m_progress_data.m_vec_node[i].m_rewards);
	}
	else if (NGRS_CanTake == m_cur_page_data.m_progress_data.m_vec_node[i].m_state)
	{
		//可以领取，发送消息
		GetWndManager()->catchLock()->lock_ui(enter_handbook_take_reward);
		getClientHall()->GetNewGardenClient()->TakeHandBookSetProcessReward(m_tab_id, m_set_id, m_cur_page_data.m_progress_data.m_vec_node[i].m_id);
	}
}

void CUINewGardenHandbookSet::OnCBDetail(H3D_CLIENT::IUIWnd* wnd)
{
	int index = 0;
	for (int i = 0; i < m_vec_ui.size(); ++i)
	{
		if (wnd == m_vec_ui[i].m_cb_enter)
		{
			index = i;
		}
		m_vec_ui[i].m_cb_enter->Check(false);
	}

	if (index > m_cur_page_data.m_vec_data.size())
	{
		return;
	}

	//请求看具体信息
	if (getClientHall()->GetNewGardenClient())
	{
		getClientHall()->GetNewGardenClient()->SeeHandBookSetCollectionInfo(m_pstid, m_tab_id, m_set_id, m_cur_page_data.m_vec_data[index].m_id);
	}
}

void CUINewGardenHandbookSet::OnShow()
{
	if(!getClientHall()->GetUIHall()->GetUINewGardenBackyard()->IsShow()
		&& !getClientHall()->GetUIHall()->GetUINewGardenField()->IsShow())
	{
		m_stateWnd->ShowWindow(false);
		return; //只在上两个界面显示时才弹出
	}

	GetWndManager()->ShowModalWnd(L"wnd_newgarden_handbook_detail");
}

void CUINewGardenHandbookSet::OnHide()
{
	m_wnd_coll_detail.Hide();
	m_reward_wnd.Hide();

	GetWndManager()->HideModalWnd(false, m_stateWnd);
}

void CUINewGardenHandbookSet::ShowCollDetailWnd(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& res_info)
{
	m_wnd_coll_detail.ShowWnd(target_pstid, res_info, m_coll_infos);
}

CUINewgardenRewardWnd::CUINewgardenRewardWnd()
	: CUIBase(L"wnd_newgarden_handbook_reward")
	, m_begin_page_index(0)
{
	InitControl(this, m_btn_close, m_stateWnd, L"close", SetPressFunc(&CUINewgardenRewardWnd::OnBtnClose));
	InitControl(this, m_btn_confirm, m_stateWnd, L"btnConfirm", SetPressFunc(&CUINewgardenRewardWnd::OnBtnClose));
	InitControl(this, m_btn_pre, m_stateWnd, L"btnpre", SetPressFunc(&CUINewgardenRewardWnd::OnBtnPre));
	InitControl(this, m_btn_next, m_stateWnd, L"btnnext", SetPressFunc(&CUINewgardenRewardWnd::OnBtnNext));
	InitControl(this, m_rt_con, m_stateWnd, L"rt_con");
	InitControl(this, m_st_title, m_stateWnd, L"stTitle");

	//奖励弹窗
	m_vec_ui_rewards.resize(CNRW_REWARD_NUM_PER_PAGE);
	for (int i = 0; i < m_vec_ui_rewards.size(); ++i)
	{
		SRewardItem item;
		InitControl(this, item.m_wnd, m_stateWnd, CombineStr("wnd_reward_item_", i));
		InitControl(this, item.m_img_icon, item.m_wnd, L"fitmenticon");
		InitControl(this, item.m_st_name, item.m_wnd, L"stitemnum");
		m_vec_ui_rewards[i] = item;
	}
}

CUINewgardenRewardWnd::~CUINewgardenRewardWnd()
{

}

void CUINewgardenRewardWnd::ShowWnd(const std::string& title, const RewardBasicItems& rewards)
{
	//设置title
	m_rt_con->SetScript(H3D_CLIENT::UMConverter(EvaluateString("str_new_garden_handbook_con_replace", StrPair("con",title.c_str()))).GetUnicode(), false);
	
	//更新奖励
	m_vec_rewards_data = rewards;
	m_begin_page_index = 0;
	RefreshWnd();
	Show();
}

void CUINewgardenRewardWnd::ShowWnd(const std::string& first_title, const std::string& title, const RewardBasicItems& rewards)
{
	m_st_title->SetText(H3D_CLIENT::UMConverter(first_title.c_str()).GetUnicode());
	ShowWnd(title, rewards);
}

bool CUINewgardenRewardWnd::IsPopupShow()
{
	return getStateWnd()->IsShow();
}

bool CUINewgardenRewardWnd::CanPopupShow()
{
	return true;
}

bool CUINewgardenRewardWnd::ShowPopupWnd(IUIPopupData* data)
{
	CUINewgardenRewardData* recvData = dynamic_cast<CUINewgardenRewardData*>(data);
	if (NULL == recvData)
	{
		sysAssert(0);
		return false;
	}

	std::string first_title = FindString("str_new_garden_handbook_quest_finish_title");
	std::string title = FindString("str_new_garden_handbook_quest_finish_tip");
	ShowWnd(first_title, title, recvData->rewards);

	return true;
}

void CUINewgardenRewardWnd::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
}

void CUINewgardenRewardWnd::OnBtnNext(H3D_CLIENT::IUIWnd* wnd)
{
	int max_page = m_vec_rewards_data.size() / CNRW_REWARD_NUM_PER_PAGE;
	if (max_page % CNRW_REWARD_NUM_PER_PAGE)
	{
		max_page++;
	}
	if (m_begin_page_index + 1 > max_page)
	{
		return;
	}
	m_begin_page_index++;
	RefreshWnd();
}

void CUINewgardenRewardWnd::OnBtnPre(H3D_CLIENT::IUIWnd* wnd)
{
	if (m_begin_page_index - 1 < 0)
	{
		return;
	}
	m_begin_page_index--;
	RefreshWnd();
}

void CUINewgardenRewardWnd::RefreshWnd()
{
	int begin_index = m_begin_page_index * CNRW_REWARD_NUM_PER_PAGE;
	for (int i = 0; i < m_vec_ui_rewards.size(); ++i)
	{
		m_vec_ui_rewards[i].m_wnd->ShowWindow(false);
	}

	CUIBetRewardDlg* pRewardDlg = getClientHall()->GetUIHall()->GetRewardListDlg();
	if (!pRewardDlg)
	{
		return;
	}
	std::vector<SUIReward> tempSUIRewards;
	pRewardDlg->ConvertNew(m_vec_rewards_data, tempSUIRewards);
	for (int i = 0; i < m_vec_ui_rewards.size() && begin_index < m_vec_rewards_data.size(); ++i, ++begin_index)
	{
		SRewardItem& cur_ui = m_vec_ui_rewards[i];
		cur_ui.m_wnd->ShowWindow(true);
		SUIReward& currentSUIReward = tempSUIRewards[begin_index];
		int type = currentSUIReward.m_type;
		int count = currentSUIReward.m_count;

		CClientItemManager* item_mng = getClientHall()->GetItemManager();
		if (type == NSUIReward::AWARD_EXP_SMALL || type == NSUIReward::AWARD_EXP_BIG)	//经验
		{
			cur_ui.m_wnd->SetToolTips(GetTChar("str_get_exp_from_pet_machine"));
			cur_ui.m_img_icon->SetResourceID(NSUIReward::EXPRESID);
			cur_ui.m_st_name->SetText(ItoStr(count));
		}
		else if (type == NSUIReward::AWARD_G_SMALL || type == NSUIReward::AWARD_G_BIG)	//G币
		{
			cur_ui.m_wnd->SetToolTips(GetTChar("str_get_G_money_from_pet_machine"));
			cur_ui.m_img_icon->SetResourceID(NSUIReward::GMONEYRESID);
			cur_ui.m_st_name->SetText(ItoStr(count));
		}
		else if (item_mng)	//其他类型物品的处理
		{
			H3D_CLIENT::UUtf8Converter iron(item_mng->GetItemIconFile(type));
			cur_ui.m_img_icon->SetResourceID(iron.GetUnicode());

			_tstring tips;
			item_mng->GetItemToolTipsNormal(type,tips);
			if (!tips.empty())
			{
				cur_ui.m_wnd->SetToolTips(tips.c_str(), 200, false);
			}

			_tstring desc = item_mng->GetItemNumTStr(type, count);
			cur_ui.m_st_name->SetText(desc);
		}
	}

	//翻页按钮显示
	int max_page = m_vec_rewards_data.size() / CNRW_REWARD_NUM_PER_PAGE;
	if (max_page % CNRW_REWARD_NUM_PER_PAGE)
	{
		max_page++;
	}
	if (max_page <= 1)
	{
		m_btn_next->ShowWindow(false);
		m_btn_pre->ShowWindow(false);
	}
	else
	{
		m_btn_next->ShowWindow(true);
		m_btn_pre->ShowWindow(true);

		if (m_begin_page_index<=0)
		{
			m_btn_pre->Disable();
		}
		else
		{
			m_btn_pre->Enable();
		}
		if (m_begin_page_index+1>=max_page)
		{
			m_btn_next->Disable();
		}
		else
		{
			m_btn_next->Enable();
		}
	}
}

void CUINewgardenRewardWnd::OnShow()
{
	GetWndManager()->ShowModalWnd(L"wnd_newgarden_handbook_reward");
}

void CUINewgardenRewardWnd::OnHide()
{
	GetWndManager()->HideModalWnd(false, m_stateWnd);
}
CUINewgardenBBDetail::CUINewgardenBBDetail()
	:CUIBase(L"wnd_newgarden_handbook_bb_detail")
{
	InitControl(this,m_btn_ok, m_stateWnd,L"btnOk",SetPressFunc(&CUINewgardenBBDetail::OnBtnClose));
	InitControl(this, m_img_bb, m_stateWnd, L"img_bb");
	InitControl(this, m_st_0, m_stateWnd, L"st_0");
	InitControl(this, m_rt_0, m_stateWnd, L"rt_0");
}
CUINewgardenBBDetail::~CUINewgardenBBDetail()
{

} 
void CUINewgardenBBDetail::RefreshUIData(const BBDetailData& uidata)
{
	std::string bbDetail = CNewGardenBabyEffectConfig::Instance()->GetAppBBId(uidata.m_effect_id);
	bbDetail += "_icon";
	m_img_bb->SetResourceID(H3D_CLIENT::UUtf8Converter(bbDetail.c_str()).GetUnicode());
	m_st_0->SetText(H3D_CLIENT::UUtf8Converter(uidata.m_name.c_str()).GetUnicode());
	_tstring text = H3D_CLIENT::UUtf8Converter(uidata.m_describe.c_str()).GetUnicode();
	
	text = L"$t$" + text + L"$z";
	m_rt_0->SetScript(text,false);
	//m_rt_0->SetScript(text, false); 
	//m_rt_0->SetTextAlignTypeCenter(true);
}
void CUINewgardenBBDetail::ShowWnd()
{
	Show();
}
void CUINewgardenBBDetail::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
}
void CUINewgardenBBDetail::OnShow()
{
	GetWndManager()->ShowModalWnd(L"wnd_newgarden_handbook_bb_detail");
}
void CUINewgardenBBDetail::OnHide()
{
	GetWndManager()->HideModalWnd(false, m_stateWnd);
}
CUINewgardenHandbookDetail::CUINewgardenHandbookDetail()
	: CUIBase(L"wnd_newgarden_handbook_ani_detail")
{
	InitControl(this, m_rt_chara, m_stateWnd, L"rt_charater");
	InitControl(this, m_rt_coll_way, m_stateWnd, L"rt_coll_way");
	InitControl(this, m_rt_coll_num, m_stateWnd, L"rt_coll_num");
	InitControl(this, m_img_stamp, m_stateWnd, L"img_wander_stamp");
	InitControl(this, m_btn_bb_detail, m_stateWnd, L"btn_bb_detail", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnDetail));
	InitControl(this, m_img_bb_detail, m_stateWnd, L"img_bb_detail");
	//吸引难度窗口
	InitControl(this, m_att_dif_wnd.m_wnd, m_stateWnd, L"wnd_att");
	m_att_dif_wnd.m_vec_diff_img.resize(CNHD_ATT_DIF_COUNT);
	for (int i = 0; i < m_att_dif_wnd.m_vec_diff_img.size(); ++i)
	{
		InitControl(this, m_att_dif_wnd.m_vec_diff_img[i], m_att_dif_wnd.m_wnd, CombineStr("img_dif_", i));
	}
	
	//显示外貌窗口
	InitControl(this, m_app_wnd.m_img_app, m_stateWnd, L"img_app");
	InitControl(this, m_app_wnd.m_img_rarity, m_stateWnd, L"img_rarity");
	InitControl(this, m_app_wnd.m_st_name, m_stateWnd, L"st_name");
	InitControl(this, m_app_wnd.m_img_app_bk, m_stateWnd, L"img_app_bg");
	InitControl(this, m_app_wnd.m_img_app_bb, m_stateWnd, L"img_appbb");

	//进度条
	InitControl(this, m_progress_wnd.m_st_level, m_stateWnd, L"st_lv");
	InitControl(this, m_progress_wnd.m_st_progress, m_stateWnd, L"st_progress");
	InitControl(this, m_progress_wnd.m_img_progress, m_stateWnd, L"img_progress");
	//进度条上各节点
	m_progress_wnd.m_vec_node.resize(CNHD_STORY_NODE_COUNT);
	for (int i = 0; i < m_progress_wnd.m_vec_node.size(); ++i)
	{
		SProgressNodeItem node_item;
		InitControl(this, node_item.m_wnd, m_stateWnd, CombineStr("wnd_node_",i));
		InitControl(this, node_item.m_img, node_item.m_wnd, L"img_node");
		InitControl(this, node_item.m_btn, node_item.m_wnd, L"btn_node", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnChest));
		InitControl(this, node_item.m_st_value, node_item.m_wnd, L"st_value");
		m_progress_wnd.m_vec_node[i] = node_item;
	}
	//故事按钮节点
	m_story_wnds.resize(CNHD_ATT_DIF_COUNT);
	for (int i = 0; i < m_story_wnds.size(); ++i)
	{
		SStoryItemWnd item_wnd;
		InitControl(this, item_wnd.m_wnd, m_stateWnd, CombineStr("wnd_stroy_item_",i));
		InitControl(this, item_wnd.m_btn, item_wnd.m_wnd, L"btn_enter", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnStory));
		InitControl(this, item_wnd.m_img, item_wnd.m_wnd, L"img_tip");
		m_story_wnds[i] = item_wnd;
	}

	//翻页相关
	InitControl(this, m_btn_next, m_stateWnd, L"btn_next", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnNext));
	InitControl(this, m_btn_pre, m_stateWnd, L"btn_pre", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnPre));
	InitControl(this, m_btn_close, m_stateWnd, L"btn_close", SetPressFunc(&CUINewgardenHandbookDetail::OnBtnClose));
}

CUINewgardenHandbookDetail::~CUINewgardenHandbookDetail()
{

}

void CUINewgardenHandbookDetail::OnBtnPre(H3D_CLIENT::IUIWnd* wnd)
{
	//调用逻辑接口
	if (-1 == m_id_data.m_pre_id)
	{
		return;
	}

	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(change_coll_pages);
		getClientHall()->GetNewGardenClient()->SeeHandBookSetCollectionInfo(m_id_data.m_pstid, m_id_data.m_tab_id, m_id_data.m_set_id, m_id_data.m_pre_id);
	}
}

void CUINewgardenHandbookDetail::OnBtnNext(H3D_CLIENT::IUIWnd* wnd)
{
	//调用逻辑接口
	if (-1 == m_id_data.m_next_id)
	{
		return;
	}
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(change_coll_pages);
		getClientHall()->GetNewGardenClient()->SeeHandBookSetCollectionInfo(m_id_data.m_pstid, m_id_data.m_tab_id, m_id_data.m_set_id, m_id_data.m_next_id);
	}
}

void CUINewgardenHandbookDetail::ShowWnd(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& info, const NewGardenHandBookTabsSetCollectionSimpleInfos& coll_infos)
{
	ParseUIInfo(info);
	m_id_data.m_id = info.m_collection_info.m_id;
	m_id_data.m_pstid = target_pstid;
	m_id_data.m_set_id = info.m_set_id;
	m_id_data.m_tab_id = info.m_tabs_id;
	m_id_data.m_next_id = -1;
	m_id_data.m_pre_id = -1;
	//获取前后的id
	NewGardenHandBookTabsSetCollectionSimpleInfos::const_iterator itr = coll_infos.begin();
	for (; itr != coll_infos.end(); ++itr)
	{
		if (itr->m_id == m_id_data.m_id)
		{
			//获取前一个的id
			if (itr != coll_infos.begin())
			{
				NewGardenHandBookTabsSetCollectionSimpleInfos::const_iterator pre_itr = itr - 1;
				m_id_data.m_pre_id = pre_itr->m_id;
			}
			//获取后一个的id
			itr++;
			if (itr != coll_infos.end())
			{
				m_id_data.m_next_id = itr->m_id;
			}
			break;
		}
	}
	RefreshWnd();

	//QA要求，预览是隐藏部分图标
	if (getClientHall()->GetUIHall()->GetUINewGardenBackyard()->isPreviewWnd())
	{
		hideSomeShow();
	}
	if (NULL == m_id_data.m_set_id)
	{
		m_btn_pre->ShowWindow(false);
		m_btn_next->ShowWindow(false);
	}
	else
	{
		m_btn_pre->ShowWindow(true);
		m_btn_next->ShowWindow(true);
	}
	Show();
	if (NULL == m_id_data.m_set_id )
	{
		OnBtnDetail(NULL);
	}
}
void CUINewgardenHandbookDetail::hideSomeShow()
{
	//隐藏宝箱
	for (int i=0;i< m_progress_wnd.m_vec_node.size();++i)
	{
		m_progress_wnd.m_vec_node[i].m_wnd->ShowWindow(false);
	}
	//隐藏礼物
	for (int i=0;i< m_story_wnds.size();++i)
	{
		m_story_wnds[i].m_wnd->ShowWindow(false);
	}
}
void CUINewgardenHandbookDetail::ParseUIInfo(const NewGardenHandBookSetCollectionResInfo& info)
{
	m_ui_data.Reset();
	const NewGardenHandBookTabsSetCollectionInfo& cur_info = info.m_collection_info;
	m_ui_data.m_rarity_type = cur_info.m_rarity;
	m_ui_data.m_heart_level = cur_info.m_cur_mood_level;
	m_ui_data.m_heart_progress = cur_info.m_cur_mood_value;
	m_ui_data.m_is_max_mod = cur_info.m_is_max_mood;
	if (cur_info.m_total_mood_value > 0)
	{
		m_ui_data.m_progress_ratio = cur_info.m_cur_mood_value * 1.0f / cur_info.m_total_mood_value;
	}
	else
	{
		m_ui_data.m_progress_ratio = 1.0f;
	}
	m_ui_data.m_str_chara = cur_info.m_is_own ? EvaluateString("str_new_garden_handbook_con_replace", StrPair("con", cur_info.m_sex_words.c_str())) : EvaluateString("str_new_garden_handbook_con_replace", StrPair("con", FindString("str_new_garden_not_has_txt")));
	m_ui_data.m_str_coll_way = EvaluateString("str_new_garden_handbook_con_replace", StrPair("con", cur_info.m_obtatin_method));
	m_ui_data.m_str_coll_num = EvaluateString("str_new_garden_handbook_divide", StrPair("x", cur_info.m_cur_count), StrPair("y", cur_info.m_all_count));
	m_ui_data.m_is_collected = (cur_info.m_cur_count >= cur_info.m_all_count);
	m_ui_data.m_str_name = cur_info.m_name;
	m_ui_data.m_att_dif = cur_info.m_attract_difficulty;
	m_ui_data.m_can_wander = cur_info.m_can_wander;
	m_ui_data.m_has = cur_info.m_is_own;
	m_ui_data.m_animal_id = cur_info.m_id;
	m_ui_bb_data.m_effect_id = cur_info.m_effect_id;
	m_ui_bb_data.m_describe = cur_info.m_effect_desc;
	m_ui_bb_data.m_name = cur_info.m_effect_name;
	const EntityConfigDataMap& config = CNewGardenEntityConfig::Instance()-> GetEntityConfig();
	EntityConfigDataMap::const_iterator itr = config.find(cur_info.m_id);
	if (itr != config.end())
	{
		m_ui_data.m_str_app = itr->second.m_app_id + "_mature";
	}
	//进度条节点数据
	for (int i = 0; i < info.m_collection_info.m_mood_process_reward_infos.size(); ++i)
	{
		const NGHBTSCMoodProcessRewardInfo& cur_reward_info = info.m_collection_info.m_mood_process_reward_infos[i];
		SProgressNodeInitData node_data;
		if (cur_info.m_total_mood_value > 0)
		{
			node_data.m_ratio = cur_reward_info.m_mood_value * 1.0f / cur_info.m_total_mood_value;
		}
		else
		{
			node_data.m_ratio = 1.0f;
		}
		node_data.m_cur_heart_value = cur_reward_info.m_mood_value;
		node_data.m_rewards = cur_reward_info.m_rewards;
		node_data.m_type = cur_reward_info.m_type - NGMRT_Gift + CNHDNT_SPECIAL_IMG;
		node_data.m_state = cur_reward_info.m_state;
		m_ui_data.m_node_data.push_back(node_data);
	}
	//更新故事节点 TODO 需要处理下
	for (int i = 0; i < info.m_collection_info.m_have_storys.size(); ++i)
	{
		const NewGardenAnimalCollectorUIInfo& cur_info = info.m_collection_info.m_have_storys[i];
		SStoryNodeData story_node;
		story_node.m_str_name = cur_info.m_gift_name;
		story_node.m_collector_type = cur_info.m_collector_type;
		if (cur_info.m_collector_type == NGMRT_Cartoon)
		{
			story_node.m_str_con = cur_info.m_story_content;
			story_node.m_str_uir_id = H3D_CLIENT::UMConverter(CNewGardenUIConfig::Instance()->GetCartoonUirID(cur_info.m_collector_id).c_str()).GetMBCS();
		}
		else
		{
			story_node.m_str_con = EvaluateString("str_new_garden_handbook_con_replace", StrPair("con", cur_info.m_story_content)) ;
			story_node.m_str_uir_id = H3D_CLIENT::UMConverter(CNewGardenUIConfig::Instance()->GetGiftUirID(cur_info.m_collector_id).c_str()).GetMBCS();
		}
		m_ui_data.m_story_nodes.push_back(story_node);
	}
}

void CUINewgardenHandbookDetail::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
}

void CUINewgardenHandbookDetail::RefreshAnimalImg(const string& img)
{
	m_app_wnd.m_img_app->SetResourceID(H3D_CLIENT::UUtf8Converter(img.c_str()).GetUnicode());
}

void CUINewgardenHandbookDetail::RefreshWnd()
{
	if (!m_ui_data.m_has)
	{
		//未拥有
		m_app_wnd.m_img_app->SetResourceID(L"");
		m_app_wnd.m_img_app_bb->SetResourceID(L"");
		//m_app_wnd.m_st_name->SetCaption(GetTChar("str_new_garden_not_has_txt"));
		m_app_wnd.m_img_app_bk->SetResourceID(L"uir_huayuan_tujiandiban3");
	}
	else
	{
		string sAppId = CNewGardenEntityConfig::Instance()->GetAppId(m_ui_data.m_animal_id);
		sAppId += "_mature";
		RefreshAnimalImg(sAppId);
		if (m_ui_data.m_is_collected)
		{
			string sAppbbId = CNewGardenBabyEffectConfig::Instance()->GetAppBBId(m_ui_bb_data.m_effect_id);//TODO:新花园优化 小宝宝特效
			m_app_wnd.m_img_app_bb->SetResourceID(H3D_CLIENT::UUtf8Converter(sAppbbId.c_str()).GetUnicode());
		}
		else
		{
			m_app_wnd.m_img_app_bb->SetResourceID(L"");
		}
		//m_app_wnd.m_st_name->SetCaption(H3D_CLIENT::UMConverter(m_ui_data.m_str_name.c_str()).GetUnicode());
		m_app_wnd.m_img_app_bk->SetResourceID(L"uir_huayuan_tujiandiban2");
	}
	m_app_wnd.m_st_name->SetCaption(H3D_CLIENT::UMConverter(m_ui_data.m_str_name.c_str()).GetUnicode());
	std::string rarity_uir("");
	switch (m_ui_data.m_rarity_type)
	{
	case NGRT_R:
		rarity_uir = FindString("str_new_handbook_rarity_uir_R");
		break;
	case NGRT_SR:
		rarity_uir = FindString("str_new_handbook_rarity_uir_SR");
		break;
	case NGRT_SSR:
		rarity_uir = FindString("str_new_handbook_rarity_uir_SSR");
		break;
	default:
		break;
	}
	m_app_wnd.m_img_rarity->SetResourceID(H3D_CLIENT::UMConverter(rarity_uir.c_str()).GetUnicode());

	if (m_id_data.m_tab_id == NGCT_PARTNER)
	{
		m_att_dif_wnd.m_wnd->ShowWindow(true);
		for (int i = 0; i < m_att_dif_wnd.m_vec_diff_img.size(); ++i)
		{
			m_att_dif_wnd.m_vec_diff_img[i]->ShowWindow(false);
		}
		for (int i = 0; i < m_ui_data.m_att_dif; ++i)
		{
			m_att_dif_wnd.m_vec_diff_img[i]->ShowWindow(true);
		}
	}
	else
	{
		m_att_dif_wnd.m_wnd->ShowWindow(false);
	}
	//进度条
	for (int i = 0; i < m_progress_wnd.m_vec_node.size(); ++i)
	{
		m_progress_wnd.m_vec_node[i].m_wnd->ShowWindow(false);
	}
	if (!m_ui_data.m_is_max_mod)
	{
		for (int i = 0; i < m_ui_data.m_node_data.size() && i < m_progress_wnd.m_vec_node.size(); ++i)
		{
			m_progress_wnd.m_vec_node[i].m_wnd->ShowWindow(true);
			if (CNHDNT_SPECIAL_IMG == m_ui_data.m_node_data[i].m_type)
			{
				m_progress_wnd.m_vec_node[i].m_img->SetResourceID(GetTChar("str_new_garden_progress_img_special"));
				m_progress_wnd.m_vec_node[i].m_img->ShowWindow(true);
				m_progress_wnd.m_vec_node[i].m_btn->ShowWindow(false);
				m_progress_wnd.m_vec_node[i].m_wnd->SetToolTips(L"");
			}
			else if (CNHDNT_CHEST == m_ui_data.m_node_data[i].m_type)
			{
				m_progress_wnd.m_vec_node[i].m_img->ShowWindow(false);
				m_progress_wnd.m_vec_node[i].m_btn->ShowWindow(true);
				m_progress_wnd.m_vec_node[i].m_btn->Enable();
				m_progress_wnd.m_vec_node[i].m_wnd->SetToolTips(H3D_CLIENT::UMConverter(EvaluateString("str_new_garden_handbook_heart_reward_tips", StrPair("x", m_ui_data.m_node_data[i].m_cur_heart_value))).GetUnicode());
				//需要根据状态来设置btn的资源和状态
				std::string reward_uir_id;
				switch (m_ui_data.m_node_data[i].m_state)
				{
				case NGRS_NoReward:
					reward_uir_id = FindString("str_new_garden_chest_inactive");
					break;
				case NGRS_CanTake:
					reward_uir_id = "uir_huayuan_bxyijihuo";
					break;
				case NGRS_HasTaked:
					reward_uir_id = "uir_huayuan_bxdakai";
					m_progress_wnd.m_vec_node[i].m_btn->Disable();
					break;
				default:
					break;
				}
				m_progress_wnd.m_vec_node[i].m_btn->SetResourceID(H3D_CLIENT::UMConverter(reward_uir_id.c_str()).GetUnicode());
			}
			else if(CNHDNT_CARTOON == m_ui_data.m_node_data[i].m_type)
			{
				if (m_ui_data.m_node_data[i].m_state == NGRS_NoReward)
				{
					m_progress_wnd.m_vec_node[i].m_img->SetResourceID(GetTChar("str_new_garden_progress_img_cartoon"));
					m_progress_wnd.m_vec_node[i].m_img->ShowWindow(true);
					m_progress_wnd.m_vec_node[i].m_btn->ShowWindow(false);
					m_progress_wnd.m_vec_node[i].m_wnd->SetToolTips(L"");
				}
				else
				{
					m_progress_wnd.m_vec_node[i].m_wnd->ShowWindow(false);
				}
			}
			H3D_CLIENT::CLPoint pos;
			pos.x = atoi(FindString("str_new_handbook_heart_ori_pos_x"));
			pos.y = atoi(FindString("str_new_handbook_heart_ori_pos_y"));
			int length = atoi(FindString("str_new_handbook_heart_progress_length"));
			pos.x += length * m_ui_data.m_node_data[i].m_ratio;

			m_progress_wnd.m_vec_node[i].m_wnd->SetPosition(pos);
			m_progress_wnd.m_vec_node[i].m_st_value->SetCaption(ItoStr(m_ui_data.m_node_data[i].m_cur_heart_value).c_str());
		}
	}


	m_progress_wnd.m_st_level->SetCaption(H3D_CLIENT::UMConverter(EvaluateString("str_new_garden_handbook_detail_lv", StrPair("lv", m_ui_data.m_heart_level))).GetUnicode());
	if (m_ui_data.m_is_max_mod)
	{
		m_progress_wnd.m_st_progress->SetCaption(GetTChar("str_new_garden_handbook_level_full"));
	}
	else
	{
		m_progress_wnd.m_st_progress->SetCaption(ItoStr(m_ui_data.m_heart_progress).c_str());
	}
	m_progress_wnd.m_img_progress->SetImageRenderRatio(m_ui_data.m_progress_ratio);
	//描述相关
	m_rt_chara->SetScript(H3D_CLIENT::UMConverter(m_ui_data.m_str_chara.c_str()).GetUnicode(), false);
	if (m_ui_data.m_is_collected)
	{
		m_rt_coll_num->SetScript(GetTChar("str_newgarden_animal_collected_full"),false);
	}
	else
		m_rt_coll_num->SetScript(H3D_CLIENT::UMConverter(m_ui_data.m_str_coll_num.c_str()).GetUnicode(), false);
	m_rt_coll_way->SetScript(H3D_CLIENT::UMConverter(m_ui_data.m_str_coll_way.c_str()).GetUnicode(), false);

	m_img_bb_detail->ShowWindow(!m_ui_data.m_is_collected && (m_id_data.m_pstid == getClientHall()->getLocalPlayer()->GetPersistID().id));
	m_btn_bb_detail->ShowWindow(m_ui_data.m_is_collected);
	
	m_img_stamp->ShowWindow(m_ui_data.m_can_wander);
	
	//故事节点相关
	for (int i = 0; i < m_story_wnds.size(); ++i)
	{
		m_story_wnds[i].m_wnd->ShowWindow(false);
	}

	for (int i = 0; i < m_ui_data.m_story_nodes.size() && i < CNHD_ATT_DIF_COUNT; ++i)
	{
		m_story_wnds[i].m_wnd->ShowWindow(true);
		m_story_wnds[i].m_img->SetResourceID(H3D_CLIENT::UMConverter(m_ui_data.m_story_nodes[i].m_str_uir_id.c_str()).GetUnicode());
	}

	//翻页按钮更新
	if (-1 == m_id_data.m_pre_id)
	{
		m_btn_pre->Disable();
	}
	else
	{
		m_btn_pre->Enable();
	}
	if (-1 == m_id_data.m_next_id)
	{
		m_btn_next->Disable();
	}
	else
	{
		m_btn_next->Enable();
	}

}

void CUINewgardenHandbookDetail::OnBtnStory(H3D_CLIENT::IUIWnd* wnd)
{
	int index = 0;
	for (; index < m_story_wnds.size(); ++index)
	{
		if (wnd == m_story_wnds[index].m_btn)
		{
			break;
		}
	}
	if (index < m_ui_data.m_story_nodes.size())
	{
		const SStoryNodeData &node = m_ui_data.m_story_nodes[index];
		if (node.m_collector_type == NGMRT_Cartoon)
		{
			if (getClientHall()->GetUIHall()->GetUINewGardenBackyard(false))
			{
				getClientHall()->GetUIHall()->GetUINewGardenBackyard(false)->GetUICartoon()->ShowWnd(node.m_str_uir_id, node.m_str_con);
			}
		}
		else
		{
			m_wnd_story_detail.ShowWnd(node.m_str_name, node.m_str_uir_id, node.m_str_con);
		}
	}
}
void CUINewgardenHandbookDetail::OnBtnDetail(H3D_CLIENT::IUIWnd* wnd)
{
	//TODO:新花园优化	
	m_wnd_bb_detail.RefreshUIData(m_ui_bb_data);
	m_wnd_bb_detail.ShowWnd();
}
void CUINewgardenHandbookDetail::OnBtnChest(H3D_CLIENT::IUIWnd* wnd)
{
	//判断点的是哪个节点
	int i = 0;
	for (; i < m_progress_wnd.m_vec_node.size() ; ++i)
	{
		if (wnd == m_progress_wnd.m_vec_node[i].m_btn)
		{
			break;
		}
	}
	if (i>m_ui_data.m_node_data.size())
	{
		return;
	}
	
	std::string first_title = FindString("str_ui_new_garden_backyard_text_4");
	m_reward_wnd.ShowWnd(first_title, EvaluateString("str_new_garden_handbook_reward_title_heart_level", StrPair("x", m_ui_data.m_node_data[i].m_cur_heart_value)), m_ui_data.m_node_data[i].m_rewards);
}

void CUINewgardenHandbookDetail::OnShow()
{
	if(!getClientHall()->GetUIHall()->GetUINewGardenBackyard()->IsShow()
		&& !getClientHall()->GetUIHall()->GetUINewGardenField()->IsShow())
	{
		m_stateWnd->ShowWindow(false);
		return;//只在上两个界面显示时才弹出
	}
	GetWndManager()->ShowModalWnd(L"wnd_newgarden_handbook_ani_detail");
}

void CUINewgardenHandbookDetail::OnHide()
{
	m_reward_wnd.Hide();
	m_wnd_story_detail.Hide();
	GetWndManager()->HideModalWnd(false, m_stateWnd);
}

CUINewgardenStoryDetail::CUINewgardenStoryDetail()
	: CUIBase(L"wnd_newgarden_story_detail")
{
	InitControl(this, m_img_app, m_stateWnd, L"img_app");
	InitControl(this, m_btn_confirm, m_stateWnd, L"btn_confirm", SetPressFunc(&CUINewgardenStoryDetail::OnBtnClose));
	InitControl(this, m_btn_close, m_stateWnd, L"close", SetPressFunc(&CUINewgardenStoryDetail::OnBtnClose));
	InitControl(this, m_st_name, m_stateWnd, L"st_name");
	InitControl(this, m_rt_con, m_stateWnd, L"rt_con");
}

CUINewgardenStoryDetail::~CUINewgardenStoryDetail()
{

}

void CUINewgardenStoryDetail::ShowWnd(const std::string& name, const std::string& uir_id, const std::string& con)
{
	m_img_app->SetResourceID(H3D_CLIENT::UMConverter(uir_id.c_str()).GetUnicode());
	m_rt_con->SetScript(H3D_CLIENT::UMConverter(con.c_str()).GetUnicode(), false);
	m_st_name->SetCaption(H3D_CLIENT::UMConverter(name.c_str()).GetUnicode());
	Show();
}

void CUINewgardenStoryDetail::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
{
	Hide();
}

void CUINewgardenStoryDetail::OnShow()
{
	GetWndManager()->ShowModalWnd(L"wnd_newgarden_story_detail");
}

void CUINewgardenStoryDetail::OnHide()
{
	GetWndManager()->HideModalWnd(false, m_stateWnd);
}

CUINewGardenHandbookCollectWnd::CUINewGardenHandbookCollectWnd() :CUIBase(L"wndNewGardenTask"), m_pstid(0)
{
	m_wnd = getWindow(L"music_t", L"wndNewGardenTask");
	m_wnd->ShowWindow(false);
	InitControl(this, m_btnClose, m_wnd, L"btnClose", SetPressFunc(&CUINewGardenHandbookCollectWnd::OnBtnClose));
	InitControl(this, m_btn_next, m_wnd, L"btn_next", SetPressFunc(&CUINewGardenHandbookCollectWnd::OnBtnPageNext));
	InitControl(this, m_btn_pre, m_wnd, L"btn_prev", SetPressFunc(&CUINewGardenHandbookCollectWnd::OnBtnPagePre));
	InitControl(this, m_st_page, m_wnd, L"st_page");

	m_wndMessage = m_wnd->FindControl(L"wndSystemMessages");
	for (int i = 0; i < EM_MaxSize; i++)
	{
		InitControl(this, m_listItem[i].m_wndParent, m_wndMessage, CombineStr("wndMessage", i));
		InitControl(this, m_listItem[i].m_rMessageContent, m_listItem[i].m_wndParent, L"rt_1");
		InitControl(this, m_listItem[i].m_imgCollect, m_listItem[i].m_wndParent, L"img_0");
		InitControl(this, m_listItem[i].m_imgRewardBack, m_listItem[i].m_wndParent, L"imgBack");
		InitControl(this, m_listItem[i].m_imgRewardIcon, m_listItem[i].m_wndParent, L"imgIcon");
		InitControl(this, m_listItem[i].m_stItemName, m_listItem[i].m_wndParent, L"st_0");
		InitControl(this, m_listItem[i].m_stRewardTime, m_listItem[i].m_wndParent, L"stTime");
	}
}

CUINewGardenHandbookCollectWnd::~CUINewGardenHandbookCollectWnd()
{
}

void CUINewGardenHandbookCollectWnd::OnShow()
{
	GetWndManager()->ShowModalWnd(L"wndNewGardenTask", L"music_t");
}

void CUINewGardenHandbookCollectWnd::OnHide()
{
	m_pstid = 0;

	GetWndManager()->HideModalWnd(false, m_wnd);
}

void CUINewGardenHandbookCollectWnd::ShowWnd(const NewGardenQuestUI& quest_info)
{
	m_quest_info = quest_info;
	RefreshRewardItem();
	Show();
}

bool CUINewGardenHandbookCollectWnd::IsShow()
{
	return m_wnd->IsShow();
}

void CUINewGardenHandbookCollectWnd::OnBtnClose(H3D_CLIENT::IUIWnd * wnd)
{
	Hide();
}

void CUINewGardenHandbookCollectWnd::OnBtnPageNext(H3D_CLIENT::IUIWnd* wnd)
{
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook_query_quest);
		getClientHall()->GetNewGardenClient()->QueryQuestInfo( m_pstid, m_quest_info.m_cur_page_id + 1);
	}
}

void CUINewGardenHandbookCollectWnd::OnBtnPagePre(H3D_CLIENT::IUIWnd * wnd)
{
	if (getClientHall()->GetNewGardenClient())
	{
		GetWndManager()->catchLock()->lock_ui(enter_handbook_query_quest);
		getClientHall()->GetNewGardenClient()->QueryQuestInfo( m_pstid, m_quest_info.m_cur_page_id - 1);
	}
}

_tstring CUINewGardenHandbookCollectWnd::RefreshQuest(UISingleItem& wndItem, const SUIReward& currentSUIReward)
{
	int type = currentSUIReward.m_type;
	if (type == 0)
	{
		return L"";
	}

	//奖励数量
	int count = currentSUIReward.m_count;

	//经验
	if (type == NSUIReward::AWARD_EXP_SMALL || type == NSUIReward::AWARD_EXP_BIG)
	{
		wndItem.m_imgRewardBack->SetToolTips(GetTChar("str_get_exp_from_pet_machine"));
		wndItem.m_imgRewardIcon->SetResourceID(NSUIReward::EXPRESID);
		wndItem.m_stItemName->SetText(GetTChar("str_get_exp_from_pet_machine"));
		wndItem.m_stRewardTime->SetText(ItoStr(count));
		return GetTChar("str_get_exp_from_pet_machine");
	}
	//G币
	if (type == NSUIReward::AWARD_G_SMALL || type == NSUIReward::AWARD_G_BIG)
	{
		wndItem.m_imgRewardBack->SetToolTips(GetTChar("str_get_G_money_from_pet_machine"));
		wndItem.m_imgRewardIcon->SetResourceID(NSUIReward::GMONEYRESID);
		wndItem.m_stItemName->SetText(GetTChar("str_get_G_money_from_pet_machine"));
		wndItem.m_stRewardTime->SetText(ItoStr(count));
		return GetTChar("str_get_G_money_from_pet_machine");
	}

	//其他类型物品的处理
	CClientItemManager* item_mng = getClientHall()->GetItemManager();
	if (item_mng)
	{
		H3D_CLIENT::UUtf8Converter iron(item_mng->GetItemIconFile(type));
		wndItem.m_imgRewardIcon->SetResourceID(iron.GetUnicode());
		H3D_CLIENT::UUtf8Converter name(item_mng->GetItemName(type));
		wndItem.m_stItemName->SetText(name.GetUnicode());

		_tstring tips;
		item_mng->GetItemToolTipsNormal(type, tips);
		if (!tips.empty())
		{
			wndItem.m_imgRewardBack->SetToolTips(tips.c_str(), 200, false);
		}

		_tstring desc = item_mng->GetItemNumTStr(type, count);
		wndItem.m_stRewardTime->SetText(desc);

		return name.GetUnicode();
	}

	return L"";
}

void CUINewGardenHandbookCollectWnd::RefreshRewardItem()
{
	m_btn_pre->ShowWindow(true);
	m_btn_next->ShowWindow(true);
	m_btn_pre->Enable();
	m_btn_next->Enable();
	std::string page = EvaluateString("str_new_garden_handbook_page", StrPair("cur", m_quest_info.m_cur_page_id), StrPair("total", m_quest_info.m_total_pages));
	m_st_page->SetCaption(H3D_CLIENT::UMConverter(page.c_str()).GetUnicode());

	if (m_quest_info.m_cur_page_id <= 1)
	{
		m_btn_pre->Disable();
	}
	if (m_quest_info.m_cur_page_id == m_quest_info.m_total_pages)
	{
		m_btn_next->Disable();
	}

	CUIBetRewardDlg* pRewardDlg = getClientHall()->GetUIHall()->GetRewardListDlg();
	if (!pRewardDlg)
	{
		return;
	}

	NewGardenQuestInfos::const_iterator iter = m_quest_info.m_quest_info.begin();
	for (int i = 0; i != EM_MaxSize; ++i)
	{
		std::vector<SUIReward> tempSUIRewards;
		UISingleItem& wndItem = m_listItem[i];
		if (iter != m_quest_info.m_quest_info.end())
		{
			wndItem.m_wndParent->ShowWindow(true);
			pRewardDlg->ConvertNew(iter->m_rewards, tempSUIRewards);
			m_listItem[i].m_imgCollect->ShowWindow(iter->m_is_finished);
			
			if (!tempSUIRewards.empty())
			{
				SUIReward& currentSUIReward = tempSUIRewards[0];
				_tstring itemName = RefreshQuest(wndItem, currentSUIReward);
				std::string str = iter->m_is_finished ? "str_new_garden_handbook_quest_finish_" : "str_new_garden_handbook_quest_";
				std::string strCondition = EvaluateString(std::string(str + ItoA(iter->m_type)).c_str(),
					StrPair("XXX", iter->m_param1), StrPair("YYY", H3D_CLIENT::UUtf8Converter(itemName.c_str()).GetUtf8()));
				m_listItem[i].m_rMessageContent->SetScript(H3D_CLIENT::UUtf8Converter(strCondition.c_str()).GetUnicode(), false);
			}

			++iter;
		}
		else
		{
			wndItem.m_wndParent->SetToolTips(L"");
			wndItem.m_imgRewardIcon->SetResourceID(L"");
			wndItem.m_stRewardTime->SetText(L"");
			wndItem.m_wndParent->ShowWindow(false);
		}
	}
}
