/*
 * GateConManager.h
 *
 *  Created on: 2013-4-3
 *      Author: guanlei
 */

#ifndef GATECONMANAGER_H_
#define GATECONMANAGER_H_
#include "../common/lock.h"
#include "ConnectToGateJob.h"

class GateConManager {
public:
	GateConManager();
	virtual ~GateConManager();
	CConnectToGateJob*	GetGateConnectionByIPP(std::string ip_port){
		CON_GATE_ITR	itr = _connection_map.find(ip_port);
		if(itr != _connection_map.end()){
			return itr->second;
		}
		return NULL;
	}

	void RegisterGateConnection(std::string ip_port,CConnectToGateJob* job){
		_lock.lock();
		_connection_map[ip_port] = job;
		_lock.unlock();
	}

	static GateConManager*	GetInstance(){
		if(_instance == NULL){
			_instance = new GateConManager();
		}
		return	_instance;
	}

	void UnRegisterGateConnection(std::string& ip_port){
		_lock.lock();
		std::map<std::string,CConnectToGateJob*>::iterator itr = _connection_map.find(ip_port);
		if(itr == _connection_map.end()){
			LOG(INFO)<<"Gate Connection"<<ip_port<<"  Can't find";
		}else{
			delete itr->second;
			_connection_map.erase(itr);
		}
		_lock.unlock();
	}


	void BrocastAllConnection(MsgBase* pMsgBase){
		std::map<std::string,CConnectToGateJob*>::iterator itr = _connection_map.begin();
		while(itr != _connection_map.end()){
			itr->second->SendMsgToGateServer(pMsgBase);
			itr++;
		}
	}

	void AddConnectionToVerifyList(CConnectToGateJob* conn){
		_lock.lock();
		_connection_unverify_list.push_back(conn);
		_lock.unlock();
	}

	void ModiferConnectionToRegister(std::string ip_port){
		std::list<CConnectToGateJob*>::iterator itr = _connection_unverify_list.begin();
		_lock.lock();
		while(itr != _connection_unverify_list.end()){
			LOG(INFO)<<ip_port.c_str()<<" : "<< (*itr)->GetConnectionIpPortStr();
			if(ip_port == (*itr)->GetConnectionIpPortStr()){
				_connection_map[ip_port] = *itr;
				_connection_unverify_list.erase(itr);
				_lock.unlock();
				return;
			}
			itr++;
		}
		_lock.unlock();
	}

private:
	std::map<std::string,CConnectToGateJob*>	_connection_map;
	typedef std::map<std::string,CConnectToGateJob*> CONN_GATE_MAP;
	typedef std::map<std::string,CConnectToGateJob*>::iterator	CON_GATE_ITR;
	std::list<CConnectToGateJob*>				_connection_unverify_list;
	static GateConManager	*_instance;
	omg::MutexLock	_lock;
	//IMsgDispatcher*	_msg_dispatcher;
};

#endif /* GATECONMANAGER_H_ */
