#ifndef _MERRY_COMMAND_MANAGER_H_
#define _MERRY_COMMAND_MANAGER_H_

#include "MerryCommand.h"
#include <vector>

typedef std::vector<MerryCommand*> MerryCommandArray;

class MerryCommandManager
{
public:
	~MerryCommandManager();

	const MerryCommand* AddCommand(const wxString& commandName, int funcRef, const wxString& triggerKey);
	const MerryCommand* GetCommand(int commandID) const;
	MerryCommandArray Collect(const wxString& commandPrefix) const;

private:
	MerryCommandArray m_commands;
};

extern MerryCommandManager* g_commands;

#endif
