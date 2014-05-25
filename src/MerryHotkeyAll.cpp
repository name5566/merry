#include "MerryHotkeyAll.h"

#ifdef MERRY_HOTKEY_ALL

#include "MerryKey.h"

MerryHotkey* NewMerryHotkey()
{
	return new MerryHotkeyAll();
}

MerryHotkeyAll::MerryHotkeyAll()
{
	m_lastHotkey.modifiers = 0;
	m_lastHotkey.keyCode = 0;

	this->Start(10);
}

bool MerryHotkeyAll::OnRegisterHotkey(int commandID, int modifiers, int keyCode)
{
	HotkeyMap::const_iterator it = m_hotkeys.begin();
	for (; it != m_hotkeys.end(); ++it) {
		const Hotkey& hotkey = it->second;
		if (hotkey.modifiers == modifiers && hotkey.keyCode == keyCode)
			return false;
	}

	Hotkey newHotkey;
	newHotkey.modifiers = modifiers;
	newHotkey.keyCode = keyCode;
	return m_hotkeys.insert(std::make_pair(commandID, newHotkey)).second;
}

void MerryHotkeyAll::OnUnregisterHotkey(int commandID)
{
	m_hotkeys.erase(commandID);
}

void MerryHotkeyAll::Notify()
{
	// wxMOD_WIN wxMOD_META not support yet
	int modifiers = 0;
	if (::wxGetKeyState(WXK_ALT))
		modifiers |= wxMOD_ALT;
	if (::wxGetKeyState(WXK_RAW_CONTROL))
		modifiers |= wxMOD_CONTROL;
	if (::wxGetKeyState(WXK_SHIFT))
		modifiers |= wxMOD_SHIFT;

	int keyCode = 0;
	for (int i=32; i<=127; ++i) {
		if (::wxGetKeyState((wxKeyCode)i)) {
			keyCode = i;
			break;
		}
	}

	if (m_lastHotkey.modifiers == modifiers && m_lastHotkey.keyCode == keyCode)
		return;
	m_lastHotkey.modifiers = 0;
	m_lastHotkey.keyCode = 0;

	HotkeyMap::const_iterator it = m_hotkeys.begin();
	for (; it != m_hotkeys.end(); ++it) {
		const Hotkey& hotkey = it->second;
		if (hotkey.modifiers == modifiers && hotkey.keyCode == keyCode) {
			this->OnTriggerKey(it->first);
			m_lastHotkey = hotkey;
			break;
		}
	}
}

#endif
