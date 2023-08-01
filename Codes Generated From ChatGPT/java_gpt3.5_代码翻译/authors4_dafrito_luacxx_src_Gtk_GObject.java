import org.python.core.*;
import org.python.util.PythonInterpreter;

import java.lang.reflect.Method;

public class GObject {
    private Object wrappedObject;

    public GObject(Object obj) {
        this.wrappedObject = obj;
    }

    public Object getWrappedObject() {
        return wrappedObject;
    }

    public PyObject getAttribute(String name) {
        try {
            Method method = wrappedObject.getClass().getMethod(name);
            return Py.java2py(method.invoke(wrappedObject));
        } catch (Exception e) {
            return Py.None;
        }
    }

    public String toString() {
        return wrappedObject.toString();
    }

    public static void main(String[] args) {
        // Initialize Jython
        PythonInterpreter interpreter = new PythonInterpreter();

        // Create a sample object to work with
        String testObject = "Test String";
        GObject gObject = new GObject(testObject);

        // Access the "toUpperCase" method of the wrapped String object
        PyObject result = gObject.getAttribute("toUpperCase");
        System.out.println(result);

        // Access an undefined method
        PyObject undefinedResult = gObject.getAttribute("undefinedMethod");
        System.out.println(undefinedResult);

        // Use Jython to interact with the GObject
        interpreter.set("gObject", gObject);
        interpreter.exec("print(gObject.getAttribute('toUpperCase'))");
    }
}
