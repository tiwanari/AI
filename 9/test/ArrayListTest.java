import java.util.ArrayList;

class ArrayListTest {
    public static void main(String args[]) {
        ArrayList<String> list = new ArrayList<String>();
        list.ensureCapacity(3);
        list.add(2, "a");
        System.out.println(list);
    }
}
