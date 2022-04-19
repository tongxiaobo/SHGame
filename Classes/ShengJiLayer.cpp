//
//  ShengJiLayer.cpp
//  kapai
//
//  Created by qin on 14-1-7.
//
//

#include "ShengJiLayer.h"
#include "ZhuangBeiLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
#include "HeroLayer.h"
#define HEROUP 10
ShengJiLayer::ShengJiLayer()
{
	
}
ShengJiLayer::~ShengJiLayer()
{
	
}
bool ShengJiLayer::init(HeroType hero)
{
    if(!CCLayer::init()){
        return false;
    }
    m_hero=hero;
    setTouchEnabled(true);
    m_pUiLayer=Layer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(m_pUiLayer);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    ImageView* imageView = ImageView::create();
    imageView->loadTexture("herolistbg.png");
    
    imageView->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addChild(imageView);
    
    ImageView* heroImage = ImageView::create();
    heroImage->loadTexture(hero.textureName.c_str());
    heroImage->setPosition(ccp(winSize.width/2,winSize.height/2));
    heroImage->setTag(1);
    m_pUiLayer->addChild(heroImage);
    
    ImageView* coinImage = ImageView::create();
    coinImage->loadTexture("coins.png");
    coinImage->setPosition(ccp(coinImage->getContentSize().width/2+30,winSize.height/2));
    m_pUiLayer->addChild(coinImage);
    
    Label *label = Label::create();
    string str = hero.name + " +" + to_string(hero.exlevel);
    label->setSystemFontSize(48);
    label->setColor(ccMAGENTA);
    label->setPosition(ccp(winSize.width/2, winSize.height/2+300));
    label->setString(str);
    m_pUiLayer->addChild(label);
    
    Button *btn=Button::create();
    btn->setTouchEnabled(true);
    btn->loadTextures("heroup1.png","heroup2.png","heroup2.png");
    btn->setPosition(ccp(winSize.width/2,winSize.height/2-200));
//    btn->addReleaseEvent(this, coco_releaseselector(ShengJiLayer::menuPauseCallback));
    m_pUiLayer->addChild(btn);
    
    Button *btnclose=Button::create();
    btnclose->setTouchEnabled(true);
    btnclose->loadTextures("close1.png","close2.png","close2.png");
    btnclose->setPosition(ccp(winSize.width-60, winSize.height/2+300));
//    btnclose->addReleaseEvent(this, coco_releaseselector(ShengJiLayer::close));
    m_pUiLayer->addChild(btnclose);
    
    Label *levellabel = Label::create();
    levellabel->setSystemFontSize(32);
    levellabel->setColor(ccYELLOW);
    levellabel->setTag(8);
    string levelstr = "等级LV " + to_string(hero.level) + "-->LV " + to_string(hero.level+1);
    levellabel->setString(levelstr);
    levellabel->setPosition(ccp(winSize.width/2, winSize.height/2-300));
    m_pUiLayer->addChild(levellabel);
    
    coinlabel = Label::create();
    coinlabel->setPosition(ccp(120,winSize.height/2-coinImage->getContentSize().height));
    coinlabel->setSystemFontSize(32);
    coinlabel->setColor(ccYELLOW);
    int money=80*hero.level+getexp(1.1, hero.level);
    coinlabel->setString("银两:"+to_string(money));
    m_pUiLayer->addChild(coinlabel);
        
    getHeros();
    return true;
}
int ShengJiLayer::getexp(float x, int n)
{
    if(n == 0)
    {
        return HEROUP;
    }
    return x * getexp(x, n-1);
}
void ShengJiLayer::getHeroInfo(CCObject *sender)
{
    HeroInfoLayer *info=new HeroInfoLayer();
    info->autorelease();
    addChild(info);
}
void ShengJiLayer::menuPauseCallback(CCObject *sender)
{
    Button * btn=(Button*)sender;
    int tag=btn->getTag();
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    int totalmoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("money",20000);
    CCUserDefault::sharedUserDefault()->flush();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int i=0; i<Heros.size(); ++i)
    {
        HeroType hero=Heros[i];
        if(hero.index==m_hero.index)
        {
            int needmoney=80*hero.level+getexp(1.1, hero.level);
            //int needmoney=0;
            int level=GameData::shareGameData()->mlevel;
            if(hero.level>=level)
            {
                CCSprite *bg=CCSprite::create("tipbg.png");
                bg->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(bg,1);
                CCActionInterval *action0=CCFadeOut::create(2);
                bg->runAction(action0);
                char str[64];
                sprintf(str,"卡牌等级不能大于主角等级");
                CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
                tiplabel->setColor(ccRED);
                tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(tiplabel,100);
                CCActionInterval *action=CCFadeOut::create(2);
                tiplabel->runAction(action);
                return;
            }
            if(totalmoney>=needmoney)
            {
            totalmoney-=needmoney;
            //printf("heroindex===%d,%d\n",hero.index,m_hero.index);
            hero.level+=1;
            Label *label = (Label*)m_pUiLayer->getChildByTag(8);
            char str[64];
            sprintf(str,"等级LV %d-->LV %d",hero.level,hero.level+1);
            label->setString(str);
            sprintf(str,"银两:%d",needmoney);
            coinlabel->setString(str);
            GameData::shareGameData()->setMoney(totalmoney);
            GameData::shareGameData()->setHero(hero);
            }
            else
            {
                CCSprite *bg=CCSprite::create("tipbg.png");
                bg->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(bg,1);
                CCActionInterval *action0=CCFadeOut::create(2);
                bg->runAction(action0);
                char str[32];
                sprintf(str,"金币不够");
                 CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
                tiplabel->setColor(ccRED);
                tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
               addChild(tiplabel,100);
                CCActionInterval *action=CCFadeOut::create(2);
                tiplabel->runAction(action);
            }
        }
    }
}
void ShengJiLayer::close(CCObject *sender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_HERO_UPDATE, (CCObject*)(intptr_t)0);
    removeFromParentAndCleanup(true);
}
void ShengJiLayer::change(int index)
{

}
void ShengJiLayer::getHeros()
{

}
void ShengJiLayer::updateHero()
{
}
//void ShengJiLayer::registerWithTouchDispatcher(void)
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127-1, false);
//    CCLayer::registerWithTouchDispatcher();
//}
//bool ShengJiLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//	return true;
//}
//
//void ShengJiLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    
//}
//void ShengJiLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//  
//}
