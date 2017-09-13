import java.io.*;
import java.util.*;

public class sol {
    class BC {
        public int bulls;
        public int cows;

        public BC() {
            this.bulls = this.cows = 0;
        }

        @Override
        public boolean equals(Object o) {
            BC rhs = (BC)o;
            return this.bulls == rhs.bulls && this.cows == rhs.cows;
        }
    }

    int[] used = new int[10];
    void compare(String q, String ans, BC out)
    {
        for (int i = 0; i < 10; ++i)
            used[i] = 0;
        for (int i = 0; i < 4; ++i)
            used[ans.charAt(i) - '0'] = 1;
        out.bulls = out.cows = 0;
        for (int i = 0; i < 4; ++i)
            if (q.charAt(i) == ans.charAt(i))
                ++out.bulls;
            else
                out.cows += used[q.charAt(i) - '0'];
    }

    void ask(String q)
    {
        out.println(q);
        out.flush();
    }

    void solve() throws IOException {
        ArrayList<String> s = new ArrayList<String>();

        for (int i = 0; i < 10000; ++i) {
            for (int j = 0; j < 10; ++j)
                used[j] = 0;
            int x = i;
            boolean ok = true;
            for (int j = 0; j < 4; ++j) {
                int d = x % 10;
                x /= 10;
                if (used[d] != 0) {
                    ok = false;
                    break;
                }
                used[d] = 1;
            }
            if (ok)
                s.add(String.format("%04d", i));
        }


        String q = "0123";
        ask(q);
        BC ans = new BC();
        BC test = new BC();

        Random rnd = new Random();
        for (;;) {
            ans.bulls = nextInt();
            ans.cows = nextInt();
            if (ans.bulls == 4 && ans.cows == 0)
                return;
            ArrayList<String> ns = new ArrayList<String>();
            for (String x : s) {
                compare(q, x, test);
                if (ans.equals(test))
                    ns.add(x);
            }
            s = ns;

            int pos = rnd.nextInt(s.size());
            q = s.get(pos);
            ask(q);
        }
    }

    int nextInt() throws IOException {
        int c = 0;
        do
            c = bis.read();
        while (c < '0' || c > '9');
        int result = 0;
        do
            result = result * 10 + (c - '0');
        while ((c = bis.read()) >= '0' && c <= '9');
        return result;
    }

    String nextToken() throws IOException {
        int c = 0;
        do
            c = bis.read();
        while (Character.isWhitespace(c));
        toksb.setLength(0);
        do
            toksb.appendCodePoint(c);
        while (!Character.isWhitespace(c = bis.read()));
        return toksb.toString();
    }

    void run() throws IOException {
        solve();
        out.flush();
        out.close();
    }

    public static void main(String []argv) throws IOException {
        new sol().run();
    }

    BufferedInputStream bis = new BufferedInputStream(System.in);
    StringBuilder toksb = new StringBuilder();
    PrintWriter out = new PrintWriter(System.out);
}
