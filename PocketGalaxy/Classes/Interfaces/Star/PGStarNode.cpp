//
//  PGStarNode.cpp
//  PocketGalaxy
//
//  Created by ProZ on 13-8-24.
//
//

#include "PGStarNode.h"
using namespace PGInterface;
USING_NS_CC;
PGStarNode* PGStarNode::create(PGModules::PGStar *star){
    PGStarNode* starNode = new PGStarNode();
    if (star && starNode->init(star)) {
        starNode->autorelease();
        return starNode;
    }else{
        delete starNode;
        starNode = NULL;
        return NULL;
    }
}

bool PGStarNode::init(PGModules::PGStar *star){
    star_ = star;
    CC_SAFE_RETAIN(star_);
    sAngle_ = 10;
    followingStarId_ = 0;
    isFollowed_ = false;
    setAnchorPoint(CCPoint(0, 0));
    initStarSprite();
    initChildStarSprite();
    setContentSize(starSprite_->getContentSize());
    if (star_->getStarData()->getType() == 1) {
        setTouchEnabled(true);
    }
    return true;
}
PGStarNode::PGStarNode(){
    
}
PGStarNode::~PGStarNode(){
    CC_SAFE_RELEASE_NULL(star_);
}

void PGStarNode::initStarSprite(){
    CCString* textureName = CCString::createWithFormat("star%d.png",star_->getStarData()->getKeyID());
    starSprite_ = CCSprite::create(textureName->getCString());
    addChild(starSprite_);
    CCRotateBy *rotation = CCRotateBy::create(star_->getStarData()->getRotationPeriod(), 360);
    CCRepeatForever* repeat = CCRepeatForever::create(rotation);
    starSprite_->runAction(repeat);
}

void PGStarNode::initChildStarSprite(){
    CCDictionary* stars = star_->getChildrenStars();
    CCDictElement* elt = NULL ;
    CCArray* sortedStars = CCArray::createWithCapacity(stars->count());
    CCDICT_FOREACH(stars, elt){
        PGModules::PGStar* star = (PGModules::PGStar*)elt->getObject();
        int index = 0;
        CCObject* obj = NULL;
        int i = 0;
        CCARRAY_FOREACH(sortedStars, obj){
            PGModules::PGStar* sortedStar = (PGModules::PGStar*)obj;
            if (sortedStar->getStarId() < star->getStarId()) {
                index = i + 1;
            }
            i++;
        }
        sortedStars->insertObject(star, index);
    }
    
    
    CCObject* obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(sortedStars, obj){
        PGModules::PGStar* sortedStar = (PGModules::PGStar*)obj;
        PGStarNode* childStarNode = PGStarNode::create(sortedStar);
        addChild(childStarNode, 1 + i, sortedStar->getStarId());
        childStarNode->setIndexInParent(i);
        float duration = ((CCString*)star_->getStarData()->getChildStarOrbitalPeriods()->objectAtIndex(i))->floatValue();
        CCActionTween* tween = CCActionTween::create(duration, "orbitalAngle", 0, 360);
        CCRepeatForever* repeat = CCRepeatForever::create(tween);
        childStarNode->runAction(repeat);
        
        float orbitalRadius = ((CCString*)star_->getStarData()->getChildStarOrbitalRadius()->objectAtIndex(i))->floatValue();
        childStarNode->setOrbitalRadius(orbitalRadius);
        
        PGStarOrbit* childOrbit1 = PGStarOrbit::create(orbitalRadius, 0, 180, 0);
        PGStarOrbit* childOrbit2 = PGStarOrbit::create(orbitalRadius, 180, 360, 0);
        addChild(childOrbit1,-1 - i);
        addChild(childOrbit2,1 + i);
        
        i++;
    }
}

PGStarNode* PGStarNode::getChildStarNode(int starId){
    return (PGStarNode*)getChildByTag(starId);
}
void PGStarNode::stopFollow(){
    if (followingStarId_) {
        stopActionByTag(followingStarId_);
        PGStarNode* starNode = getChildStarNode(followingStarId_);
        starNode->setIsFollowed(false);
        followingStarId_ = 0;
    }
}
void PGStarNode::followChildStar(int starId){
    stopFollow();
    PGStarNode* starNode = getChildStarNode(starId);
    if (!starNode) {
        return;
    }
    starNode->setIsFollowed(true);
    followingStarId_ = starId;
    PGStarFollow* follow = PGStarFollow::create(starNode);
    follow->setTag(starId);
    runAction(follow);
}

void PGStarNode::updateTweenAction(float value, const char *key){
    setOrbitalAngle(value);
}
void PGStarNode::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    PGStarNode* node = NULL;
    if (followingStarId_) {
        node = getChildStarNode(followingStarId_);
    }else{
        node = this;
    }
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint pos1 = touch->getLocation();
    CCPoint pos2 = touch->getPreviousLocation();
    float oldSAngle = node->getSAngle();
    float newSAngle = oldSAngle + (pos1.y - pos2.y) / 10;
    newSAngle = MIN(newSAngle, 30);
    newSAngle = MAX(newSAngle, -30);
    node->setSAngle(newSAngle);
    float rotation = node->getRotation();
    float touchedRotation = rotation + (pos1.x - pos2.x)/10;
    touchedRotation = MIN(touchedRotation, 60);
    touchedRotation = MAX(touchedRotation, -60);
    node->setRotation(touchedRotation);
}
void PGStarNode::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCPoint touchLocation = ((CCTouch*)pTouches->anyObject())->getLocation();
    CCPoint touchLocationInNode = convertToNodeSpace(touchLocation);
    CCDictionary* childrenStars = star_->getChildrenStars();
    CCDictElement* elt = NULL;
    CCDICT_FOREACH(childrenStars, elt){
        PGModules::PGStar* childStar = (PGModules::PGStar*)elt->getObject();
        PGStarNode* childStarNode = getChildStarNode(childStar->getStarId());
        if (childStarNode->getIsFollowed()) {
            continue;
        }
        CCRect rect;
        rect.origin = CCPoint(childStarNode->getPosition().x - childStarNode->getContentSize().width / 2, childStarNode->getPosition().y - childStarNode->getContentSize().height / 2);
        rect.size = childStarNode->getContentSize();
        if (rect.containsPoint(touchLocationInNode)) {
            followChildStar(childStar->getStarId());
            return;
        }
    }
    stopFollow();
}
void PGStarNode::setOrbitalAngle(float orbitalAngle){
    orbitalAngle_ = orbitalAngle;
    if (orbitalAngle_ >= 0 && orbitalAngle_ < 180) {
        if (getZOrder() != -1 - indexInParent_) {
            setZOrder( -1 - indexInParent_);
        }
    }else if (orbitalAngle_ >= 180 && orbitalAngle_ < 360){
        if (getZOrder() != 1 + indexInParent_) {
            setZOrder(1 + indexInParent_);
        }
    }
    setPosition(posInOrbital(orbitalAngle_, getOrbitalRadius(), ((PGStarNode*)getParent())->getSAngle()));
    setScale(scaleInOrbital(orbitalAngle_, getOrbitalRadius()));
}

float PGStarNode::getOrbitalAngle(){
    return orbitalAngle_;
}
PGStarNode::PGStarOrbit* PGStarNode::PGStarOrbit::create(float radius, float angel1, float angle2, float orbitAngle){
    PGStarOrbit* obit = new PGStarOrbit();
    if (obit && obit->init(radius, angel1, angle2, orbitAngle)) {
        obit->autorelease();
        return obit;
    }else{
        delete obit;
        obit = NULL;
        return NULL;
    }
}
bool PGStarNode::PGStarOrbit::init(float radius, float angel1, float angle2, float orbitAngle){
    radius_ = radius;
    angle1_ = angel1;
    angle2_ = angle2;
    orbitAngle_ = orbitAngle;
    return true;
}
void PGStarNode::PGStarOrbit::draw(){
    CCNode::draw();
    for (float i = angle1_; i < angle2_; i += 5) {
        CCPoint pos = posInOrbital(i, radius_ ,((PGStarNode*)getParent())->getSAngle());
        ccDrawPoint(pos);
    }
}

void PGStarNode::PGStarFollow::startWithTarget(cocos2d::CCNode *pTarget){
    CCFollow::startWithTarget(pTarget);
    originScale = pTarget->getScale();
    originAnchorPoint = pTarget->getAnchorPoint();
    originPosition = pTarget->getPosition();
}
void PGStarNode::PGStarFollow::step(float dt){
    CCFollow::step(dt);
    CCPoint anthorPoint = CCPoint(m_pobFollowedNode->getPosition().x / m_pTarget->getContentSize().width, m_pobFollowedNode->getPosition().y / m_pTarget->getContentSize().height);
    m_pTarget->setAnchorPoint(anthorPoint);
    m_pTarget->setScale(originScale / m_pobFollowedNode->getScale());
}
PGStarNode::PGStarFollow* PGStarNode::PGStarFollow::create(cocos2d::CCNode *p_followedNode){
    PGStarFollow* sf = new PGStarFollow();
    if (sf && sf->initWithTarget(p_followedNode)) {
        sf->autorelease();
        return sf;
    }else{
        delete sf;
        sf = NULL;
        return NULL;
    }
}
bool PGStarNode::PGStarFollow::initWithTarget(cocos2d::CCNode *pFollowedNode){
    return CCFollow::initWithTarget(pFollowedNode);
}

PGStarNode::PGStarFollow::~PGStarFollow(){
    m_pTarget->setScale(originScale);
    m_pTarget->setAnchorPoint(originAnchorPoint);
    m_pTarget->setPosition(originPosition);
}

