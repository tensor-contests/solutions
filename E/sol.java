import java.io.*;
import java.util.*;

public class sol {
    class Query {
        public int id;
        public int l;
        public int r;
    }

    int[] a;
    Query[] q;
    
    void read() throws IOException {
        int n = nextInt();
        a = new int[n];
        for (int i = 0; i < n; ++i)
            a[i] = nextInt();
        int m = nextInt();
        q = new Query[m];
        for (int i = 0; i < m; ++i) {
            q[i] = new Query();
            q[i].id = i;
            q[i].l = nextInt();
            q[i].r = nextInt();
        }
    }
    
    void fenwickTreeAdd(int[] t, int pos, int val) {
        for (int x = pos; x < t.length; x |= x + 1)
            t[x] += val;
    }
    
    int fenwickTreePrefixSum(int[] t, int pos) {
        int res = 0;
        for (int x = pos; x >= 0; x = (x & (x + 1)) - 1)
            res += t[x];
        return res;
    }
    
    void solve() throws IOException {
        int[] cnt = new int[a.length];
        for (Query qq : q)
            ++cnt[qq.r];
        for (int i = 1; i < cnt.length; ++i)
            cnt[i] += cnt[i - 1];
        Query[] sq = new Query[q.length];
        for (Query qq : q)
            sq[--cnt[qq.r]] = qq;
        q = sq;
        sq = null;
        cnt = null;

        int[] result = new int[q.length];
        int[] t = new int[a.length + 1];
        HashMap<Integer, Integer> prevPos = new HashMap<>();
        for (int i = 0, q_ptr = 0; i < a.length; ++i) {
            fenwickTreeAdd(t, prevPos.containsKey(a[i]) ? prevPos.get(a[i]) : 0, 1);
            fenwickTreeAdd(t, i + 1, -1);
            prevPos.put(a[i], i + 1);
            for (; q_ptr < q.length && q[q_ptr].r == i; ++q_ptr)
                result[q[q_ptr].id] = fenwickTreePrefixSum(t, q[q_ptr].l);
        }
        StringBuilder sb = new StringBuilder();
        for (int x : result) {
            sb.append(x);
            sb.append('\n');
        }
        out.write(sb.toString());
    }

    void run() throws IOException {
        read();
        solve();
        out.flush();
        out.close();
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

    public static void main(String []argv) throws IOException {
        new sol().run();
    }

    BufferedInputStream bis = new BufferedInputStream(System.in);
    StringBuilder toksb = new StringBuilder();
    PrintWriter out = new PrintWriter(System.out);
}
