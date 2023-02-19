#pragma once

#include <iterator>
#include <iostream>
#include <cstddef>
#include <algorithm>


template<size_t MAX_LENGTH>
class fixedString {
private:
	char m_string[MAX_LENGTH + 1] {};
	size_t m_size = 0;

public:
	fixedString() = default;
	fixedString(const char* string) { *this = string; }
	~fixedString() = default;

	size_t MaxLength() const { return MAX_LENGTH; }
	size_t Length() const { return this->m_size; }

	const char* c_str() const { return this->m_string; }

	fixedString& operator=(const char* str) {
		m_size = std::min(strlen(str), this->MaxLength());
		memcpy(this->m_string, str, m_size);
		this->m_string[m_size] = '\0';
		return *this;
	}
	fixedString operator+(const char* str) const {
		size_t length = this->Length();
		size_t i = 0;
		while (length < this->MaxLength() && str[i] != '\0') {
			this->m_string[length] = str[i];
			++length;
			++i;
		}
		this->m_string[length] = '\0';
		this->m_size = length;
		return *this;
	}
	fixedString& operator+=(const char* str) { *this = *this + str; return *this; }

	fixedString& operator=(const fixedString& other) { memcpy(this->m_string, other.m_string, other.Length() + 1); return *this; }
	fixedString& operator+(const fixedString& other) {
		size_t length = this->Length();
		size_t i = 0;
		while (length < this->MaxLength() && other.m_string[i] != '\0') {
			this->m_string[length] = other.m_string[i];
			++length;
			++i;
		}
		this->m_string[length] = '\0';
		this->m_size = length;
		return *this;
	}
	fixedString& operator+=(const fixedString& other) { *this = *this + other; return *this; }

	friend std::ostream& operator<<(std::ostream& os, const fixedString& str) { return os << str.m_string; }

	struct fStringIterator {
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = char;
		using pointer = char*;
		using reference = char&;

		fStringIterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		auto operator++() { m_ptr++; return *this; }
		auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }
		auto operator--() { m_ptr--; return *this; }
		auto operator--(int) { auto tmp = *this; --(*this); return tmp; }
		auto operator+=(const difference_type offset) { m_ptr += offset; return *this; }
		auto operator+(const difference_type offset) const { auto tmp = *this; return tmp += offset; }
		auto operator-=(const difference_type offset) { return *this += -offset; }
		auto operator-(const difference_type offset)const { auto tmp = *this; return tmp -= offset; }
		auto operator-(const fStringIterator& right) const { return m_ptr - right.m_ptr; }
		auto operator[](const difference_type offset) const { return *(*this + offset); }
		bool operator<(const fStringIterator& right) const { return m_ptr < right.m_ptr; }
		bool operator>(const fStringIterator& right) const { return right < *this; }
		bool operator<=(const fStringIterator& right) const { return !(right < *this); }
		bool operator>=(const fStringIterator& right) const { return !(*this < right); }
		friend bool operator==(const fStringIterator& a, const fStringIterator& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const fStringIterator& a, const fStringIterator& b) { return a.m_ptr != b.m_ptr; }

	private:
		pointer m_ptr;
	};

	fStringIterator begin() { return fStringIterator(&this->m_string[0]); }
	fStringIterator end() { return fStringIterator(&this->m_string[this->m_size]); }
};
