#pragma once

#include <cinttypes>
#include <string>
#include <complex>
#include <iostream>

namespace lab {

	using Complex = std::complex<double>;

	class BigInt
	{
	public:
		BigInt(int64_t = 0);
		BigInt(const BigInt&);
		BigInt(BigInt&&) noexcept;
		BigInt(std::string);
		BigInt(std::initializer_list<uint32_t>, int);

		~BigInt();

		BigInt& operator=(const BigInt&);
		BigInt& operator=(BigInt&&) noexcept;

		BigInt& operator+=(const BigInt&);
		BigInt& operator-=(const BigInt&);
		BigInt& operator*=(const BigInt&);
		BigInt& operator*=(int32_t);
		BigInt& operator/=(BigInt);
		BigInt& operator%=(BigInt);
		BigInt& operator<<=(uint64_t);
		BigInt& operator>>=(uint64_t);

		BigInt operator-() const;

		friend BigInt operator+(BigInt, const BigInt&);
		friend BigInt operator-(BigInt, const BigInt&);
		friend BigInt operator*(BigInt, const BigInt&);
		friend BigInt operator*(BigInt, int32_t);
		friend BigInt operator*(int32_t, BigInt);
		friend BigInt operator/(BigInt, BigInt);
		friend BigInt operator%(BigInt, BigInt);
		friend BigInt operator<<(BigInt, uint64_t);
		friend BigInt operator>>(BigInt, uint64_t);

		friend bool operator==(const BigInt&, const BigInt&);
		friend bool operator!=(const BigInt&, const BigInt&);
		friend bool operator<(const BigInt&, const BigInt&);
		friend bool operator>(const BigInt&, const BigInt&);
		friend bool operator<=(const BigInt&, const BigInt&);
		friend bool operator>=(const BigInt&, const BigInt&);

		friend std::istream& operator>>(std::istream&, BigInt&);
		friend std::ostream& operator<<(std::ostream&, const BigInt&);

		std::string toStr() const;
		BigInt& abs();
		size_t maxBit() const;

		int64_t alignBit(size_t);

		// -1 (a < b), 0 (a == b), 1 (a > b)
		static int compare(const BigInt& left, const BigInt& right, bool isAbs = false);

		static std::pair<BigInt, BigInt> div(BigInt, BigInt);
		//static std::pair<BigInt, size_t> floatDiv(BigInt, BigInt);
	private:
		int8_t _sign = 1;
		size_t _rank = 0;
		size_t _size = 0;
		uint32_t* _data = nullptr;

		const static int dataElementSize = 32;

		static void sum(BigInt& left, const BigInt& right, int rightSign);
		static size_t add(uint32_t*, const BigInt&, const BigInt&);
		static size_t sub(uint32_t*, const BigInt&, const BigInt&);

		static void mul(BigInt&, const BigInt&);
		static void shortMul(BigInt&, uint32_t);

		static size_t multiplyBufferSize;
		static Complex* mulBufferFirst, * mulBufferSecond;

		static size_t multiplyCacheSize;
		static Complex** rootCache;	// roots of 1 for any log(len)
		static size_t** revBitCache;	// bit-reversal permutation for any log(len)


		static void fft(Complex*, size_t, bool);
		static void recalcCache(size_t);
	};

}

