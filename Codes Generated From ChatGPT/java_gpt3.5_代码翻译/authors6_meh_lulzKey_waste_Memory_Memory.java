public class KernelMemory {
    private static int address = 0;

    public static void setAddress(int addr) {
        address = addr;
    }

    public static byte[] alloc(int size, boolean aligned) {
        if (size < 1) {
            return null;
        }

        if (aligned && (address & 0xFFFFF000) != 0) {
            address &= 0xFFFFF000;
            address += 0x1000;
        }

        byte[] memory = new byte[size];
        address += size;
        return memory;
    }

    public static void copy(byte[] destination, byte[] source, int size) {
        System.arraycopy(source, 0, destination, 0, size);
    }

    public static void set(byte[] destination, byte value, int size) {
        Arrays.fill(destination, 0, size, value);
    }

    public static class Memory {
        private int size;
        private byte[] memory;

        public Memory(int size) {
            this.size = size;
            this.memory = KernelMemory.alloc(size, false);
        }

        public Memory(Memory mem) {
            byte[] data = mem.data();
            this.size = mem.size();
            this.memory = KernelMemory.alloc(size, false);
            System.arraycopy(data, 0, this.memory, 0, size);
        }

        public int size() {
            return size;
        }

        public void size(int newSize) {
            size = newSize;
        }

        public byte[] data() {
            return memory;
        }

        public void data(Memory mem, int offset) {
            byte[] data = mem.data();
            int size = mem.size();
            System.arraycopy(data, 0, this.memory, offset, size);
        }

        public void data(byte[] mem, int size, int offset) {
            System.arraycopy(mem, 0, this.memory, offset, size);
        }
    }
}
