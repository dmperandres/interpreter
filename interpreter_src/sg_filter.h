#ifndef SG_FILTER_H
#define SG_FILTER_H

#include <vector>
#include <math.h>
#include <iostream>

// default convergence
static const double TINY_FLOAT = 1.0e-300;

/*! matrix class.
 *
 * This is a matrix class derived from a vector of std::vector<double>s.  Note that
 * the matrix elements indexed [row][column] with indices starting at 0 (c
 * style). Also note that because of its design looping through rows should
 * be faster than looping through columns.
 *
 * \brief two dimensional floating point array
 */
class mat_sg : public std::vector<std::vector<double>> {
private:
    //! disable the default constructor
    explicit mat_sg() {};
    //! disable assignment operator until it is implemented.
    mat_sg &operator =(const mat_sg &) { return *this; };
public:
    //! constructor with sizes
    mat_sg(const unsigned int rows, const unsigned int cols, const double def=0.0);
    //! copy constructor for matrix
    mat_sg(const mat_sg &m);
    //! copy constructor for vector
    mat_sg(const std::vector<double> &v);

    //! use default destructor
    // ~mat_sg() {};

    //! get size
    unsigned int nr_rows(void) const { return size(); };
    //! get size
    unsigned int nr_cols(void) const { return front().size(); };
};


// savitzky golay smoothing.

class _sg_filter
{
public:
  static std::vector<double> coeff(const std::vector<double> &b, const unsigned int deg);
  static std::vector<double> lsqr_fprime(const std::vector<double> &b, const int deg);

  std::vector<double> smooth(const std::vector<double> &Vec_input, const int Window, const int Degree);
  std::vector<double> derivative(const std::vector<double> &Vec_input, const int Window, const int Degree, const double h=1.0);

};

#endif
