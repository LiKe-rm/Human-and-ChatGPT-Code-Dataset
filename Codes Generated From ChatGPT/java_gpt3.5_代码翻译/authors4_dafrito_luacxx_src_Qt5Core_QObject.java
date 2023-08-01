import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer;

public class QObject {
    private Map<String, Object> properties = new HashMap<>();
    private Map<String, QMetaMethod> methods = new HashMap<>();
    private Map<String, Consumer<Object>> slots = new HashMap<>();

    public Object getProperty(String name) {
        return properties.get(name);
    }

    public void setProperty(String name, Object value) {
        properties.put(name, value);
    }

    public QMetaMethod getMethod(String name) {
        return methods.get(name);
    }

    public void addMethod(String name, QMetaMethod method) {
        methods.put(name, method);
    }

    public void connect(String signal, Consumer<Object> slot) {
        slots.put(signal, slot);
    }

    public void emit(String signal, Object argument) {
        Consumer<Object> slot = slots.get(signal);
        if (slot != null) {
            slot.accept(argument);
        }
    }

    public static void main(String[] args) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException, NoSuchMethodException {
        QObject obj = new QObject();

        obj.setProperty("name", "John Doe");

        Method method = obj.getClass().getDeclaredMethod("someMethod");
        QMetaMethod metaMethod = new QMetaMethod(method);
        obj.addMethod("sayHello", metaMethod);

        System.out.println(obj.getProperty("name"));
        obj.getMethod("sayHello").invoke(obj);

        obj.connect("testSignal", argument -> System.out.println("Slot received argument: " + argument));
        obj.emit("testSignal", "Hello from signal");
    }

    public void someMethod() {
        System.out.println("Hello, World!");
    }
}

class QMetaMethod {
    private Method method;

    public QMetaMethod(Method method) {
        this.method = method;
    }

    public void invoke(QObject object, Object... args) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException {
        method.invoke(object, args);
    }
}
