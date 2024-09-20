#include "gaussians_adjustment.h"

//HEA
// This is the important part. There is a Gaussian function centered in each X position, as the extension is infinite, each
// function contributes to all the other ones. But we want that the total contribution of all the Gaussians functions in each point
// must match the measure value. Than implies that the weight of each Gaussian function must be compute to comply with all the conditions.
// That produces an equation system that must be resolved. In the previous version I used an old code. No I have implemented it using
// Eigen library.
// so the A matrix must be of 16x16 and we have 16 input intensities.
// If we have 4 positions then the systems is this:
// A=
// | GAUSSIAN(1-1) GAUSSIAN(1-2) GAUSSIAN(1-3) GAUSSIAN(1-4) | | W1 |  | I1 |
// | GAUSSIAN(2-1) GAUSSIAN(2-2) GAUSSIAN(2-3) GAUSSIAN(2-4) | | W2 |  | I2 |
// | GAUSSIAN(3-1) GAUSSIAN(3-2) GAUSSIAN(3-3) GAUSSIAN(3-4) |x| W3 |= | I3 |
// | GAUSSIAN(4-1) GAUSSIAN(4-2) GAUSSIAN(4-3) GAUSSIAN(4-4) | | W4 |  | I4 |
//
// For the fisrt row we use the value of the first X coordinate,for the second the second value and so on

void _gaussians_adjustment::compute_weights(std::vector<_gaussians_adjustment_ns::_data_gaussian_adjustment>& Vec_data_gaussian_adjustment)
{
  Eigen::MatrixXf A(Vec_data_gaussian_adjustment.size(),Vec_data_gaussian_adjustment.size());
  Eigen::VectorXf b(Vec_data_gaussian_adjustment.size());
  std::vector<float> Vec_weights(Vec_data_gaussian_adjustment.size(),0.0f);

  for (unsigned int Row=0;Row<Vec_data_gaussian_adjustment.size();Row++){
    for (unsigned int Col=0;Col<Vec_data_gaussian_adjustment.size();Col++){
      A(Row,Col)=expf(-0.5*pow((Vec_data_gaussian_adjustment[Row].Position-Vec_data_gaussian_adjustment[Col].Position)/Sigma,2));
    }
  }

  for (unsigned int Row=0;Row<Vec_data_gaussian_adjustment.size();Row++) b(Row)=Vec_data_gaussian_adjustment[Row].Value;

  // resolve the system
  Eigen::VectorXf x_vec = A.colPivHouseholderQr().solve(b);

  for (unsigned int Row=0;Row<Vec_data_gaussian_adjustment.size();Row++) Vec_data_gaussian_adjustment[Row].Weight=x_vec[Row];

//  return Vec_weights;
}
