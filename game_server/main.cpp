#include "../common/head.h"
#include "../common/omg_type.h"
#include "../common/system_util.h"
#include "../net/serversocket.h"
#include "../net/client_socket.h"
#include "../common/CThreadManage.h"
#include "common_func.h"
#include "ConnectDBServerJob.h"
#include "CGameMsgDispatcher.h"
#include "GameConfigManage.h"
#include "../soccer_ai/soccer_formation.h"
#include "../soccer_ai/pass_refer_table.h"
#include "../soccer_ai/speed_refer_table.h"
#include "CGameTimerEventHandler.h"
#include "../common/rand_generator.h"


DEFINE_int32(index,0,"server index")
;
DEFINE_bool(daemon,false,"if start not as daemon")
;
DEFINE_int32(c_move_id,3,"default move_id")
;
#define CONFIG_FILE "config/server.xml"
#define GAME_TO_GATE_CON_FILE	"config/game_to_gate.xml"

void test_rand(){
	for(int i=0;i<100;i++){
		LOG(INFO)<<RAND_INT;
	}

}
char* public_key;
//初始化日志系统
void init_server_log(int argc, char** argv) {
	google::ParseCommandLineFlags(&argc, &argv, true);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();

	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if (loadFile == false) {
		LOG(ERROR) << "Loading file error ....";
		exit(1);
	}

	TiXmlNode* firstNode = doc.FirstChild("game_server");
	if (firstNode == NULL) {
		LOG(ERROR) << "ERROR OF XML FILE";
		exit(1);
	}

	TiXmlElement *ele = firstNode->ToElement();
	const char* log_info_dir = ele->Attribute("log_info_dir");
	const char* log_error_dir = ele->Attribute("log_error_dir");

	google::SetLogDestination(google::INFO, log_info_dir);
	google::SetLogDestination(google::ERROR, log_error_dir);

}

void init_gate_server_connection_by_xml(IMsgDispatcher* msg_dispatcher){
	TiXmlDocument doc(GAME_TO_GATE_CON_FILE);
	bool loadFile = doc.LoadFile();
	if (loadFile == false) {
		LOG(ERROR) << "Loading file error ....";
		exit(1);
	}

	TiXmlNode* root = doc.FirstChildElement("gate_server_list");

	if ( root )
	{
		TiXmlNode* gate_node = NULL;
		for(gate_node=root->FirstChild( "gate_server" );gate_node!= NULL;gate_node=root->IterateChildren(gate_node)){
			TiXmlElement* gate_element = gate_node->ToElement();
			char	ip[16];
			strcpy(ip,gate_element->Attribute("ip"));
			int 	port;
			gate_element->QueryIntAttribute("s_port",&port);
			LOG(INFO)<<"gate node"<<ip<<":"<<port;
			CConnectToGateJob *gateJob = new CConnectToGateJob(ip,port,msg_dispatcher);
			if(gateJob->IsConnected()){
				LOG(INFO)<<"game server "<<server_index<<" connect to "<<gateJob->GetConnectionIpPortStr()<<" success!";
				//GateConManager::GetInstance()->RegisterGateConnection(gateJob->GetConnectionIpPortStr(),gateJob);
				GateConManager::GetInstance()->AddConnectionToVerifyList(gateJob);
				omg::CThreadManage::AddJob(gateJob);
			}else{
				LOG(ERROR)<<"game server "<<server_index<<" connect to "<<gateJob->GetConnectionIpPortStr()<<" false !";
			}
		}

	}

}


void load_gameserver_info(){
	TiXmlDocument doc(CONFIG_FILE);
	bool loadFile = doc.LoadFile();
	if (loadFile == false) {
		LOG(ERROR) << "Loading file error ....";
		exit(1);
	}

	TiXmlNode* firstNode = doc.FirstChild("game_server");
	if (firstNode == NULL) {
		LOG(ERROR) << "ERROR OF XML FILE";
		exit(1);
	}

	TiXmlElement *ele = firstNode->ToElement();
	public_key = new char[20];
	strcpy(public_key,ele->Attribute("public_key"));
	ele->QueryIntAttribute("server_index",&server_index);
	LOG(INFO)<<"server index "<<server_index;
}

int g_move_id = -1;
int server_index = 1;
int server_type = 2;
GameConfig g_game_config;

int main(int argc, char** argv) {
	//begin pool threadpool

	init_server_log(argc, argv);
	load_gameserver_info();
	server_index = FLAGS_index;
	g_move_id = FLAGS_c_move_id;
	if (FLAGS_daemon) {
		init_daemon();
	}
	
    //init card info
	CGameConfigManager::GetInstance();

	omg::CThreadManage::BeginPoolThread(3, 4);

	//初始化逻辑处理线程
	CGameMsgDispatcher *msg_dispatcher = new CGameMsgDispatcher(2);
	msg_dispatcher->start(false);

	//初始化定时器线程
	CGameTimerEventHandler *timer_thread = new CGameTimerEventHandler(
			msg_dispatcher, 1);
	omg::CThreadManage::AddJob(timer_thread);

	//初始化连接数据库线程
	std::string db_ip;
	int db_port;
	load_db_server_info_from_xml(db_ip, db_port);
	CConnectToDB *DbJob = new CConnectToDB(db_ip.c_str(), db_port,
			msg_dispatcher);

	//初始化连接网关线程
	std::string gate_ip;
	int gate_port;
	init_gate_server_connection_by_xml(msg_dispatcher);

	msg_dispatcher->set_connection_to_db(DbJob);

	//start thread of connect to gate 
	//omg::CThreadManage::AddJob(GateJob);

	//init pitch regions.
	SoccerFormation::init_pitch_region();
	// init pass refer tables;
	pass_refer_table_init();
	//init cross refer tables
	cross_refer_table_init();
	//init speed refer table
	speed_refer_table_init();
	//init game config files maps
	init_player_attr_field_map();

	g_game_config.init();
	sleep(60 * 60 * 24 * 365);
}
