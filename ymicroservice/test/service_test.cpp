#include <unistd.h>
#include <future>
#include <semaphore>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "gtest/gtest.h"
#include "startable.h"
#include "ymicroservice.h"

using ymicroservice::Capability;
using ymicroservice::Service;
using ymicroservice::Startable;

struct TestData {
  std::vector<std::string>                     beforeStartCalls;
  std::unordered_map<std::string, std::string> status;
  std::vector<std::string>                     shutdownCalls;
};

class TestCapability : public Capability {
 public:
  TestData&   testData;
  std::string key;

  TestCapability(TestData& testData, std::string key)
      : testData(testData), key(key) {
    testData.status.insert_or_assign(key, "constructed");
  }

  void beforeStart(const yutil::ROTypeMap& capabilities) override {
    testData.beforeStartCalls.push_back(key);
    testData.status.insert_or_assign(key, "initialized");
  }

  void shutdown() override { testData.shutdownCalls.push_back(key); }
};

class TestCapabilityOne : public TestCapability, public Startable {
 public:
  TestCapabilityOne(TestData& testData, std::string key)
      : TestCapability(testData, key) {}

  void start() override { testData.status.insert_or_assign(key, "started"); }

  void stop() override {}
};

class TestCapabilityTwo : public TestCapability {
 public:
  TestCapabilityTwo(TestData& testData, std::string key)
      : TestCapability(testData, key) {}
};

class TestCapabilityBlocking : public TestCapability, public Startable {
 public:
  std::binary_semaphore semaphore;

  TestCapabilityBlocking(TestData& testData, std::string key)
      : TestCapability(testData, key), semaphore{0} {}

  void start() override {
    testData.status.insert_or_assign(key, "started");
    semaphore.acquire();
    testData.status.insert_or_assign(key, "complete");
  }

  void stop() override {}
};

TEST(ServiceTest, start) {
  Service  service;
  TestData testData;
  auto     capabilityOne = new TestCapabilityOne(testData, "one");
  auto     capabilityTwo = new TestCapabilityTwo(testData, "two");

  service.addCapability(capabilityOne).addCapability(capabilityTwo);

  auto* gotCapabilityOne = service.getCapability<TestCapabilityOne>();
  auto* gotCapabilityTwo = service.getCapability<TestCapabilityTwo>();

  // expect getCapability returns the correct object
  EXPECT_EQ(capabilityOne, capabilityOne);
  EXPECT_EQ(capabilityTwo, capabilityTwo);
  EXPECT_EQ(capabilityOne->key, "one");
  EXPECT_EQ(capabilityTwo->key, "two");

  service.start();

  // expect the order of beforeStart calls
  EXPECT_EQ(testData.beforeStartCalls[0], "one");
  EXPECT_EQ(testData.beforeStartCalls[1], "two");

  // expect the order of shutdownCalls calls
  EXPECT_EQ(testData.shutdownCalls[0], "one");
  EXPECT_EQ(testData.shutdownCalls[1], "two");
}

TEST(ServiceTest, startBlocking) {
  Service  service;
  TestData testData;
  auto     capabilityOne  = new TestCapabilityOne(testData, "one");
  auto capabilityBlocking = new TestCapabilityBlocking(testData, "blocking");

  service.addCapability(capabilityOne).addCapability(capabilityBlocking);

  auto future = std::async(&Service::start, &service);

  usleep(100);

  EXPECT_EQ(testData.status["blocking"], "started");

  capabilityBlocking->semaphore.release();
  future.wait();

  EXPECT_EQ(testData.status["blocking"], "complete");
}
