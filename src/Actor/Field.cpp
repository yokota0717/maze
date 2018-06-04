#include "Field.h"

Field::Field(const string& name, Object::Status status)
	:
	Object(name, status),
	LeftWall({ FieldState::Left, FieldState::LeftBottom, FieldState::LeftRight,FieldState::LeftRightBottom,FieldState::UpLeft,FieldState::UpLeftBottom,FieldState::UpLeftRight,FieldState::All }),
	RightWall({ FieldState::Right,FieldState::LeftRight,FieldState::LeftRightBottom,FieldState::RightBottom,FieldState::UpLeftRight,FieldState::UpRight,FieldState::UpRightBottom,FieldState::All }),
	UpWall({ FieldState::All,FieldState::Up,FieldState::UpBottom,FieldState::UpLeft,FieldState::UpLeftBottom,FieldState::UpLeftRight,FieldState::UpRight,FieldState::UpRightBottom }),
	BottomWall({ FieldState::Bottom,FieldState::LeftBottom,FieldState::LeftRightBottom,FieldState::RightBottom,FieldState::UpBottom,FieldState::UpLeftBottom,FieldState::UpRightBottom,FieldState::All })
{}

void Field::init() {
	loadMap((std::string)"./data/map/test.csv");
	insertAsChild(new Player("Player", Object::Status::run));
}
void Field::update() {
}
void Field::render() {
	for (int y = 0; y < sizeY_; ++y) {
		for (int x = 0; x < sizeX_; ++x) {
			DrawBox(field[y][x], lineColor);
		}
	}
	renderStart(start);
	renderGoal(goal);
}
void Field::setField(const int x, const int y) {
	sizeX_ = x;
	sizeY_ = y;
	field.resize(y);
	for (int i = 0; i < y; ++i) {
		field[i].resize(x);
	}
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			field[i][j] = { Math::Box2D(200.0f + 100 * j, 100.0f + 100 * i, 90.0f, 90.0f)};
		}
	}
}
bool Field::loadMap(std::string& path)
{
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
	this->field.resize(this->sizeY_);
	for (int y = 0; y < this->sizeY_; ++y) {
		this->field[y].resize(this->sizeX_);
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
				this->field[y][x].state = (FieldState)fieldState;
			}
			else {
				if (text == "s") {
					this->field[y][x].state = FieldState::Non;
					start = Math::Vec(200.0f + 100 * x + 45, 100.0f + 100 * y + 45);
				}
				if (text == "g") {
					this->field[y][x].state = FieldState::Non;
					goal = Math::Vec(200.0f + 100 * x + 45, 100.0f + 100 * y + 45);
				}
			}
			this->field[y][x].box = Math::Box2D(200.0f + 100 * x, 100.0f + 100 * y, 90.0f, 90.0f);
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

Field::FieldState Field::getState(Math::Vec& pos){
	return this->field[(int)pos.y][(int)pos.x].state;
}
bool Field::isLeftWall(Math::Vec& pos){
	for (auto block : this->LeftWall) {
		if (block == field[(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isRightWall(Math::Vec& pos){
	for (auto block : this->RightWall) {
		if (block == field[(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isUpWall(Math::Vec& pos){
	for (auto block : this->UpWall) {
		if (block == field[(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isBottomWall(Math::Vec& pos){
	for (auto block : this->BottomWall) {
		if (block == field[(int)pos.y][(int)pos.x].state) {
			return true;
		}
	}
	return false;
}
bool Field::isLeftWall(float x, float y) {
	return isLeftWall(Math::Vec(x, y));
}
bool Field::isRightWall(float x, float y){
	return isRightWall(Math::Vec(x, y));
}
bool Field::isUpWall(float x, float y){
	return isUpWall(Math::Vec(x, y));
}
bool Field::isBottomWall(float x, float y){
	return isBottomWall(Math::Vec(x, y));
}

Math::Vec Field::setPlayerPos(){
	return start;
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

void Field::renderStart(Math::Vec& start){
	DrawFormatStringF(start.x, start.y, blue, "START");
}

void Field::renderGoal(Math::Vec & goal){
	DrawFormatStringF(goal.x, goal.y, blue, "GOAL");
}
