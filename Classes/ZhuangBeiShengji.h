//
//  ZhuangBeiShengji.h
//  kapai
//
//  Created by qin on 14-1-9.
//
//

#ifndef __kapai__ZhuangBeiShengji__
#define __kapai__ZhuangBeiShengji__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace extension;
using namespace std;
using namespace ui;

class ZhuangBeiShengjiLayer : public Layer
{
    public :
	ZhuangBeiShengjiLayer();
	bool init(ZhuangBeiType type);
	~ZhuangBeiShengjiLayer();
    void getHeros();
    Layer *m_pUiLayer;
    ZhuangBeiType m_type;
//    virtual void registerWithTouchDispatcher(void);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //Layout* layout;
    Label *coinlabel;
public:
    Widget* example_root;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    //void change(int index);
    void updateHero();
    int getexp(float x, int n);
    void close(CCObject *sender);
};

#endif /* defined(__kapai__ZhuangBeiShengji__) */
