#include "punkt.h"

Punkt::Punkt()
{
    this->x = 0;
    this->y = 0;
}

Punkt::Punkt(float x, float y)
{
    this->x = x;
    this->y = y;
}

Punkt::Punkt(const Punkt &a)
{
    this->x = a.x;
    this->y = a.y;
}

void Punkt::swap(Punkt *param) {
    Punkt *temp = new Punkt(this->x,this->y);
    this->x = param->x;
    this->y = param->y;
    param->x = temp->x;
    param->y = temp->y;
    delete temp;
}

void Punkt::swapX(Punkt *param) {
    Punkt *temp = new Punkt(this->x,this->y);
    this->x = param->x;
    param->x = temp->x;
    delete temp;
}

void Punkt::swapY(Punkt *param) {
    Punkt *temp = new Punkt(this->x,this->y);
    this->y = param->y;
    param->y = temp->y;
    delete temp;
}

void Punkt::round() {
    x = ::round(x);
    y = ::round(y);
}

bool Punkt::naOdcinku(Punkt A, Punkt B)
{
    if (A.y > B.y)
        A.swap(&B);
    if (this->y < A.y || this->y > B.y)
        return false;

    if (A.x > B.x)
        A.swap(&B);
    if (this->x < A.x || this->x > B.x)
        return false;

    float ratio1 = (A.y - B.y) / sqrt(pow(A.y - B.y,2) + pow(A.x - B.x, 2));
    float ratio2 = (A.y - this->y) / sqrt(pow(A.y - this->y,2) + pow(A.x - this->x, 2));

    if (ratio1 == ratio2)
        return true;

    return false;
}

QString Punkt::GetPunkt()
{
    return QString::number(this->x) + "  " + QString::number(this->y);
}

Punkt Punkt::operator + (Punkt param) {
    int a = param.x + this->x;
    int b = this->y + param.y;
    Punkt result(a,b);
    return result;
}
/*
Punkt Punkt::operator * (int param) {
    Punkt result(param*this->x, param*this->y);
    return result;
}*/
Punkt Punkt::operator * (float param) {
    Punkt result(param*this->x, param*this->y);
    return result;
}

Punkt& Punkt::operator = (const Punkt &param) {
    if (this == &param)
      return *this;

    this->x = param.x;
    this->y = param.y;

    return *this;
}
/*
Punkt& Punkt::operator *= (const int &param) {
    (*this) = (*this) * param;
    return *this;
}*/
Punkt& Punkt::operator *= (const float &param) {
    (*this) = (*this) * param;
    return *this;
}
Punkt& Punkt::operator += (const Punkt &param) {
    (*this) = (*this) + param;
    return *this;
}
