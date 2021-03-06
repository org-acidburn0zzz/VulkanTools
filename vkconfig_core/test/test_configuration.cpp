/*
 * Copyright (c) 2020-2021 Valve Corporation
 * Copyright (c) 2020-2021 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Authors:
 * - Christophe Riccio <christophe@lunarg.com>
 */

#include "../configuration.h"
#include "../util.h"

#include <array>
#include <string>

#include <gtest/gtest.h>

static bool operator==(const Configuration& a, const Configuration& b) {
    if (a.key != b.key)
        return false;
    else if (a.platform_flags != b.platform_flags)
        return false;
    else if (a.description != b.description)
        return false;
    else if (a.setting_tree_state != b.setting_tree_state)
        return false;
    else if (a.parameters != b.parameters)
        return false;
    return true;
}

static bool operator!=(const Configuration& a, const Configuration& b) { return !(a == b); }

static bool operator==(const Parameter& a, const Parameter& b) {
    if (a.key != b.key) return false;

    if (a.state != b.state) return false;

    if (a.settings.Size() != b.settings.Size()) return false;

    for (std::size_t i = 0, n = a.settings.Size(); i < n; ++i) {
        if (a.settings[i] != b.settings[i]) return false;
    }

    return true;
}

static bool operator!=(const std::vector<Parameter>& a, const std::vector<Parameter>& b) { return !(a == b); }

TEST(test_configuration, ctor) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - API dump.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_TRUE(!configuration_loaded.parameters.empty());

    Configuration configuration_copy(configuration_loaded);

    EXPECT_EQ(configuration_loaded, configuration_copy);
}

TEST(test_configuration, load_and_save_v2_0_1_api_dump) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - API dump.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter != nullptr);

    configuration_loaded.key = "Api Dump";
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_1_api_dump.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_1_api_dump.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_1_frame_capture) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Frame Capture.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter != nullptr);

    configuration_loaded.key = "Frame Capture";
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_1_frame_capture.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_1_frame_capture.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_frame_capture) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Frame Capture.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Frame Capture - Range (F5 to start and to stop)", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_frame_capture.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_frame_capture.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_1_gpu_assisted) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - GPU-Assisted.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    configuration_loaded.key = "GPU-Assisted";
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_1_gpu_assisted.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_1_gpu_assisted.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_gpu_assisted) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - GPU-Assisted.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Validation - GPU-Assisted", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_gpu_assisted.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_gpu_assisted.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_1_shader_printf) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Shader Printf.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    configuration_loaded.key = "shader-printf";
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_1_shader_printf.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_1_shader_printf.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_debug_printf) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Debug Printf.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Validation - Debug Printf", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_shader_printf.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_shader_printf.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_1_best_practices) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Best Practices.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    configuration_loaded.key = "best-practices";
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_1_best_practices.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_1_best_practices.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_best_practices) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Best Practices.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Validation - Best Practices", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_best_practices.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_best_practices.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_override_all_layers) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Override all layers.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(6, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter_validation = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter_validation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_validation->state);

    auto parameter_api_dump = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter_api_dump != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_api_dump->state);

    auto parameter_device_simulation = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_device_simulation");
    EXPECT_TRUE(parameter_device_simulation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_device_simulation->state);

    auto parameter_gfxreconstruct = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter_gfxreconstruct != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_gfxreconstruct->state);

    auto parameter_monitor = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_monitor");
    EXPECT_TRUE(parameter_monitor != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_monitor->state);

    auto parameter_screenshot = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_screenshot");
    EXPECT_TRUE(parameter_screenshot != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_screenshot->state);

    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_override_all_layers.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_override_all_layers.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_0_2_exclude_all_layers) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Exclude all layers.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(6, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter_validation = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter_validation != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_validation->state);

    auto parameter_api_dump = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter_api_dump != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_api_dump->state);

    auto parameter_device_simulation = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_device_simulation");
    EXPECT_TRUE(parameter_device_simulation != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_device_simulation->state);

    auto parameter_gfxreconstruct = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter_gfxreconstruct != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_gfxreconstruct->state);

    auto parameter_monitor = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_monitor");
    EXPECT_TRUE(parameter_monitor != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_monitor->state);

    auto parameter_screenshot = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_screenshot");
    EXPECT_TRUE(parameter_screenshot != nullptr);
    EXPECT_EQ(LAYER_STATE_EXCLUDED, parameter_screenshot->state);

    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_2_exclude_all_layers.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_2_exclude_all_layers.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_standard) {
    Configuration configuration;
    const bool load = configuration.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Standard.json");
    EXPECT_TRUE(load);
    EXPECT_TRUE(!configuration.parameters.empty());

    EXPECT_STREQ("Validation - Standard", configuration.key.c_str());
    EXPECT_EQ(1, configuration.parameters.size());
    EXPECT_TRUE(!configuration.description.empty());
}

TEST(test_configuration, compare_version_standard) {
    Configuration configuration_2_0_1;
    const bool load_2_0_1 = configuration_2_0_1.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Standard.json");
    EXPECT_TRUE(load_2_0_1);
    EXPECT_TRUE(!configuration_2_0_1.parameters.empty());
    EXPECT_STREQ("Configuration 2.0.1 - Standard", configuration_2_0_1.key.c_str());

    Configuration configuration_2_0_2;
    const bool load_2_0_2 = configuration_2_0_2.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Standard.json");
    EXPECT_TRUE(load_2_0_2);
    EXPECT_TRUE(!configuration_2_0_2.parameters.empty());
    EXPECT_STREQ("Validation - Standard", configuration_2_0_2.key.c_str());

    EXPECT_TRUE(configuration_2_0_1.parameters == configuration_2_0_2.parameters);
}

TEST(test_configuration, compare_version_debug_printf) {
    Configuration configuration_2_0_1;
    const bool load_2_0_1 = configuration_2_0_1.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Shader Printf.json");
    EXPECT_TRUE(load_2_0_1);
    EXPECT_TRUE(!configuration_2_0_1.parameters.empty());
    EXPECT_STREQ("Configuration 2.0.1 - Shader Printf", configuration_2_0_1.key.c_str());

    Configuration configuration_2_0_2;
    const bool load_2_0_2 = configuration_2_0_2.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Debug Printf.json");
    EXPECT_TRUE(load_2_0_2);
    EXPECT_TRUE(!configuration_2_0_2.parameters.empty());
    EXPECT_STREQ("Validation - Debug Printf", configuration_2_0_2.key.c_str());

    EXPECT_TRUE(configuration_2_0_1.parameters == configuration_2_0_2.parameters);
}

TEST(test_configuration, compare_settings) {
    Configuration configuration_standard;
    const bool load_standard = configuration_standard.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Standard.json");
    EXPECT_TRUE(load_standard);
    EXPECT_TRUE(!configuration_standard.parameters.empty());
    EXPECT_STREQ("Validation - Standard", configuration_standard.key.c_str());

    Configuration configuration_best_practices;
    const bool load_best_practices =
        configuration_best_practices.Load(std::vector<Layer>(), ":/Configuration 2.0.2 - Best Practices.json");
    EXPECT_TRUE(load_best_practices);
    EXPECT_TRUE(!configuration_best_practices.parameters.empty());
    EXPECT_STREQ("Validation - Best Practices", configuration_best_practices.key.c_str());

    // Settings are reset to default
    EXPECT_TRUE(configuration_standard.parameters == configuration_best_practices.parameters);
}

TEST(test_configuration, find_layer_parameter) {
    Configuration configuration_2_0_1;
    const bool load_2_0_1 = configuration_2_0_1.Load(std::vector<Layer>(), ":/Configuration 2.0.1 - Standard.json");
    EXPECT_TRUE(load_2_0_1);

    auto parameter = FindByKey(configuration_2_0_1.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ(parameter->key.c_str(), "VK_LAYER_KHRONOS_validation");
}

TEST(test_configuration, load_and_save_v2_0_3_best_practices) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.0.3 - Best Practices.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Validation - Best Practices", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_0_3_best_practices.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_0_3_best_practices.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_1_0_Frame_Capture) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.1.0 - Frame Capture.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(1, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter != nullptr);

    EXPECT_STREQ("Frame Capture", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_1_0_frame_capture.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_1_0_frame_capture.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_1_0_Portability) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.1.0 - Portability.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(6, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter_validation = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter_validation != nullptr);

    auto parameter_simulation = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_device_simulation");
    EXPECT_TRUE(parameter_simulation != nullptr);

    auto parameter_api_dump = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter_api_dump != nullptr);

    auto parameter_monitor = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_monitor");
    EXPECT_TRUE(parameter_monitor != nullptr);

    EXPECT_STREQ("Portability", configuration_loaded.key.c_str());
    configuration_loaded.Save(std::vector<Layer>(), "test_v2_1_0_portability.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_1_0_portability.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_1_0_override_all_layers) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.1.0 - Override all layers.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(6, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter_validation = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter_validation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_validation->state);

    auto parameter_api_dump = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter_api_dump != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_api_dump->state);

    auto parameter_device_simulation = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_device_simulation");
    EXPECT_TRUE(parameter_device_simulation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_device_simulation->state);

    auto parameter_gfxreconstruct = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter_gfxreconstruct != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_gfxreconstruct->state);

    auto parameter_monitor = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_monitor");
    EXPECT_TRUE(parameter_monitor != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_monitor->state);

    auto parameter_screenshot = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_screenshot");
    EXPECT_TRUE(parameter_screenshot != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_screenshot->state);

    configuration_loaded.Save(std::vector<Layer>(), "test_v2_1_0_override_all_layers.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_1_0_override_all_layers.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

TEST(test_configuration, load_and_save_v2_2_0_override_all_layers) {
    Configuration configuration_loaded;
    const bool load_loaded = configuration_loaded.Load(std::vector<Layer>(), ":/Configuration 2.2.0 - Override all layers.json");
    EXPECT_TRUE(load_loaded);
    EXPECT_EQ(6, configuration_loaded.parameters.size());
    EXPECT_TRUE(!configuration_loaded.description.empty());

    auto parameter_validation = FindByKey(configuration_loaded.parameters, "VK_LAYER_KHRONOS_validation");
    EXPECT_TRUE(parameter_validation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_validation->state);

    auto parameter_api_dump = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_api_dump");
    EXPECT_TRUE(parameter_api_dump != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_api_dump->state);

    auto parameter_device_simulation = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_device_simulation");
    EXPECT_TRUE(parameter_device_simulation != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_device_simulation->state);

    auto parameter_gfxreconstruct = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_gfxreconstruct");
    EXPECT_TRUE(parameter_gfxreconstruct != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_gfxreconstruct->state);

    auto parameter_monitor = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_monitor");
    EXPECT_TRUE(parameter_monitor != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_monitor->state);

    auto parameter_screenshot = FindByKey(configuration_loaded.parameters, "VK_LAYER_LUNARG_screenshot");
    EXPECT_TRUE(parameter_screenshot != nullptr);
    EXPECT_EQ(LAYER_STATE_OVERRIDDEN, parameter_screenshot->state);

    configuration_loaded.Save(std::vector<Layer>(), "test_v2_2_0_override_all_layers.json");

    Configuration configuration_saved;
    configuration_saved.Load(std::vector<Layer>(), "test_v2_2_0_override_all_layers.json");

    EXPECT_EQ(configuration_loaded, configuration_saved);
}

static std::vector<Configuration> GenerateConfigurations() {
    std::vector<Configuration> configurations;

    {
        Configuration configuration;
        configuration.key = "Duplicate Configuration";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Duplicate Configuration (2)";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "My Configuration";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Old Configuration (3)";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Old Configuration (1)";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Tag Configuration (tag) (3)";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Tag Configuration (tag)";
        configurations.push_back(configuration);
    }

    {
        Configuration configuration;
        configuration.key = "Tag Configuration Bla";
        configurations.push_back(configuration);
    }

    return configurations;
}

TEST(test_configuration, make_first_duplicate_name) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "My Configuration");

    EXPECT_STREQ("My Configuration (2)", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_additional_duplicate_name) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "Duplicate Configuration");

    EXPECT_STREQ("Duplicate Configuration (3)", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_extra_duplicate_name) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "Old Configuration (2)");

    EXPECT_STREQ("Old Configuration (4)", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_new_name) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "New Configuration");

    EXPECT_STREQ("New Configuration", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_new_name_tagged) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "New Configuration (tag)");

    EXPECT_STREQ("New Configuration (tag)", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_duplicate_tagged_name) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "Tag Configuration Bla (tag)");

    EXPECT_STREQ("Tag Configuration Bla (tag)", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}

TEST(test_configuration, make_duplicate_tagged_name_mix) {
    const std::vector<Configuration>& configurations = GenerateConfigurations();

    const std::string& new_name = MakeConfigurationName(configurations, "Tag Configuration (tag) Bla");

    EXPECT_STREQ("Tag Configuration (tag) Bla", new_name.c_str());
    EXPECT_TRUE(!new_name.empty());
}
