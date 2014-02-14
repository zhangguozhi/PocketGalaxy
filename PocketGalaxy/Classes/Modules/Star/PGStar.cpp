//
//  PGStar.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-24.
//
//

#include "PGStar.h"
#include "PGStaticDataManager.h"
using namespace PGModules;
PGStar::~PGStar(){
    CC_SAFE_RELEASE_NULL(childrenStars_);
    CC_SAFE_RELEASE_NULL(parentStar_);
    CC_SAFE_RELEASE_NULL(starData_);
}

bool PGStar::init(int keyId){
    starData_ = PG_STATIC_DATA(Star, keyId);
    CC_SAFE_RETAIN(starData_);
    childrenStars_ = CCDictionary::create();
    CC_SAFE_RETAIN(childrenStars_);
    return true;
}

void PGStar:: addChildStar(PGStar *star) {
    if (childrenStars_->count() >= starData_->getMaxChildrenCount()) {
        return;
    }
    childrenStars_->setObject(star, star->getStarId());
    star->setParentStar(this);
}


