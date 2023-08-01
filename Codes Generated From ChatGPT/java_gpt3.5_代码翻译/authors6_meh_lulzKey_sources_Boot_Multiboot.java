public class Multiboot {
    private Info info;

    public Multiboot(Object information) {
        info = (Info) information;
    }

    public Memory memory() {
        return checkFlag(info.flags, 0) ? new Memory(info.memLower) : null;
    }

    public Device device() {
        return checkFlag(info.flags, 1) ? new Device(info.bootDevice) : null;
    }

    public String command() {
        return checkFlag(info.flags, 2) ? info.command : null;
    }

    public Modules modules() {
        return checkFlag(info.flags, 3) ? new Modules(info.modulesCount) : null;
    }

    public void modules(ModuleFunction function) {
        Modules modules = modules();
        for (int i = 0; i < modules.length; i++) {
            function.execute(modules.item[i]);
        }
    }

    public MemoryMaps memoryMaps() {
        return checkFlag(info.flags, 6) ? new MemoryMaps(info.mmapLength) : null;
    }

    public Drives drives() {
        return checkFlag(info.flags, 7) ? new Drives(info.drivesLength) : null;
    }

    public void drives(DriveFunction function) {
        int size = drives().size;
        Drive first = drives().first;
        int offset = 0;

        while (offset < size) {
            Drive drive = (Drive) (((byte[]) first) + offset);
            offset += drive.size;
            function.execute(drive);
        }
    }

    public Object configTable() {
        return checkFlag(info.flags, 8) ? info.configTable : null;
    }

    public String bootLoader() {
        return checkFlag(info.flags, 9) ? info.bootLoader : null;
    }

    public APM APMTable() {
        return checkFlag(info.flags, 10) ? new APM(info.APMTable) : null;
    }

    public VBE graphicsTable() {
        return checkFlag(info.flags, 11) ? new VBE(info.graphicsTable) : null;
    }

    private boolean checkFlag(int flags, int bit) {
        return (flags & (1 << bit)) != 0;
    }

    // Add other required classes such as Memory, Device, Modules, MemoryMaps, Drives, APM, and VBE.
    // Also, add interfaces like ModuleFunction and DriveFunction.

    // Example:
    public interface ModuleFunction {
        void execute(Module module);
    }
}
