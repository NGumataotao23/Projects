/*<listing chapter="8" number="5"*/
package KW.CH08;

import java.util.Arrays;

/**
 * Implements the recursive merge sort algorithm. In this version, copies
 *  of the subtables are made, sorted, and then merged.
 *  @author Koffman and Wolfgang
 */
public class MergeSort implements SortAlgorithm {
	
	public static int count;
	public String name = "Merge Sort";
    /**
     * Sort the array using the merge sort algorithm.
     * preable contains Comparable objects.
     * posttable is sorted.
     * @param table The array to be sorted
     */
    @Override
    @SuppressWarnings({"unchecked", "rawtypes"})
    public <T extends Comparable<T>>  void sort(T[] table) {
        // A table with one element is sorted already.
    	
        if (table.length > 1) {
            // Split table into halves.
        	
            int halfSize = table.length / 2;
            T[] leftTable = (T[]) new Comparable[halfSize];
            T[] rightTable =
                    (T[]) new Comparable[table.length - halfSize];
            System.arraycopy(table, 0, leftTable, 0, halfSize);
            System.arraycopy(table, halfSize, rightTable, 0,
                    table.length - halfSize);

            // Sort the halves.
            sort(leftTable);
            sort(rightTable);
            // Merge the halves.
            merge(table, leftTable, rightTable);
            
        }
  
    }
    
    /*<listing chapter="8" number="4">*/
    /**
     * Merge two sequences.
     * preeftSequence and rightSequence are sorted.
     * postoutputSequence is the merged result and is sorted.
     * @param outputSequence The destination
     * @param leftSequence The left input
     * @param rightSequence The right input
     */
    private static <T extends Comparable<T>>  void merge(T[] outputSequence, T[] leftSequence, T[] rightSequence) {
        int i = 0; // Index into the left input sequence.
        int j = 0; // Index into the right input sequence.
        int k = 0; // Index into the output sequence.

        // While there is data in both input sequences
        while (i < leftSequence.length && j < rightSequence.length) {
            // Find the smaller and
            // insert it into the output sequence.
            if (leftSequence[i].compareTo(rightSequence[j]) < 0) {
                outputSequence[k++] = leftSequence[i++];
            } else {
                outputSequence[k++] = rightSequence[j++];
            }
            //count places here because this is where the elements are inputted in the array
            count++;
        }
        // assert: one of the sequences has more items to copy.
        // Copy remaining input from left sequence into the output.
        while (i < leftSequence.length) {
            outputSequence[k++] = leftSequence[i++];
        }
        // Copy remaining input from right sequence into output.
        while (j < rightSequence.length) {
            outputSequence[k++] = rightSequence[j++];
        }
        
    }
    
    /*</listing>*/
    
    //Adding the comparable generic to the toString fucntion allows use to call the function to get the sorted algorthm since we call it after the sorting has happened
    public <T> String toString(T[] table) {
    	
    	
    	return Arrays.toString(table) + "\nName: " + name + " Comparisons: " + count + " "  + "Size: " + table.length  ;
    }
}

