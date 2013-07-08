#include "HelloWorldScene.h"

using namespace cocos2d;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("TileMap", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
   tileMap = CCTMXTiledMap::create("TileMap.tmx");
    this->addChild(tileMap);
	//the background is named as Background while creating TMX file
    CCTMXLayer *background = tileMap->layerNamed("Background");
	//captures all the objects of the TMX file created by TIle map.
	CCTMXObjectGroup *objectGroup = tileMap->objectGroupNamed("Objects");
	//spawnpoint is the name given to the heros spawn position.
	cocos2d::CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
	CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
	CCString *pX = (CCString*)spawnPoint->objectForKey("x");
	CCString *pY = (CCString*)spawnPoint->objectForKey("y");
	 
	 int x = pX->intValue();
	 int y = pY->intValue();
	 this->addChild(tileMap ,3 );

	 //creating the hero
	 player = CCSprite::create("Player.png");
	 //int y1 = y/3.74;
	// player->setPosition(ccp(x,y1));
	 player ->setPosition(ccp(34,271));
	 player->setAnchorPoint(ccp(1,1));
	 this->addChild(player,-1 );
	 //sets the camera to the player position.
	this->setViewPointCenter(player->getPosition());
	
	//enables touch
	this->setTouchEnabled(true);

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::setViewPointCenter(CCPoint position)
{
	//This code is not used as this is pointless at this point of time because both the Tiled and cocos2dx
	//has different co-ordinate system so it cannot be mapped by me. :(
	/*CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int x = MAX(position.x,winSize.width/2);
	int y = MAX(position.y,winSize.height/2);
	x = MIN(x,(tileMap->getMapSize().width * tileMap->getTileSize().width)-winSize.width/2);
	y = MIN(y,(tileMap->getMapSize().height * tileMap->getTileSize().height)-winSize.height/2);
	CCPoint actualPosition = ccp(x,y);*/
	CCPoint centerofView = ccp(0,-800); 
	//centerofView = ccpSub(centerofView, actualPosition);
	this->setPosition(centerofView);
	

}

void HelloWorld::handleUserTouch(CCTouch *touch)
{//gets the touch location
	CCPoint location = touch->getLocation();
	location = CCDirector::sharedDirector()->convertToGL(location);
//	pImage->setPosition(ccp(location.x,location.y));
	//prints the touch location
	CCLOG("%f",location.x);
	CCLOG("%f",location.y);
	 
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    // get the touch object
    CCTouch* touch = (CCTouch *)touches->anyObject();
    this->handleUserTouch(touch);
}
