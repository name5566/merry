#include "MerryTextCtrl.h"
#include "MerryConfig.h"
#include "MerryCommandManager.h"
#include "MerryHelper.h"
#include "MerryLua.h"
#include "MerryApp.h"
#include "MerryListBoxPanel.h"

#ifdef __WXOSX__
#include "MerryMacHelper.h"
#endif

BEGIN_EVENT_TABLE(MerryTextCtrl, wxTextCtrl)
	EVT_KEY_DOWN(MerryTextCtrl::OnKeyDownEvent)
#ifdef __WXGTK__
	EVT_IDLE(MerryTextCtrl::OnIdleEvent)
#else
	EVT_TEXT(wxID_ANY, MerryTextCtrl::OnTextEvent)
#endif
END_EVENT_TABLE()

MerryTextCtrl::MerryTextCtrl(wxWindow* parent):
	wxTextCtrl(parent, wxID_ANY, wxEmptyString,
		wxPoint(MERRY_DEFAULT_TEXT_CTRL_LEFT, MERRY_DEFAULT_TEXT_CTRL_TOP),
		wxSize(MERRY_DEFAULT_TEXT_CTRL_WIDTH, MERRY_DEFAULT_TEXT_CTRL_HEIGHT),
		wxWANTS_CHARS | wxBORDER_NONE
	)
{
#ifdef __WXOSX__
	MerryDisableFocusRing(this->GetHandle());
#endif

#ifdef __WXGTK__
	m_needCompletion = false;
#endif

	if (MERRY_DEFAULT_TEXT_CTRL_FONT_HEIGHT)
	{
		wxFont font = this->GetFont();
		font.SetPixelSize(wxSize(0, MERRY_DEFAULT_TEXT_CTRL_FONT_HEIGHT));
		this->SetOwnFont(font);
	}
}

void MerryTextCtrl::OnKeyDownEvent(wxKeyEvent& e)
{
	int keyCode = e.GetKeyCode();
	m_lastKeyDownCode = keyCode;

	switch (keyCode)
	{
	case WXK_RETURN:
	case WXK_NUMPAD_ENTER:
		{
			wxString commandStr = this->GetValue();
			::wxGetApp().GetFrame().Hide();

			if (commandStr.IsEmpty())
				break;
			wxString commandName, commandArg;
			::MerryParseCommandStr(commandStr, commandName, commandArg);
			MerryCommandArray commands = g_commands->Collect(commandName);
			if (commands.size() > 0)
				commands[0]->ExecuteCommand(commandArg);
			else
				g_lua->OnUndefinedCommand(commandName, commandArg);
		}
		break;
	case WXK_ESCAPE:
		::wxGetApp().GetFrame().Hide();
		break;
	case WXK_DOWN:
	case WXK_UP:
		this->AutoCompletion(keyCode);
#ifdef __WXGTK__
		m_lastValue = this->GetValue();
#endif
		break;
	case WXK_TAB:
		this->AppendText(wxT(" "));
#ifdef __WXGTK__
		m_needCompletion = true;
#endif
		break;
	default:
#ifdef __WXGTK__
		m_needCompletion = true;
#endif
		e.Skip();
		break;
	}
}

#ifdef __WXGTK__
void MerryTextCtrl::OnIdleEvent(wxIdleEvent& e)
{
	if (!m_needCompletion)
		return;
	const wxString& value = this->GetValue();
	if (m_lastValue == value)
		return;

	this->AutoCompletion(m_lastKeyDownCode);

	m_needCompletion = false;
	m_lastValue = value;
}
#else
void MerryTextCtrl::OnTextEvent(wxCommandEvent& e)
{
	this->AutoCompletion(m_lastKeyDownCode);
}
#endif

void MerryTextCtrl::AutoCompletion(int keyCode)
{
	MerryListBoxPanel* listBoxPanel = ::wxGetApp().GetFrame().GetListBoxPanel();
	assert(listBoxPanel);

	long from, to;
	this->GetSelection(&from, &to);
	wxString name = this->GetValue();
	if (from != to)
		name.Truncate(from);

	if (listBoxPanel->IsPopup() && keyCode == WXK_DOWN)
		listBoxPanel->SelectNext();
	else if (listBoxPanel->IsPopup() && keyCode == WXK_UP)
		listBoxPanel->SelectPrev();
	else
	{
		MerryCommandArray commands = g_commands->Collect(name);
		listBoxPanel->SetCommandArray(commands);
		if (commands.size() == 0)
		{
			listBoxPanel->Dismiss();
			return;
		}
		listBoxPanel->Popup();
	}

	// Auto completion
	if (keyCode != WXK_BACK && keyCode != WXK_DELETE)
	{
		const MerryCommand* command = listBoxPanel->GetSelectionCommand();
		const wxString& commandName = command->GetCommandName();
		this->ChangeValue(commandName);
		this->SetSelection(name.size(), commandName.size());
	}
}
