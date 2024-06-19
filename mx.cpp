#include "mx.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <exception>
#include <cmath>

mx::mx(double* data, int r, int c) noexcept
{
	this->data = data;
	this->r = r;
	this->c = c;
}

mx::mx() noexcept
{
	r = -1;
	c = -1;
	data = nullptr;
}


mx::mx(int r, int c)
{
	if (r <= 0 || c <= 0) throw new std::out_of_range("Invalid dimensions");
	this->r = r;
	this->c = c;
	data = new double[r * c];
}

mx::mx(const mx& m)
{
	if (m.data == nullptr || m.r == -1 || m.c == -1)
	{
		r = -1;
		c = -1;
		data = nullptr;
		return;
	}
	r = m.r;
	c = m.c;
	data = new double[r * c];
	for (int i = 0; i < r * c; ++i)
		data[i] = m.data[i];
}

mx::mx(int r, int c, std::initializer_list<double> list)
{
	if (r * c == list.size()); throw std::length_error("Initializer list dimensions do not match");

	this->r = r;
	this->c = c;
	data = new double[r * c];
	int i = 0;
	for (auto it = list.begin(); it != list.end() && i < (r * c); ++it)
		data[i++] = *it;

}

mx::mx(std::initializer_list<std::initializer_list<double>> list)
{
	r = list.size();
	c = list.begin()->size();
	data = new double[r * c];
	int i = 0;
	for (auto it = list.begin(); it != list.end() && i < (r * c); ++it)
	{
		if (it->size() != c) throw std::length_error("Initializer list dimensions do not match");
		for (auto it2 = it->begin(); it2 != it->end() && i < (r * c); ++it2)
			data[i++] = *it2;
	}

}

mx::~mx()
{
	delete[] data;
}

void mx::set(int i, int j, double val)
{
	if (i < 0 || i >= r || j < 0 || j >= c)
		throw std::out_of_range("Index out of bounds");
	data[i * c + j] = val;
}

double mx::get(int i, int j) const
{
	if (i < 0 || i >= r || j < 0 || j >= c)
		throw std::out_of_range("Index out of bounds");
	return data[i * c + j];
}

void mx::print()
{
	std::cout << "mx (" << r << ", " << c << ")" << "\n";
	std::cout << "[ ";
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
			std::cout << data[i * c + j] << " ";
		std::cout << "\n" << "  ";
	}
	std::cout << "]" << std::endl;
}

std::stringstream mx::to_string()
{
	std::stringstream ss;
	ss << "mx (" << r << ", " << c << ")" << "\n";
	ss << "[ ";
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
			ss << data[i * c + j] << " ";
		ss << "\n" << "  ";
	}
	ss << "]" << std::endl;

	return ss;
}


// Copy - Move operators

mx& mx::operator=(const mx& m)
{
	// Guard self assignment
	if (this == &m)
		return *this;

	// If same dimensions (of internal array, not nxm), do not reallocate memory
	if (data != nullptr && r * c == m.r * m.c)
	{
		r = m.r;
		c = m.c;
		for (int i = 0; i < r * c; ++i)
			data[i] = m.data[i];
		return *this;
	}

	// Reallocate memory
	delete[] data;
	r = m.r;
	c = m.c;
	data = new double[r * c];
	for (int i = 0; i < r * c; ++i)
		data[i] = m.data[i];
	return *this;
}

mx& mx::operator=(mx&& m) noexcept
{
	// Guard self assignment
	if (this == &m)
		return *this;

	// Move data
	delete[] data; // Delete old data stored in result
	r = std::exchange(m.r, -2);
	c = std::exchange(m.c, -2);
	data = std::exchange(m.data, nullptr);
	return *this;
}

double& mx::operator()(int i, int j)
{
	if (i < 0 || i >= r || j < 0 || j >= c)
		throw std::out_of_range("Index out of bounds");
	return data[i * c + j];
}


// Operators

mx mx::operator+(const mx& b) const
{
	// check dimensions
	if (this->r != b.r || this->c != b.c)
		throw std::length_error("Dimensions do not match");

	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = this->data[i] + b.data[i];
	return temp;
}


mx mx::operator-(const mx& b) const
{
	// check dimensions
	if (r != b.r || c != b.c)
		throw std::length_error("Dimensions do not match");

	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] - b.data[i];
	return temp;
}

mx mx::operator*(const mx& b) const
{
	// check dimensions
	if (r != b.r || c != b.c)
		throw std::length_error("Dimensions do not match");

	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] * b.data[i];
	return temp;
}

mx mx::operator/(const mx& b) const
{
	// check dimensions
	if (r != b.r || c != b.c)
		throw std::length_error("Dimensions do not match");

	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] / b.data[i];
	return temp;
}

mx mx::operator+(double a) const
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] + a;
	return temp;
}

mx mx::operator-(double a) const
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] - a;
	return temp;
}

mx mx::operator*(double a) const
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] * a;
	return temp;
}

mx mx::operator/(double a) const
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = data[i] / a;
	return temp;
}

mx operator+(double a, const mx& m)
{
	return m + a;
}

mx operator-(double a, const mx& m)
{
	mx temp(m.size(ROW), m.size(COL));
	for (int i = 0; i < m.size(ROW); ++i)
		for (int j = 0; j < m.size(COL); ++j)
			temp.set(i, j, a - m.get(i, j));
	return temp;
}

mx operator*(double a, const mx& m)
{
	return m * a;
}

mx operator/(double a, const mx& m) {
	mx temp(m.size(ROW), m.size(COL));
	for (int i = 0; i < m.size(ROW); ++i)
		for (int j = 0; j < m.size(COL); ++j)
			temp.set(i, j, a / m.get(i, j));
	return temp;
}

mx mx::log(const mx& m)
{
	mx temp(m.size(ROW), m.size(COL));
	for (int i = 0; i < m.size(ROW); ++i)
		for (int j = 0; j < m.size(COL); ++j)
			temp.set(i, j, std::log(m.get(i, j)));
	return temp;
}



bool mx::operator==(const mx& b) const
{
	if (r != b.r || c != b.c)
		return false;
	for (int i = 0; i < r * c; ++i)
		if (data[i] != b.data[i])
			return false;
	return true;
}

bool mx::operator!=(const mx& b) const
{
	return !(*this == b);
}

mx mx::transpose() const {
	mx temp(c, r);
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			temp.set(j, i, get(i, j));
		}
	}
	return temp;
}


//vx mx::operator()(int i, int j)
//{
//	if (i == ALL) {
//		return vx()
//	} else
//	//return data[i * c + j];
//}

mx mx::cumsum(Direction_t direction) const
{
	mx temp(r, c);
	if (direction == Direction_t::ROW)
	{
		for (int j = 0; j < c; ++j)
			temp.data[0 * c + j] = data[0 * c + j];
		for (int i = 1; i < r; ++i)
			for (int j = 0; j < c; ++j)
				temp.data[i * c + j] = temp.data[(i - 1) * c + j] + data[i * c + j];
	}
	else {
		for (int i = 0; i < r; ++i)
			temp.data[i * c + 0] = data[i * c + 0];
		for (int j = 1; j < c; ++j)
			for (int i = 0; i < r; ++i)
				temp.data[i * c + j] = temp.data[i * c + j - 1] + data[i * c + j];
	}

	return temp;
}


std::ostream& operator<<(std::ostream& os, mx& m) {
	for (int i = 0; i < m.r; ++i)
	{
		for (int j = 0; j < m.c; ++j)
			os << m.data[i * m.c + j] << " ";
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, mx& m) {
	for (int i = 0; i < m.r; ++i)
		for (int j = 0; j < m.c; ++j)
			is >> m.data[i * m.c + j];
	return is;
}

void mx::print_size() const {
	std::cout << "(" << r << ", " << c << ")" << std::endl;
}

int mx::size(Direction_t dir) const
{
	return dir == ROW ? r : c;
}

// ROW returns a column vector and vice versa
mx mx::sum(Direction_t direction) const
{
	if (direction == Direction_t::ROW)
	{
		mx temp = zeros(1, c);
		for (int j = 0; j < c; ++j)
			for (int i = 0; i < r; ++i)
				temp.data[j] += data[i * c + j];
		return temp;
	}
	else {
		mx temp = zeros(r, 1);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				temp.data[i] += data[i * c + j];
		return temp;
	}

}

mx mx::zeros(int r, int c)
{
	if (r <= 0 || c <= 0)
		throw std::out_of_range("Invalid dimensions");
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = 0;
	return temp;
}


mx mx::ones(int r, int c)
{
	if (r <= 0 || c <= 0)
		throw std::out_of_range("Invalid dimensions");
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = 1;
	return temp;
}

double mx::sum() const noexcept
{
	double sum = 0;
	for (int i = 0; i < r * c; ++i)
		sum += data[i];
	return sum;
}

double mx::maximum() const noexcept
{
	double max = data[0];
	for (int i = 1; i < r * c; ++i)
		if (data[i] > max)
			max = data[i];
	return max;
}

double mx::minimum() const noexcept
{
	double min = data[0];
	for (int i = 1; i < r * c; ++i)
		if (data[i] < min)
			min = data[i];
	return min;
}

mx mx::maximum(double n) const noexcept
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = std::max(data[i], n);
	return temp;
}


mx mx::minimum(double n) const noexcept
{
	mx temp(r, c);
	for (int i = 0; i < r * c; ++i)
		temp.data[i] = std::min(data[i], n);
	return temp;
}

