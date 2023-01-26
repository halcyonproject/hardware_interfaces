/*
 * Copyright 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <aidl/android/hardware/tv/input/BnTvInput.h>
#include <utils/KeyedVector.h>

#include <map>
#include "TvInputDeviceInfoWrapper.h"
#include "TvStreamConfigWrapper.h"

using namespace android;
using namespace std;
using ::aidl::android::hardware::common::NativeHandle;

namespace aidl {
namespace android {
namespace hardware {
namespace tv {
namespace input {

class TvInput : public BnTvInput {
  public:
    TvInput();

    ::ndk::ScopedAStatus setCallback(const shared_ptr<ITvInputCallback>& in_callback) override;
    ::ndk::ScopedAStatus getStreamConfigurations(int32_t in_deviceId,
                                                 vector<TvStreamConfig>* _aidl_return) override;
    ::ndk::ScopedAStatus openStream(int32_t in_deviceId, int32_t in_streamId,
                                    NativeHandle* _aidl_return) override;
    ::ndk::ScopedAStatus closeStream(int32_t in_deviceId, int32_t in_streamId) override;

    void init();

  private:
    native_handle_t* createNativeHandle(int fd);

    shared_ptr<ITvInputCallback> mCallback;
    map<int32_t, shared_ptr<TvInputDeviceInfoWrapper>> mDeviceInfos;
    map<int32_t, map<int32_t, shared_ptr<TvStreamConfigWrapper>>> mStreamConfigs;
};

}  // namespace input
}  // namespace tv
}  // namespace hardware
}  // namespace android
}  // namespace aidl