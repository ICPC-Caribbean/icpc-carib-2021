import java.util.*;
import java.lang.Math;
import java.io.*;

public class ernestico_java {	  

	static double eps = 1e-7;
	static StringBuffer Output = new StringBuffer("");
	static BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

	static double abs(double v) {
		if (v < -eps) return -v;
		return v;
	}

	static class point implements Comparable<point> {
		double x, y;
		int id;
		point (double xx, double yy) { 
			x = xx; y = yy; 
		}
		point () { x = 0.0; y = 0.0; } 
		public double getX ( ) { return x; }
		public double getY ( ) { return y; }
		public int getID ( ) { return id; }
		public void setID ( int idd ) { id = idd; }
		public void setX ( double xx ) { x = xx; }
		public void setY ( double yy ) { y = yy; }
		public point add(point pi) {
			return new point(x + pi.x, y + pi.y);
		}
		public point sub(point pi) {
			return new point(x - pi.x, y - pi.y);
		}
		public point mul(double t) {
			return new point(x * t, y * t);
		}
		public int compareTo (point pi) {
			if ( abs(x - pi.getX()) < eps && abs(y - pi.getY()) < eps) return 0;
			if ( x + eps < pi.getX() || ( abs(x - pi.getX()) < eps && y + eps < pi.getY() ) ) return -1;
			return 1;
		}
	}

	static double cross(point p, point q) {
		return p.getX() * q.getY() - p.getY() * q.getX();
	}
	static double dot(point p, point q) {
		return p.getX() * q.getX() + p.getY() * q.getY();
	}
	static double norm(point p) {
		return dot(p, p);
	}
	static double abs(point p) {
		return Math.sqrt(norm(p));
	}

	static int ccw(point a, point b, point c) {
		b = b.sub(a);
		c = c.sub(a);
		if (cross(b, c) > 0)
			return +1;
		if (cross(b, c) < 0)
			return -1;
		if (dot(b, c) < 0)
			return +2;
		if (norm(b) < norm(c))
			return -2;
		return 0;
	}

	static boolean intersectSP(point s[], point p) {
		if (abs(cross(s[1].sub(s[0]), p.sub(s[0]))) > eps)
			return false;
		return (abs(s[0].sub(p)) + abs(s[1].sub(p)) - abs(s[1].sub(s[0])) < eps);
	}

	static point crosspoint(point l[], point m[]) {
		double A = cross(l[1].sub(l[0]), m[1].sub(m[0]));
		double B = cross(l[1].sub(l[0]), l[1].sub(m[0]));
		if (abs(A) < eps && abs(B) < eps)
			return m[0]; // same line
		if (abs(A) < eps)
			assert(false); // PRECONDITION NOT SATISFIED
		return m[0].add(  m[1].sub(m[0]).mul(B / A)    );
	}

	static ArrayList<point> convex_hull(ArrayList<point> ps) {
		int n = ps.size();
		Collections.sort(ps);
		ArrayList<point> ch = new ArrayList<point> ();
		int k = 0;
		for (int i = 0; i < n; i++) {
			while(k >= 2 && ccw(ch.get(k-2), ch.get(k-1), ps.get(i)) <= 0) {
				k --;
				ch.remove(k);
			}
			ch.add(ps.get(i));
			k ++;
		}

		int t = k+1;
		for (int i = n-2; i >= 0; i--) {
			while(k >= t && ccw(ch.get(k-2), ch.get(k-1), ps.get(i)) <= 0) {
				k --;
				ch.remove(k);
			}
			ch.add(ps.get(i));
			k ++;
		}
		if (k > 1)
			ch.remove(k-1);
		return ch;
	}

	static boolean check_on_point(point a, point pi) throws IOException {
		if (norm(a.sub(pi)) < eps) {
			out.write("1\n");
			out.write(Integer.toString( a.getID() ) + " 1\n");
			return true;
		}
		return false;
	}

	static boolean check_on_segment(point a, point b, point pi) throws IOException {
		point seg[] = new point[] {a, b};
		if (intersectSP(seg, pi)) {
			double t = abs(pi.sub(a)) / abs(b.sub(a));
			out.write("2\n");
			out.write(Integer.toString(a.getID()) + " " + String.format("%.20f", 1-t) + "\n");
			out.write(Integer.toString(b.getID()) + " " + String.format("%.20f", t) + "\n"); 
			return true;
		}	
		return false;
	} 

	public static void main(String[] args)  throws IOException {	

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		// Scanner in = new Scanner(System.in);
		// int n = in.nextInt();
		int n = Integer.parseInt(br.readLine());
		ArrayList<point> p = new ArrayList<point>();
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			point pi = new point(x, y);
			pi.setID(i+1);		
			p.add(pi);
		}

		int q = Integer.parseInt(br.readLine());
		ArrayList<point> qs = new ArrayList<point>();
		for (int i = 0; i < q; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			qs.add(new point(x, y));
		}
		br.close();
	
		p = convex_hull(p);
		n = p.size();

		for (int i = 0; i < q; i++) {
			point pi = qs.get(i);
			
			if (n == 1) {
				if (!check_on_point(p.get(0), pi))
					out.write("impossible\n");
			} else if (n == 2) {
				point a = p.get(0);
				point b = p.get(1);
				if (check_on_point(a, pi) || check_on_point(b, pi))
					continue;
				if (!check_on_segment(a, b, pi))
					out.write("impossible\n");
			} else {
				if (cross(p.get(1).sub(p.get(0)), pi.sub(p.get(0))) < -eps) {
					out.write("impossible\n");
					continue;
				} 
				if (cross(p.get(n-1).sub(p.get(0)), pi.sub(p.get(0))) > eps) {
					out.write("impossible\n");
					continue;
				}
				
				int lo = 1, hi = n-2;
				while (lo < hi) {
					int m = (lo + hi + 1) >> 1;
					if (cross(p.get(m).sub(p.get(0)), pi.sub(p.get(0))) >= 0)
						lo = m;
					else
						hi = m-1;
				}

				point a = p.get(0), b = p.get(lo), c = p.get(lo+1);
				if (cross(c.sub(b), pi.sub(b)) < -eps) {
					out.write("impossible\n");
					continue;
				}

				if (check_on_point(a, pi) || check_on_point(b, pi) || check_on_point(c, pi))
              	  	continue;

            	if (check_on_segment(a, b, pi) || check_on_segment(b, c, pi) || check_on_segment(a, c, pi))
                	continue;

				
				point d = crosspoint(new point[] {b, pi}, new point[] {a, c});
				double t = abs(pi.sub(b)) / abs(d.sub(b));
				double k = abs(d.sub(a)) / abs(c.sub(a));

				out.write("3\n");
				out.write(Integer.toString(a.getID()) + " " + String.format("%.20f", t * (1 - k)) + "\n");
				out.write(Integer.toString(b.getID()) + " " + String.format("%.20f", 1 - t) + "\n");
				out.write(Integer.toString(c.getID()) + " " + String.format("%.20f", t * k) + "\n");
			}
		}

		out.flush();
	}
}