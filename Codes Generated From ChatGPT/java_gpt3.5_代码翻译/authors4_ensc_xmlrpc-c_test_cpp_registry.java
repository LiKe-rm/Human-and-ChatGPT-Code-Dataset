import java.util.HashMap;
import java.util.Map;

public class Registry {

    public static void main(String[] args) {
        Registry registry = new Registry();
        registry.addMethod("sample.add", new SampleAddMethod());
        registry.addMethod("test.callinfo", new TestCallInfoMethod());

        // 测试用例
        registry.processCall("sample.add", 5, 7);
        registry.processCall("test.callinfo");
    }

    private final Map<String, Method> methods = new HashMap<>();

    public void addMethod(String name, Method method) {
        methods.put(name, method);
    }

    public Object processCall(String methodName, Object... params) {
        Method method = methods.get(methodName);
        if (method == null) {
            throw new RuntimeException("Method not found: " + methodName);
        }
        return method.execute(params);
    }

    public interface Method {
        Object execute(Object... params);
    }

    public static class SampleAddMethod implements Method {
        @Override
        public Object execute(Object... params) {
            if (params.length != 2) {
                throw new IllegalArgumentException("Expected two parameters");
            }
            int a = (Integer) params[0];
            int b = (Integer) params[1];
            int sum = a + b;
            System.out.println("The sum of " + a + " and " + b + " is " + sum);
            return sum;
        }
    }

    public static class TestCallInfoMethod implements Method {
        @Override
        public Object execute(Object... params) {
            System.out.println("This is a test call info method.");
            return null;
        }
    }
}