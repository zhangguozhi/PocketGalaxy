//
//  PGStaticDataManager.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-25.
//
//

#ifndef __PocketGalaxy__PGStaticDataManager__
#define __PocketGalaxy__PGStaticDataManager__

#include <iostream>
#include "cocos2d.h"
#include "PGStaticDatas.h"
USING_NS_CC;
namespace PGDatas{
    class PGStaticData;
    class PGStaticDataManager:public CCObject{
        
    private:
        CCArray* dataFileNames_;
        CCDictionary* StarDatas_;
        void createStaticData(const char* key);
    public:
        static PGStaticDataManager* sharedStaticDataManager();
        static void cleanStaticDataManager();
        bool init();
        void loadDatas();
        
        ~ PGStaticDataManager();
        PGStarData* getStarData(int keyId);
    };
}

#define PG_STATIC_DATA(__T__, keyId)\
PGDatas::PGStaticDataManager::sharedStaticDataManager()->get##__T__##Data(keyId);

#endif /* defined(__PocketGalaxy__PGStaticDataManager__) */
