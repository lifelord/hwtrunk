#include "base_stream.h"

/*************************************************
  Description:    // 构造函数
  Input:          // uiSize 数据缓存预分配大小
*************************************************/
CStream::CStream( uint32 uiSize/* = 1024 */)
{
    m_Buff.reserve(uiSize);
    m_Pointer = m_Buff.end();
    m_MsgHead = NULL;
}

/*************************************************
  Description:    // 析构函数, 允许类被继续
*************************************************/
CStream::~CStream()
{
}

/*************************************************
  Description:    // 获取数据流当前可用字节数
  Return:         // 返回可用字节数
*************************************************/
uint32 CStream::available(void)
{
    return (uint32)( m_Buff.end() - m_Pointer );
}

/*************************************************
  Description:    // 获取数据流数据总长度
  Return:         // 返回数据流总长度
*************************************************/
uint32 CStream::length(void)
{
    return (uint32)( m_Buff.size() );
}

/*************************************************
  Description:    // 清除数据流
*************************************************/
void CStream::clear(void)
{
    m_Buff.clear();
    m_Pointer = m_Buff.end();

    m_Stack.clear();
}

/*************************************************
  Description:    // 重置缓冲区尺寸
*************************************************/
void CStream::resize( uint32 size )
{
    m_Buff.resize( size );
    m_Pointer = m_Buff.end();

    m_Stack.clear();
}

/*************************************************
  Description:    // 获取数据流当前指针位置
  Return:         // 返回数据流指针位置索引
  Oter:           // 从 0 开始
*************************************************/
uint32 CStream::position(void)
{
    return (uint32)( m_Pointer - m_Buff.begin() );
}

/*************************************************
  Description:    // 设置数据流指针位置
  Oter:           // 从 0 开始
*************************************************/
void CStream::position( uint32 uiPosition )
{
    if ( uiPosition > m_Buff.size() )
    {
        //throw new exception( "指针设置超出数据流范围!" );
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
  Description:    // 缩减数据
  Oter:           // 缩减从 0 开始到当前 position 位置的数据
*************************************************/
void CStream::erase(void)
{
    m_Buff.erase( m_Buff.begin(), m_Pointer );
    m_Pointer = m_Buff.begin();

    m_Stack.clear();
}

/*************************************************
  Description:    // 获取数据流下标引用位置
  Input:          // position : 数据流指针位置
  Return:         // 数据流数据单元引用
*************************************************/
uint8& CStream::operator [] (sint32 position)
{
    return *( m_Buff.begin() + position );
}

/*************************************************
  Description:    // 从当前数据指针位置读取数据流中的数据
  Input:          // pvData : 数据缓冲
                  // uiSize : 读取长度
*************************************************/
void CStream::read( void *pvData, uint32 uiSize )
{
    if ( available() < uiSize )
    {
        //throw new exception( "没有足够的可读数据流!" );
        return;
    }

    memcpy( pvData, &(*m_Pointer), uiSize );
    m_Pointer += uiSize;
}

/*************************************************
  Description:    // 从当产数据指针位置写入数据
  Input:          // pvData : 需要写入的二进制指针变量
  Return:         // uiSize : 需要写入的数据长度
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
  Description:    // 从当前指针位置读取字符串
  Input:          // strValue : 读取的数据将保存到该 std::string 变量中
                  // uiSize : 需要读取的数据长度
*************************************************/
void CStream::read( std::string &strValue, uint32 uiSize )
{
    strValue.resize( uiSize );
    read( (char*)strValue.c_str(), uiSize );
}

/*************************************************
  Description:    // 在当前指针位置中写入数据
  Input:          // strValue : 需要写入的 std::string 字符串变量
                  // uiSize : 需要写入的数据长度
*************************************************/
void CStream::write(const std::string &strValue, uint32 uiSize )
{
    write( strValue.c_str(), uiSize );
}