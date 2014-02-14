//
//  PGStaticData.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#ifndef __PocketGalaxy__PGStaticData__
#define __PocketGalaxy__PGStaticData__

#include <iostream>
#include "cocos2d.h"

#define PG_CREATE_DATA_FUNC(__TYPE__)\
static __TYPE__* createData(CCDictionary* dic) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(dic)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

USING_NS_CC;
namespace PGDatas{
    class PGStaticDataObject{
    public:
        virtual bool init(int keyId) = 0;
#define PG_CREATE_DATA_OBJ_FUNC(__TYPE__)\
static __TYPE__* create##__TYPE__(int keyId) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(keyId)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}
    };
    class PGStaticData: public CCObject{
        CC_SYNTHESIZE_READONLY(int, keyId_, KeyID)
    public:
        PG_CREATE_DATA_FUNC(PGStaticData)
        virtual bool init(CCDictionary* dic);
    };
}
#endif /* defined(__PocketGalaxy__PGStaticData__) */
