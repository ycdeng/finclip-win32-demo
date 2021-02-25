/**@mainpage  FinClip小程序开放平台
* <table>
* <tr><th>Project  <td>FinClip小程序开放平台
* <tr><th>Author   <td>gordanyang
* <tr><th>Source   <td>
* </table>
* @section   项目详细描述
* -# FinClip可让您的自有APP获得小程序运行能力，有效降低企业研发与管理成本，完备的小程序后台管理系统，协助企业构建自己的小程序数字化生态
* -# 凡泰极客借鉴微信、支付宝等主流小程序平台技术，进一步打造出可私有化的小程序开放平台产品 —— FinClip，该平台主要由两个客户端组成，一个是运营端，负责审核小程序内容，确保小程序的内容符合合规要求；另一个是企业端，负责开发小程序及小程序上下架管理
* @section 产品定位
* FinClip 面向全行业发布，尤其适合金融业及其他需要自建数字化生态以及实现业务场景敏捷迭代的行业，帮助合作伙伴构建一个安全、合规、可控的小程序生态
* @section   功能描述
* -# 开放 \n
* 稳定、高可用的小程序内核；丰富的 OpenAPI 支持二次开发;模块功能组件化，支持业务灵活配置;允许多方参与，共建小程序生态。
* -# 免费 \n
* 快速部署免费社区版，全平台功能一键部署，打造自己的小程序生态
* -# 价值\n
* 快速拥有小程序技术，快速业务创新；私有化小程序生态，统一管理内外部业务场景
* -# 多端上线\n
* 同一小程序可以同步上线多个宿主端（宿主：即小程序可上线的 APP），为开发者节省大量的人力和时间
* -# 部署方式 \n
* 支持私有化部署、混合部署、行业云部署
*
*
* @section 技术体系
* @image html arch.png
* 小程序前端框架借鉴了主流前端框架Vue的设计思路，从小程序的应用形态，提供了简洁的编程模型，定义了一套组件和API 接口的规范，降低了学习门槛，方便开发者快速开发小程序。
  在小程序框架内部提供了小程序的生命周期管理，通过事件的方式把小程序每个阶段都注入到小程序里面，开发者可以通过这些事件来处理小程序每个阶段需要完成的业务逻辑。同时框架内部使用了虚拟DOM 来处理页面的每次更新，提升了页面的渲染性能。

  前端框架下面是小程序Native引擎，包括了小程序容器、渲染引擎和JavaScript引擎，这块主要是把客户端Native 的能力和前端框架结合起来，给开发者提供系统底层能力的接口。

  在渲染引擎上面，FinClip不仅提供JavaScript + WebView 的方式，还提供JavaScript + Native 的方式，在对性能要求较高的场景，可以选择Native 的渲染模式，给用户更好的体验。

   示意图左边和右边分别是面对开发者提供的研发支撑和运维支撑服务，可以帮助开发者更有效率的开发小程序，在上线后也提供众多的工具帮助开发者管理和运营线上的小程序
* @section   用法描述
* @see https://www.finclip.com/mop/document/quickstart/deploy.html
* @section   版本更新
* <table>
* <tr><th>Date        <th>H_Version  <th>S_Version  <th>Author    <th>Description  </tr>
* <tr><td>2021/01/31  <td>1.0    <td>S02010041808171   <td>gordanyang  <td>创建初始版本 </tr>
* -# 初始版本
* </tr>
* </table>
**********************************************************************************
*/

/*******************************************************
* @file  finclip-sdk.h
* @brief
* @details
* @mainpage
* @author      gordanyang
* @date        2021/01/31
* @version
* @copyright    Copyright (c) 2017-2021  凡泰极客科技有限公司
*
* @attention
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author       <th>Description
* <tr><td>2021/01/31      <td>1.0      <td>gordanyang <td>创建初始版本
* </table>
*
**********************************************************************************/
#ifndef __H_FINCLIPSDK_H__
#define __H_FINCLIPSDK_H__

#include "finclip-api.h"

extern "C"
{
	DLL_EXPORT int FINSTDMETHODCALLTYPE Initialize(HINSTANCE hinstance, IFinConfigPacker* configpacker);
	DLL_EXPORT IFinPacker* FINSTDMETHODCALLTYPE NewFinPacker();
	DLL_EXPORT IFinConfigPacker* FINSTDMETHODCALLTYPE NewFinConfigPacker();

	///小程序Api
	/**打开小程序
	*
	*
	* @param appId 小程序appId
	* @return 1表示成功，0表示失败
	*/
	DLL_EXPORT int  FINSTDMETHODCALLTYPE StartApplet(int apptype,const char* appid, IFinPacker* param, FinClipSDKCallback callback);
}
#endif // !_H_FINCLIPSDK_H_
