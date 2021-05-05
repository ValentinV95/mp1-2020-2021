#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include "BigInt.h"

namespace lab {

	size_t BigInt::multiplyBufferSize = 0;
	size_t BigInt::multiplyCacheSize = 0;

	Complex* BigInt::mulBufferFirst = nullptr;
	Complex* BigInt::mulBufferSecond = nullptr;
	Complex** BigInt::rootCache = nullptr;
	size_t** BigInt::revBitCache = nullptr;

	BigInt::BigInt(int64_t num)
	{
		if (num < 0) {
			this->_sign = -1;
			num = -num;
		}

		if (num != 0) {
			this->_rank = 2;
			if (num < (1ull << BigInt::dataElementSize)) {
				this->_rank = 1;
			}

			this->_size = 2;
			this->_data = new uint32_t[this->_size]{ uint32_t(num), uint32_t(num >> BigInt::dataElementSize) };
		}
	}

	BigInt::BigInt(const BigInt& right)
		: _sign(right._sign)
		, _rank(right._rank)
		, _size(right._rank)
		, _data(new uint32_t[right._rank])
	{
		for (size_t i = 0; i < this->_rank; i++)
		{
			this->_data[i] = right._data[i];
		}
	}

	BigInt::BigInt(BigInt&& right) noexcept
		: _sign(right._sign)
		, _rank(right._rank)
		, _size(right._size)
		, _data(right._data)
	{
		right._sign = 1;
		right._rank = 0;
		right._size = 0;
		right._data = nullptr;
	}

	BigInt::BigInt(std::string num)
	{
		if (num.empty()) {
			this->_sign = 1;
			this->_rank = 0;
			this->_size = 0;
			this->_data = nullptr;

			return;
		}

		this->_size = num.size() * 7 / 2 / BigInt::dataElementSize + 1;
		this->_data = new uint32_t[this->_size]{};

		size_t startIndex = 0;
		this->_sign = 1;
		if (num.front() == '-') {
			this->_sign = -1;
			startIndex++;
		}

		while (num[startIndex] == '0') startIndex++;

		for (size_t bit = 0; startIndex != num.size(); bit++)
		{
			this->_data[bit / BigInt::dataElementSize] |=
				(num.back() - '0') % 2 << bit % BigInt::dataElementSize;

			int shift = 0;
			for (size_t i = startIndex; i < num.size(); i++)
			{
				int temp = (num[i] - '0') % 2;
				num[i] = (num[i] - '0' + shift) / 2 + '0';
				shift = temp * 10;

				assert(num[i] <= '9' || num[i] >= '0');
			}

			if (num[startIndex] == '0') startIndex++;
		}

		this->_rank = this->_size;
		while (this->_rank > 0 && this->_data[this->_rank - 1] == 0)
		{
			this->_rank--;
		}
	}

#pragma warning(push)
#pragma warning(disable:6386)
	BigInt::BigInt(std::initializer_list<uint32_t> iList, int sign)
		: _sign(sign)
		, _rank(iList.size())
		, _size(iList.size())
		, _data(new uint32_t[iList.size()])
	{
		size_t i = 0;
		for (uint32_t val : iList)
		{
			this->_data[i] = val;
			i++;
		}
	}
#pragma warning(pop)



	BigInt::~BigInt()
	{
		delete[] this->_data;
	}



	BigInt& BigInt::operator=(const BigInt& right)
	{
		if (this == &right) {
			return *this;
		}

		if (this->_size < right._rank) {
			this->_size = right._rank;

			delete[] this->_data;
			this->_data = new uint32_t[this->_size];
		}

		this->_sign = right._sign;
		this->_rank = right._rank;

		for (size_t i = 0; i < this->_rank; i++)
		{
			this->_data[i] = right._data[i];
		}

		return *this;
	}

	BigInt& BigInt::operator=(BigInt&& right) noexcept
	{
		if (this == &right) {
			return *this;
		}

		this->_sign = right._sign;
		this->_rank = right._rank;
		this->_size = right._size;
		std::swap(this->_data, right._data);

		return *this;
	}



	BigInt& BigInt::operator+=(const BigInt& right)
	{
		BigInt::sum(*this, right, 1);

		return *this;
	}

	BigInt& BigInt::operator-=(const BigInt& right)
	{
		BigInt::sum(*this, right, -1);

		return *this;
	}

	BigInt& BigInt::operator*=(const BigInt& right)
	{
		if (this->_rank == 0) {
			return *this;
		}
		if (right._rank == 0) {
			this->_rank = 0;
			return *this;
		}

		if (right._rank == 1) {
			BigInt::shortMul(*this, right._data[0]);
		}
		else if (this->_rank == 1) {
			BigInt temp(right);
			BigInt::shortMul(temp, this->_data[0]);
			*this = std::move(temp);
		}
		else {
			BigInt::mul(*this, right);
		}
		this->_sign = this->_sign * right._sign;

		return *this;
	}

	BigInt& BigInt::operator*=(int32_t right)
	{
		if (right < 0) {
			right = -right;
			this->_sign = -this->_sign;
		}
		BigInt::shortMul(*this, right);

		return *this;
	}

	BigInt& BigInt::operator/=(BigInt right)
	{
		*this = BigInt::div(std::move(*this), std::move(right)).first;

		return *this;
	}

	BigInt& BigInt::operator%=(BigInt left)
	{
		*this = BigInt::div(std::move(*this), std::move(left)).second;

		return *this;
	}

	BigInt& BigInt::operator<<=(uint64_t shift)
	{
		if (this->_rank == 0 || shift == 0) {
			return *this;
		}

		int64_t digitShift = shift / BigInt::dataElementSize;
		int64_t bitShift = shift % BigInt::dataElementSize;

		size_t nsize = this->_rank + digitShift + 1;
		uint32_t* buffer = this->_data;
		if (this->_size < nsize)
		{
			buffer = new uint32_t[nsize];
			this->_size = nsize;
		}

		for (int64_t i = this->_rank + digitShift - 1; i >= digitShift; i--)
		{
			buffer[i] = this->_data[i - digitShift];
		}
		for (int64_t i = digitShift - 1; i >= 0; i--)
		{
			buffer[i] = 0;
		}

#pragma warning(push)
#pragma warning(disable:6001)
		uint64_t temp = 0;
		size_t nrank = 0;
		for (size_t i = 0; i < this->_rank + digitShift; i++)
		{
			temp += (uint64_t(buffer[i]) << bitShift);
			buffer[i] = uint32_t(temp);
			temp >>= BigInt::dataElementSize;

			if (buffer[i] != 0) {
				nrank = i + 1;
			}
		}
#pragma warning(pop)
		if (temp != 0) {
			buffer[this->_rank + digitShift] = uint32_t(temp);
			nrank = this->_rank + digitShift + 1;
		}

		if (this->_data != buffer) {
			delete[] this->_data;
			this->_data = buffer;
		}

		this->_rank = nrank;

		return *this;
	}

	BigInt& BigInt::operator>>=(uint64_t shift)
	{

		int64_t digitShift = shift / BigInt::dataElementSize;
		int64_t bitShift = shift % BigInt::dataElementSize;

		if (this->_rank <= size_t(digitShift)) {
			this->_rank = 0;
			this->_sign = 1;

			return *this;
		}

		size_t nrank = this->_rank - digitShift;
		for (size_t i = 0; i < nrank; i++)
		{
			this->_data[i] = this->_data[i + digitShift];
		}

		uint64_t last = 0;
		for (int64_t i = nrank - 1; i >= 0; i--)
		{
			uint64_t temp = this->_data[i] % (1ll << bitShift);
			this->_data[i] = uint32_t((this->_data[i] >> bitShift) + last);
			last = (temp << (BigInt::dataElementSize - bitShift));
		}
		if (this->_data[nrank - 1] == 0) {
			nrank--;
		}

		this->_rank = nrank;

		return *this;
	}



	BigInt BigInt::operator-() const
	{
		BigInt temp(*this);
		temp._sign = -temp._sign;
		return temp;
	}

	BigInt operator+(BigInt left, const BigInt& right)
	{
		left += right;
		return left;
	}

	BigInt operator-(BigInt left, const BigInt& right)
	{
		left -= right;
		return left;
	}

	BigInt operator*(BigInt left, const BigInt& right)
	{
		left *= right;
		return left;
	}

	BigInt operator*(BigInt left, int32_t right)
	{
		left *= right;
		return left;
	}

	BigInt operator*(int32_t left, BigInt right)
	{
		right *= left;
		return right;
	}

	BigInt operator/(BigInt left, BigInt right)
	{
		left /= std::move(right);
		return left;
	}

	BigInt operator%(BigInt left, BigInt right)
	{
		left %= std::move(right);
		return left;
	}

	BigInt operator<<(BigInt left, uint64_t shift)
	{
		left <<= shift;
		return left;
	}

	BigInt operator>>(BigInt left, uint64_t shift)
	{
		left >>= shift;
		return left;
	}



	bool operator==(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) == 0;
	}

	bool operator!=(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) != 0;
	}

	bool operator<(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) == -1;
	}

	bool operator>(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) == 1;
	}

	bool operator<=(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) != 1;
	}

	bool operator>=(const BigInt& left, const BigInt& right)
	{
		return BigInt::compare(left, right, false) != -1;
	}



	std::istream& operator>>(std::istream& in, BigInt& num)
	{
		std::string num_str;
		in >> num_str;
		num = BigInt(std::move(num_str));

		return in;
	}

	std::ostream& operator<<(std::ostream& out, const BigInt& num)
	{
		out << num.toStr();

		return out;
	}



	void BigInt::sum(BigInt& left, const BigInt& right, int rightSign)
	{
		if (right._rank == 0) {
			return;
		}
		if (left._rank == 0) {
			left = right;
			left._sign = right._sign * rightSign;
			return;
		}

		size_t nsize = std::max(left._rank, right._rank) + 1;
		uint32_t* buffer = left._data;

		if (left._size < nsize) {
			buffer = new uint32_t[nsize];
			left._size = nsize;
		}

		if ((left._sign ^ right._sign ^ rightSign) >= 0) {
			left._rank = BigInt::add(buffer, left, right);
		}
		else {
			int compareRes = BigInt::compare(left, right, true);

			switch (compareRes)
			{
			case 0:
				left._sign = 1;
				left._rank = 0;

				break;
			case 1:
				left._rank = BigInt::sub(buffer, left, right);

				break;
			case -1:
				left._rank = BigInt::sub(buffer, right, left);
				left._sign = -left._sign;

				break;
			}
		}

		if (buffer != left._data) {
			delete[] left._data;
			left._data = buffer;
		}
	}

	size_t BigInt::add(uint32_t* dest, const BigInt& left, const BigInt& right)
	{
		uint64_t temp = 0;
		size_t i = 0;

		while (i < left._rank && i < right._rank)
		{
			temp += uint64_t(left._data[i]) + uint64_t(right._data[i]);
			dest[i] = uint32_t(temp);
			temp >>= BigInt::dataElementSize;

			i++;
		}
		while (i < left._rank && (dest != left._data || temp > 0)) {
			temp += left._data[i];
			dest[i] = uint32_t(temp);
			temp >>= BigInt::dataElementSize;

			i++;
		}
		while (i < right._rank) {
			temp += right._data[i];
			dest[i] = uint32_t(temp);
			temp >>= BigInt::dataElementSize;

			i++;
		}
		if (temp > 0) {
			dest[i] = uint32_t(temp);
			i++;
		}

		return std::max(i, left._rank);
	}

	// abs(left) >= abs(right)
	size_t BigInt::sub(uint32_t* dest, const BigInt& left, const BigInt& right)
	{
		int temp = 0;
		size_t nrank = 0;

		size_t i = 0;
		while (i < right._rank)
		{
			if (left._data[i] >= temp + right._data[i]) {
				dest[i] = uint32_t(left._data[i] - right._data[i] - temp);
				temp = 0;
			}
			else {
				dest[i] = uint32_t(left._data[i] - right._data[i] - temp);
				temp = 1;
			}

			if (dest[i] != 0) nrank = i;
			i++;
		}
		if (dest != left._data) {
			while (i < left._rank)
			{
				dest[i] = uint32_t(left._data[i] - temp);
				temp = 0;

				if (dest[i] != 0) nrank = i;
				i++;
			}
		}
		else {
			nrank = left._rank - 1;

			if (temp != 0) {
				dest[i] -= temp;
			}

			if (dest[nrank] == 0) {
				nrank--;
			}
		}

		return nrank + 1;
	}



	void BigInt::recalcCache(size_t logLen)
	{
		// maybe it works

		if (logLen < BigInt::multiplyCacheSize) return;

		// recalculate bit reverse
		size_t** tempRev = new size_t * [logLen + 1];

		for (size_t i = 0; i < BigInt::multiplyCacheSize; i++)
		{
			tempRev[i] = BigInt::revBitCache[i];
		}
		for (size_t i = BigInt::multiplyCacheSize; i <= logLen; i++)
		{
			tempRev[i] = nullptr;
		}

		delete[] BigInt::revBitCache;
		BigInt::revBitCache = tempRev;

		// recalculate roots of 1
		Complex** tempRoot;
		tempRoot = new Complex * [logLen + 1];

		for (size_t i = 0; i < BigInt::multiplyCacheSize; i++)
		{
			tempRoot[i] = BigInt::rootCache[i];
		}
		for (size_t i = BigInt::multiplyCacheSize; i <= logLen; i++)
		{
			tempRoot[i] = new Complex[1ll << i];

			double ang = 2 * M_PI / (1ll << i);
			Complex temp(cos(ang), sin(ang));

			tempRoot[i][0] = { 1, 0 };
			for (size_t j = 1; j < (1ull << i); j++)
			{
#pragma warning(push)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
				tempRoot[i][j] = tempRoot[i][j - 1] * temp;
#pragma warning(pop)
			}
		}

		delete[] BigInt::rootCache;
		BigInt::rootCache = tempRoot;
	}

	void BigInt::fft(Complex* arr, size_t logLen, bool invert)
	{
		if (logLen >= BigInt::multiplyCacheSize) {
			recalcCache(logLen);
			BigInt::multiplyCacheSize = logLen + 1;
		}

		if (BigInt::revBitCache[logLen - 1] == nullptr) {
			BigInt::revBitCache[logLen - 1] = new size_t[1ll << logLen];
			for (size_t i = 0; i < (1ull << logLen); i++)
			{
				size_t res = 0;
				for (size_t j = 0; j < logLen; j++)
				{
					if (i & (1ull << j)) {
						res |= 1ull << (logLen - 1 - j);
					}
				}

				BigInt::revBitCache[logLen - 1][i] = res;
			}
		}

		size_t n = (1ull << logLen);

		for (size_t i = 0; i < n; i++)
		{
			if (i < BigInt::revBitCache[logLen - 1][i]) {
				std::swap(arr[i], arr[BigInt::revBitCache[logLen - 1][i]]);
			}
		}

		for (size_t tempLenLog = 1; tempLenLog <= logLen; tempLenLog++)
		{
			for (size_t i = 0; i < n; i += (1ull << tempLenLog))
			{
				for (size_t j = 0; j < (1ull << (tempLenLog - 1)); j++)
				{
					size_t rootI = invert ? ((1ull << tempLenLog) - j) % (1ull << tempLenLog) : j;
					Complex u = arr[i + j];
					Complex v = arr[i + j + (1ull << (tempLenLog - 1))] * BigInt::rootCache[tempLenLog][rootI];
					arr[i + j] = u + v;
					arr[i + j + (1ull << (tempLenLog - 1))] = u - v;
				}
			}
		}

		if (invert) {
			for (size_t i = 0; i < n; i++)
			{
				arr[i] /= Complex(double(n));
			}
		}
	}

	void BigInt::mul(BigInt& left, const BigInt& right)
	{
		size_t nsize = std::max(left._rank, right._rank);
		size_t nrank = left._rank + right._rank + 1;
		uint32_t* buffer = left._data;

		if (left._size < nrank + 1)
		{
			buffer = new uint32_t[nrank + 1];
			left._size = nrank + 1;
		}

		size_t log_n = 0;
		while ((1ull << log_n) < nsize) log_n++;
		log_n += 2;

		if (BigInt::multiplyBufferSize < (1ull << log_n)) {
			multiplyBufferSize = (1ull << log_n);

			delete[] BigInt::mulBufferFirst;
			delete[] BigInt::mulBufferSecond;

			BigInt::mulBufferFirst = new Complex[BigInt::multiplyBufferSize]{};
			BigInt::mulBufferSecond = new Complex[BigInt::multiplyBufferSize]{};
		}
		else {
			for (size_t i = 0; i < BigInt::multiplyBufferSize; i++)
			{
				BigInt::mulBufferFirst[i] = BigInt::mulBufferSecond[i] = { 0, 0 };
			}
		}

#pragma warning(push)
#pragma warning(disable:4244)
		for (size_t i = 0; i < left._rank; i++)
		{
			BigInt::mulBufferFirst[i << 1] = left._data[i] % (1ll << (BigInt::dataElementSize / 2));
			BigInt::mulBufferFirst[(i << 1) + 1] = left._data[i] / (1ll << (BigInt::dataElementSize / 2));
		}
		for (size_t i = 0; i < right._rank; i++)
		{
			BigInt::mulBufferSecond[i << 1] = right._data[i] % (1ll << (BigInt::dataElementSize / 2));
			BigInt::mulBufferSecond[(i << 1) + 1] = right._data[i] / (1ll << (BigInt::dataElementSize / 2));
		}
#pragma warning(pop)

		fft(BigInt::mulBufferFirst, log_n, false);
		fft(BigInt::mulBufferSecond, log_n, false);

		for (size_t i = 0; i < (1ull << log_n); i++)
		{
			BigInt::mulBufferFirst[i] *= BigInt::mulBufferSecond[i];
		}

		fft(BigInt::mulBufferFirst, log_n, true);

		uint64_t tempSum = 0;
		size_t lastNotNull = 0;
		for (size_t i = 0; i < nrank || tempSum > 0; i++)
		{
			if (i < nrank) {
				tempSum += uint64_t(BigInt::mulBufferFirst[i << 1].real() + 0.5) +
					(uint64_t(BigInt::mulBufferFirst[(i << 1) + 1].real() + 0.5) << BigInt::dataElementSize / 2);
			}
			buffer[i] = tempSum % (1ll << BigInt::dataElementSize);
			tempSum >>= BigInt::dataElementSize;

			if (buffer[i] != 0) {
				lastNotNull = i;
			}
		}

		if (buffer != left._data) {
			delete[] left._data;
			left._data = buffer;
		}

		left._rank = lastNotNull + 1;
	}

	void BigInt::shortMul(BigInt& left, uint32_t right)
	{
		if (right == 1 || left._rank == 0) {
			return;
		}
		if (right == 0) {
			left._rank = 0;
			return;
		}
		if (left == 1) {
			left._data[0] = right;
			return;
		}

		uint32_t* buffer = left._data;
		if (left._size <= left._rank + 1)
		{
			left._size = left._rank + 1;
			buffer = new uint32_t[left._size];
		}

		uint64_t temp = 0;
		size_t i = 0;
		while (i < left._rank)
		{
			temp += uint64_t(left._data[i]) * uint64_t(right);
			buffer[i] = uint32_t(temp);
			temp >>= BigInt::dataElementSize;

			i++;
		}
		if (temp > 0)
		{
			buffer[i] = uint32_t(temp);
			i++;
		}

		if (left._data != buffer)
		{
			delete[] left._data;
			left._data = buffer;
		}

		left._rank = i;
	}



	std::pair<BigInt, BigInt> BigInt::div(BigInt left, BigInt right)
	{
		//assert(right._rank != 0);

		if (left._rank == 0) {
			return { 0, 0 };
		}

		int compareResult = BigInt::compare(left, right, true);
		if (compareResult == -1) {
			return { 0, std::move(left) };
		}
		if (compareResult == 0) {
			return { 1, 0 };
		}

		int64_t shift = int64_t(left._rank - right._rank + 1) * BigInt::dataElementSize;
		right <<= shift;

		BigInt ans = 0;
		int8_t nsign = left._sign * right._sign;

		if (left._sign != right._sign) {
			right._sign = left._sign;
		}

		while (shift >= 0)
		{
			ans <<= 1;

			if (BigInt::compare(left, right, true) != -1) {
				left -= right;
				ans += 1;
			}

			right >>= 1;
			shift--;
		}

		ans._sign = nsign;


		return { std::move(ans), std::move(left) };
	}



	int BigInt::compare(const BigInt& left, const BigInt& right, bool isAbs)
	{
		if (&left == &right) return 0;

		if (!isAbs && left._sign != right._sign) {
			return (left._sign < right._sign ? -1 : 1);
		}
		if (left._rank != right._rank) {
			return (left._rank < right._rank && (isAbs || left._sign > 0) ? -1 : 1);
		}

		for (int64_t i = int64_t(right._rank) - 1; i >= 0; i--)
		{
			if (left._data[i] != right._data[i]) {
				return (left._data[i] < right._data[i] && (isAbs || left._sign > 0) ? -1 : 1);
			}
		}

		return 0;
	}

	std::string BigInt::toStr() const
	{
		std::string ans = "0";

		for (size_t digit = this->_rank; digit > 0;)
		{
			digit--;
			for (int bit = BigInt::dataElementSize - 1; bit >= 0; bit--)
			{
				uint32_t temp = 0;
				if (((1u << bit) & this->_data[digit]) != 0) {
					temp = 1;
				}

				for (size_t i = 0; i < ans.size(); i++)
				{
					temp += 2 * (ans[i] - '0');
					ans[i] = '0' + temp % 10;
					temp /= 10;
				}
				if (temp != 0) {
					ans.push_back('0' + temp);
				}
			}
		}

		if (this->_sign == -1) {
			ans.push_back('-');
		}

		std::reverse(ans.begin(), ans.end());

		return ans;
	}

	BigInt& BigInt::abs()
	{
		this->_sign = -this->_sign;
		return *this;
	}

	int64_t BigInt::alignBit(size_t bit)
	{
		size_t temp = this->maxBit();

		if (temp > bit) {
			*this >>= temp - bit;
		}
		else {
			*this <<= bit - temp;
		}

		return int64_t(temp) - int64_t(bit);
	}

	static int getMaxBit(uint32_t a)
	{
		int l = 0, r = 32;
		while (r - l > 1)
		{
			int m = (l + r) / 2;
			if ((1ull << m) > a) {
				r = m;
			}
			else {
				l = m;
			}
		}

		return r;
	}

	size_t BigInt::maxBit() const
	{
		if (this->_rank == 0) return 0;
		return getMaxBit(this->_data[this->_rank - 1]) + (this->_rank - 1) * BigInt::dataElementSize;
	}

}

