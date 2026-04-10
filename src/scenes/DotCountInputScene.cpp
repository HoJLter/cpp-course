#include "scenes/DotCountInputScene.h"

DotCountInputScene::DotCountInputScene(sf::Vector2u windowSize) :
dotCountInput({300, 50}, {windowSize.x / 2, windowSize.y - 200}),
dotInputLabel("Enter count of dots:", { windowSize.x / 2, windowSize.y - 100}, 14){
	
}