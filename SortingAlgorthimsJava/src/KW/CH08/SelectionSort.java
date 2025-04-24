package KW.CH08;

import java.util.Arrays;

/** Implements the selection sort algorithm.
 *  @author Koffman and Wolfgang
 **/
public class SelectionSort implements SortAlgorithm {
	
	public int count;
    public String name = "Selection Sort";
	
	
	
	/**
     * Sort the array using selection sort algorithm.
     * pretable contains Comparable objects.
     * posttable is sorted.
     * @param table The array to be sorted
     */
    @Override
    public <T extends Comparable<T>>  void sort(T[] table) {
        int n = table.length;
        for (int fill = 0; fill < n - 1; fill++) {
            // Invariant: table[0 . . . fill - 1] is sorted.
            int posMin = fill;
            for (int next = fill + 1; next < n; next++) {
                // Invariant: table[posMin] is the smallest item in
                // table[fill . . . next - 1].
                if (table[next].compareTo(table[posMin]) < 0) {
                    posMin = next;
                    
                }
                //Everytime that an element was moved it was taken into account 
                count++;
            }
            
            // assert: table[posMin] is the smallest item in
            // table[fill . . . n - 1].
            // Exchange table[fill] and table[posMin].
            T temp = table[fill];
            table[fill] = table[posMin];
            table[posMin] = temp;
            // assert: table[fill] is the smallest item in
            // table[fill . . . n - 1].
        }
        // assert: table[0 . . . n - 1] is sorted.
    
    }
    public <T> String toString(T[] table) {
    	return Arrays.toString(table) + "\nName: " + name + " Comparisons: " + count + " " + "Size: " + table.length;
    }
   
}
