// Copied Si64 Release. Now it's named as "Classic!Flowless_int64"
#include <iostream>
#include <bitset>

#define si64 safe_int64

class safe_int64 {
public:
	// 构造函数 & 析构函数 
	safe_int64() {
		flowed = 0;
		val = 0;
	}
	safe_int64(long long vll) {
		if (vll < 0) {
			val = -vll;
			*this = -(*this);
		}
		else val = vll;
		flowed = 0;
	}
	safe_int64(std::string vs) {
		if (vs[0] == '-') {
			val = 0;
			flowed = 0;
			for (int i = 1; i < vs.size(); i++) {
				safe_int64 tmp = 1;
				for (int j = 1; j < i; j++) tmp *= safe_int64(10);
				*this = *this + (safe_int64(vs[vs.size() - i] - '0') * tmp);
				if (flowed) {
					val[63] = 1;
					return;
				}
			}
			*this = -*this;
			if (flowed) {
				val[63] = 1;
			}
		}
		else {
			val = 0;
			flowed = 0;
			for (int i = 0; i < vs.size(); i++) {
				safe_int64 tmp = 1;
				for (int j = 0; j < i; j++) tmp *= safe_int64(10);
				*this = *this + (safe_int64(vs[vs.size() - i - 1] - '0') * tmp);
				if (flowed) {
					val.set();
					val[63] = 0;
					return;
				}
			}
			if (flowed) {
				val.set();
				val[63] = 0;
			}
		}
		
	}
	safe_int64(const char* vs) {
		val = 0;
		flowed = 0;
		int vsz = 0;
		for (int i = 0; vs[i] != '\0'; i++) {
			vsz++;
		}
		if (vs[0] == '-') {
			for (int i = 1; i < vsz; i++) {
				safe_int64 tmp = 1;
				for (int j = 1; j < i; j++) tmp *= safe_int64(10);
				*this = *this + (safe_int64(vs[vsz - i] - '0') * tmp);
				if (flowed) {
					val[63] = 1;
					return;
				}
			}
			*this = -*this;
			if (flowed) {
				val[63] = 1;
			}
		}
		else {
			for (int i = 0; i < vsz; i++) {
				safe_int64 tmp = 1;
				for (int j = 0; j < i; j++) tmp *= safe_int64(10);
				*this = *this + (safe_int64(vs[vsz - i - 1] - '0') * tmp);
				if (flowed) {
					val.set();
					val[63] = 0;
					return;
				}
			}
			if (flowed) {
				val.set();
				val[63] = 0;
			}
		}
		
	}
	~safe_int64() {}

	//赋值
	void operator=(safe_int64 sll) {
		val = sll.val;
		flowed = sll.flowed;
		return;
	}
	void operator+=(safe_int64 sll) {
		*this = *this + sll;
		return;
	}
	void operator-=(safe_int64 sll) {
		*this = *this - sll;
		return;
	}
	void operator*=(safe_int64 sll) {
		*this = *this * sll;
		return;
	}
	void operator/=(safe_int64 vsll) {
		*this = *this / vsll;
		return;
	}

	// 运算 
	safe_int64 operator+(safe_int64 sll) {
		safe_int64 ans;
		bool s1 = val[63], s2 = sll.val[63];
		if (s1 && s2) {
			ans = (-(*this)) + (-sll);
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (s1) {
			ans = sll - (-(*this));
			return ans;
		}
		if (s2) {
			ans = (*this) - (-sll);
			return ans;
		}

		char addi = 0;
		for (int i = 0; i < 63; i++) {
			char tmp = val[i] + sll.val[i] + addi;
			ans.val[i] = tmp % 2;
			addi = tmp / 2;
		}
		if (addi) {
			ans.val.set();
			ans.val[63] = 0;
			ans.flowed = 1;
		}
		return ans;
	}
	safe_int64 operator-(safe_int64 sll) {
		safe_int64 ans;
		bool s1 = val[63], s2 = sll.val[63];
		if (s1 && s2) {
			ans = (-sll) - (-(*this));
			return ans;
		}
		if (s1) {
			ans = (-(*this)) + sll;
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (s2) {
			ans = (*this) + (-sll);
			return ans;
		}
		if (sll > (*this)) {
			ans = sll - (*this);
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		char subi = 0;
		for (int i = 0; i < 63; i++) {
			int tmp = subi + sll.val[i];
			if (tmp > val[i]) {
				subi = 1;
				ans.val[i] = val[i] + 2 - tmp;
			}
			else {
				subi = 0;
				ans.val[i] = val[i] - tmp;
			}
		}
		return ans;
	}
	safe_int64 operator*(safe_int64 sll) {
		safe_int64 ans;
		bool s1 = val[63], s2 = sll.val[63];
		if (s1 && s2) {
			ans = (-(*this)) * (-sll);
			return ans;
		}
		if (s1) {
			ans = (-(*this)) * sll;
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (s2) {
			ans = (*this) * (-sll);
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		for (int i = 0; i < 63; i++) {
			safe_int64 t;
			if (sll.val[i]) {
				int tmp = val[63];
				t.val = val << i;
				t.val[63] = tmp;
				ans = ans + t;
				if (ans.flowed) {
					ans.val.set();
					ans.val[63] = 0;
					return ans;
				}
			}
		}
		return ans;
	}
	safe_int64 operator/(safe_int64 sll) {
		safe_int64 ans = 0ll;
		bool s1 = val[63], s2 = sll.val[63];
		if (s1 && s2) {
			ans = (-(*this)) / (-sll);
			return ans;
		}
		if (s1) {
			ans = (-(*this)) / sll;
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (s2) {
			ans = (*this) / (-sll);
			if (ans.flowed) {
				ans.val = 0;
				ans.val[63] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (sll == safe_int64(0ll)) {
			std::cerr << "MathError:Cannot use zero as a divisor!";
			exit(-1);
		}
		if (sll > (*this)) {
			ans.val = 0;
			return ans;
		}
		/* Older Ver. Slowerererer than now.
		ONE.val = 0;
		ONE.val[0] = 1;
		tmp -= sll;
		while (!tmp.val[63]) {
			tmp = tmp - sll;
			ans += ONE;
		}
		return ans;
		*/
		safe_int64 tmp = 0ll;
		for (int i = 62; i >= 0; i--) {
			tmp = tmp * safe_int64(2) + val[i];
			if (tmp.flowed) {
				ans.val.set();
				ans.val[63] = 0;
				return ans;
			}
			if (tmp >= sll) {
				ans.val[i] = 1;
				tmp -= sll;
			}
		}
		return ans;
	}
	safe_int64 operator%(safe_int64 sll) {
		safe_int64 ans;
		ans = sll * ((*this) / sll);
		ans = (*this) - ans;
		return ans;
	}

	// 比较
	bool operator==(safe_int64 sll) {
		for (int i = 63; i >= 0; i--) {
			if (val[i] != sll.val[i]) return 0;
		}
		return 1;
	}
	bool operator>(safe_int64 sll) {
		if (*this == sll) return 0;
		bool s1 = val[63], s2 = sll.val[63];
		if (s1 && s2) {
			return !((-(*this)) > (-sll));
		}
		if (s1) {
			return 0;
		}
		if (s2) {
			return 1;
		}

		for (int i = 62; i >= 0; i--) {
			if (val[i] < sll.val[i]) return 0;
			else if (val[i] > sll.val[i]) return 1;
		}
		return 0;
	}
	bool operator<(safe_int64 sll) {
		if ((!(*this > sll)) && (!(*this == sll))) return 1;
		return 0;
	}
	bool operator!=(safe_int64 sll) {
		return !(*this == sll);
	}
	bool operator>=(safe_int64 sll) {
		return (*this > sll) || (*this == sll);
	}
	bool operator<=(safe_int64 sll) {
		return (*this < sll) || (*this == sll);
	}

	// 单目
	safe_int64 operator-() {
		safe_int64 ONE, ans;
		ONE.val = 0;
		ONE.val[0] = 1;
		if (val[63]) {
			ans = *this;
			ans.val[63] = 0;
			for (int i = 0; i < 63; i++) {
				ans.val[i] = !val[i];
			}
			ans = ans + ONE;
		}
		else {
			if (*this == ONE) {
				ans.val.set();
				return ans;
			}
			bool is_zero = 1;
			ans = *this - ONE;
			for (int i = 0; i < 64; i++) {
				if (ans.val[i]) is_zero = 0;
				ans.val[i] = !ans.val[i];
			}
			ans.val[63] = 1;
			if (is_zero) return *this;
		}
		return ans;
	}

	// 输出(原始方案&导出至其他类型)

	void out(std::string type = "d", bool mode = 0) {
		if (type == "d") {
			out_d(mode);
		}
		if (type == "b") {
			out_b(mode);
		}
		if (type == "a") {
			out_d(1);
			out_b(mode);
		}
		return;
	}
	void out_d(bool enter = 0) {
		printf("%lld", val);
		if (enter) {
			printf("\n");
		}
		return;
	}
	void out_b(bool enter = 0) {
		for (int i = 63; i >= 0; i--) {
			std::cout << val[i];
		}
		if (enter) {
			printf("\n");
		}
		return;
	}
	long long to_longlong() {
		long long ans = 0;
		if (val[63]) {
			safe_int64 tmp = -(*this);
			ans = tmp.val.to_ullong();
			return -ans; // 无法返回-2^63，待修
		}
		ans = (*this).val.to_ullong();
		return ans;
	}
	std::string to_stdstring() {
		std::string ans = "";
		if (val[63]) {
			safe_int64 tmp = -*this;
			ans = "-" + tmp.to_stdstring();
			return ans;
		}
		if (*this == safe_int64(0ll)) {
			std::string tmp = "0";
			return tmp;
		}
		safe_int64 tmp = *this;
		while (tmp > safe_int64(0ll)) {
			char t = (tmp % safe_int64(10)).to_longlong() + '0';
			ans = t + ans;
			tmp = tmp / 10;
		}
		return ans;
	}

	// 补充函数 (内置整型转化等 )
	bool operator<(long long vll) {
		safe_int64 tmp = vll;
		return *this < tmp;
	}
	safe_int64 operator+(long long vll) {
		safe_int64 tmp = vll;
		return *this + tmp;
	}
private:
	std::bitset<64> val;
	bool flowed;
};
inline std::istream& operator>>(std::istream& is, safe_int64& vsll) {
	std::string s;
	is >> s;
	vsll = s;
	return is;
}
inline std::ostream& operator<<(std::ostream& os, safe_int64& vsll) {
	os << vsll.to_stdstring();
	return os;
}

