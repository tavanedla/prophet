#include "gtest/gtest.h"
#include "ip_ranges.h"

namespace prophet {

class IpRangesTest : public testing::Test {
    protected:
        IpRangesTest() : data_dir_("test_data_dir/") {
            std::filesystem::create_directory(data_dir_);
        }

        ~IpRangesTest() {
            std::filesystem::remove_all(data_dir_);
        }
    std::filesystem::path data_dir_;
};

TEST_F(IpRangesTest, Add) {
    IpRanges ip_ranges(data_dir_ / "test_data");
    ip_ranges.Add("100.200.0.0/16");    
    EXPECT_TRUE(ip_ranges.Contains("100.200.1.1"));
    EXPECT_FALSE(ip_ranges.Contains("1.1.1.1"));
}

TEST_F(IpRangesTest, Remove) {
    IpRanges ip_ranges(data_dir_ / "test_data");
    ip_ranges.Add("1.1.0.0/16");
    ip_ranges.Remove("1.1.0.0/16");
    EXPECT_FALSE(ip_ranges.Contains("1.1.2.3"));
}

TEST_F(IpRangesTest, RemoveOverlapping) {
    IpRanges ip_ranges(data_dir_ / "test_data");
    ip_ranges.Add("1.1.1.0/24");
    ip_ranges.Add("1.1.2.0/24");
    ip_ranges.Add("2.2.2.0/24");
    ASSERT_TRUE(ip_ranges.Remove("1.1.0.0/16"));
    EXPECT_FALSE(ip_ranges.Contains("1.1.1.1"));
    EXPECT_TRUE(ip_ranges.Contains("2.2.2.2"));
}

TEST_F(IpRangesTest, RemoveNonExistingFails) {
    IpRanges ip_ranges(data_dir_ / "test_data");
    ip_ranges.Add("1.1.0.0/16");
    EXPECT_FALSE(ip_ranges.Remove("1.1.1.0/24"));
}

}
