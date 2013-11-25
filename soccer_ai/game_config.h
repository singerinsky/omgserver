#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#include "../common/head.h"
#include <string>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

typedef enum
{
	player = 0,
	ball,
	mark,
	kick_off_config
} CONFIG_ENUM;

class GameConfig
{
public:
	void split_string_to_number_array(std::vector<double> &values, std::string &str, char delimiters)
	{
		values.clear();
		std::string::size_type pos2 = 0;
		std::string::size_type pos1 = 0;
        pos2 = str.find(delimiters);
        while (string::npos != pos2)
        {
        	values.push_back(atof(str.substr(pos1, pos2 - pos1).c_str()));
        	pos1 = pos2 + 1;
        	pos2 = str.find(delimiters, pos1);
        }
        values.push_back(atof(str.substr(pos1).c_str()));
	}


	GameConfig(void)
	{
	}

	int get_player_config(const char *attr_name)
	{
		std::string tmp_attr_name(attr_name);
		std::map<std::string, int>::iterator itr = _player_config.find(tmp_attr_name);
		if (itr != _player_config.end())
		{
			return itr->second;
		}

		return -1;
	}

	void get_kick_off_player(int pos, int &x, int &y)
	{
		char name[20];
		snprintf(name, 20, "player_pos_%d_x", pos);
		std::string tmp_attr_name(name);
		std::map<std::string,int>::iterator itr = _player_config.find(tmp_attr_name);
		if (itr != _player_config.end())
		{
			x = itr->second;
		}

		snprintf(name, 20, "player_pos_%d_y", pos);
		itr = _player_config.find(tmp_attr_name);
		if (itr != _player_config.end())
		{
			y = itr->second;
		}
	}

	std::vector<double> *get_player_mark_array(int player_position)
	{
		MARK_ITR itr = _mark_config.find(player_position);
		if (itr == _mark_config.end())
		{
			return NULL;
		}

		return &(itr->second);
	}

	bool init(void)
	{
		set_config(ball, "config_file/ball_config.xml");
		set_config(player, "config_file/player_config.xml");
		set_config(mark, "config_file/player_mark.xml");

		return true;
	}

	void view_all_value(void)
	{
		GameConfig::CONFIG_ITR itr = this->_player_config.begin();
		while (itr != _player_config.end())
		{
			itr++;
		}
	}

	bool reload(void)
	{
		this->_ball_config.clear();
		this->_pitch_config.clear();
		this->_player_config.clear();
		this->_team_config.clear();
		this->_mark_config.clear();
		init();

		return true;
	}

	void set_config(CONFIG_ENUM typ, const char *filePath)
	{
			xmlDocPtr doc; //定义解析文档指针
			xmlNodePtr curNode; //定义结点指针(你需要它为了在各个结点间移动)
			xmlChar *key;

			doc = xmlReadFile(filePath, "UTF-8", XML_PARSE_RECOVER);
			if (doc == NULL)
			{
				exit(1);
			}

			curNode = xmlDocGetRootElement(doc);
			curNode = curNode->xmlChildrenNode;
			while (curNode != NULL)
			{
				//取出节点中的内容
				if ((xmlStrcmp(curNode->name, (const xmlChar *) "text")))
				{
					key = xmlNodeGetContent(curNode);
					switch (typ)
					{
					case player:
					{
						std::string str;
						str.append((const char*)curNode->name);
						int value = atoi((const char*)key);
						_player_config[str] = value;
						break;
					}
					case ball:
					{
						std::string str;
						str.append((const char*)curNode->name);
						int value = atoi((const char*)key);
						_ball_config[str] = value;
						break;
					}
					case kick_off_config:
					{
						std::string str;
						str.append((const char*)curNode->name);
						double value = atof((const char*)key);
						_kick_off_config[str] = value;
						break;
					}
					case mark:
						{
							std::string str;
							str.append((const char*)curNode->name);
							int first_index = str.find('_');
							int index = atoi(str.substr(first_index+1).c_str());
							std::string value = (const char*)key;
							vector<double> values;
							split_string_to_number_array(values, value, ',');
							_mark_config[index] = values;
							break;
						}
					}
				}
				curNode = curNode->next;
			}
			  xmlFreeDoc (doc);
			  xmlCleanupParser();
	}

private:
		std::map<std::string, int> _ball_config;
		std::map<std::string, int> _player_config;
		std::map<std::string, int> _pitch_config;
		std::map<std::string, int> _team_config;
		std::map<std::string, double> _kick_off_config;
		std::map<int, std::vector<double> > _mark_config;
		typedef std::map<std::string, int>::iterator CONFIG_ITR;
		typedef std::map<int, std::vector<double> >::iterator MARK_ITR;

	//	char *file_path;
};

#endif
