 package P1;

import java.io.*;
import java.util.*;

public class MagicSquare {
	
	public static void test (int x) {
		String fileName = String.format("src/P1/txt/%d.txt",x);
		System.out.println("The result of test " + x + " is: " + isLeagleMagicSquare(fileName));
	}
	
	public static void main (String[] args) {
		System.out.println("Part1.");

		System.out.println("The test results are as follows");
		for (int i=1; i<=6; ++i) test(i);
		System.out.println("Part2. Please input the size of the square to generate:");
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		if (generateMagicSquare(n)) {
			System.out.println("Successfully! The result has been written into src/P1/txt/6.txt");
			test(6);
		} else {
			System.out.println("Fail to generate");
		}
		
		in.close();
	}

	/**
	 * 
	 *@description Check whether a matrix a magic square 
	 *@param fileName the path of the file
	 *@return true if the matrix is a magic square or false if not
	 */
	
	public static boolean isLeagleMagicSquare(String fileName) {
		try (Scanner in = new Scanner(new FileInputStream(fileName));) {
			
			Vector<Vector<Integer>> matrix = new Vector<Vector<Integer>>();
			
			while (in.hasNext()) {
				String now = in.nextLine();
				Vector <Integer> it = new Vector <Integer> ();
				String[] line = now.trim().split("\t");
				
				int leng = line.length;
				for (int i=0; i<leng; ++i) {
					String x = line[i];
					try {
						it.add(Integer.parseInt(x));
					}
					catch (NumberFormatException e){
						System.err.println("!Error: The input file:" + fileName + " contains non-integer or doesn't be separated by '\\t'.");
						return false;
					}
				}
				matrix.add(it);
			}
			
			for (int i=1; i<matrix.size(); ++i) {
				if (!matrix.isEmpty() && (matrix.get(i).size() != matrix.get(0).size())) {
					System.err.println("!Error: The input file:" + fileName + " is not a matrix.");
					return false;
				}
			}
			
			if (matrix.size() != matrix.get(0).size()) System.err.println("!Error: The input file:" + fileName + " is not a square.");
			if (matrix.isEmpty()) System.err.println("!Error: The input file:" + fileName + " is an empty matrix");
			
			int n = matrix.size();
			
			boolean[] v = new boolean[n*n];
			Arrays.fill(v, false);
			
			for (int i=0; i<n; ++i) {
				for (int j=0; j<n; ++j) {
					int x = matrix.get(i).get(j);
					if (x < 1 || x > n*n || v[x-1]) {
						System.err.println("!Error: The numbers of the input file:" + fileName + "are not different each other and ranged between 1 and 10.");
						return false;
					}
					v[x-1] = true;
				}
			}
			
			int sum = 0;
			
			for (int i=0; i<n; ++i) {
				sum += matrix.get(0).get(i);
			}
			
			for (int i=1; i<n; ++i) {
				int tot = 0;
				for (int j=0; j<n; ++j) {
					tot += matrix.get(i).get(j);
				}
				if (tot != sum) {
					System.err.println("!Error: The sums of the numbers in all rows, all columns, and both diagonals of the input file:" + fileName + "are not the same.");
					return false;
				}
			}
			
			for (int i=0; i<n; ++i) {
				int tot = 0;
				for (int j=0; j<n; ++j) {
					tot += matrix.get(j).get(i);
				}
				if (tot != sum) {
					System.err.println("!Error: The sums of the numbers in all rows, all columns, and both diagonals of the input file:" + fileName + "are not the same.");
					return false;
				}
			}
			
			int tot = 0;
			for (int i=0; i<n; ++i) {
				tot += matrix.get(i).get(i);
			}
			
			if (tot != sum) {
				System.err.println("!Error: The sums of the numbers in all rows, all columns, and both diagonals of the input file:" + fileName + "are not the same.");
				return false;
			}
			
			tot = 0;
			for (int i=0; i<n; ++i) {
				tot += matrix.get(i).get(n-i-1);
			}
			
			if (tot != sum) {
				System.err.println("!Error: The sums of the numbers in all rows, all columns, and both diagonals of the input file:" + fileName + "are not the same.");
				return false;
			}
			
			return true;
			
		} catch (FileNotFoundException e) {
			System.err.println("!Error: The input file:" + fileName + " not found.");
			return false;
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	}
	
	/**
	 * 
	 *@description generate a magic square of size n*n 
	 *@param n a positive odd integer which means the size of the matrix
	 *@return true if generate successfully or false if not
	 */
	
	public static boolean generateMagicSquare(int n) {
		
		String fileName = String.format("src/P1/txt/6.txt");
		
		try {
			File file = new File(fileName);
			file.createNewFile();
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		
			   if (n < 0 || n%2 == 0) {
			System.err.println("!Error: n is not a positive odd");
			return false;
		}
		
		int magic[][] = new int[n][n];
		int row = 0, col = n / 2, i, j, square = n * n; // 定义放置1的位置为第一行正中间
		for (i = 1; i <= square; i++) {
			magic[row][col] = i;
			if (i % n == 0) // 填数字时n个数字一组，每n个数字就会重叠，需要重新定义初始位置
				row++;
			else { // 填数字时每次都将下一个数字填在右上方
				if (row == 0) // 若当前填数字在第一行，那么下一个数字填在最后一行
					row = n - 1;
				else
					row--;
				if (col == (n - 1)) // 若当前填数字在最后一列，那么下一个数字就填在第一列
					col = 0;
				else
					col++; //每次位置向右移动
			}
		}
		
		try (PrintStream out = new PrintStream(new FileOutputStream(fileName));) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++)
					out.print(magic[i][j] + "\t");
				out.println();
			}
			out.close();
			return true;
		} catch (FileNotFoundException e) {
			System.err.println("!Error: Unable to find " + fileName);
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}
}