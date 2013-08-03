#ifndef SIGNAL_SIGNAL_IMP_H
#define SIGNAL_SIGNAL_IMP_H

#include "signal_define.h"

class SignalMgr 
{
	typedef boost::signals2::signal< SLOT_CALLBACK_TYPE >	SignalType;
	// key : order
	typedef std::map<unsigned int,SignalType*>				Order2SignalType;
	// key : 信号id 
	typedef std::map<unsigned int,Order2SignalType>			SignalCenterType;
public:
	// 连接信号
	bool ConnectSignal( unsigned int ui32EventID, 
		unsigned int ui32SrcType, 
		unsigned int ui32SrcID,
		common::CallbackType& fnSlot,
		unsigned int ui32Order,
		const string& strDesc
		)
	{
		SignalType* pSignal = NULL;
		SignalCenterType::iterator it = map_signal_.find( ui32EventID );
		if ( it != map_signal_.end() ) {
			Order2SignalType& rOrder2Signal = it->second;
			Order2SignalType::iterator itSignal = rOrder2Signal.find( ui32Order );
			if ( itSignal == rOrder2Signal.end() )
				pSignal = itSignal->second;	
		}
		else {
			Order2SignalType& rOrder2Signal = map_signal_[ ui32EventID ];
			pSignal = new SignalType;
			if ( pSignal )
				rOrder2Signal.insert( make_pair(ui32EventID,pSignal) );
		}
		if ( pSignal ) {
			pSignal->connect( fnSlot );
			return true;
		} else
			return false;
		
	}

	// 发射信号
	void FireSignal( unsigned int ui32EventID, 
		unsigned int ui32SrcType, 
		unsigned int ui32SrcID, 
		void* pContext, 
		unsigned int ui32Len 
		)
	{
		SignalCenterType::iterator it = map_signal_.find( ui32EventID );
		if ( it != map_signal_.end() ) {
			Order2SignalType& rOrder2Signal = it->second;
			for ( Order2SignalType::itSignal = rOrder2Signal.begin(); itSignal != rOrder2Signal.end(); ++itSignal ) {
				if ( itSignal->second ) {
					SignalType* pSignal = itSignal->second;	
					(*pSignal)( ui32EventID, ui32SrcType, ui32SrcID, pContext );
				}
			}
		}
	}

private:
	// 信号容器
	SignalCenterType	map_signal_;
};

void slots1(		
			unsigned int ui32EventID, 
			unsigned int ui32SrcType, 
			unsigned int ui32SrcID, 
			void* pContext, 
			unsigned int ui32Len) 
{
	std::cout << "slot1 called " << ui32EventID << "," << ui32Len << std::endl;
}

void slots2(		
			unsigned int ui32EventID, 
			unsigned int ui32SrcType, 
			unsigned int ui32SrcID, 
			void* pContext, 
			unsigned int ui32Len) 
{
	std::cout << "slot2 called " << ui32EventID << "," << ui32Len << std::endl;
}


void signal_test()
{

	SignalMgr sig;

	CallbackType fun1 = slots1;
	sig.ConnectSignal( 1, fun1 );
	fun1 = slots2;
	sig.ConnectSignal( 1, fun1 );

	sig.FireSignal( 1, 0, 0,NULL,0 );
}

#endif // SIGNAL_SIGNAL_IMP_H