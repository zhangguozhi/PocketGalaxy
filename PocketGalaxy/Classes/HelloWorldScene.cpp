#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PGStarNode.h"
#include "PGStaticDataManager.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    PGDatas::PGStaticDataManager::sharedStaticDataManager()->loadDatas();
    
    
    PGModules::PGStar *sun = PGModules::PGStar::createPGStar(1001);
    CC_SAFE_RETAIN(sun);
    
    PGModules::PGStar* star1 = PGModules::PGStar::createPGStar(2001);
    star1->setStarId(1);
    sun->addChildStar(star1);
    
    PGModules::PGStar* star2 = PGModules::PGStar::createPGStar(2002);
    star2->setStarId(2);
    sun->addChildStar(star2);
    
    
    PGModules::PGStar* star11 = PGModules::PGStar::createPGStar(3001);
    star11->setStarId(1);
    star1->addChildStar(star11);
    

    PGInterface::PGStarNode* sunNode = PGInterface::PGStarNode::create(sun);
    addChild(sunNode);
    sunNode->setPosition(size.width / 2, size.height / 2);
    sunNode->setRotation(-15);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
