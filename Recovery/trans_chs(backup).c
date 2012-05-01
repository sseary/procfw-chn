#include "systemctrl.h"
#include "systemctrl_se.h"
#include "utils.h"
#include "main.h"

const char * g_messages_chs[] = {
	"PRO 恢复菜单",
	"主菜单",
	"进入中",
	"退出中",
	"返回",
	"默认",
	"启用",
	"禁用",
	"切换USB",
	"启用USB",
	"禁用USB",
	"基本设置",
	"区域欺骗",
	"恢复菜单字体",
	"ISO 模式",
	"标准",
	"M33 driver",
	"Sony NP9660",
	"Inferno",
	"USB 设备",
	"Flash 0",
	"Flash 1",
	"Flash 2",
	"Flash 3",
	"UMD Disc",
	"连接 USB时给电池充电 (PSP-1000无效)",
	"使用Slim颜色 (PSP-1000专用)",
	"使用htmlviewer自定义保存位置",
	"隐藏 MAC地址",
	"启动时跳过Sony Logo",
	"跳过游戏启动画面",
	"游戏列表中隐藏PIC0.PNG和PIC1.PNG",
	"保护 USB设备安装Flash",
	"使用/seplugins/version.txt",
	"使用/seplugins/usbversion.txt",
	"使用自定义更新服务器",
	"阻止删除休眠文件 (PSP-Go专用)",
	"高级设置",
	"插件(XMB)",
	"插件(Game)",
	"插件(Pops)",
	"NoDRM 引擎",
	"游戏时隐藏 CFW文件",
	"游戏时禁用摇杆",
	"旧插件支持(PSP-Go专用)",
	"Inferno & NP9660 使用ISO高速缓存",
	"Inferno & NP9660 缓存大小(MB)",
	"Inferno & NP9660 缓存数",
	"Inferno & NP9660 缓存策略",
	"允许非latin1的ISO文件名",
	"Memory Stick加速",
	"无",
	"Pop",
	"Game",
	"Vsh",
	"Pop & Game",
	"Game & Vsh",
	"Vsh & Pop",
	"始终",
	"CPU 频率",
	"CPU/BUS(XMB) ",
	"CPU/BUS(Game)",
	"插件管理",
	"System Storage",
	"Memory Stick",
	"插件在System Storage",
	"插件在Memory Stick",
	"注册表破解",
	"WMA 激活",
	"Flash 激活",
	"按钮交换",
	"确认按钮: X",
	"确认按钮: O",
	"激活 WMA",
	"激活 Flash",
	"交换 O/X按钮",
	"交换 O/X按钮 (需重启 VSH后才能生效)",
	"删除休眠文件 (PSP-Go专用)",
	"休眠文件删除",
	"运行/PSP/GAME/RECOVERY/EBOOT.PBP",
	"关闭设备",
	"挂起设备",
	"重启设备",
	"重启VSH",
	"分页",
	"日本",
	"美国",
	"欧洲",
	"韩国",
	"英国",
	"墨西哥",
	"澳大利亚",
	"香港",
	"台湾",
	"俄罗斯",
	"中国",
	"调试类型I",
	"调试类型II",
	"解锁PSP游戏内存 (休眠主屏幕)",
};

u8 message_test_chs[NELEMS(g_messages_chs) == MSG_END ? 0 : -1];
