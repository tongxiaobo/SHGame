//
//  GroupLayer.h
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#ifndef __kapai__GroupLayer__
#define __kapai__GroupLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "GameData.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace extension;
using namespace ui;

class GroupLayer : public CCLayer
{
    public :
	GroupLayer();
	bool init();
	~GroupLayer();
    void menuPauseCallback(CCObject *sender);
    void close();
    int selectIndex;
    void addHero(CCObject *sender);
    void changeHero(CCObject *sender);
    void onExit();
public:
    Widget* example_root;
    CCRect transRect;
//    void draw();
    Layer *m_pUiLayer;
    //CCControlButton *selectButton;
    Button *selectButton;
    CCPoint oldPositon;
//    virtual void  registerWithTouchDispatcher();
//    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
};

#endif /* defined(__kapai__GroupLayer__) */
