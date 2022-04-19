//
//  ZhuangBeiLayer.cpp
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#include "ZhuangBeiLayer.h"
#include "GameData.h"
#include "HeroLayer.h"
#include "ZhuangBeiShengji.h"
ZhuangBeiListLayer::ZhuangBeiListLayer()
{
	
}
ZhuangBeiListLayer::~ZhuangBeiListLayer()
{
	
}
bool ZhuangBeiListLayer::init(HeroType hero,int type,ZhuangBeiType zhuang)
{
    if(!CCLayer::init()){
        return false;
    }
    m_hero=hero;
    m_type=type;
    m_zhuangtype=zhuang;
    setData(hero,type,zhuang);
    return true;
}
void ZhuangBeiListLayer::setData(HeroType hero,int type,ZhuangBeiType zhuangtype)
{
    Layer*m_pUiLayer=Layer::create();
    addChild(m_pUiLayer,0);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    ImageView * imagebg=ImageView::create();
    setTouchEnabled(true);
    imagebg->loadTexture("herobg.png");
    imagebg->setPosition(ccp(winSize.width/2, winSize.height/2));
    m_pUiLayer->addChild(imagebg);
    

    
    ui::ScrollView*scrollView = ui::ScrollView::create();
    scrollView->setTouchEnabled(true);
//    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));

    scrollView->setPosition(ccp(0,winSize.height/2-360));
    m_pUiLayer->addChild(scrollView);
    

    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    int j=0;
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
         int t=(type+3)*100;
        printf("zhuangtype==%d,%d,%d",zhuang.type,t,m_type);
       
        if((zhuang.type>=t&&zhuang.type<(t+100))||type==-1)
        {
            j++;
            ImageView* imageView = ImageView::create();
            imageView->loadTexture("cellbg.png");
            int imageHeight=imageView->getContentSize().height;
            float innerWidth = scrollView->getContentSize().width;
            float innerHeight = scrollView->getContentSize().height +imageHeight*zhuangBeis.size();
            scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
            
            
            imageView->setPosition(ccp(innerWidth / 2,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imageView);
            
            ImageView* imagebg= ImageView::create();
            imagebg->loadTexture("addbutton.png");
            imagebg->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imagebg);
            
            ImageView* imageHead = ImageView::create();
            imageHead->loadTexture(zhuang.textureName.c_str());
            imageHead->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imageHead);
            
            Label *label=Label::create();
            char strlevel[32];
            sprintf(strlevel,"Lv:%d",zhuang.level);
            label->setSystemFontSize(24);
            label->setString(strlevel);
            label->setColor(ccBLUE);
            label->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
            scrollView->addChild(label);
            
            Label *namelabel=Label::create();
            namelabel->setSystemFontSize(24);
            namelabel->setString(zhuang.name.c_str());
            namelabel->setColor(ccBLUE);
            namelabel->setPosition(ccp(winSize.width/2,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
            scrollView->addChild(namelabel);
            
            if(zhuang.hp>0)
            {
                ImageView* imageattack = ImageView::create();
                imageattack->loadTexture("heart.png");
                imageattack->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                Label *label=Label::create();
                label->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int hp=zhuang.hp+(40+10*zhuang.star)*zhuang.level;
                sprintf(str,"%d",hp);
                label->setSystemFontSize(24);
                label->setColor(ccBLACK);
                label->setString(str);
            }
            if(zhuang.ap>0)
            {
            ImageView* imageattack = ImageView::create();
            imageattack->loadTexture("swordicon.png");
            imageattack->setPosition(ccp(winSize.width/2+40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(imageattack);
            Label *label=Label::create();
            label->setPosition(ccp(winSize.width/2+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(label);
            char str[32];
            int ap=zhuang.ap+(10+2*zhuang.star)*zhuang.level;
            sprintf(str,"%d",ap);
            label->setColor(ccBLACK);
            label->setSystemFontSize(24);
            label->setString(str);
                
            }

            if(zhuang.defender>0)
            {
                ImageView* imageattack = ImageView::create();
                imageattack->loadTexture("fang.png");
                imageattack->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                Label *label=Label::create();
                label->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int defender=zhuang.defender+(6+1*zhuang.star)*zhuang.level;
                sprintf(str,"%d",defender);
                label->setColor(ccBLACK);
                label->setSystemFontSize(24);
                label->setString(str);
            }
            if(zhuang.magicdefender>0)
            {
                ImageView* imageattack = ImageView::create();
                imageattack->loadTexture("mofang.png");
                imageattack->setPosition(ccp(winSize.width/2+40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                Label *label=Label::create();
                label->setPosition(ccp(winSize.width/2+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int magicdefender=zhuang.magicdefender+(6+1*zhuang.star)*zhuang.level;
                sprintf(str,"%d",magicdefender);
                label->setSystemFontSize(24);
                label->setColor(ccBLACK);
                label->setString(str);
            }
            for(int i=0;i<zhuang.star;i++)
            {
                ImageView* imageattack = ImageView::create();
                imageattack->loadTexture("star.png");
                imageattack->setPosition(ccp(winSize.width/2+i*20+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
                scrollView->addChild(imageattack);
            }

            Button* button = Button::create();
            button->setTouchEnabled(true);
            button->setTag(zhuang.index);
            //string texturename=zhuang.textureName;
            if(type==-1)
            {
            button->loadTextures("heroup1.png", "heroup2.png", "");
//            button->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::Shengji));
            button->addTouchEventListener(CC_CALLBACK_1(ZhuangBeiListLayer::Shengji, this));
            }
            else
            {
                button->loadTextures("zhuangbei1.png", "zhuangbei2.png", "");
//                button->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::menuPauseCallback));
                button->addTouchEventListener(CC_CALLBACK_1(ZhuangBeiListLayer::menuPauseCallback, this));
            }
            
            button->setPosition(ccp(winSize.width-120, scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(button);
        }
    }
    Button * btn= Button::create();
    btn->setTouchEnabled(true);
//    btn->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::close));
    btn->addTouchEventListener(CC_CALLBACK_1(ZhuangBeiListLayer::close, this));
    btn->loadTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width/2+150, winSize.height/2+250));
    m_pUiLayer->addChild(btn);
}
int ZhuangBeiListLayer::getexp(int ap,float x, int n)
{
    if(n == 0)
    {
        return ap;
    }
    
    return x * getexp(ap,x, n-1);
}
void ZhuangBeiListLayer::Zhuangupdate()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_ZHUANG_UPDATE);
    removeAllChildrenWithCleanup(true);
    setData(m_hero,m_type,m_zhuangtype);
}
void ZhuangBeiListLayer::menuPauseCallback(CCObject *sender)
{
    Button* button=(Button*)sender;
    int index=button->getTag();
    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
        if(index==zhuang.index)
        {
            GameData::shareGameData()->changeZhuangBei(m_hero,zhuang,m_type);
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_CHANGE_STATE, (CCObject*)(intptr_t)index);
            this->removeFromParentAndCleanup(true);
        }
    }
}
void ZhuangBeiListLayer::Shengji(CCObject *sender)
{
//    NotificationCenter::getInstance()->addObserver(this, CC_CALLBACK_0(ZhuangBeiListLayer::Zhuangupdate, this), MSG_ZHUANG_UPDATE, NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ZhuangBeiListLayer::Zhuangupdate),MSG_ZHUANG_UPDATE, NULL);
    Button* button=(Button*)sender;
    int index=button->getTag();
    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
        if(index==zhuang.index)
        {
            ZhuangBeiShengjiLayer *layer=new ZhuangBeiShengjiLayer();
            layer->init(zhuang);
            addChild(layer,10);
        }
    }

    
}
void ZhuangBeiListLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
