//
//  Config.cpp

#include "Config.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/fwd.h"

using namespace rapidjson;

CCArray *play_bullet;
CCArray *enemy_bullet;
CCArray *enemy_items;
CCArray *add_Sprites;
static  Config *g_config = NULL;

/**这里用的单例做的全局参数。JS版的直接就定义了一堆全局数组，真是方便*/
Config::Config():m_scoreValue(0),m_life(3),m_isAudioOn(true)
{

    ReadEnemy();
    ReadHero();
    ReadZhuangBei();
    printf("readjson\n");
    m_money=0;
    
    
}
Config::~Config()
{
    play_bullet->release();
    enemy_bullet->release();
    enemy_items->release();
    enemy_items = NULL;
    play_bullet = NULL;
    enemy_bullet = NULL;
    CCLOG("release config");

}

Config* Config::sharedConfig()
{
    if (!g_config) {
        g_config = new Config();
    }
    return g_config;
}
void Config::ReadEnemy()
{
    string path =FileUtils::getInstance()->fullPathForFilename("enemy.json");
    string content = FileUtils::getInstance()->getStringFromFile(path);

    Document jsonData;
    jsonData.Parse<0>(content.c_str());
    if (jsonData.HasParseError()) {
        log("GetParseError%d", jsonData.GetParseError());
    }
    rapidjson::Value& datas = jsonData["data"];

    for (int i = 0; i < datas.Size(); i++) {
        rapidjson::Value& dic = datas[i];
        EnemyType enemyType;
        int type= dic["type"].GetInt();
        enemyType.type =type;
        enemyType.name =dic["name"].GetString();
        enemyType.textureName =dic["picture"].GetString();
        enemyType.hp = dic["hp"].GetInt();
        enemyType.ap = dic["ap"].GetInt();
        enemyType.skillsid =dic["skillsid"].GetInt();
        enemyType.attackid=dic["attackid"].GetInt();
        enemyType.defend=dic["defend"].GetInt();
        enemyType.magicdefend=dic["magicdefend"].GetInt();
        m_enemyTypes.insert(map <int,EnemyType>::value_type(type,enemyType));
    }
}
void Config::ReadHero()
{
    string path =FileUtils::getInstance()->fullPathForFilename("hero.json");
    string content = FileUtils::getInstance()->getStringFromFile(path);

    Document jsonData;
    jsonData.Parse<0>(content.c_str());
    if (jsonData.HasParseError()) {
        log("GetParseError%d", jsonData.GetParseError());
    }
    rapidjson::Value& datas = jsonData["data"];

    for (int i = 0; i < datas.Size(); i++) {
        rapidjson::Value& dic = datas[i];
        HeroType enemyType;
        int type= dic["type"].GetInt();
        enemyType.type =type;
        enemyType.name =dic["name"].GetString();
        enemyType.exname =dic["exname"].GetString();
        enemyType.starname =dic["starname"].GetString();
        enemyType.textureName =dic["picture"].GetString();
        enemyType.skillsname =dic["skillsname"].GetString();
        enemyType.defend=0;
        enemyType.magicdefend=0;
        enemyType.hp = dic["hp"].GetInt();
        enemyType.ap = dic["ap"].GetInt();
        enemyType.skillsid =dic["skillsid"].GetInt();
        enemyType.attackid=dic["attackid"].GetInt();
//        enemyType.magic=dic["magic"].GetInt();
        enemyType.des=dic["des"].GetString();
        enemyType.number=dic["number"].GetInt();
        enemyType.card=dic["card"].GetInt();
        //printf("des===%s",enemyType.des.c_str());
        m_HeroTypes.insert(map <int,HeroType>::value_type(type,enemyType));
    }
}
void Config::ReadZhuangBei()
{
    string path =FileUtils::getInstance()->fullPathForFilename("cloth.json");
    string content = FileUtils::getInstance()->getStringFromFile(path);

    Document jsonData;
    jsonData.Parse<0>(content.c_str());
    if (jsonData.HasParseError()) {
        log("GetParseError%d", jsonData.GetParseError());
    }
    rapidjson::Value& datas = jsonData["datas"];

    for (int i = 0; i < datas.Size(); i++) {
        rapidjson::Value& dic = datas[i];
        ZhuangBeiType headType;
        int type= dic["type"].GetInt();
        headType.type =type;
        headType.name =dic["name"].GetString();
        headType.textureName =dic["picture"].GetString();
        headType.defender = dic["defend"].GetInt();
        headType.magicdefender = dic["magic"].GetInt();
        headType.star = dic["star"].GetInt();
        headType.hp = dic["hp"].GetInt();
        headType.ap = dic["ap"].GetInt();
        m_ZhuangTypes.insert(map <int,ZhuangBeiType>::value_type(type,headType));
    }
}

map<int,EnemyType> Config::getEnemyType()
{
    return m_enemyTypes;
}
map<int,HeroType> Config::getHerosType()
{
    return m_HeroTypes;
}
map<int,ZhuangBeiType> Config::getZhuangBei()
{
    return m_ZhuangTypes;
}
int Config::getScoreValue()
{
    return m_scoreValue;
}

void Config::setScoreValue(int score)
{
    m_scoreValue += score;
}
void Config::setMoney(int money)
{
    m_money+=money;
}
int Config::getMoney()
{
    return m_money;
}
int Config::getLifeCount()
{
    return m_life;
}
void Config::updateLifeCount()
{
    m_life--;
}

bool Config::getAudioState()
{
    return m_isAudioOn;
}

void Config::updateAudioState(bool isOn)
{
    m_isAudioOn = isOn;
}

void Config::resetConfig()
{
    m_scoreValue = 0;
    m_life = 3;
//    m_isAudioOn = true;
}
