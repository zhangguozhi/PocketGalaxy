//
//  PGStarNode.h
//  PocketGalaxy
//
//  Created by ProZ on 13-8-24.
//
//

#ifndef __PocketGalaxy__PGStarNode__
#define __PocketGalaxy__PGStarNode__

#include <iostream>
#include "cocos2d.h"
#include "PGStar.h"
USING_NS_CC;

namespace PGInterface{
    class PGStarNode:public CCLayer ,public CCActionTweenDelegate{
        CC_SYNTHESIZE(int, indexInParent_, IndexInParent)
        CC_SYNTHESIZE(bool, isFollowed_, IsFollowed)
        CC_PROPERTY(float, orbitalAngle_, OrbitalAngle)
        CC_SYNTHESIZE(float, orbitalRadius_, OrbitalRadius)
        CC_SYNTHESIZE(float, sAngle_, SAngle);
    private:
        CCSprite* starSprite_;
        PGModules::PGStar* star_;
        int followingStarId_;
        void initStarSprite();
        void initChildStarSprite();
        void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
        void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
        void updateTweenAction(float value, const char* key);
        void stopFollow();
    public:
        static PGStarNode* create(PGModules::PGStar* star);
        bool init(PGModules::PGStar *star);
        PGStarNode* getChildStarNode(int starId);
        void followChildStar(int starId);
        ~ PGStarNode();
        PGStarNode();

        
        class PGStarOrbit : public CCNode{
        private:
            float radius_;
            float angle1_;
            float angle2_;
            float orbitAngle_;
            bool init(float radius,float angel1,float angle2,float orbitAngle);
            void draw();
        public:
            static PGStarOrbit* create(float radius,float angel1,float angle2,float orbitAngle);
            
        };
        
        class PGStarFollow :public CCFollow{
        private:
            float originScale;
            CCPoint originPosition;
            CCPoint originAnchorPoint;
            void startWithTarget(cocos2d::CCNode *pTarget);
            void step(float dt);
            ~ PGStarFollow();
        public:
            static PGStarFollow* create(CCNode* p_followedNode);
            bool initWithTarget(CCNode *pFollowedNode);
        };
    };
    
}
inline CCPoint posInOrbital(float angle, float radius,float sAngle){
    return CCPointMake(radius * cos(CC_DEGREES_TO_RADIANS(angle)), radius * sin(CC_DEGREES_TO_RADIANS(sAngle) * sin(CC_DEGREES_TO_RADIANS(angle))));
}
inline float scaleInOrbital(float angle, float radius){
    float a = 400;
    return (a + radius) / (radius * (sin(CC_DEGREES_TO_RADIANS(angle)) + 1) + a);
}
#endif /* defined(__PocketGalaxy__PGStarNode__) */
