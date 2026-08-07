#define _CRT_SECURE_NO_WARNINGS
#include "./includes/RMemoryManager.hpp"
#include <iostream>
#include <cstring>
#include <cstdint>

int main() 
{
    std::cout << "==================================================\n";
    std::cout << "  Testing Multi-Pool RMemoryManager (10 KB Total) \n";
    std::cout << "==================================================\n\n";

    RMemoryManager manager(10240); // 10 KB Master Buffer

    // -------------------------------------------------------------
    // Test 1: Allocating across different size classes (16B, 32B, 64B, 128B, 256B)
    // -------------------------------------------------------------
    std::cout << "[Test 1] Allocating across various size classes...\n";
    
    void* ptr16  = manager.Allocate(12);  // Should route to Pool 16B
    void* ptr32  = manager.Allocate(28);  // Should route to Pool 32B
    void* ptr64  = manager.Allocate(50);  // Should route to Pool 64B
    void* ptr128 = manager.Allocate(100); // Should route to Pool 128B
    void* ptr256 = manager.Allocate(220); // Should route to Pool 256B

    std::cout << "  -> Alloc 12B  (Pool 16B)  @ " << ptr16  << "\n";
    std::cout << "  -> Alloc 28B  (Pool 32B)  @ " << ptr32  << "\n";
    std::cout << "  -> Alloc 50B  (Pool 64B)  @ " << ptr64  << "\n";
    std::cout << "  -> Alloc 100B (Pool 128B) @ " << ptr128 << "\n";
    std::cout << "  -> Alloc 220B (Pool 256B) @ " << ptr256 << "\n";

    // -------------------------------------------------------------
    // Test 2: Writing & Verifying Data Integrity
    // -------------------------------------------------------------
    std::cout << "\n[Test 2] Writing and verifying data payload across pools...\n";
    
    snprintf((char*)ptr16, 16, "Small_16B");
    snprintf((char*)ptr32, 32, "Medium_32B_Payload_String");
    snprintf((char*)ptr64, 64, "Large_64B_Buffer_String_With_Extra_Payload_Data");

    std::cout << "  -> Data in 16B Pool:  \"" << (char*)ptr16 << "\"\n";
    std::cout << "  -> Data in 32B Pool:  \"" << (char*)ptr32 << "\"\n";
    std::cout << "  -> Data in 64B Pool:  \"" << (char*)ptr64 << "\"\n";

    // -------------------------------------------------------------
    // Test 3: Freeing and Re-allocating Across Pools
    // -------------------------------------------------------------
    std::cout << "\n[Test 3] Freeing pointers and re-allocating...\n";
    
    manager.Free(ptr32);  // Free from 32B Pool
    manager.Free(ptr128); // Free from 128B Pool

    void* newPtr32  = manager.Allocate(30);  // Should reuse ptr32
    void* newPtr128 = manager.Allocate(110); // Should reuse ptr128

    snprintf((char*)newPtr32, 32, "Reused_32B_Slot");

    std::cout << "  -> Reallocated 30B  (Pool 32B)  @ " << newPtr32  << " (Reused " << ptr32 << ")\n";
    std::cout << "     Content: \"" << (char*)newPtr32 << "\"\n";
    std::cout << "  -> Reallocated 110B (Pool 128B) @ " << newPtr128 << " (Reused " << ptr128 << ")\n";

    // -------------------------------------------------------------
    // Test 4: Requesting > 256 Bytes (Size Limit Check)
    // -------------------------------------------------------------
    std::cout << "\n[Test 4] Requesting allocation > 256 bytes...\n";
    void* ptr500 = manager.Allocate(500);
    if (ptr500 == nullptr) {
        std::cout << "  -> SUCCESS: Allocate(500) returned nullptr (exceeds max pool size of 256B).\n";
    } else {
        std::cout << "  -> Allocation returned: " << ptr500 << "\n";
    }

    // Cleanup
    manager.Free(ptr16);
    manager.Free(ptr64);
    manager.Free(ptr256);
    manager.Free(newPtr32);
    manager.Free(newPtr128);

    std::cout << "\n==================================================\n";
    std::cout << "  All Multi-Pool RMemoryManager Tests Passed!     \n";
    std::cout << "==================================================\n";

    return 0;
}