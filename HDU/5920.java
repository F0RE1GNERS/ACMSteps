// [Auto Archived]
// Submit: 2016-10-04 19:36:49
// Time: 452MS
// Memory: 14008K

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{

    public static List<BigInteger> list;
    public static BigInteger r;

    public static String copyNumber(String s, int repeat)
    {
        StringBuffer sb = new StringBuffer(s);
        int startPosition = s.length() - 1 - repeat;
        for (int i = startPosition; i >= 0; --i)
            sb.append(s.charAt(i));
        return sb.toString();
    }

    public static boolean isSpecial(BigInteger b)
    {
        String st = b.toString();
        if (st.charAt(0) != '1')
            return false;
        for (int i = 1; i < st.length(); ++i)
            if (st.charAt(i) != '0')
                return false;
        return true;
    }

    public static boolean check()
    {
        if (r.compareTo(BigInteger.ZERO) == 0)
            return false;
        if (isSpecial(r)) {
            list.add(BigInteger.ONE);
            r = r.subtract(BigInteger.ONE);
            return true;
        }
        String newStr = r.toString();
        int rlen = newStr.length();
        int nlen = (rlen+1)/2;
        String nStr = newStr.substring(0,nlen);
        String mStr;
        while (true) {
            mStr = copyNumber(nStr, rlen%2);
            //System.out.println(mStr.toString());
            BigInteger b = new BigInteger(mStr);
            if (b.compareTo(r) <= 0) {
                list.add(b);
                r = r.subtract(b);
                return true;
            } else {
                BigInteger c = new BigInteger(nStr);
                nStr = c.subtract(BigInteger.ONE).toString();
            }
        }
    }

    public static void main(String args[])
    {
        Scanner cin = new Scanner(System.in);
        int t;
        t = cin.nextInt();
        for (int testc = 1; testc <= t; ++testc)
        {
            r = cin.nextBigInteger();
            list = new ArrayList<BigInteger>();
            while (check());
            System.out.println("Case #"+Integer.toString(testc)+":");
            System.out.println(list.size());
            for (int i = 0; i < list.size(); ++i)
                System.out.println(list.get(i).toString());
        }

    }
}