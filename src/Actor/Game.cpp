#include "Game.h"
#include "Field.h"
#include "Title.h"


Root::Root()
	:
	Object("Root", Object::Status::run),
	frame_(0)
{}
Root::~Root() {}

void Root::init(std::shared_ptr<Object> thisptr) {
	setWeakPtr(thisptr);
	insertAsChild(new Title("Title", Object::Status::run));
}
void Root::update() {
	++frame_;
}
void Root::render() {

}
int Root::frame() {
	return frame_;
}
int Root::receiveMsg(std::weak_ptr<Object> sender, const std::string & msg)
{
	if (msg == "Start") {
		insertAsChild(new Field("Field", Object::Status::run));
	}
	else if (msg == "Title") {
		insertAsChild(new Title("Title", Object::Status::run));
	}
	return 0;
}
Game::Game() 
	:
	pad(0)
{
	root = std::make_shared<Root>();
	root->init(root);
//	grafac = std::make_unique<GraphFactory>();
}

Game::~Game(){}

void Game::doAll() {
	kb.update();
	mouse.update();
	pad.update();
	if (kb.Down(Q)) { debug_ = !debug_; }
	root->updateWithChildren();
	root->renderWithChildren();
}
void Game::fin() {}

bool Game::DebugMode() {
	return debug_;
}

extern std::unique_ptr<Game> game(new Game);