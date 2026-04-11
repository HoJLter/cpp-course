#pragma once
#include <optional>

enum class SceneID {
	Initial,
	DotCountInput,
	DotInput,
	Result
};

class SharedData {
private:
	int dotCount;
public:
	int getDotCount();
	void setDotCount(int count);
};

class ISceneSwitcher {
private:
	std::optional<SceneID> requestedScene;
public:
	SharedData shared;
	virtual void requestSwitchScene(SceneID id) = 0;
};