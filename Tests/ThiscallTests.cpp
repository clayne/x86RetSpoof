#include <array>
#include <cstdint>
#include <intrin.h>

#include <gtest/gtest.h>

#include "x86RetSpoof.h"

#pragma section(".text")
__declspec(allocate(".text")) constexpr std::array<std::uint8_t, 2> gadget{ 0xFF, 0x23 }; // jmp dword ptr[ebx]

static void* __fastcall getReturnAddressOfMyself()
{
    return _ReturnAddress();
}

TEST(InvokeThiscallTest, ReturnAddressOfTheInvokedFunctionIsTheAddressOfTheGadget) {
    EXPECT_EQ(x86RetSpoof::invokeThiscall<void*>(0, std::uintptr_t(&getReturnAddressOfMyself), std::uintptr_t(gadget.data())), gadget.data());
}
