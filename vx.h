#pragma once
#include "mx.h"

// Vectors are only column vectors
// (n x 1) matrix

class vx : public mx
{
public:
	vx() noexcept : mx() {}
	vx(int r) : mx(r, 1) {}
	vx(const vx& a) : mx(a) {}
	//vx(const vx&& a) = delete;	
	vx(mx& m, int i, Direction_t dir);

	vx(mx& m); // cast is possible if matrix is (nx1)

	void set(int i, double v);
	double get(int i) const;

	void print();

	double& operator()(int i) const;

	vx slice(int start, int end) const;

	/// <summary>
	/// Returns the row of the maximum value in the vector in the array
	/// 
	/// </summary>
	/// <returns>Row index</returns>
	int maximum_index() noexcept;
	/// <summary>
	/// Returns the row of the minimum value in the vector in the array
	/// 
	/// </summary>
	/// <returns>Row index</returns>
	int minimum_index() noexcept;

	static vx zeros(int r);
	static vx ones(int r);

	double last() const noexcept { return data[r - 1]; }

	vx cumsum() const { return (vx&)mx::cumsum(ROW); }
	double sum() const noexcept { return mx::sum(); }


	// Matrix-Vector inverse operators
	mx operator+(const mx& m) const { return m + *this; }
	mx operator-(const mx& m) const { return m - *this; }
	mx operator*(const mx& m) const { return m * *this; }
	mx operator/(const mx& m) const { return m / *this; }

	// Array-Array operators
	vx operator+(const vx& b) const { return (vx&)(((mx&)*this) + (mx&)b); } // terrible is there a better way?
	vx operator-(const vx& b) const { return (vx&)(((mx&)*this) - (mx&)b); }
	vx operator*(const vx& b) const { return (vx&)(((mx&)*this) * (mx&)b); }
	vx operator/(const vx& b) const { return (vx&)(((mx&)*this) / (mx&)b); }

	// Array-Value operators
	vx operator+(double v) { return (vx&)(((mx&)*this) + v); }
	vx operator-(double v) { return (vx&)(((mx&)*this) - v); }
	vx operator*(double v) { return (vx&)(((mx&)*this) * v); }
	vx operator/(double v) { return (vx&)(((mx&)*this) / v); }

	static vx log(const vx& m);	

private:

	// Hide generic matrix metods for vectors
	using mx::zeros;
	using mx::ones;

	using mx::set;
	using mx::get;

	using mx::sum;
	using mx::cumsum;

};

// Inverse Value-Vector operators
vx operator+(double a, const vx& m);
vx operator-(double a, const vx& m);
vx operator*(double a, const vx& m);
vx operator/(double a, const vx& m);

