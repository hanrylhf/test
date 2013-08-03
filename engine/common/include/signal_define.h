#ifndef SIGNAL_SIGNAL_DEFINE_H
#define SIGNAL_SIGNAL_DEFINE_H

namespace common
{
#include <iostream>
#include <map>
#include <boost/signals2.hpp>
#include <boost/function.hpp>

// 回调函数签名
#define SLOT_CALLBACK_TYPE	void( unsigned int ui32EventID, unsigned int ui32SrcType, unsigned int ui32SrcID, void* pContext, unsigned int ui32Len )

typedef boost::function< SLOT_CALLBACK_TYPE > SlotCallbackType;

}

#endif // SIGNAL_SIGNAL_DEFINE_H