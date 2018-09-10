// [Auto Archived]
// Submit: 2017-04-28 23:38:53
// Time: 312MS
// Memory: 10488K

import java.util.*;

public class Main {
    
    public static boolean getInteger(String s, int a, int b) {
        // s = s.trim();
        int t = Integer.parseInt(s);
        if (!Integer.toString(t).equals(s))
            return false;
        if (t < a || t > b)
            return false;
        return true;
    }

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNextLine()) {
            String s = cin.nextLine();
            int a = cin.nextInt();
            int b = cin.nextInt();
            if (cin.hasNextLine())
                cin.nextLine();
            try {
                if (getInteger(s, a, b))
                    System.out.println("YES");
                else System.out.println("NO");
            } catch (NumberFormatException e) {
                System.out.println("NO");
            }
        }
    }
}