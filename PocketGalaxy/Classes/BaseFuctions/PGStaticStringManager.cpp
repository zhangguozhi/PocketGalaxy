//
//  PGStaticStringManager.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-26.
//
//

#include "PGStaticStringManager.h"
using namespace PGDatas;
static PGStaticStringManager* sharedStaticStringManager_ = NULL;
PGStaticStringManager* PGStaticStringManager::sharedStaticStringManager(){
    if (!sharedStaticStringManager_) {
        sharedStaticStringManager_ = new PGStaticStringManager();
        sharedStaticStringManager_->init();
    }
    return sharedStaticStringManager_;
}

bool PGStaticStringManager::init(){
    return true;
}
PGStaticStringManager::~PGStaticStringManager(){
    CC_SAFE_RELEASE_NULL(stringFileNames);
    CC_SAFE_RELEASE_NULL(strings);
}


void PGStaticStringManager::loadStrings(){
    stringFileNames = CCArray::createWithContentsOfFile("StringNames.plist");
    CC_SAFE_RETAIN(stringFileNames);
    
    strings = CCDictionary::create();
    CC_SAFE_RETAIN(strings);
    
    CCObject* obj = NULL;
    CCARRAY_FOREACH(stringFileNames, obj){
        CCString* fileName = CCString::createWithFormat("%s.plist",((CCString*)obj)->getCString());
        CCDictionary* fileStrings = CCDictionary::createWithContentsOfFile(fileName->getCString());
        strings->setObject(fileStrings, ((CCString*)obj)->getCString());
    }
}

CCString* PGStaticStringManager::getString(const char *fileName, const char *key){
    CCString* fullFileName = CCString::createWithFormat("%s_string",fileName);
    CCDictionary* fileStrings = (CCDictionary*)strings->objectForKey(fullFileName->getCString());
    return (CCString*)fileStrings->objectForKey(key);
}


