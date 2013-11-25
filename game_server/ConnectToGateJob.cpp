#include "ConnectToGateJob.h"


void CConnectToGateJob::ExecuteJob(){
	if(_client != NULL){
		LOG(INFO)<<"START LISTENING...";
		int sleep_time = 1;
		while(1){
			int	msg_size =_client->recvData();
			if(msg_size <= 0){
				LOG(ERROR)<<"与网关服务器连接断开!";
				_client->set_connection(false);
				reconnect:
				sleep(sleep_time);
				bool rst = _client->connectToServer();	
				if(rst == false){
					if(sleep_time < 60){
						sleep_time += 10;
					}else{
						sleep_time = 60;
					}
					LOG(INFO)<<"will reconnect after "<<sleep_time<<" seconds.";
					goto reconnect;	
				}else{
					sleep_time = 1;
					_client->set_msg_dispatcher(_msg_dispatcher);
					LOG(INFO)<<"重新连接网关服务器成功!";
				}
			}
		}


	}

}
