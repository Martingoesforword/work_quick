#pragma once
#include "..\..\UIBase.h"
#include "modules\new_garden\share\new_garden_shared_info.h"
#include "modules\new_garden\share\new_garden_quest_info.h"
#include "..\..\..\IUIPopupInterface.h"

class CUINewgardenRewardData : public IUIPopupData
{
public:
	CUINewgardenRewardData() {}
	virtual ~CUINewgardenRewardData() {}

public:
	RewardBasicItems rewards;
};

//奖励弹框
class CUINewgardenRewardWnd : public CUIBase, public IUIPopupBase
{
public:
	CUINewgardenRewardWnd();
	virtual ~CUINewgardenRewardWnd();
	void ShowWnd(const std::string& title, const RewardBasicItems& rewards);
	void ShowWnd(const std::string& first_title, const std::string& title, const RewardBasicItems& rewards);
public:
	// 判断当前窗口是否处于显示状态
	virtual bool IsPopupShow();

	// 判断是否能够进行显示
	virtual bool CanPopupShow();

	// 显示弹窗
	virtual bool ShowPopupWnd(IUIPopupData* data);
private:
	H3D_CLIENT::IUIButton* m_btn_close;
	H3D_CLIENT::IUIButton* m_btn_pre;
	H3D_CLIENT::IUIButton* m_btn_next;
	H3D_CLIENT::IUIButton* m_btn_confirm;
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnNext(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnPre(H3D_CLIENT::IUIWnd* wnd);

	struct SRewardItem
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIImage* m_img_icon;
		H3D_CLIENT::IUIStaticText* m_st_name;
	};

	enum 
	{
		CNRW_REWARD_NUM_PER_PAGE = 6, //一页显示的奖励数量
	};
	std::vector<SRewardItem> m_vec_ui_rewards;
	H3D_CLIENT::IUIRichEditBox* m_rt_con;
	H3D_CLIENT::IUIStaticText* m_st_title;
	int m_begin_page_index;
	RewardBasicItems m_vec_rewards_data;
	void RefreshWnd();
	virtual void OnShow();
	virtual void OnHide();
};

//故事弹窗
class CUINewgardenStoryDetail : public CUIBase
{
public:
	CUINewgardenStoryDetail();
	virtual ~CUINewgardenStoryDetail();
	void ShowWnd(const std::string& name, const std::string& uir_id, const std::string& con);
private:
	H3D_CLIENT::IUIWnd* m_img_app;
	H3D_CLIENT::IUIStaticText* m_st_name;
	H3D_CLIENT::IUIRichEditBox* m_rt_con;
	H3D_CLIENT::IUIButton* m_btn_confirm;
	H3D_CLIENT::IUIButton* m_btn_close;
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	virtual void OnShow();
	virtual void OnHide();
};
struct BBDetailData
{
	int m_effect_id;
	std::string m_name;
	std::string m_describe;
};
//宝宝弹窗
class CUINewgardenBBDetail : public CUIBase
{
public:
	CUINewgardenBBDetail();
	virtual ~CUINewgardenBBDetail();
	void RefreshUIData(const BBDetailData& uidata);
	void ShowWnd();
private:
	H3D_CLIENT::IUIImage* m_img_bb;
	H3D_CLIENT::IUIButton* m_btn_ok;
	H3D_CLIENT::IUIStaticText* m_st_0;
	H3D_CLIENT::IUIRichEditBox* m_rt_0;
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	virtual void OnShow();
	virtual void OnHide();
};
class CUINewgardenHandbookDetail : public CUIBase
{
public:
	CUINewgardenHandbookDetail();
	virtual ~CUINewgardenHandbookDetail();
	void OnBtnPre(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnNext(H3D_CLIENT::IUIWnd* wnd);
	void ShowWnd(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& info, const NewGardenHandBookTabsSetCollectionSimpleInfos& coll_infos);
	void ParseUIInfo(const NewGardenHandBookSetCollectionResInfo& info);
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	//刷新动物图片
	void RefreshAnimalImg(const string& img);

	//预览是隐藏的部分控件
	void hideSomeShow();
	enum 
	{
		CNHDNT_INVALID = -1,
		CNHDNT_SPECIAL_IMG,	//特殊标记
		CNHDNT_CHEST,		//宝箱
		CNHDNT_CARTOON,		//漫画
	};

	struct SProgressNodeInitData
	{
		float m_ratio;
		float m_cur_heart_value;
		int m_type;
		RewardBasicItems m_rewards;
		int m_state;
		SProgressNodeInitData()
			: m_ratio(0.0)
			, m_type(CNHDNT_INVALID)
			, m_cur_heart_value(0.0)
		{

		}
	};
	struct SStoryNodeData
	{
		char m_collector_type;	// NewGardenMoodRewardType
		std::string m_str_name;
		std::string m_str_con;
		std::string m_str_uir_id;
		SStoryNodeData()
			: m_str_name("")
			, m_str_con("")
			, m_str_uir_id("")
			, m_collector_type(NGMRT_Invalid)
		{

		}
	};
	struct SWndInitData
	{
		int m_rarity_type;
		int m_heart_level;
		int m_heart_progress;
		int m_animal_id;
		std::vector<SProgressNodeInitData> m_node_data;
		std::vector<SStoryNodeData> m_story_nodes;
		std::string m_str_chara;
		std::string m_str_coll_way;
		std::string m_str_coll_num;
		bool m_is_collected;
		std::string m_str_app;
		std::string m_str_name;
		int m_att_dif;
		bool m_can_wander;
		bool m_has;
		bool m_is_max_mod;
		float m_progress_ratio;
		SWndInitData()
			: m_heart_level(0)
			, m_heart_progress(0)
			, m_animal_id(-1)
			, m_str_chara("")
			, m_str_coll_num("")
			, m_str_coll_way("")
			, m_att_dif(-1)
			, m_can_wander(false)
			, m_has(false)
			, m_is_max_mod(false)
			, m_progress_ratio(0.0f)
			, m_is_collected(false)
		{

		}
		void Reset()
		{
			m_node_data.clear();
			m_story_nodes.clear();
			m_rarity_type = 0;
			m_heart_level = 0;
			m_heart_progress = 0;
			m_animal_id = -1;
			m_str_chara = "";
			m_str_coll_way = "";
			m_str_coll_num = "";
			m_str_app = "";
			m_str_name = "";
			m_att_dif = -1;
			m_can_wander = false;
			m_has = false;
		}
	};

	
private:
	SWndInitData m_ui_data;
	BBDetailData m_ui_bb_data;
	void RefreshWnd();
	H3D_CLIENT::IUIButton* m_btn_pre;
	H3D_CLIENT::IUIButton* m_btn_next;
	H3D_CLIENT::IUIButton* m_btn_close;
	struct SAppWnd
	{
		H3D_CLIENT::IUIImage* m_img_rarity;
		H3D_CLIENT::IUIImage* m_img_app;
		H3D_CLIENT::IUIImage* m_img_app_bb;
		H3D_CLIENT::IUIStaticText* m_st_name;
		H3D_CLIENT::IUIImage* m_img_app_bk;
	};
	SAppWnd m_app_wnd;
	struct SProgressNodeItem
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIStaticText* m_st_value;
		H3D_CLIENT::IUIImage* m_img;
		H3D_CLIENT::IUIButton* m_btn;
	};
	
	//进度条
	enum 
	{
		CNHD_STORY_NODE_COUNT = 5, //心情触发节点的最大数量
	};
	struct SProgressNodeWnd
	{
		H3D_CLIENT::IUIStaticText* m_st_level;
		H3D_CLIENT::IUIImage* m_img_progress;
		H3D_CLIENT::IUIStaticText* m_st_progress;
		std::vector<SProgressNodeItem> m_vec_node;
	};
	SProgressNodeWnd m_progress_wnd;
	//获取难度
	enum 
	{
		CNHD_ATT_DIF_COUNT = 5, //吸引难度等级
	};
	struct SAttDifWnd
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		std::vector<H3D_CLIENT::IUIImage*> m_vec_diff_img;
	};
	SAttDifWnd m_att_dif_wnd;

	//故事按钮节点
	struct SStoryItemWnd
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIButton* m_btn;
		H3D_CLIENT::IUIImage* m_img;
	};
	std::vector<SStoryItemWnd> m_story_wnds;
	void OnBtnStory(H3D_CLIENT::IUIWnd* wnd);
	H3D_CLIENT::IUIRichEditBox* m_rt_chara;
	H3D_CLIENT::IUIRichEditBox* m_rt_coll_way;
	H3D_CLIENT::IUIRichEditBox* m_rt_coll_num;
	H3D_CLIENT::IUIButton* m_btn_bb_detail;
	H3D_CLIENT::IUIImage* m_img_bb_detail;
	void OnBtnDetail(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnChest(H3D_CLIENT::IUIWnd* wnd);

	H3D_CLIENT::IUIImage* m_img_stamp;

	CUINewgardenRewardWnd m_reward_wnd;
	struct SIDData
	{
		int64 m_pstid;
		int m_set_id;
		int m_id;
		int m_tab_id;
		int m_pre_id;
		int m_next_id;
		SIDData()
			: m_pstid(0)
			, m_set_id(0)
			, m_id(0)
			, m_tab_id(0)
			, m_pre_id(0)
			, m_next_id(0)
		{

		}
	};
	SIDData m_id_data;

	CUINewgardenStoryDetail m_wnd_story_detail;
	CUINewgardenBBDetail m_wnd_bb_detail;
	virtual void OnShow();
	virtual void OnHide();
};

class CUINewGardenHandbookSet : public CUIBase
{
public:
	CUINewGardenHandbookSet();
	virtual ~CUINewGardenHandbookSet();
	enum
	{
		CNGHS_CAT_ITEM_NUM_PER_PAGE = 8,//单页显示集合数目
		CNGHS_CHEST_NUM = 5,//宝箱个数
	};

	//数据类
	struct UISetSingleItemData
	{
		int m_rarity;
		std::string m_name;
		int m_id;
		int m_effect_id;
		bool m_is_collected_full;
		bool m_has;
		UISetSingleItemData()
			: m_rarity(0)
			, m_name("")
			, m_has(false)
			, m_effect_id(0)
			, m_is_collected_full(false)
		{

		}
	};

	//进度条
	enum
	{
		CNGHS_INVALID = -1,
		CNGHS_INACTIVE,		//未解锁
		CNGHS_GET,			//已领取
		CNGHS_ACTIVE,		//已解锁
		
		CNGHS_NUM,
	};

	struct SSingleProgressItem
	{
		H3D_CLIENT::CLPoint m_pos;
		int m_state;
		int m_num;
		int m_id;
		RewardBasicItems m_rewards;
		SSingleProgressItem()
			: m_state(CNGHS_INVALID)
			, m_num(0)
			, m_id(0)
		{

		}
	};

	struct SProgressWndData
	{
		int m_cur_num;
		int m_max_num;
		std::vector<SSingleProgressItem> m_vec_node;
		float m_cur_ratio;
		SProgressWndData()
			: m_cur_num(0)
			, m_max_num(0)
			, m_cur_ratio(0.0)
		{
			m_vec_node.clear();
		}
		void Reset()
		{
			m_cur_num = 0;
			m_max_num = 0;
			m_cur_ratio = 0.0f;
			m_vec_node.clear();
		}
	};

	struct UIHandbookSetWndData
	{
		std::vector<UISetSingleItemData> m_vec_data;
		SProgressWndData m_progress_data;
		std::string m_set_name;
		UIHandbookSetWndData()
		{

		}
		void Reset()
		{
			m_vec_data.clear();
			m_progress_data.Reset();
		}
	};

	UIHandbookSetWndData m_cur_page_data; //两种类型的数据

										  //表现类
	struct UIHandebookSetSingleItem
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIImage* m_img_icon;
		H3D_CLIENT::IUIImage* m_imgbb;
		H3D_CLIENT::IUIImage* m_img_rarity;
		H3D_CLIENT::IUIStaticText* m_st_name;
		H3D_CLIENT::IUICheckBox* m_cb_enter;
	};

	struct SProgressWndItem
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIButton* m_btn;
		H3D_CLIENT::IUIStaticText* m_st_num;
		H3D_CLIENT::IUIEffectWnd* m_eff;
	};

	struct SCollProgressWnd
	{
		H3D_CLIENT::IUIStaticText* m_st_progress;
		H3D_CLIENT::IUIImage* m_img_progress;
		std::vector<SProgressWndItem> m_vec_item;
		H3D_CLIENT::IUIWnd* m_wnd;
	};
	void ShowCollDetailWnd(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& res_info);
	void ShowWnd(int64 target_pstid, const NewGardenHandBookTabsSetDetailInfo& res_info);
	void OnTakeProgressReward(const NewGardenHandBookTabsSetRewardResInfo& res_info);
	void OnTakeQuestReward(const RewardBasicItems& rewards);
	void RefreshWndInfo();
	CUINewgardenRewardWnd* getRewardWnd() {return &m_reward_wnd;}
private:
	SCollProgressWnd m_progress_wnd;
	H3D_CLIENT::IUIButton* m_btn_pre;
	H3D_CLIENT::IUIButton* m_btn_next;
	H3D_CLIENT::IUIStaticText* m_st_page;
	H3D_CLIENT::IUIButton* m_btn_close;
	int m_begin_page_index;
	std::vector<UIHandebookSetSingleItem> m_vec_ui;
	int64 m_pstid;
	void ParseUIInfo(const NewGardenHandBookTabsSetDetailInfo& res_info);
	void RefreshPageWnd();
	void OnBtnPage(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnChest(H3D_CLIENT::IUIWnd* wnd);
	void OnCBDetail(H3D_CLIENT::IUIWnd* wnd);
	virtual void OnShow();
	virtual void OnHide();
	//奖励窗口
	CUINewgardenRewardWnd m_reward_wnd;
	CUINewgardenHandbookDetail m_wnd_coll_detail;
	NewGardenHandBookTabsSetCollectionSimpleInfos m_coll_infos;
	int m_tab_id;
	int m_set_id;
	H3D_CLIENT::IUIStaticText* m_st_title;
};

class CUINewGardenHandbookCollectWnd;

class CUINewGardenHandbookMainWnd : public CUIBase
{
public:
	CUINewGardenHandbookMainWnd();
	virtual ~CUINewGardenHandbookMainWnd();
	void ShowCatWnd(int type);
	void RequestShowWnd(int64 pstid);
	void ShowWnd(const NewGardenHandBookTabsInfo& res_info);
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnPage(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnCollectReward(H3D_CLIENT::IUIWnd* wnd);
	void OnCBCat(H3D_CLIENT::IUIWnd* wnd);
	void ParseTabInfo(const NewGardenHandBookTabsInfo& res_info);
	void RefreshCollect(const NewGardenHandBookTabsInfo& Info);
	void RefreshTabWnd();
	void OnCBEnterSet(H3D_CLIENT::IUIWnd* wnd);
	void ShowCollDetailInfo(int64 target_pstid, const NewGardenHandBookSetCollectionResInfo& res_info);
	void ShowHandbookSetInfo(int64 target_pstid, const NewGardenHandBookTabsSetDetailInfo& res_info);
	void OnTakeProgressReward(const NewGardenHandBookTabsSetRewardResInfo& res_info);
	void OnTakeQuestReward(const RewardBasicItems& rewards);
	bool IsShow();
	void RequstCurTabInfo();
	void RefreshHandbookSet();
	CUINewGardenHandbookCollectWnd* getCollectUI(bool ForceCreate = true);
	CUINewgardenRewardWnd* getRewardWnd() {return m_wnd_coll_set.getRewardWnd();}
	std::vector<CUINewgardenRewardData*> getRewardCache() { return m_vecRewardCache; }
	void clearRewardCache() { m_vecRewardCache.clear(); }
private:
	enum 
	{
		CNGHMW_CAT_ANI = 0, //动物类别
		CNGHMW_CAT_PARTENER,//伙伴类别
		CNGHMW_CAT_NUM, 
	};

	enum 
	{
		CNGHMW_CAT_ITEM_NUM_PER_PAGE = 6,//单页显示集合数目
	};

	//数据类
	struct UIMainWndSingleItemData
	{
		int m_collect_effect_num;
		int m_has_num;
		int m_total;
		std::string m_name;
		int m_id;
		bool m_has_reward;
		bool m_has_new_animal;
		UIMainWndSingleItemData()
			: m_collect_effect_num(0)
			, m_has_num(0)
			, m_total(0)
			, m_name("")
			, m_has_reward(false)
			, m_has_new_animal(false)
		{

		}
	};

	struct UIMainWndData
	{
		int m_max_page;
		int m_cur_page;
		int m_cur_tab_type;
		std::vector<bool> m_has_cat_rewards;
		std::vector<bool> m_has_new_animal;
		std::vector<UIMainWndSingleItemData> m_vec_data;
		UIMainWndData()
			: m_max_page(0)
			, m_cur_page(0)
			, m_cur_tab_type(CNGHMW_CAT_ANI)
		{

		}
		void Reset()
		{
			m_vec_data.clear();
			m_max_page = 0;
			m_cur_page = 0;
			m_has_cat_rewards.resize(CNGHMW_CAT_NUM, false);
			m_has_new_animal.resize(CNGHMW_CAT_NUM,false);
		}
	};

	UIMainWndData m_cur_mainwnd_page_data; //两种类型的数据

	//表现类
	struct UIMainWndSingleItem
	{
		H3D_CLIENT::IUIWnd* m_wnd;
		H3D_CLIENT::IUIImage* m_img;
		H3D_CLIENT::IUIStaticText* m_st_has;
		H3D_CLIENT::IUIStaticText* m_st_name;
		H3D_CLIENT::IUICheckBox* m_cb_enter;
		H3D_CLIENT::IUIEffectWnd* m_eff_has;
		H3D_CLIENT::IUIImage* m_img_full;
		H3D_CLIENT::IUIImage* m_img_tips;			//红点提示
		H3D_CLIENT::IUIImage* m_img_box;			//礼盒
		H3D_CLIENT::IUIButton* m_btn_box;			//礼盒
	};
	H3D_CLIENT::IUIButton* m_btn_pre;
	H3D_CLIENT::IUIButton* m_btn_next;
	H3D_CLIENT::IUIStaticText* m_st_page;
	//收集进度
	H3D_CLIENT::IUIStaticText* m_stCollectAnimal;
	H3D_CLIENT::IUIStaticText* m_stCollectR;
	H3D_CLIENT::IUIStaticText* m_stCollectSR;
	H3D_CLIENT::IUIStaticText* m_stCollectSSR;
	H3D_CLIENT::IUIStaticText* m_stCollectBaby;
	std::vector<H3D_CLIENT::IUICheckBox*> m_vec_cb_cat;
	std::vector<H3D_CLIENT::IUIImage*> m_vec_img_cat;
	H3D_CLIENT::IUIButton* m_btn_close;
	H3D_CLIENT::IUIButton* m_btnCollectReward;
	std::vector<UIMainWndSingleItem> m_vec_ui;
	std::vector<CUINewgardenRewardData*> m_vecRewardCache;	// 任务奖励缓存
	virtual void OnShow();
	virtual void OnHide();

	int64 m_pstid;
	CUINewGardenHandbookSet m_wnd_coll_set;

	NewGardenHandBookTabsInfo m_tab_info; //主界面服务器回传的消息

	CUINewGardenHandbookCollectWnd* m_collectWnd;
};


class CUINewGardenHandbookCollectWnd : public CUIBase
{
public:
	CUINewGardenHandbookCollectWnd();
	virtual ~CUINewGardenHandbookCollectWnd();
	void ShowWnd(const NewGardenQuestUI& quest_info);
	void SetPstid(int64 pstid) { m_pstid = pstid;}
	bool IsShow();
	void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnPageNext(H3D_CLIENT::IUIWnd* wnd);
	void OnBtnPagePre(H3D_CLIENT::IUIWnd* wnd);
private:
	void RefreshRewardItem();

	enum
	{
		EM_MaxSize = 4,
	};

	H3D_CLIENT::IUIWnd* m_wnd;				///< 主窗口
	H3D_CLIENT::IUIButton* m_btnClose;		///< 关闭按钮
	H3D_CLIENT::IUIButton* m_btn_pre;
	H3D_CLIENT::IUIButton* m_btn_next;
	H3D_CLIENT::IUIStaticText* m_st_page;
	H3D_CLIENT::IUIWnd* m_wndMessage;				

	//表现类
	struct UISingleItem
	{
		H3D_CLIENT::IUIWnd* m_wndParent;
		H3D_CLIENT::IUIRichEditBox*		m_rMessageContent;			//显示内容
		H3D_CLIENT::IUIImage*			m_imgCollect;				//收集图标
		H3D_CLIENT::IUIImage*			m_imgRewardBack;			//奖励图标背景
		H3D_CLIENT::IUIImage*			m_imgRewardIcon;			//奖励图标
		H3D_CLIENT::IUIStaticText*		m_stItemName;				//道具名称
		H3D_CLIENT::IUIStaticText*		m_stRewardTime;				//奖励数量/时效	
	};
	UISingleItem m_listItem[EM_MaxSize];

	NewGardenQuestUI m_quest_info;				// 数据
	int64 m_pstid;

	virtual void OnShow();
	virtual void OnHide();
	_tstring RefreshQuest(UISingleItem& listItem, const SUIReward& currentSUIReward);

};