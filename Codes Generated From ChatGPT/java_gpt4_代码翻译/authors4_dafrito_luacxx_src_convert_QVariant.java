import io.qt.core.*;
import io.qt.gui.*;

import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;
import java.util.function.BiFunction;

public class LuaQVariant {
    private static final Map<Integer, BiConsumer<QVariant, QVariant>> variantStoreHandlers = new HashMap<>();
    private static final Map<Integer, BiConsumer<QVariant, QVariant>> variantPushHandlers = new HashMap<>();
    private static final Map<Integer, BiFunction<QVariant, QVariant, QVariant>> variantGetHandlers = new HashMap<>();

    public static void setVariantStoreHandler(int type, BiConsumer<QVariant, QVariant> handler) {
        variantStoreHandlers.put(type, handler);
    }

    public static void setVariantPushHandler(int type, BiConsumer<QVariant, QVariant> handler) {
        variantPushHandlers.put(type, handler);
    }

    public static void setVariantGetHandler(int type, BiFunction<QVariant, QVariant, QVariant> handler) {
        variantGetHandlers.put(type, handler);
    }

    public static void pushVariant(QVariant source, QVariant destination) {
        // This is a placeholder implementation. In practice, you would push the QVariant value to the Lua state.
        if (source.isNull()) {
            destination.setValue(QVariant.NULL);
            return;
        }

        int userType = source.userType();
        BiConsumer<QVariant, QVariant> pushHandler = variantPushHandlers.get(userType);

        if (pushHandler != null) {
            pushHandler.accept(source, destination);
        } else {
            throw new UnsupportedOperationException("No handler exists to push QVariant type: " + source.typeName());
        }
    }

    public static void storeVariant(QVariant destination, QVariant source) {
        // This is a placeholder implementation. In practice, you would store the QVariant value from the Lua state.
        int userType = source.userType();
        BiConsumer<QVariant, QVariant> storeHandler = variantStoreHandlers.get(userType);

        if (storeHandler != null) {
            storeHandler.accept(destination, source);
        } else {
            throw new UnsupportedOperationException("No QVariant handler exists to store type: " + source.typeName());
        }
    }

    public static QVariant getVariant(QVariant source, QVariant destination) {
        // This is a placeholder implementation. In practice, you would get the QVariant value from the Lua state.
        int userType = source.userType();
        BiFunction<QVariant, QVariant, QVariant> getHandler = variantGetHandlers.get(userType);

        if (getHandler != null) {
            return getHandler.apply(source, destination);
        } else {
            throw new UnsupportedOperationException("No QVariant handler exists to get type: " + source.typeName());
        }
    }
}
