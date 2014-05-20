addCommand{ key = 'A-R', func = toggleMerry }

addCommand{ key = 'A-M', func = function()
	local window = getForegroundWindow()
	if isWindowMax(window) then
		showWindow(window, 'restore')
	else
		showWindow(window, 'max')
	end
end }

addCommand{ key = 'A-Q', func = function()
	closeWindow(getForegroundWindow())
end }

local curHideWindow
addCommand{ key = 'A-H', func = function()
    if not curHideWindow then
        curHideWindow = getForegroundWindow()
        showWindow(curHideWindow, 'hide')
    else
        showWindow(curHideWindow, 'normal')
        curHideWindow = nil
    end
end }

if WINDOWS then
	for i = string.byte('a'), string.byte('z') do
		local disk = string.char(i)
		local isOk, errMsg = io.open(disk .. ':')
		if isOk or errMsg:find('Permission denied') then
			addCommand{ command = disk, func = function() shellExecute(disk .. ':', '', '', 'max') end }
		end
	end

	addCommand{ command = 'computer', func = function() shellExecute('::{20D04FE0-3AEA-1069-A2D8-08002B30309D}', '', '', 'max') end }
	addCommand{ command = 'merry', func = function() shellExecute('explorer', '.', '', 'max') end }
	addCommand{ command = 'ip', func = function() shellExecute('cmd', '/K ipconfig') end }
	addCommand{ command = 'ping', func = function(str) shellExecute('cmd', '/K ping ' .. str) end }

	addCommand{ command = 'cmd', key = 'A-T', func = function(arg)
		local window = getForegroundWindow()
		local dir = getWindowText(window)
		shellExecute('cmd', '', dir)
	end }

	addCommand{ key = 'A-Up', func = function() shellExecute('nircmdc', 'changesysvolume 65535', '', 'hide') end }
	addCommand{ key = 'A-Down', func = function() shellExecute('nircmdc', 'changesysvolume -65535', '', 'hide') end }
	addCommand{ key = 'A-Left', func = function() shellExecute('nircmdc', 'changesysvolume -4000', '', 'hide') end }
	addCommand{ key = 'A-Right', func = function() shellExecute('nircmdc', 'changesysvolume 4000', '', 'hide') end }
elseif MAC then
	addCommand{ command = 'terminal', key = 'A-T', func = function() shellExecute('/Applications/Utilities/terminal.app') end }
end

addCommand{ command = 'google', func = function(str) shellExecute('http://www.google.com.hk/search?q=' .. str) end }
addCommand{ command = 'googlecode', func = function(str) shellExecute('http://code.google.com/query/#q=' .. str) end }
addCommand{ command = 'baidu', func = function(str) shellExecute('http://www.baidu.com/s?wd=' .. str) end }
addCommand{ command = 'youku', func = function(str) shellExecute('http://www.soku.com/search_video/q_' .. str) end }
addCommand{ command = 'doubanbook', func = function(str) shellExecute('http://book.douban.com/subject_search?search_text=' .. str) end }
addCommand{ command = 'doubanmovie', func = function(str) shellExecute('http://movie.douban.com/subject_search?search_text=' .. str) end }
addCommand{ command = 'name5566', func = function(str) shellExecute('http://name5566.com/?s=' .. str) end }
addCommand{ command = 'dict', func = function(str) shellExecute('http://dict.cn/' .. str) end }

-- Events
local histroy = io.open(MERRY_ROOT_PATH .. 'histroy.lua', 'a')
addEventHandler('onUndefinedCommand', function(commandName, commandArg)
	local commandNameArray = { commandName }
	if MAC then
		table.insert(commandNameArray, "/Applications/" .. commandName .. ".app")
		table.insert(commandNameArray, "/Applications/Utilities/" .. commandName .. ".app")
	end

	for _, commandNameFull in ipairs(commandNameArray) do
		if shellExecute(commandNameFull, commandArg) then
			addCommand{ command = commandName, func = function() shellExecute(commandNameFull) end }
			local strCommandName = string.gsub(commandName, '\\', '\\\\')
			local strCommandNameFull = string.gsub(commandNameFull, '\\', '\\\\')
			histroy:write(string.format("addCommand{ command = '%s', func = function() shellExecute('%s') end }\n",
				strCommandName, strCommandNameFull))
			histroy:flush()
			break
		end
	end
end)

addEventHandler('onClose', function()
	histroy:close()
	showWindow(curHideWindow, 'normal')
end)
