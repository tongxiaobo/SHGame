//
//  HeroInfoLayer.cpp
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#include "HeroInfoLayer.h"
#include "editor-support/cocostudio/CocoStudio.h"

using namespace cocostudio;

HeroInfoLayer::HeroInfoLayer()
{
	
}
HeroInfoLayer::~HeroInfoLayer()
{
	
}
bool HeroInfoLayer::init(HeroType hero)
{
    if(!CCLayer::init()){
        return false;
    }
    m_hero=hero;
    layer=NULL;
    CCSize size= CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg=CCSprite::create("herolistbg.png");
    bg->setPosition(ccp(size.width/2,size.height/2));
    addChild(bg);
    setTouchEnabled(true);
    m_pUiLayer=Layer::create();
    this->addChild(m_pUiLayer);
    
    Size winSize =Director::getInstance()->getWinSize();
    scrollView = ui::ScrollView::create();
    scrollView->setTouchEnabled(true);
//    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));
    scrollView->setPosition(ccp(0,winSize.height/2-360));
    scrollView->setInnerContainerSize(CCSizeMake(winSize.width,1920));
    m_pUiLayer->addChild(scrollView);

    string filePath = FileUtils::getInstance()->fullPathForFilename("HeroInfoLayer_1.json");
    Widget*example_root = GUIReader::getInstance()->widgetFromJsonFile(filePath.c_str());
    scrollView->addChild(example_root);
//    for(int i=21;i<24;i++)
//    {
//        UIButton* btn=(UIButton*)example_root->getChildByTag(i);
//        btn->setTouchEnabled(true);
//        btn->addReleaseEvent(this, coco_releaseselector(HeroInfoLayer::menuPauseCallback));
//    }
    ImageView *image=(ImageView*)example_root->getChildByTag(3);
    image->loadTexture(hero.textureName.c_str());

    string strLevel = hero.name + "_" + to_string(hero.exlevel);
    Label *nameLabel=Label::createWithSystemFont(strLevel, "Arial", 48);
    nameLabel->setPosition(ccp(winSize.width-200,1920-50));
    scrollView->addChild(nameLabel);
    
    int star=5;
    if(hero.type>=36&&hero.type!=108)
        star=4;
    for(int i=0;i<star;i++)
    {
        ImageView *image=ImageView::create();
        image->loadTexture("star.png");
        image->setPosition(ccp(winSize.width-25*i-60,1920-100));
        scrollView->addChild(image);
//        UILabel *label=UILabel::create();
//        label->setText("★");
//        label->setColor(ccYELLOW);
//        label->setFontSize(16);
//        label->setPosition(ccp(winSize.width-20*i-100,1920-100));
//        scrollView->addChild(label);
    }
    
    Label *exLevelLabel=(Label*)example_root->getChildByTag(32);
    exLevelLabel->setColor(ccYELLOW);
    exLevelLabel->setSystemFontSize(32);
    exLevelLabel->setString(to_string(hero.exlevel));

    Label *LevelLabel=(Label*)example_root->getChildByTag(33);
    LevelLabel->setSystemFontSize(32);
    LevelLabel->setString(to_string(hero.level));

    Label *hpLevelLabel=(Label*)example_root->getChildByTag(34);
    hpLevelLabel->setSystemFontSize(32);
    hpLevelLabel->setString(to_string(hero.totalhp));

    Label *apLevelLabel=(Label*)example_root->getChildByTag(35);
    hpLevelLabel->setSystemFontSize(32);
    hpLevelLabel->setString(to_string(hero.totalap));

    Label *defendLabel=(Label*)example_root->getChildByTag(36);
    defendLabel->setSystemFontSize(32);
    defendLabel->setString(to_string(hero.totaldefend));

    Label *magicLabel=(Label*)example_root->getChildByTag(37);
    magicLabel->setSystemFontSize(32);
    magicLabel->setString(to_string(hero.totalmagicdefend));
    
    ImageView *skillsimage=(ImageView*)example_root->getChildByTag(51);
    Label *skillsLabel=Label::create();
    skillsLabel->setSystemFontSize(48);
    skillsLabel->setString("技能");
    skillsLabel->setPosition(ccp(skillsimage->getPosition().x+10,skillsimage->getPosition().y-10));
    scrollView->addChild(skillsLabel);
    
    ImageView *qianghuaimage=(ImageView*)example_root->getChildByTag(52);
    Label *qianghuaLabel=Label::create();
    qianghuaLabel->setSystemFontSize(48);
    qianghuaLabel->setString("强化");
    qianghuaLabel->setPosition(ccp(qianghuaimage->getPosition().x+10,qianghuaimage->getPosition().y-10));
    scrollView->addChild(qianghuaLabel);
    
    ImageView *jianjieimage=(ImageView*)example_root->getChildByTag(53);
    Label *jianjieLabel=Label::create();
    jianjieLabel->setSystemFontSize(48);
    jianjieLabel->setString("简介");
    jianjieLabel->setPosition(ccp(jianjieimage->getPosition().x+10,jianjieimage->getPosition().y-10));
    scrollView->addChild(jianjieLabel);
    
    char str[2048];
    int skills=hero.skillsid;
    if(skills<100)
    sprintf(str,"普通攻击:对单体造成80％-120％伤害\n必杀技:%s 对单体造成320％-380％攻击伤害",hero.skillsname.c_str());
    else if(skills>=100&&skills<=200)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对全体造成60％-100％攻击伤害",hero.skillsname.c_str());
    else if(skills>=200&&skills<300)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对前排造成120％-160％攻击伤害",hero.skillsname.c_str());
    else if(skills>=300&&skills<400)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对后排造成120％-160％攻击伤害",hero.skillsname.c_str());
    else if(skills>=400&&skills<500)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对竖排造成200％-240％攻击伤害",hero.skillsname.c_str());


    Text *label=(Text*)example_root->getChildByTag(41);
    label->setTextAreaSize(CCSize(540,300));
    label->setColor(ccYELLOW);
    label->setText(str);
    label->setFontSize(32);
    label->setPosition(ccp(winSize.width/2,label->getPosition().y-20));
    
    Text *label2=(Text*)example_root->getChildByTag(42);
    int number=(108-hero.type)/10+20;
    int number1=hero.type/10+20;
    sprintf(str,"绰号:%s 生命加成%d％  英雄+2激活\n星座:%s 攻击加成%d％  英雄+5激活",hero.exname.c_str(),number,hero.starname.c_str(),number1);
    label2->setText(str);
    label2->setColor(ccYELLOW);
    label2->setTextAreaSize(CCSize(540,400));
    label2->setFontSize(32);
    label2->setPosition(ccp(winSize.width/2,700));
    
    Text *label3=(Text*)example_root->getChildByTag(43);
    label3->setFontSize(32);
    label3->setTextAreaSize(CCSize(540,800));
    label3->setText(hero.des.c_str());
    label3->setColor(ccYELLOW);
    label3->setPosition(ccp(winSize.width/2,200));
    
//    UIButton * btn= UIButton::create();
//    btn->setTouchEnable(true);
//    btn->addReleaseEvent(this, coco_releaseselector(HeroInfoLayer::close));
//    btn->setTextures("close1.png","close2.png","close2.png");
//    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
//    m_pUiLayer->addWidget(btn);
    
    CCMenuItemImage* pHome = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(HeroInfoLayer::close));
    CCMenu *menu=CCMenu::create(pHome,NULL);
    menu->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menu,2);

    return true;
}
void HeroInfoLayer::menuPauseCallback(CCObject *sender)
{

}
void HeroInfoLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
void HeroInfoLayer::setData(HeroType hero)
{
    string name=hero.name;
    
}
void HeroInfoLayer::updateText(int tag)
{
    
}
