#pragma once

#include "balchunayte_z_dot_product/common/include/common.hpp"
#include "task/include/task.hpp"

namespace balchunayte_z_dot_product {

class BalchunayteZDotProductSEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }

  explicit BalchunayteZDotProductSEQ(const InType &in);

 private:
  bool ValidationImpl() override;      // NOLINT(readability-convert-member-functions-to-static)
  bool PreProcessingImpl() override;   // NOLINT(readability-convert-member-functions-to-static)
  bool RunImpl() override;             // NOLINT(readability-convert-member-functions-to-static)
  bool PostProcessingImpl() override;  // NOLINT(readability-convert-member-functions-to-static)
};

}  // namespace balchunayte_z_dot_product
