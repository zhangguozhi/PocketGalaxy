//
//  StarData.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#ifndef __PocketGalaxy__PGStarData__
#define __PocketGalaxy__PGStarData__

#include <iostream>
#include "PGStaticData.h"
USING_NS_CC;
namespace PGDatas{
    class PGStarData: public PGStaticData{
        CC_SYNTHESIZE_READONLY(int , type_, Type)
        CC_SYNTHESIZE_READONLY(int , maxChildrenCount_, MaxChildrenCount)
        CC_SYNTHESIZE_READONLY(CCArray*, childStarOrbitalRadius_, ChildStarOrbitalRadius)
        CC_SYNTHESIZE_READONLY(CCArray*, childStarOrbitalPeriods_, ChildStarOrbitalPeriods)
        CC_SYNTHESIZE_READONLY(int , rotationPeriod_, RotationPeriod)
    public:
        PG_CREATE_DATA_FUNC(PGStarData)
        bool init(CCDictionary* dic);
        ~ PGStarData();
    };
}
#endif /* defined(__PocketGalaxy__PGStarData__) */
