// A2dpSinkServiceTest.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "A2dpSinkService.h"
#include "BluetoothAdapter.h"
#include "BluetoothDevice.h"
#include "BluetoothProfile.h"
#include "DatabaseManager.h"

class A2dpSinkServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize objects and services
        mAdapter = std::make_shared<BluetoothAdapter>();
        mDatabaseManager = std::make_shared<DatabaseManager>();
        mService = std::make_shared<A2dpSinkService>(mAdapter, mDatabaseManager);
    }

    void TearDown() override {
        mService.reset();
        mAdapter.reset();
        mDatabaseManager.reset();
    }

    std::shared_ptr<BluetoothAdapter> mAdapter;
    std::shared_ptr<A2dpSinkService> mService;
    std::shared_ptr<DatabaseManager> mDatabaseManager;
};

TEST_F(A2dpSinkServiceTest, TestInitialize) {
    ASSERT_NE(mService, nullptr);
}

TEST_F(A2dpSinkServiceTest, TestConnect) {
    std::string address = "11:11:11:11:11:11";
    auto device = mAdapter->getRemoteDevice(address);
    mDatabaseManager->setProfileConnectionPolicy(device, BluetoothProfile::CONNECTION_POLICY_ALLOWED);

    ASSERT_TRUE(mService->connect(device));
}

TEST_F(A2dpSinkServiceTest, TestConnectPriorityOffDevice) {
    std::string address = "11:11:11:11:11:11";
    auto device = mAdapter->getRemoteDevice(address);
    mDatabaseManager->setProfileConnectionPolicy(device, BluetoothProfile::CONNECTION_POLICY_FORBIDDEN);

    ASSERT_FALSE(mService->connect(device));
}
