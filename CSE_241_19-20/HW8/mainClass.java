import java.util.Iterator;

public class mainClass {
    public static void main(String [] args){
        GTUContainer<Integer> gtuSet = new GTUSet<>(5);

        // Check if the array is empty.
        isEmptyPrint(gtuSet);
        System.out.println("-----------------------------------------------------");

        for (int i = 0; i < 10; i++) {
            gtuSet.insert(i);
        }

        gtuSet.insert(100);
        gtuSet.insert(50);
        gtuSet.insert(44);
        gtuSet.insert(47);
        gtuSet.insert(19);

        System.out.println("Array after insertions:");
        printElements(gtuSet);
        System.out.println("-----------------------------------------------------");

        int item = 10;
        // Check the element that is not in the array.
        containsPrint(gtuSet, item);
        System.out.println("-----------------------------------------------------");

        item = 5;
        // Check the element that is in the array.
        containsPrint(gtuSet, item);
        System.out.println("-----------------------------------------------------");

        // Add the element inside the array to the set.
        System.out.println("Array before inserting duplicated element");
        System.out.println("Trying to insert duplicated element: "+ item);
        printElements(gtuSet);
        gtuSet.insert(item);
        System.out.println("Array after trying to insert duplicated element");
        printElements(gtuSet);
        System.out.println("-----------------------------------------------------");

        // Check the size and element after deleting it.
        System.out.println("size: " + gtuSet.size() + ", maxsize: " + gtuSet.max_size() + " before erasing.");
        int deletedItem = 7;
        System.out.println("The item that will be deleted: " + deletedItem);
        gtuSet.erase(deletedItem);
        containsPrint(gtuSet, deletedItem);

        System.out.println("size: " + gtuSet.size() + ", maxsize: " + gtuSet.max_size() + " after erasing.");

        // Check if the set is empty after adding an element.
        isEmptyPrint(gtuSet);

        // After deleting the entire array, check if it's empty.
        System.out.println("-----------------------------------------------------");
        System.out.println("Clearing all the content...");
        gtuSet.clear();
        System.out.println("Cleared all the content.");
        isEmptyPrint(gtuSet);
        System.out.println("size: " + gtuSet.size() + ", maxsize: " + gtuSet.max_size() + " after clearing.");
        System.out.println("Iterating over the container to see whether all elements are deleted.");
        printElements(gtuSet);
        System.out.println("Iteration is completed.");

        GTUContainer<String> gtuVector = new GTUVector<>(5);

        isEmptyPrint(gtuVector);

        System.out.println("-----------------------------------------------------");

        gtuVector.insert("Mamitora");
        gtuVector.insert("Erza");
        gtuVector.insert("Jeanne");
        gtuVector.insert("Jalter");
        gtuVector.insert("2B");

        System.out.println("Vector after insertions:");
        printElements(gtuVector);

        System.out.println("-----------------------------------------------------");

        String str = "Saber";
        // Check the element that is not in the array.
        containsPrint(gtuVector, str);
        System.out.println("-----------------------------------------------------");

        str = "Jeanne";
        // Check the element that is in the array.
        containsPrint(gtuVector, str);
        System.out.println("-----------------------------------------------------");


        // Adding an element to the vector.
        System.out.println("Vector before inserting duplicated element");
        System.out.println("Trying to insert duplicated element: "+ str);
        printElements(gtuVector);
        gtuVector.insert(str);
        System.out.println("Vector after trying to insert duplicated element");
        printElements(gtuVector);
        System.out.println("-----------------------------------------------------");

        // Check the size and the element after deleting it from the Vector.
        System.out.println("size: " + gtuVector.size() + ", maxsize: " + gtuVector.max_size() + " before erasing.");
        String deletedStr = "Jeanne";
        System.out.println("The item that will be deleted: " + deletedStr);
        gtuVector.erase(deletedStr);
        containsPrint(gtuVector, deletedStr);

        System.out.println("size: " + gtuVector.size() + ", maxsize: " + gtuVector.max_size() + " after erasing.");

        // Check if the vector is empty after adding an element
        isEmptyPrint(gtuVector);

        // Check if the vector is empty after deleting the entire vector.
        System.out.println("-----------------------------------------------------");
        System.out.println("Clearing all the content...");
        gtuVector.clear();
        System.out.println("Cleared all the content.");
        isEmptyPrint(gtuVector);
        System.out.println("size: " + gtuVector.size() + ", maxsize: " + gtuVector.max_size() + " after clearing.");
        System.out.println("Iterating over the container to see whether all elements are deleted.");
        printElements(gtuVector);
        System.out.println("Iteration is completed.");
    }

    public static <T> void isEmptyPrint(GTUContainer<T> gtuContainer) {
        if (gtuContainer.empty())
            System.out.println("Collection is empty");
        else
            System.out.println("Collection is not empty.");
    }

    public static <T> void containsPrint(GTUContainer<T> gtuContainer, T item) {
        if (gtuContainer.contains(item)) {
            System.out.println(item + " is in array.");
        }
        else {
            System.out.println(item + " is not in array.");
        }
    }

    public static <T> void printElements(GTUContainer<T> gtuContainer) {
        Iterator<T> iter = gtuContainer.iterator();
        for (; iter.hasNext(); ) {
            T element = iter.next();
            System.out.print(element + ", ");
        }
        System.out.println();
    }
}
