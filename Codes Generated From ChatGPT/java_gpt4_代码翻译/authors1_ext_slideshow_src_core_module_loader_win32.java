import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;

public class ModuleLoader {

    private Map<String, Module> loadedModules;

    public ModuleLoader() {
        loadedModules = new HashMap<>();
    }

    public void init(String searchPath) {
        // 在Java中，类路径由类加载器负责，因此，你需要设置一个合适的类加载器。
        // 这里暂时省略这部分代码。
    }

    public void cleanup() {
        loadedModules.clear();
    }

    public Module open(String name) {
        try {
            if (loadedModules.containsKey(name)) {
                return loadedModules.get(name);
            }

            Class<?> moduleClass = Class.forName(name);
            Module module = new Module(moduleClass);
            loadedModules.put(name, module);

            return module;
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public void close(Module module) {
        loadedModules.remove(module.getName());
    }

    public static class Module {
        private Class<?> moduleClass;

        public Module(Class<?> moduleClass) {
            this.moduleClass = moduleClass;
        }

        public String getName() {
            return moduleClass.getName();
        }

        public String getAuthor() {
            // 如果需要，请在实际代码中为模块提供作者信息。
            return "Unknown";
        }

        public Object callMethod(String methodName, Object... args) {
            try {
                Class<?>[] argTypes = new Class<?>[args.length];
                for (int i = 0; i < args.length; i++) {
                    argTypes[i] = args[i].getClass();
                }

                Method method = moduleClass.getMethod(methodName, argTypes);
                return method.invoke(null, args);
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }
    }
}
