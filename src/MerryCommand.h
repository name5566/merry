#ifndef _MERRY_COMMAND_H_
#define _MERRY_COMMAND_H_

#include "MerryWx.h"

class MerryCommand
{
public:
	MerryCommand(int commandID, const wxString& commandName, int funcRef, const wxString& triggerKey);
	~MerryCommand();

	int GetCommandID() const { return m_commandID; }
	const wxString& GetCommandName() const { return m_commandName; }
	const wxString& GetTriggerKey() const { return m_triggerKey; }

	void ExecuteCommand(const wxString& commandArg) const;

private:
	int m_commandID;
	wxString m_commandName;
	int m_commandFunc;
	wxString m_triggerKey;
};

#endif
