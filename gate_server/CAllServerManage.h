#ifndef ALLSERVERMANAGEH_

#define ALLSERVERMANAGEH


#include "../common/head.h"
#include "GServer.h"

using namespace std;

class CALLServerManage
{
	public:
		static CALLServerManage* GetInstance(){
			if(_m_instance == NULL){
				_m_instance = new CALLServerManage();
			}
			return _m_instance;
		}
		void	RegisterServer(int index,GServerInfo* server){
			_server_map[index] = server;
		}	
		
		GServerInfo* 	GetServerByIndexId(int index){
			std::map<int,GServerInfo*>::iterator itr = _server_map.find(index);
			if(itr != _server_map.end()){
				return itr->second;
			}
			return NULL;
		}

		void UnRegisterServer(int index){
			std::map<int,GServerInfo*>::iterator itr = _server_map.find(index);
			if(itr != _server_map.end()){
				_server_map.erase(itr);
			}
		}

		GServerInfo*	GetOneServer(){
			if(_server_map.empty()){
				return NULL;
			}
			return (_server_map.begin()->second);
		}

		void BrocastAllServer(const char* msg,int msg_size){
			std::map<int,GServerInfo*>::iterator itr = _server_map.begin();
			while(itr != _server_map.end()){
				itr->second->SendData(msg,msg_size);
				itr++;
			}
		}

	private:
		static CALLServerManage* _m_instance;

		std::map<int,GServerInfo*>	_server_map;
};

#endif
