// [Auto Archived]
// Submit: 2017-08-08 23:50:58
// Time: 1669MS
// Memory: 16476K

import java.awt.*;
import java.math.*;
import java.util.*;

class Main {

    public static final int modn = 998244353;
    public static final int maxv = 20000;
    public static BigInteger range[];
    public static int smallerAns[];
    public static BigInteger pows[];
    public static int c[];

    public static void bit_init() {
        c = new int[maxv];
    }

    public static int bit_sum(int x) {
        int res = 0;
        while (x > 0) {
            res += c[x];
            x -= x & -x;
        }
        return res;
    }

    public static void bit_add(int x, int add) {
        while (x < maxv) {
            c[x] += add;
            x += x & -x;
        }
    }

    public static boolean findSmaller(int signum[], int d, int len,
                                      boolean vis[], int depth, int restrict, boolean free) {
        if (depth == len)
            return true;
        // System.out.printf("%d %d %d %d\n", d, len, depth, restrict);
        int upperBound = signum[depth];
        if (free) upperBound = restrict;
        for (int i = upperBound; i >= (depth == 0 ? 1 : 0); --i) {
            if (!vis[i]) {
                vis[i] = true;
                if (findSmaller(signum, d, len, vis, depth + 1, free ? restrict - 1 : d - 1, free || i != upperBound)) {
                    smallerAns[depth] = i;
                    return true;
                }
                vis[i] = false;
            }
        }
        return false;
    }

    public static long fac(int x) {
        long res = 1;
        for (int i = 1; i <= x; ++i)
            res = res * i % modn;
        return res;
    }

    public static long solve(BigInteger b) {
        if (b.compareTo(BigInteger.ZERO) == 0 || b.compareTo(BigInteger.ONE) == 0) return 0;
        int d = 2;
        for (; ; ++d) {
            if (b.compareTo(pows[d]) >= 0 && b.compareTo(pows[d + 1]) < 0)
                break;
        }
        int signum[] = new int[5000];
        smallerAns = new int[5000];
        BigInteger c = b;
        int len = 0;
        while (c.compareTo(BigInteger.ZERO) > 0) {
            signum[len++] = c.mod(BigInteger.valueOf(d)).intValue();
            c = c.divide(BigInteger.valueOf(d));
        }

        if (len > d) {
            return (fac(d) - 1 + modn) % modn;
        }

        for (int i = 0; i < len / 2; i++) {
            int temp = signum[i];
            signum[i] = signum[len - i - 1];
            signum[len - i - 1] = temp;
        }

        boolean res = findSmaller(signum, d, len, new boolean[5000], 0, d - 1, false);

        long ans = 0;
        if (res) {
            bit_init();
            long f = 1;
            for (int i = len - 1; i >= 0; --i) {
                ans = (ans + bit_sum(smallerAns[i] + 1) * f) % modn;
                bit_add(smallerAns[i] + 1, 1);
                f = f * (len - i) % modn;
            }
            ans = (ans - fac(d - 1) + 1 + modn) % modn;
        }
        ans = (ans + fac(d - 1) - 1 + modn) % modn;
        return ans;
    }

    public static void main(String[] args) {
        int t;
        BigInteger L, R;
        pows = new BigInteger[1700];
        for (int i = 1; i < 1700; ++i) {
            pows[i] = BigInteger.valueOf(i).pow(i - 1);
        }
        Scanner cin = new Scanner(System.in);
        t = cin.nextInt();
        for (int cas = 0; cas < t; ++cas) {
            L = cin.nextBigInteger();
            R = cin.nextBigInteger();
            long ans1 = solve(L.subtract(BigInteger.ONE));
            long ans2 = solve(R);
//            System.out.println("!!   " + ans1 + "      " + ans2);
            System.out.println((ans2 - ans1 + modn) % modn);
        }
    }
}