#ifndef FIX_HPP
#define FIX_HPP

#define FRACTION 32

class fix
{
   private:
      long long value;

   public:
      fix(void);
      fix(int v);
      fix(float v);
      fix(const fix& other);
      fix operator+(void) const;
      fix operator+(int v) const;
      fix operator+(float v) const;
      fix operator+(const fix& other) const;
      fix operator-(void) const;
      fix operator-(int v) const;
      fix operator-(float v) const;
      fix operator-(const fix& other) const;
      fix operator*(int v) const;
      fix operator*(float v) const;
      fix operator*(const fix& other) const;
      fix operator/(int v) const;
      fix operator/(float v) const;
      fix operator/(const fix& other) const;
      fix& operator=(int v);
      fix& operator=(float v);
      fix& operator=(const fix& other);
      bool operator==(int v) const;
      bool operator==(float v) const;
      bool operator==(const fix& other) const;
      bool operator!=(int v) const;
      bool operator!=(float v) const;
      bool operator!=(const fix& other) const;
      bool operator>(int v) const;
      bool operator>(float v) const;
      bool operator>(const fix& other) const;
      bool operator<(int v) const;
      bool operator<(float v) const;
      bool operator<(const fix& other) const;
      bool operator>=(int v) const;
      bool operator>=(float v) const;
      bool operator>=(const fix& other) const;
      bool operator<=(int v) const;
      bool operator<=(float v) const;
      bool operator<=(const fix& other) const;
      fix& operator+=(int v);
      fix& operator+=(float v);
      fix& operator+=(const fix& other);
      fix& operator-=(int v);
      fix& operator-=(float v);
      fix& operator-=(const fix& other);
      fix& operator*=(int v);
      fix& operator*=(float v);
      fix& operator*=(const fix& other);
      fix& operator/=(int v);
      fix& operator/=(float v);
      fix& operator/=(const fix& other);
      fix& operator++(void);
      fix operator++(int unused);
      fix& operator--(void);
      fix operator--(int unused);
      operator int(void) const;
      operator float(void) const;
      fix abs(void) const;
      fix pow(int exponent) const;
      fix min(int v) const;
      fix min(float v) const;
      fix min(const fix& other) const;
      fix max(int v) const;
      fix max(float v) const;
      fix max(const fix& other) const;
};

fix operator+(int v, const fix& other);
fix operator+(float v, const fix& other);
fix operator-(int v, const fix& other);
fix operator-(float v, const fix& other);
fix operator*(int v, const fix& other);
fix operator*(float v, const fix& other);
fix operator/(int v, const fix& other);
fix operator/(float v, const fix& other);
bool operator==(int v, const fix& other);
bool operator==(float v, const fix& other);
bool operator!=(int v, const fix& other);
bool operator!=(float v, const fix& other);
bool operator>(int v, const fix& other);
bool operator>(float v, const fix& other);
bool operator<(int v, const fix& other);
bool operator<(float v, const fix& other);
bool operator>=(int v, const fix& other);
bool operator>=(float v, const fix& other);
bool operator<=(int v, const fix& other);
bool operator<=(float v, const fix& other);
int& operator+=(int& v, const fix& other);
float& operator+=(float& v, const fix& other);
int& operator-=(int& v, const fix& other);
float& operator-=(float& v, const fix& other);
int& operator*=(int& v, const fix& other);
float& operator*=(float& v, const fix& other);
int& operator/=(int& v, const fix& other);
float& operator/=(float& v, const fix& other);

#endif

