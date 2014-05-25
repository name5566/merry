#ifndef _MERRY_HOTKEY_ALL_H_
#define _MERRY_HOTKEY_ALL_H_

#include "MerryHotkey.h"

#ifdef MERRY_HOTKEY_ALL

#include <map>

class MerryHotkeyAll : public MerryHotkey, private wxTimer
{
public:
	MerryHotkeyAll();

private:
	virtual bool OnRegisterHotkey(int commandID, int modifiers, int keyCode);
	virtual void OnUnregisterHotkey(int commandID);

private:
	virtual void Notify();

private:
	struct Hotkey {
		int modifiers;
		int keyCode;
	};

	typedef std::map<int, Hotkey> HotkeyMap;
	HotkeyMap m_hotkeys;
	Hotkey m_lastHotkey;
};

#endif

#endif
