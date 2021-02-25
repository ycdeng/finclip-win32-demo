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

### 查看API文档

[FinClipSDK WindowsAPI](https://docs.finogeeks.club/docs/finclip-win32/)

## 📚 想要通关全程？这里是全程攻略
直接跑demo虽然快，不过快速通关总会留下各种遗憾。<br />来吧，跟随全程攻略，了解一下“让App运行小程序”的全貌吧：
<a name="Ri882"></a>
### 1、FinClip 平台是什么？

- Finclip平台是凡泰极客旗下的一款可私有化的小程序开放平台<br />
- 凡泰极客借鉴微信、支付宝等主流小程序平台技术，进一步打造出可私有化的小程序开放平台产品 —— FinClip，该平台主要由两个客户端组成，一个是运营端，负责审核小程序内容，确保小程序的内容符合合规要求；另一个是企业端，负责开发小程序及小程序上下架管理。
- FinClip 面向全行业发布，尤其适合金融业及其他需要自建数字化生态以及实现业务场景敏捷迭代的行业，帮助合作伙伴构建一个安全、合规、可控的小程序生态。
<a name="sx7EX"></a>
### 2、FinClip 平台的特色？

- 多端上线：同一小程序可以同步上线多个宿主端（即小程序可上线的 APP），为开发者节省大量的人力和时间。
- 合规引流：解决“行业应用嵌入第三方网络空间”的安全合规问题，合规引流，连接金融服务场景。
- 方便快捷：相较于 APP，小程序开发周期短，开发成本低等特性让更多的开发者能够轻松、快速的参与到开发过程中，实现快速上线，快速起量。
- 优质体验：小程序拥有优于现有 H5 页面的用户体验，帮助企业/机构获取更多渠道用户，同时节省获客成本。
- 部署方式：满足合规监管多种部署方式，支持私有化部署、混合部署、行业云部署。
<a name="l5pz3"></a>
### 3、FinClip 有哪些典型案例？
（如需了解更多案例，可以与小助手联系呀）<br />
![Yippi](media/image/image-1612508915946.jpeg)
<a name="l352x"></a>
## ⛳️ 获得更多指引
✅ 部署一套私有化社区版：[https://www.finclip.com/mop/document/quickstart/Community-Edition.html](https://www.finclip.com/mop/document/quickstart/Community-Edition.html)<br />✅ 了解iOS相关API：[https://www.finclip.com/mop/document/runtime-sdk/sdk-api/ios.html](https://www.finclip.com/mop/document/runtime-sdk/sdk-api/ios.html)<br />✅ 了解更多iOS常见问题：[https://www.finclip.com/mop/document/faq/SDK/iOS-SDK.html](https://www.finclip.com/mop/document/faq/SDK/iOS-SDK.html)<br />

<a name="9K1zU"></a>
## ☎️ 与我们联系
如想进入FinClip小程序技术群交流探讨，或了解更多使用场景，请添加小助手微信。<br />
![](media/image/demo_readme2.png)

（如图片未能正常展示，请直接手动添加wx号：liudiyang1212 ）



