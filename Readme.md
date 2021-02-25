# FinClip小程序开放平台-windows运行时

## 使用指引

### 使用前提

windows小程序运行环境需要Microsoft WebView2支持。
可以从[这里下载最新版本webview2运行库](https://developer.microsoft.com/zh-cn/microsoft-edge/webview2/#download-section)安装后即可以使用。

### 集成SDK
Windows版本FinClip运行时一共有4个文件。

1. finclip-api.h: Api定义文件
2. finclip-sdk.h: 接口定义文件
3. FinClipSDK.lib 链接库文件(x86,x64)
4. FinClipSDK.dll 动态链接库(x86,x64)

#### 第一步 引入头文件

```c++

#include "finclip-sdk.h"
#pragma comment(lib, "FinClipSDK.lib")

```

### 第二步 初始化SDK

```c++
  FinConfig config = {
		1,
		"https://api.finclip.com",
		"/api/v1/mop",
		"这里输入appkey",
		"这里输入secret",
		"",
		1
	};
	IFinConfigPacker* configpacker = NewFinConfigPacker();
	configpacker->AddConfig(config);
	Initialize(hInstance, configpacker);
```

- **SDKKEY** 和 **Secret** 可以从[ FinClip开放平台](https://finclip.com/#/home) 获取，你也可以直接点击进入[注册页面](https://finclip.com/#/register)
- 进入平台后，在【应用管理】页面添加你自己的包名后，点击【复制】即可获得key\secret\apisever字段<br />
- **apiServer** 和 **apiPrefix** 是固定字段，请直接参考本demo
- **小程序id** 为在管理后台上架的小程序AppID，需要在【小程序管理】中创建并在【应用管理】中关联 <br />（与微信小程序ID不一样哦！这里是特指finclip平台的ID）


### 第三步 打开小程序

```c++

  int server_type = 1;
  init_finclipsdk(server_type,wappkey, wsecret);
  IFinPacker* packer = NewFinPacker();
  packer->BeginPacker();
  packer->AddField("appId");
  packer->AddValue("appId");
  packer->EndPacker();
  StartApplet(server_type, utf8_encode(wappid).c_str(), packer, finclip_applet_callback);
  packer->Release();

```


