import java.util.BitSet;

public class QBitArray {
    private BitSet bitSet;

    public QBitArray() {
        bitSet = new BitSet();
    }

    public QBitArray(int size) {
        bitSet = new BitSet(size);
    }

    public QBitArray(int size, boolean value) {
        bitSet = new BitSet(size);
        if (value) {
            bitSet.set(0, size);
        }
    }

    public QBitArray(QBitArray other) {
        bitSet = (BitSet) other.bitSet.clone();
    }

    public boolean at(int index) {
        return bitSet.get(index);
    }

    public void clear() {
        bitSet.clear();
    }

    public void clearBit(int index) {
        bitSet.clear(index);
    }

    public int count() {
        return bitSet.cardinality();
    }

    public void fill(boolean value) {
        fill(value, bitSet.size());
    }

    public void fill(boolean value, int size) {
        if (value) {
            bitSet.set(0, size);
        } else {
            bitSet.clear(0, size);
        }
    }

    public boolean isEmpty() {
        return bitSet.isEmpty();
    }

    public boolean isNull() {
        return bitSet == null;
    }

    public void resize(int newSize) {
        if (newSize < bitSet.size()) {
            for (int i = newSize; i < bitSet.size(); i++) {
                bitSet.clear(i);
            }
        }
    }

    public void setBit(int index) {
        bitSet.set(index);
    }

    public int size() {
        return bitSet.size();
    }

    public void swap(QBitArray other) {
        BitSet temp = this.bitSet;
        this.bitSet = other.bitSet;
        other.bitSet = temp;
    }

    public boolean testBit(int index) {
        return bitSet.get(index);
    }

    public void toggleBit(int index)) {
        bitSet.flip(index);
    }

    public void truncate(int pos) {
        if (pos < bitSet.size()) {
            for (int i = pos; i < bitSet.size(); i++) {
                bitSet.clear(i);
            }
        }
    }
}
