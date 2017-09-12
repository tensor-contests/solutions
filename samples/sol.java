import java.io.*;
import java.util.*;

public class sol {
    void solve() throws IOException {
        int a = nextInt();
        int b = nextInt();
        out.println(a + b);
        out.flush(); // Only for interactive problem B
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
