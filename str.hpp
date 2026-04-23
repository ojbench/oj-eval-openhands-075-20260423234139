#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
	char *data;
	size_t length;

public:
	str() : data(nullptr), length(0) {
		data = new char[1];
		data[0] = '\0';
	}

	str(const char &c) : data(nullptr), length(1) {
		data = new char[2];
		data[0] = c;
		data[1] = '\0';
	}

	str(const char *&& s_) : data(nullptr), length(0) {
		if (s_ == nullptr) {
			data = new char[1];
			data[0] = '\0';
		} else {
			length = strlen(s_);
			data = new char[length + 1];
			strcpy(data, s_);
		}
	}

	str &operator=(const char *&& s_) {
		if (data != s_) {
			delete[] data;
			if (s_ == nullptr) {
				length = 0;
				data = new char[1];
				data[0] = '\0';
			} else {
				length = strlen(s_);
				data = new char[length + 1];
				strcpy(data, s_);
			}
		}
		return *this;
	}

	str(const str &other) : data(nullptr), length(other.length) {
		data = new char[length + 1];
		strcpy(data, other.data);
	}

	str &operator=(const str &other) {
		if (this != &other) {
			delete[] data;
			length = other.length;
			data = new char[length + 1];
			strcpy(data, other.data);
		}
		return *this;
	}

	char &operator[](size_t pos) {
		return data[pos];
	}

	size_t len() const {
		return length;
	}

	str join(const std::vector<str> &strs) const {
		if (strs.empty()) {
			return str();
		}
		
		// Calculate total length needed
		size_t total_len = 0;
		for (size_t i = 0; i < strs.size(); i++) {
			total_len += strs[i].length;
			if (i < strs.size() - 1) {
				total_len += this->length;
			}
		}
		
		// Create result string
		str result;
		delete[] result.data;
		result.length = total_len;
		result.data = new char[total_len + 1];
		
		// Build the joined string
		size_t pos = 0;
		for (size_t i = 0; i < strs.size(); i++) {
			for (size_t j = 0; j < strs[i].length; j++) {
				result.data[pos++] = strs[i].data[j];
			}
			if (i < strs.size() - 1) {
				for (size_t j = 0; j < this->length; j++) {
					result.data[pos++] = this->data[j];
				}
			}
		}
		result.data[pos] = '\0';
		
		return result;
	}

	str slice(size_t l, size_t r) const {
		if (l >= length || l >= r) {
			return str();
		}
		
		size_t slice_len = std::min(r, length) - l;
		str result;
		delete[] result.data;
		result.length = slice_len;
		result.data = new char[slice_len + 1];
		
		for (size_t i = 0; i < slice_len; i++) {
			result.data[i] = data[l + i];
		}
		result.data[slice_len] = '\0';
		
		return result;
	}

	~str() {
		delete[] data;
	}
};
