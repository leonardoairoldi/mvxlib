#pragma once


#include <iostream>
#include <tuple>
#include <vector>
#include <list>

#define ALL -1

class vx;

/// <summary>
/// Standart type of mxvlib to indicate direction of selection or calculation
/// </summary>
typedef enum
{
	ROW,
	COL
} Direction_t;

class mx
{
private:

protected:
	double* data;
	int r, c;

public:
	mx() noexcept;

	/// <summary>
	/// Creates a matrix object
	/// </summary>
	/// <param name="r">Number of rows</param>
	/// <param name="c">Number of columns</param>
	mx(int r, int c);

	/// Copy constructor
	/// <summary>
	/// Creates a copy of the object mx
	/// </summary>
	/// <param name="m">Matrix to copy</param>
	mx(const mx& m);

	/// List inizializer
	/// <summary>
	/// Initializes the matrix with the values in the list, with the specified dimensions.
	/// The values are stored in row-major order (row after row)
	/// </summary>
	/// <example>
	/// Create a 2x2 matrix initializing [1, 2; 2, 4]
	/// <code>
	/// mx m(2, 2, {1, 2, 3, 4});
	/// </code>
	/// </example>
	/// <param name="r">Number of rows</param>
	/// <param name="c">Number of columns</param>
	/// <param name="list">Initializer list</param>
	mx(int r, int c, std::initializer_list<double> list);


	/// List-List initializer
	/// <summary>
	/// Initialize the matrix with the corrispong values in the list.
	/// The dimensions are inferred from the list.
	/// 
	/// </summary>
	/// <param name="list">A list of row values</param>
	mx(std::initializer_list<std::initializer_list<double>> list);

	mx(std::vector<std::vector<double>> list);

	/// Destructor
	/// <summary>
	/// Deallocates the object
	/// </summary>
	~mx();
	
	/// <summary>
	/// Set the element in the matrix at the specified position
	/// </summary>
	/// <param name="i">Row index</param>
	/// <param name="j">Column index</param>
	/// <param name="val">Value to set</param>
	void set(int i, int j, double val);

	/// <summary>
	/// Get the element in the matrix at the specified position
	/// </summary>
	/// <param name="i">Row index</param>
	/// <param name="j">Column index</param>
	/// <returns>Value at the specified position</returns>
	double get(int i, int j) const;

	/// <summary>
	/// Prints the matrix to the standard output
	/// </summary>
	void print();

	/// <summary>
	/// Returns a string representation of the matrix
	/// </summary>
	/// <returns>Matrix formatted string</returns>
	std::stringstream to_string();


	/// <summary>
	/// Copy-assignment operator. 
	/// Safe on self-assignment, and to return the lhs by reference
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	mx& operator=(const mx& m);

	/// <summary>
	/// Move-assignment operator
	/// Safe on self-assignment, and to return the lhs by reference
	/// The move result uses the same data pointer of the moved object
	/// Be careful if using the moved object after the move operation!
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	mx& operator=(mx&& m) noexcept;

	/// <summary>
	/// Get the value reference at the specified position.
	/// Useful for beatiful assignment operations.
	/// </summary>
	/// <example>
	/// Assign a value to the element at position (1, 2)
	/// <code>
	/// m(1, 2) = 10;
	/// </code>
	/// </example>
	/// <param name="i">Row index</param>
	/// <param name="j">Columnd index</param>
	/// <returns>Element (i,j) reference</returns>
	double& operator()(int i, int j);

	vx operator()(int i, Direction_t dir);

	mx transpose() const;

	/// <summary>
	/// Returns the maximum value in the matrix
	/// </summary>
	/// <returns>The maximum element value</returns>
	double maximum() const noexcept;
	/// <summary>
	/// Returns the minimum value in the matrix
	/// </summary>
	/// <returns>The minimum element value</returns>
	double minimum() const noexcept;


	/// <summary>
	/// Returns a matrix with elements equals 
	///    max(element, n)
	/// </summary>
	/// <param name="n">Saturator value</param>
	/// <returns>A new matrix, result of operation</returns>
	mx maximum(double n) const noexcept;
	/// <summary>
	/// Returns a matrix with elements equals 
	///    min(element, n)
	/// </summary>
	/// <param name="n">Saturator value</param>
	/// <returns>A new matrix, result of operation</returns>
	mx minimum(double n) const noexcept;


	mx cumsum(Direction_t direction) const;
	mx sum(Direction_t direction) const;

	static mx zeros(int r, int c);
	static mx ones(int r, int c);

	double sum() const noexcept;


	void print_size() const;
	int size(Direction_t dir) const;
	void to_csv(std::string filename) const;
	// Do not use to_csv and then append_to_csv, as a matrix separator is needed
	void append_to_csv(std::string filename, std::string matrix_separator) const;
	
	static mx from_csv(std::string filename);
	static std::list<mx> from_csv(std::string filename, std::string multiple_matrix_separator);


	friend std::ostream& operator<<(std::ostream& os, mx& m);
	friend std::istream& operator>>(std::istream& is, mx& m);

	// Matrix-Matrix operators
	// Both inputs are consts as they are not modified
	mx operator+(const mx& b) const;
	mx operator-(const mx& b) const;
	mx operator*(const mx& b) const;
	mx operator/(const mx& b) const;

	// Matrix-Value operators
	mx operator+(double a) const;
	mx operator-(double a) const;
	mx operator*(double a) const;
	mx operator/(double a) const;


	// Value compare operators
	bool operator==(const mx& b) const;
	bool operator!=(const mx& b) const;

	// Matrix-Array broadcast operators
	mx operator+(const vx& a) const;
	mx operator-(const vx& a) const;
	mx operator*(const vx& a) const;
	mx operator/(const vx& a) const;

	static mx log(const mx& m);

};

// Inverse Value-Matrix operators
mx operator+(double a, const mx& m);
mx operator-(double a, const mx& m);
mx operator*(double a, const mx& m);
mx operator/(double a, const mx& m);
