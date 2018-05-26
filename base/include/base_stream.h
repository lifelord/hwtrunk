#ifndef _BASE_STREAM_H_
#define _BASE_STREAM_H_

#include <vector>
#include <string>
#include <deque>

#include "base_util.h"

class CStream
{
private:
	std::vector<uint8> m_Buff;
	std::vector<uint8>::iterator m_Pointer;

	std::deque<sint32> m_Stack;
public:
    void* m_MsgHead;

    template< typename TYPE >
    inline TYPE*& NewHead()
    {
        uint32 posi = position();
        m_Buff.resize(posi + sizeof(TYPE));
        m_Pointer = m_Buff.end();

        uint8* pPack = &m_Buff[posi];
        new ((TYPE*)pPack) TYPE();

        m_MsgHead = &m_Buff[0];
        return ((TYPE*&)m_MsgHead);
    };
public:
	/*************************************************
	Description:    // 构造函数
	Input:          // uiSize 数据缓存预分配大小
	*************************************************/
	CStream(uint32 uiSize = 1024);

	/*************************************************
	Description:    // 析构函数, 允许类被继续
	*************************************************/
	virtual ~CStream();

	/*************************************************
	Description:    // 获取数据流当前可用字节数
	Return:         // 返回可用字节数
	*************************************************/
	uint32 available(void);

	/*************************************************
	Description:    // 获取数据流数据总长度
	Return:         // 返回数据流总长度
	*************************************************/
	uint32 length(void);

	/*************************************************
	Description:    // 清除数据流
	*************************************************/
	void clear(void);

	/*************************************************
	Description:    // 重置缓冲区尺寸
	*************************************************/
	void resize(uint32 size);

	/*************************************************
	Description:    // 获取数据流当前指针位置
	Return:         // 返回数据流指针位置索引
	Oter:           // 从 0 开始
	*************************************************/
	uint32 position(void);

	/*************************************************
	Description:    // 设置数据流指针位置
	Oter:           // 从 0 开始
	*************************************************/
	void position(uint32 uiPosition);

	void posi_push(void);
	void posi_pop(void);
	void posi_clear(void);

	CStream& operator += (sint32 offset);
	CStream& operator -= (sint32 offset);

	/*************************************************
	Description:    // 缩减数据
	Oter:           // 缩减从 0 开始到当前 position 位置的数据
	*************************************************/
	void erase(void);

	/*************************************************
	Description:    // 获取数据流下标引用位置
	Input:          // position : 数据流指针位置
	Return:         // 数据流数据单元引用
	*************************************************/
	uint8& operator [] (sint32 position);

	/*************************************************
	Description:    // 从当前数据指针位置读取数据流中的数据
	Input:          // pvData : 数据缓冲
	// uiSize : 读取长度
	*************************************************/
	void read(void *pvData, uint32 uiSize);

	/*************************************************
	Description:    // 从当产数据指针位置写入数据
	Input:          // pvData : 需要写入的二进制指针变量
	Return:         // uiSize : 需要写入的数据长度
	*************************************************/
	void write(const void *pvData, uint32 uiSize);

	/*************************************************
	Description:    // 从当前指针位置读取字符串
	Input:          // strValue : 读取的数据将保存到该 std::string 变量中
	// uiSize : 需要读取的数据长度
	*************************************************/
	void read(std::string &strValue, uint32 uiSize);

	/*************************************************
	Description:    // 在当前指针位置中写入数据
	Input:          // strValue : 需要写入的 std::string 字符串变量
	// uiSize : 需要写入的数据长度
	*************************************************/
	void write(const std::string &strValue, uint32 uiSize);
};
#endif