import java.util.HashMap;
import java.util.Map;

public class AlgorithmParameters {

    private AlgorithmParametersNode mNext;
    private boolean mDefaultThrowIfNotUsed;

    public AlgorithmParameters() {
        mDefaultThrowIfNotUsed = true;
    }

    public AlgorithmParameters(AlgorithmParameters x) {
        mDefaultThrowIfNotUsed = x.mDefaultThrowIfNotUsed;
        mNext = x.mNext;
    }

    public AlgorithmParameters assign(AlgorithmParameters x) {
        mNext = x.mNext;
        return this;
    }

    public boolean getVoidValue(String name, Class<?> valueType, Object pValue) {
        if (mNext != null) {
            return mNext.getVoidValue(name, valueType, pValue);
        } else {
            return false;
        }
    }

    public interface CombinedNameValuePairs {
        boolean getVoidValue(String name, Class<?> valueType, Object pValue);
    }

    public abstract class AlgorithmParametersBase implements CombinedNameValuePairs {

        private String mName;
        private AlgorithmParametersNode mNext;
        private boolean mUsed;

        public AlgorithmParametersBase() {
            mUsed = false;
        }

        public void assign(AlgorithmParametersBase rhs) {
            throw new UnsupportedOperationException("Assignment not supported");
        }

        public boolean getVoidValue(String name, Class<?> valueType, Object pValue) {
            if (name.equals("ValueNames")) {
                if (!valueType.isAssignableFrom(String.class)) {
                    throw new IllegalArgumentException("Type mismatch");
                }
                if (mNext != null) {
                    mNext.getVoidValue(name, valueType, pValue);
                }
                ((StringBuilder) pValue).append(mName).append(";");
                return true;
            } else if (name.equals(mName)) {
                assignValue(name, valueType, pValue);
                mUsed = true;
                return true;
            } else if (mNext != null) {
                return mNext.getVoidValue(name, valueType, pValue);
            } else {
                return false;
            }
        }

        protected abstract void assignValue(String name, Class<?> valueType, Object pValue);

    }

    public class AlgorithmParametersNode extends AlgorithmParametersBase {

        private final Map<String, Object> mValues;

        public AlgorithmParametersNode() {
            mValues = new HashMap<>();
        }

        @Override
        protected void assignValue(String name, Class<?> valueType, Object pValue) {
            Object value = mValues.get(name);
            if (value != null && valueType.isAssignableFrom(value.getClass())) {
                pValue = value;
            } else {
                throw new IllegalArgumentException("Type mismatch");
            }
        }

        public boolean getVoidValue(String name, Class<?> valueType, Object pValue) {
            if (name.equals("ValueNames")) {
                return mValues.keySet().stream().anyMatch(key -> key.equals(name));
            } else {
                return super.getVoidValue(name, valueType, pValue);
            }
        }

    }
}
