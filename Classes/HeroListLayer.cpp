//
//  HeroListLayer.cpp
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#include "HeroListLayer.h"
#include "GameData.h"
#include "ShengJiLayer.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace ui;

HeroListLayer::HeroListLayer()
{
	
}
HeroListLayer::~HeroListLayer()
{
	
}
bool HeroListLayer::init(HeroType hero,int type)
{
    if(!CCLayer::init()){
        return false;
    }
    m_oldHero=hero;
    mindex=type;
    getHeros();
    return true;
}
void HeroListLayer::getHeros()
{
    Layer *m_pUiLayer=Layer::create();
    addChild(m_pUiLayer,1);
    Size winSize =Director::getInstance()->getWinSize();
    ImageView* imagehead= ImageView::create();
    imagehead->loadTexture("herolistbg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addChild(imagehead);
    
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setTouchEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));
    //CCSize backgroundSize =CCSize(500,200);
    scrollView->setPosition(ccp(0,winSize.height/2-380));
    m_pUiLayer->addChild(scrollView);
    
    int j=-1;
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for(int i=0;i<Heros.size();i++)
    {
        HeroType hero=Heros[i];
        if(hero.pos<=0||mindex==-1)
        {
            j++;
            ImageView* imageView = ImageView::create();
            imageView->loadTexture("cellbg.png");
            float innerWidth = scrollView->getContentSize().width;
            float innerHeight = scrollView->getContentSize().height + imageView->getContentSize().height*Heros.size();
            
            scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
            
            int imageHeight=imageView->getContentSize().height;
            imageView->setPosition(ccp(innerWidth /2,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imageView);
            
            ImageView* imagebg= ImageView::create();
            imagebg->loadTexture("headbk4.png");
            imagebg->setPosition(ccp(165,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imagebg);
            
            ImageView* imagehead= ImageView::create();
            char strImage[32];
            sprintf(strImage,"head%d.png",hero.type);
            imagehead->loadTexture(strImage);
            //imagehead->setScale(0.2);
            imagehead->setPosition(ccp(165,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imagehead);

            Label *namelabel=Label::createWithSystemFont(hero.name, "Arial", 32);
            namelabel->setColor(ccBLACK);
            namelabel->setPosition(ccp(winSize.width/2-50,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/3));
            scrollView->addChild(namelabel);

            string levelStr = "Lv:" + to_string(hero.level);
            Label *label=Label::createWithSystemFont(levelStr, "Arial", 32);
            label->setColor(ccBLACK);
            label->setPosition(ccp(winSize.width/2+50,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/3));
            scrollView->addChild(label);
            
            ImageView* imagehp= ImageView::create();
            imagehp->loadTexture("heart.png");
            imagehp->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(imagehp);
            
            char str[32];
            sprintf(str,"%d",hero.hp);
            Label *hplabel=Label::createWithSystemFont(to_string(hero.hp), "Arial", 24);
            hplabel->setString(str);
            hplabel->setColor(ccRED);
            hplabel->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(hplabel);
            
            ImageView* imageap= ImageView::create();
            imageap->loadTexture("swordicon.png");
            imageap->setPosition(ccp(winSize.width/2+30,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(imageap);
            
//            sprintf(str,"%d",hero.ap);
            Label *aplabel=Label::createWithSystemFont(to_string(hero.ap), "Arial", 24);
//            aplabel->setFontSize(24);
//            aplabel->setText(str);
            aplabel->setColor(ccRED);
            aplabel->setPosition(ccp(winSize.width/2+90,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(aplabel);
            
            Button* button = Button::create();
            button->setTouchEnabled(true);
            if(mindex==-1)//升级
            {
                button->loadTextures("heroup1.png", "heroup2.png", "");
//                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuPauseCallback));
            }
            else if(mindex>0)//换将
            {
                button->loadTextures("changhero1.png", "changhero2.png", "");
//                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuCallback));
            }
            else if(mindex==-2)//英雄上阵
            {
                button->loadTextures("changhero1.png", "changhero2.png", "");
//                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuAddhero));
            }
            button->setPosition(ccp(winSize.width-165, scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            button->setTag(hero.index);
            scrollView->addChild(button);
        }
        
    }
    Button * btn= Button::create();
    btn->setTouchEnabled(true);
    btn->addTouchEventListener(CC_CALLBACK_0(HeroListLayer::close, this));
//    btn->addReleaseEvent(this, coco_releaseselector(HeroListLayer::close));
    btn->loadTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width/2+150, winSize.height/2+250));
    m_pUiLayer->addChild(btn);
}
void HeroListLayer::close()
{
    removeFromParentAndCleanup(true);
}
void HeroListLayer::menuAddhero(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    Button* button=(Button*)sender;
    int tag=button->getTag();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    
    HeroType hero;
    for(int j=0;j<Heros.size();j++)
    {
        if(tag==Heros[j].index)
        {
            hero=Heros[j];
        }
    }
    for(int j=0;j<Heros.size();j++)
    {
        if(Heros[j].pos>0&&hero.type==Heros[j].type)
        {

            CCSprite *bg=CCSprite::create("tipbg.png");
            bg->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(bg,1);
            CCActionInterval *action0=CCFadeOut::create(2);
            bg->runAction(action0);
            char str[32];
            sprintf(str,"相同英雄不可同时上阵");
            CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
            tiplabel->setColor(ccRED);
            tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(tiplabel,100);
            CCActionInterval *action=CCFadeOut::create(2);
            tiplabel->runAction(action);
            return;
        }
    }
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_ADD_HERO, (CCObject*)(intptr_t)hero.index);
    this->removeFromParentAndCleanup(true);
}
void HeroListLayer::menuCallback(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    Button* button=(Button*)sender;
    int tag=button->getTag();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();

    HeroType hero;
    for(int j=0;j<Heros.size();j++)
    {
        if(tag==Heros[j].index)
        {
            hero=Heros[j];
        }
    }
    for(int j=0;j<Heros.size();j++)
    {
        if(Heros[j].pos>0&&hero.type==Heros[j].type)
        {
            
            CCSprite *bg=CCSprite::create("tipbg.png");
            bg->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(bg,1);
            CCActionInterval *action0=CCFadeOut::create(2);
            bg->runAction(action0);
            char str[32];
            sprintf(str,"相同英雄不可同时上阵");
            CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
            tiplabel->setColor(ccRED);
            tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(tiplabel,100);
            CCActionInterval *action=CCFadeOut::create(2);
            tiplabel->runAction(action);
            return;
        }
    }
    GameData::shareGameData()->changeHero(m_oldHero,hero);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_CHANGE_HERO, (CCObject*)(intptr_t)hero.index);
    this->removeFromParentAndCleanup(true);
}
void HeroListLayer::menuPauseCallback(CCObject *sender)
{
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroListLayer::Heroupdate),MSG_HERO_UPDATE, NULL);
//    UIButton* button=(UIButton*)sender;
//    int tag=button->getTag();
//
//    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
//    for(int i=0;i<Heros.size();i++)
//    {
//        HeroType hero=Heros[i];
//        if(tag==hero.index)
//        {
//            ShengJiLayer *layer=new ShengJiLayer();
//            layer->init(hero);
//            layer->autorelease();
//            addChild(layer,10);
//        }
//    }
}
void HeroListLayer::Heroupdate()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_HERO_UPDATE);
    removeAllChildrenWithCleanup(true);
    getHeros();
    
}
