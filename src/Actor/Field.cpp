#include "Field.h"
#include <iostream>

Field::Field(const string& name, Object::Status status)
	:
	Object(name, status),
	LeftWall({ FieldState::Left, FieldState::LeftBottom, FieldState::LeftRight,FieldState::LeftRightBottom,FieldState::UpLeft,FieldState::UpLeftBottom,FieldState::UpLeftRight,FieldState::All }),
	RightWall({ FieldState::Right,FieldState::LeftRight,FieldState::LeftRightBottom,FieldState::RightBottom,FieldState::UpLeftRight,FieldState::UpRight,FieldState::UpRightBottom,FieldState::All }),
	UpWall({ FieldState::All,FieldState::Up,FieldState::UpBottom,FieldState::UpLeft,FieldState::UpLeftBottom,FieldState::UpLeftRight,FieldState::UpRight,FieldState::UpRightBottom }),
	BottomWall({ FieldState::Bottom,FieldState::LeftBottom,FieldState::LeftRightBottom,FieldState::RightBottom,FieldState::UpBottom,FieldState::UpLeftBottom,FieldState::UpRightBottom,FieldState::All })
{}

void Field::init() {
	this->cleared = false;
	loadMaps(std::vector<std::string>{(std::string)"test5.csv", (std::string)"test6.csv", (std::string)"test7.csv", (std::string)"test8.csv"});
	insertAsChild(new Player("Player", Object::Status::run));
}
void Field::update() {
	if (game->kb.Down(W)) { this->changeMap(MapChangeKey::UP); }
	if (game->kb.Down(A)) { this->changeMap(MapChangeKey::LEFT); }
	if (game->kb.Down(D)) { this->changeMap(MapChangeKey::RIGHT); }
	if (game->kb.Down(S)) { this->changeMap(MapChangeKey::BOTTOM); }
}
void Field::render() {
	DrawOutLine();
	for (int y = 0; y < sizeY_; ++y) {
		for (int x = 0; x < sizeX_; ++x) {
			DrawBox(field[this->activeMapID][y][x], lineColor);
			if (game->DebugMode()) {
				DrawFormatStringF(field[this->activeMapID][y][x].box.x, field[this->activeMapID][y][x].box.y, debugRed, "%d", field[this->activeMapID][y][x].state);
			}
		}
	}
	renderStart(Math::Vec(200.0f + 100 * start.x + 45, 100.0f + 100 * start.y + 45));
	renderGoal(Math::Vec(200.0f + 100 * goal.x + 45, 100.0f + 100 * goal.y + 45));
	if (cleared) {
		DrawFormatString(50, 50, GetColor(80, 255, 80), "GOAL!");
	}
}
bool Field::loadMaps(std::vector<std::string>& pathes) {
	for (int i = 0; i < 4; ++i) {
		loadMap(pathes[i], i);
	}
	return true;
}
void Field::changeMap(MapChangeKey key) {
	this->activeMapID = (int)key;
	std::cout << this->activeMapID << std::endl;
	postMsg(this->getObjectFromChildren("Player"), this->activeMapID);
}
bool Field::loadMap(std::string& path, int id)
{
	path = "./data/map/" + path;
	//バイナリファイルを読み取り専用で開く
	ifstream fin(path, ios::in | ios::binary);
	if (!fin) { return false; }
	//マップサイズの読み込み
	//一行分読み込む
	std::string line;
	std::getline(fin, line);
	//文字列操作のクラスにコピー
	std::istringstream is(line);
	//一文字分保管用
	std::string text;
	//isの内部から','までの文字をコピー
	std::getline(is, text, ',');
	(std::stringstream)text >> this->sizeX_;
	std::getline(is, text, ',');
	(std::stringstream)text >> this->sizeY_;
	//配列のサイズを変更
	this->field[id].resize(this->sizeY_);
	for (int y = 0; y < this->sizeY_; ++y) {
		this->field[id][y].resize(this->sizeX_);
	}
	//マップ情報を読み込み
	for (int y = 0; y < this->sizeY_; ++y) {
		std::string lineText;
		std::getline(fin, lineText);
		std::istringstream is_lt(lineText);
		for (int x = 0; x < this->sizeX_; ++x) {
			//一文字分取り出す
			std::string text;
			std::getline(is_lt, text, ',');
			//改行文字が入っていたら除く
			if (text.find("\r") != std::string::npos) {
				text.erase(text.find("\r"));
			}
			//文字列が数字のみの場合
			if (std::all_of(text.cbegin(), text.cend(), isdigit)) {
				//データ格納
				int fieldState;
				(std::stringstream)text >> fieldState;
				this->field[id][y][x].state = (FieldState)fieldState;
			}
			else {
				if (text == "s") {
					this->field[id][y][x].state = FieldState::Non;
					start = Math::Vec((float)x, (float)y);
					//start = Math::Vec(200.0f + 100 * x + 45, 100.0f + 100 * y + 45);
				}
				if (text == "g") {
					this->field[id][y][x].state = FieldState::Non;
					goal = Math::Vec((float)x, (float)y);
					//goal = Math::Vec(200.0f + 100 * x + 45, 100.0f + 100 * y + 45);
				}
			}
			this->field[id][y][x].box = Math::Box2D(200.0f + 100 * x, 100.0f + 100 * y, 90.0f, 90.0f);
		}
	}
	fin.close();
	return true;
}
int Field::sizeX() {
	return sizeX_;
}
int Field::sizeY() {
	return sizeY_;
}

Field::FieldState Field::getState(int nowMap, Math::Vec& pos) {
	return this->field[nowMap][(int)pos.y][(int)pos.x].state;
}
bool Field::isLeftWall(int nowMap, Math::Vec& pos) {
	for (auto block : this->LeftWall) {
		if (block == field[nowMap][(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isRightWall(int nowMap, Math::Vec& pos) {
	for (auto block : this->RightWall) {
		if (block == field[nowMap][(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isUpWall(int nowMap, Math::Vec& pos) {
	for (auto block : this->UpWall) {
		if (block == field[nowMap][(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isBottomWall(int nowMap, Math::Vec& pos) {
	for (auto block : this->BottomWall) {
		if (block == field[nowMap][(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isLeftWall(int nowMap, float x, float y) {
	return isLeftWall(nowMap, Math::Vec(x, y));
}
bool Field::isRightWall(int nowMap, float x, float y) {
	return isRightWall(nowMap, Math::Vec(x, y));
}
bool Field::isUpWall(int nowMap, float x, float y) {
	return isUpWall(nowMap, Math::Vec(x, y));
}
bool Field::isBottomWall(int nowMap, float x, float y) {
	return isBottomWall(nowMap, Math::Vec(x, y));
}

Math::Vec Field::setPlayerPos() {
	return start;
}

Math::Vec Field::getGoalPos(){
	return goal;
}

int Field::getActiveMapID() {
	return this->activeMapID;
}

bool Field::isCleared(){
	return this->cleared;
}

void Field::DrawBox(Box box, int color) {
	DrawBox2D(box.box, color);
	switch (box.state) {
	case Up:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		break;
	case Left:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		break;
	case Right:
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case Bottom:
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpLeft:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpBottom:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpRight:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case LeftRight:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case LeftBottom:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case RightBottom:
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpRightBottom:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpLeftRight:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case UpLeftBottom:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case LeftRightBottom:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case All:
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y - 5, color, 5);
		DrawLineF(box.box.x - 5, box.box.y - 5, box.box.x - 5, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x + box.box.w + 4, box.box.y - 5, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		DrawLineF(box.box.x - 5, box.box.y + box.box.h + 4, box.box.x + box.box.w + 4, box.box.y + box.box.h + 4, color, 5);
		break;
	case Non:
	default:
		break;
	}
}

void Field::DrawOutLine(){
	//上
	DrawLineF(
		this->field[this->activeMapID][0][0].box.x - 5,
		this->field[this->activeMapID][0][0].box.y - 5,
		this->field[this->activeMapID][0][this->sizeX_ - 1].box.x + this->field[this->activeMapID][0][0].box.w + 4,
		this->field[this->activeMapID][0][this->sizeX_ - 1].box.y - 5,
		lineColor, 5);
	//右
	DrawLineF(
		this->field[this->activeMapID][0][this->sizeX_ - 1].box.x + this->field[this->activeMapID][0][0].box.w + 4,
		this->field[this->activeMapID][0][this->sizeX_ - 1].box.y - 5,
		this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.x + this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.w + 4,
		this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.y + this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.h + 4,
		lineColor, 5);
	//左
	DrawLineF(
		this->field[this->activeMapID][0][0].box.x - 5,
		this->field[this->activeMapID][0][0].box.y - 5,
		this->field[this->activeMapID][this->sizeY_ - 1][0].box.x - 5,
		this->field[this->activeMapID][this->sizeY_ - 1][0].box.y + this->field[this->activeMapID][this->sizeY_ - 1][0].box.h + 4,
		lineColor, 5);
	//下
	DrawLineF(
		this->field[this->activeMapID][this->sizeY_ - 1][0].box.x - 5,
		this->field[this->activeMapID][this->sizeY_ - 1][0].box.y + this->field[this->activeMapID][this->sizeY_ - 1][0].box.h + 4,
		this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.x + this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.w + 4,
		this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.y + this->field[this->activeMapID][this->sizeY_ - 1][this->sizeX_ - 1].box.h + 4,
		lineColor, 5
	);
}

void Field::renderStart(Math::Vec& start) {
	DrawFormatStringF(start.x, start.y, blue, "START");
}

void Field::renderGoal(Math::Vec & goal) {
	DrawFormatStringF(goal.x, goal.y, blue, "GOAL");
}

int Field::postMsg(std::weak_ptr<Object> reciever, int mapnum) {
	dynamic_pointer_cast<Player>(reciever.lock())->recieveMsg(selfPtr(), mapnum);
	return 0;
}

int Field::receiveMsg(std::weak_ptr<Object> sender, const std::string & msg){
	if (msg == "Goal") {
		cleared = true;
	}
	return 0;
}
