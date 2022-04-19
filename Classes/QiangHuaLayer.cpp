//
//  QiangHuaLayer.cpp
//  kapai
//
//  Created by qin on 14-3-8.
//
//

#include "QiangHuaLayer.h"
#include "ZhuangBeiLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
QiangHuaLayer::QiangHuaLayer()
{
	
}
QiangHuaLayer::~QiangHuaLayer()
{
	
}
bool QiangHuaLayer::init(HeroType hero)
{
    if(!CCLayer::init())
    {
        return false;
    }
    m_hero=hero;
    bUpgrade=false;
    m_pUiLayer=Layer::create();

    this->addChild(m_pUiLayer);
    Size winSize =Director::getInstance()->getWinSize();
    ImageView* imageView = ImageView::create();
    imageView->loadTexture("herolistbg.png");
    imageView->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addChild(imageView);
    
    ImageView* heroImage = ImageView::create();
    heroImage->loadTexture(hero.textureName.c_str());
    heroImage->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addChild(heroImage);
    
    ImageView* coinImage = ImageView::create();
    coinImage->loadTexture("coins.png");
    coinImage->setPosition(ccp(coinImage->getContentSize().width/2+30,winSize.height/2));
    coinImage->setTag(111);
    m_pUiLayer->addChild(coinImage);
    
    
    Label *label = Label::create();
    label->setString(to_string(hero.level));
    m_pUiLayer->addChild(label);
    
    Button *btn=Button::create();
    btn->setTouchEnabled(true);
    btn->loadTextures("qianghua1.png","qianghua2.png","");
    btn->setPosition(ccp(winSize.width/2,winSize.height/2-250));
//    btn->addReleaseEvent(this, coco_releaseselector(QiangHuaLayer::qianghua));
    m_pUiLayer->addChild(btn);
    
    Button *btnclose=Button::create();
    btnclose->setTouchEnabled(true);
    btnclose->loadTextures("close1.png","close2.png","close2.png");
    btnclose->setPosition(ccp(winSize.width-60, winSize.height/2+300));
//    btnclose->addReleaseEvent(this, coco_releaseselector(QiangHuaLayer::close));
    m_pUiLayer->addChild(btnclose);
    getHeros();
    return true;
}
void QiangHuaLayer::getHeroInfo(CCObject *sender)
{
    HeroInfoLayer *info=new HeroInfoLayer();
    addChild(info);
}
void QiangHuaLayer::qianghua(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    if(bUpgrade)
    {
      vector<HeroType> Heros=GameData::shareGameData()->getHeros();
      for(int i=0;i<Heros.size();i++)
       {
        HeroType hero=Heros[i];
        if(hero.type==m_hero.type&&hero.index!=m_hero.index&&m_hero.exlevel<=9)
         {
             
              printf("qingggg'");
            GameData::shareGameData()->QianghuaHero(hero,m_hero);
            GameData::shareGameData()->removeKapai(hero);
            
         }
          else if(m_hero.exlevel>=9)
          {
              CCSprite *bg=CCSprite::create("tipbg.png");
              bg->setPosition(ccp(winSize.width/2,winSize.height/2));
              addChild(bg,1);
              CCActionInterval *action0=CCFadeOut::create(2);
              bg->runAction(action0);
              char str[64];
              sprintf(str,"已经到最高品质");
              CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
              tiplabel->setColor(ccRED);
              tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
              addChild(tiplabel,100);
              CCActionInterval *action=CCFadeOut::create(2);
              tiplabel->runAction(action);
          }
        }
    }
    else
    {
        CCSprite *bg=CCSprite::create("tipbg.png");
        bg->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(bg,1);
        CCActionInterval *action0=CCFadeOut::create(2);
        bg->runAction(action0);
        char str[64];
        sprintf(str,"材料不够,需要一张同类型卡牌");
        CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
        tiplabel->setColor(ccRED);
        tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(tiplabel,100);
        CCActionInterval *action=CCFadeOut::create(2);
        tiplabel->runAction(action);
    }
}
void QiangHuaLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
void QiangHuaLayer::change(int index)
{
    printf("change%d",index);
}
void QiangHuaLayer::getHeros()
{
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int i=0; i<Heros.size(); ++i)
    {
        HeroType hero=Heros[i];
        ImageView* image=(ImageView*)m_pUiLayer->getChildByTag(111);
        if(m_hero.type==hero.type&&m_hero.index!=hero.index&&hero.pos<=0)
        {
            string strname = "head" + to_string(hero.type) + ".png";
            image->loadTexture(strname);
            //image->setScale(0.3);
            bUpgrade=true;
        }
    }
}
void QiangHuaLayer::updateHero()
{

}
