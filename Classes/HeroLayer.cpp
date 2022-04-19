//
//  HeroLayer.cpp
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#include "HeroLayer.h"
#include "ZhuangBeiLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
#include "ShengJiLayer.h"
#include "HeroListLayer.h"
#include "QiangHuaLayer.h"
#include "editor-support/cocostudio/CocoStudio.h"

using namespace cocostudio;

HeroLayer::HeroLayer()
{
	init();
}
HeroLayer::~HeroLayer()
{
	
}
bool HeroLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    Layer * ul=Layer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(ul);
    

    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    ImageView * imagebg=ImageView::create();
    setTouchEnabled(true);
//    imagebg->addReleaseEvent(this, coco_releaseselector(HeroLayer::getHeroInfo));

    imagebg->loadTexture("herobg1.png");
    imagebg->setScaleX(winSize.width/640);
    imagebg->setScaleY(winSize.height/960);
    imagebg->setPosition(ccp(winSize.width/2, winSize.height/2));
    ul->addChild(imagebg);
    
    pageView = PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(CCSize(winSize.width,winSize.height));
    ul->addChild(pageView);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::changeHero),MSG_CHANGE_HERO, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::changeState),MSG_CHANGE_STATE, NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::updateHero),MSG_HERO_UPDATE, NULL);

    LanguageType language=Application::getInstance()->getCurrentLanguage();
    Button* textButton = Button::create();
    textButton->setTouchEnabled(true);
    textButton->loadTextures("changhero1.png", "changhero2.png", "");
    textButton->setTitleFontSize(24);
//    textButton->setFontSize(24);
    textButton->setPosition(ccp(winSize.width/2-150,200));
//    textButton->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton->setTag(11);
    ul->addChild(textButton);
    
    Button* textButton1 = Button::create();
    textButton1->setTouchEnabled(true);
    textButton1->loadTextures("heroup1.png", "heroup2.png", "");
    textButton1->setTitleFontSize(24);
    textButton1->setPosition(ccp(winSize.width/2,200));
//    textButton1->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton1->setTag(12);
    ul->addChild(textButton1);
    
    Button* textButton2 = Button::create();
    textButton2->setTouchEnabled(true);
    textButton2->loadTextures("qianghua1.png", "qianghua2.png", "");
    textButton2->setTitleFontSize(24);
    textButton2->setPosition(ccp(winSize.width/2+150,200));
//    textButton2->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton2->setTag(13);
    ul->addChild(textButton2);

    getHeros();
    return true;
}
void HeroLayer::getHeroInfo(CCObject *sender)
{
    HeroInfoLayer *info=new HeroInfoLayer();
    int page=pageView->getCurrentPageIndex();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    info->init(hero);
    addChild(info);
}
void HeroLayer::menuCallback(CCObject *sender)
{
    Button * btn=(Button*)sender;
    int tag=btn->getTag();
    int page=pageView->getCurrentPageIndex();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    ZhuangBeiType zhuang=hero.zhuang[tag];
    ZhuangBeiListLayer *zhuangbei=new ZhuangBeiListLayer();
    zhuangbei->init(hero,tag,zhuang);
    addChild(zhuangbei,10);
}
void HeroLayer::changeState(CCObject *object)
{
    updateHero();
}
void HeroLayer::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_CHANGE_STATE);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_CHANGE_HERO);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_HERO_UPDATE);
}
void HeroLayer::getHeros()
{
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int index=0;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
        index++;
        string name =Heros[i].name;
        char strap[64];
        sprintf(strap,"%d",Heros[i].totalap);
        char strhp[64];
        sprintf(strhp,"%d",Heros[i].totalhp);

        Layout* layout = Layout::create();
        layout->setSize(CCSizeMake(winSize.width, winSize.height));
        layout->setTag(100+index);

        string filePath = FileUtils::getInstance()->fullPathForFilename("HeroLayer_1.json");
        Widget*example_root = GUIReader::getInstance()->widgetFromJsonFile(filePath.c_str());
//        Widget*example_root = CCSGUIReader::shareReader()->widgetFromJsonFile("HeroLayer_1.json");
        layout->addChild(example_root);
        pageView->addPage(layout);
        

        Label *nameLabel=dynamic_cast<Label *>(layout->getChildByTag(11));
        nameLabel->setSystemFontSize(48);
        string strName = name + " " + to_string(Heros[i].level) + "级";
        nameLabel->setString(strName);
            
        Label *hpLabel=dynamic_cast<Label *>(layout->getChildByTag(9));
        hpLabel->setString(to_string(Heros[i].totalhp));
        
        Label *apLabel=dynamic_cast<Label *>(layout->getChildByTag(10));
        apLabel->setString(to_string(Heros[i].totalap));
        

        
        string textureName=Heros[i].textureName;
        ImageView * image= dynamic_cast<ImageView *>(layout->getChildByTag(2));
//        image->addReleaseEvent(this, coco_releaseselector(HeroLayer::getHeroInfo));
        image->loadTexture(textureName.c_str());
        image->setScale(1.5);
        
        for(int j=0;j<6;j++)
        {

            string swordname=Heros[i].zhuang[j].textureName;
            Button * btn=dynamic_cast<Button *>(layout->getChildByTag(j+3));
            btn->setTag(j);
//            btn->addReleaseEvent(this, coco_releaseselector(HeroLayer::menuCallback));
            
            ImageView * image1=ImageView::create();
            image1->loadTexture(swordname.c_str());
            image1->setPosition(ccp(btn->getPosition().x+10,btn->getPosition().y));
            image1->setTag(20+j);
            layout->addChild(image1);
        }
      }
    }
}
void HeroLayer::changeHero(CCObject* object)
{
    updateHero();
}
void HeroLayer::Jinjie()
{
    
}
void HeroLayer::pageLeft()
{
    int index=pageView->getCurrentPageIndex();
    index--;
    if(index<=0)
        index=0;
    pageView->scrollToPage(index);
}
void HeroLayer::pageRight()
{
    int index=pageView->getCurrentPageIndex();
    index++;
    vector<HeroType>  heros=GameData::shareGameData()->getHeros();
    if(index>=heros.size())
        index=heros.size();
    pageView->scrollToPage(index);
}
void HeroLayer::Shengji(CCObject *sender)
{
    Button * btn=(Button*)sender;
    int tag=btn->getTag();
    int page=pageView->getCurrentPageIndex();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    if(tag==13)
    {
    QiangHuaLayer *layer=new QiangHuaLayer();
    layer->init(hero);
//    layer->autorelease();
    this->addChild(layer, 10);
    }
    if(tag==12)
    {
        ShengJiLayer *layer=new ShengJiLayer();
        layer->init(hero);
//        layer->autorelease();
        this->addChild(layer,10);
    }
    if(tag==11)
    {
        
        HeroListLayer *layer=new HeroListLayer();
        layer->init(hero,1);
        layer->autorelease();
        this->addChild(layer);
    }
}
void HeroLayer::updateHero()
{
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=0;
    for (int i=0; i<Heros.size(); ++i)
    {
        
        if(Heros[i].pos>0)
        {
        j++;
        Layout* layout=(Layout*)pageView->getChildByTag(100+j);
        string name =Heros[i].name;
  
        string textureName=Heros[i].textureName;
        ImageView * image= dynamic_cast<ImageView *>(layout->getChildByTag(2));
        image->loadTexture(textureName.c_str());
            
            Label *nameLabel=dynamic_cast<Label *>(layout->getChildByTag(11));
            nameLabel->setSystemFontSize(48);
            char strname[64];
            sprintf(strname,"%s %d级",name.c_str(),Heros[i].level);
            nameLabel->setString(strname);
            
            char strap[64];
            sprintf(strap,"%d",Heros[i].totalap);
            char strhp[64];
            sprintf(strhp,"%d",Heros[i].totalhp);

            Label *hpLabel=dynamic_cast<Label *>(layout->getChildByTag(9));
            hpLabel->setString(strhp);
            
            Label *apLabel=dynamic_cast<Label *>(layout->getChildByTag(10));
            apLabel->setString(strap);
        for(int a=0;a<6;a++)
        {
        string swordname=Heros[i].zhuang[a].textureName;
        ImageView * images= dynamic_cast<ImageView *>(layout->getChildByTag(a+20));
        images->loadTexture(swordname.c_str());
        }
        }
    }
}
