#include "base_stream.h"

/*************************************************
  Description:    // ���캯��
  Input:          // uiSize ���ݻ���Ԥ�����С
*************************************************/
CStream::CStream( uint32 uiSize/* = 1024 */)
{
    m_Buff.reserve(uiSize);
    m_Pointer = m_Buff.end();
    m_MsgHead = NULL;
}

/*************************************************
  Description:    // ��������, �����౻����
*************************************************/
CStream::~CStream()
{
}

/*************************************************
  Description:    // ��ȡ��������ǰ�����ֽ���
  Return:         // ���ؿ����ֽ���
*************************************************/
uint32 CStream::available(void)
{
    return (uint32)( m_Buff.end() - m_Pointer );
}

/*************************************************
  Description:    // ��ȡ�����������ܳ���
  Return:         // �����������ܳ���
*************************************************/
uint32 CStream::length(void)
{
    return (uint32)( m_Buff.size() );
}

/*************************************************
  Description:    // ���������
*************************************************/
void CStream::clear(void)
{
    m_Buff.clear();
    m_Pointer = m_Buff.end();

    m_Stack.clear();
}

/*************************************************
  Description:    // ���û������ߴ�
*************************************************/
void CStream::resize( uint32 size )
{
    m_Buff.resize( size );
    m_Pointer = m_Buff.end();

    m_Stack.clear();
}

/*************************************************
  Description:    // ��ȡ��������ǰָ��λ��
  Return:         // ����������ָ��λ������
  Oter:           // �� 0 ��ʼ
*************************************************/
uint32 CStream::position(void)
{
    return (uint32)( m_Pointer - m_Buff.begin() );
}

/*************************************************
  Description:    // ����������ָ��λ��
  Oter:           // �� 0 ��ʼ
*************************************************/
void CStream::position( uint32 uiPosition )
{
    if ( uiPosition > m_Buff.size() )
    {
        //throw new exception( "ָ�����ó�����������Χ!" );
        return;
    }

    m_Pointer = m_Buff.begin() + uiPosition;
}

void CStream::posi_push(void)
{
    m_Stack.push_front( position() );
}

void CStream::posi_pop(void)
{
    position( *m_Stack.begin() );
    m_Stack.pop_front();
}

void CStream::posi_clear(void)
{
    m_Stack.clear();
}

CStream& CStream::operator += (sint32 offset)
{
    position( position() + offset );
    return (*this);
}
CStream& CStream::operator -= (sint32 offset)
{
    position( position() - offset );
    return (*this);
}

/*************************************************
  Description:    // ��������
  Oter:           // ������ 0 ��ʼ����ǰ position λ�õ�����
*************************************************/
void CStream::erase(void)
{
    m_Buff.erase( m_Buff.begin(), m_Pointer );
    m_Pointer = m_Buff.begin();

    m_Stack.clear();
}

/*************************************************
  Description:    // ��ȡ�������±�����λ��
  Input:          // position : ������ָ��λ��
  Return:         // ���������ݵ�Ԫ����
*************************************************/
uint8& CStream::operator [] (sint32 position)
{
    return *( m_Buff.begin() + position );
}

/*************************************************
  Description:    // �ӵ�ǰ����ָ��λ�ö�ȡ�������е�����
  Input:          // pvData : ���ݻ���
                  // uiSize : ��ȡ����
*************************************************/
void CStream::read( void *pvData, uint32 uiSize )
{
    if ( available() < uiSize )
    {
        //throw new exception( "û���㹻�Ŀɶ�������!" );
        return;
    }

    memcpy( pvData, &(*m_Pointer), uiSize );
    m_Pointer += uiSize;
}

/*************************************************
  Description:    // �ӵ�������ָ��λ��д������
  Input:          // pvData : ��Ҫд��Ķ�����ָ�����
  Return:         // uiSize : ��Ҫд������ݳ���
*************************************************/
void CStream::write( const void *pvData, uint32 uiSize )
{
    uint32 posi = position();

    m_Buff.resize( posi + uiSize );
    memcpy( &m_Buff[ posi ], pvData, uiSize );
    m_MsgHead = &m_Buff[0];
    m_Pointer = m_Buff.end();
}

/*************************************************
  Description:    // �ӵ�ǰָ��λ�ö�ȡ�ַ���
  Input:          // strValue : ��ȡ�����ݽ����浽�� std::string ������
                  // uiSize : ��Ҫ��ȡ�����ݳ���
*************************************************/
void CStream::read( std::string &strValue, uint32 uiSize )
{
    strValue.resize( uiSize );
    read( (char*)strValue.c_str(), uiSize );
}

/*************************************************
  Description:    // �ڵ�ǰָ��λ����д������
  Input:          // strValue : ��Ҫд��� std::string �ַ�������
                  // uiSize : ��Ҫд������ݳ���
*************************************************/
void CStream::write(const std::string &strValue, uint32 uiSize )
{
    write( strValue.c_str(), uiSize );
}