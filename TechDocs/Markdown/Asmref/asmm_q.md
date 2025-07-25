## 2.5 Routines M-Q

----------
#### MemAlloc
Creates a block and assigns a handle to it. This block can be discardable, 
swapable, fixed or movable. A passed flag determines whether heap 
compaction or discarding of objects should be used to generate free space.

**Pass:**  
ax - Size (in bytes) to allocate.  
cl - **HeapFlags** record.  
ch - **HeapAllocFlags** record.

**Returns:**  
CF - Set if error (not enough memory).  
bx - Handle to block allocated.  
ax - Address of block allocated (if block is fixed or locked).

**Destroyed:**  
cx

**Library:** heap.def

----------
#### MemAllocLMem
Allocates a block within a local memory heap from scratch. To take an 
existing block and create a local memory heap built on it, use 
**LMemInitHeap**.

**Pass:**  
ax - Type of heap (**LMemType**).  
cx - Size of block header (or 0 for the default).

**Returns:**  
bx - Block handle of the new block. This block will have two 
handles allocated and 64 bytes heap space.

**Destroyed:**  
Nothing.

**Library:** lmem.def

----------
#### MemAllocSetOwner
Creates a block, assigns a handle to it, and explicitly sets the owner of the 
new block by passing the handle of the owning geode. Otherwise, it is 
identical to **MemAlloc**.

**Pass:**  
ax - Size (in bytes) to allocate.  
cl - **HeapFlags** record.  
ch - **HeapAllocFlags** record.  
bx - New owner of block.

**Returns:**  
CF - Set if error (not enough memory).  
bx - Handle to block allocated.  
ax - Address of block allocated (if block is fixed or locked).

**Destroyed:**  
cx

**Library:** heap.def

----------
#### MemDecRefCount
Decrements a reference count in a memory handle and immediately frees it 
when the count reaches zero.

**Pass:**  
bx - Memory handle. If zero, this routine will do nothing; 

**Returns:**  
Non-EC: - Nothing.  
EC: - **bx** cleared if reference count drops to zero (and block was 
freed).

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemDerefDS
Returns the address of the block referenced by its block handle into the DS 
register. The block must be locked before calling this routine. This routine is 
useful in allocating a fixed or locked block.

**Pass:**  
bx - Block handle.

**Returns:**  
ds - Segment of handle.

**Destroyed:**  
Nothing. Flags preserved.

**Library:** heap.def

----------
#### MemDerefES
Returns the address of a block referenced by its block handle into the ES 
register. the block must be locked before calling this routine.

**Pass:**  
bx - Block handle.

**Returns:**  
es - Segment of handle.

**Destroyed:**  
Nothing. Flags preserved.

**Library:** heap.def

----------
#### MemDiscard
Throws away the contents of a discardable memory block.

**Pass:**  
bx - Handle of memory block.

**Returns:**  
CF - Set if block couldn't be discarded. (This may happen if the 
block being discarded is a VM block, for example, and some 
other thread is using the file.)

**Destroyed:**  
bx

**Library:** heap.def

----------
#### MemDowngradeExclLock
Downgrades an exclusive lock to a shared lock, waking any shared lockers 
blocked on the block.

**Pass:**  
bx - Block handle whose exclusive lock should be downgraded.

**Returns:**  
ax - Segment of block.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemFree
Frees a memory block. The block may be locked at the time it is freed. 
Therefore, make sure that no other thread has locked the block before freeing 
it.

**Pass:**  
bx - Handle of block to free.

**Returns:**  
Nothing.

**Destroyed:**  
bx

**Library:** heap.def

----------
#### MemGetInfo
Returns information about a memory block. Pass this routine the proper 
**MemGetInfoType**. The return values depend on what information you 
request.

**Pass:**  
ax - **MemGetInfoType**.  
bx - Handle of block.

**Returns:**  
ax - Value based on the MemGetInfoType passed:  
MGIT_SIZE  
 - ax = size of block in bytes.  
MGIT_FLAGS_AND_LOCK_COUNT   
 - al = **HeapFlags**.  
 - ah = lock count.  
MGIT_OWNER_OR_VM_FILE_HANDLE  
 - ax = handle of owner.  
MGIT_ADDRESS  
 - ax = segment of block.  
MGIT_OTHER_INFO  
 - ax = contents of HM_otherInfo field.  
MGIT_EXEC_THREAD  
 - ax = handle of thread.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemIncRefCount
Increments a reference count on a memory handle.

**Pass:**  
bx - Memory handle. If zero, will do nothing. 

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemInitRefCount
Initializes a reference count for a memory handle.

**Pass:**  
bx - Memory handle.  
ax - Initial reference count (0 is not allowed).

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemLock
Locks the given block, returning the absolute address of the block of memory 
pointed to by the given handle. Increments the lock count by one. Locked 
memory blocks cannot be moved or discarded (though they may be freed). You 
cannot give a block a lock count greater than 255.

**Pass:**  
bx - Handle to block of memory.

**Returns:**  
CF - Set on error (Block is discarded).  
ax - Segment address of block of memory.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemLockExcl

Locks a memory block for exclusive read/write access. If no one has locked the 
block, the thread will gain exclusive access; otherwise, the thread will block 
and the request will go on the queue. Use **MemUnlockExcl** to unlock the 
block for exclusive access.

**Pass:**  
bx - Block to lock.

**Returns:**  
ax - Segment address of locked block.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemLockFixedOrMovable
Given a virtual segment, locks the corresponding block down if the segment 
is movable.

**Pass:**  
bx - Virtual segment.

**Returns:**  
CF - Set if block is discarded and can't be reloaded; clear if block 
is OK.  
ax - Segment if block is OK; zero otherwise.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemLockShared
Locks a block down for shared (usually read-only) access.

**Pass:**  
bx - Handle of block to be locked.

**Returns:**  
ax - Segment of locked block.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemModifyFlags
Modify the *HM_flags* associated with a memory block. The following bits may 
be altered: HF_SHARABLE, HF_DISCARDABLE, HF_SWAPABLE, and 
HF_LMEM.

**Pass:**  
bx - Handle of block to modify.  
al - Flags to set in the *HM_flags* field.  
ah - Flags to clear in the *HM_flags* field.

**Returns:**  
Nothing.

**Destroyed:**  
ax

**Library:** heap.def

----------
#### MemModifyOtherInfo
Modifies the *HM_otherInfo* field associated with a memory block.

**Pass:**  
bx - Handle of block to modify.  
ax - New *HM_otherInfo* value.

**Returns:**  
Nothing.

**Destroyed:**  
ax

**Library:** heap.def

----------
#### MemOwner
Returns the owner field of a handle.

**Pass:**  
bx - Handle.

**Returns:**  
bx - Owner. if the block is owned by a VM file, the process that 
owns the VM file is returned. 

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemPLock
Calls **HandleP** and **MemLock** in that order.

**Pass:**  
bx - Handle of memory block.

**Returns:**  
ax - Segment address of block.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemReAlloc
Reallocates space within a given block, changing its size. Also used to 
reallocate space for a block that has been discarded.

**Pass:**  
ax - Size (in bytes) to allocate. Pass zero to allocate the block with 
the same size.  
bx - Handle of block.  
ch - **HeapAllocFlags**.

**Returns:**  
CF - Set if error (not enough memory).  
bx - Handle of block (unchanged).  
ax - Segment address of block if HF_LOCK was passed in the 
**HeapAllocFlags**.

**Destroyed:**  
ax, cx

**Library:** heap.def

----------
#### MemSegmentToHandle
Returns the corresponding handle of a passed segment value.

**Pass:**  
cx - Segment address.

**Returns:**  
CF - Set if a matching handle is found.  
cx - Handle.

**Returns:**  
Nothing.

**Library:** heap.def

----------
#### MemThreadGrab
Locks a block and increments a semaphore on the block; the current thread 
will be able to perform more **MemThreadGrab** operations but other threads 
will block on **MemThreadGrab**. If another thread has the semaphore 
**MemThreadGrab** blocks until it can get the semaphore; it then increments 
the semaphore, locks the block, and returns the address.

**Pass:**  
bx - Handle of block.

**Returns:**  
CF - Set if block has been discarded; clear if block is resident.  
ax - If CF is set ax = segment address of block of memory. 
If CF is clear, ax = 0.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemThreadGrabNB
Performs the same function as **MemThreadGrab** (locks a block and 
increments a semaphore on the block) except that it doesn't block if another 
thread has the semaphore.

**Pass:**  
bx - Handle of block.

**Returns:**  
CF - Set if block has been discarded; clear if block is resident.  
ax - If CF is set, ax = segment address of block of memory. If CF is clear, ax = 0.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemThreadRelease
Releases a thread previously grabbed by **MemThreadGrab**.

**Pass:**  
bx - Handle of block.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MemUnlock
Unlocks a given block of memory by decrementing its lock count. If the lock 
count reaches zero then the block is subject to moving or discarding.

**Pass:**  
bx - Handle of block.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing (flags preserved).  
(If EC checking): Possibly **ds** **or** es will be destroyed. (If segment 
error-checking is on and either **ds** or **es** is pointing to a block 
that has become unlocked, then that register will be set to 
NULL_SEGMENT upon return from this procedure.)

**Library:** heap.def

----------
#### MemUnlockFixedOrMovable
Given a virtual segment, unlocks the corresponding block if the segment is 
movable.

**Pass:**  
bx - Virtual segment.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing (flags preserved).

**Library:** heap.def

----------
#### MemUnlockShared
Unlocks a block that was locked by either **MemLockShared** or 
**MemLockExcl**. 

**Pass:**  
bx - Handle to be unlocked.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing (flags preserved).

**Library:** heap.def

----------
#### MemUnlockV
Unlocks a block and releases a semaphore on that block. (Performs a 
**MemUnlock** and a **HandleV** in that order.)

**Pass:**  
bx - Handle of memory block.

**Returns:**  
bx - Same handle.

**Destroyed:**  
Nothing (flags preserved).

**Library:** heap.def

----------
#### MemUpgradeSharedLock
Upgrades a shared lock to an exclusive lock. If the block is shared by other 
threads this will block and the memory block may move on the heap before 
gaining exclusive access.

**Pass:**  
bx - Handle (locked and shared) whose lock should be upgraded. 
The handle must not be locked more than once by the thread 
calling this routine

**Returns:**  
ds, es - Fixed up to possibly new block location if they were pointing 
to the block upon entry.  
ax - Position of locked block.

**Destroyed:**  
Nothing.

**Library:** heap.def

----------
#### MessageDispatch
Dispatches a passed message without destroying the handle of the message 
(event) to dispatch using **ObjMessage**.

**Pass:**  
bx - Handle of message (event).

di - **MessageFlags**. MF_RECORD in this instance means to 
dispatch but do not destroy the message.

**Returns:**  
ax, cx, dx, bp - As in **ObjMessage**.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### MessageProcess
Processes a message (event) dispatching it via a custom callback routine.

**Pass:**  
bx - Handle of message (event) to dispatch.  
di - Data to pass to callback routine, if any.  
si - Non-zero to preserve event. Zero to destroy it.

**Pass on stack:**  
fptr - Address of callback routine. (Segment is pushed first).

**Callback Routine Specifications:**  
**Passed:**  
(Same as in **ObjMessage** except that **di** is passed through 
from caller.)  
CF - Set if event has stack data.  
ss:[sp+4] - Calling thread. (This address is directly 
above the return address.)  
**Return:**  
Nothing.  
**May Destroy:**  
ax, cx, dx, si, di, bp, ds, es

**Returns:**  
ax, cx, dx, bp - As returned by callback routine.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### MessageSetDestination
Changes an event's destination optr.

**Pass:**  
bx - Event handle (message).  
cx:si - destination.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### MetaGrabFocusExclLow
This routine grabs the focus exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaGrabModelExclLow
This routine grabs the model exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaGrabTargetExclLow
This routine grabs the target exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaReleaseFocusExclLow
This routine releases the focus exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaReleaseFTExclLow
This routine releases the focus and target exclusives for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaRelaseModelExclLow
This routine releases the model exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### MetaReleaseTargetExclLow
This routine releases the target exclusive for the object.

**Pass:**  
*ds:si - Object instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** uiInputC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers to them.

----------
#### NameArrayAdd
Creates an element within a name array and copies the data and name into 
it. If an element with the same name already exists, this routine will not 
create a duplicate; if NAAF_SET_DATA_ON_REPLACE is passed, the newly 
added element will replace the duplicate element.

This routine may resize the LMem block, moving it on the heap and 
invalidating stored segment pointers to it.

**Pass:**  
*ds:si - Name array.  
es:di - Name to add.  
cx - Length of name (0 for null-terminated).  
bx - **NameArrayAddFlags**.  
dx:ax - Data for element.

**Returns:**  
CF - Set if name added.  
ax - Name token.

**Destroyed:**  
Nothing.

**Library:** chunkarr.def

----------
#### NameArrayChangeName
Changes the element's name within the passed name array.

This routine may resize the LMem block, moving it on the heap and 
invalidating stored segment pointers to it.

**Pass:**  
*ds:si - Name array.  
ax - Name token.  
es:di - New name.  
cx - Length of name (0 for null-terminated).

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** chunkarr.def

----------
#### NameArrayCreate
Creates a name array with zero elements. Add elements with 
**NameArrayAdd**.

This routine may resize the LMem block, moving it on the heap and 
invalidating stored segment pointers to it.

**Pass:**  
ds - Block for new array.  
bx - Data size for each element.  
cx - Size for **ChunkArrayHeader**. Default size is zero.  
si - ChunkHandle to use (or 0 if you want to allocate one).  
al - **ObjChunkFlags** to pass to **LMemAlloc**.

**Returns:**  
*ds:si - Name array.

**Destroyed:**  
Nothing.

**Library:** chunkarr.def

----------
#### NameArrayFind

Finds a name element within a name array.

**Pass:**  
*ds:si - Name array.  
es:di - Name to find.  
cx - Length of name (0 for null-terminated).  
dx:ax - Buffer to return data (or zero to not return data).

**Returns:**  
ax - Name token. (CA_NULL_ELEMENT if not found).  
CF - Set if name found.

**Destroyed:**  
Nothing.

**Library:** chunkarr.def

----------
#### ObjBlockGetOutput
Returns the optr of the object set to receive output messages from all objects 
within the object block. (This output optr is stored in an object block's 
**ObjLMemBlockHeader**.)

**Pass:**  
ds - Object block.

**Returns:**  
bx:si - Output optr.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjBlockSetOutput
Sets the optr of the object set to receive output messages from all objects 
within the object block. (This output optr is stored in an object block's 
**ObjLMemBlockHeader**.)

**Pass:**  
ds - Object block.  
bx:si - Output optr.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjCallClassNoLock

Sends a message (invokes a method) of the given class for an object. If the 
message is not resident in the passed class, sends that message on to the 
class' superclass.

This routine assumes that the object block containing the receiving object is 
already locked down and is being run by the same process. It is the 
responsibility of the caller to ensure that this is the case.

**Pass:**  
ax - Message.  
cx, dx, bp - Other data to pass.  
*ds:si - Instance data of object in question; if the receiving object is a 
process **ds** is the core block of the process. **ds** must be 
pointing to an object block, another kind of local memory 
block, or a core block; **ds**:0 must the be the handle of the 
block.  
es:di - Class to call.

**Returns:**  
CF - Clear if no message was called; otherwise, this flag is set by 
the invoked message.  
ax, cx, dx, bp - Return values set by message.  
ds - Pointing to same object block. (The address may be different 
since LMem block may move while locked.)  
bx, si, di, es - Unchanged.

**Message Specifications:**  
**Passed:**  
es - Segment of class called.  
*ds:si - Instance data of object called.  
ds:bx - Instance data of object called (= ***ds:si**).  
ds:di - If class of message handler is in a master 
part, this is the data for master part of 
message. Otherwise, **ds:di** = ***ds:si**.  
cx, dx, bp - Other data.  
ax - Message.  
**Return:**  
ax, cx, dx, bp - Return values of message. If message does 
not return some or all of these registers, 
those not returned may be destroyed.  
**May Destroy:**  
bx, si, di, ds, es (and unused return registers above).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjCallInstanceNoLock
Invokes a message of the given instance's class, fixing up **ds** upon return. 

This routine assumes that the object block containing the receiving object is 
already locked down and is being run by the same process. It is the 
responsibility of the caller to ensure that this is the case.

**Pass:**  
ax - Message to invoke.  
cx, dx, bp - Other data to pass with message.  
*ds:si - Instance data of object to call. **ds** must be pointing to an 
object block, another local memory block, or a core block. (I.e., 
**ds**:0 must be the handle of the block.)

**Returns:**  
CF - Clear if no message was called; otherwise, this flag is set by 
the invoked message.  
ax, cx, dx, bp - Return values set by message.  
ds - Pointing to same object block. (The address may be different 
since LMem block may move while locked.)  
bx, si, di - Unchanged.  
es - If **es** = **ds** upon entry, then **es** is destroyed. Otherwise, **es** is 
unchanged.

**Message Specifications:**  
**Passed:**  
es - Segment of class called.  
*ds:si - Instance data of object called.  
ds:bx - Instance data of object called (= ***ds:si**).  
ds:di - If class of message handler is in a master 
part, this is the data for master part of 
message. Otherwise, **ds:di** = ***ds:si**.  
cx, dx, bp - Other data.  
ax - Message.  
**Return:**  
ax, cx, dx, bp - Return values of message. If message does 
not return some or all of these registers, 
those not returned may be destroyed.  
**May Destroy:**  
bx, si, di, ds, es (and unused return registers above).

**Destroyed:**  
Nothing. (Possibly **es**; see above.)

**Library:** object.def

----------
#### ObjCallInstanceNoLockES
Invokes a message of the given object instance's class, fixing up both **ds** and 
**es** upon return.

This routine assumes that the object block containing the receiving object is 
already locked down and is being run by the same process. It is the 
responsibility of the caller to ensure that this is the case.

**Pass:**  
ax - Message to invoke.  
cx, dx, bp - Other data to pass with message.  
*ds:si - Instance data of object to call. **ds** must be pointing to an 
object block, another local memory block, or a core block. (I.e. 
**ds**:0 must be the handle of the block.)  
es - Pointing to an object block, a local memory bloc, or a core 
block. (I.e. **es**:0 must be the handle of the block.)

**Returns:**  
CF - Clear if no message was called; otherwise, this flag is set by 
the invoked message.  

ax, cx, dx, bp - Return values set by message (if any).  
ds - Pointing to same object block as the **ds** passed. (The address 
may be different since lmem block may move while locked.)  
es - Pointing to same object block as the **es** passed. (The address 
may be different since lmem block may move while locked.)  
bx, si, di - Unchanged.

**Message Specifications:**  
**Passed:**  
es - Segment of class called.  
*ds:si - Instance data of object called.  
ds:bx - Instance data of object called (= ***ds:si**).  
ds:di - If class of message handler is in a master 
part, this is the data for master part of 
message.    Otherwise, **ds:di** = ***ds:si**.  
cx, dx, bp - Other data.  
ax - Message.  
**Return:**  
ax, cx, dx, bp - Return values of message. If message does 
not return some or all of these registers, 
those not returned may be destroyed.  
**May Destroy:**    bx, si, di, ds, es (and unused return registers above).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjCallSuperNoLock
Invokes a message of the given object instance's superclass.

This routine assumes that the object block containing the receiving object is 
already locked down and is being run by the same process. It is the 
responsibility of the caller to ensure that this is the case.

**Pass:**  
ax - Message to invoke.  
cx, dx, bp - Other data to pass with message.  
*ds:si - Instance data of object to call. **ds** must be pointing to an 
object block, another local memory block, or a core block. (I.e. 
**ds**:0 must be the handle of the block.)  
es:di - Class to call superclass of.

**Returns:**  
CF - Clear if no message was called; otherwise, this flag is set by 
the invoked message.  
ax, cx, dx, bp - Return values set by message (if any).  
ds - Pointing to same object block as the **ds** passed. (The address 
may be different since LMem block may move while locked.)  
bx, si, di, es - Unchanged.

**Message Specifications:**  
**Passed:**  
es - Segment of class called.  
*ds:si - Instance data of object called.  
ds:bx - Instance data of object called (= ***ds:si**).  
ds:di - If class of message handler is in a master 
part, this is the data for master part of 
message.    Otherwise, **ds:di** = ***ds:si**.  
cx, dx, bp - Other data useful to message.  
ax - Message.  
**Return:**  
ax, cx, dx, bp - Return values of message. If message does 
not return some or all of these registers, 
those not returned may be destroyed.  
**May Destroy:**  
bx, si, di, ds, es - (and unused return registers above).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjCompAddChild
Adds a child object to the composite field of another, composite object.

**Pass:**  
*ds:si - Instance data of composite object.  
cx:dx - Object to add as child.  
bp - **CompChildFlags** to specify desired child location. Use the 
CCF_MARK_DIRTY field to mark chunks as dirty.  
bx - Offset to master instance offset to part containing LinkPart 
and CompPart fields.  
ax - Offset to field of type "LinkPart" in instance data.  
di - Offset to field of type "CompPart" in instance data.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
ax, bx, di, bp.

**Library:** metaC.def

----------
#### ObjCompFindChild
Pass a message to the next sibling of a linkable object.

**Pass:**  
*ds:si - Object.  
cx: dx - Optr of child object, or to find the *n*th child let cx be zero and 
**dx** the number *n* of the child to find (first child is zero).  
ax - Offset to field of type "LinkPart" in instance data.  
bx - Offset to master instance offset to part containing LinkPart 
and CompPart.  
di - Offset to field of type "CompPart" in instance data.

**Returns:**  
CF - Set if not found, clear otherwise.  
bp - If child found, this is the child's position (first child is zero). If 
child not found, this register holds the total number of 
children.  
cx:dx - If child found, OD of child. If child not found and you were 
searching for an OD, then these registers will be unchanged. 
If child not found and you were searching for a child by 
position, then **cx** will be unchanged and **dx** will be equal to 
the passed child number minus the total number of children.

**Destroyed:**  
Nothing.

**Library:** metaC.def

----------
#### ObjCompMoveChild
This routine performs a MSG_MOVE_CHILD for a composite object.

This routine is used to move a child to a different location in the list of 
children. The child is not physically moved, rather the nextSibling pointers 
(and possibly the composite's firstChild pointer) are changed. The child to be 
moved must be a child of the composite (or else a fatal error will be generated 
in the Error Checking system). The location to add the child is determined by 
the flags and the reference child passed.

**Pass:**  
*ds:si - Object.  
cx: dx - Optr of child object.  
ax - Offset within master group instance data to "LinkPart" in the 
child.  
bx - Offset of master group pointer in composite and child's base 
structure.  
di - Offset within master group instance data to CompPart in the 
composite.  
bp - **CompChildOptions** to specify target position.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
ax, bx, di.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjCompProcessChildren
This routine processes the children of a composite object via a callback 
routine or via several predefined callback routines.

The callback routine is called for each child in order with all passed registers 
preserved except **bx**. The callback routine returns the carry set to end 
processing at this point.

**Pass:**  
*ds:si - Object.  
bx - Offset of master group pointer in composite and child's base 
structure.  
di - Offset within master group instance data to CompPart in the 
composite.  
ax, cx, dx, bp - Parameters to pass to callback routine. If using an 
**ObjCompCallType** instead of a custom routine, then ax is 
the message to send to children.

**Pass on stack:**  
(Pushed in this order)  
optr - Object descriptor of initial child to process (or zero to start at 
composite's nth child, where n is stored in the chunk half of 
the optr).  
word - Offset to field of type LinkPart in instance data.  
fptr - Address of callback routine (segment pushed first), or if 
segment is zero then offset is an **ObjCompCallType**. This 
field will be popped off of stack on return.

**Returns:**  
Callback routine popped off of stack.  
CF - Set if call aborted in the middle.  
ax, cx, dx, di, bp - Returned with callback routine's changes.  
ds - Pointing at same block (could have moved).  
es - Untouched (i.e. isn't fixed up, even if it points at a block that 
might have moved).

**Destroyed:**  
di.

**Callback Routine Specifications:**  
**Passed:**  
*ds:si - Child object.  
*es:di - Composite object.  
ax, cx, dx, bp - Data.  
**Return:**  
CF - Set to end processing.  
ax, cx, dx, bp - Data to send to next child.  
**May Destroy:**  
bx, si, di, ds, es.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjCompRemoveChild
This routine performs a MSG_REMOVE_CHILD for a composite object.

This routine is used to remove a child from a composite. The child to be 
removed must be a child of the composite (The error checking system will 
generate a fatal error otherwise.). the child is not destroyed and is not sent 
any notification that it is being removed.

**Pass:**  
*ds:si - Object.  
cx: dx - Optr of child object.  
ax - Offset within master group instance data to "LinkPart" in the 
child.  
bx - Offset of master group pointer in composite and child's base 
structure.  
di - Offset within master group instance data to CompPart in the 
composite.  
bp - **CompChildFlags**. Set CCF_MARK_DIRTY to mark chunks as 
dirty.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
ax, bx, di.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjDecInUseCount
Decrements the in-use count for an object block, stored in the 
**ObjLMemBlockHeader** structure at the from of an object block. The in-use 
count ensures that an object block being used is not freed prematurely.

**Pass:**  
ds - Object block.  
si - Chunk handle of object in block that is decrementing the 
count. (In EC code, this is used to keep track of counts on a 
per-object basis.)

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjDecInteractibleCount
Decrements the interactible count of the passed object block. This count 
quantifies the number of objects in the block that are currently interactible 
with the user.

**Pass:**  
ds - Object block.  
si - Chunk handle of object in block that is decrementing the 
count. (In EC code, this is used to keep track of counts on a 
per-object basis.)

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjDoRelocation

Relocates a single piece of data (word or double word) within an object block. 

**Pass:**  
al - **ObjRelocationType**.  
bx - Handle of block to perform relocation operation.  
cx - Low word of relocation data.  
dx - High word of relocation data. (This is only used if the 
**ObjRelocationType** is RELOC_ENTRY_POINT.)

**Returns:**  
CF - Set if error is encountered.  
cx - Low word relocated.  
dx - High word relocated (unless **ObjRelocationType** was not 
RELOC_ENTRY_POINT, in which case **dx** is unchanged.)

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjDoUnRelocation
Unrelocates a single piece of data (word or double word) within an object 
block.

**Pass:**  
al - **ObjRelocationType**.  
bx - Handle of block to perform relocation operation.  
cx - Low word of relocation data.  
dx - High word of relocation data. (This is only used if the 
**ObjRelocationType** is RELOC_ENTRY_POINT.)

**Returns:**  
CF - Set if error is encountered.  
cx - Low word unrelocated.  
dx - High word unrelocated (unless **ObjRelocationType** was 
not RELOC_ENTRY_POINT, in which case dx is unchanged.)

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjDuplicateMessage
Duplicates an encapsulated message (event), returning a copy of the event.

**Pass:**  
bx - Message to duplicate.

**Returns:**  
ax - Duplicate message (event).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjDuplicateResource
Duplicates an object resource block (and any objects and chunks within that 
object block), returning the handle of the newly-created block. 

**Pass:**  
bx - Resource block handle to duplicate.  
ax - Handle of geode to own block.  
 - Zero to have block owned by geode running current thread.  
 - -1 to copy owner from source block.  
cx - Handle of thread to run new block.  
 - Zero to have block run by current thread.  
 - -1 to copy nature of thread from source block.  
 - (If source is process-driven, duplicated block will be 
process-driven. If source is ui-driven, duplicated block will be 
ui-driven. If source is run by anything else, that same thread 
will run the new thread.)

**Returns:**  
bx  Handle of duplicated block.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjEnableDetach
Acknowledge detach for an object.

**Pass:**  
*ds:si - Object.

**Returns:**  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them

----------
#### ObjFreeChunk
Frees a chunk within an object block. (Chunks within resources will remain, 
with their size resized to zero.)

**Pass:**  
*ds:ax - Chunk to free.

**Returns:**  
Nothing.

**Destroyed:**  
ax

**Library:** object.def

----------
#### ObjFreeDuplicate
Frees a block created by ObjDuplicateResource or saved with 
ObjSaveBlock. 

**Pass:**  
bx - Handle of block to free.

**Returns:**  
Nothing.

**Destroyed:**  
bx

**Library:** object.def

----------
#### ObjFreeMessage
Frees an event handle (and the event attached to that handle).

**Pass:**  
bx - Event handle.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjFreeObjBlock
Frees an object block. Object blocks created with **ObjDuplicateBlock** or 
**ObjSaveBlock** should use **ObjFreeDuplicate** instead.

**Pass:**  
bx - Object block.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjGetFlags
Returns the **ObjChunkFlags** associated with an object block's chunk.

**Pass:**  
ds - Object block.  
ax - Chunk.

**Returns:**  
al - **ObjChunkFlags**.  
ah - Zero.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjGetMessageInfo
Returns information about an event handle.

**Pass:**  
bx - Event handle.

**Returns:**  
ax - Message number.  
cx:si - Destination optr.  
CF - Set if event contains stack data, clear if event contains 
register data.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjGotoSuperTailRecurse
This is an optimized version of **ObjCallSuperNoLock** that only works in 
the case of tail recursion.

**Pass:**  
ax - method number to call  
cx, dx, bp - other data to pass  
ds:*si - instance data to pass (**si** is lmem handle) or **ds** = core block 
of process. The **ds** register must point to an object block, 
other local memory block, or a core block - **ds**:0 must be the 
handle of the block.  
es:di - class to call superclass of

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjIncDetach
Increment the acknowledge count for a detaching object.

**Pass:**  
*ds:si - Object.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** metaC.def

----------
#### ObjIncInUseCount
Increments the in-use count for an object block, stored in the 
**ObjLMemBlockHeader** structure at the front of an object block. The in-use 
count ensures that an object block being used is not freed prematurely.

**Pass:**  
ds - Object block.  
si - Chunk handle of object in block that is incrementing the 
count. (In EC code, this is used to keep track of counts on a 
per-object basis.)

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjIncInteractibleCount
Increments the interactible count of the passed object block. This count 
quantifies the number of objects in the block that are currently interactible 
with the user.

**Pass:**  
ds - Object block.  
si - Chunk handle of object in block that is incrementing the 
count. (In EC code, this is used to keep track of counts on a 
per-object basis.)

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjInitDetach
Prepare to detach an object.

**Pass:**  
*ds:si - Object.  
dx:bp - optr to receive MSG_META_SHUTDOWN_ACK.  
ax - Message provoking this call (MSG_META_DETACH or 
MSG_META_APP_SHUTDOWN).  
cx - Caller ID; an identifier token for the caller.

**Returns:**  
ds  Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them

----------
#### ObjInitializeMaster
Initializes a master part of an object.

**Pass:**  
*ds:si - Object.  
es:di - Class of part to initialize.

**Returns:**  
CF - Set.  
ds - Possibly changed.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjInitializePart
Ensures that an object is expanded, and initialized if necessary, for all master 
parts down through the part passed. This routine sends 
MSG_META_RESOLVE_VARIANT_SUPERCLASS to any master parts above the 
one passed, if that variable class had not yet been determined.

This routine may resize any LMem and/or object blocks, moving them on the 
heap and invalidating stored segment pointers to them.

**Pass:**  
*ds:si - Object.  
bx - Offset to the part to build.

**Returns:**  
ds - Possibly changed.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjInstantiate
Instantiates (creates) an object of the passed class, allocating a chunk for the 
object, initializing the chunk to zeroes, filling in the class pointer and passing 
MSG_PROCESS_INSTANTIATE to the object (if it has no master classes).

If the object block is run by a different process, instantiation is done via a 
remote call.

**Pass:**  
es:di - Class to instantiate a new object.  
bx - Handle of block in which to instantiate the object.

**Returns:**  
si - Chunk handle to the new object  
ds - Updated to point at same segment as on entry.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjIsClassADescendant
Test whether a given class is a subclass of another specified class.

**Pass:**  
ds:si - Class pointer to the potential ancestor class.  
es:di - Class pointer to the potential descendant class.

**Returns:**  
CF - Set if class in **es:di** is a descendant of the class in **ds:si**.
Clear otherwise.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjIsObjectInClass
Tests whether or not an object is of a given class. If a variant class is 
encountered, the object will not be grown out past that class in the search. 

If you wish to do a complete search past any variant classes, send the object 
MSG_META_DUMMY first.

**Pass:**  
*ds:si - Object.  
es:di - Class.

**Returns:**  
CF - Set if object is in the given class.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjLinkCallNextSibling
Pass a message to the next sibling of a linkable object.

**Pass:**  
*ds:si - Object.  
ax - Message to call.  
cx, dx, bp - Parameters for message.  
bx - Offset to master class pointer.  
di - Offset into master part where LinkPart is.

**Returns:**  
CF - Clear if not method routine called; otherwise set by message 
handler.  
ax, cx, dx, bp - Return value of message, if any.  
bx, si, di, es - Unchanged.  
ds - Updated to point at segment of same block as on entry.

**Destroyed:**  
Nothing.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjLinkCallParent
Pass a message to the parent of a linkable object.

**Pass:**  
*ds:si - Object.  
ax - Message to call.  
cx, dx, bp - Parameters for message.  
bx - Offset to master class pointer.  
di - Offset into master part where LinkPart is.

**Returns:**  
CF - Clear if not method routine called; otherwise set by message 
handler.  
ax, cx, dx, bp - Return value of message, if any.  
bx, si, di, es - Unchanged.  
ds - Updated to point at segment of same block as on entry. the 
address could be different since local memory blocks can 
move while locked.

**Destroyed:**  
Nothing.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjLinkFindParent
Pass a method to the next sibling of a linkable object.

**Pass:**  
*ds:si - Object.  
bx - Offset to master class pointer.  
di - Offset into master part where LinkPart is.

**Returns:**  
bx:si - Parent object, or zero if none.  
ds - Unchanged.

**Destroyed:**  
Nothing.

**Library:** metaC.def

**Warning:**  
This routine may resize LMem or object blocks, moving them on the heap and 
invalidating stored segment pointers and current register or stored offsets to 
them.

----------
#### ObjLockObjBlock
Locks an object block, loading in the resource if necessary. If the block is an 
LMem heap but is not an object block, this routine acts like **MemLock**.

**Pass:**  
bx - Handle of block.

**Returns:**  
ax - Segment.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjMapSavedToState
Maps a saved/duplicated block to its corresponding VM block handle in the 
process' state file.

**Pass:**  
bx - Process handle (or 0 for current thread's process).

**Returns:**  
CF - Clear if block is found. Set if no such block appears on a 
process' saved block list.  
ax - VM block handle (if block found).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjMapStateToSaved
Maps a VM block ID from a state file to the corresponding memory block 
handle for a process.

**Pass:**  
ax - VM block handle.  
bx - Process handle (or 0 for current thread's process).

**Returns:**  
CF - Clear if block is found. Set if no such block appears on a 
process' saved block list.  
bx - (If block is found) Memory block handle.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjMarkDirty
Register-saving routine to mark an object dirty.

**Pass:**  
*ds:si - Chunk in object block to mark dirty.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjMessage
Sends a message to an object.

**Pass:**  
bx:si - Destination for message. In most cases, this is the optr of the 
object to receive the message; this destination may also be a 
process, in which case bx = process ID and si contains other 
data.  
di - **MessageFlags**. (If MF_CUSTOM is passed, a fptr to a 
callback routine is pushed on the stack. The routine must be 
locked in memory for the duration of the **ObjMessage**.)  
ax - Message.  
cx - Event word 0.  
dx - Event word 1.  
bp - Event word 2.

**Returns:**  
di - MESSAGE_NO_ERROR if no error is encountered; otherwise 
**MessageError**.  
 - (If MF_CUSTOM was passed, the custom routine will be popped off the stack.)  
 - (If MF_CALL was passed, **ax, cx, dx, bp**, and CF will contain return 
values.)

**Destroyed:**  
Nothing.

**Message Specifications:**  
**Passed:**  
es - Segment of class called.  
*ds:si - Instance data of object called. (If class is a 
subclass of ProcessClass **ds** = dgroup of 
process and **si** = other data passed by caller.)  
ds:bx - Instance data of object called (= ***ds:si**).  
ds:di - If the class of the message handler is in a 
master part, this is the data for master part 
of message. Otherwise, **ds:di** = ***ds:si**.  
cx, dx, bp - Other data useful to message.  
ax - Message.  
**Return:**  
ax, cx, dx, bp - Return values of message. If message does 
not return some or all of these registers, 
those not returned may be destroyed.  
**May Destroy:**  
bx, si, di, ds, es (and unused return registers above).

**Library:** object.def

----------
#### ObjProcBroadcastMessage
Broadcasts an event to all threads with event queues.

**Pass:**  
bx - Encapsulated message (event) to broadcast.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjRelocOrUnRelocSuper
Relocate or unrelocate an object's superclass structures and pointers.

**Pass:**  
*ds:si - Segment:Chunk handle of the object's instance chunk.  
bp - Inherited variables.  
es:di - Class pointer to the object's class.

**Returns:**  
CF - Set if error, clear otherwise.

**Destroyed:**  
ax, dx, dx

**Library:** object.def

----------
#### ObjResizeMaster
Resizes a master class part of an object.

**Pass:**  
*ds:si - Object.  
bx - Offset to master part to expand.  
ax - New size for master part.

**Returns:**  
ds  Possibly changed.

**Destroyed:**  
ax

**Library:** object.def

----------
#### ObjSaveBlock
Sets up an LMem block to be saved to its owner's state file.

**Pass:**  
bx - Handle of block to be saved. This block must be an LMem 
block and have LMF_HAS_FLAGS set in its LMBH_flags word 
(and contain a corresponding flags chunk).

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjSetFlags
Sets the object flags (**ObjChunkFlags**) associated with a chunk.

**Pass:**  
ax - Chunk.  
bl - ObjChunkFlags to set.  
bh - ObjChunkFlags to clear.  
ds - Object block.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjSwapLock
This utility routine locks a new object block and saves the old object's block 
handle. This is useful when using **ObjCallInstanceNoLock** is much more 
desirable than using **ObjMessage** for repeated operations; for example, if an 
object needs to send 5 messages to an object, it might be faster to lock that 
object and use **ObjCallInstanceNoLock**.

**Pass:**  
ds - Segment of object 1.  
bx - Block handle of object 2.

**Returns:**  
ds - Segment of object 2 (now locked, if different from object 1).  
bx - Block handle of object 1.

**Destroyed:**  
Nothing. Flags preserved.

**Library:** object.def

----------
#### ObjSwapLockParent
This utility routine locks the parent of an object and saves the child's block 
handle. This is useful when using **ObjCallInstanceNoLock** is much more 
desirable than using **ObjMessage** for repeated operations; for example, if an 
object needs to send 5 messages to its parent, it might be faster to lock the 
parent object and use **ObjCallInstanceNoLock**.

**Pass:**  
*ds:si - Object.  
bx - Master offset.  
di - Offset to linkage part.

**Returns:**  
CF - Set if successful; otherwise, object is not linked to a parent.  
*ds:si - Instance data of parent object. (**si** = 0 if no parent is 
encountered.)  
bx - Block handle of original object, which is still locked.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjSwapUnlock
This utility routine swaps a locked object block, unlocking it in the process, 
with a new object block.

**Pass:**  
ds - Segment of object 2.  
bx - Block handle of object 1 (which must be locked).

**Returns:**  
ds - Segment of object 1.  
bx - Block handle of object 2.

**Destroyed:**  
Nothing. Flags preserved.

**Library:** object.def

----------
#### ObjTestIfObjBlockRunByCurThread
Determines if the current running thread owns a given object block. 

**Pass:**  
bx - Handle of object block. (If **bx** is a VM block, then the thread 
which runs the VM file is checked.)

**Returns:**  
ZF - Set if current thread is the same thread specified running the 
object block. The block may be locked, unlocked, and sent 
messages using any routines available by the current thread. 
Clear if the block is inaccessible by the current thread. 
(**ObjMessage** must be called to communicate with any 
objects in the block.)

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarAddData
Adds a new vardata entry or replaces the existing data within an entry (with 
zeroed data). This routine returns a pointer to the extra data section of the 
vardata entry in order to allow you to initialize this data immediately.

**Pass:**  
*ds:si - Object to add vardata entry (or replace an entry).  
ax - Vardata type (with VDF_SAVE_TO_STATE set correctly by the 
caller).  
cx - Size of extra data. (cx = zero if no extra data).

**Returns:**  
ds:bx - (If object has extra data, pointer to the extra data; otherwise, 
an opaque pointer which may be passed to 
**ObjVarDeleteDataAt**.)  
Object is marked dirty even if vardata entry field previously existed.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarCopyDataRange
Copies a group of vardata entries (matching the specified range values) from 
one object into another object. You can pass an identical start and end 
vardata type value to copy a single vardata entry from one object another.

**Pass:**  
*ds:si - Source object to copy vardata entries from.  
*es:bp - Destination object to copy vardata entries into.  
cx - Smallest vardata value to copy (inclusive). Any 
**VarDataFlags** are ignored.  
dx - Largest vardata value to copy (inclusive). Any 
**VarDataFlags** are ignored.

**Returns:**  
ds, es - Updated segment addresses of blocks.  
Destination object is marked dirty if any entries are copied.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarDeleteData
Deletes a specified vardata entry field and associated extra data (if any) 
within an object.

**Pass:**  
*ds:si - Object to delete vardata entry from.  
ax - Vardata type to delete. (**VarDataFlags** ignored.)

**Returns:**  
CF - Set if vardata entry not found, else clear if data deleted.  
ds - Updated segment of object block.  
Object is marked dirty (if data field is found and deleted).

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarDeleteDataAt
Deletes a vardata entry field (specified at by the passed opaque pointer).

**Pass:**  
*ds:si - Object to delete vardata entry from.  
ds:bx - Opaque pointer as returned by **ObjVarAddData**, 
**ObjVarFindData**, or **ObjVarDerefData**.

**Returns:**  
Object is marked dirty.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarDeleteDataRange
Deletes a group of vardata entries (matching the specified range values). You 
may also specify that you only wish to delete vardata entries that are not 
marked VDF_SAVE_TO_STATE.

**Pass:**  
*ds:si - Object to delete vardata entries from.  
cx - Smallest vardata value to delete (inclusive). Any 
**VarDataFlags** are ignored.  
dx - Largest vardata value to delete (inclusive). Any 
**VarDataFlags** are ignored.  
bp - Zero to delete all data entries within the passed range values; 
if non-zero, routine will only delete vardata entries that are 
both within the passed range and are not marked 
VDF_SAVE_TO_STATE. 

**Returns:**  
Object is marked dirty if any vardata entries are deleted.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarDerefData
Returns either a pointer to a vardata entry's extra data section or an opaque 
pointer to the vardata entry type passed. (If there is no extra data, it returns 
a pointer to the data entry + offset *VDI_extraData*. This is used as an opaque 
pointer in such routines as **ObjVarDeleteDataAt**)

**Pass:**  
*ds:si - Object in which to return opaque pointer to vardata data 
section.  
ax - Vardata type. (**VarDataFlags** ignored.)

**Returns:**  
ds:bx - If entry contains extra data, pointer to the extra data section 
of the vardata entry; otherwise, **ds:bx** is an opaque pointer 
which may be passed to **ObjVarDeleteDataAt**.

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarFindData
Searches an object's vardata section for a given vardata type. If found, this 
routine returns a pointer to the appropriate vardata section (or an opaque 
pointer if there is no extra data; this opaque pointer should be used before 
performing any LMem operations on the block containing the object.)

**Pass:**  
*ds:si - Object to search vardata section for the particular data type.  
ax - Vardata type. (**VarDataFlags** ignored.)

**Returns:**  
CF - Set if vardata type is found; otherwise clear.

ds:bx - If vardata entry contains extra data, **ds:bx** returns 
containing a pointer to the extra data; otherwise, **ds:bx** 
returns containing an opaque pointer which may be passed to 
**ObjVarDeleteDataAt**. (This opaque pointer actually points 
to the location of the vardata entry + VDI_extraOffset.)

**Destroyed:**  
Nothing.

**Library:** object.def

----------
#### ObjVarScanData
Scans an object's vardata and calls all pertaining routines listed in a "vardata 
handler" table.

**Pass:**  
*ds:si - Object to scan vardata fields.  
ax - Number of **VarDataHandler** structures in table.  
es:di - Pointer to a list of **VarDataHandler** structures. The handler 
routines must be far routines in the same segment as the 
handler table.  
cx, dx, bp - Data to pass to vardata handlers.

**Returns:**  
cx, dx, bp - Data returned after passing through handlers.  
ds - Updated segment address of object.

**Destroyed:**  
Nothing.

**VarData Handler Routine Specifications:**  
**Passed:**  
*ds:si - Object.  
ds:bx - Extra data of vardata entry in question; 
otherwise an opaque pointer to the start of 
vardata entry + size vardata entry.  
ax - Vardata type.  
cx, dx, bp - Data to pass to **VarDataHandler**.  
**Return:**  
ds - Updated segment for object.  
cx, dx, bp - Returned data from **VarDataHandler**.  
**May Destroy:**  
ax, bx, si, di, es

**Library:** object.def

----------
#### ParserAddDependencies
Adds a set of dependencies from a dependency block.

**Pass:**  
bx - Handle of the dependency block.  
ss:bp - Pointer to **DependencyParameters** on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF is set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserAddSingleDependency
Adds a single dependency to a cell.

**Pass:**  
ds:si - **CellFunctionParameters**.  
ax - Row of cell to add dependency to.  
cx - Column of cell to add dependency to.  
ss:bp - **DependencyParameters**.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF is set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserErrorMessage
Returns a text-based error message string, when passed a 
**ParserScannerEvaluatorError**.

**Pass:**  
ds:si - Buffer to place the error message string.  
al - ParserScannerEvaluatorError

**Returns:**  
cx - Length of the error message (not including the null).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserEvalExpression
Evaluates a stream of parser tokens.

**Pass:**  
ds:si - Pointer to parsed expression.  
es:di - Pointer to the base of a scratch buffer. This buffer consists of 
two stacks. The argument stack grows down from the top of 
the buffer and the operator/function stack grows up from the 
bottom of the buffer. The two stacks should not collide. If they 
do, an error is reported.  
cx - Size of scratch buffer. This size must be large enough to avoid 
collisions between the argument stack and the 
operator/function stack. (See above.)  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set if a "serious" error occurs. If a non-serious error occurs, 
then the evaluator argument stack will contain the error 
token.  
al - (If CF is set): **ParserScannerEvalError** code.  
es:bx - Pointer to the evaluated stream.  
ss:[bp].*EP_depHandle* - If generating dependencies, then this holds the block handle 
of the locked block containing the list of cells, ranges, names, 
and functions that the expression depends on.

**Destroyed:**  
ah

**Library:** parse.def

----------
#### ParserEvalForeachArg
Calls a callback routine for each argument within an argument stack.

**Pass:**  
es:bx - Pointer to argument stack.  
cx - Number of arguments.  
ss:bp - Pointer to **EvalParameters** structure on the stack.  
ax:si - Pointer to callback routine.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF is set): Error code.

**Destroyed:**  
ax

**Callback Routine Specifications:**  
**Passed:**  
es:bx - Pointer to argument on the stack.  
cx - Argument number (zero-based).  
**Return:**  
CF - Set on error.  
 - (If CF is set):  **al** = error code.

**Library:** parse.def

----------
#### ParserEvalPopNArgs
Pops a number of arguments off the argument stack. It is important to note 
that this routine does not perform any sort of destructive acts to the 
argument stack.

**Pass:**  es:bx - Pointer to top of argument stack.  

ss:bp - Pointer to **EvalParameters** structure on the stack.  
cx - Number of arguments to pop off.

**Returns:**  
es:bx - Pointer to new top of argument stack.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserEvalPropagateEvalError
Propagates an error up the argument stack.

**Pass:**  
es:bx - Pointer to the argument stack.  
es:di - Pointer to the operator stack.  
cx - Number of arguments to pop.  
al - Error code to put on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
es:bx - New pointer to top of argument stack.  
al - Error code.

**Destroyed:**  
ax.

**Library:** parse.def

----------
#### ParserEvalPushArgument

Pushes an argument onto the argument stack.
**Pass:**  
es:bx - Pointer to the argument stack.  
es:di - Pointer to the operator stack.  
al - Type of item (**EvalArgumentType**).  
cx - Additional size to allocate beyond which would normally be 
assumed for this item.  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
es:bx - New pointer to top of argument stack. (This points to the 
allocated item.)  
al - (If CF set): Error code.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserEvalPushCellReference
Pushes a cell reference on the argument stack.

**Pass:**  
ds:si - Pointer to **ParseTokenCellData**.  
es:di - Pointer to top of operator stack.  
es:bx - Pointer to top of argument stack.  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
si - Pointer past the **ParserTokenCellData**.the allocated item.)  
al - (If CF set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserEvalPushNumericConstant
Pushes a numeric constant on the argument stack.

**Pass:**  
ds:si - Pointer to **ParseTokenNumberData**.  
es:di - Pointer to top of operator stack.  
es:bx - Pointer to top of argument stack.  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
si - Pointer past the **ParserTokenNumberData**.the allocated 
item.)  
al - (If CF set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserEvalPushNumericConstantWord
Pushes a word-length numeric constant onto the argument stack.

**Returns:**  
es:di - Pointer to top of operator stack.  
es:bx - Pointer to top of argument stack.  
ss:bp - Pointer to **EvalParameters** structure on the stack.  
cx - Word value to push.

**Returns:**  
es:bx - New argument stack.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserEvalPushRange
Pushes a range on the argument stack.

**Pass:**  
ds:si - Pointer to **EvalRangeData**.  
es:di - Pointer to top of operator stack.  
es:bx - Pointer to top of argument stack.  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserEvalPushStringConstant
Pushes a string constant on the argument stack.

**Pass:**  
ds:si - Pointer to string data.  
cx - Size of the string.  
es:di - Pointer to top of operator stack.  
es:bx - Pointer to top of argument stack.  
ss:bp - Pointer to **EvalParameters** structure on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserEvalRangeIntersection
Implements the range intersection operator on two passed ranges.

**Pass:**  
ds:si - Pointer to first range. This range must contain absolute 
values (i.e. $A$1).  
es:di - Pointer to second range. This range must also contain 
absolute values (i.e. $A$1).

**Returns:**  
es:di - Intersection of the two ranges, in absolute values.  
CF - Set on error.  
al - (If CF is set): Error code. (This is always 
PSEE_ROW_OUT_OF_RANGE or 
PSEE_COLUMN_OUT_OF_RANGE.)

**Destroyed:**  
ax

**Library:** parse.def

----------
#### ParserForeachPrecedent
Calls a routine for each entry within a precedent list. (Precedents are the 
actual cells that an expression depends on.)

**Pass:**  
bx - Block.  
di:dx - Callback routine.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF is set): Error code.

**Destroyed:**  
ax

**Callback Routine Specifications:**  
**Passed:**  
cx, ds, si, bp - Same as passed in.  
dl - Type of precedent.  
es:di - Pointer to the precedent data.  
**Return:**  
CF - Set to abort continuation.  
al - (If CF is set): Error code.  
**May Destroy:**  
Nothing.

**Library:** parse.def

----------
#### ParserForeachReference
Calls a routine for each reference within the given expression. (References 
are the cells that are referred to in the expression; this may be either a cell 
reference or a name.)

**Pass:**  
es:di - Pointer to the expression.  
cx:dx - Callback routine.  
ss:bp - Arguments to the callback routine.  
ds:si - Other arguments to the callback routine.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Callback Routine Specifications:**  
**Passed:**  
es:di - Pointer to the cell reference.  
ss:bp - Passed parameters.  
ds:si - Other passed parameters.  
al - Type of reference:  
 - PARSER_TOKEN_CELL  
 - PARSER_TOKEN_NAME  
**Return:**  
Nothing.  
**May Destroy:**  
Nothing.

**Library:** parse.def

----------
#### ParserForeachToken
Calls a routine for each token within the given expression. (A token is a 
distinct, separate element within an expression; e.g. a number, operator, 
function, etc.)

**Pass:**  
es:di - Pointer to the expression.  
cx:dx - Callback routine.  
ss:bp - Arguments to the callback routine.  
ds:si - Other arguments to the callback routine.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Callback Routine Specifications:**  
**Passed:**  
es:di - Pointer to the cell reference.  
ss:bp - Passed parameters.  
ds:si - Other passed parameters.  
al - Type of reference:  
 - PARSER_TOKEN_CELL  
 - PARSER_TOKEN_NAME  
**Return:**  
Nothing.  
**May Destroy:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatCellReference
Formats a single cell reference of the form AB123.

**Pass:**  
ax - Row of cell.  
cx - Column of cell.  
es:di - Pointer to buffer (MAX_CELL_REF_SIZE or larger).

**Returns:**  
es:di - String (null-terminated).  
cx - Length of string (without null-terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatColumnReference
Formats a column reference in the form "AB."

**Pass:**  
ax - Column number (zero-based) to format.  
es:di - Pointer to buffer to place text.  
cx - Size of buffer.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatExpression
Formats a parsed expression into a text string.

**Pass:**  
ds:si - Pointer to the parsed expression.  
es:di - Pointer to buffer to place the text.  
ss:bp - Pointer to **FormatParameters**.

**Returns:**  
cx - Length of the text (not including the null-terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatRangeReference
Formats a multiple (range) cell reference of the form AB123:CD456.

**Pass:**  
ax - Row of starting cell.  
cx - Column of starting cell.  
dx - Row of ending cell.  
bx - Column of ending cell.  
es:di - Pointer to buffer.

**Returns:**  
es:di - String (null-terminated).  
cx - Length of string (without null-terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatRowReference
Formats a row reference in the form "123."

**Pass:**  
ax - Row number (zero-based) to format.  
es:di - Pointer to buffer to place string (of MAX_REFERENCE_SIZE 
or larger).  
cx - Size of buffer.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserFormatWordConstant
Formats a word constant.

**Pass:**  
ax - Number to format.  
es:di - Pointer to buffer to place string (of MAX_REFERENCE_SIZE 
or larger).  
cx - Size of buffer.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserGetFunctionArgs
Returns the arguments of a specified parser function. The arguments are 
stored as a text string within the passed buffer.

**Pass:**  
cx - Item number.  
ax - **FunctionType** to match.  
es:di - Buffer to place string.

**Returns:**  
cx - Number of characters (not including null terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserGetFunctionDescription
Returns a description of a specified parser function. The description string is 
stored in the passed buffer.

**Pass:**  
cx - Item number.  
ax - **FunctionType** to match.  
es:di - Buffer to place string.

**Returns:**  
cx - Number of characters (not including null terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserGetFunctionMoniker
Returns the name of the specified parser function.

**Pass:**  
cx - Item number.  
ax - **FunctionType** to match.  
es:di - Buffer to place string.

**Returns:**  
cx  Number of characters (not including null terminator).

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserGetNumberOfFunctions
Returns the number of parser functions matching a particular function type.

**Pass:**  
ax - **FunctionType** to match.

**Returns:**  
cx - Number of functions of type **FunctionType**.

**Destroyed:**  
Nothing.

**Library:** parse.def

----------
#### ParserLocalizeFormats
Re-initialize localization information.

**Pass:**  
Nothing.

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

Library: parse.def

----------
#### ParserParseString
Parses a string.

**Pass:**  
ds:si - Pointer to text to perform the parse operation.  
es:di - Buffer to place parsed data.  
ss:bp - Pointer to **ParserParameters** structure on the stack.

**Returns:**  
CF - Set on error; clear otherwise.  
al - **ParserScannerEvaluatorError**.  
cx, dx - Range of text where the error was encountered.  
es:di - Pointer past the last token written.

**Destroyed:**  
ah

**Library:** parse.def

----------
#### ParserRemoveDependencies
Removes a set of dependencies from a dependency block.

**Pass:**  
bx - Handle of the dependency block.  
ss:bp - Pointer to **DependencyParameters** on the stack.

**Returns:**  
CF - Set on error; otherwise clear.  
al - (If CF is set): Error code.

**Destroyed:**  
ax

**Library:** parse.def

----------
#### PrefTestVideoDevice
Checks if the selected video driver is available on the machine.

**Pass:**  
bx:si - Handle of the **PrefDeviceList**.

**Returns:**  
CF - Set if device is unavailable, clear if available or if it is 
indeterminate whether the device is available.  
ax - (If CF clear): **DisplayType** (in **al**, 0 in ah**)**.  
 - (If CF set): 0 if driver is definitely not present or 
**GeodeLoadError**+1 if the driver couldn't be loaded for 
some reason.

**Destroyed:**  
cx, dx, di

**Library:** config.def

----------
#### ProcCallFixedOrMovable
Calls the routine specified by the passed virtual far pointer.

**Pass:**  
ax - Offset of routine.  
bx - Virtual segment. (Together bx and ax form a virtual far 
pointer.)

**Returns:**  
From called routine.

**Destroyed:**  
All registers returned by called routine will be returned to the caller of 
**ProcCallFixedOrMovable**.

**Library:** resource.def

----------
#### ProcCallModuleRoutine
Calls a process' routine in another code resource. The stack usage of this 
routine is guaranteed; the routine called will return two words of the return 
address on the stack followed by any parameters that the caller may have 
pushed.

**Pass:**  
ax - Offset to routine.  
bx - Virtual segment of routine. (Together bx and ax form a 
virtual far pointer.)

**Returns:**  
From called routine.

**Destroyed:**  
All registers returned by called routine will be returned to the caller of 
**ProcCallModuleRoutine**.

**Library:** resource.def

----------
#### ProcGetLibraryEntry
Returns the address of a routine within a library. You can pass the result 
directly to **ProcCallFixedOrMovable** to call the routine.

**Pass:**  
ax - Library entry point number.  
bx - Library handle.

**Returns:**  
bx:ax - Library entry point (virtual far pointer).

**Destroyed:**  
Nothing.

**Library:** resource.def

----------
#### ProcInfo
Returns the contents of the *HM_otherInfo* field for a given process. This field 
holds the first thread of this process.

**Pass:**  
bx - Process handle.

**Returns:**  
bx - Contents of *HM_otherInfo* field of process (this field holds the 
first thread of this process).

**Destroyed:**  
Nothing.

**Library:** geode.def

----------
#### QueueGetMessage
Returns the next event from a given event queue; this routine blocks the 
queue if it is currently empty until an event is added which can be returned.

**Pass:**  
bx - Handle of event queue.

**Returns:**  
ax - Event handle.

**Destroyed:**  
Nothing.

**Library:** geode.def

----------
#### QueuePostMessage
Adds the passed event to the specified event queue.

**Pass:**  
bx - Handle of event queue.  
ax - Event to post.  
si - Calling thread.  
di - **MessageFlags** though only MF_INSERT_AT_FRONT is used 
(to place the message at the front of the queue).

**Returns:**  
Nothing.

**Destroyed:**  
Nothing.

**Library:** geode.def

[Routines H-L](asmh_l.md) <-- [Table of Contents](../asmref.md) &nbsp;&nbsp; --> [Routines R-U](asmr_u.md)
