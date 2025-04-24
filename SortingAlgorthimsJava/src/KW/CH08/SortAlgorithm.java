package KW.CH08;

/**
 * Interface to define sort algoirthms.
 * @author Paul Wolfgang
 */
public interface SortAlgorithm {

    /** Sort an array of Comparable objects
     * @param <T> the type to be sorted, must implement Comparable
     * @param table The array of items to sort
     */
    <T extends Comparable<T>>  void sort(T[] table);

	
}
