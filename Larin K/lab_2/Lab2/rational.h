#pragma once

#include <utility>
#include <algorithm>
#include <iostream>

namespace lab {

	template <typename T>
	class Rational
	{
	public:
		Rational()
			: numerator(0)
			, denominator(1)
		{}
		Rational(const Rational&) = default;
		Rational(Rational&&) = default;

		template <typename U>
		Rational(U num)
			: numerator(std::move(num))
			, denominator(1)
		{}
		Rational(T num, T denom)
			: numerator(std::move(num))
			, denominator(std::move(denom))
		{
			assert(this->denominator != 0);

			Rational::normalize(*this);
		}

		~Rational() = default;

		Rational& operator=(const Rational&) = default;
		Rational& operator=(Rational&&) = default;

		Rational& operator+=(const Rational& right)
		{
			this->numerator = this->numerator * right.denominator + right.numerator * this->denominator;
			this->denominator *= right.denominator;
			Rational::normalize(*this);

			return *this;
		}
		Rational& operator-=(const Rational& right)
		{
			this->numerator = this->numerator * right.denominator - right.numerator * this->denominator;
			this->denominator *= right.denominator;
			Rational::normalize(*this);

			return *this;
		}
		Rational& operator*=(const Rational& right)
		{
			this->numerator *= right.numerator;
			this->denominator *= right.denominator;
			Rational::normalize(*this);

			return *this;
		}
		Rational& operator/=(const Rational& right)
		{
			assert(right.numerator != 0);

			this->numerator *= right.denominator;
			this->denominator *= right.numerator;
			Rational::normalize(*this);

			return *this;
		}

		Rational operator-() const
		{
			return Rational(-this->numerator, this->denominator);
		}

		friend Rational operator+(Rational left, const Rational& right)
		{
			left += right;
			return left;
		}
		friend Rational operator-(Rational left, const Rational& right)
		{
			left -= right;
			return left;
		}
		friend Rational operator*(Rational left, const Rational& right)
		{
			left *= right;
			return left;
		}
		friend Rational operator/(Rational left, const Rational& right)
		{
			left /= right;
			return left;
		}


		friend bool operator==(const Rational& left, const Rational& right)
		{
			return left.numerator == right.numerator && left.denominator == right.denominator;
		}
		friend bool operator!=(const Rational& left, const Rational& right)
		{
			return !(left == right);
		}
		friend auto operator<(const Rational& left, const Rational& right)
		{
			return (left.numerator * right.denominator) < (right.numerator * left.denominator);
		}
		friend auto operator>(const Rational& left, const Rational& right)
		{
			return (left.numerator * right.denominator) > (right.numerator * left.denominator);
		}
		friend auto operator<=(const Rational& left, const Rational& right)
		{
			return (left.numerator * right.denominator) <= (right.numerator * left.denominator);
		}
		friend auto operator>=(const Rational& left, const Rational& right)
		{
			return (left.numerator * right.denominator) >= (right.numerator * left.denominator);
		}

		friend std::istream& operator>>(std::istream& in, Rational& num)
		{
			in >> num.numerator;
			char c;
			in >> c;
			in >> num.denominator;
			Rational::normalize(num);

			return in;
		}
		friend std::ostream& operator<<(std::ostream& out, const Rational& num)
		{
			out << num.numerator;
			if (num.denominator != 0) {
				out << " / " << num.denominator;
			}

			return out;
		}

	private:
		T numerator;
		T denominator;

		static T gcd(T a, T b)
		{
			while (b != 0)
			{
				a %= b;
				std::swap(a, b);
			}

			return a;
		}

		static void normalize(Rational& num)
		{
			int sign = 1;
			if (num.numerator < 0) {
				sign *= -1;
				num.numerator *= -1;
			}
			if (num.denominator < 0) {
				sign *= -1;
				num.denominator *= -1;
			}

			T temp = gcd(num.numerator, num.denominator);
			num.numerator /= temp;
			num.denominator /= temp;

			num.numerator *= sign;
		}
	};

}

