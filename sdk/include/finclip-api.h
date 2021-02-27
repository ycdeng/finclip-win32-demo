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
#include <windows.h>
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

///各类接口统一的查询与引用接口，所有插件提供的接口都要实现 IKnown (参照COM标准)
struct IKnown
{
	///接口查询
	/**查询与当前接口相关的其他接口，例如可以查到 IIoC, IManager 等
	 *@param HS_SID  iid  接口全局唯一标识
	 *@param IKnown **ppv 返回iid对应的接口指针
	 *@return I_OK 成功，I_NONE 未查到iid 相应接口
	 */
	 //virtual unsigned long  FUNCTION_CALL_MODE QueryInterface(HS_SID iid, IKnown** ppv) = 0;
	 ///引用接口，引用计数加一(多线程引用时，方法实现代码里要对计数值加锁后修改)
	 //virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;
	 ///释放接口，引用计数减一，计数为0时释放接口的实现对象(多线程引用时，方法实现代码里要对计数值加锁加锁后修改)
	 //virtual unsigned long  FUNCTION_CALL_MODE Release() = 0;
};

struct IFinPacker : public IKnown
{
public:
	virtual void BeginPacker() = 0;
	virtual void AddField(const char* field) = 0;
	virtual void AddValue(const char* value) = 0;
	virtual void EndPacker() = 0;
	virtual void Release() = 0;
};

struct IFinConfig
{
public:
	virtual void SetAppStore(int app_store) = 0;
	virtual void SetEncryptType(int encrypt_type) = 0;
	virtual void SetDomain(const char* domain) = 0;
	virtual void SetApiPrefix(const char* apiprefix) = 0;
	virtual void SetAppKey(const char* appkey) = 0;
	virtual void SetSecret(const char* secret) = 0;
	virtual void SetFinger(const char* finger) = 0;

	virtual int GetAppStore() = 0;
	virtual int GetEncryptType() = 0;
	virtual const char* GetDomain() = 0;
	virtual const char* GetApiPrefix() = 0;
	virtual const char* GetAppKey() = 0;
	virtual const char* GetSecret() = 0;
	virtual const char* GetFinger() = 0;
};
struct IFinConfigPacker : public IKnown
{
public:
	virtual IFinConfig* NewConfig() = 0;
	virtual int AddConfig(IFinConfig* config) = 0;
	virtual IFinConfig* GetConfig(int type) = 0;
	virtual int GetConfigSize() = 0;
	virtual IFinConfig* GetConfigByIndex(int index) = 0;

};
//函数指针回调
/**
 * @params ret 调用结果 0成功,1失败
 * @params data 返回结果 {}
 *
 */
typedef void(*FinClipSDKCallback)(int, const char*);
#endif // !__H_FINCLIPAPI_H__
