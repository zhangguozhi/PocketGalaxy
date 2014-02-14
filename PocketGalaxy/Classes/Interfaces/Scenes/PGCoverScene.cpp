//
//  CoverScene.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-26.
//
//

#include "PGCoverScene.h"
#include "PGStaticStringManager.h"
using namespace PGInterface;
CCScene* PGCoverScene::scene(){
    PGCoverScene* layer = PGCoverScene::create();
    CCScene* scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}

bool PGCoverScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    CCString* gameName = PG_STATIC_STRING("UIStrings", "gameName");
    CCLabelTTF* titleLabel = CCLabelTTF::create(gameName->getCString(), "Courier", 60);
    addChild(titleLabel);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
            
    titleLabel->setPosition(CCPoint(size.width / 2, size.height / 2 + 100));
    return true;
}