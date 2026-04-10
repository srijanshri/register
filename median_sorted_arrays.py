"""
Median of Two Sorted Arrays
Time Complexity: O(log(min(m, n)))  — satisfies O(log(m+n))
Space Complexity: O(1)

Algorithm: Binary search on the smaller array to find a partition point i.
For a partition i in nums1 (0..m), the corresponding partition in nums2 is
j = half_len - i, where half_len = (m + n + 1) // 2.

The partition is valid when:
    max(nums1_left) <= min(nums2_right)  AND
    max(nums2_left) <= min(nums1_right)

Once the valid partition is found, the median is:
  - Odd total length:  max(left halves)
  - Even total length: (max(left halves) + min(right halves)) / 2
"""

import math


def find_median_sorted_arrays(nums1: list[int], nums2: list[int]) -> float:
    # Ensure nums1 is the smaller array to minimise binary search range
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1

    m, n = len(nums1), len(nums2)
    half_len = (m + n + 1) // 2

    lo, hi = 0, m

    while lo <= hi:
        i = (lo + hi) // 2   # partition index for nums1
        j = half_len - i      # partition index for nums2

        # Values just to the left and right of each partition
        max_left1  = nums1[i - 1] if i > 0 else -math.inf
        min_right1 = nums1[i]     if i < m else  math.inf
        max_left2  = nums2[j - 1] if j > 0 else -math.inf
        min_right2 = nums2[j]     if j < n else  math.inf

        if max_left1 <= min_right2 and max_left2 <= min_right1:
            # Correct partition found
            if (m + n) % 2 == 1:
                return float(max(max_left1, max_left2))
            else:
                return (max(max_left1, max_left2) + min(min_right1, min_right2)) / 2.0

        elif max_left1 > min_right2:
            # nums1 partition is too far right — move left
            hi = i - 1
        else:
            # nums1 partition is too far left — move right
            lo = i + 1

    raise ValueError("Input arrays are not sorted.")


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

def run_tests():
    test_cases = [
        # (nums1, nums2, expected)
        ([1, 3],          [2],             2.0),
        ([1, 2],          [3, 4],          2.5),
        ([0, 0],          [0, 0],          0.0),
        ([],              [1],             1.0),
        ([2],             [],              2.0),
        ([1, 3, 5, 7],    [2, 4, 6, 8],    4.5),
        ([1, 2],          [1, 2, 3],       2.0),
        ([-5, -3, -1],    [-4, -2, 0],    -2.5),
        ([1, 3],          [2, 4, 5, 6],    3.5),
        ([100000],        [100001],        100000.5),
    ]

    all_passed = True
    for i, (nums1, nums2, expected) in enumerate(test_cases):
        result = find_median_sorted_arrays(nums1, nums2)
        status = "PASS" if abs(result - expected) < 1e-9 else "FAIL"
        if status == "FAIL":
            all_passed = False
        print(f"Test {i + 1:2d}: {status}  "
              f"nums1={nums1}, nums2={nums2}  "
              f"→ got {result}, expected {expected}")

    print()
    print("All tests passed." if all_passed else "Some tests FAILED.")


if __name__ == "__main__":
    run_tests()
