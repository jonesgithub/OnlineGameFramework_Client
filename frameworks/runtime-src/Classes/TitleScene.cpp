//
//  TitleScene.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/11/9.
//
//

#include "TitleScene.h"
#include "GameManager.h"

USING_NS_CC;
using namespace red;

bool TitleScene::init() {
    if(!Scene::init()) {
        return false;
    }
    
    // 初始化并启动游戏。临时写在此处
    auto gameManager = GameManager::getInstance();
    gameManager->init();
//    gameManager->connDelegate()->bindConnect([](){
//        log("[Red] do conn");
//    });
    
    auto customListener = EventListenerCustom::create("CONNECT", CC_CALLBACK_1(TitleScene::onConnect, this));
    getEventDispatcher()->addEventListenerWithFixedPriority(customListener, 1);
    
    gameManager->start();
    
    scheduleUpdate();
    return true;
}

// 此处是临时代码。最终会绑定到lua，由lua处理下面的2个循环
void TitleScene::update(float dlt) {
    UIThreadTask::getInstance()->do_tasks();
    
    auto protos = UIThreadTask::getInstance()->pop_protos();
    for(auto item: protos) {
        auto proto = item.asValueMap();
        log("do proto: %s", proto["_proto_name_"].asString().c_str());
    }
}

void TitleScene::onConnect(EventCustom *event) {
    log("[Red] do conn ...");
}
