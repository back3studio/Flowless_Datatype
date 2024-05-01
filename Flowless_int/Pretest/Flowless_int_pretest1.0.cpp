/*
Easily changed from C!Fi64.
Add get_val() to get the bitset<ms> from fi<ms>
Add set_biggest() & set_smallest() & check_flowed() instead of the same part of -,*,/ etc. to set the flowed int into the max/min of fi<ms>
*/

#include <iostream>
#include <bitset>

template <int maxsize>
class flowless_int {
public:
	// 构造函数 & 析构函数 
	flowless_int() {
		flowed = 0;
		val = 0;
	}
	flowless_int(long long vll) {
		if (vll < 0) {
			val = -vll;
			*this = -(*this);
		}
		else val = vll;
		flowed = 0;
	}
	flowless_int(std::string vs) {
		if (vs[0] == '-') {
			val = 0;
			flowed = 0;
			for (int i = 1; i < vs.size(); i++) {
				flowless_int tmp = 1;
				for (int j = 1; j < i; j++) tmp *= flowless_int(10);
				*this = *this + (flowless_int(vs[vs.size() - i] - '0') * tmp);
				if (check_flowed())return ;
			}
			*this = -*this;
			if (check_flowed())return ;
		}
		else {
			val = 0;
			flowed = 0;
			for (int i = 0; i < vs.size(); i++) {
				flowless_int tmp = 1;
				for (int j = 0; j < i; j++) tmp *= flowless_int(10);
				*this = *this + (flowless_int(vs[vs.size() - i - 1] - '0') * tmp);
				if (check_flowed())return ;
			}
			if (check_flowed())return ;
		}

	}
	flowless_int(const char* vs) {
		val = 0;
		flowed = 0;
		int vsz = 0;
		for (int i = 0; vs[i] != '\0'; i++) {
			vsz++;
		}
		if (vs[0] == '-') {
			for (int i = 1; i < vsz; i++) {
				flowless_int tmp = 1;
				for (int j = 1; j < i; j++) tmp *= flowless_int(10);
				*this = *this + (flowless_int(vs[vsz - i] - '0') * tmp);
				if (check_flowed())return ;
			}
			*this = -*this;
			if (check_flowed())return ;
		}
		else {
			for (int i = 0; i < vsz; i++) {
				flowless_int tmp = 1;
				for (int j = 0; j < i; j++) tmp *= flowless_int(10);
				*this = *this + (flowless_int(vs[vsz - i - 1] - '0') * tmp);
				if (flowed) {
					val.set();
					val[maxsize-1] = 0;
					return;
				}
			}
			if (check_flowed()) return;
		}

	}
	~flowless_int() {}

	//赋值
	void operator=(flowless_int vfi) {
		val = vfi.val;
		flowed = vfi.flowed;
		return;
	}
	void operator+=(flowless_int vfi) {
		*this = *this + vfi;
		return;
	}
	void operator-=(flowless_int vfi) {
		*this = *this - vfi;
		return;
	}
	void operator*=(flowless_int vfi) {
		*this = *this * vfi;
		return;
	}
	void operator/=(flowless_int vfi) {
		*this = *this / vfi;
		return;
	}

	// 运算 
	flowless_int operator+(flowless_int vfi) {
		flowless_int ans;
		bool s1 = val[maxsize-1], s2 = vfi.val[maxsize-1];
		if (s1 && s2) {
			ans = (-(*this)) + (-vfi);
			if (ans.flowed) {
				ans.val = 0;
				ans.val[maxsize-1] = 1;
			}
			else {
				ans = -ans;
			}
			return ans;
		}
		if (s1) {
			ans = vfi - (-(*this));
			return ans;
		}
		if (s2) {
			ans = (*this) - (-vfi);
			return ans;
		}

		char addi = 0;
		for (int i = 0; i < maxsize-1; i++) {
			char tmp = val[i] + vfi.val[i] + addi;
			ans.val[i] = tmp % 2;
			addi = tmp / 2;
		}
		if (addi) {
			ans.val.set();
			ans.val[maxsize-1] = 0;
			ans.flowed = 1;
		}
		return ans;
	}
	flowless_int operator-(flowless_int vfi) {
		flowless_int ans;
		bool s1 = val[maxsize-1], s2 = vfi.val[maxsize-1];
		if (s1 && s2) {
			ans = (-vfi) - (-(*this));
			return ans;
		}
		if (s1) {
			ans = (-(*this)) + vfi;
			ans = -ans;
			if (ans.check_flowed())return ans;
			return ans;
		}
		if (s2) {
			ans = (*this) + (-vfi);
			return ans;
		}
		if (vfi > (*this)) {
			ans = vfi - (*this);
			ans = -ans;
			if (ans.check_flowed())return ans;
			return ans;
		}
		char subi = 0;
		for (int i = 0; i < maxsize-1; i++) {
			int tmp = subi + vfi.val[i];
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
	flowless_int operator*(flowless_int vfi) {
		flowless_int ans;
		bool s1 = val[maxsize-1], s2 = vfi.val[maxsize-1];
		if (s1 && s2) {
			ans = (-(*this)) * (-vfi);
			return ans;
		}
		if (s1) {
			ans = (-(*this)) * vfi;
			ans = -ans;
			if (ans.check_flowed())return ans;
			return ans;
		}
		if (s2) {
			ans = (*this) * (-vfi);
			ans = -ans;
			if (ans.check_flowed())return ans;
			return ans;
		}
		for (int i = 0; i < maxsize-1; i++) {
			flowless_int t;
			if (vfi.val[i]) {
				int tmp = val[maxsize-1];
				t.val = val << i;
				t.val[maxsize-1] = tmp;
				ans = ans + t;
				if (ans.check_flowed())return ans;
			}
		}
		return ans;
	}
	flowless_int operator/(flowless_int vfi) {
		flowless_int ans = 0ll;
		bool s1 = val[maxsize-1], s2 = vfi.val[maxsize-1];
		if (s1 && s2) {
			ans = (-(*this)) / (-vfi);
			return ans;
		}
		if (s1) {
			ans = (-(*this)) / vfi;
			ans = -ans;
			if (ans.check_flowed()) return ans;
			return ans;
		}
		if (s2) {
			ans = (*this) / (-vfi);
			ans = -ans;
			if (ans.check_flowed())return ans;
			return ans;
		}
		if (vfi == flowless_int(0ll)) {
			std::cerr << "MathError:Cannot use zero as a divisor!";
			exit(-1);
		}
		if (vfi > (*this)) {
			ans.val = 0;
			return ans;
		}
		/* Older Ver. Slowerererer than now.
		ONE.val = 0;
		ONE.val[0] = 1;
		tmp -= vfi;
		while (!tmp.val[maxsize-1]) {
			tmp = tmp - vfi;
			ans += ONE;
		}
		return ans;
		*/
		flowless_int tmp = 0ll;
		for (int i = maxsize-2; i >= 0; i--) {
			tmp = tmp * flowless_int(2) + val[i];
			if (ans.check_flowed()) return ans;
			if (tmp >= vfi) {
				ans.val[i] = 1;
				tmp -= vfi;
			}
		}
		return ans;
	}
	flowless_int operator%(flowless_int vfi) {
		flowless_int ans;
		ans = vfi * ((*this) / vfi);
		ans = (*this) - ans;
		return ans;
	}

	// 比较
	bool operator==(flowless_int vfi) {
		for (int i = maxsize-1; i >= 0; i--) {
			if (val[i] != vfi.val[i]) return 0;
		}
		return 1;
	}
	bool operator>(flowless_int vfi) {
		if (*this == vfi) return 0;
		bool s1 = val[maxsize-1], s2 = vfi.val[maxsize-1];
		if (s1 && s2) {
			return !((-(*this)) > (-vfi));
		}
		if (s1) {
			return 0;
		}
		if (s2) {
			return 1;
		}

		for (int i = maxsize-2; i >= 0; i--) {
			if (val[i] < vfi.val[i]) return 0;
			else if (val[i] > vfi.val[i]) return 1;
		}
		return 0;
	}
	bool operator<(flowless_int vfi) {
		if ((!(*this > vfi)) && (!(*this == vfi))) return 1;
		return 0;
	}
	bool operator!=(flowless_int vfi) {
		return !(*this == vfi);
	}
	bool operator>=(flowless_int vfi) {
		return (*this > vfi) || (*this == vfi);
	}
	bool operator<=(flowless_int vfi) {
		return (*this < vfi) || (*this == vfi);
	}

	// 单目
	flowless_int operator-() {
		flowless_int ONE, ans;
		ONE.val = 0;
		ONE.val[0] = 1;
		if (val[maxsize-1]) {
			ans = *this;
			ans.val[maxsize-1] = 0;
			for (int i = 0; i < maxsize-1; i++) {
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
			for (int i = 0; i < maxsize; i++) {
				if (ans.val[i]) is_zero = 0;
				ans.val[i] = !ans.val[i];
			}
			ans.val[maxsize-1] = 1;
			if (is_zero) return *this;
		}
		return ans;
	}

	// 导出至其他类型
	long long to_longlong() {
		long long ans = 0;
		if (val[maxsize-1]) {
			flowless_int tmp = -(*this);
			ans = tmp.val.to_ullong();
			return -ans;
		}
		ans = (*this).val.to_ullong();
		return ans;
	}
	std::string to_stdstring() {
		std::string ans = "";
		if (val[maxsize-1]) {
			flowless_int tmp = -*this;
			ans = "-" + tmp.to_stdstring();
			return ans;
		}
		if (*this == flowless_int(0ll)) {
			std::string tmp = "0";
			return tmp;
		}
		flowless_int tmp = *this;
		while (tmp > flowless_int(0ll)) {
			char t = (tmp % flowless_int(10)).to_longlong() + '0';
			ans = t + ans;
			tmp = tmp / 10;
		}
		return ans;
	}

	// 特殊函数
	std::bitset<maxsize> get_val() {
		return val;
	}
	bool check_flowed() {
		if (flowed) {
			if (val[maxsize - 1]) set_smallest();
			if (!val[maxsize - 1]) set_biggest();
			return 1;
		}
		return 0;
	}
	void set_biggest() {
		val.set();
		val[maxsize - 1] = 0;
	}
	void set_smallest() {
		for (int i = 0; i < maxsize; i++) val[i] = 0;
		val[maxsize - 1] = 1;
	}

	// 补充函数 (内置整型转化等 )
	bool operator<(long long vll) {
		flowless_int tmp = vll;
		return *this < tmp;
	}
	flowless_int operator+(long long vll) {
		flowless_int tmp = vll;
		return *this + tmp;
	}
private:
	std::bitset<maxsize> val;
	bool flowed;
};

// 输入 & 输出
template <int maxsize>
inline std::istream& operator>>(std::istream& is, flowless_int<maxsize>& vfi) {
	std::string s;
	is >> s;
	vfi = s;
	return is;
}
template <int maxsize>
inline std::ostream& operator<<(std::ostream& os, flowless_int<maxsize>& vfi) {
	os << vfi.to_stdstring();
	return os;
}
