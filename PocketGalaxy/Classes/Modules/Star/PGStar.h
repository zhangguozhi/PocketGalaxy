//
//  PGStar.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-24.
//
//

#ifndef __PocketGalaxy__PGStar__
#define __PocketGalaxy__PGStar__

#include <iostream>
#include "cocos2d.h"
#include "PGStarData.h"
USING_NS_CC;
namespace PGModules{
    class PGStar: public CCObject ,public PGDatas::PGStaticDataObject{
        CC_SYNTHESIZE(int , starId_, StarId)
        CC_SYNTHESIZE_READONLY(CCDictionary*, childrenStars_, ChildrenStars)
        CC_SYNTHESIZE_RETAIN(PGStar*, parentStar_, ParentStar)
        CC_SYNTHESIZE_READONLY(PGDatas::PGStarData*, starData_, StarData)
    public:
        PG_CREATE_DATA_OBJ_FUNC(PGStar);
        bool init(int keyId);
        void addChildStar(PGStar* star);
        ~ PGStar();
    };
}
#endif /* defined(__PocketGalaxy__PGStar__) */
