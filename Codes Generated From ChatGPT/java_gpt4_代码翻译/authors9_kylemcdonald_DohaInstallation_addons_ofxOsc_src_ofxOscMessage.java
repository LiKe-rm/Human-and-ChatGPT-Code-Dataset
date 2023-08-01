import java.util.ArrayList;
import java.util.List;

public class OscMessage {

    private String address;
    private List<OscArg> args;
    private String remoteHost;
    private int remotePort;

    public OscMessage() {
        args = new ArrayList<>();
    }

    public void clear() {
        args.clear();
        address = "";
    }

    public int getNumArgs() {
        return args.size();
    }

    public OscArgType getArgType(int index) {
        if (index >= args.size()) {
            System.err.println("OscMessage::getArgType: index " + index + " out of bounds");
            return OscArgType.INDEX_OUT_OF_BOUNDS;
        } else {
            return args.get(index).getType();
        }
    }

    public String getArgTypeName(int index) {
        if (index >= args.size()) {
            System.err.println("OscMessage::getArgTypeName: index " + index + " out of bounds");
            return "INDEX OUT OF BOUNDS";
        } else {
            return args.get(index).getTypeName();
        }
    }

    public int getArgAsInt(int index) {
        if (getArgType(index) != OscArgType.INT) {
            if (getArgType(index) == OscArgType.FLOAT) {
                System.err.println("OscMessage::getArgAsInt: warning: converting float to int for argument " + index);
                return (int) ((OscArgFloat) args.get(index)).get();
            } else {
                System.err.println("OscMessage::getArgAsInt: error: argument " + index + " is not a number");
                return 0;
            }
        } else {
            return ((OscArgInt) args.get(index)).get();
        }
    }

    public float getArgAsFloat(int index) {
        if (getArgType(index) != OscArgType.FLOAT) {
            if (getArgType(index) == OscArgType.INT) {
                System.err.println("OscMessage::getArgAsFloat: warning: converting int to float for argument " + index);
                return (float) ((OscArgInt) args.get(index)).get();
            } else {
                System.err.println("OscMessage::getArgAsFloat: error: argument " + index + " is not a number");
                return 0;
            }
        } else {
            return ((OscArgFloat) args.get(index)).get();
        }
    }

    public String getArgAsString(int index) {
        if (getArgType(index) != OscArgType.STRING) {
            if (getArgType(index) == OscArgType.FLOAT) {
                System.err.println("OscMessage::getArgAsString: warning: converting float to string for argument " + index);
                return Float.toString(((OscArgFloat) args.get(index)).get());
            } else if (getArgType(index) == OscArgType.INT) {
                System.err.println("OscMessage::getArgAsString: warning: converting int to string for argument " + index);
                return Integer.toString(((OscArgInt) args.get(index)).get());
            } else {
                System.err.println("OscMessage::getArgAsString: error: argument " + index + " is not a string");
                return "";
            }
        } else {
            return ((OscArgString) args.get(index)).get();
        }
    }

    public void addIntArg(int argument) {
        args.add(new OscArgInt(argument));
    }

    public void addFloatArg(float argument) {
        args.add(new OscArgFloat(argument));
    }
    public void addStringArg(String argument) {
        args.add(new OscArgString(argument));
    }

    public OscMessage copy(OscMessage other) {
        address = other.address;

        remoteHost = other.remoteHost;
        remotePort = other.remotePort;

        for (int i = 0; i < other.args.size(); ++i) {
            OscArgType argType = other.getArgType(i);
            if (argType == OscArgType.INT) {
                args.add(new OscArgInt(other.getArgAsInt(i)));
            } else if (argType == OscArgType.FLOAT) {
                args.add(new OscArgFloat(other.getArgAsFloat(i)));
            } else if (argType == OscArgType.STRING) {
                args.add(new OscArgString(other.getArgAsString(i)));
            } else {
                assert false : "bad argument type";
            }
        }

        return this;
    }
}

enum OscArgType {
    INT, FLOAT, STRING, INDEX_OUT_OF_BOUNDS
}

interface OscArg {
    OscArgType getType();

    String getTypeName();
}

class OscArgInt implements OscArg {
    private int value;

    public OscArgInt(int value) {
        this.value = value;
    }

    public int get() {
        return value;
    }

    @Override
    public OscArgType getType() {
        return OscArgType.INT;
    }

    @Override
    public String getTypeName() {
        return "int";
    }
}

class OscArgFloat implements OscArg {
    private float value;

    public OscArgFloat(float value) {
        this.value = value;
    }

    public float get() {
        return value;
    }

    @Override
    public OscArgType getType() {
        return OscArgType.FLOAT;
    }

    @Override
    public String getTypeName() {
        return "float";
    }
}

class OscArgString implements OscArg {
    private String value;

    public OscArgString(String value) {
        this.value = value;
    }

    public String get() {
        return value;
    }

    @Override
    public OscArgType getType() {
        return OscArgType.STRING;
    }

    @Override
    public String getTypeName() {
        return "string";
    }
}
