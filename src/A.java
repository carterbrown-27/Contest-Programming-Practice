import java.io.*;
import java.util.*;

public class A {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        for(int t = 0; t < T; t++){
            int n = Integer.parseInt(in.readLine());
            boolean odd = false;
            boolean even = false;
            StringTokenizer st = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                if(Integer.parseInt(st.nextToken()) % 2 == 0){
                    even = true;
                }else{
                    odd = true;
                }
            }

            System.out.println(((n%2==1 && odd) || (n%2==0 && odd && even)) ? "YES" : "NO");
        }
    }

    public static boolean okcheck(int[] a){
        return true;
    }
}
