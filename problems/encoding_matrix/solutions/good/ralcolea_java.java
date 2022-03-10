import java.io.*;
import java.util.*;

/**
 *
 * @author Rubén Alcolea Núñez
 * Problem Encoding Matrix
 * AdHoc 1: Just do it!!!
 */
public class ralcolea_java {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();  // For endline
        int zeros = 0, ones = 0;
        char first = 'a';
        String star_zeros = "", star_ones = "", row;
        for (int i = 0; i < n; i++) {
            row = in.nextLine();
            if (first == 'a')
                first = row.charAt(0);
            for (int j = 0; j < n; j++) {
                char x = row.charAt(j);
                if (x == '0') {
                    zeros++;
                    star_zeros += '*';
                    star_ones += 'o';
                }
                else if (x == '1') {
                    ones++;
                    star_zeros += 'o';
                    star_ones += '*';
                }
            }
        }
        
        if (zeros > ones || (zeros == ones && first == '0'))
            star_ones = star_zeros;
        
        for (int i = 0; i < n; i++) {
            row = "";
            for (int j = 0; j < n; j++) 
                row += star_ones.charAt(n * i + j);
            System.out.println(row);
        }
    }
}
