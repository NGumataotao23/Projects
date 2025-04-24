/*<listing chapter="8" number="2">*/
package KW.CH08;

import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Implements the insertion sort algorithm.
 * @author Koffman and Wolfgang
 **/
public class InsertionSort implements SortAlgorithm {

	
	public int count;
	public String name = "Insertion Sort";
    /**
     * Sort the table using insertion sort algorithm.
     * pretable contains Comparable objects.
     * posttable is sorted.
     * @param table The array to be sorted
     */
    @Override
    public <T extends Comparable<T>>  void sort(T[] table) {
        for (int nextPos = 1; nextPos < table.length; nextPos++) {
            // Invariant: table[0 . . . nextPos - 1] is sorted.
            // Insert element at position nextPos
            // in the sorted subarray.
        	
            insert(table, nextPos);
            //count was placed here to count the amount of comparisons 
            count++;
        } // End for.
        
    } // End sort.

    /**
     * Insert the element at nextPos where it belongs
     * in the array.
     * pretable[0 . . . nextPos - 1] is sorted.
     * posttable[0 . . . nextPos] is sorted.
     * @param table The array being sorted
     * @param nextPos The position of the element to insert
     */
    private static <T extends Comparable<T>>  void insert(T[] table,
            int nextPos) {
    	
        T nextVal = table[nextPos]; // Element to insert.
        while (nextPos > 0
                && nextVal.compareTo(table[nextPos - 1]) < 0) {
            table[nextPos] = table[nextPos - 1]; // Shift down.
            nextPos--; // Check next smaller element.
        }
        // Insert nextVal at nextPos.
        table[nextPos] = nextVal;
    }
   
    //All the toStrings are basically the same, with name and the amount of comaprisons 
    public <T> String toString(T[] table) {
    	return Arrays.toString(table)+ "\nName: " + name + " Comparisons: " + count + " " + "Size: " + table.length;
    }
}
/*</listing>*/
