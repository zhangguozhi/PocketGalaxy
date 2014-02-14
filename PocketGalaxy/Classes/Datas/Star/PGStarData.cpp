//
//  StarData.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#include "PGStarData.h"
using namespace PGDatas;

bool PGStarData::init(cocos2d::CCDictionary *dic){
    if (PGStaticData::init(dic)) {
        type_ = ((CCString*)dic->objectForKey("type"))->intValue();
        maxChildrenCount_ = ((CCString*)dic->objectForKey("maxChildrenCount"))->intValue();
        rotationPeriod_ = ((CCString*)dic->objectForKey("rotationPeriod"))->intValue();
        childStarOrbitalRadius_ = (CCArray*)dic->objectForKey("childStarOrbitalRadius");
        CC_SAFE_RETAIN(childStarOrbitalRadius_);
        childStarOrbitalPeriods_ = (CCArray*)dic->objectForKey("childStarOrbitalPeriods");
        CC_SAFE_RETAIN(childStarOrbitalPeriods_);
    }
    return true;
}

PGStarData::~PGStarData(){
    CC_SAFE_RELEASE_NULL(childStarOrbitalRadius_);
    CC_SAFE_RELEASE_NULL(childStarOrbitalPeriods_);
}