/*
 * common_func.h
 *
 *  Created on: 2012-4-17
 *      Author: guanlei
 */

#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_
#include "../common/head.h"

void load_gate_server_info_from_xml(std::string& ip, int& port) {
	TiXmlDocument doc("config/server.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"载入xml文件失败!!";
		exit(1);
	}

	TiXmlElement *ele = doc.FirstChild("gate_server")->ToElement();
	if(ele != NULL) {
		ip = ele->Attribute("ip");
		port = atoi(ele->Attribute("s_port"));
	}
}

void load_db_server_info_from_xml(std::string& ip, int& port) {
	TiXmlDocument doc("config/server.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"载入xml文件失败!!";
		exit(1);
	}

	TiXmlElement *ele = doc.FirstChild("db_server")->ToElement();
	if(ele != NULL) {
		ip = ele->Attribute("ip");
		port = atoi(ele->Attribute("s_port"));
	}
}



#endif /* COMMON_FUNC_H_ */
