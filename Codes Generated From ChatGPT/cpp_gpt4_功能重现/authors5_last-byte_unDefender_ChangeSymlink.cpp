#include <iostream>
#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS(NTAPI* NtOpenSymbolicLinkObjectType)(
    _Out_ PHANDLE             LinkHandle,
    _In_ ACCESS_MASK          DesiredAccess,
    _In_ POBJECT_ATTRIBUTES   ObjectAttributes
);

typedef NTSTATUS(NTAPI* NtCreateSymbolicLinkObjectType)(
    _Out_ PHANDLE             LinkHandle,
    _In_ ACCESS_MASK          DesiredAccess,
    _In_ POBJECT_ATTRIBUTES   ObjectAttributes,
    _In_ PUNICODE_STRING      DestinationName
);

typedef NTSTATUS(NTAPI* NtMakeTemporaryObjectType)(
    _In_ HANDLE hObject
);

NTSTATUS ModifySymbolicLink(const std::wstring& existingLinkName, const std::wstring& newTarget)
{
    HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");
    if (hNtdll == NULL) {
        return STATUS_UNSUCCESSFUL;
    }

    NtOpenSymbolicLinkObjectType NtOpenSymbolicLinkObject = (NtOpenSymbolicLinkObjectType)GetProcAddress(hNtdll, "NtOpenSymbolicLinkObject");
    NtCreateSymbolicLinkObjectType NtCreateSymbolicLinkObject = (NtCreateSymbolicLinkObjectType)GetProcAddress(hNtdll, "NtCreateSymbolicLinkObject");
    NtMakeTemporaryObjectType NtMakeTemporaryObject = (NtMakeTemporaryObjectType)GetProcAddress(hNtdll, "NtMakeTemporaryObject");

    if (NtOpenSymbolicLinkObject == NULL || NtCreateSymbolicLinkObject == NULL || NtMakeTemporaryObject == NULL) {
        return STATUS_UNSUCCESSFUL;
    }

    UNICODE_STRING uExistingLinkName;
    RtlInitUnicodeString(&uExistingLinkName, existingLinkName.c_str());

    OBJECT_ATTRIBUTES objAttr;
    InitializeObjectAttributes(&objAttr, &uExistingLinkName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    HANDLE hExistingLink;
    NTSTATUS status = NtOpenSymbolicLinkObject(&hExistingLink, SYMBOLIC_LINK_ALL_ACCESS, &objAttr);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    status = NtMakeTemporaryObject(hExistingLink);
    if (!NT_SUCCESS(status)) {
        CloseHandle(hExistingLink);
        return status;
    }

    CloseHandle(hExistingLink);

    UNICODE_STRING uNewTarget;
    RtlInitUnicodeString(&uNewTarget, newTarget.c_str());

    HANDLE hNewLink;
    InitializeObjectAttributes(&objAttr, &uExistingLinkName, OBJ_CASE_INSENSITIVE | OBJ_PERMANENT, NULL, NULL);

    status = NtCreateSymbolicLinkObject(&hNewLink, SYMBOLIC_LINK_ALL_ACCESS, &objAttr, &uNewTarget);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    CloseHandle(hNewLink);
    return STATUS_SUCCESS;
}

int main()
{
    std::wstring existingLinkName = L"\\??\\C:\\ExistingLink";
    std::wstring newTarget = L"\\??\\C:\\NewTarget";

    NTSTATUS status = ModifySymbolicLink(existingLinkName, newTarget);
    if (NT_SUCCESS(status)) {
        std::wcout << L"Symbolic link modified successfully." << std::endl;
    } else {
        std::wcout << L"Failed to modify symbolic link. NTSTATUS: " << std::hex << status << std::endl;
    }

    return 0;
}
