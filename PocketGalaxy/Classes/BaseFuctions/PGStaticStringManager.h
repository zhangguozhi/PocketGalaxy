//
//  PGStaticStringManager.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-26.
//
//

#ifndef __PocketGalaxy__PGStaticStringManager__
#define __PocketGalaxy__PGStaticStringManager__

#include <iostream>
#include "cocos2d.h"    
USING_NS_CC;
namespace PGDatas{
    class PGStaticStringManager : public CCObject{
    private:
        CCDictionary* strings;
        CCArray* stringFileNames;
    public:
        static PGStaticStringManager* sharedStaticStringManager();
        bool init();
        void loadStrings();
        CCString* getString(const char* fileName, const char* key);
        ~ PGStaticStringManager();
    };
}

#define PG_STATIC_STRING(fileName,key)\
PGDatas::PGStaticStringManager::sharedStaticStringManager()->getString(fileName, key);

#endif /* defined(__PocketGalaxy__PGStaticStringManager__) */
