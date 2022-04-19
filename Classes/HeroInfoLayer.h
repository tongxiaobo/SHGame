//
//  HeroInfoLayer.h
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#ifndef __kapai__HeroInfoLayer__
#define __kapai__HeroInfoLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

//using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
using namespace ui;

class HeroInfoLayer : public Layer
{
    public :
	HeroInfoLayer();
	bool init(HeroType hero);
	~HeroInfoLayer();
    void ReadJson();
    HeroType m_hero;
public:
    Widget* example_root;
    Layer * m_pUiLayer;
    Layer *layer;
    ui::ScrollView *scrollView;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    void setData(HeroType hero);
    void close(CCObject *sender);
    void updateText(int tag);
};

#endif /* defined(__kapai__HeroInfoLayer__) */
