#include <ntifs.h>
#include <ntddk.h>
#include <string>
#include <vector>

extern "C" NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT   DriverObject,
    _In_ PUNICODE_STRING  RegistryPath
);

extern "C" NTSTATUS
UnloadDriver(
    _In_ PDRIVER_OBJECT DriverObject
);

extern "C" VOID
OnProcessNotify(
    _Inout_ PEPROCESS      Process,
    _In_    HANDLE         ProcessId,
    _Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
);

NTSTATUS
AddPathHandler(
    _In_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength
);

NTSTATUS
RemovePathHandler(
    _In_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength
);

NTSTATUS
GetPathListLengthHandler(
    _Out_ PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG ReturnLength
);

NTSTATUS
GetPathsHandler(
    _Out_ PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG ReturnLength
);

extern "C" NTSTATUS
DeviceControlHandler(
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ PIRP Irp
);

std::vector<std::wstring> g_blockedPaths;

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT   DriverObject,
    _In_ PUNICODE_STRING  RegistryPath
) {
    NTSTATUS status;
    PDEVICE_OBJECT deviceObject = nullptr;
    UNICODE_STRING deviceName, symbolicLink;

    RtlInitUnicodeString(&deviceName, L"\\Device\\BlockedPathDriver");
    status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObject);

    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to create device object (0x%08X)\n", status));
        return status;
    }

    RtlInitUnicodeString(&symbolicLink, L"\\DosDevices\\BlockedPathDriver");
    status = IoCreateSymbolicLink(&symbolicLink, &deviceName);

    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to create symbolic link (0x%08X)\n", status));
        IoDeleteDevice(deviceObject);
        return status;
    }

    DriverObject->MajorFunction[IRP_MJ_CREATE] = DeviceControlHandler;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = DeviceControlHandler;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceControlHandler;
    DriverObject->DriverUnload = UnloadDriver;

    status = PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, FALSE);

    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to register process notify routine (0x%08X)\n", status));
        IoDeleteSymbolicLink(&symbolicLink);
        IoDeleteDevice(deviceObject);
        return status;
    }

    return STATUS_SUCCESS;
}

NTSTATUS
UnloadDriver(
    _In_ PDRIVER_OBJECT DriverObject
) {
    UNICODE_STRING symbolicLink;

    PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, TRUE);

    RtlInitUnicodeString(&symbolicLink, L"\\DosDevices\\BlockedPathDriver");
    IoDeleteSymbolicLink(&symbolicLink);
    IoDeleteDevice(DriverObject->DeviceObject);

    return STATUS_SUCCESS;
}

VOID
OnProcessNotify(
    _Inout_ PEPROCESS      Process,
    _In_    HANDLE         ProcessId,
    _Inout_ PPS_CREATE_NOTIFY_INFO CreateInfo
) {
    if (CreateInfo != nullptr) {
        for (const auto& path : g_blockedPaths) {
            if (_wcsnicmp(CreateInfo->CommandLine->Buffer, path.c_str(), path.size()) == 0) {
                CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
                break;
            }
        }
    }
}

NTSTATUS
AddPathHandler(
    In PVOID InputBuffer,
    In ULONG InputBufferLength
) {
    if (InputBufferLength % sizeof(wchar_t) != 0) {
        return STATUS_INVALID_PARAMETER;
    }
    std::wstring path(static_cast<wchar_t*>(InputBuffer), InputBufferLength / sizeof(wchar_t));
    g_blockedPaths.push_back(path);

    return STATUS_SUCCESS;
}

NTSTATUS
RemovePathHandler(
    In PVOID InputBuffer,
    In ULONG InputBufferLength
) {
    if (InputBufferLength % sizeof(wchar_t) != 0) {
        return STATUS_INVALID_PARAMETER;
    }
    std::wstring path(static_cast<wchar_t*>(InputBuffer), InputBufferLength / sizeof(wchar_t));
    auto it = std::find(g_blockedPaths.begin(), g_blockedPaths.end(), path);

    if (it == g_blockedPaths.end()) {
        return STATUS_NOT_FOUND;
    }

    g_blockedPaths.erase(it);

    return STATUS_SUCCESS;
}

NTSTATUS
GetPathListLengthHandler(
    Out PVOID OutputBuffer,
    In ULONG OutputBufferLength,
    Out PULONG ReturnLength
) {
    if (OutputBufferLength < sizeof(ULONG)) {
        return STATUS_BUFFER_TOO_SMALL;
    }

    *reinterpret_cast<PULONG>(OutputBuffer) = static_cast<ULONG>(g_blockedPaths.size());
    *ReturnLength = sizeof(ULONG);

    return STATUS_SUCCESS;
}

NTSTATUS
GetPathsHandler(
    Out PVOID OutputBuffer,
    In ULONG OutputBufferLength,
    Out PULONG ReturnLength
) {
    ULONG requiredSize = 0;

    for (const auto& path : g_blockedPaths) {
        requiredSize += static_cast<ULONG>(path.size() * sizeof(wchar_t));
    }

    if (OutputBufferLength < requiredSize) {
        return STATUS_BUFFER_TOO_SMALL;
    }

    wchar_t* pBuffer = static_cast<wchar_t*>(OutputBuffer);

    for (const auto& path : g_blockedPaths) {
        memcpy(pBuffer, path.c_str(), path.size() * sizeof(wchar_t));
        pBuffer += path.size();
    }

    *ReturnLength = requiredSize;

    return STATUS_SUCCESS;
}

extern "C" NTSTATUS
DeviceControlHandler(
    In PDEVICE_OBJECT DeviceObject,
    Inout PIRP Irp
) {
    PIO_STACK_LOCATION ioStack;
    PVOID inputBuffer, outputBuffer;
    ULONG inputBufferLength, outputBufferLength, controlCode, returnLength = 0;
    NTSTATUS status;

    UNREFERENCED_PARAMETER(DeviceObject);

    ioStack = IoGetCurrentIrpStackLocation(Irp);
    inputBuffer = Irp->AssociatedIrp.SystemBuffer;
    outputBuffer = Irp->AssociatedIrp.SystemBuffer;
    inputBufferLength = ioStack->Parameters.DeviceIoControl.InputBufferLength;
    outputBufferLength = ioStack->Parameters.DeviceIoControl.OutputBufferLength;
    controlCode = ioStack->Parameters.DeviceIoControl.IoControlCode;

    switch (controlCode) {
        case IOCTL_ADD_PATH:
            status = AddPathHandler(inputBuffer, inputBufferLength);
            break;

        case IOCTL_REMOVE_PATH:
            status = RemovePathHandler(inputBuffer, inputBufferLength);
            break;

        case OCTL_GET_PATH_LIST_LENGTH:
            status = GetPathListLengthHandler(outputBuffer, outputBufferLength, &returnLength);
            break;

        case IOCTL_GET_PATHS:
            status = GetPathsHandler(outputBuffer, outputBufferLength, &returnLength);
            break;

        default:
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = returnLength;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return status;
}
