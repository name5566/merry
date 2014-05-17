本文总是以最新版本的 Merry 为准，因此下载的老版本可能和文档中描述的部分功能不符。

Merry 被设计用于简化对计算机的操作，其可以将一组操作定义为一个可执行的 Merry 命令并通过命令名、快捷键等方式执行。

Merry 名字的由来
----------------
Merry 是本软件的开发代号，此名字来源于漫画《[海贼王](http://movie.douban.com/subject/1453238/)》的一艘叫梅利号的船（详细的故事请关注《海贼王》）。

为什么开发 Merry
----------------
最初使用 Linux 系统非常喜欢 gmrun + openbox 的组合，gmrun 能够弹出一个命令输入窗口，输入程序的名称就可以执行对应的程序，而 openbox 则可以非常方便的进行快捷键的绑定。后来使用 Windows 系统时，一直没有找到类似的替代软件，从而萌发了自己开发一个的想法。简单的制作之后，我开始使用 Merry，经过长时间的使用发现确实带来了很多的便利，致使之后使用没有安装 Merry 的机器时感觉很不习惯，这时候我发现它应该是一个有用的软件，于是有了今天的开源软件 Merry。随着时间的流逝 Merry 已经越来越丰富，而不仅仅只有上述这么简单的功能而已，只要你有想法，Merry 能尽量帮助你实现。

Merry 的目标
------------
在基于窗口的操作系统中，简化一切重复、繁琐的操作并提供一些实用的功能。

Merry 的特点和功能
------------------
* 跨平台的支持，让你在所有平台下保持一致的操作方式（目前 Windows 版本功能完善，Linux、MacOS 版仅仅支持部分功能且暂时不提供下载）
* 可以定义 Merry 命令（快捷键）来完成一些常用的操作，例如：打开目录、启动程序、打开网页等
* 通过 Merry 命令可以模拟用户的输入，例如：模拟键盘和鼠标输入
* 通过 Merry 可以轻松的管理窗口，例如：关闭窗口、最大化和还原窗口、移动窗口、隐藏窗口等
* 通过 Merry 命令可以来进行自动化的操作，例如：打开某应用程序，自动输入用户密码进行登录等
* Merry 采用完全开放的体系，可以使用 [Lua](http://www.lua.org/) 的扩展库或者外部程序来扩展 Merry 的功能

认识 Merry
----------
Merry 运行之后的样子：
![Merry 运行之后的样子](http://name5566.com/wp-content/uploads/2012/09/merry_1.0.0.png)

对于 Windows 用户来说，Windows 本身提供了一些快捷键，例如：

* W-D（表示 Windows 按键 + D）能够用来显示桌面
* W-L 用来锁定计算机
* S-F10（表示 Shift + F10）用来显示右键菜单

默认的配置下，Merry 能够提供一些快捷键（又被叫做 key 或者触发键 trigger key），作为系统提供快捷键的一个补充：

* A-R（表示 Alt + R）能够用来打开和隐藏 Merry 的界面
* A-M 用于最大化或者还原（如果已经最大化）当前窗口
* A-H 用于隐藏和显示当前窗口（有点类似于老板键）
* A-Q 用于关闭当前窗口
* A-T 用于打开 CMD 窗口
* A-Up（表示 Alt + 上方向键）用于音量最大化（音量调节功能需要 [nircmdc](http://www.nirsoft.net/utils/nircmd.html) 命令行软件的支持）
* A-Down 用于静音
* A-Left 用于调小音量
* A-Right 用于调大音量

Merry 命令
----------
当然 Merry 不会仅仅是一个提供简单快捷键功能的软件，Merry 的核心术语是：Merry 命令。在 Merry 窗口中输入的字符被叫做 Merry 的命令。我们可以在 Merry 的配置文件 Merry.lua 中添加任何我们需要的 Merry 命令（Merry.lua 是一个 [lua](http://www.lua.org/) 文件，Merry 使用 Lua 处理配置脚本）。Merry 命令能够绑定一个 Lua 函数，也就是说可以通过 Lua 函数来定义一个 Merry 命令。具体来说，一个 Merry 命令包括：

1. 一个可选的命令名，命令名不区分大小写，如果没有设定快捷键则必须设定命令名
2. 一个可选的快捷键，快捷键不区分大小写，如果没有设定命令名则必须设定快捷键
3. 定义命令行为的 Lua 函数（必须设定）

简单的看一个例子：

```lua
-- 增加一个 Merry 命令 "c"
-- Merry 命令的名字为 c，没有快捷键
addCommand{ name = 'c', func = function()
    -- Merry 命令执行一个函数，此函数将运行一个 shell 程序，这里为打开 c:
    shellExecute('c:', '', '', 'max')
end }
```

有了上面这个命令，我们在 Merry 的命令窗口中输入 c 回车就会打开 C:

每一个 Merry 命令都可以带有参数，在 Merry 命令窗口中输入的字符串： string1 string2 string3 ... stringN 以第一个空格为标准，Merry 命令被解析为 "string1" 为命令的名字，"string 2 string3 ... stringN" 为命令的参数，参数将以字符串的形式传递给设定的 Lua 函数。例如在命令窗口中输入 say hello，表示执行命令 say，命令的参数为 hello：

```lua
-- 增加命令 say
addcommand{ command = 'say', func = function(arg)
    -- 在 merry 的命令窗口输入的 say 命令的参数将以字符串的形式传递给 arg
    message(arg)
end }
```

对于上面这个命令，当我们输入 say hi 的时候，将弹出一个对话框，上面写着 "hi"。作为范例，Merry 的默认配置中，我们有两个命令 google 和 baidu，他们分别使用默认浏览器打开 google 和百度进行搜索，例如我们可以输入：google merry 快捷键。

每一个 Merry 命令都可以绑定一个快捷键，例如：

```lua
addCommand{ key = 'A-Q', func = function() closeWindow(getForegroundWindow()) end }
```

此命令没有命令名，仅仅设定了一个快捷键 Alt + Q。快捷键使用 "X-Y" 这样的字符串（不区分大小写）描述，例如： A-l 表示 Alt + l A-C-c 表示 Alt + Control + c 在快捷键描述字符串 "X-Y" 中 X 为可选的（也就是快捷键可以为一个按键，例如 F9），可以为：

* A 表示 Alt 键
* C 表示 Control 键
* W 或者 M 表示 Win 键
* S 表示 Shift 键

其中 Y 可以为：

* 任意的字母和数字，对应键盘上的字母和数字
* 一个字符串，表示键盘上的某个按键，例如：字符串 "Home" 表示键盘上的 Home 键

可用的表示按键的[字符串在这里](https://github.com/name5566/merry/wiki/MerryKeyString)（部分按键字符串在 Windows 下无效）。

上面就是 Merry 的基本功能的一个展示，我们可以定义各种各样的命令，满足我们的需要，特别是解决每天需要重复进行的一些工作（[Don't repeat yourself](http://en.wikipedia.org/wiki/Don't_repeat_yourself)），使用 Merry 使它们能够更加便捷的完成。

Merry 的配置和 API
------------------
只要稍学习一下 lua 编程语言，就可以灵活的配置 Merry。配置文件位于 config 目录中，common.lua 为 Merry 提供了默认的配置。

这里介绍一下 Merry 配置文件的 API：

shellExecute

```lua
-- 用于执行一个 shell 命令
-- commandName 为 shell 命令名
-- commandArg 为 shell 命令需要的参数
-- workingDir 为 shell 命令的工作路径
-- show 表示显示的方式，包括 'normal'、'max'、'min'、'hide'（常规显示、最大化、最小化、隐藏）
-- 函数返回 true / false 表示是否执行是否成功
shellExecute(commandName, commandArg, workingDir, show)

-- 范例，打开 cmd 窗口并且最大化
shellExecute('cmd', '', '', 'max')
```

getForegroundWindow

```lua
-- 获取前台窗口
-- 函数返回前台窗口
getForegroundWindow()
```

setForegroundWindow

```lua
-- 设置窗口 window 为前台窗口
setForegroundWindow(window)
```

showWindow

```lua
-- 显示窗口 window
-- show 表示显示的方式，包括 'normal'、'max'、'min'、'hide'、'restore'（常规显示、最大化、最小化、隐藏、还原）
showWindow(window, show)

-- 范例，最大化或还原窗口
if isWindowMax(window) then
    showWindow(window, 'restore')
else
    showWindow(window, 'max')
end
```

closeWindow

```lua
-- 关闭窗口 window
closeWindow(window)

-- 范例，关闭前台窗口
closeWindow(getForegroundWindow())
```

isWindowMax

```lua
-- 窗口 window 是否为最大化
-- 函数返回 true / false 表示 window 是否最大化
isWindowMax(window)
```

isWindowMin

```lua
-- 窗口 window 是否为最小化
-- 函数返回 true / false 表示 window 是否最小化
isWindowMin(window)
```

isWindowShown

```lua
-- 窗口 window 是否在显示
-- 函数返回 true / false 表示 window 是否在显示
isWindowShown(window)
```

getWindowText

```lua
-- 获取窗口 window 的标题栏文字
-- 函数返回窗口 window 的标题栏文字
getWindowText(window)
```

setWindowText

```lua
-- 设置窗口 window 的标题栏文字
setWindowText(window, text)
```

getWindowSize

```lua
-- 获取窗口 window 的大小
-- 函数返回两个值 width 和 height
getWindowSize(window)

-- 范例，获取前台窗口的大小
local width, height = getWindowSize(getForegroundWindow())
```

setWindowSize

```lua
-- 设置窗口 window 的大小
setWindowSize(window, width, height)
```

getWindowPosition

```lua
-- 获取窗口 window 的位置
-- 函数返回两个值 x 和 y 为窗口左上角的位置
getWindowPosition(window)

-- 范例，获取前台窗口的位置
local x, y = getWindowPosition(getForegroundWindow())
```

setWindowPosition

```lua
-- 设置窗口 window 的位置
-- 设置的位置为窗口左上角的位置
setWindowPosition(window, x, y)
```

findWindow

```lua
-- 通过窗口名称查找窗口
-- 参数 parentWindow 为可选参数，用于表示被查找窗口的父窗口
findWindow(name, parentWindow)
```

getMousePosition

```lua
-- 获取当前鼠标的位置
-- 函数返回两个值 x 和 y 为鼠标的位置
getMousePosition()
```

setMousePosition

```lua
-- 设置当前鼠标的位置
setMousePosition(x, y)
```

enterKey

```lua
-- 模拟敲击一个按键
enterKey(keyStr)

-- 范例，模拟快捷键 Shift + F10 来打开右键菜单
enterKey('S-F10')
```

message

```lua
-- 将用对话框输出消息
message(str)

-- 范例，输出 Hello Merry
message('Hello Merry')
```

enableCommandKey

```lua
-- 激活快捷键
-- 参数 keyID 由 addCommand 函数返回
-- 创建一个命令后，其快捷键是默认激活的
-- 若执行了 disableCommandKey 禁用了某个命令的快捷键，可调用此函数激活此命令的快捷键
enableCommandKey(keyID)
```

disableCommandKey

```lua
-- 禁用快捷键
-- 参数 keyID 由 addCommand 函数返回
-- 创建一个命令后，其快捷键是默认激活的
-- 调用此函数可以禁用某个命令的快捷键
disableCommandKey(keyID)

-- 范例，按 HOME 键禁用某快捷键
local keyID = addCommand{ key = 'C-1', func = function() enterKey('S-F10', 'V', '', 'Return') end }
local enabled = true
addCommand{ key = 'HOME', func = function()
    if enabled then
        disableCommandKey(keyID)
        enabled = false
    else
        enableCommandKey(keyID)
        enabled = true
    end
end }
```

setTimer

```lua
-- 开启一个定时器
-- 参数 milliseconds 表示定时器每隔 milliseconds 触发一次
-- 参数 oneShot 表示定时器是否只触发一次
-- 参数 callback 为一个 Lua 函数，定时器每次触发时都会被调用
-- 函数返回成功创建的定时器
setTimer(milliseconds, oneShot, callback)

-- 范例，实现功能：使用 Windows 照片查看器时，定时翻看下一张图片
--
-- 使用 F7 启动一个定时器，每 5 秒模拟按下右方向键
-- 使用 Ctrl + F7 关闭定时器
local timer
addCommand{ key = 'F7', func = function()
    timer = setTimer(5000, false, function()
        enterKey('Right')
    end)
end }
addCommand{ key = 'C-F7', func = function()
    clearTimer(timer)
end }
```

clearTimer

```lua
-- 清理定时器
clearTimer(timer)
```

如果有更多 API 需求，请给我发邮件。

Merry 事件
----------
我们可以在 Merry 的基本配置中找到如下代码：

```lua
addEventHandler('onClose', function()
    -- ...
end)

addEventHandler('onUndefinedCommand', function(commandName, commandArg)
    -- ...
end)
```

事件发生时，Merry 会去调用定义的事件处理函数。例如：Merry 关闭（或重新载入配置时）时会调用一个名为 onClose 的函数。addEventHandler 用于为某个事件添加事件处理函数。Merry 已有的事件如下：

onClose

```lua
-- Merry 关闭或者重新载入配置时触发
onClose()
```

onUndefinedCommand

```lua
-- 执行 Merry 命令时，出现未定义命令时触发
onUndefinedCommand(commandName, commandArg)
```

Merry 软件的使用技巧
--------------------

* 如何开机自动运行 Merry？在 Windows 下，把 Merry 的快捷方式放入启动目录（启动目录可以在开始菜单中找到）
* 如何快捷的关闭 Merry？默认情况下，最简单的关闭 Merry 的方法就是用 A-R 呼出 Merry，然后用 A-Q（关闭窗口的快捷键）关闭 Merry
* 如何调试 Merry 配置脚本？目前你可以使用 message 来输出一些调试信息，暂时不打算提供过于强大的调试功能
* 中文乱码的问题。如果出现中文乱码，考虑 Merry.lua 的文件编码是否正确，Merry.lua 文件需要是 ANSI 编码的。Windows 下可以使用 Notepad 修改编码方式，具体的做法是用 Notepad 打开 Merry.lua，然后另存为 Merry.lua 并且选择编码为 ANSI
* Windows 下的命令小技巧。我们可以建立一个目录并将其加入到环境变量 PATH 中，然后将程序、目录等快捷方式放入此目录中，那么在 Merry 中输入这些快捷方式的名称后将运行指定程序，不过注意，此技巧可能会无法进行命令的自动补全
* 使用 Merry 配置 DOTA、魔兽的改键：

```lua
-- 将数字键盘上的 7 8 4 5 改为 A-1，A-2，A-3，A-4
-- 使用 HOME 键启动和关闭改键

local war3Enabled
addCommand{ key = 'Home', func = function()
    if war3Enabled then
        war3Enabled = false
    else
        war3Enabled = true
    end
end }
addCommand{ key = 'A-1', func = function()
    if war3Enabled then
        enterKey('NUMPAD7')
    end
end }
addCommand{ key = 'A-2', func = function()
    if war3Enabled then
        enterKey('NUMPAD8')
    end
end }
addCommand{ key = 'A-3', func = function()
    if war3Enabled then
        enterKey('NUMPAD4')
    end
end }
addCommand{ key = 'A-4', func = function()
    if war3Enabled then
        enterKey('NUMPAD5')
    end
end }
```

* 使用 Merry 解决 DOTA 技能快捷键冲突的问题。DOTA IMBA 存在随机技能的时候，快捷键冲突是一个很头痛的问题，我们可以使用 Merry 来解决冲突快捷键的问题，基本的思路就是通过 Merry 模拟移动鼠标到技能处，然后点击技能：

```lua
-- 使用按键 Q 来代替某个技能的快捷键
addCommand{ key = 'q', func = function()
    -- 保存鼠标当前位置
    local x, y = getMousePosition()
    -- 移动鼠标到需要修改快捷键的技能的位置（这里随便写了两个值，实际要按具体情况修改）
    setMousePosition(800, 700)
    -- 模拟点击鼠标左键
    enterKey('lbutton')
    -- 鼠标移动回原来的位置
    setTimer(30, true, function()
        setMousePosition(x, y)
    end)
end }
```

* 使用鼠标选中文件后，使用快捷键来自动打开 VIM 对文件进行编辑，在 Windows 7 下，希望使用 VIM 来编辑文件一般这么做：在文件上点击右键，然后敲击 V 按键，最后回车（也许还有其他的办法）。这种操作比较繁琐，现在通过 Merry 我们可以定义一个快捷键，快速打开 VIM 来编辑当前选中文件：

```lua
addCommand{ key = 'C-F1', func = function()
    enterKey('S-F10', 'V', 'Return')
end }
```

* Windows 下，在资源管理器中，使用 Merry 打开 DOS 窗口且设定工作目录为资源管理器所在目录。首先，我们应该设置资源管理器在标题栏显示完整路径，使得 Merry 可以获取到这个路径，设置的方法为：资源管理器 --- 工具 --- 文件夹选项 --- 查看 --- 标题栏显示完整路径。然后我们就可以在打开 DOS 窗口的时候设定工作目录了：

```lua
addCommand{ command = 'cmd', key = 'A-T', func = function()
        local window = getForegroundWindow()
        local dir = getWindowText(window)
        shellExecute('cmd', '', dir)
end }
```

反过来，我们也可以在 DOS 窗口中打开资源管理器并设定工作目录为 DOS 当前的工作目录：

```lua
addCommand{ key = 'A-E', func = function()
        enterKey('e', 'x', 'p', 'l', 'o', 'r', 'e', 'r', 'Space', '.', 'Return')
end }
```

* 自动输入用户名和密码。我们经常需要输入我们的用户名和密码，Merry 可以帮我们自动输入：

```lua
-- 使用快捷键 A-n 输入 name
addCommand{ key = 'A-n', func = function()
        enterKey('n', 'a', 'm', 'e')
end }
```

我们当然也可以自动来输入密码，不过直接把密码明文保存在配置文件中并不安全（当然你可以使用其他的小程序来扩展 Merry 使得能够较为安全的保存密码）。

* 清理历史记录。一个不存在的 Merry 命令，一旦被成功执行就会被记录下来，保存在 Histroy.lua 中，我们可以通过编辑此文件来修改或者清理历史记录。

历史上的 Merry
--------------

## 2012/11/02

Merry 的第一个对外版本发布，版本号 0.1.2，此版本仅仅支持 Windows

![Merry 第一个对外版本](http://name5566.com/wp-content/uploads/2012/09/merry.png)

## 2013/04/02

Merry 的第二个对外版本发布，版本号 1.0.0。版本相对于 0.1.2 的变化：

* 细微调节了一下 API（极大多数 API 未改动）
* Linux、MacOS 版实现部分功能（但未提供下载）
* 重新设计了界面
* 已发现的少量 BUG 被修复

![Merry 第二个对外版本](http://name5566.com/wp-content/uploads/2012/09/merry_1.0.0.png)

TODO LIST
---------

版本 v0.1 目标

* 增加模拟按键 API（已完成）
* 增加按键映射的 API（目前不考虑增加此 API，建议使用其他软件完成此功能，例如 Windows 下的 KeyTweak?）
* 增加界面配置的 API（已完成）
* 增加鼠标点击等相关 API（已完成）
* 窗口管理相关的 API（已完成）
* 增加定时器相关的 API（已完成）
* 增加事件，例如：Merry 关闭事件等（已完成）
* 增加重新载入配置文件的功能（已完成）

版本 v0.2 目标

* 自动补全和下拉列表的支持（已完成）
* 增加系统托盘（已完成）
* 历史记录的支持（已完成）
* 增加下列列表界面配置的 API（暂不考虑此功能）
* 替换 Win API RegisterHotKey? 通过 Hook 实现快捷键（暂不考虑此功能）

版本 v1.0 目标

* Linux 支持
* MacOS 支持
* 增加插件体系
* 多语言的支持
* 界面美化

版本 v2.0 目标

* 增加手势支持

版本 v3.0 目标

* 增加语音支持
