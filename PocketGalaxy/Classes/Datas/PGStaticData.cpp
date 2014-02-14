//
//  PGStaticData.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#include "PGStaticData.h"
using namespace PGDatas;
bool PGStaticData::init(cocos2d::CCDictionary *dic){
    keyId_ = ((CCString*)dic->objectForKey("keyId"))->intValue();
    return true;
}