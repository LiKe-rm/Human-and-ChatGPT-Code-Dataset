#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "serial_frame_router.h"

using namespace testing;

// Mock class for SerialPort
class MockSerialPort : public SerialPort {
public:
    MOCK_METHOD(void, write, (const std::vector<uint8_t>& data), (override));
    MOCK_METHOD(std::vector<uint8_t>, read, (), (override));
};

// Test fixture for SerialFrameRouter
class SerialFrameRouterTest : public Test {
protected:
    void SetUp() override {
        router = std::make_unique<SerialFrameRouter>(upLink.get(), downLink.get());
    }

    std::unique_ptr<SerialFrameRouter> router;
    NiceMock<MockSerialPort> upLink;
    NiceMock<MockSerialPort> downLink;
};

TEST_F(SerialFrameRouterTest, BroadcastFrame) {
    std::vector<uint8_t> frame = {0xFF, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(1);
    EXPECT_CALL(downLink, write(frame)).Times(1);

    router->routeFrame(frame);
}

TEST_F(SerialFrameRouterTest, UnicastFrame) {
    std::vector<uint8_t> frame = {0x02, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(0);
    EXPECT_CALL(downLink, write(frame)).Times(1);

    router->routeFrame(frame);
}

TEST_F(SerialFrameRouterTest, FirstPortToHost) {
    std::vector<uint8_t> frame = {0x01, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(0);
    EXPECT_CALL(downLink, write(frame)).Times(1);

    router->routeFrameFromFirstPort(frame);
}

TEST_F(SerialFrameRouterTest, SecondPortToHostAndDestination) {
    std::vector<uint8_t> frame = {0x02, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(1);
    EXPECT_CALL(downLink, write(frame)).Times(1);

    router->routeFrameFromSecondPort(frame);
}

TEST_F(SerialFrameRouterTest, HostToRouter) {
    std::vector<uint8_t> frame = {0x00, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(0);
    EXPECT_CALL(downLink, write(frame)).Times(0);

    router->routeFrame(frame);
}

TEST_F(SerialFrameRouterTest, RouterToRouter) {
    std::vector<uint8_t> frame = {0x03, 0x01, 0x02, 0x03};

    EXPECT_CALL(upLink, write(frame)).Times(0);
    EXPECT_CALL(downLink, write(frame)).Times(0);

    router->routeFrame(frame);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
