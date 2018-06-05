#include "Math.h"

float Math::ToDegree(float radian) {
	return (radian / Math::PI)*180.0f;
}
float Math::ToRadian(float degree) {
	return (degree / 180.0f)*Math::PI;
}
float Math::Gravity(int onemeter) {
	return ((9.8f / 60) / 60)*onemeter;
}

//Vec-------------------------------------------------------------------------------------------
Math::Vec::Vec(float x, float y, float z)
	:
	x(x),
	y(y),
	z(z)
{}
Math::Vec::~Vec() {};
void Math::Vec::Zero(){
	x = 0;
	y = 0;
	z = 0;
}
//�x�N�g���𐳋K��
Math::Vec Math::Vec::Normalize() {
	float len = GetVecLen(*this);
	if (len == 0) return *this;
	return Math::Vec(x /= len, y /= len);
}
//�x�N�g����x���@�ŉ�]����
Math::Vec Math::Vec::RotateVecDegree(float deg) {
	float rad = (deg / 180) * Math::PI;
	return RotateVecRadian(rad);
}
//�x�N�g�����ʓx�@�ŉ�]����
Math::Vec Math::Vec::RotateVecRadian(float rad) {
	x = float(x*cos(rad) - y * sin(rad));
	y = float(x*sin(rad) + y * cos(rad));
	return *this;
}
//�x�N�g����x���@�ŉ�]����A��]���S�w��
void Math::Vec::RotateVecDegree(Math::Vec center, float deg) {
	float rad = (deg / 180) * Math::PI;
	RotateVecRadian(center, rad);
}
//�x�N�g�����ʓx�@�ŉ�]����A��]���S�w��
void Math::Vec::RotateVecRadian(Math::Vec center, float rad) {
	float tempX = x;
	float tempY = y;
	x = (tempX - center.x)*cos(rad) - (tempY - center.y)*sin(rad) + center.x;
	y = (tempX - center.x)*sin(rad) + (tempY - center.y)*cos(rad) + center.y;
}
//2�̃x�N�g���̊O�ς�Ԃ�(3����)
Math::Vec Math::Vec::GetCrossVec3(Math::Vec v1, Math::Vec v2) {
	Math::Vec Result;
	Result.x = v1.y*v2.z - v1.z*v2.y;
	Result.y = v1.z*v2.x - v1.x*v2.z;
	Result.z = v1.x*v2.y - v1.y*v2.x;
	return Result;
}
//�x�N�g���̒����𓾂�
float Math::Vec::GetVecLen() const {
	return std::powf(x*x + y * y + z * z, 0.5f);
}
//���K�����ꂽ�x�N�g���𓾂�
Math::Vec Math::Vec::GetUnitVec(Math::Vec v) {
	float len = GetVecLen(v);
	Math::Vec Result = v;
	Result.x /= len;
	Result.y /= len;
	Result.z /= len;
	return Result;
}
//�x�N�g����n�{����
Math::Vec Math::Vec::VecScale(Math::Vec v, float n) {
	Math::Vec Result;
	Result.x *= n;
	Result.y *= n;
	Result.z *= n;
	return Result;
}
//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̍����̕� (��:���w�̍��W�n)
Math::Vec Math::Vec::GetUnitNormVec2Left(Math::Vec v) {	//������90�x��]���Ă邾����Ł�
	Math::Vec Result = v;
	float tmpx = Result.x;
	Result.x = Result.y;
	Result.y = (-1)*tmpx;
	Result = GetUnitVec(Result);
	return Result;
}
//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̉E���̕� (��:���w�̍��W�n)
Math::Vec Math::Vec::GetUnitNormVec2Right(Math::Vec v) {	//�������͉E����Ł�
	Math::Vec Result = v;
	float tmpx = Result.x;
	Result.x = (-1)*Result.y;
	Result.y = tmpx;
	Result = GetUnitVec(Result);
	return Result;
}
//3�������ʂ̒P�ʖ@���x�N�g���𓾂�(��:���w�̍��W�n) v1,v2�͕��ʏ�ɑ��݂���x�N�g��
Math::Vec Math::Vec::GetUnitNormVec3(Math::Vec v1, Math::Vec v2) {
	Math::Vec Result = GetCrossVec3(v1, v2);
	Result = GetUnitVec(Result);
	return Result;
}
bool Math::Vec::Hit(Math::Vec& v) const {
	//������
	return false;
}
bool Math::Vec::Hit(Math::Box2D& b) const {
	if (x >= b.x && x < b.x + b.w) {
		if (y >= b.y && y < b.y + b.h) {
			return true;
		}
	}
	return false;
}
bool Math::Vec::Hit(Math::Circle& c) const {
	return (GetVecLen(Vec(x - c.center.x, y - c.center.y)) <= c.r);
}
bool Math::Vec::HitBox(Math::Box2D& b) const {
	return false;
}
//�I�y���[�^��`
Math::Vec& Math::Vec::operator = (const Math::Vec& v) {	x = v.x; y = v.y; z = v.z; return *this; }
const Math::Vec Math::Vec::operator + (const Math::Vec& v) const { return Vec(x + v.x, y + v.y, z + v.z); }
const Math::Vec Math::Vec::operator - (const Math::Vec& v) const { return Vec(x - v.x, y - v.y, z - v.z); }
const Math::Vec Math::Vec::operator * (const float n) const { return Vec(x*n, y*n, z*n); }
const Math::Vec Math::Vec::operator / (const float n) const { return Vec(x / n, y / n, z / n); }
Math::Vec& Math::Vec::operator += (const Math::Vec& v) { x += v.x; y += v.y; z += v.z; return *this; }
Math::Vec& Math::Vec::operator -= (const Math::Vec& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Math::Vec& Math::Vec::operator *= (const float n) { x *= n; y *= n; z *= n; return *this; }
Math::Vec& Math::Vec::operator /= (const float n) { x /= n; y /= n; z /= n; return *this; }
bool Math::Vec::operator==(const Vec & v) const {
	return this->x == v.x && this->y == v.y && this->z == v.z;
}
//---------------------------------------------------------------------------------------------------------------------

//Box2D----------------------------------------------------------------------------------------------------------------
Math::Box2D::Box2D()
	:
	x(0.0f),
	y(0.0f),
	w(0.0f),
	h(0.0f)
{}
Math::Box2D::Box2D(float x, float y, float w, float h)
	:
	x(x),
	y(y),
	w(w),
	h(h)
{}
Math::Box2D::~Box2D() {}
void Math::Box2D::Offset(Math::Vec v) {							//�������x�N�g��
	x += v.x;
	y += v.y;
}
void Math::Box2D::Offset(float vx, float vy) {			//������x,y
	x += vx;
	y += vy;
}
Math::Box2D Math::Box2D::OffsetCopy(float vx, float vy) const {	//x,y�������ɂ���Box2D��Ԃ�
	return Box2D(x + vx, y + vy, w, h);
}
Math::Box2D Math::Box2D::OffsetCopy(const Vec& v)const {
	return Math::Box2D(x + v.x, y + v.y, w, h);
}
bool Math::Box2D::Hit(const Math::Box2D& b) const {		//��`���m�̓����蔻��
	if (x < b.x + b.w	&&
		b.x < x + w &&
		y < b.y + b.h	&&
		b.h < y + h) {
		return true;
	}
	return false;
}
bool Math::Box2D::Hit(const Math::Vec& b) const {		//��`�ƃx�N�g���̓����蔻��
	if (x < b.x	&&
		b.x < x + w &&
		y < b.y	&&
		b.y < y + h) {
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------

//Circle-------------------------------------------------------------------------------------------------
Math::Circle::Circle()
	:
	center({ 0.0f, 0.0f, 0.0f }),
	r(0.0f)
{};
Math::Circle::Circle(float x, float y, float z, float r)
	:
	center({ 0.0f, 0.0f, 0.0f }),
	r(r)
{};
Math::Circle::~Circle() {};

void Math::Circle::Offset(Math::Vec v) {							//�������x�N�g��
	center.x += v.x;
	center.y += v.y;
	center.z += v.z;
}
void Math::Circle::Offset(float vx, float vy, float vz) {			//������x,y,z
	center.x += vx;
	center.y += vy;
	center.z = vz;
}
Math::Circle Math::Circle::OffsetCopy(float vx, float vy, float vz) const {	//x,y�������ɂ���Circle��Ԃ�
	return Math::Circle(center.x + vx, center.y + vy, center.z + vz, r);
}
Math::Circle Math::Circle::OffsetCopy(const Math::Vec& v)const {
	return Math::Circle(center.x + v.x, center.y + v.y, center.z + v.z, r);
}
bool Math::Circle::Hit(const Math::Circle& c) const {
	//���S�Ԃ̋�������̔��a�̘a��菬����������true
	float mx = powf(center.x - c.center.x, 2.0f);
	float my = powf(center.y - c.center.y, 2.0f);
	float mz = powf(center.z - c.center.z, 2.0f);
	if (powf(mx + my + mz, 0.5f) <= (r + c.r)) { return true; }
	return false;
}
bool Math::Circle::Hit(const Math::Vec& v) const {
	float mx = powf(center.x - v.x, 2.0f);
	float my = powf(center.y - v.y, 2.0f);
	float mz = powf(center.z - v.z, 2.0f);
	if (powf(mx + my + mz, 0.5f) <= r) { return true; }
	return false;
}
bool Math::Circle::Hit(const Math::Box2D& b) const {
	Math::Box2D hitArea1(b.x - r, b.y, b.w + r * 2, b.h);
	if (center.Hit(hitArea1)) { return true; }
	Math::Box2D hitArea2(b.x, b.y - r, b.w, b.h + r * 2);
	if (center.Hit(hitArea2)) { return true; }
	Math::Vec vertex[4] = { Math::Vec(b.x,b.y),
		Math::Vec(b.x + b.w - 1,b.y),
		Math::Vec(b.x + b.w - 1,b.y + b.h - 1),
		Math::Vec(b.x,b.y + b.h - 1)
	};
	for (int i = 0; i < 4; ++i) {
		if (Math::Vec::GetVecLen(center - vertex[i]) <= r) { return true; }
	}
	return false;
}


Math::Triangle::Triangle(Math::Vec v1, Math::Vec v2, Math::Vec v3)
	:
	v1(v1), v2(v2), v3(v3)
{}

Math::Orval::Orval(float x, float y, float lr, float sr, float ang)
	:
	x(x), y(y),
	lr(lr), sr(sr),
	angle(ang)
{}


Math::Rect::Rect(Vec tl, Vec tr, Vec bl, Vec br)
	:
	tl(tl),
	tr(tr),
	bl(bl),
	br(br)
{}
void Math::Rect::Rotate(float rad) {
	tl = tl.RotateVecRadian(rad);
	tr = tr.RotateVecRadian(rad);
	bl = bl.RotateVecRadian(rad);
	br = br.RotateVecRadian(rad);
}
void Math::Rect::Rotate(float rad, Math::Vec center) {
	tl.RotateVecRadian(center, rad);
	tr.RotateVecRadian(center, rad);
	bl.RotateVecRadian(center, rad);
	br.RotateVecRadian(center, rad);
}