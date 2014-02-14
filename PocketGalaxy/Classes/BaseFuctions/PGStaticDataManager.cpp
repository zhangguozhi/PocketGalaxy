//
//  PGStaticDataManager.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#include "PGStaticDataManager.h"
#include "PGStaticData.h"
using namespace PGDatas;
static PGStaticDataManager* sharedStaticDataManager_ = NULL;
PGStaticDataManager* PGStaticDataManager::sharedStaticDataManager(){
    if (!sharedStaticDataManager_) {
        sharedStaticDataManager_ = new PGStaticDataManager();
        sharedStaticDataManager_->init();
    }
    return sharedStaticDataManager_;
}
void PGStaticDataManager::cleanStaticDataManager(){
    CC_SAFE_RELEASE_NULL(sharedStaticDataManager_);
}
bool PGStaticDataManager::init(){
    return true;
}
PGStaticDataManager::~PGStaticDataManager(){
    CC_SAFE_RELEASE_NULL(StarDatas_);
    CC_SAFE_RELEASE_NULL(dataFileNames_);
}
#define PG_LOAD_DATA(_T_)\
_T_##Datas_ = CCDictionary::create();\
CC_SAFE_RETAIN(_T_##Datas_);\
CCDictElement* elt = NULL;\
CCDICT_FOREACH(fileDic, elt){\
    CCDictionary* dic = (CCDictionary*)elt->getObject();\
    PG##_T_##Data* data = PG##_T_##Data::createData(dic);\
    _T_##Datas_->setObject(data, data->getKeyID());\
}
void PGStaticDataManager::createStaticData(const char *key){
    CCString* fileName = CCString::createWithFormat("%s.plist",key);
    CCDictionary* fileDic = CCDictionary::createWithContentsOfFile(fileName->getCString());
    if (strcmp(key, "Star_data") == 0) {
        PG_LOAD_DATA(Star);
    }
}
void PGStaticDataManager::loadDatas(){
    dataFileNames_ = CCArray::createWithContentsOfFile("StaticDataNames.plist");
    CC_SAFE_RETAIN(dataFileNames_);
    CCObject* elt = NULL;
    CCARRAY_FOREACH(dataFileNames_, elt){
        CCString* dataName = (CCString*)elt;
        createStaticData(dataName->getCString());
    }
}

PGStarData* PGStaticDataManager::getStarData(int keyId){
    return (PGStarData*)StarDatas_->objectForKey(keyId);
}