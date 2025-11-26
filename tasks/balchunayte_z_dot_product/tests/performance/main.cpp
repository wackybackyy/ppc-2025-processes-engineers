#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "balchunayte_z_dot_product/common/include/common.hpp"
#include "balchunayte_z_dot_product/mpi/include/ops_mpi.hpp"
#include "balchunayte_z_dot_product/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace balchunayte_z_dot_product {

class DotProductRunPerfTestProcesses : public ppc::util::BaseRunPerfTests<InType, OutType> {
 public:
  void SetUp() override {
    constexpr int kSize = 100000;

    input_data_.a.resize(kSize);
    input_data_.b.resize(kSize);

    for (int i = 0; i < kSize; ++i) {
      input_data_.a[i] = static_cast<double>(i + 1);
      input_data_.b[i] = static_cast<double>(2 * (i + 1));
    }

    expected_ = 0.0;
    for (int i = 0; i < kSize; ++i) {
      expected_ += input_data_.a[i] * input_data_.b[i];
    }
  }

  bool CheckTestOutputData(OutType &output_data) override {
    const double eps = 1e-6;
    return std::fabs(output_data - expected_) < eps;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_{};
  OutType expected_{0.0};
};

TEST_P(DotProductRunPerfTestProcesses, RunPerfModes) {
  ExecuteTest(GetParam());
}

// MPI + SEQ задачи для всех режимов запуска
const auto kAllPerfTasks = ppc::util::MakeAllPerfTasks<InType, BalchunayteZDotProductMPI, BalchunayteZDotProductSEQ>(
    PPC_SETTINGS_balchunayte_z_dot_product);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);
const auto kPerfTestName = DotProductRunPerfTestProcesses::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, DotProductRunPerfTestProcesses, kGtestValues, kPerfTestName);

}  // namespace balchunayte_z_dot_product
