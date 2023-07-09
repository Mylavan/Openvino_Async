// Copyright (C) 2018-2023 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <memory>
#include <vector>

#include "ngraph/opsets/opset8.hpp"
#include "openvino/pass/pass.hpp"

namespace ov {
namespace pass {
/**
 * @brief The transformation replaces the provided pairs Parameter and Result with ngraph Memory layers
 * ReadValue and Assign
 * \ingroup ov_pass_cpp_api
 */
class OPENVINO_API MakeStateful : public ModelPass {
public:
    OPENVINO_RTTI("MakeStateful");

    using ParamResPairs =
        std::vector<std::pair<std::shared_ptr<ngraph::opset8::Parameter>, std::shared_ptr<ngraph::opset8::Result>>>;

    explicit MakeStateful(const ParamResPairs& pairs_to_replace) : m_param_res_pairs(pairs_to_replace) {}
    explicit MakeStateful(const std::map<std::string, std::string>& param_res_names)
        : m_param_res_names(param_res_names) {}
    bool run_on_model(const std::shared_ptr<ngraph::Function>& m) override;

private:
    ParamResPairs m_param_res_pairs;
    std::map<std::string, std::string> m_param_res_names;
};
}  // namespace pass
}  // namespace ov
