package KW.CH08;

import java.util.Arrays;

/**
 * Class to extend QuickSort implementing the second version of the
 * partition Algorithm
 * @author Paul Wolfgang
 */
public class QuickSort2 extends QuickSort {
	
	public int count;
	
    /*<listing chapter="8" number="10">*/
    /**
     * Partition the table so that values from first to pivIndex
     * are less than or equal to the pivot value, and values from
     * pivIndex to last are greater than the pivot value.
     * @param <T> the type being sorted
     * @param table The table to be partitioned
     * @param first The index of the low bound
     * @param last  The index of the high bound
     * @return The location of the pivot value
     */
    @Override
    protected <T extends Comparable<T>>  int partition(T[] table,
            int first,
            int last) {
        // Put the median of table[first], table[middle], table[last]
        // int table[first] and use this value as the pivot
        bubbleSort3(table, first, last);
        swap(table, first, first + (last - first) / 2);
        T pivot = table[first];
        int up = first;
        int down = last;
        do {
            // Invariant:
            // All items in table[first . . . up - 1] <= pivot
            // All items in table[down + 1 . . . last] > pivot
            while ((up < last) && (pivot.compareTo(table[up]) >= 0)) {
                up++;
                //the counts here go up for every time the elements are moved around in the Quick Start
                count++;
            }
            // assert: up equals last or table[up] > pivot.
            while (pivot.compareTo(table[down]) < 0) {
                down--;
                count++;
            }
            // assert: down equals first or table[down] <= pivot.
            if (up < down) { // if up is to the left of down.
                // Exchange table[up] and table[down].
                swap(table, up, down);
            }
        } while (up < down); // Repeat while up is left of down.

        // Exchange table[first] and table[down] thus putting the
        // pivot value where it belongs.
        swap(table, first, down);

        // Return the index of the pivot value.
        return down;
    }

    /**
     * Sort table[first], table[middle], table[last].
     * @param <T> The data type
     * @param table The table to be sorted
     * @param first Index of the first element
     * @param last Index of the last element
     */
    protected <T extends Comparable<T>>  void bubbleSort3(T[] table,
            int first, int last) {
        int middle = first + (last - first) / 2;
        if ((table[middle].compareTo(table[first]) < 0)) {
            swap(table, first, middle);
        }
        // assert: table[first] <= table[middle]
        if ((table[last].compareTo(table[middle])) < 0) {
            swap(table, middle, last);
        }
        // assert: table[last] is the largets of the three.
        if ((table[middle].compareTo(table[first]) < 0)) {
            swap(table, first, middle);
        }
        // assert table[first] <= table[middle] <= table[last]
    }
    /*</listing>*/
    public <T> String toString(T[] table) {
    	return Arrays.toString(table) + "\nName: " + name + " Comparisons: " + count + " " + "Size: " + table.length;
    }
}
