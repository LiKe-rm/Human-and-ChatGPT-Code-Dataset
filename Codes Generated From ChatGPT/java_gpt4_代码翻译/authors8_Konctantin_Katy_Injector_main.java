import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.*;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.win32.StdCallLibrary;

import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.ArrayList;

public class DLLInjector {
    private static final String DLL_PATH = "path/to/your/dll.dll";
    private static final String PROCESS_NAME = "notepad.exe";

    public static void main(String[] args) {
        System.out.println("DLL Injector");

        List<Integer> processIds = findProcessIds(PROCESS_NAME);
        if (processIds.isEmpty()) {
            System.out.println("No process found with the name: " + PROCESS_NAME);
            return;
        }

        for (Integer processId : processIds) {
            System.out.println("Found process with id: " + processId);

            if (injectDLL(processId, DLL_PATH)) {
                System.out.println("DLL injection successful");
            } else {
                System.out.println("DLL injection failed");
            }
        }
    }

    private static List<Integer> findProcessIds(String processName) {
        List<Integer> processIds = new ArrayList<>();
        Tlhelp32.PROCESSENTRY32.ByReference processEntry = new Tlhelp32.PROCESSENTRY32.ByReference();
        WinNT.HANDLE snapshot = Kernel32.INSTANCE.CreateToolhelp32Snapshot(Tlhelp32.TH32CS_SNAPPROCESS, 0);

        if (Kernel32.INSTANCE.Process32First(snapshot, processEntry)) {
            do {
                String currentProcessName = Native.toString(processEntry.szExeFile);
                if (currentProcessName.equalsIgnoreCase(processName)) {
                    processIds.add(processEntry.th32ProcessID.intValue());
                }
            } while (Kernel32.INSTANCE.Process32Next(snapshot, processEntry));
        }

        Kernel32.INSTANCE.CloseHandle(snapshot);
        return processIds;
    }

    private static boolean injectDLL(int processId, String dllPath) {
        WinNT.HANDLE processHandle = Kernel32.INSTANCE.OpenProcess(WinNT.PROCESS_CREATE_THREAD | WinNT.PROCESS_QUERY_INFORMATION | WinNT.PROCESS_VM_OPERATION | WinNT.PROCESS_VM_WRITE | WinNT.PROCESS_VM_READ, false, processId);
        if (processHandle == null) {
            return false;
        }

        try {
            int dllPathLength = dllPath.length() + 1;
            Pointer dllPathMemory = Kernel32.INSTANCE.VirtualAllocEx(processHandle, null, dllPathLength, Kernel32.MEM_COMMIT | Kernel32.MEM_RESERVE, Kernel32.PAGE_READWRITE);
            if (dllPathMemory == null) {
                return false;
            }

            if (!Kernel32.INSTANCE.WriteProcessMemory(processHandle, dllPathMemory, dllPath, dllPathLength, null)) {
                return false;
            }

            Pointer loadLibraryAddress = Kernel32.INSTANCE.GetProcAddress(Kernel32.INSTANCE.GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            if (loadLibraryAddress == null) {
                return false;
            }
            WinNT.HANDLE threadHandle = Kernel32.INSTANCE.CreateRemoteThread(processHandle, null, 0, loadLibraryAddress, dllPathMemory, 0, null);
            if (threadHandle == null) {
                return false;
            }

            Kernel32.INSTANCE.WaitForSingleObject(threadHandle, WinDef.INFINITE);

            Kernel32.INSTANCE.VirtualFreeEx(processHandle, dllPathMemory, dllPathLength, Kernel32.MEM_RELEASE);
            Kernel32.INSTANCE.CloseHandle(threadHandle);
        } finally {
            Kernel32.INSTANCE.CloseHandle(processHandle);
        }

        return true;
    }
}
