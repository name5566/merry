#include "MerryCommandManager.h"
#include "MerryError.h"

MerryCommandManager* g_commands = NULL;

MerryCommandManager::~MerryCommandManager()
{
	for (size_t i=0; i<m_commands.size(); ++i)
		delete m_commands[i];
}

const MerryCommand* MerryCommandManager::AddCommand(const wxString& commandName, int funcRef, const wxString& triggerKey)
{
	if (commandName.empty() && triggerKey.empty())
	{
		::MerrySetLastError(wxT("Command name and key not found"));
		return NULL;
	}
	for (size_t i=0; i<m_commands.size(); ++i)
	{
		const MerryCommand* command = m_commands[i];
		assert(command);
		if (!commandName.empty() && commandName.IsSameAs(command->GetCommandName(), false))
		{
			::MerrySetLastError(wxString::Format(wxT("Command name %s already exists"), commandName));
			return NULL;
		}
		if (!triggerKey.empty() && triggerKey.IsSameAs(command->GetTriggerKey(), false))
		{
			::MerrySetLastError(wxString::Format(wxT("Command key %s already exists"), triggerKey));
			return NULL;
		}
	}

	MerryCommand* command = new MerryCommand(m_commands.size(), commandName, funcRef, triggerKey);
	m_commands.push_back(command);
	return command;
}

const MerryCommand* MerryCommandManager::GetCommand(int commandID) const
{
	if (commandID >= (int)m_commands.size() || commandID < 0)
		return NULL;
	assert(m_commands[commandID]);
	return m_commands[commandID];
}

MerryCommandArray MerryCommandManager::Collect(const wxString& commandPrefix) const
{
	MerryCommandArray commands;
	for (size_t i=0; i<m_commands.size(); ++i)
	{
		MerryCommand* command = m_commands[i];
		assert(command);
		const wxString& commandName = command->GetCommandName();
		if (commandName.empty())
			continue;
		if (commandName.size() < commandPrefix.size())
			continue;
		if (commandName.Upper().compare(0, commandPrefix.size(), commandPrefix.Upper()) == 0)
			commands.push_back(command);
	}

	return commands;
}
