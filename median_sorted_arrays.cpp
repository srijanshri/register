/*
 * Median of Two Sorted Arrays
 *
 * Time Complexity : O(log(min(m, n)))  — satisfies O(log(m+n))
 * Space Complexity: O(1)
 *
 * Algorithm:
 *   Binary search on the smaller array to find a partition index i.
 *   The corresponding partition in the larger array is j = half - i,
 *   where half = (m + n + 1) / 2.
 *
 *   A partition is valid when:
 *       maxLeft1 <= minRight2  AND  maxLeft2 <= minRight1
 *
 *   Median:
 *     - Odd  total length : max(maxLeft1, maxLeft2)
 *     - Even total length : (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <cmath>

double findMedianSortedArrays(const std::vector<int>& nums1,
                               const std::vector<int>& nums2)
{
    // Always binary-search on the smaller array
    const std::vector<int>& A = (nums1.size() <= nums2.size()) ? nums1 : nums2;
    const std::vector<int>& B = (nums1.size() <= nums2.size()) ? nums2 : nums1;

    int m = static_cast<int>(A.size());
    int n = static_cast<int>(B.size());
    int half = (m + n + 1) / 2;

    int lo = 0, hi = m;

    while (lo <= hi) {
        int i = (lo + hi) / 2;   // partition in A
        int j = half - i;         // partition in B

        int maxLeft1  = (i > 0) ? A[i - 1] : INT_MIN;
        int minRight1 = (i < m) ? A[i]     : INT_MAX;
        int maxLeft2  = (j > 0) ? B[j - 1] : INT_MIN;
        int minRight2 = (j < n) ? B[j]     : INT_MAX;

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // Valid partition found
            if ((m + n) % 2 == 1) {
                return static_cast<double>(std::max(maxLeft1, maxLeft2));
            } else {
                return (std::max(maxLeft1, maxLeft2) +
                        std::min(minRight1, minRight2)) / 2.0;
            }
        } else if (maxLeft1 > minRight2) {
            hi = i - 1;   // move partition left in A
        } else {
            lo = i + 1;   // move partition right in A
        }
    }

    throw std::invalid_argument("Input arrays are not sorted.");
}

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

struct TestCase {
    std::vector<int> nums1;
    std::vector<int> nums2;
    double expected;
};

int main()
{
    std::vector<TestCase> tests = {
        {{1, 3},          {2},             2.0},
        {{1, 2},          {3, 4},          2.5},
        {{0, 0},          {0, 0},          0.0},
        {{},              {1},             1.0},
        {{2},             {},              2.0},
        {{1, 3, 5, 7},    {2, 4, 6, 8},    4.5},
        {{1, 2},          {1, 2, 3},       2.0},
        {{-5, -3, -1},    {-4, -2, 0},    -2.5},
        {{1, 3},          {2, 4, 5, 6},    3.5},
        {{100000},        {100001},        100000.5},
    };

    bool allPassed = true;

    for (int i = 0; i < static_cast<int>(tests.size()); ++i) {
        const auto& t = tests[i];
        double result = findMedianSortedArrays(t.nums1, t.nums2);
        bool pass = std::fabs(result - t.expected) < 1e-9;
        if (!pass) allPassed = false;

        std::cout << "Test " << (i + 1) << ": " << (pass ? "PASS" : "FAIL")
                  << "  →  got " << result
                  << ", expected " << t.expected << "\n";
    }

    std::cout << "\n" << (allPassed ? "All tests passed." : "Some tests FAILED.") << "\n";
    return allPassed ? 0 : 1;
}
