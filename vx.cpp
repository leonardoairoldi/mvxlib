#include "vx.h"

#include <exception>

vx::vx(mx& m, int i, Direction_t dir)
{
	if (dir == ROW) {
		r = m.size(COL);
		data = new double[m.size(COL)];
		for (int j = 0; j < m.size(COL); ++j) {
			data[j] = m.get(i, j);
		}

	}
	else {
		r = m.size(ROW);
		data = new double[m.size(ROW)];
		for (auto j = 0; j < m.size(ROW); ++j) {
			data[j] = m.get(j, i);
		}
	}

	c = 1;
}

vx::vx(mx& m) {
	if (m.size(COL) != 1 && m.size(ROW) != 1) throw std::length_error("Cast to matrix to vector is allowed only for (nx1) matrixes (Column vectors) or (1xn) matrixes casting them to column vector");

	if (m.size(COL) == 1) {
		r = m.size(ROW);
		c = 1;
		data = new double[r];
		for (int i = 0; i < r; ++i)
			data[i] = m.get(i, 0);
	}
	else {
		r = m.size(COL);
		c = 1;
		data = new double[r];
		for (int i = 0; i < r; ++i)
			data[i] = m.get(0, i);
	}
}


int vx::maximum_index() noexcept
{
	int max = 0;
	for (int i = 1; i < r; ++i)
		if (data[i] > data[max])
			max = i;
	return max;
}


int vx::minimum_index() noexcept
{
	int min = 0;
	for (int i = 1; i < r; ++i)
		if (data[i] < data[min])
			min = i;
	return min;
}

vx vx::zeros(int r)
{
	vx temp(r);
	for (int i = 0; i < r; ++i)
		temp.data[i] = 0;
	return temp;
}

vx vx::ones(int r)
{
	vx temp(r);
	for (int i = 0; i < r; ++i)
		temp.data[i] = 1;
	return temp;
}

vx mx::operator()(int i, Direction_t dir)
{
	if (i >= r || i < 0) throw new std::out_of_range("Index fail");
	return vx(*this, i, dir);
}


// Operators 


mx mx::operator+(const vx& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			temp.data[i * c + j] = data[i * c + j] + a.get(i);
	return temp;
}

mx mx::operator-(const vx& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			temp.data[i * c + j] = data[i * c + j] - a.get(i);
	return temp;
}

mx mx::operator*(const vx& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			temp.data[i * c + j] = data[i * c + j] * a.get(i);
	return temp;
}

mx mx::operator/(const vx& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			temp.data[i * c + j] = data[i * c + j] / a.get(i);
	return temp;
}

vx operator+(double a, const vx& m)
{
	return (vx&)(a + (mx&)m);
}
vx operator-(double a, const vx& m)
{
	return (vx&)(a - (mx&)m);
}
vx operator*(double a, const vx& m)
{
	return (vx&)(a * (mx&)m);
}
vx operator/(double a, const vx& m)
{
	return (vx&)(a / (mx&)m);
}


vx vx::slice(int start, int end) const {
	if (end <= start || start < 0 || end < 0) throw std::out_of_range("Index fail");
	if (end >= r) throw std::length_error("Slice dimension error");

	vx temp(end - start + 1);

	for (int i = start; i <= end; ++i) {
		temp.set(i - start, data[i]);
	}

	return temp;
}

void vx::set(int i, double v) {
	if (i >= r || i < 0) throw std::out_of_range("Index fail");
	data[i] = v;
}

double vx::get(int i) const {
	if (i >= r || i < 0) throw std::out_of_range("Index fail");
	return data[i];
}

void vx::print() {
	std::cout << "vx (" << r << ", " << c << ")" << "\n";
	std::cout << "[ ";
	for (int i = 0; i < r; ++i)
	{
		std::cout << data[i] << "\n";
	}
	std::cout << "]" << std::endl;
}

double& vx::operator()(int i) const
{
	if (i >= r || i < 0) throw new std::out_of_range("Index fail");
	return data[i];
}

vx vx::log(const vx& m) {
	return (vx&)mx::log((mx&)m);
}

vx vx::from_csv(std::string filename) {
	mx m = mx::from_csv(filename);
	vx v;
	try
	{
		v = vx(m);
	}
	catch (const std::length_error&)
	{
		throw std::invalid_argument("Imported matrix is not a vector");
	}
	return v;
}