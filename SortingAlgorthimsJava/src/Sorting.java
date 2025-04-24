import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

import KW.CH08.InsertionSort;
import KW.CH08.MergeSort;
import KW.CH08.QuickSort;
import KW.CH08.QuickSort2;
import KW.CH08.SelectionSort;


public class Sorting {
	
	public static void main(String args[]) {
		
		Scanner myObj = new Scanner(System.in);
		
		//Random class being used to generate random numbers 0-1000
		Random rand = new Random();
		
	
		//takes user input to 
		System.out.println("Welcome to the Array Sorter, Input how many elements you would like sorted: ");
		int userIn1 = myObj.nextInt();
		//Integer had to be used insetad of Int because of complexity with the comparable
		Integer[] arr = new Integer[userIn1];
		
		//using for loop to insert random numbers into user defined array size
		for(int i = 0; i < userIn1; i++) {
			
			arr[i] = rand.nextInt(1000);
		}
		
		//Prints the OG String of randomized characters 
		System.out.println(Arrays.toString(arr));
		
		System.out.println("Sorted Algorithmns:");
				
				//Selection sort object maker 
				InsertionSort IS = new InsertionSort();
				IS.sort(arr);
				//Prints the length and the information about the Sorted array
				System.out.println(IS.toString(arr));
				
				System.out.println(" ");
				MergeSort MS = new MergeSort();
				MS.sort(arr);
				//passing our array to toString allows the sorted array to be displayed through the toStirng function
				System.out.println(MS.toString(arr));
				
				System.out.println(" ");
				//couldnt use the Quicksort1 because of the abstarct class so used QS2 instead
				QuickSort2 QS = new QuickSort2();
				QS.sort(arr);
				System.out.println(QS.toString(arr));
				
				System.out.println(" ");
				SelectionSort SS = new SelectionSort();
				SS.sort(arr);
				System.out.println(SS.toString(arr));
				
		}
		
		
	}