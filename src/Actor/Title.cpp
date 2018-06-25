#include "Title.h"

Title::Title(const std::string & name, Object::Status status)
	:
	Object(name, status)
{}

void Title::init()
{

}

void Title::update()
{
	if (game->kb.Down(ENTER)) {
		StartGame();
	}
}

void Title::render()
{
	DrawFormatString(0, 0, debugRed, "TITLE");
}

bool Title::StartGame() {
	postMsg(getParentPtr(), "Start");
	this->kill();
	return 0;
}

int Title::postMsg(std::weak_ptr<Object> receiver, const std::string & msg)
{
	return receiver.lock()->receiveMsg(selfPtr(), msg);
}

