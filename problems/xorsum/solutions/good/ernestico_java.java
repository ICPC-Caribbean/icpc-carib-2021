import java.util.*;

public class ernestico_java {	  
	
	static long get_best_with_2(int a, int b) {
		long ret = 0;
		for (int i = 0; i < 30; i++) {
			if((a&(1<<i)) == (b&(1<<i)))
				ret += 2l * (1<<i);
			else 
				ret += 3l * (1<<i);
		}
		return ret;
	}

	static long get_best_with_1(int a, int b) {
		long ret = 0;
		for (int i = 0; i < 30; i++) {
			if((a&(1<<i)) == (b&(1<<i)))
				ret += 2l * (1<<i);
			else 
				ret += 1l * (1<<i);
		}
		return ret;
	}
	
	static long max(long a, long b) {
		if (a > b) return a;
		return b;
	}

	static long v = (1<<30) - 1;

	public static void main(String[] args) {	
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int a[] = new int[n];
		for (int i = 0; i < n; i++) 
			a[i] = in.nextInt();
		in.close();
	
		
		if (n == 2) {
			System.out.println(v);
			return;
		}

		if (n == 3) {
			System.out.println(2l * v);
			return;
		}

		long pref[] = new long[n];
		long suff[] = new long[n];
		for (int i = 1; i < n; i++) 
			pref[i] = pref[i-1] + (a[i-1] ^ a[i]);
		for (int i = n-2; i >= 0; i--) 
			suff[i] = suff[i+1] + (a[i] ^ a[i+1]);

		long ans = pref[n-1];

		ans = max(ans, max(suff[2], pref[n-3]) + 2l*v);
		for (int i = 1; i < n-2; i++) 
			ans = max(ans, pref[i-1] + suff[i+2] + get_best_with_2(a[i-1], a[i+2]));
		
		long dp[] = new long[n];
		dp[0] = v;
		ans = max(ans, suff[1] + v);
		for (int i = 1; i < n; i++) {
			dp[i] = pref[i-1];
			if (i < n-1)
				dp[i] += get_best_with_1(a[i-1], a[i+1]);
			else 
				dp[i] += v;
			
			ans = max(ans, dp[i] + ((i == n-1)? 0 : suff[i+1]));
			
			if (i > 1) 
				ans = max(ans, dp[i-2] + ((i == n-1)? v : get_best_with_1(a[i-1], a[i+1]) + suff[i+1]));
			if (i < n-1)
				dp[i] = max(dp[i], dp[i-1] + ((i == n-1)? 0 : (a[i] ^ a[i+1])));
		}	
		
		System.out.println(ans);
	}
}