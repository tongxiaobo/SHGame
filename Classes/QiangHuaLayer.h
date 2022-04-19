//
//  QiangHuaLayer.h
//  kapai
//
//  Created by qin on 14-3-8.
//
//

#ifndef __kapai__QiangHuaLayer__
#define __kapai__QiangHuaLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace extension;
using namespace std;
using namespace ui;

class QiangHuaLayer : public Layer
{
    public :
	QiangHuaLayer();
	bool init(HeroType hero);
	~QiangHuaLayer();
    void getHeros();
    Layer *m_pUiLayer;
    HeroType m_hero;
//    virtual void registerWithTouchDispatcher(void);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //Layout* layout;
public:
    Widget* example_root;
    void qianghua(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    void change(int index);
    void updateHero();
    void close(CCObject *sender);
private:
    bool bUpgrade;
};
#endif /* defined(__kapai__QiangHuaLayer__) */
