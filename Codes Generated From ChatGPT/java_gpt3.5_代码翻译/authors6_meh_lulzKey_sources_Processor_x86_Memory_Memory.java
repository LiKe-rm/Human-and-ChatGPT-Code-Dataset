public class MemoryManager {
    private int address = 0;

    public byte[] alloc(int size, boolean aligned) {
        if (size < 1) {
            return null;
        }

        return _alloc(size, aligned);
    }

    public byte[] alloc(int size, Integer physical, boolean aligned) {
        if (size < 1) {
            return null;
        }

        return _alloc(size, physical, aligned);
    }

    public void free(byte[] pointer) {
        // Java has automatic garbage collection, so no need to implement this method
    }

    public void copy(byte[] destination, byte[] source, int size) {
        System.arraycopy(source, 0, destination, 0, size);
    }

    public void set(byte[] destination, byte value, int size) {
        for (int i = 0; i < size; i++) {
            destination[i] = value;
        }
    }

    private byte[] _alloc(int size, boolean align) {
        if (align && (address & 0xFFFFF000) != 0) {
            address &= 0xFFFFF000;
            address += 0x1000;
        }

        byte[] tmp = new byte[size];
        address += size;

        return tmp;
    }

    private byte[] _alloc(int size, Integer physical, boolean align) {
        if (align && (address & 0xFFFFF000) != 0) {
            address &= 0xFFFFF000;
            address += 0x1000;
        }

        if (physical != null) {
            physical = address;
        }

        byte[] tmp = new byte[size];
        address += size;

        return tmp;
    }
}
