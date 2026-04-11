#pragma once
#include <optional>

enum class SceneID {
	Initial,
	DotCountInput,
	DotInput,
	Result
};

class ISceneSwitcher {
private:
	std::optional<SceneID> requestedScene;
public:
	virtual void requestSwitchScene(SceneID id) = 0;
};