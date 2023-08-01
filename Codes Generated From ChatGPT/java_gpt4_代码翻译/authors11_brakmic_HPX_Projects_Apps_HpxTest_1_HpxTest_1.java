import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class HpxTestJava {

    public static void main(String[] args) {
        MyComponent component = new MyComponent();
        component.setId(1);

        functionInvocationDemo(component);

        continuationDemo(component);

        errorHandlingDemo(component);

        componentDemo(component);

        dllComponentDemo(10, "Harris");
    }

    public static void functionInvocationDemo(MyComponent component) {
        component.printNumber(2.0);
        int value1 = component.getNumber();
        System.out.println("Async function returned: " + value1);

        component.printNumber(5.0);
    }

    public static void continuationDemo(MyComponent component) {
        CompletableFuture<Integer> future = CompletableFuture.supplyAsync(() -> component.increaseTen(31))
                .thenApplyAsync(value -> component.increaseOne(value));

        try {
            int contValue = future.get();
            System.out.println("Value from continuation: " + contValue);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }

    public static void errorHandlingDemo(MyComponent component) {
        try {
            component.divideNumber(0);
        } catch (Exception e) {
            System.out.println("Exception thrown: " + e.getMessage());
        }
    }

    public static void componentDemo(MyComponent component) {
        int aNumber = component.getNumber();
        System.out.println("Original value from component: " + aNumber);

        component.setNumber(125);

        aNumber = component.getNumber();
        System.out.println("Component changed value to: " + aNumber);
    }

    public static void dllComponentDemo(int numComponents, String name) {
        List<MyComponent> components = new ArrayList<>();
        for (int i = 0; i < numComponents; i++) {
            MyComponent newComponent = new MyComponent();
            newComponent.setId(i + 1);
            components.add(newComponent);
        }

        for (MyComponent component : components) {
            component.printGreeting(name);
        }
    }
}

class MyComponent {

    private int id;
    private int number = 42;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void printNumber(double value) {
        System.out.println("Printing number: " + (value * number));
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public int increaseTen(int value) {
        return value + 10;
    }

    public int increaseOne(int value) {
        return value + 1;
    }

    public void divideNumber(int divisor) throws Exception {
        if (divisor == 0) {
            throw new Exception("Cannot divide by zero");
        }
        System.out.println("Dividing number: " + (number / divisor));
    }

    public void printGreeting(String name) {
        System.out.println("Hello, " + name + " from component " + id);
    }
}
