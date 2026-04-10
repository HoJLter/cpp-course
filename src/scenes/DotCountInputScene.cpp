#include "scenes/DotCountInputScene.h"

DotCountInputScene::DotCountInputScene(sf::Vector2u windowSize, SceneManager& sm) :
	Scene(sm),
	dotCountInput({300.f, 50.f}, {windowSize.x / 2.f, windowSize.y - 200.f}),
	dotInputLabel("Enter count of dots:", { windowSize.x / 2.f, windowSize.y - 100.f}, 14){
	
}