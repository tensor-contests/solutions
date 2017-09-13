import java.io.*;
import java.util.*;

public class sol {
    void solve() throws IOException {
        String s1 = nextToken();
        String s2 = nextToken();
        String s = nextToken();
        HashMap<Character, Character> m = new HashMap<Character, Character>();
        for (int i = 0; i < 26; ++i) {
            char c1 = s1.charAt(i);
            char c2 = s2.charAt(i);
            m.put(c1, c2);
            m.put(Character.toUpperCase(c1), Character.toUpperCase(c2));
        }

        for (int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if (m.containsKey(c))
                out.print(m.get(c));
            else
                out.print(c);
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
