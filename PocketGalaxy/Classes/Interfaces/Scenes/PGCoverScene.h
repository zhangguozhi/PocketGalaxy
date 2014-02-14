//
//  CoverScene.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-26.
//
//

#ifndef __PocketGalaxy__PGCoverScene__
#define __PocketGalaxy__PGCoverScene__


#include <iostream>


#include "cocos2d.h"
USING_NS_CC;
namespace PGInterface{
    class PGCoverScene : public CCLayer{
    public:
        static CCScene* scene();
        bool init();
        CREATE_FUNC(PGCoverScene);
    };
}
#endif /* defined(__PocketGalaxy__CoverScene__) */
