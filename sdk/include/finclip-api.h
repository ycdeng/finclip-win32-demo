/*******************************************************
* @file  finclip-api.h
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
#ifndef __H_FINCLIPAPI_H__
#define __H_FINCLIPAPI_H__
#ifdef _WIN32
#ifndef FINSTDMETHODCALLTYPE
#define FINSTDMETHODCALLTYPE __stdcall
#define DLL_EXPORT _declspec(dllexport)
#endif
#else
#define FUNCTION_CALL_MODE
#define DLL_EXPORT
#endif

#define FIN_SID  const char *
#define FIN_OK   0
#define FIN_FAIL 1

struct IKnown
{
};

///数据打包器接口
struct IFinPacker : public IKnown
{
public:
	/**
	 * @brief 打包准备
	 */
	virtual void BeginPacker() = 0;
	/**
	 * @brief 往数据包增加内容
	 * @detail 分别为KEY,VALUE
	 *
	 * @param field 数据字段
	 * @param value 数据值
	 * @return 0成功，1失败
	 */
	virtual void Add(const char* field, const char* value) = 0;
	/**
	 * @brief 结束打包
	 */
	virtual void EndPacker() = 0;

	/**
	 * @brief 释放打包器
	 */
	virtual void Release() = 0;

	/**
	 * @brief 取数据缓冲大小
	 * @return 返回数据缓冲大小
	 */
	virtual int GetBufferSize() = 0;

	/**
	 * @brief 导出数据缓冲
	 * @param buffer 存放数据缓冲，由调用方预申请空间
	 * @param size   存放数据缓冲长度
	 * @return 0成功，1失败
	 */
	virtual int Dump(unsigned char* buffer, int* size) = 0;
};

///配置信息接口
struct IFinConfig
{
public:
	/**
	 * 功能：设置应用市场
	 * SDK支持多应用市场，可以打开不同应用市场的小程序;
	 * 不同的应用市场对应不同的domain;
	 * 打开小程序时需要指定应用市场
	 *@param       app_store：应用市场类型，由开发者自主设置
	 *@return void
	 */
	virtual void SetAppStore(int app_store) = 0;
	/**
	 * @brief 设置加密类型
	 * @param encrypt_type 0:标准加密 1:国密
	 * @return void
	 */
	virtual void SetEncryptType(int encrypt_type) = 0;
	/**
	 * @brief 设置应用市场域名
	 * @param domain 形如: https://api.finogeeks.com
	 * @return void
	 */
	virtual void SetDomain(const char* domain) = 0;
	/**
	 * @brief 设置Api前辍
	 * @param apiprefix /api/v1/mop
	 * @return void
	 */
	virtual void SetApiPrefix(const char* apiprefix) = 0;
	/**
	 * @brief 设置SDK的秘钥
	 * @param appkey
	 * @return void
	 */
	virtual void SetAppKey(const char* appkey) = 0;
	/**
	 * @brief 设置SDK的私钥
	 * @param secret
	 * @return void
	 */
	virtual void SetSecret(const char* secret) = 0;
	/**
	 * @brief 设置SDK的指纹
	 * @param finger
	 * @return void
	 */
	virtual void SetFinger(const char* finger) = 0;

};
///配置打包器接口
struct IFinConfigPacker : public IKnown
{
public:

	/**
	 * @brief 获取配置信息实例
	 * @return 返回配置信息实例
	 */
	virtual IFinConfig* NewConfig() = 0;

	/**
	 * @brief 增加配置信息
	 * @return 负数表示失败，0表示成功
	 */
	virtual int AddConfig(IFinConfig* config) = 0;
	/**
	 * @brief 获取配置信息
	 * @return 返回配置信息
	 */
	virtual IFinConfig* GetConfig(int type) = 0;
	/**
	 * @brief 获取配置信息个数
	 * @return 返回配置信息个数
	 */
	virtual int GetConfigSize() = 0;
	/**
	 * @brief 通过索引获取配置信息
	 * @return 返回配置信息
	 */
	virtual IFinConfig* GetConfigByIndex(int index) = 0;
};
///SDK统一事件接口
struct IEvent :public IKnown {
public:
	virtual int GetErrorCode() = 0;
	virtual const char* GetErrorInfo() = 0;
	virtual const char* GetBody() = 0;
};

struct IPackerFactory : public IKnown {
public:

	/**
	 * @brief 获取配置打包器
	 * @detail 获取配置打包器实例
	 *
	 * @return 返回配置打包器实例
	 */
	virtual IFinConfigPacker* GetFinConfigPacker() = 0;

	/**
	 * @brief 获取数据打包器
	 * @detail 获取数据打包器实例
	 *
	 * @return 返回数据打包器实例
	 */
	virtual IFinPacker* GetFinPacker() = 0;
};
//函数指针回调
/**
 * @params ret 调用结果 0成功,1失败
 * @params event 返回结果 IEvent对像
 * 如下格式
 *
 */
typedef void(*FinClipSDKCallback)(int ret, IEvent* event);
#endif // !__H_FINCLIPAPI_H__
