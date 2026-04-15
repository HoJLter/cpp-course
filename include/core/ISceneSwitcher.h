#pragma once
#include <optional>

enum class SceneID {
	Initial,
	DotCountInput,
	DotInput,
	Result,
	Tests
};

struct SharedData {
	int dotCount;
	sf::ConvexShape contour;
	sf::VertexArray dots;
};

class ISceneSwitcher {
private:
	std::optional<SceneID> requestedScene;
public:
	SharedData shared;
	virtual void requestSwitchScene(SceneID id) = 0;
};