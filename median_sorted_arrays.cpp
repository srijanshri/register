/*
 * Median of Two Sorted Arrays
 *
 * Time Complexity : O(log(min(m, n)))  — satisfies O(log(m+n))
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Always binary-search on the smaller array
        vector<int>& A = (nums1.size() <= nums2.size()) ? nums1 : nums2;
        vector<int>& B = (nums1.size() <= nums2.size()) ? nums2 : nums1;

        int m = A.size();
        int n = B.size();
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
                if ((m + n) % 2 == 1)
                    return max(maxLeft1, maxLeft2);
                else
                    return (max(maxLeft1, maxLeft2) +
                            min(minRight1, minRight2)) / 2.0;

            } else if (maxLeft1 > minRight2) {
                hi = i - 1;   // move partition left in A
            } else {
                lo = i + 1;   // move partition right in A
            }
        }

        return -1.0; // unreachable if inputs are valid sorted arrays
    }
};
