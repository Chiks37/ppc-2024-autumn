// Copyright 2024 Tarakanov Denis
#pragma once

#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <memory>
#include <numeric>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace tarakanov_d_integration_the_trapezoid_method_mpi {

class integration_the_trapezoid_method_seq : public ppc::core::Task {
 public:
  explicit integration_the_trapezoid_method_seq(std::shared_ptr<ppc::core::TaskData> taskData_)
      : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  double a{}, b{}, h{}, res{};

  static double f(double x) { return x * x; };
};

class integration_the_trapezoid_method_par : public ppc::core::Task {
 public:
  explicit integration_the_trapezoid_method_par(std::shared_ptr<ppc::core::TaskData> taskData_)
      : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;
  double res{};

  double a{}, b{}, h{}, local_a{};
  uint32_t partsCount{}, localPartsCount{};

  static double f(double x) { return x * x; };

  boost::mpi::communicator world;
};

}  // namespace tarakanov_d_integration_the_trapezoid_method_mpi