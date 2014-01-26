#ifndef _SERVER_MANAGE_H_
#define _SERVER_MANAGE_H
#include "../common/head.h"
#include "../net/socketclient.h"
#include <set>
using namespace std;

class GameServerClient :public socket_client{
public:
	GameServerClient(){
        
	}

	~GameServerClient(){

	}

    void on_timeout(timer_manager* timer_mgr);

public:
	int index;
	std::set<int> _match_list;
private:
    template_timer<GameServerClient,&GameServerClient::on_timeout> _timer;
};

class CServerManage {
protected:
	CServerManage() {
		_lock.init();
	}

public:
	static CServerManage* GetInstance() {
		if (_m_instance == NULL) {
			_m_instance = new CServerManage();
		}
		return _m_instance;
	}
	void RegisterServer(int index, EPollSocket* socket) {
		GameServerClient *client = new GameServerClient();
		client->index = index;
		client->connection = socket;
		client->server_ip = inet_ntoa(socket->get_client_ip_address().sin_addr);
		VLOG(2)<<"GameServer connect from "<<client->server_ip.c_str();
		_server_map[index] = client;
	}

	void RemoveServer(int index){
		SERVER_ITR itr = _server_map.find(index);
		if(itr != _server_map.end()){
			_server_map.erase(itr);
		}
	}

	//先选取承载比赛最小的服务器
	GameServerClient* PickServerToRunMatch() {
		if (_server_map.size() <= 0) {
			VLOG(1)<<"没有游戏服务器注册";
			return NULL;
		}

		SERVER_ITR itr = _server_map.begin();
		GameServerClient* server_pick = itr->second;
		while(itr != _server_map.end()) {
			if(itr->second->_match_list.size() < server_pick->_match_list.size()){
					server_pick = itr->second;
				}
				itr++;
			}
		return server_pick;
	}

	GameServerClient* GetGameServerBySocketFd(int fd){
		_lock.lock();
		SERVER_ITR itr = _server_map.begin();
		while(itr != _server_map.end()) {
			if(fd == itr->second->connection->fd){
				_lock.unlock();
				return itr->second;
			}
			itr++;
		}
		_lock.unlock();
		return NULL;
	}

	//获取mid所在的比赛的服务器
	GameServerClient* GetMatchRunServer(int mid) {
		_lock.lock();
		SERVER_ITR itr = _server_map.begin();
		while(itr != _server_map.end()) {
			std::set<int>::iterator itr_match = itr->second->_match_list.begin();
			while(itr_match != itr->second->_match_list.end()){
				if(*itr_match == mid){
					_lock.unlock();
					return itr->second;
				}
				itr_match++;
			}
			itr++;
		}
		_lock.unlock();
		return NULL;
	}

	//比赛结束，移除比赛
	void RemoveMatch(int server_index,int mid){
		_lock.lock();
		SERVER_ITR itr = _server_map.find(server_index);
		if(itr != _server_map.end()){
			itr->second->_match_list.erase(mid);
		}
		_lock.unlock();
	}


	//添加一个比赛到比赛服务器中
	GameServerClient* AddNewMatch(int mid) {
		_lock.lock();
		GameServerClient* server = PickServerToRunMatch();
		if(server != NULL) {
			server->_match_list.insert(mid);
		}
		_lock.unlock();
		return server;
	}

	GameServerClient* AddMatchToServerByIp(std::string ip,int mid){
		_lock.lock();
		std::map<int,GameServerClient*>::iterator itr = _server_map.begin();
		while(itr != _server_map.end()){
			if(itr->second->server_ip == ip){
				itr->second->_match_list.insert(mid);
				_lock.unlock();
				return itr->second;
			}
			itr++;
		}
		_lock.unlock();
		return NULL;
	}

	int GetMatchServerOnlineCount(){
		return _server_map.size();	
	}

private:
	static CServerManage* _m_instance;
	omg::MutexLock _lock;
	std::map<int,GameServerClient*> _server_map;
	typedef std::map<int,GameServerClient*>::iterator SERVER_ITR;
};

#endif
