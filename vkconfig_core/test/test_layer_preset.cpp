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

#include "../layer_preset.h"
#include "../util.h"

#include <gtest/gtest.h>

TEST(test_layer_preset, get_preset) {
    LayerPreset layer_preset_a;
    layer_preset_a.label = "1";

    LayerPreset layer_preset_b;
    layer_preset_b.label = "2";

    std::vector<LayerPreset> presets;
    presets.push_back(layer_preset_a);
    presets.push_back(layer_preset_b);

    EXPECT_STREQ("1", GetPreset(presets, "1")->label.c_str());
    EXPECT_EQ(nullptr, GetPreset(presets, "3"));
}

TEST(test_layer_preset, has_preset) {
    SettingDataSet preset_settings;
    SettingDataSet layer_settings;

    EXPECT_EQ(false, HasPreset(layer_settings, preset_settings));

    static_cast<SettingDataString&>(preset_settings.Create("KeyA", SETTING_STRING)).value = "ValueA";
    EXPECT_EQ(false, HasPreset(layer_settings, preset_settings));

    static_cast<SettingDataString&>(layer_settings.Create("KeyA", SETTING_STRING)).value = "ValueA";
    EXPECT_EQ(true, HasPreset(layer_settings, preset_settings));

    static_cast<SettingDataString&>(layer_settings.Create("KeyB", SETTING_STRING)).value = "ValueB";
    EXPECT_EQ(true, HasPreset(layer_settings, preset_settings));

    static_cast<SettingDataString&>(preset_settings.Create("KeyC", SETTING_STRING)).value = "ValueC";
    EXPECT_EQ(false, HasPreset(layer_settings, preset_settings));
}
