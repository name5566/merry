#include "MerryTaskBarIcon.h"
#include "MerryApp.h"
#include "MerryInformationDialog.h"

enum
{
	MENU_ITEM_OPEN = 10001,
	MENU_ITEM_CONFIG,
	MENU_ITEM_ABOUT,
	MENU_ITEM_EXIT,
};

BEGIN_EVENT_TABLE(MerryTaskBarIcon, wxTaskBarIcon)
	EVT_MENU(MENU_ITEM_OPEN, MerryTaskBarIcon::OnOpenEvent)
	EVT_MENU(MENU_ITEM_CONFIG, MerryTaskBarIcon::OnConfigEvent)
	EVT_MENU(MENU_ITEM_ABOUT, MerryTaskBarIcon::OnAboutEvent)
	EVT_MENU(MENU_ITEM_EXIT, MerryTaskBarIcon::OnExitEvent)
	EVT_TASKBAR_LEFT_DCLICK(MerryTaskBarIcon::OnLeftButtonDClickEvent)
END_EVENT_TABLE()

wxMenu* MerryTaskBarIcon::CreatePopupMenu()
{
	wxMenu* menu = new wxMenu;

	menu->Append(MENU_ITEM_OPEN, wxT("&Open Merry(O)"));
	menu->Append(MENU_ITEM_CONFIG, wxT("&Reload Configuration(R)"));
	menu->Append(MENU_ITEM_ABOUT, wxT("&About Merry(A)"));
	menu->Append(MENU_ITEM_EXIT, wxT("E&xit(X)"));

	return menu;
}

void MerryTaskBarIcon::OnOpenEvent(wxCommandEvent& e)
{
	::wxGetApp().GetFrame().Show();
}

void MerryTaskBarIcon::OnConfigEvent(wxCommandEvent& e)
{
	::wxGetApp().NewFrame();
}

void MerryTaskBarIcon::OnAboutEvent(wxCommandEvent& e)
{
	new MerryInformationDialog(wxT("About Merry"), wxT("version 1.0.0 --- http://name5566.com"));
}

void MerryTaskBarIcon::OnExitEvent(wxCommandEvent& e)
{
	::wxGetApp().GetFrame().Close();
}

void MerryTaskBarIcon::OnLeftButtonDClickEvent(wxTaskBarIconEvent& e)
{
	::wxGetApp().GetFrame().Show();
	e.Skip();
}
