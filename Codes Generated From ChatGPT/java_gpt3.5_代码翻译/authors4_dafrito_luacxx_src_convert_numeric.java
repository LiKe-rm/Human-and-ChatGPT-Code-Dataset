import org.luaj.vm2.*;

public class LuaNumeric {

    public static class LuaConversionException extends RuntimeException {
        public LuaConversionException(String message) {
            super(message);
        }
    }

    public static long luaToJavaInteger(LuaValue source) {
        long destination;

        // Directly retrieve boolean types.
        if (source.isboolean()) {
            destination = source.toboolean() ? 1 : 0;
            return destination;
        }

        // Directly retrieve numeric types.
        if (source.isnumber()) {
            destination = source.tolong();
            return destination;
        }

        // Convert the first character of a string to its numeric value.
        if (source.isstring()) {
            destination = source.tojstring().charAt(0);
            return destination;
        }

        // Convert userdata to integers by interpreting the data as-is.
        if (source.isuserdata()) {
            // Since we cannot access the internal representation of userdata,
            // an exception is thrown to indicate that this conversion is not supported.
            throw new LuaConversionException("Cannot convert userdata to integer.");
        }

        // If the value cannot be converted, throw an exception.
        throw new LuaConversionException("Unsupported Lua value type for conversion.");
    }
}
