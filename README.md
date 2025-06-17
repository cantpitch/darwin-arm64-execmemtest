darwin-arm64-execmemtest.entitlements is just an example file of what seems to be needed by `codesign` to allow a mmap with both executable and writable memory with:

`com.apple.security.cs.allow-jit`

It may be possible to use an even more permissive entitlement: 

`com.apple.security.cs.allow-unsigned-executable-memory` 

To test this code, simply run `make` and then `./darm64execmemtest`
