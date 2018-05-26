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
	Description:    // ���캯��
	Input:          // uiSize ���ݻ���Ԥ�����С
	*************************************************/
	CStream(uint32 uiSize = 1024);

	/*************************************************
	Description:    // ��������, �����౻����
	*************************************************/
	virtual ~CStream();

	/*************************************************
	Description:    // ��ȡ��������ǰ�����ֽ���
	Return:         // ���ؿ����ֽ���
	*************************************************/
	uint32 available(void);

	/*************************************************
	Description:    // ��ȡ�����������ܳ���
	Return:         // �����������ܳ���
	*************************************************/
	uint32 length(void);

	/*************************************************
	Description:    // ���������
	*************************************************/
	void clear(void);

	/*************************************************
	Description:    // ���û������ߴ�
	*************************************************/
	void resize(uint32 size);

	/*************************************************
	Description:    // ��ȡ��������ǰָ��λ��
	Return:         // ����������ָ��λ������
	Oter:           // �� 0 ��ʼ
	*************************************************/
	uint32 position(void);

	/*************************************************
	Description:    // ����������ָ��λ��
	Oter:           // �� 0 ��ʼ
	*************************************************/
	void position(uint32 uiPosition);

	void posi_push(void);
	void posi_pop(void);
	void posi_clear(void);

	CStream& operator += (sint32 offset);
	CStream& operator -= (sint32 offset);

	/*************************************************
	Description:    // ��������
	Oter:           // ������ 0 ��ʼ����ǰ position λ�õ�����
	*************************************************/
	void erase(void);

	/*************************************************
	Description:    // ��ȡ�������±�����λ��
	Input:          // position : ������ָ��λ��
	Return:         // ���������ݵ�Ԫ����
	*************************************************/
	uint8& operator [] (sint32 position);

	/*************************************************
	Description:    // �ӵ�ǰ����ָ��λ�ö�ȡ�������е�����
	Input:          // pvData : ���ݻ���
	// uiSize : ��ȡ����
	*************************************************/
	void read(void *pvData, uint32 uiSize);

	/*************************************************
	Description:    // �ӵ�������ָ��λ��д������
	Input:          // pvData : ��Ҫд��Ķ�����ָ�����
	Return:         // uiSize : ��Ҫд������ݳ���
	*************************************************/
	void write(const void *pvData, uint32 uiSize);

	/*************************************************
	Description:    // �ӵ�ǰָ��λ�ö�ȡ�ַ���
	Input:          // strValue : ��ȡ�����ݽ����浽�� std::string ������
	// uiSize : ��Ҫ��ȡ�����ݳ���
	*************************************************/
	void read(std::string &strValue, uint32 uiSize);

	/*************************************************
	Description:    // �ڵ�ǰָ��λ����д������
	Input:          // strValue : ��Ҫд��� std::string �ַ�������
	// uiSize : ��Ҫд������ݳ���
	*************************************************/
	void write(const std::string &strValue, uint32 uiSize);
};
#endif