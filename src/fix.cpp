#include <fix.hpp>

fix::fix(void)
{
   *this = 0;
}

fix::fix(int v)
{
   *this = v;
}

fix::fix(float v)
{
   *this = v;
}

fix::fix(const fix& other)
{
   *this = other;
}

fix fix::operator+(void) const
{
   fix result = *this;
   return result;
}

fix fix::operator+(int v) const
{
   fix result = *this;
   result += v;
   return result;
}

fix fix::operator+(float v) const
{
   fix result = *this;
   result += v;
   return result;
}

fix fix::operator+(const fix& other) const
{
   fix result = *this;
   result += other;
   return result;
}

fix fix::operator-(void) const
{
   fix result = *this;
   result.value = -result.value;
   return result;
}

fix fix::operator-(int v) const
{
   fix result = *this;
   result -= v;
   return result;
}

fix fix::operator-(float v) const
{
   fix result = *this;
   result -= v;
   return result;
}

fix fix::operator-(const fix& other) const
{
   fix result = *this;
   result -= other;
   return result;
}

fix fix::operator*(int v) const
{
   fix result = *this;
   result *= v;
   return result;
}

fix fix::operator*(float v) const
{
   fix result = *this;
   result *= v;
   return result;
}

fix fix::operator*(const fix& other) const
{
   fix result = *this;
   result *= other;
   return result;
}

fix fix::operator/(int v) const
{
   fix result = *this;
   result /= v;
   return result;
}

fix fix::operator/(float v) const
{
   fix result = *this;
   result /= v;
   return result;
}

fix fix::operator/(const fix& other) const
{
   fix result = *this;
   result /= other;
   return result;
}

fix& fix::operator=(int v)
{
   value = (v << FRACTION);
   return *this;
}

fix& fix::operator=(float v)
{
   value = (int)(v * (1 << FRACTION));
   return *this;
}

fix& fix::operator=(const fix& other)
{
   value = other.value;
   return *this;
}

bool fix::operator==(int v) const
{
   fix other = v;
   return (*this == other);
}

bool fix::operator==(float v) const
{
   fix other = v;
   return (*this == other);
}

bool fix::operator==(const fix& other) const
{
   return value == other.value;
}

bool fix::operator!=(int v) const
{
   fix other = v;
   return (*this != other);
}

bool fix::operator!=(float v) const
{
   fix other = v;
   return (*this != other);
}

bool fix::operator!=(const fix& other) const
{
   return value != other.value;
}

bool fix::operator>(int v) const
{
   fix other = v;
   return (*this > other);
}

bool fix::operator>(float v) const
{
   fix other = v;
   return (*this > other);
}

bool fix::operator>(const fix& other) const
{
   return value > other.value;
}

bool fix::operator<(int v) const
{
   fix other = v;
   return (*this < other);
}

bool fix::operator<(float v) const
{
   fix other = v;
   return (*this < other);
}

bool fix::operator<(const fix& other) const
{
   return value < other.value;
}

bool fix::operator>=(int v) const
{
   fix other = v;
   return (*this >= other);
}

bool fix::operator>=(float v) const
{
   fix other = v;
   return (*this >= other);
}

bool fix::operator>=(const fix& other) const
{
   return value >= other.value;
}

bool fix::operator<=(int v) const
{
   fix other = v;
   return (*this <= other);
}

bool fix::operator<=(float v) const
{
   fix other = v;
   return (*this <= other);
}

bool fix::operator<=(const fix& other) const
{
   return value <= other.value;
}

fix& fix::operator+=(int v)
{
   fix other = v;
   *this += other;
   return *this;
}

fix& fix::operator+=(float v)
{
   fix other = v;
   *this += other;
   return *this;
}

fix& fix::operator+=(const fix& other)
{
   value += other.value;
   return *this;
}

fix& fix::operator-=(int v)
{
   fix other = v;
   *this -= other;
   return *this;
}

fix& fix::operator-=(float v)
{
   fix other = v;
   *this -= other;
   return *this;
}

fix& fix::operator-=(const fix& other)
{
   value -= other.value;
   return *this;
}

fix& fix::operator*=(int v)
{
   value *= v;
   return *this;
}

fix& fix::operator*=(float v)
{
   fix other = v;
   *this *= other;
   return *this;
}

fix& fix::operator*=(const fix& other)
{
   value >>= (FRACTION / 4);
   value *= (other.value >> (FRACTION / 4));
   value >>= (FRACTION / 2);
   return *this;
}

fix& fix::operator/=(int v)
{
   value /= v;
   return *this;
}

fix& fix::operator/=(float v)
{
   fix other = v;
   *this /= other;
   return *this;
}

fix& fix::operator/=(const fix& other)
{
   value <<= (FRACTION / 4);
   value /= (other.value >> (FRACTION / 4));
   value <<= (FRACTION / 2);
   return *this;
}

fix& fix::operator++(void)
{
   *this += 1;
   return *this;
}

fix fix::operator++(int unused)
{
   fix result = *this;
   ++(*this);
   return result;
}

fix& fix::operator--(void)
{
   *this -= 1;
   return *this;
}

fix fix::operator--(int unused)
{
   fix result = *this;
   --(*this);
   return result;
}

fix::operator int(void) const
{
   return (value >> FRACTION);
}

fix::operator float(void) const
{
   return ((float)value / (1 << FRACTION));
}

fix fix::abs(void) const
{
   fix result = *this;
   if(result.value < 0)
   {
      result.value = -result.value;
   }
   return result;
}

fix fix::pow(int exponent) const
{
   fix result = 1;
   for(int i = 0; i < exponent; i++)
   {
      result *= *this;
   }
   return result;
}

fix fix::min(int v) const
{
   return this->min(fix(v));
}

fix fix::min(float v) const
{
   return this->min(fix(v));
}

fix fix::min(const fix& other) const
{
   fix result = *this;
   if(other < result)
   {
      result = other;
   }
   return result;
}

fix fix::max(int v) const
{
   return this->max(fix(v));
}

fix fix::max(float v) const
{
   return this->max(fix(v));
}

fix fix::max(const fix& other) const
{
   fix result = *this;
   if(other > result)
   {
      result = other;
   }
   return result;
}

fix operator+(int v, const fix& other)
{
   return other + v;
}

fix operator+(float v, const fix& other)
{
   return other + v;
}

fix operator-(int v, const fix& other)
{
   return -other + v;
}

fix operator-(float v, const fix& other)
{
   return -other + v;
}

fix operator*(int v, const fix& other)
{
   return other * v;
}

fix operator*(float v, const fix& other)
{
   return other * v;
}

fix operator/(int v, const fix& other)
{
   return fix(v) / other;
}

fix operator/(float v, const fix& other)
{
   return fix(v) / other;
}

bool operator==(int v, const fix& other)
{
   return other == v;
}

bool operator==(float v, const fix& other)
{
   return other == v;
}

bool operator!=(int v, const fix& other)
{
   return other != v;
}

bool operator!=(float v, const fix& other)
{
   return other != v;
}

bool operator>(int v, const fix& other)
{
   return other <= v;
}

bool operator>(float v, const fix& other)
{
   return other <= v;
}

bool operator<(int v, const fix& other)
{
   return other >= v;
}

bool operator<(float v, const fix& other)
{
   return other >= v;
}

bool operator>=(int v, const fix& other)
{
   return other < v;
}

bool operator>=(float v, const fix& other)
{
   return other < v;
}

bool operator<=(int v, const fix& other)
{
   return other > v;
}

bool operator<=(float v, const fix& other)
{
   return other > v;
}

int& operator+=(int& v, const fix& other)
{
   v += (int)other;
   return v;
}

float& operator+=(float& v, const fix& other)
{
   v += (float)other;
   return v;
}

int& operator-=(int& v, const fix& other)
{
   v -= (int)other;
   return v;
}

float& operator-=(float& v, const fix& other)
{
   v -= (float)other;
   return v;
}

int& operator*=(int& v, const fix& other)
{
   v *= (int)other;
   return v;
}

float& operator*=(float& v, const fix& other)
{
   v *= (float)other;
   return v;
}

int& operator/=(int& v, const fix& other)
{
   v /= (int)other;
   return v;
}

float& operator/=(float& v, const fix& other)
{
   v /= (float)other;
   return v;
}

