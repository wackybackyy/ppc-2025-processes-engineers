#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

#include "balchunayte_z_shell_batcher/common/include/common.hpp"
#include "balchunayte_z_shell_batcher/mpi/include/ops_mpi.hpp"
#include "balchunayte_z_shell_batcher/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace balchunayte_z_shell_batcher {

class ShellBatcherRunPerfTestProcesses : public ppc::util::BaseRunPerfTests<InType, OutType> {
 public:
  void SetUp() override {
    constexpr std::size_t kSize = 200000;
    input_data_.resize(kSize);

    int x = 17;
    for (std::size_t i = 0; i < kSize; ++i) {
      x = (x * 1103515245 + 12345);
      input_data_[i] = x;
    }

    expected_ = input_data_;
    std::sort(expected_.begin(), expected_.end());
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data == expected_;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_{};
  OutType expected_{};
};

TEST_P(ShellBatcherRunPerfTestProcesses, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, BalchunayteZShellBatcherMPI, BalchunayteZShellBatcherSEQ>(
        PPC_SETTINGS_balchunayte_z_shell_batcher);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

const auto kPerfTestName = ShellBatcherRunPerfTestProcesses::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, ShellBatcherRunPerfTestProcesses, kGtestValues, kPerfTestName);

}  // namespace balchunayte_z_shell_batcher
