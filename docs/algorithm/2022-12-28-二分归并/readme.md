## 南川题解Leetcode 4. Median of Two Sorted Arrays

要在两个有序数组 $A(m), B(n)$ 中找到合并后数组的中位数，即在这两个数组中分别找到两个分界点 $i, j$（对于分界点的定义，理论上应该既可以是一个元素，也可以是两个元素之间的间隔，为编程方便，我们统一为元素），使得：
1. 位于这两个分界点左边的元素个数总和（$i+j$）等于总元素的一半；
2. 所有位于左边的元素都不大于这两个分界点中的较小值，所有位于右边的元素都不小于在这两个分界点中的较大值。

显然，$(i, j) \in [0, m] \times [0, n]$，这是个有限集，遍历的复杂度为$O(mn)$。

考虑条件1，可以知道 $i$ 和 $j$ 始终一一对应，因此遍历的复杂度为 $O(m+n)$。又由于两个数组有序，因此基于二分法可以做到 $O(log(m+n))$。

考虑条件2，可以得到其等价条件，即$A_{i-1} \le B_{j} \cap B_{j-1} \le A_{i}$。编程实现时，若 $i, j$ 抵达右边界，则需使用判断控制或者哨兵结点的手段。

基于条件1和条件2，我们可以写出状态转移函数，即在不满足条件2的情况对 $i$ 和 $j$ 进行同步微调，用一个 $step$ 进行控制，循环时，$step$ 可取如下：
$$
k = \left\{\begin{aligned}
min(m-i, j),& i往右j往左时\\
min(i, n-j),& i往左j往右时
\end{aligned}\right.\\
step = \left\{\begin{aligned}
min\{max\{step / 2, 1\}, k\}, & 二分法 \\
1, & 暴力法
\end{aligned}\right.
$$

接下来分析一下中位数计算逻辑。

首先，分界点所在的指针并不始终等价于中位数的决定元素。例如 $A=[2,3], B=[-1,4]$，则分别从A、B的中间划分，其分界点为$(1, 1)$，但是中位数并非由$A_1, B_1$决定的，而是$A_0, A_1$决定的。而若 $A=[-2, 3], B=[-1, 4]$，则分界点依旧为$(1, 1)$，但中位数由 $A_1, B_0$ 决定。可见，找到分界点之后，我们需要综合考虑分界点附近的最多四个数，找到左边两个数中的较大值，与右边两个数中的较小值，继而求其平均。

以上是长度和为偶数时的情况，奇数时则稍微简单一些。例如 $A=[1,3], B=[2]$，则2为中点，分界点为$(1,0)$，中位数一定是由两个分界点中的较小值决定（可以思考一下为什么）。

因此，我们可以得出以下中位数计算公式：

$$
f(m, n, i, j) = \left\{ \begin{aligned}
    \min \{ A_i, B_j\},&\ m+n\ is\ odd, 0\le i\lt m, 0\le j \lt n\\
    A_i,&\ m+n\ is\ odd, 0\le i\lt m, j = n\\
    B_j,&\ m+n\ is\ odd, i = m, 0\le j \lt n\\
    (\max \{ A_{i-1}, B_{j-1}\} + \min \{A_i, B_j\}) / 2,&\ m+n\ is\ even, 0\lt i\lt m, 0\lt j \lt n\\
    (A_{i-1} + A_i) / 2,&\ m+n\ is\ even, 0\lt i\lt m, j=0\\
    (A_{i} + A_{i+1}) / 2,&\ m+n\ is\ even, 0\lt i\lt m, j=n\\
    (B_{j} + B_{j+1}) / 2,&\ m+n\ is\ even, i = 0, 0\lt j\lt n\\
    (B_{j} + B_{j+1}) / 2,&\ m+n\ is\ even, i = m, 0\lt j\lt n\\
\end{aligned} \right.
$$

代码：
```c++
class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int HALF = (m + n) / 2;
        int step = HALF;
        int i = m / 2, j = HALF - i;

        // 状态转移迭代
        while(true) {
            // i左移j右移
            if(i > 0 && j < n && nums1[i-1] > nums2[j]) {
                step = min(max(step/2, 1), min(i, n-j));
                i -= step; 
                j += step;
            }
            // i右移j左移
            else if(j > 0 && i < m && nums2[j-1] > nums1[i]) {
                step = min(max(step/2, 1), min(j, m-i));
                i += step; 
                j -= step;
            }
            else break;
        }

        // 计算中位数
        if((m + n) % 2) { // 奇数
            if(i == m) return nums2[j];
            if(j == n) return nums1[i];
            return min(nums1[i], nums2[j]);
        } else {  // 偶数
            int L = i == 0 ? nums2[j-1] : j == 0 ? nums1[i-1] : max(nums1[i-1], nums2[j-1]);
            int R = i == m ? nums2[j] : j == n ? nums1[i] : min(nums1[i], nums2[j]);
            return (double) (L + R) / 2;
        }
    }
};
```