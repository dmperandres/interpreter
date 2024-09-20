#ifndef GAUSSIANS_ADJUSTMENT_2D
#define GAUSSIANS_ADJUSTMENT_2D

#include <vector>
#include <math.h>
#include <string>

#include <Eigen/Dense>

namespace _gaussians_adjustment_ns {

  struct _data_gaussian_adjustment {
    std::string Name;
    float Value=0;
    float Position=0;
    float Weight=0;
  };
}


class _gaussians_adjustment
{
public:
  _gaussians_adjustment(float Sigma1):Sigma(Sigma1){}

  void compute_weights(std::vector<_gaussians_adjustment_ns::_data_gaussian_adjustment> &Vec_data_gaussian_adjustment);

protected:
  float Sigma;
};


#endif
